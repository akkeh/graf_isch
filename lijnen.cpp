#include <GL/freeglut.h>
#include <vector>
struct lijn{
    double x1, y1;
    double x2, y2;
    float r, g, b, a;
};
int cycle = 0;
int branch = 1;
//std::vector<std::vector<struct lijn> >lijnen;
std::vector<struct lijn>lijnen;
std::vector<std::vector<struct lijn> > oudl;
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
void add_line() {
    lijn l;
    if((lijnen[lijnen.size()-1].x2 > -1) && (lijnen[lijnen.size()-1].x2 < 1) && (lijnen[lijnen.size()-1].y2 > -1) && (lijnen[lijnen.size()-1].y2 < 1)) {
        l.x1 = lijnen[lijnen.size()-1].x2;
        l.y1 = lijnen[lijnen.size()-1].y2;
        l.x2 = lijnen[lijnen.size()-1].x2 + (random() % 100 - 50)/1000.0;
        l.y2 = lijnen[lijnen.size()-1].y2 + (random() % 100 - 50)/1000.0;
        l.r = float(random() % 100 / 100.0); 
        l.g = float(random() % 100 / 100.0);
        l.b = float(random() % 100 / 100.0);
        l.a = 1.0f;
    } else {
        oudl.push_back(lijnen);
        lijnen.clear();
        lijn l;
        l.x1 = 0.0;
        l.y1 = 0.0;
        l.x2 = 0.0;
        l.y2 = 0.0;
        l.r = float(random() % 100 / 100.0); 
        l.g = float(random() % 100 / 100.0);
        l.b = float(random() % 100 / 100.0);       
        l.a = 1.0f;
        lijnen.push_back(l);
        cycle = 0;
    }

    
    lijnen.push_back(l);
         

}
void render_lines() {
 
    glBegin(GL_LINES);
            for(int i=0; i<lijnen.size(); i++) {
                glColor4f(float(lijnen[i].r), float(lijnen[i].g), float(lijnen[i].b), 1.0f);  
                glVertex2f(lijnen[i].x1, lijnen[i].y1);
                glVertex2f(lijnen[i].x2, lijnen[i].y2);
            }
        for(int i=0; i<oudl.size(); i++) {
            for(int n=0; n<oudl[i].size(); n++) {
                oudl[i][n].a = oudl[i][n].a*0.99;
                glColor4f(oudl[i][n].r, oudl[i][n].g, oudl[i][n].b, oudl[i][n].a);  
                glVertex2f(oudl[i][n].x1, oudl[i][n].y1);
                glVertex2f(oudl[i][n].x2, oudl[i][n].y2);
            }
        }
            
    glEnd();
}

void display() {                        //  called at repaint request
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);         //  set model-view matrix
    glLoadIdentity();                   //  reset model-view matrix
    cycle++;
    if(cycle % 1 == 0) add_line(); 
    render_lines();    
    
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
    lijn l;
    l.x1 = 0.0;
    l.y1 = 0.0;
    l.x2 = 0.0;
    l.y2 = 0.0;
    lijnen.push_back(l);

                                       //      processes are being processed
 
    initGL();

    glutMainLoop();                     //  enter event-processing loop

    return 0;
}
