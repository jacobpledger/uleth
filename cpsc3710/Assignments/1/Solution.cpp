#include<GLUT/glut.h>
#include<stdlib.h>
#include<iostream>

bool DO_FLAP = false;
float FLAP = 0.0;
unsigned char DIR = 'u';

void init(void)
{
    glClearColor(0.0, 0.60, 1.0, 0.0); //clear to sky blue-ish
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LINE_SMOOTH); //enable anti-aliasing
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //clear pixels
    glPushMatrix();
    
    //Main Body
    glColor3f (0.0, 0.0, 0.0);
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glEnd();
    
    //Antenae
    glLineWidth(2.0);
    glColor3f (0.0, 0.0, 0.0);
    
    //Left Antennae
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(-0.7, 0.0, 0.5);
    glEnd();
    
    //Right Antennae
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(-0.7, 0.0, -0.5);
    glEnd();
    
    //Wings
    
    //Flap left wings
    glRotatef(FLAP, 1.0, 0.0, 0.0);
    
    //Left Wings
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0); //connected to body
    glVertex3f(-1.0, 0.0, 1.2);
    glVertex3f(0.0, 0.0, 1.2);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0); //connected to body
    glVertex3f(0.0, 0.0, 1.2);
    glVertex3f(1.0, 0.0, 1.2);
    glEnd();
    
    //Flap right wings
    glRotatef((-2*FLAP), 1.0, 0.0, 0.0); //have to negate the flap from left wings
    
    //Right Wings
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0); //connected to body
    glVertex3f(-1.0, 0.0, -1.2);
    glVertex3f(0.0, 0.0, -1.2);
    glEnd();
    
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0); //connected to body
    glVertex3f(0.0, 0.0, -1.2);
    glVertex3f(1.0, 0.0, -1.2);
    glEnd();
    
    glPopMatrix();
    glutSwapBuffers();
}

void action(void)
{
    if (DO_FLAP == true)
    {
        if (DIR == 'u')
        {
            if (50 > FLAP && FLAP > -50)
            {
                FLAP -= 0.02;
                std::cout << FLAP << std::endl;
            }
            if (FLAP <= -49)
                DIR = 'd';
        }
        
        if (DIR == 'd')
        {
            if (50 > FLAP && FLAP > -50)
            {
                FLAP += 0.02;
                std::cout << FLAP << std::endl;
            }
            if (FLAP >= 49)
                DIR = 'u';
        }
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'f':
            if (DO_FLAP == true)
            {
                DO_FLAP = false;
            }
            else
            {
                DO_FLAP = true;
            }
            break;
        case '\e':
            exit(0);
        default:
            break;
    }
}

void mouse (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//display as wireframe
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//display as solid object
            break;
        default:
            break;
    }
}

void reshape (int w, int h)
/* supplied -- do not change!  */
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    /* set the viewing area -- use perspective projection 
     an object at the origin that is about 1 or 2 units wide should 
     be nicely visible    */
    glFrustum (-1.0, 1.0, -1.0, 1.0, 5.0, 15.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();            
    /* viewing transformation  
     sets the eye to be at (6,8,7.5) looking at the origin
     etc. */
    gluLookAt (6.0, 8.0, 7.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
}

int main(int argc, char** argv)
/* supplied -- do not change!   */
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(action);
    glutMainLoop();
    return 0;
}
