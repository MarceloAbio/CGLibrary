#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <SOIL.h>

#define PI  3.1415926
#define nl 256
#define nc 256
using namespace std;

typedef GLubyte imagem[nl][nc][3];
GLuint texture[10];
imagem image;

float rotZ=0,rotY=0,rotX=0, tranZ=0,tranX=0;
float angle=0.0, movementAngle=0.0f,cameraX=0.0f,cameraY=0.0f,cameraZ=0.0f;
float doorAngle=90.0;
int flag=0;

void dimensionaJanela(int w, int h)
{
    glViewport(0, 0, w, h);

}
int LoadGLTextures(const char *filename, int id)
{
    texture[id] = SOIL_load_OGL_texture
        (
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );

    if(texture[id] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, texture[id]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return true;
}

void IniciarTexturas()
{
    LoadGLTextures("madeira.jpg",0);
    LoadGLTextures("livro.png",1);
    LoadGLTextures("piso.jpg",2);
    LoadGLTextures("concreto.jpg",3);
    LoadGLTextures("wood.jpg",4);
    LoadGLTextures("big.jpg",5);

}
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //criaDefineTexturas();
    IniciarTexturas();

    GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 6.9, 0.0, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40,1.0f,0.00001f,10000000);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0);
    gluLookAt(0.0,-6.0,0.0,1.0,-6.0,0.0,0.0,1.0,0.0);

}

void porta()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glColor3f(1,1,1);
    glTexCoord2f(0.0,1.0); glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,2.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(2.0,2.0,0.0);
    glTexCoord2f(1.0,1.0); glVertex3f(2.0,0.0,0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /*glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    glNormal3f(1.0,0.0,0.1);
    glVertex3f(0.7,0.9,0.1);
    glVertex3f(0.7,1.1,0.1);
    glVertex3f(0.9,1.1,0.1);
    glVertex3f(0.9,0.9,0.1);

    glNormal3f(1.0,0.0,0.1);
    glVertex3f(1.3,0.9,0.1);
    glVertex3f(1.3,1.1,0.1);
    glVertex3f(1.1,1.1,0.1);
    glVertex3f(1.1,0.9,0.1);
    glEnd();*/
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glVertex3f(1.0,2.0,0.0);
    glEnd();
}

