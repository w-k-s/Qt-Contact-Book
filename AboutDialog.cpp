#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("About");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::mouseReleaseEvent(QMouseEvent *)
{
    this->hide();
}
