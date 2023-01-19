// Brian Hong

#include "PCB.h"

PCB::PCB(int PID, int p, std::string&& s){
  pid = PID;
  priority = p;
  state = s;
  pc = 0;
  page = 0;
}

int PCB::GetPID() const{
  return pid;
}

int PCB::GetPriority() const{
  return priority;
}

std::string PCB::GetState() const{
  return state;
}

void PCB::SetState(std::string&& s){
  state = s;
}

void PCB::SetPriority(int p){
  priority = p;
}

int PCB::GetPC() const{
  return pc;
}

void PCB::SetPC(unsigned int address){
  pc = address;
}

int PCB::GetPage() const{
  return page;
}

void PCB::SetPage(int p){
  page= p;
}