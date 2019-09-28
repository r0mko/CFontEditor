#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fontselector.h"
#include "glyph.h"
#include <QTextCodec>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    qDebug() << QTextCodec::availableCodecs();
    
    qmlRegisterType<FontSelector>("FontEditor", 1, 0, "FontSelector");
    qmlRegisterType<Glyph>("FontEditor", 1, 0, "Glyph");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    
    return app.exec();
}
    
