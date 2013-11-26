#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    child(NULL)
{
    ui->setupUi(this);
    child = new HunterPreyGL(this);
    this->setCentralWidget(child);
    child->Start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
