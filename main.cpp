#include <GL/glut.h>
#include <complex>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    std::complex<float> z;
    std::complex<float> c;

    const float step = 0.005;
    const float jumps = 20.0f;

    const float range = std::sqrt(powf(2.0f, 2.0f) + powf(2.0f, 2.0f));

    glBegin(GL_POINTS);
    for (float i = -2.0f; i <= 2.0f; i += step)
    {
        for (float j = -2.0f; j <= 2.0f; j += step)
        {
            z = {0, 0};
            c = {i, j};
            for (float k = 1; k <= jumps; k++)
            {
                z = (z * z) + c;
                if (std::abs(z) > range)
                {
                    glColor3f(k / jumps, 0.0f, 0.0f);
                    glVertex2f(c.real(), c.imag());
                    break;
                }
                if (k == jumps)
                {
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(c.real(), c.imag());
                    break;
                }
            }
        }
    }
    glEnd();

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Mandelbrot Set");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}