#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget> // Afin que ce que l'on écrit dans la méthode de triggered soit reconnu
#include <QPlainTextEdit>
#include <QLabel>
#include <QTreeView>
#include <QSplitter>
#include <QFileSystemModel> // Permet de gérer les fichiers du système; complète QTreeView

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    // void quitClicked();

    void on_actionNew_File_triggered();

    void on_actionClose_File_triggered();

    void closeTab(int index); // Méthode que l'on déclare pour pouvoir fermer un onglet avec la croix de fermeture

    void createTab();

    void on_actionOpen_File_triggered();

    void openTabFile(QString filePath);

    QPlainTextEdit* currentTextEdit();

    QLabel* currentStatus();

    void textEditChanged();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void updateStatus();

    void on_actionOpen_Folder_triggered();

    void openTreeViewFile(QModelIndex index);

private:
    Ui::MainWindow *ui;

    QTabWidget *tabsWidget = new QTabWidget(this); // Afin que ce que l'on écrit dans la méthode de triggered soit reconnu

    QTreeView *treeView = new QTreeView;

    QSplitter *window = new QSplitter(this); // L'on passe "this" dans le constructeur

    QFileSystemModel *dirModel = new QFileSystemModel(this); // On appelle l'instance "dirModel"
};
#endif // MAINWINDOW_H
