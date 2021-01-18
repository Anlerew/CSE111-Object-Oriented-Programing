#include <iostream>
#include <cmath>
#include <vector>
#include "Rect.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;


// Store the width and height of the window
int width = 640, height = 640;

bool player_select = false;
bool first_player = true;
bool game_over = false;

vector<Rect> grid;
vector<Rect> box;

bool cpu = true;

bool winner_x(vector<Rect> grid);
bool winner_o(vector<Rect> grid);

// Only 1 Player
void players_1(float x, float y, float width, float height)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-.8, .8);
    glVertex2f(-.8, -.8);
    glVertex2f(-.6, -.8);
    glVertex2f(-.6, .8);
    glEnd();
}

// 2 Players
void players_2(float x, float y, float width, float height)
{
   glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.8);
    glVertex2f(0.2, -0.8);
    glVertex2f(0.4, -0.8);
    glVertex2f(0.4, 0.8);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.8, 0.8);
    glVertex2f(0.8, -0.8);
    glVertex2f(0.6, -0.8);
    glVertex2f(0.6, 0.8);
    glEnd();
}

void verifyGame(vector<Rect> grid){
    if (winner_x(grid)){
        cout << "X WINS THE GAME!" << endl;
        game_over = true;
    }
    if (winner_o(grid)){
        cout << "O WINS THE GAME!" << endl;
        game_over = true;
    }
    
    if (!game_over){
        bool flag = true;
        for (int i = 0; i < grid.size(); i++) {
            if (!grid[i].taken){
                flag = false;
                break;
            }
        }
        if (flag){
            game_over = true;
            cout << "OOF NOBODY WINS THE GAME!" << endl;
        }
    }
}

bool winner_x(vector<Rect> grid){
    Sign move = c;
    if (grid[0].symbol == move && grid[1].symbol ==  move && grid[2].symbol == move){
        return true;
    }
    if (grid[3].symbol == move && grid[4].symbol ==  move && grid[5].symbol == move){
        return true;
    }
    if (grid[6].symbol == move && grid[7].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[0].symbol == move && grid[3].symbol ==  move && grid[6].symbol == move){
        return true;
    }
    if (grid[1].symbol == move && grid[4].symbol ==  move && grid[7].symbol == move){
        return true;
    }
    if (grid[2].symbol == move && grid[5].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[0].symbol == move && grid[4].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[2].symbol == move && grid[4].symbol ==  move && grid[6].symbol == move){
        return true;
    }
}

bool winner_o(vector<Rect> grid){
    Sign move = o;
    if (grid[0].symbol == move && grid[1].symbol ==  move && grid[2].symbol == move){
        return true;
    }
    if (grid[3].symbol == move && grid[4].symbol ==  move && grid[5].symbol == move){
        return true;
    }
    if (grid[6].symbol == move && grid[7].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[0].symbol == move && grid[3].symbol ==  move && grid[6].symbol == move){
        return true;
    }
    if (grid[1].symbol == move && grid[4].symbol ==  move && grid[7].symbol == move){
        return true;
    }
    if (grid[2].symbol == move && grid[5].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[0].symbol == move && grid[4].symbol ==  move && grid[8].symbol == move){
        return true;
    }
    if (grid[2].symbol == move && grid[4].symbol ==  move && grid[6].symbol == move){
        return true;
    }
}


//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (!player_select)
    {
        box.push_back(Rect(-1.0, 1.0, 1.0, 2.0));
        box.push_back(Rect(0.0, 1.0, 1.0, 2.0));
        players_1(-0.65, 0.75, 0.2, 1.5);
        players_2(0.25, 0.75, 0.5, 1.5);
        for (int i = 0; i < box.size(); i++)
        {
            box[i].draw();
        }
    }
    
    for (int i = 0; i < grid.size(); i++) {
        grid[i].draw();
    }
    glFlush();
    glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments:
//    x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
    x = (2.0f*(x / float(width))) - 1.0f;
    y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments:
