#include "folio.h"
#include "ui_folio.h"

#include <QDebug>

Folio::Folio(QString root_path, QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::Folio)
{
    ui_->setupUi(this);

    // Setup tree view
    model_ptr_ = QSharedPointer<QFileSystemModel>::create();
    model_ptr_->setRootPath(root_path);
    model_ptr_->setNameFilters(named_filters_);
    ui_->treeView->setModel(model_ptr_.get());
    ui_->treeView->setRootIndex(model_ptr_->index(root_path));
    ui_->treeView->setIndentation(20);
    ui_->treeView->setWindowTitle(QObject::tr("Dir View"));
}

void Folio::on_treeView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // Check file validity
        QFileInfo target = model_ptr_->fileInfo(index);
        // Check if file is filtered
        bool is_filtered = target.absoluteDir().entryList(named_filters_).contains(target.fileName());
        if (is_filtered && target.exists() && target.isFile() && target.isReadable()) {
            ui_->textEdit->clear();

            // Read file
            QFile read_file(target.absoluteFilePath());
            if (!read_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return;
            }

            // Print contents to text edit
            QTextStream in(&read_file);
            while (!in.atEnd()) {
                ui_->textEdit->append(in.readLine());
            }
        }
    }
}
