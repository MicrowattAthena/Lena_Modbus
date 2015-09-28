#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_btn_ECBedroom_released();

    void on_btn_ECSaloon_released();

    void on_btn_LCD_released();

    void on_btn_Engine_released();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
