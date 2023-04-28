// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>

// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat rot = 20.0f;
int indo = 1;

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
    gluPerspective(35.0f, fAspect, 1.0, 40.0);

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

    // Black blue background
    glClearColor(0.7f, 0.8f, 1.0f, 0.0f);
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
    glTranslatef(0.0f, 0.0f, -5.0f);

    xRot += 1.0f;
    // yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);

    glutPostRedisplay();

    glRotatef(xRot, 0.0f, 1.0f, 0.0f);
    // glRotatef(xRot, 1.0f, 0.0f, 0.0f);

    // Draw something
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    if (indo)
    {
        rot -= 2;
        if (rot == -30)
            indo = 0;
    }
    else
    {
        rot += 2;
        if (rot == 30)
            indo = 1;
    }

    // body
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.f, 1.2, 0.8);
    glutSolidCube(0.5);
    glPopMatrix();
    // head
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix(); // save transform matrix state
    glTranslatef(0.0f, .5f, 0.0f);
    glScalef(.8, 1.05, 1);
    glutSolidCube(0.4);
    glPopMatrix(); // restore transform matrix state
    glPushMatrix();
    glTranslatef(0.0f, .77, 0.0f);
    glRotatef(90.0f, 1.0f, .0f, 0.0f);
    gluCylinder(pObj, 0.02f, 0.02f, 0.15f, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0f, .77f, 0.0f);
    gluSphere(pObj, 0.05f, 26, 13);
    glPopMatrix();

    // eyes
    glColor3f(.0f, 1.0f, .3f);
    glPushMatrix();
    glTranslatef(-0.08f, .56f, 0.22f);
    gluSphere(pObj, 0.045f, 26, 13);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.08f, .56f, 0.22f);
    gluSphere(pObj, 0.045f, 26, 13);
    glPopMatrix();

    // mouth
    glColor3f(.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0, .45, 0.2f);
    glScalef(0.4f, 0.08f, 0.02f);
    glutSolidCube(0.5);
    glPopMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.05, .41, 0.2f);
    glScalef(0.2f, 0.08f, 0.02f);
    glutSolidCube(0.5);
    glPopMatrix();
    glColor3f(.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-.02, .41, 0.2f);
    glScalef(0.08f, 0.08f, 0.02f);
    glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix(); // restore transform matrix state

    glColor3f(0.7f, 0.7f, 0.7f);
    // ombro esquerdo
    glPushMatrix();
    glTranslatef(0.3f, 0.2, 0.0f);
    // glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(pObj, 0.08, 26, 13);

    // braco
    glPushMatrix();
    // rot = 20 ate -30
    glTranslatef(0.02f, -0.06f, 0.0f);
    glRotatef(90.0f, 5.0f, 0.7f, 0.0f);
    glRotatef(rot, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

    // cotovelo
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(-90.0f, 5.0f, 0.7f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(pObj, 0.08, 26, 13);

    // antebraco
    glPushMatrix();
    glTranslatef(0.02f, -0.055f, 0.0f);
    glRotatef(90.0f, 5.0f, 0.8f, 0.0f);
    // glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

    // mao
    glPushMatrix();
    glRotatef(-90.0f, 5.0f, 0.8f, 0.0f);
    glScalef(0.8, 1.2, 0.6);
    glTranslatef(0.028, -0.2, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // dedo
    glPushMatrix();
    glTranslatef(-0.05, 0.02, 0.0f);
    glScalef(1.8, 1.0, 1.6);
    glRotatef(-90.0f, -1.0f, 1.0f, 0.0f);
    gluCylinder(pObj, 0.02f, 0.005f, 0.08f, 26, 13);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // ombro direito
    glPushMatrix();
    glTranslatef(-0.3f, 0.2, 0.0f);
    gluSphere(pObj, 0.08, 26, 13);

    // braco
    glPushMatrix();
    glTranslatef(-0.02f, -0.06f, 0.0f);
    glRotatef(90.0f, 5.0f, -0.7f, 0.0f);
    glRotatef(-rot, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

    // cotovelo
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.18);
    glRotatef(-90.0f, 5.0f, -0.7f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(pObj, 0.08, 26, 13);

    // antebraco
    glPushMatrix();
    glTranslatef(-0.02f, -0.055f, 0.0f);
    glRotatef(90.0f, 5.0f, -0.8f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

    // mao
    glPushMatrix();
    glRotatef(-90.0f, 5.0f, -0.8f, 0.0f);
    glScalef(0.8, 1.2, 0.6);
    glTranslatef(-0.028, -0.2, 0.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // dedo
    glPushMatrix();
    glTranslatef(0.05, 0.0, 0.0f);
    glScalef(1.8, 1.0, 1.6);
    glRotatef(-90.0f, -1.0f, -1.0f, 0.0f);
    gluCylinder(pObj, 0.02f, 0.005f, 0.08f, 26, 13);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // perna esquerda
    glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(0.15f, -0.28f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // coxa
    glPushMatrix();
    glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    glRotatef(rot, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);

    // joelho
    glPushMatrix();
    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
    // glRotatef(-30.0f, 5.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.28f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // panturrilha
    glPushMatrix();
    glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);

    // foot
    glPushMatrix();
    glScalef(1.2, 1.5, 1.0);
    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.28f, -0.01f);
    gluSphere(pObj, 0.05f, 26, 13);

    glPushMatrix();
    glTranslatef(0.00f, 0.0f, 0.0f);
    glScalef(0.5, 0.6, 0.7);
    gluCylinder(pObj, 0.07f, 0.05f, 0.2f, 26, 13);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.2f);
    gluSphere(pObj, 0.05f, 26, 13);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // perna direita
    glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(-0.15f, -0.28f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // coxa
    glPushMatrix();
    glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    glRotatef(-rot, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);

    // joelho
    glPushMatrix();
    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.28f, 0.0f);
    gluSphere(pObj, 0.08f, 26, 13);

    // panturrilha
    glPushMatrix();
    glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);

    // foot
    glPushMatrix();
    glScalef(1.2, 1.5, 1.0);
    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.28f, -0.01f);
    gluSphere(pObj, 0.05f, 26, 13);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(0.5, 0.6, 0.7);
    gluCylinder(pObj, 0.07f, 0.05f, 0.2f, 26, 13);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.2f);
    gluSphere(pObj, 0.05f, 26, 13);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

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
    glutCreateWindow("RoboArticulado");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutMainLoop();

    return 0;
}