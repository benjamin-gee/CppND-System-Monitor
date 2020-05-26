#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

#include "process.h"
#include "linux_parser.h"
#include "format.h"
#include <iostream>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {}

// DONE
int Process::Pid() { 
    return pid_; 
}

// DONE
float Process::CpuUtilization() {
    float seconds = LinuxParser::ActiveJiffies() - (LinuxParser::UpTime(pid_) / sysconf(_SC_CLK_TCK));
    cpu_util = ((((LinuxParser::ActiveJiffies(pid_) + LinuxParser::IdleJiffies(pid_)) / sysconf(_SC_CLK_TCK))) / seconds);
    return cpu_util;
}

// DONE
string Process::Command() { 
    return LinuxParser::Command(pid_); 
}

// DONE
string Process::Ram() { 
    ram_ = std::stof(LinuxParser::Ram(pid_)) * 0.001;
    return std::to_string(ram_); 
}

// DONE
string Process::User() { 
    return LinuxParser::User(pid_); 
}

// DONE
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
}

// DONE
bool Process::operator<(Process const& a) const { 
   return (a.cpu_util < cpu_util); 
}