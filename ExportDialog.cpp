#include "ExportDialog.h"
#include "ui_ExportDialog.h"

#include <QButtonGroup>
#include <QFileDialog>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    ui->browseButton->setFocus(Qt::OtherFocusReason);
    setWindowTitle(tr("Export Contact(s)"));
    setModal(true);

    mExportLocation="";
    mDefaultFileName="";
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_buttonBox_accepted()
{
    if(mExportLocation.isEmpty())
        return;
    else
    {
        mExportLocation = mExportLocation/*.append(".vcf")*/;
        ui->exportLocationLineEdit->clear();
        this->hide();
    }
}

void ExportDialog::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export Location"),mDefaultFileName,
                                                    tr("vCard Format (*.vcf);;All Files (*)"));
    if(!fileName.isEmpty())
    {
        mExportLocation = fileName;
        ui->exportLocationLineEdit->setText(fileName/*.append(".vcf")*/);
    }
    return;
}


QString ExportDialog::exportLocation()
{
    return mExportLocation;
}

void ExportDialog::setDefaultFileName(const QString& fileName)
{
    mDefaultFileName = fileName;
}
