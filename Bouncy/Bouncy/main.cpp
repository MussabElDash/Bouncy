#include <cstdio>
#include <functional>
#include "PlatformCompatibility.h"
#include "Wall.h"

const int XSIZE = 13, YSIZE = 12, ZSIZE = 12;
double eyeX, eyeY, eyeZ, centerX, centerY, centerZ;
POINT arrowAngle = MAKE_POINT(0, 0, 0);
float ballRadius = 0.5;
bool stopped = 1;
std::vector<Wall> walls;
POINT ballPosition = MAKE_POINT(6, 6, 0);
POINT ballVector = MAKE_POINT(0, 0, ZSIZE / 500.0);
int result = 0;
int circleMesh = 200;
int ended = 0;
int lastScore = 0;
int beforeAim = 1;
double initialAngle = 0;
int wasBeforeAim = 0;
int slowMotion = 0;
int totalScore = 0;

void calculateCollisions(){
    int all = 0;
    for(Wall wall : walls){
        int score = wall.getScore(ballPosition, ballRadius);
        if(score != 0){
            if(score == -111111111){
                score = 0;
            }
            POINT planeVector = wall.planeVector;
            ballVector.X *= planeVector.X == 1 ? -1 : 1;
            ballVector.Y *= planeVector.Y == 1 ? -1 : 1;
            ballVector.Z *= planeVector.Z == 1 ? -1 : 1;

            if(planeVector.Z != 0){
                ended = 1;
                stopped = 1;
                lastScore = all;
                return;
            }

            result += score;
            all += score;
            totalScore += score;
        }
    }
    if(all != 0){
        lastScore = all;
    }
}

void timer(int v) {
    if(!stopped){
	   ballPosition.X += ballVector.X * (slowMotion == 1 ? 0.2 : 1);
	   ballPosition.Y += ballVector.Y * (slowMotion == 1 ? 0.2 : 1);
	   ballPosition.Z += ballVector.Z * (slowMotion == 1 ? 0.2 : 1);
    }
	glutTimerFunc(10, timer, 1);
    glutPostRedisplay();
}

void beginQuads(){
    glBegin(GL_QUADS);
}

void wall(double thickness){
    glPushMatrix();
    glTranslated(0.5, 0.5*thickness, 0.5);
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void house(double size)
{
    // Drawing the walls
    wall(size);
    glPushMatrix();
    glRotated(90.0, 0.0, 0.0, 1.0);
    wall(size);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    wall(size);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, 1.0 - 0.02, 0.0);
    wall(size);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.0, 0.0, 0.0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    wall(size);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, 0.0, 1.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    wall(size);
    glPopMatrix();
    // Drawing the roof
    glPushMatrix();
    glTranslated(0.5, 1.0, 0.5);
    glRotated(-90, 1, 0, 0);
    glRotated(45, 0, 0, 1);
    glutSolidCone(0.9, 0.5, 4, 9);
    glPopMatrix();
}


void drawArrowIfPossible(){
    if(stopped && !ended && !beforeAim && !slowMotion){
        glPushMatrix();
        glRotated(5 * arrowAngle.X, 0.0, 0.0, 1.0);
        glTranslated(0.0, ballRadius + 0.05, 0.0);
        glRotated(-90, 1.0, 0.0, 0.0);
        glutSolidCone(ballRadius/2, ballRadius/1.5, 100, 100);
        glPopMatrix();
    }
}

void drawSphere(void){
    glPushMatrix();
    glColor3d(0.5, 0.5, 0.5);
    glTranslated(ballPosition.X, ballPosition.Y, ballPosition.Z);
    glutWireSphere(ballRadius, circleMesh, circleMesh);
    drawArrowIfPossible();
    glPopMatrix();
}

void print(double x, double y, double z, char* string){
    int len;
    glRasterPos3f(x, y, z);
    len = (int)strlen(string);
    for(int q = 0; q < len; q++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[q]);
    }
}

void displayWire(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //set the world
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt = 5.0;
    gluPerspective(60, 1, 0.1, 100);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
    if(!stopped){
        eyeZ += ballVector.Z * (slowMotion == 1 ? 0.2 : 1);
    }
    //gluLookAt(x, y, z + 10, x, y, z, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(!ended && !stopped){
        calculateCollisions();
    }
    if(ballVector.Z < 0){
        stopped = 1;
    }
    //printf("%d\n", result);
    drawSphere();
    
    /*house(0.02);
     // Drawing the first row
     glPushMatrix();
     for (int i = 0; i<5; i++){
     glTranslated(1.5, 0.0, 0.0);
     house(0.02);
     }
     glPopMatrix();
     // Drawing the second row
     glPushMatrix();
     glTranslated(0, 0, 5);
     house(0.02);
     for (int j = 0; j<5; j++){
     glTranslated(1.5, 0.0, 0.0);
     house(0.02);
     }
     glPopMatrix();*/
    
    // Testing wall
    for(Wall wall : walls){
        wall.draw();
    }

    glColor3d(0, 0, 0);
    char* stC[100];
    sprintf((char*)stC, "Score: %d", result);
    print(eyeX + 5, eyeY, eyeZ + 10, (char*)stC);

    sprintf((char*)stC, "Last Score: %d", lastScore);
    print(eyeX + 5, eyeY - 1, eyeZ + 10, (char*)stC);

    sprintf((char*)stC, "Total Score: %d", totalScore);
    print(eyeX + 5, eyeY - 2, eyeZ + 10, (char*)stC);

    sprintf((char*)stC, "Delta Y: %lf", ballVector.Y);
    print(eyeX + 5, eyeY + 3, eyeZ + 10, (char*)stC);

    sprintf((char*)stC, "Delta X: %lf", ballVector.X);
    print(eyeX + 5, eyeY + 2, eyeZ + 10, (char*)stC);

    sprintf((char*)stC, "Camera Mode: %s", slowMotion == 1 ? "Slow Motion" : "Normal");
    print(eyeX + 5, eyeY + 1, eyeZ + 10, (char*)stC);
    glColor3d(1, 1, 1);

    glFlush();
}


