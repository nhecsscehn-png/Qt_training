#include "mainwindow.h"
#include "ui_mainwindow.h"

float number1, number2, result = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Pour entrer le premier nombre dans le premier label
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    number1=arg1.toFloat();
}

// Pour entrer le second nombre dans le second label
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    number2=arg1.toFloat();
}

// Pour faire l'addition du premier et deuxième nombre et entrer le résultat dans le premier label
void MainWindow::on_pushButton_clicked()
{
    result = number1 + number2;
    ui->label->setText(QString::number(result));
}

// Pour faire la soustraction du premier et deuxième nombre et entrer le résultat dans le premier label
void MainWindow::on_pushButton_2_clicked()
{
    result = number1 - number2;
    ui->label->setText(QString::number(result));
}

// Pour faire la multiplication du premier et deuxième nombre et entrer le résultat dans le premier label
void MainWindow::on_pushButton_3_clicked()
{
    result = number1 * number2;
    ui->label->setText(QString::number(result));
}

// Pour faire la division du premier et deuxième nombre et entrer le résultat dans le premier label
void MainWindow::on_pushButton_4_clicked()
{
    result = number1 / number2;
    ui->label->setText(QString::number(result));
}

