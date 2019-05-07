#include "ui/winmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    WINMain w;
//    w.show();
    w.showFullScreen();

    return prog.exec();
}
