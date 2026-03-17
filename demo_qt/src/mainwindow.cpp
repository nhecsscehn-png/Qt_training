// Pour commenter rapidement sur Qt creator : contrôle + /
#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox> // Affiche des messages dans des fenêtres
#include <QTextStream>
#include <QList>
#include <QFontDatabase>
// #include <QPushButton>
// #include<QLabel> // Nécessaire pour le fonctionnement du label plus en-dessous et pour la barre de statut
// #include <QTabWidget> // On peut l'enlever puisque déclaré dans mainwindow.h

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
    // setCentralWidget(tabsWidget); // Pour que le widget occupe l'espace, méthode de MainWindow
    setCentralWidget(window); // window est le QSplitter

    setCentralWidget(window);

    treeView->setMaximumWidth(0);
    treeView->setMaximumWidth(0);

    window->addWidget(treeView); // Dans le QSplitter, l'on doit ajouter les widgets que l'on veut splitter
    window->addWidget(tabsWidget);

    // tabsWidget->show(); // setCentralWidget la remplace

    // Il existe un signal qui permet de détecté le clique sur la croix de fermeture
    connect(tabsWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(openTreeViewFile(QModelIndex)));

    QFontDatabase::addApplicationFont("fonts/StardosStencil-Regular.ttf"); // L'on doit mettre le chemin pour aller au fichier
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
    // QFrame *tabFrame = new QFrame(this);
    // tabsWidget->addTab(tabFrame, "Untitled");
    // Se renseigner dessus
    // QLabel *label = new QLabel(tabFrame);
    // label->setText("Hello world");
    MainWindow::createTab(); // Parceque l'on a crée une fonction dédiée dans mainwindow.h
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

void MainWindow::createTab()
{
    QFrame *tabFrame = new QFrame(this);
    QVBoxLayout *tabLayout = new QVBoxLayout(tabFrame);

    QPlainTextEdit *fileEdit = new QPlainTextEdit();

    fileEdit->setObjectName("textEdit"); // On nomme l'objet

    //QFont font = fileEdit->document()->defaultFont();
    QFont font;
    font.setFamily("Stardos Stencil"); // L'on doit être placer le nom exacte de la police ici
    fileEdit->setFont(font);

    fileEdit->setTabStopDistance(QFontMetrics(fileEdit->font()).horizontalAdvance(' ') * 4);

    tabLayout->addWidget(fileEdit);

    // Pour ajouter la barre de statut
    QLabel *status = new QLabel(this);
    status->setText("Line 1, Column 1"); // Ajout d'un texte par défaut
    status->setObjectName("status");

    tabLayout->addWidget(fileEdit);
    tabLayout->addWidget(status);

    int tab = tabsWidget->addTab(tabFrame, "Untitled");
    tabsWidget->setCurrentIndex(tab);

    tabsWidget->setTabToolTip(tabsWidget->currentIndex(), "Untitled");

    connect(MainWindow::currentTextEdit(), SIGNAL(textChanged()), this, SLOT(textEditChanged())); // Pour écouter un signal
    connect(MainWindow::currentTextEdit(), SIGNAL(cursorPositionChanged()), this, SLOT(updateStatus())); // Signal pour la barre d'attribut change l'indication de ligne et de colonne au fur ét à mesure du déplacement du curseur
}

void MainWindow::openTabFile(QString filePath)
{
    QFile file(filePath); // Récupère le fichier à l'aide de QFile à l'aide du chemin filePath
    QFileInfo fileName(filePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString()); // Type:warning; Quelle fenêtre ?:celle-ci; Message:"Warining", "Cannot open file : "; et à la fin on concatène grâce à + file.errorString()
        return; // Afin d'ignorer les autres lignes de code qui vont suivre ce if et sortir de cette fonction
    }
                          // (Retourne l'index courant, chemin complet du fichier)
    tabsWidget->setTabToolTip(tabsWidget->currentIndex(), filePath); // Le tooltip est le petit texte qui s'affiche lorsque l'on survole un élément

    QTextStream in(&file); // Récupérer le texte dans un fichier; Il faut passer à QTextStream une adresse (pointeur ou &variable). "in" pour lire et "out" pour écrire
    QString text = in.readAll(); // Récupérer toutes les lignes contenues dans le fichier

    MainWindow::currentTextEdit()->setPlainText(text); // L'on a spécifié "text" qui se trouve juste au-dessus

    file.close();

    tabsWidget->setTabText(tabsWidget->currentIndex(), fileName.fileName());
}

QPlainTextEdit* MainWindow::currentTextEdit()
{                                                                                    // Dans Qt, l'on peut nommer les objets ce qui permet de les spécifier
    QList<QPlainTextEdit *> fileEditList = tabsWidget->findChildren<QPlainTextEdit *>("textEdit"); // On spécifie l'objet nommé "textEdit"
    // return fileEditList[tabsWidget->currentIndex()]; // Retourner celui qui est à l'index
    for(int i = 0; i < fileEditList.count(); i++){
        if(tabsWidget->indexOf(fileEditList[i]->parentWidget()) == tabsWidget->currentIndex()){
            return fileEditList[i];
        }
    }
    return new QPlainTextEdit;
}

