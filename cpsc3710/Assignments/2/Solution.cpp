#include<GLUT/glut.h>
#include<stdlib.h>
#include<iostream>

bool DO_FLAP = false;
float FLAP[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
float ROT = 0.0;
float Z = 10.0;
float FSM[5] = {1,2,3,4,5};
unsigned char DIR[5] = {'u', 'u', 'u', 'u', 'u'};

class butterfly
{
public:
    butterfly(int n);
private:
    int num;
};

butterfly::butterfly(int n)
{
    num = n;
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
    glRotatef((FLAP[num]), 1.0, 0.0, 0.0);
    
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
    glRotatef((-2*FLAP[num]), 1.0, 0.0, 0.0);
    
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
};

void init(void)
{
    glClearColor(0.0, 0.60, 1.0, 0.0); //clear to sky blue-ish
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH); //enable anti-aliasing
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //clear pixels
    glClear(GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    gluLookAt(0, 0, Z, 0, 0, 0, 0, 1, 0);
    
    //create the center object
    //square base
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, 0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.5);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.0, -0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, -0.5);
    glEnd();
    
    //sides
    //front
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, 0.5);
    
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0.0, 0.5);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 4.0, 0.0);
    glEnd();
    
    //right side
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0.0, 0.5);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.0, -0.5);
    
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 4.0, 0.0);
    glEnd();
    
    //back side
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.0, -0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, -0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 4.0, 0.0);
    glEnd();
    
    //left side
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, -0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.0, 0.5);
    
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 4.0, 0.0);
    glEnd();
    
    //make the butterflies
    
    glRotatef(-ROT, 0, 1, 0);
    glTranslatef(0, 2, 2);
    butterfly b1(0);
    glTranslatef(0, -2, -2);
    
    glRotatef((-1.5*ROT), 0, 1, 0);
    glTranslatef(0, 4, 4);
    butterfly b2(1);
    glTranslatef(0, -4,-4);
    
    glRotatef((-1.5*ROT), 0, 1, 0);
    glTranslatef(0, 5, 10);
    butterfly b5(4);
    glTranslatef(0, -5, -10);
    
    glRotatef((-1.5*ROT), 0, 1, 0);
    glTranslatef(0, 3, 6);
    butterfly b3(2);
    glTranslatef(0, -3, -6);
    
    glRotatef((-1.5*ROT), 0, 1, 0);
    glTranslatef(0, 3, 8);
    butterfly b4(3);
    glTranslatef(0, -3, -8);
    
    glPopMatrix();
    glutSwapBuffers();
}

void action(void)
{
    if (DO_FLAP == true)
    {
        ROT += 0.01;
        for (int n = 0; n < 5; ++n)
        {
            for (int i = 0; i < FSM[n]; ++i)
            {
                if (DIR[n] == 'u')
                {
                    if (50 > FLAP[n] && FLAP[n] > -50)
                    {
                        FLAP[n] -= 0.02;
                    }
                    if (FLAP[n] <= -49)
                        DIR[n] = 'd';
                }
                
                if (DIR[n] == 'd')
                {
                    if (50 > FLAP[n] && FLAP[n] > -50)
                    {
                        FLAP[n] += 0.02;
                    }
                    if (FLAP[n] >= 49)
                        DIR[n] = 'u';
                }
                glutPostRedisplay();
            }
        }
    }
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
        case 'm':
        {
            Z-=0.5;
            break;
        }
        case 'b':
        {
            Z+=0.5;
            break;
        }
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
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-5.0, 5.0, -1.0, 10.0, 4.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(action);
    glutMainLoop();
    return 0;
}
