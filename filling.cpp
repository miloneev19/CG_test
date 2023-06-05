#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

float newcolor[3] = {1.0,1.0,0.0};
float newcolor1[3] = {0.0,1.0,0.0};
float intcolor[3] = {0.0,0.0,0.0};
float boundcolor[3] = {1.0,1.0,1.0};

int round(float a)
{
    return int(a+0.5);
}

int abs(int a)
{
    if(a<0){
        return -a;
    }
    else
    {
        return a;
    }
}
void DDA(float xa,float ya, float xb, float yb)
{
    float dx,dy,steps;
    float xinc,yinc;

    dx=abs(xb-xa);
    dy=abs(yb-ya);

    if(abs(dx)>abs(dy))
    {
        steps = abs(dx);
    }
    else{
        steps=abs(dy);
    }

    xinc = dx/steps;
    yinc = dy/steps;

    float x,y;
    x=xa;
    y=ya;

    glBegin(GL_POINTS);
    glVertex2d(round(x),round(x));

    for(int i=0;i<steps;i++)
    {
        x = x + xinc;
        y = y + yinc;
        glVertex2d(round(x),round(x));
    }

    glEnd();
}

void setPixel(int x,int y, float f[3])
{
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(x,y);
    glEnd();
    glFlush();

}

void getPixel(int x,int y, float pixels[3])
{
    glReadPixels(x,y,1,1,GLUT_RGB,GL_FLOAT,pixels);
}

void floodfill(int x, int y, float color[3])
{
    float floodcolor[3];
    getPixel(x,y,floodcolor);
    
    if(floodcolor[0] == intcolor[0] && floodcolor[1] == intcolor[1] && floodcolor[2]== intcolor[2] )
    {
        setPixel(x,y,color);
        floodfill(x+1,y,color);
        floodfill(x-1,y,color);
        floodfill(x,y+1,color);
        floodfill(x,y-1,color);

    }
    glFlush();

}

void boundaryfill(int x, int y, float newcolor1[3])
{
    float color[3];
    getPixel(x,y,color);

    if(color[0] != boundcolor[0] || color[0] != boundcolor[0] || color[0] != boundcolor[0]   )
    {
        if(color[0] == newcolor1[0] || color[1] == newcolor1[1] || color[1] == newcolor1[1])
        {
            setPixel(x,y,newcolor1);
            boundaryfill(x+1,y,newcolor1);
            boundaryfill(x-1,y,newcolor1);
            boundaryfill(x,y+1,newcolor1);
            boundaryfill(x,y-1,newcolor1);
        }
    }
    glFlush();
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DDA(100,100,300,100);
    DDA(300,100,300,300);
    DDA(300,300,100,300);
    DDA(100,300,100,100);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{

    y=500-y;

    if(button == GLUT_LEFT_BUTTON && state== GLUT_DOWN)
    {
         floodfill(x,y,newcolor);
    }
    if(button ==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        boundaryfill(x,y,newcolor1);
    }
}
int main(int argc , char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Flood fill");
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0,500,0,500);
  
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
