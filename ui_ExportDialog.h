/********************************************************************************
** Form generated from reading UI file 'ExportDialog.ui'
**
** Created: Mon Jun 25 18:55:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTDIALOG_H
#define UI_EXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout_2;
    QLabel *exportLocationLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *exportLocationLineEdit;
    QPushButton *browseButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExportDialog)
    {
        if (ExportDialog->objectName().isEmpty())
            ExportDialog->setObjectName(QString::fromUtf8("ExportDialog"));
        ExportDialog->resize(450, 170);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExportDialog->sizePolicy().hasHeightForWidth());
        ExportDialog->setSizePolicy(sizePolicy);
        ExportDialog->setMinimumSize(QSize(450, 170));
        ExportDialog->setMaximumSize(QSize(450, 170));
        verticalLayout = new QVBoxLayout(ExportDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ExportDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        exportLocationLabel = new QLabel(ExportDialog);
        exportLocationLabel->setObjectName(QString::fromUtf8("exportLocationLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, exportLocationLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        exportLocationLineEdit = new QLineEdit(ExportDialog);
        exportLocationLineEdit->setObjectName(QString::fromUtf8("exportLocationLineEdit"));
        exportLocationLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(exportLocationLineEdit);

        browseButton = new QPushButton(ExportDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));

        horizontalLayout->addWidget(browseButton);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout->addLayout(formLayout_2);

        buttonBox = new QDialogButtonBox(ExportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ExportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportDialog)
    {
        ExportDialog->setWindowTitle(QApplication::translate("ExportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ExportDialog", "Contact(s) will be exported in vCard 3.0 format, which is compatible with most smartphones and E-mail services.", 0, QApplication::UnicodeUTF8));
        exportLocationLabel->setText(QApplication::translate("ExportDialog", "Export Location:", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("ExportDialog", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportDialog: public Ui_ExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTDIALOG_H
