#include <string>

#include "format.h"

using std::string;

// DONE
string Format::ElapsedTime(long int seconds) { 
    int h_ = seconds / 3600;
    seconds = seconds % 3600;
    int m_ = seconds / 60;
    seconds = seconds % 60;
    return std::to_string(h_) + ":" + std::to_string(m_) + ":" + std::to_string(seconds);
}