#include "folio.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Folio folio("C:/Users/Winston Liu/Dropbox/Writing");
    folio.show();

    return a.exec();
}
