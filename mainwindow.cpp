#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QMenuBar * menubar = this->menuBar( ); // adds/returns the menu bar
    QMenu * menu = menubar->addMenu(tr("&File")); // adds a pulldown menu
    // new.png is specified in a resource file (see later)
    QAction * action = new QAction( QIcon(":images/open.png"), tr("&Open..."), this );
    QAction * action1 = new QAction( QIcon(":images/save.png"), tr("&Save..."), this );
    QAction * action2 = new QAction( QIcon(":images/quit.png"), tr("&QQuit..."), this );
    action->setShortcut( tr("Ctrl+N") ); // hot key
    action->setToolTip( tr("Open file") ); // tool tip
    action->setStatusTip( tr("Open file") ); // info on status bar

    action1->setShortcut( tr("Ctrl+S") ); // hot key
    action1->setToolTip( tr("Save file") ); // tool tip
    action1->setStatusTip( tr("Save file") ); // info on status bar

    action2->setShortcut( tr("Ctrl+Q") ); // hot key
    action2->setToolTip( tr("Quit file") ); // tool tip
    action2->setStatusTip( tr("Quit file") ); // info on status bar


    menu->addAction(action); // adds the action to the menu
    menu->addAction(action1);
    menu->addAction(action2);


//    QTextEdit * text = new QTextEdit(this);
    text = new QTextEdit(this);
    this->setCentralWidget(text);

    connect(action, SIGNAL(triggered( )), this, SLOT(openFile( ))); // connection
//    connect(action, &QAction::triggered,
//            [=]()
//            {
//                QString fileName =
//                QFileDialog::getOpenFileName(this,
//                tr("Open Text"), // title
//                "/Users/weixiang/QtWorkSpace", // directory
//                tr("Text Files (*.txt *.doc *.docx)") // filter
//                );

//                QFile file(fileName);
//                QString line;

//                if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
//                    QTextStream in(&file);
//                    while (!in.atEnd()) {
//                        QString line = in.readLine();
//                        text->setHtml(line);
//                    }

//                }
//            }

//            ); // connection

//    connect(action1, &QAction::triggered,
//            [=]()
//            {
//                QString fileName =
//                QFileDialog::getSaveFileName(this,
//                tr("Save File"), // title
//                "../", // directory
//                tr("Text Files (*.txt *.doc *.docx)") // filter
//                );

//                QFile file(fileName);


//                if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
//                    QString str = text->toPlainText();
//                    file.write(str.toUtf8());

//                }

//                file.close();
//            }

//            ); // connection

    connect(action1, SIGNAL(triggered( )), this, SLOT(saveFile( ))); // connection
    connect(action2, SIGNAL(triggered( )), this, SLOT(quitApp( ))); // connection


    QToolBar * toolbar = this->addToolBar( tr("File") );
    toolbar->addAction(action);
    toolbar->addAction(action1);
    toolbar->addAction(action2);


    //QStatusBar *statusbar = this->statusBar();


//    QTextEdit * text = new QTextEdit(this);
//    this->setCentralWidget(text);


    //ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow ::openFile(){
    QString fileName =
            QFileDialog::getOpenFileName(this,
            tr("Open Text"), // title
            "/Users/weixiang/QtWorkSpace", // directory
            tr("Text Files (*.txt *.doc *.docx)") // filter
            );

    QFile file(fileName);
    QString line;


    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()) {
                QString line = in.readLine();
                //ui->text->setHtml(line);
                text->setHtml(line);
            }
    }


    file.close();

}
void MainWindow ::saveFile(){
    QString fileName =
            QFileDialog::getSaveFileName(this,
            tr("Save Text"), // title
            "/Users/weixiang/QtWorkSpace", // directory
            tr("Text Files (*.txt)") // filter
            );

    QFile file(fileName);

    // Trying to open in WriteOnly and Text mode
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
//        QTextStream out(&fileName);
//        out << text->toPlainText();
        QString str = text->toPlainText();
        file.write(str.toUtf8());
    }


    file.close();
}

void MainWindow ::quitApp(){
    QMessageBox msgBox;
    msgBox.setText("Really want to quit?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes );
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.exec();

    if(QMessageBox::Yes){
        QApplication::quit();
    }

}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

