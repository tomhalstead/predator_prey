#include "hunterPreyGL.h"
#include "GL/glu.h"

#define H_POP_FACTOR    80
#define P_POP_FACTOR    4

HunterPreyGL::HunterPreyGL(QWidget *parent) :
    QGLWidget(parent),running(false),busy(false),timer(NULL),grid(NULL)
{
    this->setAutoBufferSwap(true);
    setFocusPolicy(Qt::StrongFocus);
    Random::Seed();
    setGridSize(100,100);
}

HunterPreyGL::~HunterPreyGL()
{
    if(timer) {
        delete timer;
        timer = NULL;
    }
    if(grid) {
        delete grid;
        grid = NULL;
    }
}

bool HunterPreyGL::isInitialized() const
{
    return grid ? true: false;
}

bool HunterPreyGL::isRunning() const
{
    return (timer && timer->isActive()) ? true : false;
}

void HunterPreyGL::setGridSize(int width, int height)
{
    if(timer)
        timer->stop();
    while(busy);
    if(grid)
        delete grid;
    gridWidth = width;
    gridHeight = height;
    gridSize = gridHeight * gridWidth;
    grid = new Grid(gridWidth,gridHeight);
    grid->Populate(gridSize / H_POP_FACTOR, gridSize / P_POP_FACTOR);
    updateOrtho();
    Start();
}

void HunterPreyGL::Start()
{
    if(grid) {
        if(!timer) {
            timer = new QTimer(this);
            connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
        }
        timer->start(50);
    }
}

void HunterPreyGL::Stop()
{
    if(timer)
        timer->stop();
}


void HunterPreyGL::initializeGL() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClearColor(255,255,255,0);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void HunterPreyGL::resizeEvent(QResizeEvent *event)
{
    resizeGL(event->size().width(),event->size().height());
    paintGL();
}

void HunterPreyGL::keyPressEvent(QKeyEvent *event)
{
    if(event) {
        switch(event->key()) {
        case Qt::Key_Plus:
            this->parentWidget()->resize(QSize(this->parentWidget()->width()+10,this->parentWidget()->height()+10));
            break;
        case Qt::Key_Minus:
            this->parentWidget()->resize(QSize(this->parentWidget()->width()-10,this->parentWidget()->height()-10));
            break;
        }
    }
    else {
        qDebug() << "Fired empty key event.";
    }
}

void HunterPreyGL::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(grid) {
        glClear(GL_COLOR_BUFFER_BIT);
        busy = true;
        int row = 0;
        int col = 0;
        char* snapshot = grid->Snapshot();
        while(*snapshot) {
            if(*snapshot == '\n') {
                ++row;
                col = 0;
            }
            else if(*snapshot == '0'){
                ++col;
            }
            else {
                glBegin(GL_QUADS);
                if(*snapshot=='H')
                    glColor3f(1.0f,0.0f,0.0f);
                else
                    glColor3f(0.0f,0.0f,1.0f);
                glVertex2f(float(col),float(row));
                glVertex2f(float(col),float(row)+1.0f);
                glVertex2f(float(col)+1.0f,float(row)+1.0f);
                glVertex2f(float(col)+1.0f,float(row));
                glEnd();
                ++col;
             }
             ++snapshot;
        }
        snapshot = NULL;
        busy = false;
    }
    swapBuffers(); //auto swap buffers currently not working
}

void HunterPreyGL::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    updateOrtho();
}

void HunterPreyGL::updateOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f,float(gridWidth),float(gridHeight),0.0f,-1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void HunterPreyGL::updateGL()
{
    if(grid) {
        grid->Move();
        paintGL();
    }
}
