#include <GL/freeglut.h>

void initGL() {                         //  initialiser functions
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //  bg color
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

void display() {                        //  called at repaint request
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);         //  set model-view matrix
    glLoadIdentity();                   //  reset model-view matrix
    
    for(int i=0; i<200; i++) {
        glTranslatef((random() % 100 - 50)/1000.0, (random() % 100 - 50)/1000.0, 0.0f);    
        glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);    //  foreground color
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, -0.5f);
            
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(-0.5f, 0.5f);
        glEnd();
        glRotatef(45.0f+(random() % 100)/100.0, 0, 0, 1);
    } 
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutCreateWindow("base");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);

    glutDisplayFunc(display);           //  what function to call on repaint
    glutReshapeFunc(reshape);           //  what function to call on reshape 
    initGL();

    glutMainLoop();                     //  enter event-processing loop

    return 0;
}
