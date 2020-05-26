#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   // DONE
  std::vector<Process>& Processes();  // DONE
  float MemoryUtilization();          // DONE
  long UpTime();                      // DONE
  int TotalProcesses();               // DONE
  int RunningProcesses();             // DONE
  std::string Kernel();               // DONE
  std::string OperatingSystem();      // DONE

  // DONE
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::vector<int> pids_ = {};
};

#endif