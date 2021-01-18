#pragma once

#include "Game.h"
#include <iostream>

#if defined won_game32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Game::Game(int w, int h) : window_width(w), window_height(h){

    hero = new Enemy();

    villain = new Rect(-.125,.75, .15,.15,0,1,1);

    projectile_speed = .003;

    won_game = lost_game = false;
}

void Game::draw(){
    
    if(won_game){
        renderText("YOU WIN", -.1, .1);
    }else{
        villain->draw();
    }

    if(lost_game){
        renderText("GAME OVER", -.2, .1);
    }else{
        hero->draw();
        for(Rect* r : projectiles){
            r->draw();
        }
    }
}


void Game::keyDown(unsigned char key, float x, float y) {
    if(!lost_game){
        hero->keyDown(key,x,y);
        if(key == ' '){
            fire();
        }
    }
}

void Game::keyUp(unsigned char key, float x, float y){
    if(!lost_game)
        hero->keyUp(key,x,y);
}

void Game::idle(){
    
    if(!lost_game){
        hero->idle();

        if(!won_game && checkCollision(*hero,*villain)){
            lost_game = true;
        }

        for(Rect* r : projectiles){
            //move bullet up
            r->placeY(r->grabY() + projectile_speed);
            if(!won_game && checkCollision(*r,*villain)){
                won_game = 1;
            }
        }
    }
    
}

void Game::fire(){
    projectiles.push_front(new Rect(hero->grabX() + hero->grabW()/2, hero->grabY(), .01,.1,1,1,1));
}

void Game::renderText(std::string text, float x, float y){
    glColor3f(1, 1, 1);
    float offplace = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x+offplace, y-2*(float)glutBitmapHeight(GLUT_BITMAP_HELVETICA_12)/window_height);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
        offplace += (2*(float)glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, text[i]) / window_width);
    }
}

bool Game::checkCollision(const Rect& a, const Rect& b) const{
    
    return  (a.grabX() < (b.grabX() + b.grabW()) && b.grabX() < (a.grabX() + a.grabW())) &&
            (a.grabY() > (b.grabY() - b.grabH()) && b.grabY() > (a.grabY() - a.grabH()));
}

Game::~Game(){
    for(Rect* r : projectiles){
        delete r;
    }
    delete hero;
    delete villain;
}