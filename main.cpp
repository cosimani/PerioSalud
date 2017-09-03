#include "login.h"
#include <QApplication>

#include <QQuickView>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QDebug>
#include "squircle.h"
#include "database.hpp"

#include <QTimer>
#include <QFontDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Esta funete se llama "BethHand"
//    QFontDatabase::addApplicationFont(":/resources/fuentes/Bethhrg_.ttf");

    // Se llama "Avant que..."
//    QFontDatabase::addApplicationFont(":/resources/fuentes/album-avantquelombre.ttf");

    // Angelina
    QFontDatabase::addApplicationFont(":/resources/fuentes/angelina.TTF");

//    QFontDatabase baseFuentes;
//    qDebug() << baseFuentes.families();

    Login * login = NULL;

    QQuickView * view = NULL;

//    Database::getInstance()->borrarTablas();

    switch( Database::getInstance()->checkLogin() )
    {
    case 0:
    //        QTimer::singleShot(30000, &application, SLOT(quit()));
        QTimer::singleShot(20000, &a, SLOT(quit()));  // Emmi

        qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

        view = new QQuickView;
        view->setResizeMode(QQuickView::SizeRootObjectToView);
        view->setSource(QUrl("qrc:///openglunderqml.qml"));
        view->show();

        break;
    case -1:
        qDebug() << "Si se devolvio un -1 es porque no anda la base. Seguimos y que sea lo que Dios quiera.";

    case 1:
        qDebug() << "Ya entro antes";

        login = new Login();

        login->show();

        break;

    default:

        break;
    }


    return a.exec();
}


