// Brian Hong

#pragma once

#include "PCB.h"
#include "Disk.h"
#include "RAM.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class SimulatedOS{
public:
  SimulatedOS(int numDisks, int numRAM, int pageSize);
  void NewProcess(int priority);
  void Exit();
  void DiskReadRequested(int diskNum, std::string fileName);
  void FetchFrom(unsigned int memoryAddress);
  void DiskJobCompleted (int diskNum);
  void PrintCPU();
  void PrintReadyQueue();
  void PrintRAM();
  void PrintDisk(int diskNum);
  void PrintDiskQueue(int diskNum);
private:
  // Helper Methods 
  void UpdateCPU();
  void SetMarkedFrame();
  void SetCPUFrame();
  void UpdateFrame(int pages, int PID);
  // Debugging Methods
  void PrintProcess(std::vector<PCB> process);
  void PrintVector(std::vector<int> vector);
  // variables
  int pids;
  int num_disks;
  int num_ram;
  int page_size;
  int num_frames;
  int cpu_pid;
  int cpu_frame;
  int marked_frame;
  int time_counter;
  bool fetching;
  std::vector<PCB> processes;
  std::vector<Disk> disks;
  std::vector<RAM> frame_table;
};