void escada()
{
    float x;
    int np =70;
    float passo = 2*PI/np;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
     for(x=0;x<4;x+=2*passo)
    {
        //sustentação corrimão
      glVertex3f(cos(2*x+0.1)*0.6f,x+0.05,sin(2*x+0.1)*0.6f);
      glVertex3f(cos(2*x+0.1)*0.6f,x+0.65,sin(2*x+0.1)*0.6f);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(x=0;x<4;x+=passo)
    {
        //helice inferior
      glVertex3f(cos(2*x)*0.6f,x,sin(2*x)*0.6f);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(x=0;x<4;x+=passo)
    {
        //helice de corrimão.
      glVertex3f(cos(2*x)*0.6f,x+0.6,sin(2*x)*0.6f);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0,1.0,0.0);
    glColor3f(1.0, 1.0, 1.0);
    for(x=0;x<4;x+=0.2)
    {
      glVertex3f(cos(2*x)*0.6f,x,sin(2*x)*0.6f);
      glVertex3f(cos(2*x+0.2)*0.6f,x,sin(2*x+0.2)*0.6f);
      glVertex3f(0.0,x,0.0);

      glVertex3f(cos(2*x)*0.6f,x+0.03,sin(2*x)*0.6f);
      glVertex3f(cos(2*x+0.2)*0.6f,x+0.03,sin(2*x+0.2)*0.6f);
      glVertex3f(0.0,x+0.03,0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    for(x=0;x<4;x+=0.2)
    {
        glVertex3f(cos(2*x)*0.6f,x,sin(2*x)*0.6f);
        glVertex3f(cos(2*x)*0.6f,x+0.03,sin(2*x)*0.6f);
        glVertex3f(0.0,x,0.0);
        glVertex3f(0.0,x+0.03,0.0);

        glVertex3f(cos(2*x+0.2)*0.6f,x,sin(2*x+0.2)*0.6f);
        glVertex3f(cos(2*x+0.2)*0.6f,x+0.03,sin(2*x+0.2)*0.6f);
        glVertex3f(0.0,x,0.0);
        glVertex3f(0.0,x+0.03,0.0);
    }
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    //cone central
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    //gluQuadricDrawStyle(quadratic,GLU_LINE);
    gluCylinder(quadratic,0.2f,0.2f,4,32,32);
}
void sala()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glBegin(GL_QUADS);
    /* Floor */
    glColor3f(1.0,1.0,1.0);
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1.0,0.0); glVertex3f(-1,-1,1);
    glTexCoord2f(1.0,1.0); glVertex3f(1,-1,1);
    glTexCoord2f(0.0,1.0); glVertex3f(1,-1,-1);
    glEnd();


    glBindTexture(GL_TEXTURE_2D,3);
    glBegin(GL_QUADS);
    /* Ceiling */
    glNormal3f(0.0,-1.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,1,-1);
    glTexCoord2f(1.0,0.0); glVertex3f(1,1,-1);
    glTexCoord2f(1.0,1.0); glVertex3f(1,1,1);
    glTexCoord2f(0.0,1.0); glVertex3f(-1,1,1);
    glEnd();

    glBegin(GL_QUADS);
    /* Walls */
    glNormal3f(0.0,0.0,-1.0);
    glColor3f(1.0,1.0,1.0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,1);
    glTexCoord2f(1.0,0.0); glVertex3f(1,-1,1);
    glTexCoord2f(1.0,1.0); glVertex3f(1,1,1);
    glTexCoord2f(0.0,1.0); glVertex3f(-1,1,1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1.0,0.0); glVertex3f(1,-1,-1);
    glTexCoord2f(1.0,1.0); glVertex3f(1,1,-1);
    glTexCoord2f(0.0,1.0); glVertex3f(-1,1,-1);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.9,0.8,0.9);
    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0); glVertex3f(1,1,1);
    glTexCoord2f(1.0,0.0); glVertex3f(1,-1,1);
    glTexCoord2f(1.0,1.0); glVertex3f(1,-1,-1);
    glTexCoord2f(0.0,1.0); glVertex3f(1,1,-1);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,1,1);
    glTexCoord2f(1.0,0.0); glVertex3f(-1,-1,1);
    glTexCoord2f(1.0,1.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(0.0,1.0); glVertex3f(-1,1,-1);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void estante()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glColor3f(0.5,0.35,0.05);
    glColor3f(1.0,1.0,1.0); //AMARELO
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,2.0,0.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,2.0,0.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.0,0.0);

    glColor3f(1.0,1.0,1.0); //BRANCO
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,0.0,1.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,2.0,1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,2.0,1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.0,1.0);

    glColor3f(1.0,1.0,1.0); //VERDE
    glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.0,1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,0.2,1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.2,0.0);

    glColor3f(1.0,1.0,1.0); //AZUL
    glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.7,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.7,1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,0.9,1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.9,0.0);

    glColor3f(1.0,1.0,1.0);//CIANO
    glTexCoord2f(0.0,0.0); glVertex3f(0.5,1.4,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.5,1.4,1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,2.0,1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,2.0,0.0);

    glColor3f(1.0,1.0,1.0);//ROXO
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.0,2.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex3f(0.0,2.0,1.0);
    glTexCoord2f(1.0,1.0); glVertex3f(0.5,2.0,1.0);
    glTexCoord2f(0.0,1.0); glVertex3f(0.5,2.0,0.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glNormal3f(1.0,0.0,0.0);

        glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.2,0.0);
        glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.2,1.0);
        glTexCoord2f(1.0,1.0); glVertex3f(0.5,0.7,1.0);
        glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.7,0.0); //livros

        glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.9,0.0);
        glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.9,1.0);
        glTexCoord2f(1.0,1.0); glVertex3f(0.5,1.4,1.0);
        glTexCoord2f(0.0,1.0); glVertex3f(0.5,1.4,0.0); //livros
    glEnd();


    glFlush();

    glDisable(GL_TEXTURE_2D);
}
void andar()
{
    glColor3f(0.5,0.5,0.5);

    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,11.45);
        glVertex3f(3.5,0.0,11.45);
        glVertex3f(3.5,0.0,0.0);

        glNormal3f(0.0,-1.0,0.0);
        glVertex3f(0.0,-0.2,0.0);
        glVertex3f(0.0,-0.2,11.45);
        glVertex3f(3.5,-0.2,11.45);
        glVertex3f(3.5,-0.2,0.0);

        glNormal3f(1.0,0.0,0.0);
        glVertex3f(3.5,0.0,11.45);
        glVertex3f(3.5,0.0,0.0);
        glVertex3f(3.5,-0.2,0.0);
        glVertex3f(3.5,-0.2,11.45);

        glNormal3f(0.0,0.0,1.0);
        glVertex3f(0.0,0.0,11.45);
        glVertex3f(3.5,0.0,11.45);
        glVertex3f(3.5,-0.2,11.45);
        glVertex3f(0.0,-0.2,11.45);

        glEnd();
}

