#include "folio.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Temporary until I get around to adding a config file
    Folio folio("C:/Users/Winston Liu/Dropbox/Writing");

    // Path is temporary until I add a config file
    folio.setCommand("C:/Program Files (x86)/Vim/vim80/gvim.exe");

    folio.show();

    return a.exec();
}
