#include "contacts.h"
#include "ui_contacts.h"
#include <QDate>
#include <QLocale>
#include <QMessageBox>
#include <QtDebug>
#include <ExportDialog.h>
#include <ImportDialog.h>
#include <AboutDialog.h>
#include <QFile>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <vcardparser.h>

#define MAXIMUM_NUMBER_OF_CONTACTS 5000; /*Contacts database should not be allowed to be greater than 2MB in size. */

Contacts::Contacts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Contacts)
{
    //1. Setup ui
    ui->setupUi(this);
    QLocale locale;
    ui->BirthdayDateEdit->setDisplayFormat(locale.dateFormat(QLocale::LongFormat));
    ui->NameLineEdit->setFocus();

    clear();



    //2. Initialise Database;

    SelectedRecordId = -1;
    SearchInProgress = false;

    OpenDatabase();

    DefaultModelQuery.append("SELECT Id,FirstName||' '||LastName AS FullName,");
    DefaultModelQuery.append("FirstName,LastName,Email,HomeNumber,WorkNumber,MobileNumber,Address,City,State,Zip,Country,Birthdate FROM Contacts ");
    DefaultModelQuery.append("ORDER BY FirstName;");

    QSqlQuery Query(DefaultModelQuery);
    /*if(!Query.exec())
    {
        QMessageBox::warning(this,
                             tr("Problem Displaying Contacts"),
                             tr("A problem occured while attempting to display the contact list."));
        exit(1);
    }*/

    ActiveQuery = Query;
    Model = new QSqlQueryModel(this);
    Model->setQuery(ActiveQuery);

    ui->listView->setModel(Model);
    ui->listView->setModelColumn(1);

    ui->ContactCountLabel->setAlignment(Qt::AlignCenter);
    this->UpdateContactCount();

    exportDialog = new ExportDialog(this);
    importDialog = new ImportDialog(this);
    aboutDialog = new AboutDialog(this);

    connect(ui->listView,SIGNAL(activated(QModelIndex)),this,SLOT(DisplayContact(QModelIndex)));

    connect(ui->AddButton,SIGNAL(clicked()),this,SLOT(AddContact()));
    connect(ui->EditButton,SIGNAL(clicked()),this,SLOT(EditContact()));
    connect(ui->CancelButton,SIGNAL(clicked()),this,SLOT(CancelEditContact()));
    connect(ui->SaveButton,SIGNAL(clicked()),this,SLOT(SaveContact()));
    connect(ui->RemoveButton,SIGNAL(clicked()),this,SLOT(RemoveContact()));
    connect(ui->ExportButton,SIGNAL(clicked()),this,SLOT(ExportContact()));
    connect(ui->actionImport,SIGNAL(triggered()),this,SLOT(ImportContacts()));
    connect(ui->DoneButton,SIGNAL(clicked()),this,SLOT(ReturnFromSearchResults()));
    connect(ui->actionRemove_All,SIGNAL(triggered()),this,SLOT(RemoveAllContacts()));
    connect(ui->SearchLineEdit,SIGNAL(returnPressed()),SLOT(SearchContact()));

    this->SetView(Contacts::View_AddContactView);
    //this->Test();
}

Contacts::~Contacts()
{
    db.close();
    delete ui;
}

void Contacts::OpenDatabase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    /*Remove hard-coded file path*/
    db.setDatabaseName("Contacts.db");
    db.setUserName("Waqqas");
    db.setPassword("W0096523984409K270188S");

    if(!db.open())
    {
        qDebug()<<db.lastError().driverText();
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("A problem occurred while trying to open the database. The application will exit.\nDetails: %1").arg(db.lastError().text()));
        exit(1);
    }

    QString CreateQuery;
    CreateQuery.append("CREATE TABLE IF NOT EXISTS Contacts ");
    CreateQuery.append("(Id INTEGER PRIMARY KEY AUTOINCREMENT,");
    CreateQuery.append("FirstName VARCHAR(30) NOT NULL,");
    CreateQuery.append("LastName VARCHAR(30) NOT NULL,");
    CreateQuery.append("Email VARCHAR(70),");
    CreateQuery.append("HomeNumber UNSIGNED LONG,");
    CreateQuery.append("MobileNumber UNSIGNED LONG,");
    CreateQuery.append("WorkNumber UNSIGNED LONG,");
    CreateQuery.append("Address VARCHAR(200),");
    CreateQuery.append("City VARCHAR(50),");
    CreateQuery.append("State VARCHAR(50),");
    CreateQuery.append("Zip UNSIGNED SHORT,");
    CreateQuery.append("Country VARCHAR(50),");
    CreateQuery.append("Birthdate DATE);");

    QSqlQuery Query(CreateQuery);
    if(!Query.exec())
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("A problem occured while trying to create the database. The application will exit.\nDetails: %1").arg(Query.lastError().text()));
        exit(1);
    }
}

