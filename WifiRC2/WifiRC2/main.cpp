#include <QApplication>
#include "fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindows fenetre;
    fenetre.show();

    return app.exec();
}
