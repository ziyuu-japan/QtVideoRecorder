#include "mainwindow.h"

#include <QApplication>
#include <graphicsscene.h>
#include <widget.h>
#include <camerastartwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow  main_window;
    main_window.show();

    return a.exec();
}
