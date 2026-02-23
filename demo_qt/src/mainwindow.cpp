#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
// #include <QPushButton>
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *myLabel = new QLabel(this);
    myLabel->setText("Hello");
    setCentralWidget(myLabel);

    // QPushButton *myButton = new QPushButton(this);
    // myButton->setText("Quit");

    // connect(myButton, SIGNAL(clicked()), this, SLOT(quitClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered(){
    QApplication::quit();
}

// void MainWindow::quitClicked(){
//     QApplication::quit();
// }