void Contacts::SetView(Contacts::View v)
{
    switch(v)
    {
    case Contacts::View_DisplayContactView:
        view = Contacts::View_DisplayContactView;

        ui->NameLineEdit->setReadOnly(true);
        ui->BirthdayDateEdit->setReadOnly(true);
        ui->EmailLineEdit->setReadOnly(true);
        ui->PhoneHomeLineEdit->setReadOnly(true);
        ui->PhoneMobileLineEdit->setReadOnly(true);
        ui->PhoneWorkLineEdit->setReadOnly(true);
        ui->AddressLineEdit->setReadOnly(true);
        ui->CityLineEdit->setReadOnly(true);
        ui->StateLineEdit->setReadOnly(true);
        ui->ZipCodeLineEdit->setReadOnly(true);
        ui->CountryLineEdit->setReadOnly(true);

        ui->AddButton->setVisible(!SearchInProgress);
        ui->EditButton->setVisible(true);
        ui->SaveButton->setVisible(false);
        ui->CancelButton->setVisible(false);
        ui->RemoveButton->setVisible(true);
        ui->ExportButton->setVisible(true);
        ui->DoneButton->setVisible(SearchInProgress);
        break;

    case Contacts::View_AddContactView:
        view = Contacts::View_AddContactView;

        ui->NameLineEdit->setReadOnly(false);
        ui->BirthdayDateEdit->setReadOnly(false);
        ui->EmailLineEdit->setReadOnly(false);
        ui->PhoneHomeLineEdit->setReadOnly(false);
        ui->PhoneMobileLineEdit->setReadOnly(false);
        ui->PhoneWorkLineEdit->setReadOnly(false);
        ui->AddressLineEdit->setReadOnly(false);
        ui->CityLineEdit->setReadOnly(false);
        ui->StateLineEdit->setReadOnly(false);
        ui->ZipCodeLineEdit->setReadOnly(false);
        ui->CountryLineEdit->setReadOnly(false);

        ui->AddButton->setVisible(!SearchInProgress);
        ui->EditButton->setVisible(false);
        ui->SaveButton->setVisible(false);
        ui->CancelButton->setVisible(false);
        ui->RemoveButton->setVisible(false);
        ui->ExportButton->setVisible(false);
        ui->DoneButton->setVisible(SearchInProgress);
    break;

    case Contacts::View_EditContactView:
        view = Contacts::View_EditContactView;

        ui->NameLineEdit->setReadOnly(false);
        ui->BirthdayDateEdit->setReadOnly(false);
        ui->EmailLineEdit->setReadOnly(false);
        ui->PhoneHomeLineEdit->setReadOnly(false);
        ui->PhoneMobileLineEdit->setReadOnly(false);
        ui->PhoneWorkLineEdit->setReadOnly(false);
        ui->AddressLineEdit->setReadOnly(false);
        ui->CityLineEdit->setReadOnly(false);
        ui->StateLineEdit->setReadOnly(false);
        ui->ZipCodeLineEdit->setReadOnly(false);
        ui->CountryLineEdit->setReadOnly(false);

        ui->AddButton->setVisible(false);
        ui->EditButton->setVisible(false);
        ui->SaveButton->setVisible(true);
        ui->CancelButton->setVisible(true);
        ui->RemoveButton->setVisible(false);
        ui->ExportButton->setVisible(false);
        ui->DoneButton->setVisible(SearchInProgress);
    break;

    case Contacts::View_DisplaySearchResultsView:
        view = Contacts::View_DisplaySearchResultsView;
        SearchInProgress = true;

        ui->NameLineEdit->setReadOnly(true);
        ui->BirthdayDateEdit->setReadOnly(true);
        ui->EmailLineEdit->setReadOnly(true);
        ui->PhoneHomeLineEdit->setReadOnly(true);
        ui->PhoneMobileLineEdit->setReadOnly(true);
        ui->PhoneWorkLineEdit->setReadOnly(true);
        ui->AddressLineEdit->setReadOnly(true);
        ui->CityLineEdit->setReadOnly(true);
        ui->StateLineEdit->setReadOnly(true);
        ui->ZipCodeLineEdit->setReadOnly(true);
        ui->CountryLineEdit->setReadOnly(true);

        ui->AddButton->setVisible(false);
        ui->EditButton->setVisible(true);
        ui->SaveButton->setVisible(false);
        ui->CancelButton->setVisible(false);
        ui->RemoveButton->setVisible(true);
        ui->ExportButton->setVisible(true);
        ui->DoneButton->setVisible(true);
        break;
    }
}

