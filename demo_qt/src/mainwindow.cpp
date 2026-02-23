// Pour commenter rapidement sur Qt creator : contrôle + /
#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
// #include <QPushButton>
#include<QLabel>
//#include <QTabWidget> // On peut l'enlever puisque déclaré dans mainwindow.h

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QTabWidget *tabsWidget = new QTabWidget(this); // Instance de QTabWidget
    tabsWidget->addTab(new QWidget, "Tab1"); // Ajout d'un onglet. Prend en 1er paramètre un objet de type QWidget
                                       // et en deuxième une chaîne de caractère qui sera le titre de cet onglet
    tabsWidget->addTab(new QWidget, "Tab2");
    tabsWidget->addTab(new QWidget, "Tab3");
    tabsWidget->setMovable(true); // Pour permettre aux onglets de pouvoir bouger quand on les saisi avec la souris
    tabsWidget->setTabsClosable(true); // Pour ajouter une croix de fermeture
    setCentralWidget(tabsWidget); // Pour que le widget occupe l'espace, méthode de MainWindow
    // tabsWidget->show(); // setCentralWidget la remplace
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered(){
    QApplication::quit();
}


// Méthode apparue après que l'on ait fait un clic droit et "aller au slot"
void MainWindow::on_actionNew_File_triggered()
{

}

