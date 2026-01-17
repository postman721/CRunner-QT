#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// MainWindow is a QWidget-based top-level window.
// Qt 6: include <QMainWindow> from the Widgets module.
#include <QMainWindow>

// We override keyPressEvent, so we need QKeyEvent.
#include <QKeyEvent>

// For showing the about box.
#include <QMessageBox>

// For launching external programs.
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Explicit constructor is standard Qt style.
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor: deletes the generated UI object.
    ~MainWindow();

private slots:
    // Auto-connected by Qt Designer naming convention:
    // objectName: lineEdit
    // signal: returnPressed()
    // slot: on_lineEdit_returnPressed()
    void on_lineEdit_returnPressed();

protected:
    // We override this so we can handle F1 and ESC globally.
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui = nullptr;
};

#endif // MAINWINDOW_H
