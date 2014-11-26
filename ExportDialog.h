#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportDialog(QWidget *parent = 0);
    QString exportLocation();
    void setDefaultFileName(const QString&);
    ~ExportDialog();

    private slots:
        void on_buttonBox_accepted();
        void on_browseButton_clicked();

private:
    Ui::ExportDialog *ui;
    QString mExportLocation;
    QString mDefaultFileName;
};
#endif // EXPORTDIALOG_H
