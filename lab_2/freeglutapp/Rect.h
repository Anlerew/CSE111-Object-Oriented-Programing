#ifndef Rect_h
#define Rect_h
enum Sign {no, o, c};

struct Rect {
    float x;
    float y;
    float w;
    float h;
    
    bool taken;
    Sign symbol;
    
    Rect ();
    
    Rect (float x, float y, float w, float h);
    
    bool contains(float mx, float my);
    
    void draw();
};

#endif
