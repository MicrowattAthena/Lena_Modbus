#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QtCore>


class workerthread :public QThread
{
public:
    workerthread();
    void run();
signals:

public slots:
};

#endif // WORKERTHREAD_H
