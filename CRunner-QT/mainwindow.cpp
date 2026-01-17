#include "mainwindow.h"
#include "ui_mainwindow.h"

// QApplication::quit()
#include <QApplication>

// QStringList needed for argument lists.
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Builds the UI
    ui->setupUi(this);

    // Remove window frame (no title bar, no buttons, no border)
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    // Optional: keep rounded corners visible
    setAttribute(Qt::WA_TranslucentBackground);

    // Small hint for users.
    ui->statusBar->showMessage("F1 for info.");
}

MainWindow::~MainWindow()
{
    // ui is created with new, so we delete it here.
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    // Read what user typed and trim whitespace from both ends.
    const QString cmdLine = ui->lineEdit->text().trimmed();

    // Guard: empty input.
    if (cmdLine.isEmpty()) {
        ui->statusBar->showMessage("Error: empty command.");
        return;
    }

    // IMPORTANT (Qt 6):
    // The old/deprecated overload QProcess::startDetached(const QString &command)
    // is NOT available in Qt 6.
    //
    // Instead, we must split the command line into:
    //   program + argument list
    //
    // QProcess::splitCommand handles quotes properly, e.g.:
    //   firefox "https://google.com"
    const QStringList parts = QProcess::splitCommand(cmdLine);

    // Guard: splitCommand may return empty list if input was weird.
    if (parts.isEmpty()) {
        ui->statusBar->showMessage("Error: invalid command.");
        return;
    }

    // First item is the program (executable).
    const QString program = parts.first();

    // Remaining items are arguments.
    const QStringList args = parts.mid(1);

    // Launch detached:
    // - The launched app will NOT be tied to this Qt app's lifetime.
    // - So we can safely quit after launching.
    //
    // startDetached returns true/false.
    // Note: it does not provide detailed error reasons, only success/failure.
    const bool ok = QProcess::startDetached(program, args);

    if (!ok) {
        // If launching failed, show a user-friendly error.
        // (This usually means: program not found / not executable / permission issue.)
        ui->statusBar->showMessage("Error: failed to launch.");
        return;
    }

    // On success, clear status and exit immediately (your original behavior).
    ui->statusBar->clearMessage();
    QApplication::quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // F1 shows program info.
    if (event->key() == Qt::Key_F1) {
        QMessageBox::about(
            this,
            "CRunner-QT v.3 QT6",
            "\n"
            "Author: JJ Posti <techtimejourney.net>"
            "\n\n"
            "This is free software, and you are welcome to redistribute it under\n"
            "GPL Version 2, June 1991. This program comes with ABSOLUTELY NO WARRANTY."
            "\n\n"
            "Default usage is:"
            "\n\n"
            "program or program argument. For example: firefox google.fi"
            "\n\n"
            "Shortkeys: ESC key quits the program."
            "\n\n"
            "Be mindful about what you type. CRunner-QT also accepts terminal commands, which can"
            " be dangerous if used incorrectly."
        );

        // Restore the small hint.
        ui->statusBar->showMessage("Press F1 for info.");
        return;
    }

    // ESC quits the program.
    if (event->key() == Qt::Key_Escape) {
        close();
        return;
    }

    // For all other keys, let the base class handle them.
    QMainWindow::keyPressEvent(event);
}
