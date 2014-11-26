#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportDialog(QWidget *parent = 0);
    ~ImportDialog();
    QString& importLocation();
    
private slots:
    void on_buttonBox_accepted();
    void on_BrowseButton_clicked();

private:
    Ui::ImportDialog *ui;
    QString mImportLocation;
};

#endif // IMPORTDIALOG_H
