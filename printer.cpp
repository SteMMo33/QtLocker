/**
  Supporto per la stampa dello scontrino
  Utilizzo stampa CUPS
*/


#include "printer.h"


/**
 * @brief printer::printer
 * Costruttore
 */
Printer::Printer()
{
    qDebug() << "C'tor printer";

    QPrinter printer;

    QPrinterInfo* info = new QPrinterInfo();
    qDebug() << "Default printer: " << info->defaultPrinter().description();
    qDebug() << "PID: " << info->description();

    QStringList printers = info->availablePrinterNames();
    for(int i=0; i < printers.size(); i++){
        qDebug() << "P: " << printers.at(i);
    }

    /* QList<QPrinterInfo> infos = info->availablePrinters();
    for(int i=0; i < infos.size(); i++){
        qDebug() << "I: " << info->makeAndModel();
    } */
}

