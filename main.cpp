/*TO DO
 * If modbus not found/working - retry, then throw error. Do not allow program to run
 * Manage Flags for Thresholds etc.
 * Manage queue for GUI inputs
 * Manage GUI design
 */
#include "widget.h"
#include "workerthread.h"
#include <QApplication>
#include <QTimer>
#include <QtCore/QCoreApplication>
#include "guihandler.h"
#include <QWSServer>
#include "calibration.h"
#include "scribblewidget.h"

guihandler *handler = new guihandler;

int main(int argc, char *argv[])
{

    // Create and Show Widget
    QApplication a(argc, argv);


    Calibration cal;
    cal.exec();

    qWarning() << "Initialising";

    handler->initialise();
    Widget w;
    w.show();
    workerthread mThread;
    mThread.start();


    return   a.exec();
}


