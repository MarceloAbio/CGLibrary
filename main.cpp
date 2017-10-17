
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI  3.1415926
#define nl 256
#define nc 256
typedef GLubyte imagem[nl][nc][3];
GLuint texture;
imagem image;

float rotZ=0,rotY=0,rotX=0, tranZ=0,tranX=0;
float angle=0.0, movementAngle=0.0f,cameraX=0.0f,cameraY=0.0f,cameraZ=0.0f;
/*void leimagem(imagem im, char* nome)
{
   FILE *f;
   if ((f = fopen(nome,"rb"))==NULL){
       printf ("Erro leitura %s!\n(O programa sera fechado)\n",nome);
       system("pause");
       exit(0);
   }
   fread (im, sizeof(GLubyte),nl*nc*3,f);
   fclose(f);
}*/

void dimensionaJanela(int w, int h)
{
    glViewport(0, 0, w, h);

    }

   /* void criaDefineTexturas(void)
{//-------------------------------------- existe apenas um cubo
   //Ativa do modo de textura
   glEnable(GL_TEXTURE_2D);

   //Cria o identificador de uma textura
   glGenTextures(1, &texture); //(Havendo mais de uma textura,'texture' será um vetor)

   //Cria um objeto textura associando-o ao identificador
   glBindTexture(GL_TEXTURE_2D, texture);

   /*Especifica a imagem
   É bastante prático implementar uma função específica para tanto(como a função
   a seguir). As imagens aqui estão no formato RAW (sem abeçalho, sem compressão
   e de um byte por componente)                                               */
   /*leimagem(image, "books_texture.");

   //Especifica parâmetros da textura (ampliação, redução, repetição)
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

   /* Finalmente, constroi a textura
   Nesse caso :                                                               */
   /*glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,nc,nl,0,GL_RGB,GL_UNSIGNED_BYTE, image);
   /* Onde:
   Tipo = GL_TEXTURE_2D , pretende-se criar uma textura 2D,
   Level = 0 , significa uma única imagem de textura (Podem existir várias
   texturas para se obter diferentes níveis de detalhe)
   Internalformat= GL_RGB, descreve a repres. interna da textura (em OpenGL).
   nc - largura da imagem em pixels
   nl - altura da imagem em pixels
   Border=0, indica se desejamos uma borda de 0 ou mais pixels.
   Format=GL_RGB, correspondem ao formato original da imagem
   Type= GL_UNSIGNED_BYTE , tipo de dados usados no formato da imagem
   image - Corresponde ao array de imagem propriamente dito.                  */
//}

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //criaDefineTexturas();

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
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glColor3f(0.5,0.35,0.05);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,2.0,0.0);
    glVertex3f(2.0,2.0,0.0);
    glVertex3f(2.0,0.0,0.0);

    glColor3f(1.0,1.0,1.0);
    glNormal3f(1.0,0.0,0.01);
    glVertex3f(0.7,0.9,0.01);
    glVertex3f(0.7,1.1,0.01);
    glVertex3f(0.9,1.1,0.01);
    glVertex3f(0.9,0.9,0.01);

    glNormal3f(1.0,0.0,0.01);
    glVertex3f(1.3,0.9,0.01);
    glVertex3f(1.3,1.1,0.01);
    glVertex3f(1.1,1.1,0.01);
    glVertex3f(1.1,0.9,0.01);
    glEnd();
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
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_QUADS);
/* Floor */
glNormal3f(0.0,1.0,0.0);
glVertex3f(-1,-1,-1);
glVertex3f(-1,-1,1);
glVertex3f(1,-1,1);
glVertex3f(1,-1,-1);
/* Ceiling */
glNormal3f(0.0,-1.0,0.0);
glColor3f(0,1.0,0);
glVertex3f(-1,1,-1);
glVertex3f(1,1,-1);
glVertex3f(1,1,1);
glVertex3f(-1,1,1);
    /* Walls */
    glColor3f(0.5,0,0.3);
    glNormal3f(0.0,0.0,-1.0);
glVertex3f(-1,-1,1);
glVertex3f(1,-1,1);
glVertex3f(1,1,1);
glVertex3f(-1,1,1);


glNormal3f(0.0,0.0,1.0);
glVertex3f(-1,-1,-1);
glVertex3f(1,-1,-1);
glVertex3f(1,1,-1);
glVertex3f(-1,1,-1);

glColor3f(0.9,0.8,0.9);
glNormal3f(-1.0,0.0,0.0);
glVertex3f(1,1,1);
glVertex3f(1,-1,1);
glVertex3f(1,-1,-1);
glVertex3f(1,1,-1);

glNormal3f(1.0,0.0,0.0);
glVertex3f(-1,1,1);
glVertex3f(-1,-1,1);
glVertex3f(-1,-1,-1);
glVertex3f(-1,1,-1);
glEnd();
}
void estante()
{
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
    glColor3f(0.5,0.35,0.05);
    glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,2.0,0.0);
        glVertex3f(0.5,2.0,0.0);
        glVertex3f(0.5,0.0,0.0);

    glVertex3f(0.0,0.0,1.0);
        glVertex3f(0.0,2.0,1.0);
        glVertex3f(0.5,2.0,1.0);
        glVertex3f(0.5,0.0,1.0);

    glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.5,0.0,1.0);
        glVertex3f(0.5,0.2,1.0);
        glVertex3f(0.5,0.2,0.0);


    glVertex3f(0.5,0.7,0.0);
        glVertex3f(0.5,0.7,1.0);
        glVertex3f(0.5,0.9,1.0);
        glVertex3f(0.5,0.9,0.0);


    glVertex3f(0.5,1.4,0.0);
        glVertex3f(0.5,1.4,1.0);
        glVertex3f(0.5,2.0,1.0);
        glVertex3f(0.5,2.0,0.0);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(0.0,2.0,0.0);
        glVertex3f(0.0,2.0,1.0);
        glVertex3f(0.5,2.0,1.0);
        glVertex3f(0.5,2.0,0.0);

        glColor3f(0.0,0.0,0.0);
        glNormal3f(1.0,0.0,0.0);

        //glTexCoord2f(0.0,0.0);
        glVertex3f(0.5,0.2,0.0);
      //  glTexCoord2f(0.0,1.0);
        glVertex3f(0.5,0.2,1.0);
        //glTexCoord2f(1.0,1.0);
        glVertex3f(0.5,0.7,1.0);
        //glTexCoord2f(1.0,0.0);
        glVertex3f(0.5,0.7,0.0); //livros

        //glTexCoord2f(0.0,0.0);
        glVertex3f(0.5,0.9,0.0);
        //glTexCoord2f(0.0,1.0);
        glVertex3f(0.5,0.9,1.0);
        //glTexCoord2f(1.0,1.0);
        glVertex3f(0.5,1.4,1.0);
        //glTexCoord2f(1.0,0.0);
        glVertex3f(0.5,1.4,0.0); //livros
    glEnd();
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
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glTranslatef(0,0.0,-1.0);
    estante();
    glPopMatrix();

    glPushMatrix();
    glRotated(90,0.0,1.0,0.0);
    glTranslatef(-6.9,-7.0,-7.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
    estante();
    glTranslatef(0.0,0.0,1.0);
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
    glTranslatef(-1.0,-7.0,-6.95);
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

    }
    printf("camerax: %f, cameray: %f, camera z: %f, angulo: %f,distancetostairs: %f\n",cameraX,cameraY,cameraZ,angle,Distance(cameraX,cameraZ,-5,-4.5));
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
