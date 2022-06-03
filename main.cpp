#include "mainwindow.h"
#include "loginprompt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // stop app from closing when closing another window (child)
//    a.setQuitOnLastWindowClosed(false);

    LoginPrompt lp;
//    lp.setAttribute(Qt::WA_DeleteOnClose);
    lp.show();

    return a.exec();
}