Contacts::View Contacts::getView()
{
    return view;
}

bool Contacts::Validate()
{
    bool EverythingOkay = true;
    //Validate Name
    {
    QString Text = ui->NameLineEdit->text();

    if(Text.isEmpty()||Text.split(" ").length()<2)
        {
            ui->NameLineEdit->clear();
            ui->NameLineEdit->setPlaceholderText("First Name & Last Name Required");
            ui->NameLineEdit->setStyleSheet("QLineEdit{background-color: red;}");
            EverythingOkay = false;
        }else
        {
            if(Text.contains(QRegExp("^[0-9]+$")))
            {
                ui->NameLineEdit->clear();
                ui->NameLineEdit->setStyleSheet("QLineEdit{background-color: red;}");
                ui->NameLineEdit->setPlaceholderText("Must NOT contain number.");
                EverythingOkay = false;
            }else
            {
                ui->NameLineEdit->setPlaceholderText("First-Name Last-Name");
                ui->NameLineEdit->setStyleSheet("QLineEdit{background-color:white;}");
            }
        }
    }
    //NUMBER VALIDATION
    {
        QStringList Numbers;
        Numbers<<ui->PhoneHomeLineEdit->text().trimmed()
                 <<ui->PhoneMobileLineEdit->text().trimmed()
                   <<ui->PhoneWorkLineEdit->text().trimmed();

        bool NumberFieldsCorrect = true;
        for(int i=0;i<Numbers.length();i++)
        {
            if(Numbers.at(i).isEmpty())
                break;

            if(!Numbers.at(i).contains(QRegExp("^[0-9]+$")))
            {
                switch(i)
                {
                //Home Number
                case 0:
                    ui->PhoneHomeLineEdit->clear();
                    ui->PhoneHomeLineEdit->setStyleSheet("QLineEdit{background-color:red;}");
                    ui->PhoneHomeLineEdit->setPlaceholderText("Digits Only.");
                    EverythingOkay = NumberFieldsCorrect = false;
                    break;

                //Mobile Number
                case 1:
                    ui->PhoneMobileLineEdit->clear();
                    ui->PhoneMobileLineEdit->setStyleSheet("QLineEdit{background-color:red;}");
                    ui->PhoneMobileLineEdit->setPlaceholderText("Digits Only.");
                    EverythingOkay = NumberFieldsCorrect = false;
                    break;

                //Work Number
                case 2:
                    ui->PhoneWorkLineEdit->clear();
                    ui->PhoneWorkLineEdit->setStyleSheet("QLineEdit{background-color:red;}");
                    ui->PhoneWorkLineEdit->setPlaceholderText("Digits Only.");
                    EverythingOkay = NumberFieldsCorrect = false;
                    break;
                }
            }
        }

        if(NumberFieldsCorrect)
        {
            ui->PhoneHomeLineEdit->setStyleSheet("QLineEdit{background-color:white;}");
            ui->PhoneMobileLineEdit->setStyleSheet("QLineEdit{background-color:white;}");
            ui->PhoneWorkLineEdit->setStyleSheet("QLineEdit{background-color:white;}");

            ui->PhoneHomeLineEdit->setPlaceholderText("Example: 00 965 123 456");
            ui->PhoneMobileLineEdit->setPlaceholderText("Example: 00 965 123 456");
            ui->PhoneWorkLineEdit->setPlaceholderText("Example: 00 965 123 456");
        }

    }
    //EMAIL VALIDATION
    {
        QString Email = ui->EmailLineEdit->text();
        if(!Email.isEmpty())
        {
            /*
              This regex returns all emails as false. Look into this regex before release.


            if(!Email.contains(QRegExp("\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}\b")))
            {
                ui->EmailLineEdit->clear();
                ui->EmailLineEdit->setStyleSheet("QLineEdit{background-color:red;}");
                ui->EmailLineEdit->setPlaceholderText("Improper E-mail.");
                EverythingOkay = false;
            }else
            {
                ui->EmailLineEdit->setStyleSheet("QLineEdit{background-color:white;}");
                ui->EmailLineEdit->setPlaceholderText("Example@Example.com");
            }*/
        }

    }
    //ADDRESS VALIDATION
    {
        QStringList address;
        address << ui->AddressLineEdit->text()
                   <<ui->CityLineEdit->text()
                     <<ui->StateLineEdit->text()
                       <<ui->ZipCodeLineEdit->text()
                         <<ui->CountryLineEdit->text();
        for(int i=0;i<address.length();i++)
            address[i].remove(QRegExp("[^A-Za-z0-9\s,./-]"));

        ui->AddressLineEdit->setText(address[0]);
        ui->CityLineEdit->setText(address[1]);
        ui->StateLineEdit->setText(address[2]);
        ui->ZipCodeLineEdit->setText(address[3]);
        ui->CountryLineEdit->setText(address[4]);
    }

    return EverythingOkay;
}

