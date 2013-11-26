#ifndef GLCANVAS_H
#define GLCANVAS_H
#include <QtGui>
#include <QGLWidget>
#include "CreatureGrid.h"

class HunterPreyGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit HunterPreyGL(QWidget *parent = 0);
    virtual ~HunterPreyGL();
    bool isInitialized() const;
    bool isRunning() const;
    void setGridSize(int width, int height);
    void Start();
    void Stop();
private:
    virtual void initializeGL();
    bool running, busy;
    QTimer* timer;
    Grid* grid;
    unsigned int gridWidth, gridHeight, gridSize;
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void updateOrtho();
signals:
public slots:
    virtual void updateGL();
};

#endif // GLCANVAS_H
