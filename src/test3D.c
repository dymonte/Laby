#include "test3D.h"

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50;  // Position horizontale de la fenetre
static int wPy = 50;  // Position verticale de la fenetre

static float looking_at[3] = {0.0, 0.0, 0.0};

static float pos[3] = {0.0, 2, 0.0};

static int old_x = 0;
static int old_y = 0;

static float rotate_x = 0;
static float rotate_y = 0;

static void normalizeVector2D(float v[2])
{
    float l = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] /= l;
    v[1] /= l;
}

static void init(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static void scene(void)
{
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 0.0, 1.0});

    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(-5.0, 10.0, -5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glVertex3f(5.0, 10.0, -5.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 1.0, 0.0, 1.0});
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(5.0, 10.0, 5.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 0.0, 1.0});
    glVertex3f(-5.0, 0.0, 5.0);
    glVertex3f(-5.0, 10.0, 5.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 1.0, 1.0});
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(-5.0, 10.0, -5.0);

    glEnd();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 1.0, 1.0, 1.0});

    glBegin(GL_QUADS);
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(-5.0, 0.0, 5.0);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glEnd();

    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* caméra */
    gluLookAt(
        pos[0], pos[1], pos[2],                                                 // position caméra
        pos[0] + looking_at[0], pos[1] + looking_at[1], pos[2] + looking_at[2], // point regardé
        0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();

    glLightfv(GL_LIGHT0, GL_AMBIENT, (float[]){1.0, 1.0, 1.0, 0.2});
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

static void reshape(int wx, int wy)
{
    wTx = wx;
    wTy = wy;

    glViewport(0, 0, wx, wy);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)wx / wy, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

static void idle(void)
{
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    old_x = x;
    old_y = y;
}

static void mouseMotion(int x, int y)
{
    float dx = (x - old_x) * 0.003;
    float dy = (y - old_y) * 0.003;

    old_x = x;
    old_y = y;

    rotate_x += dx;
    rotate_y += dy;

    printf("rotate_x = %f, rotate_y = %f\n", rotate_x, rotate_y);

    looking_at[0] = cos(rotate_y) * sin(rotate_x);
    looking_at[1] = sin(rotate_y);
    looking_at[2] = -cos(rotate_y) * cos(rotate_x);

    glutPostRedisplay();
}

static void specialKey(int key, int x, int y)
{
    float vect[2] = {looking_at[0], looking_at[2]};
    normalizeVector2D(vect);
    switch (key)
    {
    case GLUT_KEY_LEFT:
        pos[0] += vect[1];
        pos[2] -= vect[0];
        break;
    case GLUT_KEY_RIGHT:
        pos[0] -= vect[1];
        pos[2] += vect[0];
        break;
    case GLUT_KEY_UP:
        pos[0] += vect[0];
        pos[2] += vect[1];
        break;
    case GLUT_KEY_DOWN:
        pos[0] -= vect[0];
        pos[2] -= vect[1];
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Gestion �v�nementielle de GLUt");
    init();

    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutSpecialFunc(specialKey);

    // glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutIdleFunc(NULL);
    glutDisplayFunc(display);
    glutMainLoop();
    return (0);
}