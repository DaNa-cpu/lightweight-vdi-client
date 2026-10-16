#include <QApplication>
#include <QDebug>

#include "MainWindow.h"
#include "ConfigLoader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const QVector<VdiSession> sessions =
        ConfigLoader::loadSessions("config/sessions.json");

    if (sessions.isEmpty()) {
        qWarning() << "Nu s-au incarcat sesiuni din fisierul JSON.";
    }

    MainWindow window(sessions);
    window.show();

    return app.exec();
}

