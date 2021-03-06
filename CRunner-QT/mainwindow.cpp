#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("F1 for info.");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errors()
{ui->statusBar->showMessage("Error. No such program found.");}

void MainWindow::starting(){
    ui->statusBar->showMessage("");
    run_command->waitForStarted(-1);
    QApplication::quit();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString x; // Using QString since it has utf-8 support --> and because we want info from the Qt ui.
    x=ui->lineEdit->text(); //Get text from the line edit.


//Declare the actual command for the run.
//Using QProcess here. It is friendly to our cause and spawns resouces nicely, unlike the system command.
   run_command = new QProcess(this);

// Start the QProcess.
   run_command->startDetached(x);
    run_command->start(x);
    connect(run_command,SIGNAL(error(QProcess::ProcessError)),this,SLOT(errors()));
    connect(run_command,SIGNAL(started()),this,SLOT(starting()));

//Security note. Be mindful about what you write. Crunner-QT can also execute terminal commands because QProcess sets
// shell to equal true. Be careful NEVER to write something like: rm -r some_location, unless you now exactly what you
// are doing.

 }

void MainWindow::keyPressEvent(QKeyEvent *events){

    if(events->key()==Qt::Key_F1){

        messagebox=new QMessageBox(this);
        messagebox->about(this,
                                "CRunner-QT v.2",

                                "\n"

                                "Author: JJ Posti <techtimejourney.net>"

                                "\n"
                                "\n"

                               "This is free software, and you are welcome to redistribute it under" "\n"
                               "GPL Version 2, June 1991. This program comes with ABSOLUTELY NO WARRANTY."

                                "\n"
                                "\n"

                                "Default usage is:"

                                "\n"
                                "\n"

                                "program or program argument. For example: firefox google.fi"

                                "\n"
                                "\n"

                                "Shortkeys:ESC key quits the program."

                                "\n"
                                "\n"

                          "Be mindful about what you type. CRunner-QT also accepts terminal commands, which can"
                              " be dangerous if used incorrectly.");

                               //Delete messagebox from the heap.
                               delete messagebox;
                               //Return our standard message to the statusbar.
                               ui->statusBar->showMessage("Press F1 for info.");

          }
//Esc event == Quit the program
    else if(events->key()==Qt::Key_Escape){
        this->close();    
    }
};
