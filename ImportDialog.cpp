#include "ImportDialog.h"
#include "ui_ImportDialog.h"
#include <QFileDialog>
#include <QtDebug>

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    ui->BrowseButton->setFocus(Qt::OtherFocusReason);

    setWindowTitle("Import Contact(s)");

    mImportLocation = "";
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

void ImportDialog::on_buttonBox_accepted()
{
    if(mImportLocation.isEmpty())
        return;
    else
    {
        ui->importLocationLineEdit->clear();
        this->hide();
    }
}

void ImportDialog::on_BrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Import Location"),"",
                                                    tr("vCard Format (*.vcf);;All Files (*)"));
    if(!fileName.isEmpty())
    {
        mImportLocation = fileName;
        ui->importLocationLineEdit->setText(fileName);
    }
    return;
}

QString& ImportDialog::importLocation()
{
    return mImportLocation;
}
