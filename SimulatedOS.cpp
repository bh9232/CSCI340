// Brian Hong

#include "SimulatedOS.h"

SimulatedOS::SimulatedOS(int numDisks, int numRAM, int pageSize){
  num_disks = numDisks;
  num_ram = numRAM;
  page_size = pageSize;
  num_frames = numRAM/pageSize;
  pids = 1;
  time_counter = 0;
  cpu_frame = -1;
  marked_frame = 0;
  fetching = false;
  for(int i = 0; i < num_frames; i++){
    RAM ram(i, -1, -1, time_counter);
    time_counter++;
    frame_table.push_back(ram);
  }
  for(int i = 0; i < num_disks; i++){
    Disk hdd;
    disks.push_back(hdd);
  }
}

void SimulatedOS::NewProcess(int priority){
  PCB process(pids, priority, "ready");
  if(processes.empty()){
    cpu_pid = pids;
    process.SetState("executing");
  }else if(priority > processes[cpu_pid-1].GetPriority()){
    processes[cpu_pid-1].SetState("ready");
    cpu_pid = pids;
    process.SetState("executing");
  }
  processes.push_back(process);
  UpdateCPU();
  UpdateFrame(0, pids);
  pids++;
}

void SimulatedOS::Exit(){
  processes[cpu_pid-1].SetState("terminated");
  processes[cpu_pid-1].SetPriority(-1);
  processes[cpu_pid-1].SetPC(-1);
  processes[cpu_pid-1].SetPage(-1);
  for(int i = 0; i < frame_table.size(); i++){
    if(frame_table[i].GetPID() == cpu_pid){
      frame_table[i].SetPage(-1);
      frame_table[i].SetPID(-1);
      frame_table[i].SetTS(0);
    }
  }
  UpdateCPU();
}
void SimulatedOS::DiskReadRequested(int diskNum, std::string fileName){
  processes[cpu_pid-1].SetState("waiting");
  disks[diskNum].PushToDisk(cpu_pid, fileName);
  UpdateCPU();
}

void SimulatedOS::FetchFrom(unsigned int memoryAddress){
  fetching = true;
  processes[cpu_pid-1].SetPC(memoryAddress);
  int page = memoryAddress/page_size;
  processes[cpu_pid-1].SetPage(page);
  UpdateCPU();
  UpdateFrame(page, cpu_pid);
  fetching = false;
}

void SimulatedOS::DiskJobCompleted (int diskNum){
  processes[disks[diskNum].GetDiskPID()-1].SetState("ready");
  disks[diskNum].DiskPop();
  UpdateCPU();
  UpdateFrame(processes[cpu_pid-1].GetPage(), processes[cpu_pid-1].GetPID());
}

void SimulatedOS::PrintCPU(){
  if(processes.empty()){
    std::cout << "CPU: idle" << std::endl;
  }else{
    std::cout << "CPU: " << cpu_pid << std::endl;
  }
}

void SimulatedOS::PrintReadyQueue(){
  std::cout << "Ready-Queue: ";
  for(int i = 0; i < processes.size(); i++){
    if(processes[i].GetState() == "ready"){
      std::cout << processes[i].GetPID() << " ";
    }
  }
  std::cout << std::endl;
}

void SimulatedOS::PrintRAM(){
  std::cout << "Frame\tPage\tPID" << std::endl;
  for(int i = 0; i < num_frames; i++){
    std::cout << frame_table[i].GetFrame() << "\t" << frame_table[i].GetPage() 
    << "\t" << frame_table[i].GetPID() << std::endl;
  }
}

void SimulatedOS::PrintDisk(int diskNum){
  if(diskNum <= num_disks){
    if(disks[diskNum].GetDiskPID() == 0){
      std::cout << "Disk " << diskNum << ": Idle" << std::endl;
    }else{
      std::cout << "Disk " << diskNum << ": PID " << disks[diskNum].GetDiskPID() 
      << ", " << disks[diskNum].GetFileName() << std::endl;
    }
  }else{
    std::cout << "Disk number does not exist" << std::endl;
  }
}

