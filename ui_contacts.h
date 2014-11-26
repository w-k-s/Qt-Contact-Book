/********************************************************************************
** Form generated from reading UI file 'contacts.ui'
**
** Created: Wed Jun 27 00:42:56 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTS_H
#define UI_CONTACTS_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Contacts
{
public:
    QAction *actionImport;
    QAction *actionExport_All;
    QAction *actionQuit;
    QAction *actionAbout_Contacts;
    QAction *actionAbout_Qt;
    QAction *actionHelp;
    QAction *actionRemove_All;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *SearchLineEdit;
    QPushButton *DoneButton;
    QListView *listView;
    QLabel *ContactCountLabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *EmailLabel;
    QLineEdit *EmailLineEdit;
    QLabel *PhoneHomeLabel;
    QLineEdit *PhoneHomeLineEdit;
    QLabel *PhoneMobileLabel;
    QLineEdit *PhoneMobileLineEdit;
    QLabel *PhoneWorkLabel;
    QLineEdit *PhoneWorkLineEdit;
    QLabel *AddressLabel;
    QLineEdit *AddressLineEdit;
    QLabel *CityLabel;
    QLineEdit *CityLineEdit;
    QLabel *StateLabel;
    QLineEdit *StateLineEdit;
    QLabel *ZipCodeLabel;
    QLineEdit *ZipCodeLineEdit;
    QLabel *CountryLabel;
    QLineEdit *CountryLineEdit;
    QLabel *BirthdayLabel;
    QDateEdit *BirthdayDateEdit;
    QLabel *NameLabel;
    QLineEdit *NameLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *AddButton;
    QPushButton *EditButton;
    QPushButton *SaveButton;
    QPushButton *CancelButton;
    QPushButton *RemoveButton;
    QPushButton *ExportButton;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Contacts)
    {
        if (Contacts->objectName().isEmpty())
            Contacts->setObjectName(QString::fromUtf8("Contacts"));
        Contacts->resize(826, 547);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Contacts->sizePolicy().hasHeightForWidth());
        Contacts->setSizePolicy(sizePolicy);
        Contacts->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background:qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:0, stop:0  rgba(255,255, 255, 255), stop:1 rgba(229, 229, 229, 255));\n"
"}\n"
"\n"
"QLineEdit {\n"
"     border: 1px solid #cccccc;\n"
"     border-radius: 4px;\n"
"	padding:2px;\n"
"	margin:4px;\n"
" }\n"
"\n"
"QLineEdit:read-only {\n"
"     border:none;\n"
"}\n"
"\n"
"QPushButton {\n"
"     border: 1px solid #cccccc;\n"
"     border-radius: 4px;\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,          stop:0 rgba(255,255,255,255), stop:0.46 rgba(246,246,246,255),stop: 1 rgba(237,237,237,255));\n"
"	padding:7px;\n"
"	margin:2px;\n"
"	min-width:80px;\n"
"	color:black;\n"
"	font-weight:bold;\n"
" }\n"
"\n"
" QPushButton:pressed {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 rgba(238,238,238,255), stop: 1 rgba(204,204,204,255));\n"
" }\n"
"\n"
" QPushButton:flat {\n"
"     border: none; \n"
" }\n"
"\n"
" QPushButton:default {\n"
"   "
                        "  border-color: #4196e1; /* make the default button prominent*/  \n"
