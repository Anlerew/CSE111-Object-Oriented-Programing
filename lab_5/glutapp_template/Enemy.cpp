#pragma once

#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : Rect::Rect(-.125,-.6, .15,.15,1,0,1), dx(0), dy(0), speed(.001){

}

void Enemy::idle(){
    x += dx;
    y += dy;
    if(x < -1){
        x = -1;
    }
    if(x + w > 1){
        x = 1- w;
    }
    if(y > 1){
        y = 1;
    }
    if(y - h < -1){
        y = -1 + h;
    }
}
void Enemy::keyDown(unsigned char key, float x, float y) {
    if(key == 'w'){
        dy += speed;
        std::cout<< dx << std::endl;

    }else if(key == 'a'){
        dx += -speed;

    }else if(key == 'd'){
        dx += speed;

    }else if(key == 's'){
        dy += -speed;
    }
}

void Enemy::keyUp(unsigned char key, float x, float y) {
    if(key == 'w'){
        dy += -speed;
    }

    if(key == 's'){
        dy += speed;
    }

    if(key == 'a'){
        dx += speed;
    }

    if(key == 'd'){
        dx += -speed;
    }
}

float Enemy::getSpeed() const{
    return speed;
}
