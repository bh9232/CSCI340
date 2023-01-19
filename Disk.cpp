// Brian Hong

#include "Disk.h"

Disk::Disk(){
  io_queue.clear();
  files.clear();
}

void Disk::PushToDisk(int id, std::string file){
  io_queue.push_back(id);
  files.push_back(file);
}

int Disk::GetDiskPID(){
  if(io_queue.empty()){
    return 0;
  }else{
    return io_queue[0];
  }
}

std::string Disk::GetFileName(){
  if(io_queue.empty()){
    return "Empty";
  }else{
    return files[0];
  }
}

std::string Disk::DisplayIOQueue(){
  std::string result;
  if(io_queue.empty() || io_queue.size() == 1){
    result = "Empty";
  }else{
    for(int i = 1; i < io_queue.size(); i++){
      result += std::to_string(io_queue[i]) + " ";
    }
  }
  return result;
}

void Disk::DiskPop(){
  io_queue.erase(io_queue.begin());
  files.erase(files.begin());
}

void Disk::PrintVector(std::vector<int> vector){
  for(int i = 0; i < vector.size(); i++){
    std::cout << vector[i] << " ";
  }
  std::cout << std::endl;
}