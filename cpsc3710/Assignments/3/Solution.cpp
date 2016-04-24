#include<GLUT/glut.h>
#include<stdlib.h>
#include<iostream>
#include<cmath>

bool DO_FLAP = false;
float FLAP[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
float FSM[5] = {1,2,3,4,5};
unsigned char DIR[5] = {'u', 'u', 'u', 'u', 'u'};

float ROT = 0.0;

float VRP[3] = {0,0,10};
float VUP[3] = {0,1,0};
float VPN[3] = {0,0,-1};
float R[3] = {1,1,1};

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

void CrossProduct(float A[3], float B[3], float R[3])
{
    R[0] = A[1]*B[2]-A[2]*B[1];
    R[1] = A[2]*B[0]-A[0]*B[2];
    R[2] = A[0]*B[1]-A[1]*B[0];
}

void s_rotateAxis(GLfloat * A, GLfloat uX, GLfloat uY, GLfloat uZ, float Theta)
{   float ct,st,lv0,lv1,lv2;
    ct= cos(Theta);
    st= sin(Theta);
    
    lv0=A[0];
    lv1=A[1];
    lv2=A[2];
    
    A[0] = lv0*(uX*uX +  ct*(1.0-uX*uX))+lv1*(uX*uY * (1.0-ct) - uZ*st)+lv2*(uZ*uX * (1.0-ct) + uY*st);
    
    A[1] = lv0*(uX*uY * (1.0-ct) + uZ*st)+
    lv1*(uY*uY +  ct      * (1.0-uY*uY))  +
    lv2*(uY*uZ * (1.0-ct) - uX*st);
    
    A[2] = lv0*(uZ*uX * (1.0-ct) - uY*st)+
    lv1*(uY*uZ * (1.0-ct) + uX*st)+
    lv2*(uZ*uZ +  ct      * (1.0-uZ*uZ));
}

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
    
    gluLookAt(VRP[0], VRP[1], VRP[2], VRP[0]+VPN[0], VRP[1]+VPN[1], VRP[2]+VPN[2], VUP[0], VUP[1], VUP[2]);
    
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
                    if (50 > FLAP[n] && FLAP[n] > (-50))
                    {
                        FLAP[n] -= 0.02;
                    }
                    if (FLAP[n] <= -49)
                        DIR[n] = 'd';
                }
                
                if (DIR[n] == 'd')
                {
                    if (50 > FLAP[n] && FLAP[n] > (-50))
                    {
                        FLAP[n] += 0.02;
                    }
                    if (FLAP[n] >= 49)
                        DIR[n] = 'u';
                }
            }
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
        case 'b':
        {
            VRP[0]-=VPN[0];
            VRP[1]-=VPN[1];
            VRP[2]-=VPN[2];
            break;
        }
        case ' ':
        {
            VRP[0]+=VPN[0];
            VRP[1]+=VPN[1];
            VRP[2]+=VPN[2];
            break;
        }
        case 'm':
        {
            s_rotateAxis(VUP, VPN[0], VPN[1], VPN[2], (-0.2));
            break;   
        }
        case 'n':
        {
           s_rotateAxis(VUP, VPN[0], VPN[1], VPN[2], 0.2);
            break;
        }
        case '\e':
            exit(0);
        default:
            break;
    }
}

void SpecialKeyboard(int key, int x, int y)
{
    switch (key)
    {
        //pitch
        case GLUT_KEY_UP:
        {
            CrossProduct(VPN,VUP,R);
            s_rotateAxis(VPN, R[0], R[1], R[2], 0.2);
            s_rotateAxis(VUP, R[0], R[1], R[2], 0.2);
            break;
        }
        case GLUT_KEY_DOWN:
        {
            CrossProduct(VUP,VPN,R);
            s_rotateAxis(VPN, R[0], R[1], R[2], 0.2);
            s_rotateAxis(VUP, R[0], R[1], R[2], 0.2);
            break;
        }
        case GLUT_KEY_LEFT: //yaw
            s_rotateAxis(VPN, VUP[0], VUP[1], VUP[2], 0.2);
            break;
        case GLUT_KEY_RIGHT:
            s_rotateAxis(VPN, VUP[0], VUP[1], VUP[2], (-0.2));
            break;
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
    glutSpecialFunc(SpecialKeyboard);
    glutIdleFunc(action);
    glutMainLoop();
    return 0;
}
