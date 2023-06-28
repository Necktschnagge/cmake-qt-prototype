#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap pixmap(":/Resources/Images/splashscreen.png");
    QSplashScreen splashscreen(pixmap);

    splashscreen.show();
    QTimer::singleShot(WAIT_NORMAL, &splashscreen, SLOT(close()));
    QTimer::singleShot(WAIT_NORMAL, &w, SLOT(show()));

    return a.exec();
}
