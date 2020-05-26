#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <fstream>
#include <regex>

class Processor {
 public:
  float Utilization();  // DONE

  // DONE
 private:
  std::string kProcDirectory_{"/proc"};
  std::string kStatFilename_{"/stat"};
  float user_, nice_, system_, idle_, iowait_, irq_, softirq_, steal_, guest_, guest_nice_, idle, nonIdle, total, totald, idled, prevTotal, prevIdle;
};

#endif