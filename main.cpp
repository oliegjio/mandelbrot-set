#ifdef _WIN32
	#include <windows.h>
#endif
#include <GL/glut.h>
#include <complex>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

//#define WIN_WIDTH 2560
//#define WIN_HEIGHT 1440

const float mandelbrot_range = 2.0f;
float view_range = mandelbrot_range;
const float range = std::sqrt(powf(mandelbrot_range, 2.0f) + powf(mandelbrot_range, 2.0f));

//float view_x = 0.0001f;
//float view_y = 0.0001f;

float view_x = 0.42884f;
float view_y = -0.231345f;

const float move_step = 10.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    const float step = (mandelbrot_range / 1500.0f) * view_range;
    const float jumps = 40.0f / view_range;

    std::complex<float> z;
    std::complex<float> c;

    glPointSize(1.5f);
    glBegin(GL_POINTS);
    for (float i = -view_range + view_x; i <= view_range + view_x; i += step)
    {
        for (float j = -view_range + view_y; j <= view_range + view_y; j += step)
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

void update_projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-view_range + view_x, view_range + view_x, -view_range + view_y, view_range + view_y, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    update_projection();
    glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            view_y += view_range / move_step;
            break;

        case GLUT_KEY_DOWN:
            view_y -= view_range / move_step;
            break;

        case GLUT_KEY_LEFT:
            view_x -= view_range / move_step;
            break;

        case GLUT_KEY_RIGHT:
            view_x += view_range / move_step;
            break;

        case GLUT_KEY_F1:
            view_range -= view_range / move_step;
            break;

        case GLUT_KEY_F2:
            view_range += view_range / move_step;
            break;

        default: return;
    }

    update_projection();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Mandelbrot Set");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}