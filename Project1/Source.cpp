#include<GL/glut.h>
#include<vector>
#include<iostream>
#include"Vector2.h"
#include<algorithm>
#include<iterator>
#include<math.h>
using namespace std;
GLsizei StartMOUSEx = 0, EndMOUSEy = 0;

GLfloat RED[3] = { 1,0,0 };
GLfloat BLUE[3] = { 0, 0, 1 };
GLfloat point = 5;
int cnt = 0;
float angle, deltaAngle = 0.0f;
int xOrigin = -1;
int lx, lz;
vector<Vector2> mousePoints[4];
vector<vector<Vector2>> polygons;
int polygoncount = 0;
Vector2 startPoint(0, 0);
Vector2 endPoint(0, 0);
Vector2 MousepointClick;
Vector2 *CurrentVertex = nullptr;
bool Editable = false;
bool BeforeClick = false;
bool putCurrrentVerctor = false;
bool polystart = false;
unsigned int count = 0;


enum classicDrawingOptions 
{
	LINES,
	RECTANGLES, 
	CIRCLES,
	POLYGON, 
	TRANSFORM, 
	EXIT
};


int pickOption = LINES;
void point1()
{
	glColor3fv(BLUE);
	glPointSize(point);
	glBegin(GL_POINTS);

	//vector<Vector2>::iterator po = mousePoints[0].begin();
	for (unsigned int j = 0; j <4; j++)
		for (unsigned int i = 0; i <mousePoints[j].size(); i++)
		{
			Vector2 vec[2];
			//vec[0] = (*std::next(line_mousePoints.begin(),i));
			//vec[1] = (*std::next(line_mousePoints[].begin(), i));
			vec[0] = mousePoints[j][i];
			//vec[1] = mousePoints[LINES][i + 1];

			glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
			//	glVertex2i(vec[1].getVector2x(), vec[1].getVector2y());
		}
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector2 vec[2];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];

			glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());

		}
	}
	if (Editable&&putCurrrentVerctor)
	{
		glPointSize(100);
		glColor3f(0, 1, 1);
		glVertex2i(CurrentVertex->getVector2x(), CurrentVertex->getVector2y());
	}
	glEnd();
}


void drawpoint()
{

	glColor3fv(BLUE);


	glBegin(GL_LINES);

	//vector<Vector2>::iterator po = mousePoints[0].begin();

	unsigned int lPoints = mousePoints[LINES].size() - mousePoints[LINES].size() % 2;
	for (unsigned int i = 0; i <lPoints; i = i + 2)
	{
		Vector2 vec[2];
		//vec[0] = (*std::next(line_mousePoints.begin(),i));
		//vec[1] = (*std::next(line_mousePoints[].begin(), i));
		vec[0] = mousePoints[LINES][i];
		vec[1] = mousePoints[LINES][i + 1];

		glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
		glVertex2i(vec[1].getVector2x(), vec[1].getVector2y());
	}

	glEnd();
}

void drawRectangle()
{
	//glPointSize(5);
	glColor3f(0.6, 0.6, 0.6);


	glBegin(GL_LINES);
	unsigned int lPoints = mousePoints[RECTANGLES].size() - mousePoints[RECTANGLES].size() % 2;
	for (unsigned int i = 0; i <lPoints; i = i + 2)
	{
		Vector2 vec[4];
		vec[0] = mousePoints[RECTANGLES][i];
		vec[1] = mousePoints[RECTANGLES][i + 1];
		vec[2].setVector2(vec[0].getVector2x(), vec[1].getVector2y());
		vec[3].setVector2(vec[1].getVector2x(), vec[0].getVector2y());

		glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
		glVertex2i(vec[2].getVector2x(), vec[2].getVector2y());

		glVertex2i(vec[2].getVector2x(), vec[2].getVector2y());
		glVertex2i(vec[1].getVector2x(), vec[1].getVector2y());

		glVertex2i(vec[1].getVector2x(), vec[1].getVector2y());
		glVertex2i(vec[3].getVector2x(), vec[3].getVector2y());

		glVertex2i(vec[3].getVector2x(), vec[3].getVector2y());
		glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
	}
	glEnd();

	/*glBegin(GL_TRIANGLES);

	glVertex2i(startPoint.getVector2x(), startPoint.getVector2y());
	glVertex2i(startPoint.getVector2x(), endPoint.getVector2y());
	glVertex2i(endPoint.getVector2x(), startPoint.getVector2y());

	glVertex2i(endPoint.getVector2x(), startPoint.getVector2y());
	glVertex2i(endPoint.getVector2x(), endPoint.getVector2y());
	glVertex2i(startPoint.getVector2x(), endPoint.getVector2y());

	glEnd();*/

}

