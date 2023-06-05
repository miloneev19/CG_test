#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

class Point()
{
    public:
    int x, y;
   
    Point()
    { 
       x=0;
       y=0;
     }
 
   Point(int x, int y)
    {
         this->x = x;
         this->y = y;
    }
}

Point points[20];
int count=0;

int abs(int x)
{
    if(x<0)
    {
      return -x;
    }
     else 
      { return x; }
}

void drawPoints(Point a)
{
   glBegin(GL_POINTS);
   glVertex2i(a.x,a.y);
   glEnd();
   glFlush();
}

void DDA(Point a, Point b)
{
      int dx, dy, steps ; 
       float Dx, Dy;

        dx = abs(b.x-a.x);
         dy = abs(b.y-a.y);

        if(abs(dx)>abs(dy))
        { steps = abs(dx) ; }
         else 
        { steps=abs(dy); }

        for ( int i =0; i<=steps ; i++)
         { 
             x += Dx;
		y += Dy;
		
		a.x = x;
		a.y = y;
		
		
           drawPoints(Points(a.x,a.y));
           } 
}

void axes()
{
     Point a(-500,0),b(500,0) , c(0,-500) , d(0,500);
     DDA(a,b);
     DDA(c,d);
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500,500,-500,500);
	glFlush();
}

void plotCompletely( Point centre, Point a)
{
   drawPoints(Point(a.x + centre.x, a.y + centre.y));
   drawPoints(Point(a.y + centre.x, a.x + centre.y));
   drawPoints(Point(-a.x + centre.x, a.y + centre.y));
   drawPoints(Point(-a.y + centre.x, a.x + centre.y));
   drawPoints(Point(a.x + centre.x, -a.y + centre.y));
   drawPoints(Point(a.y + centre.x, -a.x + centre.y));
   drawPoints(Point(-a.x + centre.x, -a.y + centre.y));
   drawPoints(Point(-a.y + centre.x, -a.x + centre.y));

   }

void circle(Point centre, double radius)
{
   glColor3f(0,0,1);
   double p = 3 - 2*r;
    double x=0; y = radius;

       while(x<=y)
         {
                  if(p<0)
                   {
                      x++;
                      p += (4*x) + 6;
                    }

                    else 
                    {
                         x++;
                         y--;
                         p += (4*(x-y)) + 10;
                    }
             plotCompletely(centre,Point(x,y));
         }
}

void mouse(int button, int state, int x, int y){
	x = x - 500;
	y = 500 - y;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		points[count++] = Point(x,y);
	}
	
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		int dist = pow((points[1].x - points[0].x),2) + pow((points[1].y - points[0].y),2);
		double r = pow(dist, 0.5);
		
		circle(points[0],r);
		count = 0;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham Circle ");
	init();
	axes();
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
