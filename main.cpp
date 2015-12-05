#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/mytrayicon.ico"));
    MainWindow w;
    // We actually do not need this default window to show up ...
    //w.show();

    return a.exec();
}