void circle(int x, int y, float radius, int numofSegments)
{
	glBegin(GL_LINE_LOOP);

	float incVal = (2 * 3.1456f) / (float)numofSegments;
	for (int i = 0; i < numofSegments; i++)
	{
		int x1 = (int)((float)x + sin(incVal*i)*radius);
		int y1 = (int)((float)y + cos(incVal*i)*radius);
		glVertex2i(x1, y1);
	}
	glEnd();
}

void drawCircle()
{
	//glPointSize(5);
	glColor3f(1, 0, 0);
	unsigned int lPoints = mousePoints[CIRCLES].size() - mousePoints[CIRCLES].size() % 2;
	for (unsigned int i = 0; i <lPoints; i = i + 2)
	{
		Vector2 vec[4];

		vec[0] = mousePoints[CIRCLES][i];
		vec[1] = mousePoints[CIRCLES][i + 1];
		float radius = sqrt(pow((vec[1].getVector2x() - vec[0].getVector2x()), 2) +
			pow((vec[1].getVector2y() - vec[0].getVector2y()), 2));

		circle(vec[0].getVector2x(), vec[0].getVector2y(), radius, 100);
	}
}

void drawpolygon()
{
	//	unsigned int lPoints = mousePoints[POLYGON].size() - mousePoints[POLYGON].size() % 2;
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector2 vec[2];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];

			glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
		}
		glEnd();
	}
}



void processMenuEvents(int option)
{
	std::cout << "Option";

	switch (option) 
{
	case LINES:
		cout << "LInes\n";
		selectOption = LINES;
		Editable = false;
		break;
	case RECTANGLES:
		cout << "Rectangles\n";
	    selectOption = RECTANGLES;
		Editable = false;
		break;
	case CIRCLES:
		cout << "Circles\n";
		selectOption = CIRCLES;
		Editable = false;
		break;
	case POLYGON:
		cout << "Polygon\n";
		selectOption = POLYGON;
		Editable = false;
		break;
	case TRANSFORM:
		cout << "TRANSFORM\n";
		selectOption = TRANSFORM;
		Editable = true;
		break;
	case EXIT:
		cout << "EXIT\n";
		selectOption = EXIT;
		Editable = false;
		exit(0);
		break;
	}
}
void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	point1();
	drawpoint();
	drawRectangle();
	drawCircle();
	drawpolygon();
	glFlush();
}

void spindisplay(void)
{
	glutPostRedisplay();
}

void setX(int x)
{
	StartMOUSEx = x;
}

