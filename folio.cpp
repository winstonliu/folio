#include "folio.h"
#include "ui_folio.h"

#include <QDebug>
#include <QProcess>

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

bool Folio::checkValidity(const QFileInfo &target) {
    // Check if file is filtered
    bool is_filtered = target.absoluteDir().entryList(named_filters_).contains(target.fileName());
    return (is_filtered && target.exists() && target.isFile() && target.isReadable());
}

void Folio::runEditor(const QFileInfo& target) {
    // Start a detached process
    QProcess process;
    process.setWorkingDirectory(target.absoluteDir().absolutePath());
    process.setProgram(command_);
    process.setArguments({target.absoluteFilePath()});
    process.startDetached();
}

void Folio::on_treeView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // Check file validity
        QFileInfo target = model_ptr_->fileInfo(index);
        if (!checkValidity((target))) {
            return;
        }

        // Clear text
        ui_->textEdit->clear();

        // Read file
        QFile read_file(target.absoluteFilePath());
        if (!read_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
        }

        // Print
        QTextStream in(&read_file);
        while (!in.atEnd()) {
            ui_->textEdit->append(in.readLine());
        }
    }
}

void Folio::on_treeView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QFileInfo target = model_ptr_->fileInfo(index);
        if (!checkValidity(target)) {
            return;
        }

        // Opens editor
        runEditor(target);
    }
}
