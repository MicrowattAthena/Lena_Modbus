#ifndef EC_SALOON_H
#define EC_SALOON_H

#include <QDialog>
namespace Ui {
class EC_Saloon;
}

class EC_Saloon : public QDialog
{
    Q_OBJECT

public:
    explicit EC_Saloon(QWidget *parent = 0);
    ~EC_Saloon();
public slots:
    void update_ecs_values();
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

    void on_control_roomtemp_sliderMoved(int position);

private:
    Ui::EC_Saloon *ui;
    float get_databasevalues(int);
    float set_databasevalues(int,int);
};


#endif // EC_SALOON_H
