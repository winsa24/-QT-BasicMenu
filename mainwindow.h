#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void openFile();
    void saveFile();
    void quitApp();


private:
    Ui::MainWindow *ui;
    QTextEdit * text;
};

//class OpFile : public QObject{
//    Q_OBJECT

//public slots:
//    void openFile();
//    void saveFile();
//    void quitFile();
//};

#endif // MAINWINDOW_H
