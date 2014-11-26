#ifndef CONTACTS_H
#define CONTACTS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QModelIndex>
#include <QSqlQuery>
class QSqlQueryModel;
class ExportDialog;
class ImportDialog;
class AboutDialog;

namespace Ui {
    class Contacts;
}

class Contacts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Contacts(QWidget *parent = 0);
    enum View{View_AddContactView,
              View_DisplayContactView,
              View_EditContactView,
              View_DisplaySearchResultsView};
    void clear();
    View getView();
    bool Validate();
    void SetView(Contacts::View);

    ~Contacts();

public slots:
    void AddContact();
    void DisplayContact(QModelIndex);
    void EditContact();
    void CancelEditContact();
    void SaveContact();
    void RemoveContact();
    void RemoveAllContacts();
    void SearchContact();
    void ExportContact();
    void ImportContacts();
    void ReturnFromSearchResults();
    void UpdateContactCount();

private slots:
    void on_actionAbout_Qt_triggered();
    void on_actionQuit_triggered();
    void on_actionExport_All_triggered();

    void on_actionAbout_Contacts_triggered();

private:
    enum ExportMode{ExportMode_ExportAllContacts,ExportMode_ExportOneContact};
    void OpenDatabase();
    void exportAsVCF(QString&,int,int);
    void Test();

    Ui::Contacts*   ui;
    QSqlQueryModel* Model;
    QSqlDatabase    db;
    QSqlQuery       ActiveQuery;
    QString         DefaultModelQuery;
    View            view;
    QModelIndex     SelectedRecordIndex; /* Perhaps, one of these is unnecessary*/
    ExportDialog*   exportDialog;
    ImportDialog*   importDialog;
    AboutDialog*    aboutDialog;

    int             SelectedRecordId;
    bool            SearchInProgress;

};

#endif // CONTACTS_H
