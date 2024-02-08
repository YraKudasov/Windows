#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#include <QWheelEvent>
#include "simplesquarewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;


protected:


private slots:
    void onRectangleSelected();
    void onTriangleSelected();
    void onCircleSelected();
    void onTrapezoidSelected();
};

#endif // MAINWINDOW_H
