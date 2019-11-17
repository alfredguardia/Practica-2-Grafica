#include <windows.h>
#include <C:\GLUT\include\GL\glut.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#define PI 3.14159265

using namespace std;

class Punto
{
public:
    float x;
    float y;
    Punto();
    ~Punto();
};

Punto::~Punto()
{

}
Punto::Punto()
{

}

const int tam=3;
Punto* lista[tam];
float a = cos(30*PI/180);
float b = sin(30*PI/180);
float M[2][2]= {{a, -1*b},{b,a}};
float G[2][2]={};

void mostrar(Punto* lista[])
{
    for(int i=0;i<tam;i++)
    {
        cout<<"Punto "<<i<<": ";
        cout<<lista[i]->x<<" - "<<lista[i]->y;
        cout<<endl<<endl;
    }
}

void convertir(Punto* lista[], float M[2][2] )
{
    float aux;
    float auy;
    for(int i=0;i<tam;i++)
    {
        Punto* nuevo=new Punto;
        aux=lista[i]->x*M[0][0]+lista[i]->y*M[0][1];
        auy=lista[i]->x*M[1][0]+lista[i]->y*M[1][1];

        nuevo->x=aux;
        nuevo->y=auy;

        lista[i]=nuevo;
    }
}

void transladar(Punto* lista[], int muevex, int muevey)
{
    float aux;
    float auy;
    for(int i=0;i<tam;i++)
    {
        Punto* nuevo=new Punto;
        aux=lista[i]->x+muevex;
        auy=lista[i]->y+muevey;

        nuevo->x=aux;
        nuevo->y=auy;

        lista[i]=nuevo;
    }
}
void escalar(Punto* lista[],int escalado)
{
    float aux;
    float auy;
    for(int i=0;i<tam;i++)
    {
        Punto* nuevo=new Punto;
        aux=lista[i]->x*escalado;
        auy=lista[i]->y*escalado;

        nuevo->x=aux;
        nuevo->y=auy;

        lista[i]=nuevo;
    }
}

void initGL()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyKeyboardFunc(unsigned char Key, int x, int y)
{

    if(Key == 'z'){
        convertir(lista,M);
        glutPostRedisplay();
    }
    if(Key =='4'){
        transladar(lista,-1,0);
        glutPostRedisplay();
    }
    if(Key =='6'){
        transladar(lista,1,0);
        glutPostRedisplay();
    }
    if(Key =='2'){
        transladar(lista,0,-1);
        glutPostRedisplay();
    }
    if(Key =='8'){
        transladar(lista,0,1);
        glutPostRedisplay();
    }
    if(Key =='e'){
        escalar(lista,2);
        glutPostRedisplay();
    }
    glutSwapBuffers();
}




void poligono()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-20, 0.0, 0.0);
    glVertex3f(20, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, -20, 0.0);
    glVertex3f(0, 20, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 0.0f);
    for(int i=0;i<tam;i++)
    {
        glVertex3f(lista[i]->x,lista[i]->y,0);
    }
    glEnd();
    glutSwapBuffers();
}



void ejes(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void grafica()
{
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Poligono 2D");
    glutDisplayFunc(poligono);
    glutReshapeFunc(ejes);
    initGL();
    glutKeyboardFunc(MyKeyboardFunc);
    glutMainLoop();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);



    cout<<"Ingrese datos de los puntos: "<<endl;
    for(int i=0;i<tam;i++)
    {
        cout<<"Punto "<<i<<" : ";
        Punto* nuevo= new Punto();
        cin>>nuevo->x;
        cin>>nuevo->y;
        lista[i]=nuevo;
        cout<<endl;
    }

    grafica();
   return 0;
}
