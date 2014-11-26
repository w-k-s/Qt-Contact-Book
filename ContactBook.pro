#-------------------------------------------------
#
# Project created by QtCreator 2012-06-27T00:48:53
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ContactBook
TEMPLATE = app


SOURCES += main.cpp\
        contacts.cpp\
	ExportDialog.cpp\
	ImportDialog.cpp\
	vcardparser.cpp\
	AboutDialog.cpp

HEADERS  += contacts.h\
	ExportDialog.h\
	ImportDialog.h\
	vcardparser.h\
	AboutDialog.h

FORMS    += contacts.ui\	
	ExportDialog.ui\
	ImportDialog.ui\
	AboutDialog.ui

RESOURCES += Resources.qrc

RC_FILE = icon.rc