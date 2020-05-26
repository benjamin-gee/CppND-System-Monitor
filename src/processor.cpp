#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

// DONE
float Processor::Utilization() { 
  std::string line, key;
  std::ifstream stream(kProcDirectory_ + kStatFilename_);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.begin()+4, ' ', '_');
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "cpu_") {
          linestream >> user_ >> nice_ >> system_ >> idle_ >> iowait_ >> irq_ >> softirq_ >> steal_ >> guest_ >> guest_nice_;
        }
      }
    }
  }

  idle = idle_ + iowait_;
  nonIdle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;
  total = idle + nonIdle;
  
  totald = total - prevTotal;
  idled = idle - prevIdle;
  
  prevTotal = total;
  prevIdle = idle;

  return (totald - idled)/totald;
}