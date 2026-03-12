#include "../deps/affichage3D.h"

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <time.h>

#include <math.h>

#define MOUSE_SENS 0.003

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50;  // Position horizontale de la fenetre
static int wPy = 50;  // Position verticale de la fenetre

static float rotate_x = 0.0f;
static float rotate_y = 0.0f;

static int old_x = 0;
static int old_y = 0;

static float looking_at[3] = {0.0, 0.0, -1.0};

static float pos[3] = {0.0, 1.75, 0.0};

static int camera = 0;

static float movement_speed = 0.3;

enum wall_side
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Tab tab;

static void normalizeVector2D(float v[2])
{
    float l = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] /= l;
    v[1] /= l;
}

static void scaleVector2D(float v[2], float s)
{
    v[0] *= s;
    v[1] *= s;
}

static void model_maze(Tab t, float x, float z, float height)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 1.0, 1.0, 1.0});
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(x / 2, 0, z / 2);
    glVertex3f(-x / 2, 0, z / 2);
    glVertex3f(-x / 2, 0, -z / 2);
    glVertex3f(x / 2, 0, -z / 2);
    glEnd();

    float size_cell_x = x / t.width;
    float size_cell_z = z / t.height;

    float x_min = -x / 2;
    float z_min = -z / 2;

    float wall_thickness = 0.4;

    float pillar_thickness = 0.6;

    for (int i = 0; i < t.height; i++)
    {
        for (int j = 0; j < t.width; j++)
        {
            if (j == 0 && !t.cells[i][j].left)
            {
                glPushMatrix();
                glTranslatef(x_min, height / 2, z_min + size_cell_z * i + size_cell_z / 2);
                glScalef(wall_thickness, height, size_cell_z - pillar_thickness);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 1.0, 0.0, 1.0});
                glutSolidCube(1.0);
                glPopMatrix();
            }

            if (i == 0 && !t.cells[i][j].up)
            {
                glPushMatrix();
                glTranslatef(x_min + size_cell_x * j + size_cell_x / 2, height / 2, z_min);
                glScalef(size_cell_x - pillar_thickness, height, wall_thickness);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 1.0, 1.0});
                glutSolidCube(1.0);
                glPopMatrix();
            }

            if (!t.cells[i][j].down)
            {
                glPushMatrix();
                glTranslatef(x_min + size_cell_x * j + size_cell_x / 2, height / 2, z_min + size_cell_z * (i + 1));
                glScalef(size_cell_x - pillar_thickness, height, wall_thickness);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 0.0, 1.0});
                glutSolidCube(1.0);
                glPopMatrix();
            }

            if (!t.cells[i][j].right)
            {
                glPushMatrix();
                glTranslatef(x_min + size_cell_x * (j + 1), height / 2, z_min + size_cell_z * i + size_cell_z / 2);
                glScalef(wall_thickness, height, size_cell_z - pillar_thickness);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){0.0, 1.0, 0.0, 1.0});
                glutSolidCube(1.0);
                glPopMatrix();
            }
        }
    }

    // draw connection between walls
    for (int i = 0; i < t.height + 1; i++)
    {
        for (int j = 0; j < t.width + 1; j++)
        {
            glPushMatrix();
            glTranslatef(x_min + size_cell_x * j, height / 2, z_min + size_cell_z * i);
            glScalef(pillar_thickness, height, pillar_thickness);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){0.0, 0.0, 1.0, 1.0});
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

static void init(void)
{
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static void scene(void)
{
    glPushMatrix();
    model_maze(tab, 30, 30, 4);
    glPopMatrix();

    glPushMatrix();
    if (camera == 1)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (float[]){1.0, 0.0, 1.0, 1.0});
        glTranslatef(pos[0], pos[1], pos[2]);
        glutSolidSphere(0.3, 20, 20);
    }
    glPopMatrix();
}

static void display(void)
{

    glEnable(GL_LIGHT0);
    glPushMatrix();

    if (camera == 0)
        gluLookAt(
            pos[0], pos[1], pos[2],                                                 // position caméra
            pos[0] + looking_at[0], pos[1] + looking_at[1], pos[2] + looking_at[2], // point regardé
            0.0, 1.0, 0.0);
    else
        gluLookAt(
            0.0, 30.0, 0.0, // position caméra
            0.0, 0.0, 0.0,  // point regardé
            0.0, 0.0, -1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera == 0)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]){1.0, 1.0, 1.0, 1.0});
        glLightfv(GL_LIGHT0, GL_POSITION, (float[]){pos[0], pos[1], pos[2], 1.0});
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, (float[]){1.0, 1.0, 1.0, 1.0});
        glLightfv(GL_LIGHT0, GL_POSITION, (float[]){0.0, 10.0, 0.0, 0.0});
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    }
    scene();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
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
    glLoadIdentity();
}

static void idle(void)
{

    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    (void)button;
    (void)state;
    old_x = x;
    old_y = y;
    // glfwDisable(GLFW_MOUSE_CURSOR);
    glutPostRedisplay();
}

static void mouseMotion(int x, int y)
{
    // rotate_x += x - old_x;
    // rotate_y += y - old_y;
    // old_x = x;
    // old_y = y;
    // glutPostRedisplay();

    float dx = (x - old_x) * MOUSE_SENS;
    float dy = (y - old_y) * MOUSE_SENS;

    old_x = x;
    old_y = y;

    rotate_x += dx;
    rotate_y += dy;

    printf("rotate_x = %f, rotate_y = %f\n", rotate_x, rotate_y);

    looking_at[0] = cos(rotate_y) * sin(rotate_x);
    looking_at[1] = -sin(rotate_y);
    looking_at[2] = -cos(rotate_y) * cos(rotate_x);

    glutPostRedisplay();
}

static void passiveMotion(int x, int y)
{
    (void)x;
    (void)y;
}

static void keyboard(unsigned char key, int x, int y)
{
    printf("key\n");
    (void)x;
    (void)y;
    float vect[2] = {looking_at[0], looking_at[2]};
    normalizeVector2D(vect);
    scaleVector2D(vect, movement_speed);
    switch (key)
    {
    case 'c':
        camera = (camera + 1) % 2;
        break;
    case 'q':
        pos[0] += vect[1];
        pos[2] -= vect[0];
        break;
    case 'd':
        pos[0] -= vect[1];
        pos[2] += vect[0];
        break;
    case 'z':
        pos[0] += vect[0];
        pos[2] += vect[1];
        break;
    case 's':
        pos[0] -= vect[0];
        pos[2] -= vect[1];
        break;
    }

    glutPostRedisplay();
}

static void specialKey(int key, int x, int y)
{
    (void)x;
    (void)y;

    float vect[2] = {looking_at[0], looking_at[2]};
    normalizeVector2D(vect);
    scaleVector2D(vect, movement_speed);
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
    srand(time(NULL));

    tab = tab_start(10, 10, 0);
    generate(tab, 0, 1, 1);

    maze_show(tab);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Affichage 3D maze");
    init();

    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyboard);

    glutPassiveMotionFunc(passiveMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutIdleFunc(NULL);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
