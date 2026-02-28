#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame> // Pour gérer les pages
#include <QLabel> // Pour écrire des textes

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

void MainWindow::on_pushButton_clicked()
{
    // L'index de la page est simplement son ordre
    // On commence par 0 comme avec les tableaux en programmation
    ui->stackedWidget->setCurrentIndex(0); // A la place "ui->" l'on aurait pu aussi mettre "this->ui"
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_3_clicked()
{
    // Le terme "frame" signifie "cadre". C'est ce qui sert en général à gérer les pages
    QFrame *frame = new QFrame(this); // L'on crée une frame
    QLabel *label = new QLabel(frame); // Le label sera à l'intérieur de la frame
    label->setText("New page"); // Le label affichera "New page"
    ui->stackedWidget->addWidget(frame); // Puis l'on passe la frame que l'on a crée
    ui->stackedWidget->setCurrentWidget(frame); // Rend la page visible. Sans elle, l'utilisateur verrait toujours l'ancienne page
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1); // "ui->stackedWidget->currentIndex()-1" sert à récupérer l'index courant -1
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1); // "ui->stackedWidget->currentIndex()-1" sert à récupérer l'index courant +1
}