QLabel* MainWindow::currentStatus()
{                                                                                    // Dans Qt, l'on peut nommer les objets ce qui permet de les spécifier
    QList<QLabel *>statusList = tabsWidget->findChildren<QLabel *>("status"); // On spécifie l'objet nommé "textEdit"
    // return fileEditList[tabsWidget->currentIndex()]; // Retourner celui qui est à l'index
    for(int i = 0; i < statusList.count(); i++){
        if(tabsWidget->indexOf(statusList[i]->parentWidget()) == tabsWidget->currentIndex()){
            return statusList[i];
        }
    }
    return new QLabel;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open the file"); // Pour récupérer le chemin d'un fichier qu'on va sélectionner dans une fenêtre. On a appelé la variable "filePath"
    MainWindow::createTab(); // Crée un nouvel onglet vide qui accueillera le contenu du fichier. "createTab();" serait suffisant depuis l'intérieur de la classe
    MainWindow::openTabFile(filePath); // Charge le contenu du fichier sélectionné dans l'onglet nouvellement créé
}

// Méthode qui sera appelé quand le contenu du texte sera changé
void MainWindow::textEditChanged()
{
    QString tabName = tabsWidget->tabText(tabsWidget->currentIndex()); // L'on doit d'abord récupérer le titre de l'onglet
    if (tabName.at(0) != "*"){  // "at" pour récupérer l'index spécifique d'une chaîne de caractère
        tabsWidget->setTabText(tabsWidget->currentIndex(),"*"+tabName); // le tabName est le titre de l'onglet
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = tabsWidget->tabToolTip(tabsWidget->currentIndex());
    if (fileName == "Untitled"){
        MainWindow::on_actionSave_As_triggered();
        return;
    }

    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QTextStream out(&file); // Avec "in" c'est pour lire. Cette fois-ci, avec out, c'est pour écrire
    QString text = MainWindow::currentTextEdit()->toPlainText(); // "toPlainText" pour récupérer le contenu texte du widget

    out << text;

    file.close();

    QString newTabText = tabsWidget->tabText(tabsWidget->currentIndex()).remove(0, 1);
    tabsWidget->setTabText(tabsWidget->currentIndex(), newTabText);
}


void MainWindow::on_actionSave_As_triggered()
{
    if(tabsWidget->count() == 0){ // Si 0 onglet est ouvert
        QMessageBox::warning(this, "Warning", "Cannot save file !");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save As ...");
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QTextStream out(&file);
    QString text = MainWindow::currentTextEdit()->toPlainText();

    out << text;

    file.close();

    MainWindow::openTabFile(filePath);
}

void MainWindow::updateStatus()
{
    // On le place dans un QString car QLabel n'aime pas les entiers
    QString line = QString::number(MainWindow::currentTextEdit()->textCursor().blockNumber()+1); // blockNumber() pour récupérer la ligne
    QString column = QString::number(MainWindow::currentTextEdit()->textCursor().columnNumber()+1); // columnNumber() pour récupérer la colonne

    QString newStatus = "Line " + line + ", Column " + column;

    MainWindow::currentStatus()->setText(newStatus);
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    // Ouvre une boîte de dialogue pour sélectionner un dossier
    // Paramètres : (parent, titre, dossier de départ, options)
    // Retourne : QUrl avec le chemin du dossier sélectionné (conversion implicite depuis QString)
    //            ou URL vide si annulé
    QUrl dirPath = QFileDialog::getExistingDirectory(
        this,                           // Fenêtre parente (pour la modalité et le centrage)
        "Open Folder",                  // Titre de la boîte de dialogue
        "/",                            // Dossier de départ pour la navigation (racine)
        QFileDialog::ShowDirsOnly       // Option : n'afficher que les dossiers (pas les fichiers)
    );
    dirModel->setRootPath(dirPath.toString());
    treeView->setModel(dirModel);
    treeView->setRootIndex(dirModel->index(dirPath.toString()));
    // Pour quelques colonnes que treeView affiche par défaut. "hideColumn" pour cacher les colonnes qu'on ne veut pas voir apparaître
    treeView->hideColumn(1);
    treeView->hideColumn(2);
    treeView->hideColumn(3);

    treeView->setMinimumWidth(width() * 20 / 100); // 20%
    treeView->setMaximumWidth(width() * 30 / 100); // 30%
}

void MainWindow::openTreeViewFile(QModelIndex index)
{
    MainWindow::createTab(); // Créer un onglet
    QString filePath = dirModel->fileInfo(index).absoluteFilePath(); // absolutFilePath : méthode de QFileInfo pour avoir le chemin absolu du fichier
    MainWindow::openTabFile(filePath);
}

