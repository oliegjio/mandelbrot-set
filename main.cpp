#include <GL/glut.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void setup()
{

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);



    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    setup();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Mandelbrot Set");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}