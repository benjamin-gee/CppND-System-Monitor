#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);                        // Constructor
  int Pid();                               // DONE
  float CpuUtilization();                  // DONE  
  std::string Command();                   // DONE
  std::string Ram();                       // DONE
  std::string User();                      // DONE
  long int UpTime();                       // DONE
  bool operator<(Process const& a) const;  // DONE

  // DONE
 private:
  int pid_;
  float cpu_util;
  int ram_ = 0;
};

#endif