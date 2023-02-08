#include "Timer.hpp"

Timer* Timer::instance = NULL;

Timer* Timer::Instance(){
    if(instance == NULL)
        instance = new Timer();
    
    return instance;
}

void Timer::release(){
    delete instance;
    instance = NULL;
}

Timer::Timer(){
    reset();
    timeScale = 1.0f;
    deltaTime = std::chrono::duration<float>(0.0f);

}

void Timer::reset(){
    startTime = std::chrono::system_clock::now();
}

float Timer::DeltaTime(){
    return deltaTime.count();
}

void Timer::TimeScale(float t){
    timeScale = t;
}

float Timer::TimeScale(){
    return timeScale;
}

void Timer::tick(){
    deltaTime = std::chrono::system_clock::now() - startTime;
}