void Contacts::AddContact()
{

    if(view == Contacts::View_DisplayContactView)
    {
        clear();
        SetView(Contacts::View_AddContactView);
        SelectedRecordId = -1;
        //SelectedRecordIndex = NULL;
        return;
    }

    if(this->Validate())
    {
        QString Text = ui->NameLineEdit->text();
        QStringList Name = Text.split(" ");
        QString First_Name,Last_Name;
        if(Name.size()==1)
        {
            First_Name = Name.first();
            Last_Name = "";
        }else
        {
            First_Name = Name.first();
            Last_Name = Name.last();
        }

        QDate bdate = ui->BirthdayDateEdit->date();
        QString Date = QString::number(bdate.year()) + "-"+QString::number(bdate.month())+"-"+QString::number(bdate.day());

        QSqlQuery InsertQuery;
        InsertQuery.prepare("INSERT INTO Contacts (FirstName,LastName,Email,HomeNumber,WorkNumber,MobileNumber,Address,City,State,Zip,Country,Birthdate) VALUES (:f,:l,:e,:ph,:pw,:pm,:a,:ct,:s,:z,:c,:b);");
        InsertQuery.bindValue(":f",First_Name);
        InsertQuery.bindValue(":l",Last_Name);
        InsertQuery.bindValue(":e",ui->EmailLineEdit->text());
        InsertQuery.bindValue(":ph",ui->PhoneHomeLineEdit->text());
        InsertQuery.bindValue(":pw",ui->PhoneWorkLineEdit->text());
        InsertQuery.bindValue(":pm",ui->PhoneMobileLineEdit->text());
        InsertQuery.bindValue(":a",ui->AddressLineEdit->text());
        InsertQuery.bindValue(":ct",ui->CityLineEdit->text());
        InsertQuery.bindValue(":s",ui->StateLineEdit->text());
        InsertQuery.bindValue(":z",ui->ZipCodeLineEdit->text());
        InsertQuery.bindValue(":c",ui->CountryLineEdit->text());
        InsertQuery.bindValue(":b",Date);

        if(!InsertQuery.exec())
        {
            qDebug()<<"InsertQuery.lastError().text() :"<<InsertQuery.lastError().text();
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("A problem occured while trying to add \"%1 %2\".\nDetails: %3 ")
                                 .arg(First_Name,Last_Name,InsertQuery.lastError().text()));
        }else
        {
            Model->setQuery(DefaultModelQuery);
            clear();
            UpdateContactCount();
        }
    }
}

void Contacts::clear()
{
    QString Style="QLineEdit{background:white;}";

    ui->NameLineEdit->clear();
    ui->NameLineEdit->setStyleSheet(Style);
    ui->NameLineEdit->setPlaceholderText("First-Name Last-Name");

    ui->EmailLineEdit->clear();
    ui->EmailLineEdit->setStyleSheet(Style);
    ui->EmailLineEdit->setPlaceholderText("Example@Example.com");

    ui->PhoneHomeLineEdit->clear();
    ui->PhoneHomeLineEdit->setStyleSheet(Style);
    ui->PhoneHomeLineEdit->setPlaceholderText("Example: 00 965 123 456");

    ui->PhoneMobileLineEdit->clear();
    ui->PhoneMobileLineEdit->setStyleSheet(Style);
    ui->PhoneMobileLineEdit->setPlaceholderText("Example: 00 965 123 456");

    ui->PhoneWorkLineEdit->clear();
    ui->PhoneWorkLineEdit->setStyleSheet(Style);
    ui->PhoneWorkLineEdit->setPlaceholderText("Example: 00 965 123 456");

    ui->AddressLineEdit->clear();
    ui->CityLineEdit->clear();
    ui->StateLineEdit->clear();
    ui->ZipCodeLineEdit->clear();
    ui->CountryLineEdit->clear();
    ui->BirthdayDateEdit->setDate(QDate(2000,1,1));
}

