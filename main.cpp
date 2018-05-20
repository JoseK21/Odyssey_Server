#include "odyssey_s.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Odyssey_S w;    
    w.show();

    return a.exec();
}

