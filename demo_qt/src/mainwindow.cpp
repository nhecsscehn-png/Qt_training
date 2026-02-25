// Pour commenter rapidement sur Qt creator : contrôle + /
#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
//#include <QPushButton>
//#include<QLabel> // Nécessaire pour le fonctionnement du label plus en-dessous
//#include <QTabWidget> // On peut l'enlever puisque déclaré dans mainwindow.h

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QTabWidget *tabsWidget = new QTabWidget(this); // Instance de QTabWidget
    // tabsWidget->addTab(new QWidget, "Tab1"); // Ajout d'un onglet. Prend en 1er paramètre un objet de type QWidget
    //                                    // et en deuxième une chaîne de caractère qui sera le titre de cet onglet
    // tabsWidget->addTab(new QWidget, "Tab2");
    // tabsWidget->addTab(new QWidget, "Tab3");
    tabsWidget->setMovable(true); // Pour permettre aux onglets de pouvoir bouger quand on les saisi avec la souris
    tabsWidget->setTabsClosable(true); // Pour ajouter une croix de fermeture
    setCentralWidget(tabsWidget); // Pour que le widget occupe l'espace, méthode de MainWindow
    // tabsWidget->show(); // setCentralWidget la remplace

    // Il existe un signal qui permet de détecté le clique sur la croix de fermeture
    connect(tabsWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
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
    // Créer un nouvel onglet nommé "Untitled"
    QFrame *tabFrame = new QFrame(this);
    tabsWidget->addTab(tabFrame, "Untitled");
    // Se renseigner dessus
    // QLabel *label = new QLabel(tabFrame);
    // label->setText("Hello world");
}


void MainWindow::on_actionClose_File_triggered()
{
    // Méthode pour supprimer l'onglet courant (avec "Close File" dans la barre de menu que l'on a placé ou contrôle + w)
    tabsWidget->removeTab(tabsWidget->currentIndex());
}

// Méthode que l'on définit et qui est déclaré dans mainwindow.h
void MainWindow::closeTab(int index)
{
    tabsWidget->removeTab(index); // On ne spécifie pas "currentIndex" car l'on pourrait fermer l'onglet actif en cliquant sur la croix d'un onglet qui ne l'est pas
}

