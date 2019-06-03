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
    explicit Folio(QString root_path, QWidget *parent = nullptr);
    ~Folio() {}

    void setCommand(const QString& command) {
        command_set_ = true;
        command_ = command;
    }

protected:
    bool command_set_ = false;
    QString command_;

    bool virtual checkValidity(const QFileInfo& target);
    void virtual runEditor(const QFileInfo& target);

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
};

#endif // FOLIO_H
