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
public slots:
    void update_engine_values();
private slots:
    void on_pushButton_released();

    void on_control_batterycurrentfsd_valueChanged(int value);

    void on_control_V_enginethresh_1_valueChanged(int value);

    void on_control_V_Enginethresh_2_valueChanged(int value);

    void on_Control_A_EngineThresh_valueChanged(int value);

    void on_control_enginemode_valueChanged(int value);

    void on_control_heatingmode_valueChanged(int value);

    void on_control_heatingthresh_valueChanged(int value);

    void on_chk_Input1_stateChanged(int arg1);

    void on_chk_input2_stateChanged(int arg1);

    void on_chk_input3_stateChanged(int arg1);

    void on_chk_input4_stateChanged(int arg1);

    void on_chk_input5_stateChanged(int arg1);

    void on_chk_input6_stateChanged(int arg1);

    void on_chk_input7_stateChanged(int arg1);


    void on_chk_output1_stateChanged(int arg1);

    void on_chk_output2_stateChanged(int arg1);

    void on_chk_output3_stateChanged(int arg1);

    void on_chk_output4_stateChanged(int arg1);

    void on_chk_output5_stateChanged(int arg1);

    void on_chk_output6_stateChanged(int arg1);

    void on_chk_output7_stateChanged(int arg1);

    void on_chk_output8_stateChanged(int arg1);

private:
    Ui::engine_display *ui;
    float get_databasevalues(int,char);
    void checkuserinput(char,char,char, int, int);
};

#endif // ENGINE_DISPLAY_H
