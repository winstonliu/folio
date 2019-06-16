#include "settings.h"
#include "ui_settings.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

Settings::Settings(
        QString root_folder_path,
        QString executable_path,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->rootFolderEntry->setText(root_folder_path);
    ui->executablePathEntry->setText(executable_path);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_change_rootFolder_clicked()
{
    QString root_folder = QFileDialog::getExistingDirectory(
            this,
            tr("Select Root Folder"),
            QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!root_folder.isNull()) {
        ui->rootFolderEntry->setText(root_folder);
    }
}

void Settings::on_change_executablePath_clicked()
{
    QString executable_path = QFileDialog::getOpenFileName(
            this,
            tr("Select Text Editor"),
            QStandardPaths::writableLocation(
                QStandardPaths::ApplicationsLocation),
            tr("Executables (*.bat *.exe)"));

    if (!executable_path.isNull()) {
        ui->executablePathEntry->setText(executable_path);
    }
}

void Settings::on_rootFolderEntry_textChanged(const QString &arg1)
{
    root_folder_path_ = arg1;
}


void Settings::on_executablePathEntry_textChanged(const QString &arg1)
{
    executable_path_ = arg1;
}

void Settings::on_buttonBox_accepted()
{
    // Can be empty strings as well
    bool executable_exists = (
                QFileInfo(executable_path_).isExecutable()
                || executable_path_.isEmpty());
    bool root_dir_exists = (
                QFileInfo(root_folder_path_).isDir()
                || root_folder_path_.isEmpty());

    if (executable_exists && root_dir_exists) {
        // Alert listeners to updated paths
        this->accept();
    } else {
        QString error_message;
        if (executable_exists && !root_dir_exists) {
            error_message = "Root folder path is invalid!";
        } else if (!executable_exists && root_dir_exists) {
            error_message = "Executable path is invalid!";
        } else {
            error_message = "Both paths were not found!";
        }

        // Pop up an error message
        QMessageBox message_box;
        message_box.critical(this, "Error", error_message);
    }
}
