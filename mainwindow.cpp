#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Создание всплывающего меню
       QMenu* popupMenu = new QMenu(this);
       QAction* squareAction = popupMenu->addAction("Квадрат");
       QAction* rectangleAction = popupMenu->addAction("Прямоугольник");
       QAction* triangleAction = popupMenu->addAction("Треугольник");
       QAction* circleAction = popupMenu->addAction("Круг");
       QAction* trapezoidAction = popupMenu->addAction("Трапеция");

       // Подключение слотов для обработки выбора пунктов меню
       connect(squareAction, &QAction::triggered, this, &MainWindow::onSquareSelected);
       connect(rectangleAction, &QAction::triggered, this, &MainWindow::onRectangleSelected);
       connect(triangleAction, &QAction::triggered, this, &MainWindow::onTriangleSelected);
       connect(circleAction, &QAction::triggered, this, &MainWindow::onCircleSelected);
       connect(trapezoidAction, &QAction::triggered, this, &MainWindow::onTrapezoidSelected);

       // Установка всплывающего меню для виджета
       ui->centralwidget->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(ui->centralwidget, &QWidget::customContextMenuRequested, this, [=](const QPoint &pos){
           popupMenu->exec(ui->centralwidget->mapToGlobal(pos));
       });

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    int side = qMin(squareLength, squareLength); // Определение минимальной стороны окна
        int x = (width() - side) / 2; // Вычисление координаты x для центрирования
        int y = (height() - side) / 2; // Вычисление координаты y для центрирования
        painter.drawRect(x, y, side, side); // Рисование прямоугольника по центру

    painter.end();
}

void MainWindow::onSquareSelected() {
    // Создание диалогового окна для ввода данных квадрата
    QDialog dialog(this);
    QFormLayout formLayout(&dialog);

    // Создание QLineEdit для ввода длины и установка валидатора
    QLineEdit lengthLineEdit(&dialog);
    QIntValidator* lengthValidator = new QIntValidator(&dialog);
    lengthLineEdit.setValidator(lengthValidator);
    formLayout.addRow("Длина(мм):", &lengthLineEdit);

    // Добавление кнопки "Рисовать" и связывание сигнала clicked с соответствующим слотом
    QPushButton* drawButton = new QPushButton("Рисовать", &dialog);
    formLayout.addRow(drawButton);

    // Создание лямбда-функции для обработки нажатия кнопки "Рисовать"
    connect(drawButton, &QPushButton::clicked, [&]() {
        // Получение введенных значений
        QString lengthText = lengthLineEdit.text();
        int length = lengthText.toInt();

        // Вызов метода перерисовки окна с передачей длины квадрата
        squareLength = length;
        update(); // Вызов метода перерисовки окна (paintEvent)

        // Закрытие диалогового окна
        dialog.accept();
    });

    // Отображение диалогового окна
    dialog.exec();
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
