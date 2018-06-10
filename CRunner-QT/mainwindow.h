#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QString>
#include <QMessageBox>
#include <QProcess>
#include <iostream>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();
    void errors();
    void starting();
    void keyPressEvent(QKeyEvent *events);

private:
    Ui::MainWindow *ui;
    QMessageBox *messagebox;
    QProcess *run_command;
};

#endif // MAINWINDOW_H
