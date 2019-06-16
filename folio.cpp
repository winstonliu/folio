#include "folio.h"
#include "settings.h"
#include "ui_folio.h"

#include <QDebug>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>

Folio::Folio(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::Folio)
{
    ui_->setupUi(this);

    // Get settings
    QSettings qset;
    QString root_path = qset.value(config["rootFolderPath"], "").toString();
    QString exe_path = qset.value(config["executablePath"], "").toString();
    restoreGeometry(qset.value(config["geometry"]).toByteArray());
    restoreState(qset.value(config["state"]).toByteArray());

    setWindowTitle(tr("Folio - for Organized Writers"));

    if (!exe_path.isEmpty()) {
        setCommand(exe_path);
    }

    // Setup tree view
    model_ptr_ = QSharedPointer<QFileSystemModel>::create();
    model_ptr_->setRootPath("");
    model_ptr_->setNameFilters(named_filters_);

    auto* tree_view = ui_->treeView;

    tree_view->setModel(model_ptr_.get());
    tree_view->setRootIndex(model_ptr_->index(root_path));
    tree_view->setIndentation(20);
    tree_view->setWindowTitle(QObject::tr("Dir View"));

    // Set the tree view header resizing settings
    tree_view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

bool Folio::checkValidity(const QFileInfo &target) {
    // Check if file is filtered
    bool is_filtered = target.absoluteDir()
            .entryList(named_filters_).contains(target.fileName());
    return (is_filtered && target.exists()
            && target.isFile() && target.isReadable());
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

void Folio::on_actionExit_triggered()
{
   // Close this widget
    this->close();
}

void Folio::on_actionSettings_triggered()
{
    // Create modal settings window
    Settings settings(extractRootPath(), extractCommandPath(), this);
    if (settings.exec() == QDialog::Accepted) {
        // Update tree view
        ui_->treeView->setRootIndex(
                    model_ptr_->index(settings.getRootFolderPath()));
        // Update command
        setCommand(settings.getExecutablePath());
    }
}

QString Folio::extractRootPath() {
    return model_ptr_->filePath(ui_->treeView->rootIndex());
}

void Folio::closeEvent(QCloseEvent *event) {
    // Save settings
    QSettings qset;
    qset.setValue(config["rootFolderPath"], extractRootPath());
    qset.setValue(config["executablePath"], extractCommandPath());
    qset.setValue(config["geometry"], saveGeometry());
    qset.setValue(config["state"], saveState());
    qset.sync();

    QWidget::closeEvent(event);
}