void Contacts::DisplayContact(QModelIndex index)
{
    clear();
    this->SetView(Contacts::View_DisplayContactView);

    QSqlRecord ContactRecord = Model->record(index.row());

    SelectedRecordId = ContactRecord.value("Id").toInt();
    SelectedRecordIndex = index;

    ui->NameLineEdit->setText(ContactRecord.value("FirstName").toString()+" "+ContactRecord.value("LastName").toString());
    ui->EmailLineEdit->setText(ContactRecord.value("Email").toString());
    ui->PhoneHomeLineEdit->setText(ContactRecord.value("HomeNumber").toString());
    ui->PhoneMobileLineEdit->setText(ContactRecord.value("MobileNumber").toString());
    ui->PhoneWorkLineEdit->setText(ContactRecord.value("WorkNumber").toString());
    ui->AddressLineEdit->setText(ContactRecord.value("Address").toString());
    ui->CityLineEdit->setText(ContactRecord.value("City").toString());
    ui->StateLineEdit->setText(ContactRecord.value("State").toString());
    ui->ZipCodeLineEdit->setText(ContactRecord.value("Zip").toString());
    ui->CountryLineEdit->setText(ContactRecord.value("Country").toString());

    QStringList Date = ContactRecord.value("Birthdate").toString().split("-");
    if(Date.size()==3)
        /*This code generates an assert error. I'm not sure why it happens but it will need to be looked into late.*/

        ui->BirthdayDateEdit->setDate(QDate(Date.first().toInt(),Date.at(1).toInt(),Date.last().toInt()));
    else
        ui->BirthdayDateEdit->setDate(QDate(1,1,2000));
}

void Contacts::EditContact()
{
    if(SelectedRecordId!=-1)
        SetView(Contacts::View_EditContactView);
}

void Contacts::CancelEditContact()
{
    if(SelectedRecordId!=-1)
        this->DisplayContact(SelectedRecordIndex);
    else
        QMessageBox::warning(this,
                             tr("Unexpected Error"),
                             tr("Edit Contact Operation is being cancelled but no contact is selected."));
}

void Contacts::SaveContact()
{
    if(this->Validate())
    {
        if(SelectedRecordId!=-1)
            {QString Text = ui->NameLineEdit->text();
            QStringList Name = Text.split(" ");
            QString First_Name,Last_Name;
            if(Name.size()==1)
            {
                First_Name = Name.first();
                Last_Name = "";
            }else
            {
                First_Name = Name.first();
                Last_Name = Name.last();
            }

            QDate bdate = ui->BirthdayDateEdit->date();
            QString Date = QString::number(bdate.year()) + "-"+QString::number(bdate.month())+"-"+QString::number(bdate.day());


            QSqlQuery UpdateQuery;
            UpdateQuery.prepare("UPDATE Contacts SET FirstName=:f, LastName=:l, Email=:e, HomeNumber=:ph, WorkNumber=:pw, MobileNumber=:pm, Address=:a, City=:ct, State=:s, Zip=:z, Country=:c, Birthdate=:b WHERE Id=:i ;");
            UpdateQuery.bindValue(":f",First_Name);
            UpdateQuery.bindValue(":l",Last_Name);
            UpdateQuery.bindValue(":e",ui->EmailLineEdit->text());
            UpdateQuery.bindValue(":ph",ui->PhoneHomeLineEdit->text());
            UpdateQuery.bindValue(":pw",ui->PhoneWorkLineEdit->text());
            UpdateQuery.bindValue(":pm",ui->PhoneMobileLineEdit->text());
            UpdateQuery.bindValue(":a",ui->AddressLineEdit->text());
            UpdateQuery.bindValue(":ct",ui->CityLineEdit->text());
            UpdateQuery.bindValue(":s",ui->StateLineEdit->text());
            UpdateQuery.bindValue(":z",ui->ZipCodeLineEdit->text());
            UpdateQuery.bindValue(":c",ui->CountryLineEdit->text());
            UpdateQuery.bindValue(":b",Date);
            UpdateQuery.bindValue(":i",SelectedRecordId);

            if(!UpdateQuery.exec())
            {
                qDebug()<<"Update Error: "<<UpdateQuery.lastError().text();
                QMessageBox::warning(this,
                                     tr("Error"),
                                     tr("A problem occured while trying to save changes to \"%1 %2\".\nDetails: %3 ").arg(First_Name,Last_Name,UpdateQuery.lastError().text()));
            }else
            {
                QSqlQuery Query(ActiveQuery);
                Query.exec();
                Model->setQuery(Query);

                this->clear();
                DisplayContact(SelectedRecordIndex);
            }
        }else
           QMessageBox::warning(this,
                                 tr("Unexpected Error"),
                                 tr("Edit Contact Operation is being saved but no contact is selected."));
    }
}

