#include "vcardparser.h"
#include <QFile>
#include <QtDebug>
#include <QStringList>

#define BEGIN_TOKEN "BEGIN"
#define END_TOKEN "END"
#define VCARD_TOKEN "VCARD"
#define VERSION_TOKEN "VERSION"
#define SUPPORTED_VERSION 3

vCardParser::vCardParser()
{
}

void vCardParser::parsevCardFile(const QString &fileName)
{
    if(!fileName.endsWith(".vcf",Qt::CaseInsensitive))
    {
        qDebug()<<"File does not have a .vcf extension. No assurance that file is of a valid type.\n";
        return;
    }

    m_contacts.clear();

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString line;
        while(!in.atEnd())
        {
            /*
                In a vCard file, each line consists of three parts
                - field_name //e.g. FN,N,EMAIL,ADR
                - field type//e.g. type=CELL,type=HOME
                - field_data//e.g. Joe Bloggs, joebloggs@gmail.com
                By splitting each line at the : symbol, we get field_name & field type in the first token (calls LeftHandSide),
                and we get the field_data in the second token (called RightHandSide).

                In the LeftHandSide:
                By splitting the string at the first ; symbol, we get field_name in the first token (called field_name)
                and all field types in the second token (called field_types)

                In the RightHandSide:
                By splitting the string at each ; symbol,we get different parts of the field_data.

                THEREFORE

                STEPS
                1. get line
                2. split line in two: leftHandSide and rightHandSide
                3. if leftHandSide == BEGIN, and rightHandSide == VCARD -> do nothing
                4. if leftHandSide == END, and rightHandSide == VCARD -> add to vector
                5. if leftHandSide == VERSION, conbert rightHandSide to float and make sure its three. if not issue warning
                6. if anything else,
                    if leftHandSide contains ";", split into lleftHandSide rleftHandSide.
                    pass to vCard.assigner(lleftHandSide,rleftHandSide,rightHandSide)
                    the assigner will do the rest of the parsing.

                The job of the assigner is to save the read the field_name and field_types and thus, store the field_data
                in the correct variable in the vCard struct.

            */

            //STEP 1:
            line = in.readLine();

            //STEP 2:

            QStringList tokens = line.split(":");

            //std::cout<<"leftHandSide: "<<leftHandSide<<"\t"<<"rightHandSide:"<<rightHandSide<<"\n";

            //STEP 3:
            if((tokens.at(0)=="BEGIN")/* && (rightHandSide=="VCARD")*/)
            {
                //new contact
                clear();
            }else if((tokens.at(0)=="END")/* && (rightHandSide=="VCARD")*/)
            {
                //std::cout<<"------------------------------------------------\n";
                m_contacts.push_back(m_currentCard);
            }else if(tokens.at(0)=="VERSION")
            {
                if(tokens.last().toFloat()==SUPPORTED_VERSION)
                    qDebug()<<"vCard Format is version "<<tokens.last()<<" which may cause problems.\n";
            }else
            {
                QString fieldName,fieldTypes,fieldData;
                fieldData = tokens.last();
                QStringList leftHandSide = tokens.at(0).split(";");
                fieldName = leftHandSide.first();
                fieldTypes = leftHandSide.join("");

                assigner(fieldName,fieldTypes,fieldData);
            }

        }
        file.close();
    }else
    {
        qDebug()<<"Unable to open file.\n";
        return;
    }

    return;
}

const QVector<QMap<vCardParser::vCardProperty, QString> > &vCardParser::Contacts()
{
    return m_contacts;
}

void vCardParser::clear()
{    
    m_currentCard[vCardParser::FullName]="";
    m_currentCard[vCardParser::Organisation]="";
    m_currentCard[vCardParser::Title]="";
    m_currentCard[vCardParser::Email]="";
    m_currentCard[vCardParser::EmailWork]="";

    m_currentCard[vCardParser::PhoneNumberCell]="";
    m_currentCard[vCardParser::PhoneNumberHome]="";
    m_currentCard[vCardParser::PhoneNumberWork]="";
    m_currentCard[vCardParser::Address]="";
    m_currentCard[vCardParser::City]="";

    m_currentCard[vCardParser::State]="";
    m_currentCard[vCardParser::Zip]="";
    m_currentCard[vCardParser::Country]="";
    m_currentCard[vCardParser::Birthdate]="";
}

void vCardParser::assigner(QString &fieldName, QString &fieldTypes, QString &fieldData)
{
    if(fieldName=="FN")
    {
        m_currentCard[vCardParser::FullName]=fieldData;
    }else if(fieldName=="N")
    {
        //Do nothing.
    }else if(fieldName=="ORG")
    {
        m_currentCard[vCardParser::Organisation]=fieldData;
    }else if(fieldName=="TITLE")
    {
        m_currentCard[vCardParser::Title] = fieldData;
    }else if(fieldName=="EMAIL")
    {
        if(fieldTypes.contains("WORK",Qt::CaseInsensitive))
            m_currentCard[vCardParser::EmailWork]=fieldData;
        else
            m_currentCard[vCardParser::Email]=fieldData;
    }else if(fieldName=="TEL")
    {
        if(fieldTypes.contains("WORK",Qt::CaseInsensitive))
        {
            m_currentCard[vCardParser::PhoneNumberWork]=fieldData;
        }else if(fieldTypes.contains("HOME",Qt::CaseInsensitive))
        {
            m_currentCard[vCardParser::PhoneNumberHome]=fieldData;
        }else
            m_currentCard[vCardParser::PhoneNumberCell]=fieldData;
    }else if(fieldName=="ADR")
    {
        //e.g. ADR;TYPE=WORK:;;100 Waters Edge;Baytown;LA;30314;United States of America
        QStringList tokens = fieldData.split(";");
        for(int i=0;i<tokens.length();i++)
            tokens[i].remove("\\");
        while(tokens[0].isEmpty())
            tokens.removeAt(0);

        if(tokens.size()>=5)
        {
            m_currentCard[vCardParser::Address]=tokens.at(0);
            m_currentCard[vCardParser::City]=tokens.at(1);
            m_currentCard[vCardParser::State]=tokens.at(2);
            m_currentCard[vCardParser::Zip] = tokens.at(3);
            m_currentCard[vCardParser::Country] = tokens.at(4);
        }else
        {
            qDebug()<<"Error parsing this address: "<<fieldData<<"\n";
            m_currentCard[vCardParser::Address]=tokens.join(" ");
        }
    }else if(fieldName=="BDAY")
    {
        m_currentCard[vCardParser::Birthdate]=fieldData;
    }else
    {
        qDebug()<<"Notice: The following data could not be handled parser: "<<fieldName<<fieldTypes<<fieldData<<"\n";
    }
}


