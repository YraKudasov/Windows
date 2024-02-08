#include "simplesquarewindow.h"
#include <QPainter>
#include <QWheelEvent>

simpleSquareWindow::simpleSquareWindow(QWidget *parent) : QWidget(parent)
{
    squareLength = 0;
    shouldDrawSquare = false;
}

void simpleSquareWindow::paintEvent(QPaintEvent *event)
{
     QWidget::paintEvent(event);
    if (shouldDrawSquare) { // Проверка флага для отрисовки квадрата
        QPainter painter(this);

        int x = (width() - zoom) / 2; // Вычисление координаты x для центрирования
        int y = (height() - zoom) / 2; // Вычисление координаты y для центрирования
        painter.drawRect(x, y, zoom, zoom); // Рисование квадрата с учетом текущего масштаба

        QLineF height[7] = { QLineF(x+zoom, y, x+(zoom+40), y), QLineF(x+zoom, y+zoom, x+(zoom+40), y+zoom),
                             QLineF(x+(zoom+20), y, x+(zoom+20), y+zoom), QLineF(x+(zoom+20), y, x+(zoom+15), y+10), QLineF(x+(zoom+20), y, x+(zoom+25), y+10),
                             QLineF(x+(zoom+20), y+zoom, x+(zoom+15), y+(zoom-10)), QLineF(x+(zoom+20), y+zoom, x+(zoom+25), y+(zoom-10))};
        painter.drawLines(height, 7);

        QLineF width[7] = { QLineF(x, y+zoom, x, y+(zoom+40)), QLineF(x+zoom, y+zoom, x+zoom, y+(zoom+40)),
                             QLineF(x, y+(zoom+20), x+zoom, y+(zoom+20)), QLineF(x, y+(zoom+20), x+10, y+(zoom+15)), QLineF(x, y+(zoom+20), x+10, y+(zoom+25)),
                             QLineF(x+zoom, y+(zoom+20), x+(zoom-10), y+(zoom+25)), QLineF(x+zoom, y+(zoom+20), x+(zoom-10), y+(zoom+15))};
        painter.drawLines(width, 7);

        // Добавление высоты квадрата
        QString heightStr = QString("%1").arg(squareLength);
        painter.save(); // Сохранение текущего состояния painter
        painter.translate(x + (zoom+30), y + (zoom / 2)); // Установка начальной точки для текста
        painter.rotate(90); // Поворот текста на 90 градусов против часовой стрелки
        painter.drawText(0, 0, heightStr); // Написать высоту квадрата
        painter.restore(); // Восстановление предыдущего состояния painter

        // Добавление ширины квадрата
        QString widthStr = QString("%1").arg(squareLength);
        painter.drawText(x + (zoom/2), y + (zoom+40), widthStr);


        painter.end();

    }
}

void simpleSquareWindow::onSquareSelected() {
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

        shouldDrawSquare = true; // Установка флага для отрисовки квадрата
        update(); // Вызов метода перерисовки окна (paintEvent)

        // Закрытие диалогового окна
        dialog.accept();
    });

    // Отображение диалогового окна
    dialog.exec();
}

void simpleSquareWindow::wheelEvent(QWheelEvent *event) {
    int delta = event->angleDelta().y(); // Получение значения вращения колесика мыши

    // Изменение масштаба изображения в зависимости от вращения колесика мыши
    if (delta > 0) {
        // Увеличение масштаба
        zoom += 50; // Примерное увеличение длины квадрата на 10
    } else {
        // Уменьшение масштаба
        zoom -= 50; // Примерное уменьшение длины квадрата на 10
    }

    update(); // Перерисовка окна с новым масштабом
}

