#pragma once

#include <chrono>

class Timer {
    private:
        static Timer* instance;
        std::chrono::system_clock::time_point startTime;
        std::chrono::duration<float> deltaTime;
        float timeScale;

    public:
        //costruttore
        Timer();
 
        static Timer* Instance();           //genera un nuovo instance
        static void release();              //clear dell'istanza
        void reset();                       //reset del timer
        float getDeltaTime();               //get del delta time
        float getTimeScale();               //getter del time scale
        void setTimeScale(float t = 1.0f);  //setter dello scaling del timer
        void tick();                        //aggiorna il delta time quando viene chiamata la funione
};