#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

bool keyStates[256] = {false};

enum view { INTRO, MENU };
view viewPage = INTRO; // initial value

void displayRasterText(float x, float y, float z, char *stringToDisplay) {
    glRasterPos3f(x, y, z);
    for (char *c = stringToDisplay; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1200, 1200, -700, 700);
    glMatrixMode(GL_MODELVIEW);
}

void introScreen() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 1.0);
    displayRasterText(-500, 585, 0.0, "SIMULATION OF STACK USING Open-GL");
    glColor3f(1.0, 1.0, 1.0);
    displayRasterText(-1200, 485, 0.0, "*A stack is a data structure that follows the Last In, First Out principle. This means that the last element added to the stack is the first one to be removed. ");
    displayRasterText(-1200, 385, 0.0, " "); // Add space
    glColor3f(1.0, 1.0, 1.0);
    displayRasterText(-1200, 335, 0.0, "*In a stack simulation using OpenGL, there are three main operations that can be performed: push, pop, and exit.");
    displayRasterText(-1200, 235, 0.0, " "); // Add more space
    // ... Continue adding space and text as needed

    glColor3f(1.0, 1.0, 1.0);
    displayRasterText(-300, -315, 0.0, "PRESS ENTER TO START");

    glFlush();
    glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = true;
    glutPostRedisplay();
}

void refresh() {
    glutPostRedisplay();
}

void keyOperations() {
    if (keyStates[13] == true && viewPage == INTRO) {
        viewPage = MENU;
        printf("----------------Enter key pressed---------------------\n");
        printf("=---------------Entering Stack Simulation------------=\n");
    }
}

void startScreenDisplay() {
    system("F:\\Projects\\Stack\\Q\\bin\\Debug\\Q.exe");
    exit(0);
}

void display() {
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);

    switch (viewPage) {
    case INTRO:
        introScreen();
        break;

    case MENU:
        startScreenDisplay();
        break;
    }
    glFlush();
    glLoadIdentity();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1800, 1200);
    glutCreateWindow("STACK");
    init();
    glutIdleFunc(refresh);
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMainLoop();
}