void SimulatedOS::PrintDiskQueue(int diskNum){
  if(diskNum <= num_disks){
    std::cout << "Disk " << diskNum << " I/O-queue: " << disks[diskNum].DisplayIOQueue() << std::endl;
  }else{
    std::cout << "Disk number does not exist" << std::endl;
  }
}

// Helper Methods 
void SimulatedOS::UpdateCPU(){
  PCB temp = processes.front();
  for(int i = 0; i < processes.size(); i++){
    if((temp.GetState() == "waiting") || (temp.GetState() == "terminated")){
      temp = processes[i];
      i++;
    }
    if((processes[i].GetState() == "waiting") || (processes[i].GetState() == "terminated")){
      i++;
    }else if(processes[i].GetPriority() > temp.GetPriority()){
      temp = processes[i];
    }
  }
  if((processes[cpu_pid-1].GetState() == "executing") && (temp.GetPriority() > processes[cpu_pid-1].GetPriority())){
    processes[cpu_pid-1].SetState("ready");
  }
  temp.SetState("executing");
  processes[temp.GetPID()-1] = temp;
  cpu_pid = temp.GetPID();
  SetMarkedFrame();
  SetCPUFrame();
}

void SimulatedOS::SetMarkedFrame(){
  RAM temp = frame_table.front();
  for(int i = 0; i < frame_table.size(); i++){
    if(frame_table[i].GetTS() < temp.GetTS()){
      temp = frame_table[i];
    }
    if(frame_table[i].GetPID() == -1){
      marked_frame = i;
      return;
    }
  }
  marked_frame = temp.GetFrame();
}

void SimulatedOS::SetCPUFrame(){
  RAM temp = frame_table.front();
  RAM temp2 = frame_table.back();
  if((temp.GetPID() == cpu_pid) && (temp2.GetPID() == cpu_pid)){
    if(temp2.GetTS() > temp.GetTS()){
      cpu_frame = temp2.GetFrame();
    }
    frame_table[cpu_frame].SetTS(time_counter);
    time_counter++;
    temp = frame_table[1];
  }
  for(int i = 0; i < frame_table.size(); i++){
    if(frame_table[i].GetPID() == cpu_pid){
      temp2 = frame_table[i];
      if(temp.GetPID() == cpu_pid){
        if(temp2.GetTS() > temp.GetTS()){
          temp = temp2;
        }else{
          temp2 = temp;
        }
      }
    }
  }
  temp = temp2;
  cpu_frame = temp.GetFrame();
  frame_table[temp.GetFrame()].SetTS(time_counter);
  time_counter++;
}

void SimulatedOS::UpdateFrame(int pages, int PID){
  for(int i = 0; i < frame_table.size(); i++){
    if((frame_table[i].GetPage() == pages) && (frame_table[i].GetPID() == PID)){
      frame_table[i].SetTS(time_counter);
      time_counter++;
      return;
    }
  }
  frame_table[marked_frame].SetPage(pages);
  frame_table[marked_frame].SetPID(PID);
  frame_table[marked_frame].SetTS(time_counter);
  time_counter++;
  if(cpu_frame > 0){
    frame_table[cpu_frame].SetTS(time_counter);
    time_counter++;
  }
  if(fetching){
    cpu_frame = marked_frame;
    frame_table[cpu_frame].SetTS(time_counter);
    time_counter++;
    SetMarkedFrame();
  }else{
    SetCPUFrame();
    SetMarkedFrame();
  }
}

// DEBUGGING FUNCTIONS
void SimulatedOS::PrintProcess(std::vector<PCB> process){
  for(int i = 0; i < process.size(); i++){
    std::cout << process[i].GetPID() << ":" << process[i].GetPriority() << ", ";
  }
  std::cout << std::endl;
}

void SimulatedOS::PrintVector(std::vector<int> vector){
  for(int i = 0; i < vector.size(); i++){
    std::cout << vector[i] << ", ";
  }
  std::cout << std::endl;
}