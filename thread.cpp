#include "thread.h"
#include <QThread>
#include <QDebug>
#include <QtCore>

Thread::Thread()
{

}

void Thread::run(QString a , QString b){
    qDebug() << "Running";
}
