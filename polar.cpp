#include <GL/freeglut.h>
#include <vector>
#include <complex>
int cycle=0;
struct plr{
    double real, imag;

};

struct plr polar;
struct plr polar2;
void initGL() {                         //  initialiser functions
    glClearColor(.0f, .0f, .0f, 1.0f);   //  bg color
}

void idle() {                           //   idle function
    glutPostRedisplay();                //  send re-paint request

}

void reshape(GLsizei width, GLsizei height) {
    if(height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}
void draw() {
    glBegin(GL_LINES);
        glColor3f(1.0f, .0f, .0f);
        glVertex2f(0, 0);
        glVertex2f(polar.real, polar.imag);
        glColor3f(.0f, 1.0f, .0f);
        glVertex2f(0, 0);
        glVertex2f(polar2.real, polar2.imag);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0, 0);
        glVertex2f(polar.real-0.01, polar.imag-0.01);
        glVertex2f(polar.real-0.01, polar.imag+0.01);
        glVertex2f(polar.real+0.01, polar.imag+0.01);
        glVertex2f(polar.real+0.01, polar.imag-0.01);
        glColor3f(0, 1, 0);
        glVertex2f(polar2.real-0.01, polar2.imag-0.01);
        glVertex2f(polar2.real-0.01, polar2.imag+0.01);
        glVertex2f(polar2.real+0.01, polar2.imag+0.01);
        glVertex2f(polar2.real+0.01, polar2.imag-0.01);
    glEnd();
}
void update(int step) {
    std::complex<double> z = 1i * 2*M_PI * step / 360;
    std::complex<double> expon = std::exp(z);  
    polar.real = std::real(expon);
    polar.imag = std::imag(expon);
    if(step%360<180) {
        polar2.real = std::real(-expon);
        polar2.imag = std::imag(-expon);
    }   

}

void display() {                        //  called at repaint request
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);         //  set model-view matrix
    glLoadIdentity();                   //  reset model-view matrix
    cycle++;
    update(cycle);
    draw();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);   //  set double buffered mode

    glutCreateWindow("base");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);           //  what function to call on repaint
    glutReshapeFunc(reshape);           //  what function to call on reshape
    glutIdleFunc(idle);                 //  what function to call when no
                                           //      processes are being processed
 
    initGL();

    glutMainLoop();                     //  enter event-processing loop

    return 0;
}
