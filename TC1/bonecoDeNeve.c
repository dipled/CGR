// gcc bonecoDeNeve.c -lglut -lGL -lGLU -lm -o bonecoDeNeve && ./bonecoDeNeve
#include <GL/glut.h>

// Rotation
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
    glFrontFace(GL_CCW);     // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);  // Do not calculate inside

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
    if (key == 'z')
        zoom += .3;
    else if (key == 'x')
        zoom -= .3;
    if (key == 'w')
        xRot -= 5.0f;
    else if (key == 's')
        xRot += 5.0f;
    else if (key == 'a')
        yRot -= 5.0f;
    else if (key == 'd')
        yRot += 5.0f;
    else if (key == 'q')
        zRot += 5.0f;
    else if (key == 'e')    
        zRot -= 5.0f;
    yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);
    zRot = (GLfloat)((const int)zRot % 360);
    glutPostRedisplay();
    //Nao quebra o aspect ratio nem nada :)
    ChangeSize(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
}
// Called to draw scene
void RenderScene(void)
{

    GLUquadricObj *pObj; // Quadric Object

    // Clear the window with current clearing color
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

    // Draw something
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    // white
    // Parte de baixo
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

    //Bracos
    glColor3f(0.8,0.5,0.2);
    //Esquerdo
    glPushMatrix();
	glTranslatef(0.20, 0.73, 0.0f);
	glRotatef(90, 0.0f, 1.0f, .2f);
	gluCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13); 
	glPopMatrix();
    //Direito
    glPushMatrix();
	glTranslatef(-0.20, 0.73, 0.0f);
	glRotatef(-90, 0.0f, 1.0f, .2f);
	gluCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13); 
	glPopMatrix();
    //Maos
    //Esquerda
    glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90,-1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();
    glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90,.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();
    glPushMatrix();
	glTranslatef(0.67, 0.825, 0.02f);
	glRotatef(90,1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();
    //Direita
    glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90,-1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90,.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-0.67, 0.825, 0.02f);
	glRotatef(-90,1.0f, 1.0f, 0.0f);
	gluCylinder(pObj, 0.01f, 0.01f, 0.2f, 26, 13); 
	glPopMatrix();


    //Botoes
    glColor3f(0,0,0);
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
    // Esse PopMatrix é necessário senao o bicho vai embora
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("BonecoDeNeve");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(NormalKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