//    b    - mouse button that was clicked, left or right
//    s      - state, either mouse-up or mouse-down
//    x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
    // Window size has changed
    width = w;
    height = h;
    
    double scale, center;
    double winner_xmin, winner_xmax, winYmin, winYmax;
    
    // Define x-axis and y-axis range
    const double appXmin = -1.0;
    const double appXmax = 1.0;
    const double appYmin = -1.0;
    const double appYmax = 1.0;
    
    // Define that OpenGL should use the whole window for rendering
    glViewport(0, 0, w, h);
    
    // Set up the projection matrix using a orthogridic projection that will
    // maintain the aspect ratio of the scene no matter the aspect ratio of
    // the window, and also set the min/max coordinates to be the disered ones
    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    
    if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
        scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
        center = (appXmax + appXmin) / 2;
        winner_xmin = center - (center - appXmin)*scale;
        winner_xmax = center + (appXmax - center)*scale;
        winYmin = appYmin;
        winYmax = appYmax;
    }
    else {
        scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
        center = (appYmax + appYmin) / 2;
        winYmin = center - (center - appYmin)*scale;
        winYmax = center + (appYmax - center)*scale;
        winner_xmin = appXmin;
        winner_xmax = appXmax;
    }
    
    // Now we use glOrtho to set up our viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(winner_xmin, winner_xmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments:
//    b    - mouse button that was clicked, left or right
//    s      - state, either mouse-up or mouse-down
//    x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
    // Convert from Window to Scene coordinates
    float mx = (float)x;
    float my = (float)y;
    
    windowToScene(mx, my);
    
    if (!player_select)
    {
        if (box[0].contains(mx,my))
        {
            player_select = true;
            cpu = true;
        }
        if (box[1].contains(mx,my))
        {
            player_select = true;
            cpu = false;
        }
    }
    
    else
    {
        if (b == 0){
            if (s == 0){
                for (int i = 0; i < grid.size(); i++) {
                    if (!game_over){
                        if (grid[i].contains(mx, my)){
                            if (!grid[i].taken){
                                if (first_player){
                                    grid[i].symbol = c;
                                }
                                else{
                                    grid[i].symbol = o;
                                }
                                grid[i].taken = true;
                                first_player = !first_player;
                            }
                            verifyGame(grid);
                            if (cpu && !game_over){
                                
                                for (int i = 0; i < grid.size(); i++) {
                                    int v1 = rand() % grid.size();
                                    if (!grid[v1].taken){
                                        grid[v1].symbol = o;
                                        grid[v1].taken = true;
                                        first_player = !first_player;
                                        break;
                                    }
                                }
                                verifyGame(grid);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments:
//    x, y - current coordinates of the mouse
//-------------------------------------------------------

void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	// Your code here...

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments:
//    key  - the key that was pressed
//    x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
    
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'cpu':
            if (game_over){
                for (int i = 0; i < grid.size(); i++) {
                    grid[i].symbol = no;
                    grid[i].taken = false;
                    game_over = false;
                    first_player = true;
                }
                cpu = true;
            }
            break;
        case 'player':
            if (game_over){
                for (int i = 0; i < grid.size(); i++) {
                    grid[i].symbol = no;
                    grid[i].taken = false;
                    game_over = false;
                    first_player = true;
                }
                cpu = false;
            }
            break;
        case 'neither':
            if (game_over){
                for (int i = 0; i < grid.size(); i++) {
                    grid[i].symbol = no;
                    grid[i].taken = false;
                    game_over = false;
                    first_player = true;
                }
            }
            break;
        default:
            break;
    }
    
    // After all the state changes, redraw the scene
    glutPostRedisplay();
}

void appKeyboardUpFunc(unsigned char key, int x, int y) {

}


void idle() {
    
}


int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    
    // Setup window position, size, and title
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(width, height);
    glutCreateWindow("TIC TAC TOE CSE 165");
    
    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    
    grid.push_back(Rect(-0.8, 0.8, 0.4, 0.4));
    grid.push_back(Rect(-0.2, 0.8, 0.4, 0.4));
    grid.push_back(Rect(0.4, 0.8, 0.4, 0.4));
    
    grid.push_back(Rect(-0.8, 0.2, 0.4, 0.4));
    grid.push_back(Rect(-0.2, 0.2, 0.4, 0.4));
    grid.push_back(Rect(0.4, 0.2, 0.4, 0.4));
    
    grid.push_back(Rect(-0.8, -0.4, 0.4, 0.4));
    grid.push_back(Rect(-0.2, -0.4, 0.4, 0.4));
    grid.push_back(Rect(0.4, -0.4, 0.4, 0.4));
    
    // Set callback for drawing the scene
    glutDisplayFunc(appDrawScene);
    
    // Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);
    
    // Set callback to handle mouse clicks
    glutMouseFunc(appMouseFunc);
    
    // Set callback to handle mouse dragging
    glutMotionFunc(appMotionFunc);
    
    // Set callback to handle keyboad events
    glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);
    
    // Start the main loop
    glutMainLoop();
}
