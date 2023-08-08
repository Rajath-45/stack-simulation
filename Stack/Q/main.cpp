#include<iostream>
#include<cstring>
#include<string>
#include<Windows.h>
#include<GL/glut.h>
#include <cstdlib>
#include<windows.h>
#include<mmsystem.h>
using namespace std;

struct elem
{
	char c[20];

};

int MAX = 4;
int tos = -1;
  int sizee;
int width = 200;
int height = 25;
elem a[20];
int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 800; //Height of the screen

bool init()
{

	glClearColor(0, 0, 0, 1); //Set the background to black

	glViewport(0, 0, 500, 500); //Setting the viewport i.e. where the primitive should be displayed

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-250, 250, -250, 250, -100, 100); //Set the orthogonal view for the view port

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //If error is there
	{
		return false; //return error has been detected
	}

	return true; //return everything is fine continue
}
void show();

void drawBitmap(char *string, int x, int y)
{
	glRasterPos2f(x, y);

	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


void push()
{
	if (tos >= MAX)
	{
		drawBitmap("STACK IS FULL",-70, 200);
		glutSwapBuffers();
		Sleep(100);
		PlaySound("‪F:\\cg\\f\\s.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	else{
		tos++;
		printf("\nEnter the Element: ");
		cin >> a[tos].c;
		cout << "Element " << a[tos].c << " is pushed to the stack\n";
		cout << endl;
		char message[50];
		sprintf(message, "Element %s is pushed", a[tos].c);
		drawBitmap(message,-70, 200);
		glutSwapBuffers();
		Sleep(1000);
		show();
	}
}

void show_default()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = -1; i < MAX; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 25);
		glVertex2f(-100, k + 25);
		glEnd();

		k += 25;
	}
}

void show()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    show_default();
	int k = 0;

	for (int i = 0; i <= tos; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 25);
		glVertex2f(-100, k + 25);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		for (int j = 0; j < strlen(a[i].c); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i].c[j]);
		}
		k += 25;
	}
	glutSwapBuffers();
	glPopMatrix();
}

void pop()
{
	if (tos ==-1)
	{
        PlaySound("stack_empty.wav", NULL, SND_FILENAME | SND_ASYNC);
		drawBitmap("STACK IS EMPTY",-70, 200);
		glutSwapBuffers();
		Sleep(1000);
	}
	else
	{
		cout << "\nElement " << a[tos].c << " is removed from stack\n";
		char message[50];
		sprintf(message, "Element %s is popped", a[tos].c);
		drawBitmap(message,-70, 200);
		tos--;
		glutSwapBuffers();
		Sleep(1000);
		show();
	}
}

void render() //display function
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen

	if (tos == -1)
	{
		char *c = "3. Enter q or Q to Exit";
		glRasterPos2i(-70, 120);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "2. Enter r or R to Pop";
		glRasterPos2i(-70,140);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "1. Enter i or I to Push";
		glRasterPos2i(-70, 160);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		glFlush();
		glutSwapBuffers();
	}
	else{
		glFlush();
		show();
		}
}

void reshape(int w, int h) //function to call when the screen is reshaped
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed
	glOrtho(-250, 250, -250, 250, -100, 100); //set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i' | 'I': push();
		break;

	case 'r' | 'R': pop();
		render();
		break;
	case 'q' | 'Q':
	    printf("****Exiting stack simulation******\n");
	    Sleep(4000);
	     exit(0);
	}
}
void improper_size(int sizee)
{

    if(sizee>15 || sizee<0)
    {
        printf("Enter valid size\n");
        printf("Enter the size of the stack(0-15):\n");
	    scanf("%d",&sizee);
	    improper_size(sizee);
    }

}

int main(int argc, char*argv[])
{
    printf("Enter the size of the stack(0-15):\n");
	scanf("%d",&sizee);
    improper_size(sizee);
	MAX=sizee-1;
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow("STACK");//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

}
