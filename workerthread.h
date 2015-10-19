#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QtCore>


class workerthread :public QThread
{
    Q_OBJECT
public:
    workerthread();
    void run();

};

#endif // WORKERTHREAD_H
