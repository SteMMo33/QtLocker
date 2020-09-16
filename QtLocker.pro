QT += quick sql websockets serialport printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cassetti.cpp \
    datasource.cpp \
    main.cpp \
    pos.cpp \
    prenotazioni.cpp \
    printer.cpp \
    sendemail.cpp \
    settings.cpp \
    ioboard.cpp \
    smtp/emailaddress.cpp \
    smtp/mimeattachment.cpp \
    smtp/mimecontentformatter.cpp \
    smtp/mimefile.cpp \
    smtp/mimehtml.cpp \
    smtp/mimeinlinefile.cpp \
    smtp/mimemessage.cpp \
    smtp/mimemultipart.cpp \
    smtp/mimepart.cpp \
    smtp/mimetext.cpp \
    smtp/quotedprintable.cpp \
    smtp/smtpclient.cpp

RESOURCES += qml.qrc

OBJECTS_DIR = obj
MOC_DIR = moc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    cassetti.h \
    datasource.h \
    pos.h \
    prenotazioni.h \
    printer.h \
    sendemail.h \
    settings.h \
    ioboard.h \
    smtp/SmtpMime \
    smtp/emailaddress.h \
    smtp/mimeattachment.h \
    smtp/mimecontentformatter.h \
    smtp/mimefile.h \
    smtp/mimehtml.h \
    smtp/mimeinlinefile.h \
    smtp/mimemessage.h \
    smtp/mimemultipart.h \
    smtp/mimepart.h \
    smtp/mimetext.h \
    smtp/quotedprintable.h \
    smtp/smtpclient.h \
    smtp/smtpexports.h
