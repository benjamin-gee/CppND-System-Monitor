#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE
Processor& System::Cpu() { 
    return cpu_; 
}

// DONE
vector<Process>& System::Processes() { 
    pids_ = LinuxParser::Pids();

    for (auto i:pids_) {
        processes_.push_back(Process(i));
    }

    std::sort(processes_.begin(),processes_.end());

    return processes_; 
}

// DONE
std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

// DONE
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
}

// DONE
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
}

// DONE
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
}

// DONE
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
}

// DONE
long int System::UpTime() { 
    return LinuxParser::UpTime();
}