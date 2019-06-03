#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(
            QString root_folder_path,
            QString executable_path,
            QWidget *parent = nullptr);
    ~Settings();

    QString getRootFolderPath() {
        return root_folder_path_;
    }

    QString getExecutablePath() {
        return executable_path_;
    }

private slots:
    void on_change_rootFolder_clicked();

    void on_change_executablePath_clicked();

    void on_rootFolderEntry_textChanged(const QString &arg1);

    void on_executablePathEntry_textChanged(const QString &arg1);
    /* Check that the paths are valid before acceptance */
    void on_buttonBox_accepted();

private:
    Ui::Settings *ui;

    QString root_folder_path_ = "";
    QString executable_path_ = "";
};

#endif // SETTINGS_H
