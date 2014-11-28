#include <cstdio>
#include <functional>
#include <glut.h>

double eyeX, eyeY, eyeZ, centerX, centerY, centerZ;

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
void displayWire(void)
{
    //set the world
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt = 5.0;
    gluPerspective(60, 1, 0.1, 100);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    house(0.02);
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
    glPopMatrix();
    glFlush();
}
void mySpecial(int key, int x, int y)
{
    switch (key){

    }
    
    glutPostRedisplay();
}

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

int main(int argc, char** argv)
{
    printf("%s\n", (char*)pass(print));
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set
    //display mode
    glutInitWindowSize(640, 480); // set window size
    glutInitWindowPosition(200, 150); // set window position on
    //screen
    glutCreateWindow("Colored Dots"); // open the screen window
    glutDisplayFunc(displayWire); // register redraw function
    glutSpecialFunc(mySpecial);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    eyeX = 0.5;
    eyeY = 10;
    eyeZ = 8;
    centerX = 10.0;
    centerY = 1;
    centerZ = 0.0;
    //set the light source properties
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat light_position[] = { 7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glutMainLoop(); // go into a perpetual loop
    return 0;
}