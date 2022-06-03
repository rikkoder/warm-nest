#include "mainwindow.h"
#include "loginprompt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginPrompt lp;
    lp.show();

    return a.exec();
}