void mySpecial(int key, int x, int y)
{
    if(beforeAim || slowMotion){
        return;
    }
    switch (key){
        case GLUT_KEY_RIGHT:
            if(stopped)
                arrowAngle.X ++;
            break;
        case GLUT_KEY_LEFT:
            if(stopped)
                arrowAngle.X--;
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
    }
    
    glutPostRedisplay();
}

void keyboardHandler(unsigned char key, int x, int y){
    
    double angle = 0;
    switch(key){
        case 13:
            if(!stopped){
                break;
            }
            if(ended){
                slowMotion = 1;
                if(!wasBeforeAim){
                    angle = initialAngle;
                    angle = arrowAngle.X * 5 + 90;
                    while(angle >= 360) angle -= 360;
                    ballVector.X = cos(angle * M_PI / 180.0) * ballRadius / 5;
                    ballVector.Y = sin(angle * M_PI / 180.0) * ballRadius / 5;
                }
                ended = 0;
                stopped = 0;
                ballPosition = MAKE_POINT(6, 6, 0);
                eyeX = 6;
                eyeY = 6;
                eyeZ = -10;
                result = 0;
                lastScore = 0;
                ballVector.Z *= -1;
                break;
            }
            if(beforeAim){
                stopped = 0;
                wasBeforeAim = 1;
                break;
            }
            wasBeforeAim = 0;
            initialAngle = arrowAngle.X;
            angle = arrowAngle.X * 5 + 90;
            while(angle >= 360) angle -= 360;
            ballVector.X = cos(angle * M_PI / 180.0) * ballRadius / 5;
            ballVector.Y = sin(angle * M_PI / 180.0) * ballRadius / 5;
            printf("%lf %lf, %lf %lf\n", cos(arrowAngle.X), ballRadius, sin(arrowAngle.X), ballRadius);
            stopped = 0;
            break;
        case 'a':
            beforeAim = 0;
            break;
        case 'n':
                beforeAim = 1;
                wasBeforeAim = 0;
                slowMotion = 0;
                ended = 0;
                stopped = 1;
                ballPosition = MAKE_POINT(6, 6, 0);
                eyeX = 6;
                eyeY = 6;
                eyeZ = -10;
                result = 0;
                lastScore = 0;
                ballVector = MAKE_POINT(0, 0, ZSIZE / 500.0);
            break;
    }
}

/*
void mySpecial(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_UP:
            eyeY ++;
            break;
        case GLUT_KEY_DOWN:
            eyeY --;
            break;
        case GLUT_KEY_LEFT:
            eyeX++;
            break;
        case GLUT_KEY_RIGHT:
            eyeX --;
            break;
    }
    
    glutPostRedisplay();
}*/

int print(int x){
    printf("%d\n", x);
    return 1;
}

void* pass(int (*f)(int)){
    
    std::function<int()> g = [f](){
        printf("%d\n", f(2));
        return 1;
    };
    if(g() == 1){
        return (void*) &"123";
    }
    else{
        return nullptr;
    }
}

void initWalls(){
    POINT start[5] = {
        MAKE_POINT(0, 0, 0), // Bottom
        MAKE_POINT(0, 1, 0), // Right
        MAKE_POINT(XSIZE - 1, 1, 0), // LEFT
        MAKE_POINT(0, YSIZE, 0), // Up
        MAKE_POINT(0, 0, ZSIZE)}; // Front
    POINT end[5] = {
        MAKE_POINT(XSIZE, 1, ZSIZE),
        MAKE_POINT(1, YSIZE, ZSIZE),
        MAKE_POINT(XSIZE, YSIZE, ZSIZE),
        MAKE_POINT(XSIZE, YSIZE + 1, ZSIZE),
        MAKE_POINT(XSIZE, YSIZE + 1, ZSIZE + 1)};
    POINT planeVector[5] = {
        MAKE_POINT(0, 1, 0),
        MAKE_POINT(1, 0, 0),
        MAKE_POINT(1, 0, 0),
        MAKE_POINT(0, 1, 0),
        MAKE_POINT(0, 0, 1)};
    for(int q = 0; q < 5; q++){
        walls.push_back(Wall(start[q],
                             end[q],
                             MAKE_POINT(1, 1, 1),
                             planeVector[q],
                             glPushMatrix,
                             glPopMatrix,
                             glTranslated,
                             glScaled,
                             glutSolidCube,
                             glColor3d));
    }
}

int main(int argc, char** argv)
{
    srand(time(nullptr));
    // printf("%s\n", (char*)pass(print));
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set
    //display mode
    glutInitWindowSize(640, 480); // set window size
    glutInitWindowPosition(200, 150); // set window position on
    //screen
    glutCreateWindow("Bouncy"); // open the screen window
    glutDisplayFunc(displayWire); // register redraw function
    glutSpecialFunc(mySpecial);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(1, timer, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    eyeX = 6;
    eyeY = 6;
    eyeZ = -10;
    centerX = eyeX;
    centerY = eyeY;
    centerZ = ZSIZE;
    initWalls();
    glutMainLoop(); // go into a perpetual loop
    return 0;
}