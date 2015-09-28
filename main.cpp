#include "widget.h"
#include "workerthread.h"
#include <QApplication>
#include <QTimer>
#include <QtCore/QCoreApplication>
#include "guihandler.h"


int main(int argc, char *argv[])
{

    // Create and Show Widget
    QApplication a(argc, argv);


    guihandler *handler = new guihandler();
    handler->initialise();


    Widget w;
    w.show();
    workerthread mThread;
    mThread.start();
    return   a.exec();
}


