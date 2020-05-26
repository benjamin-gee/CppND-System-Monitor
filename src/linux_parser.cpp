#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE 
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// DONE
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float value = 0;
  float memTotal_ = 0;
  float memFree_ = 0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal_ = value;
        }
        if (key == "MemFree:") {
          memFree_ = value;
          break;
        }
      }
    }
  }
  return (memTotal_-memFree_)/memTotal_;
}  

// DONE
long LinuxParser::UpTime() { 
  std::string line;
  long uptime = 0;
  long idletime = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  return uptime; 
}

// UNUSED 
// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// DONE
// Returns the sum of #14 and #15 from /proc/[PID]/stat
long LinuxParser::ActiveJiffies(int pid) { 
  std::string line;
  std::string value;
  long total_time = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      for (int i = 1; i < 16; i++) {
        linestream >> value;
        if (i == 14) {
          total_time += std::stol(value);
        }
        if (i == 15) {
          total_time += std::stol(value);
        }
      }
    }
  }
  return total_time; 
}

// DONE
// Returns #1 from /proc/uptime
long LinuxParser::ActiveJiffies() { 
  string line;
  string value;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
      std::getline(filestream,line);
      std::istringstream linestream(line);
      linestream >> value;
  }
  return std::stol(value);
}

// DONE
// Returns #16 and #17 from /proc/[PID]/stat
long LinuxParser::IdleJiffies(int pid) { 
  std::string line;
  std::string value;
  long idle_time = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      for (int i = 1; i < 18; i++) {
        linestream >> value;
        if (i == 16) {
          idle_time += std::stoi(value);
        }
        if (i == 17) {
          idle_time += std::stoi(value);
        }
      }
    }
  }
  return idle_time; 
}

// UNUSED 
// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {};}

// DONE
int LinuxParser::TotalProcesses() {   
  string line;
  string key;
  int value;
  int proc_ = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          proc_ = value;
          break;
        }
      }
    }
  }
  return proc_;
}

// DONE
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value = 0;
  int proc_ =0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          proc_ = value;
          break;
        }
      }
    }
  }
  return proc_;
}

// DONE
string LinuxParser::Command(int pid) {
  std::string line;
  std::string key;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }  

  return line;
}

// DONE
string LinuxParser::Ram(int pid) { 
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value ) {
        if (key == "VmSize:") {
            return value;
        }
      }
    }
  }
  return value; 
}

// DONE
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// DONE
string LinuxParser::User(int pid) { 
  std::string uid = LinuxParser::Uid(pid);
  string line;
  string test_user;
  string test_uid;
  string dummy;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> test_user >> dummy >> test_uid ) {
        if (test_uid == uid) {
          return test_user;
        }
      }
    }
  }
  return test_user;

}

// DONE
long LinuxParser::UpTime(int pid) { 
  std::string line;
  std::string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {
      std::istringstream linestream(line);
      for (int i = 0; i < 22; i++) {
        linestream >> value;
      }
      return std::stol(value);
    }
  }
  
  return std::stol(value);   
}