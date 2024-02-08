// simplesquarewindow.h
#ifndef SIMPLESQUAREWINDOW_H
#define SIMPLESQUAREWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>


class simpleSquareWindow : public QWidget
{
    Q_OBJECT
public:
    explicit simpleSquareWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void onSquareSelected();


private:
    int squareLength;
    int zoom = 800;
    bool shouldDrawSquare;
};

#endif // SIMPLESQUAREWINDOW_H
