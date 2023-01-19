// Brian Hong

#pragma once

#include "PCB.h"

#include <queue>

class RAM{
public: 
  RAM(int frames, int pages, int PID, int ts);
  int GetFrame() const;
  int GetPage() const;
  int GetPID() const;
  int GetTS() const;
  void SetPage(int pages);
  void SetPID(int PID);
  void SetTS(int ts);
private:
  int frame;
  int page;
  int pid;
  int time_stamp;
};