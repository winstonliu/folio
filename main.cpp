#include "folio.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QResource>
#include <QStandardPaths>
#include <QSettings>
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
    QSettings settings;

    // Temporary until I get around to adding a config file
    Folio folio("C:/Users/Winston Liu/Dropbox/Writing");
    // Path is temporary until I add a config file
    folio.setCommand("C:/Program Files (x86)/Vim/vim80/gvim.exe");
    folio.show();

    return app.exec();
}