void Contacts::RemoveContact()
{
    if(SelectedRecordId!=-1)
    {
        if(QMessageBox::information(this,
                                 tr("Remove Contact"),
                                 tr("Are you sure you want to remove this contact from your list?"),
                                 QMessageBox::Yes|QMessageBox::No)==QMessageBox::No)
            return;

        QSqlQuery DeleteQuery;
        DeleteQuery.prepare("DELETE FROM Contacts WHERE Id = :i;");
        DeleteQuery.bindValue(":i",SelectedRecordId);


        if(!DeleteQuery.exec())
        {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("A problem occured while trying to remove this contact.\nDetails: %1").arg(DeleteQuery.lastError().text()));
        }else
        {
            SelectedRecordId =-1;

            clear();
            SetView(Contacts::View_AddContactView);

            QSqlQuery Query(ActiveQuery);
            Query.exec();
            Model->setQuery(Query);

            UpdateContactCount();
        }
    }else
        QMessageBox::warning(this,
                              tr("Unexpected Error"),
                              tr("Remove Contact Operation is being attempted but no contact is selected."));
}

void Contacts::RemoveAllContacts()
{
    if(QMessageBox::warning(this,
                            tr("Remove All Contacts"),
                            tr("<b>WARNING</b>: All contacts will be permanenty deleted.<br/>Are you sure you want to proceed?"),
                            QMessageBox::Yes,QMessageBox::No)!=QMessageBox::Yes)
        return;


    QSqlQuery DeleteAllQuery;
    DeleteAllQuery.prepare("DELETE FROM Contacts");

    if(!DeleteAllQuery.exec())
    {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("A problem occurred while attempting to remove all contacts.\nDetails: %1").arg(DeleteAllQuery.lastError().text()));
    }else
    {
        QSqlQuery Query(ActiveQuery);
        Query.exec();
        Model->setQuery(Query);
        UpdateContactCount();
    }
}

void Contacts::ExportContact()
{
    if(SelectedRecordId!=-1)
    {
        exportDialog->setDefaultFileName(Model->record(SelectedRecordIndex.row()).value("FullName").toString());
        if(!exportDialog->exec()==QDialog::Accepted)
            return;

        QString fileName = exportDialog->exportLocation();
        if(fileName.isEmpty())
            return;
        exportAsVCF(fileName,SelectedRecordIndex.row(),SelectedRecordIndex.row()+1);
    }
}

void Contacts::on_actionExport_All_triggered()
{
    exportDialog->setDefaultFileName("Contacts");
    if(!exportDialog->exec()==QDialog::Accepted)
        return;

    QString fileName = exportDialog->exportLocation();
    if(fileName.isEmpty())
        return;

    exportAsVCF(fileName,0,Model->rowCount());

}

void Contacts::exportAsVCF(QString &filename, int record, int numberOfRecords)
{
    QFile vCard(filename);
    if(!vCard.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("A problem occured while trying to export contact(s).\nDetails: ").arg(vCard.errorString()));
        return;
    }

    QTextStream out(&vCard);
    for(int i=record;i<numberOfRecords;i++)
    {
        QSqlRecord record = Model->record(i);
        out<<"BEGIN:VCARD"<<"\n";
        out<<"VERSION:"<<"3.0"<<"\n";
        out<<"FN:"<<record.value("FullName").toString()<<"\n";
        out<<"N:"<<record.value("LastName").toString()<<";"<<record.value("FirstName").toString()<<";;;"<<"\n";
        out<<"EMAIL;TYPE=INTERNET:"<<record.value("Email").toString()<<"\n";
        out<<"TEL;TYPE=CELL:"<<record.value("MobileNumber").toString()<<"\n";
        out<<"TEL;TYPE=HOME:"<<record.value("HomeNumber").toString()<<"\n";
        out<<"TEL;TYPE=WORK:"<<record.value("WorkNumber").toString()<<"\n";
        out<<"ADR;TYPE=HOME:;"<<record.value("Address").toString()<<";";
        out<<record.value("City").toString()<<";";
        out<<record.value("State").toString()<<";";
        out<<record.value("Zip").toString()<<";";
        out<<record.value("Country").toString()<<"\n";
        out<<"BDAY:"<<record.value("Birthdate").toString()<<"\n";
        out<<"END:VCARD"<<"\n";
    }

    vCard.close();
    ui->statusBar->showMessage(tr("Contacts saved at %1 ").arg(filename),5000);
}

