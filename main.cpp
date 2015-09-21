#include "widget.h"
#include "workerthread.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    // Create and Show Widget
    QApplication a(argc, argv);
    Widget w;
    w.show();
    workerthread mThread;
    mThread.start();

    return   a.exec();
}
