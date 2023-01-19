// Brian Hong

#include "RAM.h"
#include "PCB.h"

RAM::RAM(int frames, int pages, int PID, int ts){
  frame = frames;
  page = pages;
  pid = PID;
  time_stamp = ts;
}

int RAM::GetPID() const{
  return pid;
}

int RAM::GetFrame() const{
  return frame;
}

int RAM::GetPage() const{
  return page;
}

int RAM::GetTS() const{
  return time_stamp;
}

void RAM::SetPage(int pages){
  page = pages;
}

void RAM::SetPID(int PID){
  pid = PID;
}

void RAM::SetTS(int ts){
  time_stamp = ts;
}