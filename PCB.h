// Brian Hong

#pragma once

#include <string>

class PCB {
public:
  PCB(int PID, int p, std::string&& s);
  int GetPID() const;
  int GetPriority() const;
  std::string GetState() const;
  int GetPC() const;
  int GetPage() const;
  void SetState(std::string&& s);
  void SetPriority(int p);
  void SetPC(unsigned int address);
  void SetPage(int p);
private:
  int pid;
  int priority;
  unsigned int pc = 0;
  int page = 0;
  std::string state;
};