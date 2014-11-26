#include <QtGui/QApplication>
#include "contacts.h"
#define APPLICATION_NAME "ContactBook"
#define APPLICATION_VERSION "Version 1.0"
#define ORGANIZATION_NAME "Waqqas K"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(APPLICATION_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    Contacts w;
    w.show();

    return a.exec();
}
