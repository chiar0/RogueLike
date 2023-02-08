#pragma once

#include <chrono>

class Timer {
    private:
        static Timer* instance;
        std::chrono::system_clock::time_point startTime;
        std::chrono::duration<float> deltaTime;
        float timeScale;

    public:
        Timer();
        static Timer* Instance();
        static void release();
        void reset();
        float DeltaTime();
        void TimeScale(float t = 1.0f);
        float TimeScale();
        void tick();
};