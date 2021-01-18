#ifndef Enemy_h
#define Enemy_h

#include "Rect.h"

class Enemy: public Rect{
    float dx, dy, speed;

    public:
        Enemy();

        void idle();

        void keyUp(unsigned char key, float x, float y);
        void keyDown(unsigned char key, float x, float y);
        float getSpeed() const;
};

#endif