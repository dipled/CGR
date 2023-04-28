// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>
  
// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat rot = 0.0f;
static GLfloat rot2 = 0.0f;
int indo = 1, count  = 0;
int flag = 0;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    }  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.7f, 0.8f, 1.0f, 0.0f);  

} 

// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_UP)  
        indo = 1;
  
    // Refresh the Window  
    glutPostRedisplay();  
}
  
// Called to draw scene  
void RenderScene(void){  

    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, 0.0f, -5.0f);  

    xRot += 1.0f;              
    //yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);  
    
    glutPostRedisplay();  

	glRotatef(xRot, 0.0f, 1.0f, 0.0f);
	// glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

    if(indo == 1 && count == 0){
        rot-=2;
        if(rot == -90){
            indo = 0;
            count++;            
        }
    }else if(indo == 0 && count == 0){
        rot+=2;
        if(rot == 0)
            indo = -1;
    }

    if(count > 0 && indo == 0){
        rot2-=5;
        if(rot2 == -90){
            indo = 1;
            count++;
        }
    }else if(count > 0 && indo == 1){
        rot2+=5;
        if(rot2 == 0){
            indo = 0;
            count++;
        }
        if(count == 11)
            count = 0;
    }
 
	//body
	glColor3f(0.7f, 0.7f, 0.7f);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glScalef(0.8f, 1.2, 0.8);
		glutSolidCube(0.5);

        //head
        glPushMatrix(); // save transform matrix state
            glTranslatef(0.0f, 0.48, 0.0f);
            glScalef(1.2, 1.0, 1.2);
            gluSphere(pObj, 0.24, 26, 26);

            //ears
            glPushMatrix();
                glTranslatef(0.23, 0.0, 0.0);
                glRotatef(90.0, 0.0, 5.0, 0.0);
                gluCylinder(pObj, 0.02, 0.02, 0.15, 26, 13);  
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.38, 0.0, 0.0f);
                glRotatef(90.0f, 0.0, 5.0, 0.0);
                gluCylinder(pObj, 0.02, 0.02, 0.15, 26, 13);  
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.4, 0.0, 0.0);
                gluSphere(pObj, 0.045, 26, 13);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.40, 0.0, 0.0);
                gluSphere(pObj, 0.045, 26, 13);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.23, 0.0, 0.0);
                gluSphere(pObj, 0.05, 26, 13);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.23, 0.0, 0.0);
                gluSphere(pObj, 0.05, 26, 13);
            glPopMatrix();


            //mouth
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0.0, -0.055, 0.234f);
                glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
                glScalef(0.2f, 0.05f, 0.02f);
                glutSolidCube(0.5);
            glPopMatrix();

            //eyes
            glColor3f(1.0f, 0.0f, 0.0f);
            glPushMatrix();
                glTranslatef(-0.08f, 0.05f, 0.185f);
                gluSphere(pObj, 0.045f, 26, 13);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.08f, 0.05f, 0.185f);
                gluSphere(pObj, 0.045f, 26, 13);
            glPopMatrix();

        glPopMatrix(); // restore transform matrix state
        

        glColor3f(0.7f, 0.7f, 0.7f);
        //ombro esquerdo
        glPushMatrix();
            glTranslatef(0.3f, 0.2, 0.0f);
            //de 0 ate -90
            glRotatef(rot, 1.0f, 0.0f, 0.0f);
            gluSphere(pObj, 0.08, 26, 13);

            //braco
            glPushMatrix();
                // rot = 20 ate -30
                glTranslatef(0.02f, -0.06f, 0.0f);
                glRotatef(90.0f, 5.0f, 0.7f, 0.0f);
                //glRotatef(-90.0, 5.0f, 0.0f, 0.0f);
                gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

                //cotovelo
                glPushMatrix();
                    glTranslatef(0.0, 0.0, 0.18);
                    glRotatef(-90.0f, 5.0f, 0.7f, 0.0f);
                    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                    gluSphere(pObj, 0.08, 26, 13);

                    //antebraco
                    glPushMatrix();
                        glTranslatef(0.02f, -0.055f, 0.0f);
                        glRotatef(90.0f, 5.0f, 0.8f, 0.0f);
                        //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
                        gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);
                        
                        //mao
                        glPushMatrix();
                            glRotatef(-90.0f, 5.0f, 0.8f, 0.0f);
                            glScalef(0.8, 1.2, 0.6);
                            glTranslatef(0.028, -0.2, 0.0f);
                            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                            //0 ate -90
                            glRotatef(rot2, 0.0f, 1.0f, 0.0f);
                            gluSphere(pObj, 0.08f, 26, 13);

                                //dedo
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


        //ombro direito
        glPushMatrix();
            glTranslatef(-0.3f, 0.2, 0.0f);
            glRotatef(rot, 1.0f, 0.0f, 0.0f);
            gluSphere(pObj, 0.08, 26, 13);

            //braco
            glPushMatrix();
                glTranslatef(-0.02f, -0.06f, 0.0f);
                glRotatef(90.0f, 5.0f, -0.7f, 0.0f);
                //glRotatef(-rot, 5.0f, 0.0f, 0.0f);
                gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);

                //cotovelo
                glPushMatrix();
                    glTranslatef(0.0, 0.0, 0.18);
                    glRotatef(-90.0f, 5.0f, -0.7f, 0.0f);
                    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                    gluSphere(pObj, 0.08, 26, 13);

                    //antebraco
                    glPushMatrix();
                        glTranslatef(-0.02f, -0.055f, 0.0f);
                        glRotatef(90.0f, 5.0f, -0.8f, 0.0f);
                        gluCylinder(pObj, 0.05f, 0.05f, 0.2f, 26, 13);
                        
                        //mao
                        glPushMatrix();
                            glRotatef(-90.0f, 5.0f, -0.8f, 0.0f);
                            glScalef(0.8, 1.2, 0.6);
                            glTranslatef(-0.028, -0.2, 0.0f);
                            glRotatef(rot2, 0.0f, 1.0f, 0.0f);
                            gluSphere(pObj, 0.08f, 26, 13);

                                //dedo
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


        //perna esquerda
        glPushMatrix();
            glScalef(1.0, 1.0, 1.0);
            glTranslatef(0.15f, -0.28f, 0.0f);
            gluSphere(pObj, 0.08f, 26, 13);

            //coxa
            glPushMatrix();
                glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
                //glRotatef(rot, 5.0f, 0.0f, 0.0f);
                gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);  

                //joelho
                glPushMatrix();
                    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
                    //glRotatef(-30.0f, 5.0f, 0.0f, 0.0f);
                    glTranslatef(0.0f, -0.28f, 0.0f);
                    gluSphere(pObj, 0.08f, 26, 13);

                    //panturrilha
                    glPushMatrix();
                        glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
                        gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13); 

                        //foot
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


        //perna direita
        glPushMatrix();
            glScalef(1.0, 1.0, 1.0);
            glTranslatef(-0.15f, -0.28f, 0.0f);
            gluSphere(pObj, 0.08f, 26, 13);

            //coxa
            glPushMatrix();
                glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
                //glRotatef(-rot, 5.0f, 0.0f, 0.0f);
                gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13);  

                //joelho
                glPushMatrix();
                    glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
                    glTranslatef(0.0f, -0.28f, 0.0f);
                    gluSphere(pObj, 0.08f, 26, 13);

                    //panturrilha
                    glPushMatrix();
                        glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
                        gluCylinder(pObj, 0.05f, 0.05f, 0.28f, 26, 13); 

                        //foot
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

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Modeling with Quadrics");  
    glutReshapeFunc(ChangeSize);   
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);  
    SetupRC();  

    glutMainLoop();  
      
    return 0; 
}