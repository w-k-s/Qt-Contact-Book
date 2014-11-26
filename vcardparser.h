#ifndef VCARDPARSER_H
#define VCARDPARSER_H

#include <QString>
#include <QVector>
#include <QMap>

class vCardParser
{
public:
    vCardParser();
    void parsevCardFile(const QString&);
    enum vCardProperty{FullName,
                       Organisation,
                       Title,
                       EmailWork,
                       Email,
                       PhoneNumberCell,
                       PhoneNumberHome,
                       PhoneNumberWork,
                       Address,
                       City,
                       State,
                       Zip,
                       Country,
                       Birthdate
    };
    const QVector < QMap <vCardProperty, QString> >& Contacts();

private:
    void clear();
    void assigner(QString&,QString&,QString&);
    QVector < QMap <vCardProperty, QString> > m_contacts;
    QMap<vCardProperty,QString> m_currentCard;
};

#endif // VCARDPARSER_H
