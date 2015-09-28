#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

#include <QDialog>

namespace Ui {
class engine_display;
}

class engine_display : public QDialog
{
    Q_OBJECT

public:
    explicit engine_display(QWidget *parent = 0);
    ~engine_display();

private slots:
    void on_pushButton_released();

private:
    Ui::engine_display *ui;
};

#endif // ENGINE_DISPLAY_H
