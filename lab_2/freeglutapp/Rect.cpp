#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>

Rect::Rect (){
    x = -0.5;
    y = 0.5;
    w = 0.5;
    h = 0.5;
    taken = false;
    symbol = no;
}

Rect::Rect (float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    taken = false;
    symbol = no;
}


bool Rect::contains(float mx, float my){
    return mx >= x && mx <= x + w && my <= y && my >= y - h;
}

void Rect::draw(){
    glLineWidth(8);
    if (symbol == o){
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        
        float inc = 0.1;
        
        for(float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f((w/2-0.1)*cos(theta)+x+(w/2), (w/2-0.1)*sin(theta) + y - h/2);
            glVertex2f((w/2-0.1)*cos(theta+inc)+x+(w/2), (w/2-0.1)*sin(theta+inc) + y - h/2);
        }
        
        glEnd();
    }
    else if (symbol == c){
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(x + 0.1, y - 0.1);
        glVertex2f(x + w - 0.1, y - h + 0.1);
        
        glVertex2f(x + 0.1, y - h + 0.1);
        glVertex2f(x + w - 0.1, y - 0.1);
        glEnd();
    }
    
    
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    
    glEnd();
    }
