/********************************************************************************
** Form generated from reading UI file 'ImportDialog.ui'
**
** Created: Mon Jun 25 18:55:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTDIALOG_H
#define UI_IMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ImportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *vCardFileLabel;
    QLineEdit *importLocationLineEdit;
    QPushButton *BrowseButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportDialog)
    {
        if (ImportDialog->objectName().isEmpty())
            ImportDialog->setObjectName(QString::fromUtf8("ImportDialog"));
        ImportDialog->resize(400, 85);
        ImportDialog->setMinimumSize(QSize(400, 85));
        ImportDialog->setMaximumSize(QSize(400, 85));
        verticalLayout = new QVBoxLayout(ImportDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        vCardFileLabel = new QLabel(ImportDialog);
        vCardFileLabel->setObjectName(QString::fromUtf8("vCardFileLabel"));

        horizontalLayout->addWidget(vCardFileLabel);

        importLocationLineEdit = new QLineEdit(ImportDialog);
        importLocationLineEdit->setObjectName(QString::fromUtf8("importLocationLineEdit"));
        importLocationLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(importLocationLineEdit);

        BrowseButton = new QPushButton(ImportDialog);
        BrowseButton->setObjectName(QString::fromUtf8("BrowseButton"));

        horizontalLayout->addWidget(BrowseButton);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ImportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ImportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportDialog)
    {
        ImportDialog->setWindowTitle(QApplication::translate("ImportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        vCardFileLabel->setText(QApplication::translate("ImportDialog", "vCard File: ", 0, QApplication::UnicodeUTF8));
        BrowseButton->setText(QApplication::translate("ImportDialog", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImportDialog: public Ui_ImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTDIALOG_H
