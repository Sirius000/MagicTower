#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include <QMainWindow>
#include <QtCore>
#include <QTimer>
#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <cstring>
#include <QPushButton>
#include <QLCDNumber>
#include <QPixmap>
#include <QGuiApplication>
#include <QFrame>
#include <QKeyEvent>
#include <QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void virtual keyPressEvent(QKeyEvent *e);
    int battle(int b,int c,int d,int e,int f,int g);
    void setplayer();
    void setstatus();
    void settable1();
    void settable2();
    void settable3();
    void settable4();
    void settable5();
    void settable6();
    void settable7();
    void settable8();
    void settable9();
    void settable10();
    ~MainWindow();

public slots:
    void npcchoice00();
    void npcchoice01();
    void npcchoice02();
    void npcchoice03();
    void npcchoice10();
    void npcchoice11();
    void npcchoice12();
    void npcchoice20();
    void npcchoice21();
    void npcchoice22();
    void npcchoice23();
    void npcchoice30();
    void npcchoice31();
    void npcchoice40();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
