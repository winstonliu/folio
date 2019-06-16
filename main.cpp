#include "folio.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QResource>
#include <QStandardPaths>
#include <QTreeView>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app(argc, argv);

    // Set window icon
    app.setWindowIcon(QIcon(":/default.png"));

    // Set configuration information
    QCoreApplication::setOrganizationName("winstonliu");
    QCoreApplication::setOrganizationDomain("github.com/winstonliu/folio");
    QCoreApplication::setApplicationName("folio");

    Folio folio;
    folio.show();

    return app.exec();
}