void Contacts::ImportContacts()
{
    if(!importDialog->exec()==QDialog::Accepted)
            return;

        QString filename = importDialog->importLocation();
        if(filename.isEmpty())
            return;

        vCardParser parser;
        parser.parsevCardFile(filename);

        QStringList details;
        QSqlQuery InsertQuery;
        int contactsImported=0;
        for(int i=0;i<parser.Contacts().size();i++)
        {
            details.clear();
            QMap<vCardParser::vCardProperty,QString> contactDetails = parser.Contacts().at(i);

            QStringList fullName = contactDetails[vCardParser::FullName].split(" ");

            if(fullName.size()>=2)
            {
                details.append(fullName.first());
                details.append(fullName.last());
            }else if(fullName.size()==1)
            {
                if(fullName.first().isEmpty())
                    continue;

                details.append(fullName.first());
                details.append(" ");
            }

            if(details.at(0).isEmpty() || details.at(1).isEmpty())
                break;

            details.append(contactDetails[vCardParser::Email]); //2
            details.append(contactDetails[vCardParser::PhoneNumberCell]);//3
            details.append(contactDetails[vCardParser::PhoneNumberHome]);//4
            details.append(contactDetails[vCardParser::PhoneNumberWork]);//5
            details.append(contactDetails[vCardParser::Address]);//6
            details.append(contactDetails[vCardParser::City]);//7
            details.append(contactDetails[vCardParser::State]);//8
            details.append(contactDetails[vCardParser::Zip]);//9
            details.append(contactDetails[vCardParser::Country]);//10
            details.append(contactDetails[vCardParser::Birthdate]);//11

            InsertQuery.prepare("INSERT INTO Contacts (FirstName,LastName,Email,HomeNumber,WorkNumber,MobileNumber,Address,City,State,Zip,Country,Birthdate) VALUES (:f,:l,:e,:ph,:pw,:pm,:a,:ct,:s,:z,:c,:b);");
            InsertQuery.bindValue(":f",details.at(0));
            InsertQuery.bindValue(":l",details.at(1));
            InsertQuery.bindValue(":e",details.at(2));
            InsertQuery.bindValue(":pm",details.at(3));
            InsertQuery.bindValue(":ph",details.at(4));
            InsertQuery.bindValue(":pw",details.at(5));
            InsertQuery.bindValue(":a",details.at(6));
            InsertQuery.bindValue(":ct",details.at(7));
            InsertQuery.bindValue(":s",details.at(8));
            InsertQuery.bindValue(":z",details.at(9));
            InsertQuery.bindValue(":c",details.at(10));
            InsertQuery.bindValue(":b",details.at(11));

            if(!InsertQuery.exec())
            {
                QMessageBox::warning(this,
                                     tr("Error"),
                                     tr("A problem occurred while trying to import contacts.\nDetails: %1").arg(InsertQuery.lastError().text()));
                return;
            }else
            {
                ui->statusBar->showMessage(tr("%1 Contact(s) Imported.").arg(++contactsImported),1000);
            }
        }

        //all contacts imported.
        Model->setQuery(DefaultModelQuery);
        clear();
        UpdateContactCount();
}


