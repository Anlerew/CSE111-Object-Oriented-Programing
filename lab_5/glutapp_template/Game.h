#ifndef Game_h
#define Game_h

#include "Enemy.h"
#include "Rect.h"
#include <string>
#include <deque>

class Game{

    Enemy* hero;
    Rect* villain;
    std::deque<Rect*> projectiles;
    
    float projectile_speed;
    bool won_game, lost_game;
    int window_width, window_height;

    public:
        Game(int , int );

        void draw();

        void keyDown(unsigned char key, float x, float y);

        void keyUp(unsigned char key, float x, float y);

        void idle();

        void fire();

        void renderText(std::string text, float x, float y);

        bool checkCollision(const Rect& one, const Rect& two) const;

        ~Game();
};


#endif