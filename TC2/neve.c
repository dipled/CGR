#include "particulas.h"

#define NUM 4000

Particula neve[NUM];

static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat zRot = 0.0f;
static GLfloat zoom = -5.0;
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
	gluPerspective(35.0, fAspect, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void SetupRC()
{
	// Light values and coordinates
	GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
	GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
	GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};

	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glFrontFace(GL_CCW);	 // Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);	 // Do not calculate inside

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.7f, 0.7f, 0.70f, 1.0f);
}
void NormalKeys(unsigned char key, int x, int y)
{
	switch (key)

	{
	case 'z':
		zoom += .3;
		break;
	case 'x':
		zoom -= .3;
		break;
	case 'w':
		xRot -= 5.0f;
		break;
	case 's':
		xRot += 5.0f;
		break;
	case 'a':
		yRot -= 5.0f;
		break;
	case 'd':
		yRot += 5.0f;
		break;
	case 'q':
		zRot += 5.0f;
		break;
	case 'e':
		zRot -= 5.0f;
		break;
	}
	yRot = (GLfloat)((const int)yRot % 360);
	xRot = (GLfloat)((const int)xRot % 360);
	zRot = (GLfloat)((const int)zRot % 360);
	glutPostRedisplay();
	// Nao quebra o aspect ratio nem nada :)
	ChangeSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void iniciaFlocos(int part)
{
	neve[part].tempoVida = (double)(8 + rand() % 4) / 10;
	neve[part].gravidade = -0.1;
	neve[part].pos_x = (double)((rand() % 100) - 60) / 10;
	neve[part].pos_z = (double)((rand() % 200) - 100) / 10;
	neve[part].pos_y = 4.5;
	neve[part].velocidade = 3.14;
	neve[part].vivo = FALSE;
	// define o tamanho
	neve[part].raio = (double)(13 + rand() % 10) / 1000;
}

void nevar()
{
	int queda = TRUE;
	for (int i = 0; i < NUM; i++)
	{
		glColor3f(0.9, 0.9, 0.9);
		glPushMatrix();
		glTranslatef(neve[i].pos_x, neve[i].pos_y, neve[i].pos_z);
		glutSolidSphere(neve[i].raio, 10, 10);
		glPopMatrix();

		if (neve[i].vivo)
		{
			// direção de movimento
			double quedax = -5000 + rand() % 2000;
			if (queda)
			{
				neve[i].pos_x += neve[i].velocidade / quedax;
				queda = !queda;
			}
			else
			{
				neve[i].pos_x += -neve[i].velocidade / quedax;
				queda = !queda;
			}
			neve[i].pos_y += neve[i].velocidade / 1000;
			neve[i].velocidade += neve[i].gravidade;
			neve[i].tempoVida -= 0.0006;
		}
		else
		{
			if (rand() % 100 < 2)
			{
				neve[i].vivo = TRUE;
			}
		}

		if (neve[i].tempoVida < 0.0)
		{
			iniciaFlocos(i);
		}
	}
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, 640, 0, 480, -1, 1);
}
void DrawBody()
{
	GLUquadricObj *pObj; // Quadric Object

	pObj = gluNewQuadric();

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, .0f, 0.0f);
	gluSphere(pObj, 0.45f, 26, 13);
	glPopMatrix();
	// Parte do meio
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, .6f, 0.0f);
	gluSphere(pObj, 0.32f, 26, 13);
	glPopMatrix();
	// Botoes

	glColor3f(0, 0, 0);

	glPushMatrix();

	glTranslatef(0.0f, .72f, 0.3f);

	gluSphere(pObj, 0.03f, 26, 13);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, .61f, 0.33f);

	gluSphere(pObj, 0.03f, 26, 13);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, .50f, 0.3f);

	gluSphere(pObj, 0.03f, 26, 13);

	glPopMatrix();
}
void DrawHead()
{
	GLUquadricObj *pObj; // Quadric Object

	pObj = gluNewQuadric();
	glColor3f(1, 1, 1);
	// Cabeca
	glPushMatrix(); // save transform matrix state
	glTranslatef(0.0f, 1.0f, 0.0f);
	gluSphere(pObj, 0.24f, 26, 13);
	glPopMatrix(); // restore transform matrix state

	// Nose (orange)
	glColor3f(1.0f, 0.4f, 0.51f);
	glPushMatrix();
	glTranslatef(0.0f, 1.05f, 0.2f);
	gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
	glPopMatrix();

	// Olho direito
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-.1f, 1.1f, .2f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();

	// Olho esquerdo
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(.1f, 1.1f, .2f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();

	// Chapeu
	// Parte de baixo
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1.0f, .0f, .0f);
	glTranslatef(.0f, .0f, 1.2f);
	gluCylinder(pObj, .24f, .24f, .03f, 26, 13);
	glPopMatrix();
	// Disco de cima (de baixo)
	glPushMatrix();
	glRotatef(-90, 1.0f, .0f, .0f);
	glTranslatef(.0f, .0f, 1.23f);
	gluDisk(pObj, .0f, .24f, 26, 13);
	glPopMatrix();
	// Disco de baixo (de baixo)
	glPushMatrix();
	glRotatef(90, 1.0f, .0f, .0f);
	glTranslatef(.0f, .0f, -1.2f);
	gluDisk(pObj, .0f, .24f, 26, 13);
	glPopMatrix();
	//// Disco de cima (de cima)
	glPushMatrix();
	glRotatef(-90, 1.0f, .0f, .0f);
	glTranslatef(.0f, .0f, 1.5f);
	gluDisk(pObj, .0f, .14f, 26, 13);
	glPopMatrix();
	// Parte de cima da cartola
	glPushMatrix();
	glRotatef(-90, 1.0f, .0f, .0f);
	glTranslatef(.0f, .0f, 1.2f);
	gluCylinder(pObj, .14f, .14f, .30f, 26, 13);
	glPopMatrix();

	// Boca
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0f, .94, .25f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.07f, .96f, 0.25f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.105f, .99f, 0.23f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.07f, .96f, 0.25f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.105f, .99f, 0.23f);
	gluSphere(pObj, 0.02f, 26, 13);
	glPopMatrix();
}
void DrawArms()
{
	GLUquadricObj *pObj; // Quadric Object

	pObj = gluNewQuadric();

	// Bracos
	// Esquerdo
	glPushMatrix();
	glColor3f(0.8, 0.5, 0.2);
	glTranslatef(0.20, 0.73, 0.0f);
	glRotatef(90, 0.0f, 1.0f, .2f);
	gluCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13);
	glPopMatrix();
	// Direito
	glPushMatrix();
	glTranslatef(-0.20, 0.73, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, .2f);
	gluCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13);
	glPopMatrix();
	// Maos
	// Esquerda
	glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90, -1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90, .0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90, 1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
	// Direita
	glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90, -1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90, .0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90, 1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13);
	glPopMatrix();
}
// Called to draw scene
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, zoom);
	// Rotacionar no y
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// Rotacionar no x
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	// Rotacionar no z
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	DrawBody();
	DrawHead();
	DrawArms();
	nevar();
	glPopMatrix();
	// Buffer swap
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 680);
	glutCreateWindow("Boneco de Neve com neve");

	// glutDisplayFunc(display);
	// glutIdleFunc(display);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = (GLfloat)800 / 600;
	gluPerspective(45, aspect, 2.0f, 15.0f);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0.15, 0.15, 0.15, 1.0);

	GLfloat mat_shininess[] = {50.0};
	GLfloat mat_specular[] = {0.75, 0.75, 0.75, 0.75};

	GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] = {10.0, 2.0, 10.0, 0.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(NormalKeys);
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}
