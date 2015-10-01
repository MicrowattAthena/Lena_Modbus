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
    void on_pushButton_2_released();

    void on_horizontalSlider_2_sliderReleased();

private:
    Ui::EC_Saloon *ui;
};


#endif // EC_SALOON_H
