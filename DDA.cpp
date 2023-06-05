#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

class Point
{
    public:
     int x,y;

    Point()
     {  
             x=0;
             y=0;
     }

    Point(int x,int y)
    { 
          this->x=x;
          this->y=y; 
    } 
};

Point points[20];
int count =0;

int abs(int x)
{
    if(x<0)
      {  
       return -x;
      }
     else 
          { 
              return x;
           } 
}

 void drawPoints(int x, int y, bool plot)
{
    glBegin(GL_POINTS);
    if(plot) {
            glVertex2i(x,y);
       } 
     glEnd();
     glFlush();
}

void DDA( Point a, Point b, int type)
{
    int counter =1;
    int dx,dy,steps;
    float Dx, Dy;
    bool draw= true;
    float x=a.x , y =a.y;

    dx = abs(b.x - a.x);
     dy= abs(b.y - a.y);
   
      if( abs(dx)>abs(dy))
         {
            steps = abs(dx);
          }
      else
         {
            steps=abs(dy);
           }
    

      Dx= abs(dx)/steps;
      Dy= abs(dy)/steps;
   
       drawPoints(x,y,true);
       for(int i=0; i <= steps ; i++)
       {
              a.x + = Dx;
              a.y + = Dy;

             if(type ==1)  //dotted line
              { 
                   drawPoints(a.x, a.y, counter %7==0);
                   counter++;
              }
             else if (type==2)    //dashed line
             {
                   if ( counter %20 ==0)
                         { 
                               if(draw==false) 
                                    { draw=true; }
                          } 
                   else 
                         {
                            draw=false;
                         }
                 drawPoints(a.x,a.y,draw);
                 counter++;
             }
             else 
                 {
                       drawPoints(a.x,a.y,true);
                 }
             glFlush();
}
}

void axes ()
{
     Point a(-500,0), b (500,0), c(0,-500) , d(0,500);
     DDA(a,b,0);
     DDA(c,d,0);
}


void init(void)
{
   glClearColor(0.0,0.0,0.0,0.0);
   glClear(Gl_COLOR_BUFFER_BIT);
   gluOrtho2D(-500,500,-500,500);
   glFlush();
}

void mouse(int button, int state, int x, int y)
 {
             y=500-y;
             x = x-500; 
 
      if(button == GLUT_BUTTON_LEFT && state == GLUT_DOWN)
        {
                Point p(x,y);
                points [count ++ ] =p;
         }
}

void keyboard(unsigned char key , int x, int y)
 {
       if(key=='0')
           {
                DDA(points[0],points[1],0);
                count =0;
            }
         else if(key=='1')
           {
                DDA(points[0],points[1],1);
                count =0;
            }
         else if(key=='2')
           {
                DDA(points[0],points[1],2);
                count =0;
            }
 }

int main(int argc , char **argv)
{
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
      glutInitWindowSize(1000,1000);
      glutInitWindowPosition(0,0);
      glutCreateWindow("DDA");
      init();
      axes();
      glutMouseFunc(mouse);
      glutKeyboardFunc(keyboard);
      glutMainLoop();
      return 0;
}