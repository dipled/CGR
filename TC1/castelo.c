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
    GLfloat whiteLight[] = {0.05, 0.05, 0.05, 1.0f};
    GLfloat sourceLight[] = {0.25, 0.25, 0.25, 0.25f};
    GLfloat lightPos[] = {-1.0, 5.0, 5.0, 1.0f};

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

    // Black blue background
    glClearColor(0.7, 0.8, 1.0, 0.0);
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

// Called to draw scene
void RenderScene(void)
{

    GLUquadricObj *pObj; // Quadric Object

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();

    // Move object back and do in place rotation
    glTranslatef(0.0, -1.0, zoom);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    // Draw something
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // Chao
    glPushMatrix();
    glColor3f(0.0, .30, 0.0);
    glTranslatef(0.0, 0.0, -0.8);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glScalef(7.0, 7.0, 0.05);
    glutSolidCube(0.5);
    glPopMatrix();

    // Telhados
    glColor3f(1.0, 0.2, 0.0);
    glPushMatrix();
    glTranslatef(1.2, 1.15, 0.4);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.26, 0.4, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 1.15, -2.0);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.26, 0.4, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 1.15, 0.4);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.26, 0.4, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 1.15, -2.0);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.26, 0.4, 26, 13);
    glPopMatrix();

    // Torres
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(1.2, 0.8, 0.4);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.2, 0.2, 0.8, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.8, -2.0);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.2, 0.2, 0.8, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.8, 0.4);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.2, 0.2, 0.8, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.8, -2.0);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.2, 0.2, 0.8, 26, 13);
    glPopMatrix();

    // Muro Principal
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glTranslatef(-0.6, 0.25, 0.4);
    glScalef(1.8, 1.0, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.6, 0.25, 0.4);
    glScalef(1.8, 1.0, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.376, 0.4);
    glScalef(1.0, 0.5, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    // Porta
    glColor3f(.3, 0, 0);
    glPushMatrix();
    glTranslatef(0.0, .136, .4);
    glScalef(.6, .48, .3);
    glutSolidCube(.5);
    glPopMatrix();
    // Muros
    glColor3f(0.6, 0.6, 0.6);

    glPushMatrix();
    glTranslatef(0.0, 0.25, -2.0);
    glScalef(4.0, 1.0, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.25, -0.8);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(4.0, 1.0, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.25, -0.8);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(4.0, 1.0, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    // Detalhe nos muros
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.3, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.6, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.6, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.9, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.9, 0.5, 0.4);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.3, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.6, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.6, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.9, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.9, 0.5, -2.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.5, -0.8);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, -1.1);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, -0.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, -1.4);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, -0.2);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, -1.7);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.5, 0.1);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2, 0.5, -0.8);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, -1.1);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, -0.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, -1.4);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, -0.2);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, -1.7);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.5, 0.1);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.3);
    glutSolidCube(0.5);
    glPopMatrix();

    // janelas
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(1.2, 0.6, 0.59);
    glScalef(0.1, 0.2, 0.05);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.6, 0.59);
    glScalef(0.1, 0.2, 0.05);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.6, -2.19);
    glScalef(0.1, 0.2, 0.05);
    glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.2, 0.6, -2.19);
    glScalef(0.1, 0.2, 0.05);
    glutSolidCube(0.5);
    glPopMatrix();

    // arvore
    glColor3f(0.7, 0.35, 0.25);
    glPushMatrix();
    glTranslatef(0.4, 0.4, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.05, 0.05, 0.3, 26, 13);
    glPopMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.4, 0.7, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.13, 0.38, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.4, 0.8, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.09, 0.3, 26, 13);
    glPopMatrix();

    glColor3f(0.7, 0.35, 0.25);
    glPushMatrix();
    glTranslatef(-0.4, 0.4, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.05, 0.05, 0.3, 26, 13);
    glColor3f(0.0, 1.0, 0.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4, 0.8, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.09, 0.3, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4, 0.7, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.13, 0.38, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4, 0.8, -0.8);
    glRotatef(90.0, 5.0, 0.0, 0.0);
    gluCylinder(pObj, 0.0, 0.09, 0.3, 26, 13);
    glPopMatrix();

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("CasteloSimples");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(NormalKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
