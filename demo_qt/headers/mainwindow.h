#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget> // Afin que ce que l'on écrit dans la méthode de triggered soit reconnu

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

private:
    Ui::MainWindow *ui;
    QTabWidget *tabsWidget = new QTabWidget(this); // Afin que ce que l'on écrit dans la méthode de triggered soit reconnu
};
#endif // MAINWINDOW_H
