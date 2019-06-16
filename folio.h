#ifndef FOLIO_H
#define FOLIO_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class Folio;
}

class Folio : public QMainWindow
{
    Q_OBJECT

public:
    // Create a configuration map
    const QMap<QString, QString> config{
        {"rootFolderPath", "config/rootFolderPath"},
        {"executablePath", "config/executablePath"},
        {"geometry", "window/geometry"},
        {"state", "window/state"},
    };

    explicit Folio(QWidget *parent = nullptr);
    ~Folio() {}

    void setCommand(const QString& command) {
        command_ = command;
    }

protected:
    QString command_ = "";

    bool virtual checkValidity(const QFileInfo& target);
    void virtual runEditor(const QFileInfo& target);

    void closeEvent(QCloseEvent* event);

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionExit_triggered();

    void on_actionSettings_triggered();

private:
    QStringList named_filters_ = {"*.txt", "*.markdown"};

    // QT Designer exepects a raw pointer
    Ui::Folio *ui_;
    QSharedPointer<QFileSystemModel> model_ptr_;

    QString extractRootPath();

    QString extractCommandPath() {
        return command_;
    }
};

#endif // FOLIO_H
