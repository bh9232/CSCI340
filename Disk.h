// Brian Hong

#pragma once

#include "PCB.h"

#include <iostream>
#include <string>
#include <vector>

class Disk {
public:
  Disk();
  void PushToDisk(int id, std::string file);
  int GetDiskPID();
  std::string GetFileName();
  std::string DisplayIOQueue();
  void DiskPop();
  void PrintVector(std::vector<int>);
private:
  std::vector<int> io_queue;
  std::vector<std::string> files;
};