void Contacts::SearchContact()
{
    /*1. Read Search Term
      2. Decide Type
      3. Generate Query
      4. Execute Query.
      5. If No results, return
      6. If resutls, update Model, show first result.
      */

    //STEP 1: Read Search Term.
    QString SearchTerm = ui->SearchLineEdit->text();

    if(SearchTerm.isEmpty())
        return;

    /*STEP 2. Decide Type
      Type n : Name
      Type e : Email
      Type p : Number
      */
    char QueryType;

    if(SearchTerm.contains(QRegExp("[A-za-z-]+")))
    {
        if(SearchTerm.contains("@"))
            QueryType = 'e';
        else
            QueryType = 'n';
    }else if(SearchTerm.contains(QRegExp("[0-9]+")))
        QueryType = 'p';
    else
        QueryType = 'n';


    //STEP 3: Generate Query
    QSqlQuery SearchQuery;

    switch(QueryType)
    {
    case 'n':
    {
        QStringList Names = SearchTerm.split(" ");
        if(Names.size()>=2)
        {
            qDebug()<<QString("Searching for %1 %2").arg(Names.first(),Names.last());
            SearchQuery.prepare("SELECT Id,FirstName||' '||LastName AS FullName,FirstName,LastName,Email,HomeNumber,MobileNumber,WorkNumber,Address,City,State,Zip,Country,Birthdate FROM CONTACTS WHERE LOWER(FirstName)=:f AND LOWER(LastName)=:l ORDER BY FirstName");
            SearchQuery.bindValue(":f",Names.first().toLower());
            SearchQuery.bindValue(":l",Names.last().toLower());
        }else
        {
            qDebug()<<QString("Searching for %1").arg(Names.first());
            SearchQuery.prepare("SELECT Id,FirstName||' '||LastName AS FullName,FirstName,LastName,Email,HomeNumber,MobileNumber,WorkNumber,Address,City,State,Zip,Country,Birthdate FROM CONTACTS WHERE LOWER(FirstName)=:f OR LOWER(LastName)=:l ORDER BY FirstName");
            SearchQuery.bindValue(":f",Names.first().toLower());
            SearchQuery.bindValue(":l",Names.first().toLower());
        }
        break;
    }

    case 'e':
    {
        QString Email = SearchTerm.trimmed();
        SearchQuery.prepare("SELECT Id,FirstName||' '||LastName AS FullName,FirstName,LastName,Email,HomeNumber,MobileNumber,WorkNumber,Address,City,State,Zip,Country,Birthdate FROM CONTACTS WHERE LOWER(Email)=:e ORDER BY FirstName");
        SearchQuery.bindValue(":e",Email.toLower());
        break;
    }

    case 'p':
    {
        QString Number = SearchTerm.trimmed();
        SearchQuery.prepare("SELECT Id,FirstName||' '||LastName AS FullName,FirstName,LastName,Email,HomeNumber,MobileNumber,WorkNumber,Address,City,State,Zip,Country,Birthdate FROM CONTACTS WHERE HomeNumber=:h OR WorkNumber=:w OR MobileNumber=:m ORDER BY FirstName");
        SearchQuery.bindValue(":h",Number);
        SearchQuery.bindValue(":m",Number);
        SearchQuery.bindValue(":w",Number);
        break;
    }
    }

    //STEP 4: Execute Query
    if(!SearchQuery.exec())
    {
        qDebug()<<QueryType<<": "<<SearchQuery.lastError().text();
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("An error occured while trying to search contacts:\nDetails: %1").arg(SearchQuery.lastError().text()));
        return;
    }

    //STEP 5: If no results, return;

    /*Note:
    I used the QSqlQuery::first() method here to check if there are any result or not.
    I doubt this is efficient, because the function probably invovles unnecessary steps & resources.
    So the following code could be made more efficient.

    I can't use QSqlQuery::size() because it always returns -1.
      */

    if(!SearchQuery.first())
    {
        QMessageBox::information(this,
                                 tr("Search"),
                                 tr("No results were found for \"%1\"").arg(SearchTerm));
        return;
    }

    //STEP 6: If results, update model, show first result.
    ActiveQuery = SearchQuery;
    Model->setQuery(SearchQuery);

    QModelIndex index = Model->index(0,1);
    DisplayContact(index);

    SetView(Contacts::View_DisplaySearchResultsView);
}

void Contacts::ReturnFromSearchResults()
{
    clear();
    ui->SearchLineEdit->clear();

    SearchInProgress = false;
    SetView(Contacts::View_AddContactView);

    ActiveQuery.exec(DefaultModelQuery);
    Model->setQuery(ActiveQuery);
}

void Contacts::UpdateContactCount()
{
    ui->ContactCountLabel->setText(tr("%1 %2").arg(
                                       QString::number(Model->rowCount()),
                                       Model->rowCount()==1?tr("Contact"):tr("Contacts")));
}

void Contacts::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void Contacts::on_actionQuit_triggered()
{
    qApp->quit();
}


void Contacts::on_actionAbout_Contacts_triggered()
{
    aboutDialog->exec();
}