void desenha()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glPushMatrix();
    glScalef(7.0,7.0,7.0);
    sala();
    glPopMatrix();
    glPushMatrix();
    glTranslated(5.0,-7.0,4.5);
    glRotated(-105,0.0,1.0,0.0);
    escada();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.5,-3.2,-7.0);
    andar();
    glPopMatrix();

    glPushMatrix();
    glRotated(180,0.0,1.0,0.0);
    glTranslatef(-6.9,-7.0,5.5);

    glTranslatef(0.1,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glTranslatef(0,0.0,-1.02);
    estante();
    glPopMatrix();

    glPushMatrix();
    glRotated(90,0.0,1.0,0.0);
    glTranslatef(-6.9,-7.0,-6.8);
    estante();
    glTranslatef(0.0,0.0,1.02);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    glTranslatef(0.0,0.0,1.03);
    estante();
    //glTranslatef(0.0,0.0,1.0);
    //estante();
    glPopMatrix();

    glPushMatrix();
    glRotated(-90,0.0,1.0,0.0);
    glTranslatef(-6.9,-7.0,6.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glTranslatef(0.0,0.0,-1.0);
    estante();
    glPopMatrix();



    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(-1.0,-6.95,-6.7);
    porta();
    glPopMatrix();

    glutSwapBuffers();
}

float Distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}