void setY(int y)
{
	EndMOUSEy = y;
}
void createGLUTMenus()
 {

	int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMenuEvents);

	//add entries to our menu
	glutAddMenuEntry("LINES", LINES);
	glutAddMenuEntry("RECTANGLE", RECTANGLES);
	glutAddMenuEntry("CIRCLES", CIRCLES);
	glutAddMenuEntry("POLYGON", POLYGON);
	glutAddMenuEntry("TRANSFORM", TRANSFORM);
	glutAddMenuEntry("EXIT", EXIT);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseMove(int x, int y) 
{

	if (BeforeClick)
	{
		if (selectOption == LINES)
		{
			startPoint = Vector2(x, y);
			(mousePoints[LINES][mousePoints[LINES].size() - 1]).setVector2(x, y);
			std::cout << "X = " << x << " , Y = " << y;
			//	mousePoints[LINES].push_back(startPoint);
		}
		if (selectOption == RECTANGLES)
		{
			startPoint = Vector2(x, y);
			(mousePoints[RECTANGLES][mousePoints[RECTANGLES].size() - 1]).setVector2(x, y);
			std::cout << "X = " << x << " , Y = " << y;
			//	mousePoints[LINES].push_back(startPoint);
		}
		if (selectOption == CIRCLES)
		{
			startPoint = Vector2(x, y);
			(mousePoints[CIRCLES][mousePoints[CIRCLES].size() - 1]).setVector2(x, y);
			std::cout << "X = " << x << " , Y = " << y;
			//	mousePoints[LINES].push_back(startPoint);
		}
	}
	if (polystart)
	{
		if (pickOption == POLYGON)
		{
			startPoint = Vector2(x, y);
			((polygons[polygoncount - 1])[(polygons[polygoncount - 1]).size() - 1]).setVector2(x, y);
			std::cout << "X = " << x << " , Y = " << y;
			//	mousePoints[LINES].push_back(startPoint);
		}
	}
	if (Editable)
	{
		if (putCurrrentVerctor)
		{
			CurrentVertex->Vector2(x, y);
		}
	}
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		if (pickOption == POLYGON)
		{
			polygoncount++;
			vector<Vector2> polyPoints;
			polygons.push_back(polyPoints);
			polystart = false;
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		//setX(x);
		//setY(y);
		if (Editable)
		{
			if (putCurrrentVerctor == false)
			{
				MousepointClick = Vector2(x, y);
				for (int j = 0; j < 3; j++) {
					for (int i = 0; i < mousePoints[j].size(); i++)
					{
						int Vertexpointx = mousePoints[j].at(i).getVector2x();
						int Vertexpointy = mousePoints[j].at(i).getVector2y();
						int clickpointx = x;
						int clickpointy = y;
						if ((Vertexpointx > clickpointx - 10 && Vertexpointx < clickpointx + 10) &&
							(Vertexpointy > clickpointy - 10 && Vertexpointy < clickpointy + 10))
						{
							CurrentVertex = &mousePoints[j].at(i);
							putCurrrentVerctor = true;
							break;
						}
					}
				}
				for (int z = 0; z < polygons.size(); z++)
				{
					for (int a = 0; a < polygons[z].size(); a++)
					{
						int Vertexpointx = polygons[z].at(a).getVector2x();
						int Vertexpointy = polygons[z].at(a).getVector2y();
						int clickpointx = x;
						int clickpointy = y;
						if ((Vertexpointx > clickpointx - 10 && Vertexpointx < clickpointx + 10) &&
							(Vertexpointy > clickpointy - 10 && Vertexpointy < clickpointy + 10))
						{
							CurrentVertex = &polygons[z].at(a);
							putCurrrentVerctor = true;
							break;
						}
					}
				}

			}
			else
			{
				CurrentVertex->Vector2(x, y);
				CurrentVertex = nullptr;
				putCurrrentVerctor = false;
			}
		}
		else
		{
			if (!BeforeClick)
			{
				setX(x);
				setY(y);
				std::cout << "X = " << x << " , Y = " << y;
				if (selectOption == LINES)
				{
					startPoint = Vector2(x, y);
					mousePoints[LINES].push_back(startPoint);
					mousePoints[LINES].push_back(startPoint);
				}
				if (selectOption == RECTANGLES)
				{
					startPoint = Vector2(x, y);
					mousePoints[RECTANGLES].push_back(startPoint);
					mousePoints[RECTANGLES].push_back(startPoint);
				}
				if (selectOption == CIRCLES)
				{
					startPoint = Vector2(x, y);
					mousePoints[CIRCLES].push_back(startPoint);
					mousePoints[CIRCLES].push_back(startPoint);
				}
				
			}
			else
			{
				std::cout << "X = " << x << " , Y = " << y;
				if (selectOption == LINES)
				{
					(mousePoints[LINES][mousePoints[LINES].size() - 1]).setVector2(x, y);
				}
				if (selectOption == RECTANGLES)
					(mousePoints[RECTANGLES][mousePoints[RECTANGLES].size() - 1]).setVector2(x, y);
				if (chosenOption == CIRCLES)
					(mousePoints[CIRCLES][mousePoints[CIRCLES].size() - 1]).setVector2(x, y);
				if (chosenOption == POLYGON)
				{
					if (polygons.size() == 0)
					{
						polygoncount = 1;
						vector<Vector2> polyPoints;
						polygons.push_back(polyPoints);
					}
					(polygons[polygoncount - 1]).push_back(Vector2(x, y));
				}
				BeforeClick = false;
			}

			if (selectOption == POLYGON)
			{
				if (polygons.size() == 0)
				{
					polygoncount = 1;
					vector<Vector2> polyPoints;
					polygons.push_back(polyPoints);
				}
				if ((polygons[polygoncount - 1]).size() == 0)
				{
					(polygons[polygoncount - 1]).push_back(Vector2(x, y));
					(polygons[polygoncount - 1]).push_back(Vector2(x, y));
				}
				else
					(polygons[polygoncount - 1]).push_back(Vector2(x, y));
				polystart = true;
			}
		}
		glutPostRedisplay();
	}
}

void changeSize(int w, int h) 
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	//gluPerspective(45, ratio, 1, 1000);
	//glOrtho(0.0, 1368, 768, 0, -1.0, 1.0);
	gluOrtho2D(0, w, h, 0);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Classic Diagrams of Geomatrics ");
	createGLUTMenus();
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);
	glutIdleFunc(spindisplay);
	glutMainLoop();
}