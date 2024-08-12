#pragma once

#include <chrono>

class Timer
{
public:
    void Start()
    {
        startTime = std::chrono::system_clock::now();
        running = true;
    }
    
    void Stop()
    {
        endTime = std::chrono::system_clock::now();
        running = false;
    }
    
    double ElapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(running)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = endTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    }
    
    double ElapsedSeconds()
    {
        return ElapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    bool running = false;
};
