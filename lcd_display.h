#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <QDialog>

namespace Ui {
class lcd_display;
}

class lcd_display : public QDialog
{
    Q_OBJECT

public:
    explicit lcd_display(QWidget *parent = 0);
    ~lcd_display();

private slots:
    void on_pushButton_released();

private:
    Ui::lcd_display *ui;
};

#endif // LCD_DISPLAY_H