"}"));
        actionImport = new QAction(Contacts);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        actionExport_All = new QAction(Contacts);
        actionExport_All->setObjectName(QString::fromUtf8("actionExport_All"));
        actionQuit = new QAction(Contacts);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout_Contacts = new QAction(Contacts);
        actionAbout_Contacts->setObjectName(QString::fromUtf8("actionAbout_Contacts"));
        actionAbout_Qt = new QAction(Contacts);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionHelp = new QAction(Contacts);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionRemove_All = new QAction(Contacts);
        actionRemove_All->setObjectName(QString::fromUtf8("actionRemove_All"));
        centralWidget = new QWidget(Contacts);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setStyleSheet(QString::fromUtf8("QSplitter{\n"
"	background-color:rgba(255,255,255,0);\n"
"}"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        SearchLineEdit = new QLineEdit(verticalLayoutWidget);
        SearchLineEdit->setObjectName(QString::fromUtf8("SearchLineEdit"));

        horizontalLayout_3->addWidget(SearchLineEdit);

        DoneButton = new QPushButton(verticalLayoutWidget);
        DoneButton->setObjectName(QString::fromUtf8("DoneButton"));

        horizontalLayout_3->addWidget(DoneButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        listView = new QListView(verticalLayoutWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy1);
        listView->setStyleSheet(QString::fromUtf8(" QListView {\n"
"     alternate-background-color: yellow;\n"
" }"));

        verticalLayout_2->addWidget(listView);

        ContactCountLabel = new QLabel(verticalLayoutWidget);
        ContactCountLabel->setObjectName(QString::fromUtf8("ContactCountLabel"));

        verticalLayout_2->addWidget(ContactCountLabel);

        splitter->addWidget(verticalLayoutWidget);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        EmailLabel = new QLabel(widget);
        EmailLabel->setObjectName(QString::fromUtf8("EmailLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, EmailLabel);

        EmailLineEdit = new QLineEdit(widget);
        EmailLineEdit->setObjectName(QString::fromUtf8("EmailLineEdit"));
        EmailLineEdit->setMaxLength(70);

        formLayout->setWidget(1, QFormLayout::FieldRole, EmailLineEdit);

        PhoneHomeLabel = new QLabel(widget);
        PhoneHomeLabel->setObjectName(QString::fromUtf8("PhoneHomeLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, PhoneHomeLabel);

        PhoneHomeLineEdit = new QLineEdit(widget);
        PhoneHomeLineEdit->setObjectName(QString::fromUtf8("PhoneHomeLineEdit"));
        PhoneHomeLineEdit->setMaxLength(18);

        formLayout->setWidget(2, QFormLayout::FieldRole, PhoneHomeLineEdit);

        PhoneMobileLabel = new QLabel(widget);
        PhoneMobileLabel->setObjectName(QString::fromUtf8("PhoneMobileLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, PhoneMobileLabel);

        PhoneMobileLineEdit = new QLineEdit(widget);
        PhoneMobileLineEdit->setObjectName(QString::fromUtf8("PhoneMobileLineEdit"));
        PhoneMobileLineEdit->setMaxLength(18);

        formLayout->setWidget(3, QFormLayout::FieldRole, PhoneMobileLineEdit);

        PhoneWorkLabel = new QLabel(widget);
        PhoneWorkLabel->setObjectName(QString::fromUtf8("PhoneWorkLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, PhoneWorkLabel);

        PhoneWorkLineEdit = new QLineEdit(widget);
        PhoneWorkLineEdit->setObjectName(QString::fromUtf8("PhoneWorkLineEdit"));
        PhoneWorkLineEdit->setMaxLength(18);

        formLayout->setWidget(4, QFormLayout::FieldRole, PhoneWorkLineEdit);

        AddressLabel = new QLabel(widget);
        AddressLabel->setObjectName(QString::fromUtf8("AddressLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, AddressLabel);

        AddressLineEdit = new QLineEdit(widget);
        AddressLineEdit->setObjectName(QString::fromUtf8("AddressLineEdit"));
        AddressLineEdit->setMaxLength(200);

        formLayout->setWidget(7, QFormLayout::FieldRole, AddressLineEdit);

        CityLabel = new QLabel(widget);
        CityLabel->setObjectName(QString::fromUtf8("CityLabel"));

        formLayout->setWidget(8, QFormLayout::LabelRole, CityLabel);

        CityLineEdit = new QLineEdit(widget);
        CityLineEdit->setObjectName(QString::fromUtf8("CityLineEdit"));
        CityLineEdit->setMaxLength(50);

        formLayout->setWidget(8, QFormLayout::FieldRole, CityLineEdit);

        StateLabel = new QLabel(widget);
        StateLabel->setObjectName(QString::fromUtf8("StateLabel"));

        formLayout->setWidget(9, QFormLayout::LabelRole, StateLabel);

        StateLineEdit = new QLineEdit(widget);
        StateLineEdit->setObjectName(QString::fromUtf8("StateLineEdit"));
        StateLineEdit->setMaxLength(50);

        formLayout->setWidget(9, QFormLayout::FieldRole, StateLineEdit);

        ZipCodeLabel = new QLabel(widget);
        ZipCodeLabel->setObjectName(QString::fromUtf8("ZipCodeLabel"));

        formLayout->setWidget(10, QFormLayout::LabelRole, ZipCodeLabel);

        ZipCodeLineEdit = new QLineEdit(widget);
        ZipCodeLineEdit->setObjectName(QString::fromUtf8("ZipCodeLineEdit"));
        ZipCodeLineEdit->setMaxLength(10);

        formLayout->setWidget(10, QFormLayout::FieldRole, ZipCodeLineEdit);

        CountryLabel = new QLabel(widget);
        CountryLabel->setObjectName(QString::fromUtf8("CountryLabel"));

        formLayout->setWidget(11, QFormLayout::LabelRole, CountryLabel);

        CountryLineEdit = new QLineEdit(widget);
        CountryLineEdit->setObjectName(QString::fromUtf8("CountryLineEdit"));
        CountryLineEdit->setMaxLength(50);

        formLayout->setWidget(11, QFormLayout::FieldRole, CountryLineEdit);

        BirthdayLabel = new QLabel(widget);
        BirthdayLabel->setObjectName(QString::fromUtf8("BirthdayLabel"));

        formLayout->setWidget(12, QFormLayout::LabelRole, BirthdayLabel);

        BirthdayDateEdit = new QDateEdit(widget);
        BirthdayDateEdit->setObjectName(QString::fromUtf8("BirthdayDateEdit"));
        BirthdayDateEdit->setMaximumDate(QDate(2100, 12, 31));

        formLayout->setWidget(12, QFormLayout::FieldRole, BirthdayDateEdit);

        NameLabel = new QLabel(widget);
        NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, NameLabel);

        NameLineEdit = new QLineEdit(widget);
        NameLineEdit->setObjectName(QString::fromUtf8("NameLineEdit"));
        NameLineEdit->setStyleSheet(QString::fromUtf8(""));
        NameLineEdit->setMaxLength(60);

        formLayout->setWidget(0, QFormLayout::FieldRole, NameLineEdit);


        horizontalLayout_2->addLayout(formLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        AddButton = new QPushButton(widget);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));

        horizontalLayout->addWidget(AddButton);

        EditButton = new QPushButton(widget);
        EditButton->setObjectName(QString::fromUtf8("EditButton"));

        horizontalLayout->addWidget(EditButton);

        SaveButton = new QPushButton(widget);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));

        horizontalLayout->addWidget(SaveButton);

        CancelButton = new QPushButton(widget);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        horizontalLayout->addWidget(CancelButton);

        RemoveButton = new QPushButton(widget);
        RemoveButton->setObjectName(QString::fromUtf8("RemoveButton"));

        horizontalLayout->addWidget(RemoveButton);

        ExportButton = new QPushButton(widget);
        ExportButton->setObjectName(QString::fromUtf8("ExportButton"));

        horizontalLayout->addWidget(ExportButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(widget);

        verticalLayout_4->addWidget(splitter);

        Contacts->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Contacts);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 826, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        Contacts->setMenuBar(menuBar);
        statusBar = new QStatusBar(Contacts);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8("QStatusBar{\n"
"	background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #2c2c2c,  stop:1 #000000);\n"
"	color:white;\n"
"}"));
        Contacts->setStatusBar(statusBar);
        QWidget::setTabOrder(NameLineEdit, EmailLineEdit);
        QWidget::setTabOrder(EmailLineEdit, PhoneHomeLineEdit);
        QWidget::setTabOrder(PhoneHomeLineEdit, PhoneMobileLineEdit);
        QWidget::setTabOrder(PhoneMobileLineEdit, PhoneWorkLineEdit);
        QWidget::setTabOrder(PhoneWorkLineEdit, AddressLineEdit);
        QWidget::setTabOrder(AddressLineEdit, CityLineEdit);
        QWidget::setTabOrder(CityLineEdit, StateLineEdit);
        QWidget::setTabOrder(StateLineEdit, ZipCodeLineEdit);
        QWidget::setTabOrder(ZipCodeLineEdit, CountryLineEdit);
        QWidget::setTabOrder(CountryLineEdit, BirthdayDateEdit);
        QWidget::setTabOrder(BirthdayDateEdit, AddButton);
        QWidget::setTabOrder(AddButton, EditButton);
        QWidget::setTabOrder(EditButton, SaveButton);
        QWidget::setTabOrder(SaveButton, CancelButton);
        QWidget::setTabOrder(CancelButton, RemoveButton);
        QWidget::setTabOrder(RemoveButton, ExportButton);
        QWidget::setTabOrder(ExportButton, listView);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport_All);
        menuFile->addAction(actionRemove_All);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAbout->addAction(actionAbout_Contacts);
        menuAbout->addAction(actionAbout_Qt);
        menuAbout->addSeparator();

        retranslateUi(Contacts);

        QMetaObject::connectSlotsByName(Contacts);
    } // setupUi

    void retranslateUi(QMainWindow *Contacts)
    {
        Contacts->setWindowTitle(QApplication::translate("Contacts", "Contacts", 0, QApplication::UnicodeUTF8));
        actionImport->setText(QApplication::translate("Contacts", "&Import", 0, QApplication::UnicodeUTF8));
        actionImport->setShortcut(QApplication::translate("Contacts", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionExport_All->setText(QApplication::translate("Contacts", "&Export All", 0, QApplication::UnicodeUTF8));
        actionExport_All->setShortcut(QApplication::translate("Contacts", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("Contacts", "&Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("Contacts", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout_Contacts->setText(QApplication::translate("Contacts", "About &Contacts", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("Contacts", "About &Qt", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("Contacts", "Help", 0, QApplication::UnicodeUTF8));
        actionRemove_All->setText(QApplication::translate("Contacts", "&Remove All", 0, QApplication::UnicodeUTF8));
        actionRemove_All->setShortcut(QApplication::translate("Contacts", "Ctrl+Del", 0, QApplication::UnicodeUTF8));
        SearchLineEdit->setText(QString());
        SearchLineEdit->setPlaceholderText(QApplication::translate("Contacts", "Search Name, E-mail or Number", 0, QApplication::UnicodeUTF8));
        DoneButton->setText(QApplication::translate("Contacts", "&Done", 0, QApplication::UnicodeUTF8));
        ContactCountLabel->setText(QString());
        EmailLabel->setText(QApplication::translate("Contacts", "<b>E-mail:</b>", 0, QApplication::UnicodeUTF8));
        EmailLineEdit->setPlaceholderText(QApplication::translate("Contacts", "Example@Example.com", 0, QApplication::UnicodeUTF8));
        PhoneHomeLabel->setText(QApplication::translate("Contacts", "<b>Phone (Home):</b>", 0, QApplication::UnicodeUTF8));
        PhoneHomeLineEdit->setPlaceholderText(QApplication::translate("Contacts", "Example: 00 965 123 456", 0, QApplication::UnicodeUTF8));
        PhoneMobileLabel->setText(QApplication::translate("Contacts", "<b>Phone (Mobile):</b>", 0, QApplication::UnicodeUTF8));
        PhoneMobileLineEdit->setText(QString());
        PhoneMobileLineEdit->setPlaceholderText(QApplication::translate("Contacts", "Example: 00 965 123 456", 0, QApplication::UnicodeUTF8));
        PhoneWorkLabel->setText(QApplication::translate("Contacts", "<b>Phone (Work):</b>", 0, QApplication::UnicodeUTF8));
        PhoneWorkLineEdit->setPlaceholderText(QApplication::translate("Contacts", "Example: 00 965 123 456", 0, QApplication::UnicodeUTF8));
        AddressLabel->setText(QApplication::translate("Contacts", "<b>Address:</b>", 0, QApplication::UnicodeUTF8));
        CityLabel->setText(QApplication::translate("Contacts", "<b>City:</b>", 0, QApplication::UnicodeUTF8));
        StateLabel->setText(QApplication::translate("Contacts", "<b>State:</b>", 0, QApplication::UnicodeUTF8));
        ZipCodeLabel->setText(QApplication::translate("Contacts", "<b>ZIP Code:</b>", 0, QApplication::UnicodeUTF8));
        CountryLabel->setText(QApplication::translate("Contacts", "<b>Country:</b>", 0, QApplication::UnicodeUTF8));
        BirthdayLabel->setText(QApplication::translate("Contacts", "<b>Birthday</b>", 0, QApplication::UnicodeUTF8));
        NameLabel->setText(QApplication::translate("Contacts", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Full Name:</span> </p></body></html>", 0, QApplication::UnicodeUTF8));
        NameLineEdit->setPlaceholderText(QApplication::translate("Contacts", "First-Name Last-Name", 0, QApplication::UnicodeUTF8));
        AddButton->setText(QApplication::translate("Contacts", "&Add", 0, QApplication::UnicodeUTF8));
        EditButton->setText(QApplication::translate("Contacts", "&Edit", 0, QApplication::UnicodeUTF8));
        SaveButton->setText(QApplication::translate("Contacts", "&Save", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("Contacts", "&Cancel", 0, QApplication::UnicodeUTF8));
        RemoveButton->setText(QApplication::translate("Contacts", "&Remove", 0, QApplication::UnicodeUTF8));
        ExportButton->setText(QApplication::translate("Contacts", "E&xport", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("Contacts", "File", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("Contacts", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Contacts: public Ui_Contacts {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTS_H
