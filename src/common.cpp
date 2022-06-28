//
// Created by znaczek on 27.06.22.
//

#include <chrono>

double getMills() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

