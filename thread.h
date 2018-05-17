#ifndef THREAD_H
#define THREAD_H
#include <QtCore>
#include <QThread>
class Thread : public QThread
{
public:
    Thread();
    void run(QString ,QString );
};

#endif // THREAD_H