void teclas_especiais(int key, int x, int y)
{
    switch(key)
    {
        //ha uma verificação dos limites das coordenadas.
    case GLUT_KEY_UP:
        if(cameraY==0.0)
        {
           if((cameraX-0.2*cos(movementAngle)>-6.9)&&(cameraX-0.2*cos(movementAngle)<6.9)&&(cameraZ-0.2*sin(movementAngle)>-6.9)&&(cameraZ-0.2*sin(movementAngle)<6.9))
            {
                cameraX -=0.2*cos(movementAngle);
                cameraZ-=0.2*sin(movementAngle);
                glTranslatef(-0.2*cos(movementAngle),0.0,-0.2*sin(movementAngle));
            }
        }
        if(cameraY==4.0)
        {
            if((cameraX-0.2*cos(movementAngle)>-6.9)&&(cameraX-0.2*cos(movementAngle)<-3.5)&&(cameraZ-0.2*sin(movementAngle)>-4.55)&&(cameraZ-0.2*sin(movementAngle)<6.9))
            {
                cameraX -=0.2*cos(movementAngle);
                cameraZ-=0.2*sin(movementAngle);
                glTranslatef(-0.2*cos(movementAngle),0.0,-0.2*sin(movementAngle));
            }
        }
        break;
    case GLUT_KEY_DOWN:
        if(cameraY==0.0)
        {
            if((cameraX+0.2*cos(movementAngle)>-6.9)&&(cameraX+0.2*cos(movementAngle)<6.9)&&(cameraZ+0.2*sin(movementAngle)>-6.9)&&(cameraZ+0.2*sin(movementAngle)<6.9))
            {
                cameraX +=0.2*cos(movementAngle);
                cameraZ+=0.2*sin(movementAngle);
                glTranslatef(0.2*cos(movementAngle),0.0,0.2*sin(movementAngle));
            }
        }
        if(cameraY==4.0)
        {
           if((cameraX+0.2*cos(movementAngle)>-6.9)&&(cameraX+0.2*cos(movementAngle)<-3.5)&&(cameraZ+0.2*sin(movementAngle)>-4.55)&&(cameraZ+0.2*sin(movementAngle)<6.9))
            {
                cameraX +=0.2*cos(movementAngle);
                cameraZ+=0.2*sin(movementAngle);
                glTranslatef(0.2*cos(movementAngle),0.0,0.2*sin(movementAngle));
            }
        }
        break;
    case GLUT_KEY_LEFT:
        angle--;
        if(angle<0)
        {
            angle = 359;
        }
        glTranslatef(-cameraX,-cameraY,-cameraZ);
        glRotatef(-1,0,1,0);
        glTranslatef(cameraX,cameraY,cameraZ);
        movementAngle=2.0*PI*angle/360;

        break;
    case GLUT_KEY_RIGHT:
        angle++;
        if(angle>359)
        {
            angle = 0;
        }
        glTranslatef(-cameraX,-cameraY,-cameraZ);
        glRotatef(1,0,1,0);
        glTranslatef(cameraX,cameraY,cameraZ);
        movementAngle=2.0*PI*angle/360;
        break;
    //se estiver proximo da escada, ira subir ou descer.
    case GLUT_KEY_F1:
        if(Distance(cameraX,cameraZ,-5,-4.5)<=3.5)
        {
            if(cameraY==0.0f)
            {
                cameraY=4.0f;
                glTranslatef(-cameraX,-cameraY,-cameraZ);
                glRotatef(270-angle,0,1,0);
                angle=270;
                movementAngle=2.0*PI*angle/360;
                glTranslatef(cameraX,cameraY,cameraZ);
                glTranslatef(-4.8-cameraX,-4.0,-4.2-cameraZ);
                cameraX=-4.8;
                cameraZ=-4.2;
            }
            else
            {
                if(cameraY==4.0f)
                {
                    cameraY=0.0f;
                    glTranslatef(-cameraX,-cameraY,-cameraZ);
                    glRotatef(270-angle,0,1,0);
                    angle=270;
                    movementAngle=2.0*PI*angle/360;
                    glTranslatef(cameraX,cameraY,cameraZ);
                    glTranslatef(0,4.0,-6.4-cameraZ);
                    cameraZ=-6.4;
                }
            }
        }
        break;
    case GLUT_KEY_F2:
        if(flag == 0) {glDisable(GL_LIGHT0); flag=1;}
        else {glEnable(GL_LIGHT0); flag = 0;}
        break;
    }
    //printf("camerax: %f, cameray: %f, camera z: %f, angulo: %f,distancetostairs: %f\n",cameraX,cameraY,cameraZ,angle,Distance(cameraX,cameraZ,-5,-4.5));
    glutPostRedisplay();

}

int main(int  argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Biblioteca");
    glutReshapeFunc( dimensionaJanela );
    glutDisplayFunc( desenha );
    //glutKeyboardFunc( teclas );
    glutSpecialFunc( teclas_especiais );
    initGL();
    glutMainLoop();
    return (0);
}
