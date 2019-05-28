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

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    QStringList named_filters_ = {"*.txt", "*.markdown"};

    QSharedPointer<Ui::Folio> ui_;
    QSharedPointer<QFileSystemModel> model_ptr_;
};

#endif // FOLIO_H
