#ifndef EC_BEDROOM_H
#define EC_BEDROOM_H

#include <QDialog>

namespace Ui {
class ec_bedroom;
}

class ec_bedroom : public QDialog
{
    Q_OBJECT

public:
    explicit ec_bedroom(QWidget *parent = 0);
    ~ec_bedroom();
public slots:
    void update_ecb_values();
private slots:
    void on_pushButton_released();

    void on_control_roomtemp_valueChanged(int value);

    void on_control_watertemp_valueChanged(int value);

    void on_control_highhumidity_valueChanged(int value);

    void on_control_lowhumidity_valueChanged(int value);

    void on_control_co2limit_valueChanged(int value);

    void on_control_backlightbrightness_valueChanged(int value);

    void on_control_ledtolerance_valueChanged(int value);

    void on_control_blight_valueChanged(int value);

    void on_control_roomtemp_sliderReleased();

private:
    Ui::ec_bedroom *ui;
       float get_databasevalues(int);
       float set_databasevalues(int, int);
       void checkuserinput(char,char,char, int, int);
};

#endif // EC_BEDROOM_H
