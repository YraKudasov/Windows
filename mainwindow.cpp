#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simplesquarewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    simpleSquareWindow* squareWindow = new simpleSquareWindow(this);
    setCentralWidget(squareWindow);

    // Создание всплывающего меню
       QMenu* popupMenu = new QMenu(this);
       QAction* squareAction = popupMenu->addAction("Квадрат");
       QAction* rectangleAction = popupMenu->addAction("Прямоугольник");
       QAction* triangleAction = popupMenu->addAction("Треугольник");
       QAction* circleAction = popupMenu->addAction("Круг");
       QAction* trapezoidAction = popupMenu->addAction("Трапеция");

       // Подключение слотов для обработки выбора пунктов меню
     connect(squareAction, &QAction::triggered, squareWindow, &simpleSquareWindow::onSquareSelected);
       connect(rectangleAction, &QAction::triggered, this, &MainWindow::onRectangleSelected);
       connect(triangleAction, &QAction::triggered, this, &MainWindow::onTriangleSelected);
       connect(circleAction, &QAction::triggered, this, &MainWindow::onCircleSelected);
       connect(trapezoidAction, &QAction::triggered, this, &MainWindow::onTrapezoidSelected);

       // Установка всплывающего меню для виджета
       squareWindow->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(squareWindow, &QWidget::customContextMenuRequested, this, [=](const QPoint &pos){
           popupMenu->exec(squareWindow->mapToGlobal(pos));
       });

}


void MainWindow::onRectangleSelected() {
    // Обработка выбора прямоугольника
}

void MainWindow::onTriangleSelected() {
    // Обработка выбора треугольника
}

void MainWindow::onCircleSelected() {
    // Обработка выбора круга
}

void MainWindow::onTrapezoidSelected() {
    // Обработка выбора трапеции
}



MainWindow::~MainWindow()
{
    delete ui;
}
