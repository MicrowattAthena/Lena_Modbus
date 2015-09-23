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

private slots:
    void on_pushButton_released();

private:
    Ui::ec_bedroom *ui;
};

#endif // EC_BEDROOM_H
