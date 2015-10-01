#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QObject>
class guihandler : public QObject
{
    Q_OBJECT
public:
    guihandler();

signals:
    void confirmupdate();
    void requestupdate();
public slots:
    void updateGUI();
    void initialise();
};

#endif // GUIHANDLER_H
