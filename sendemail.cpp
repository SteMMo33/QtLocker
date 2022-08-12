#include "sendemail.h"

SendEmail::SendEmail()
{
    qDebug() << "[SendEmail] C'tor";
}



/**
 * @brief SendEmail::send
 * Invio email
 * @return
 */
int SendEmail::send()
{
    qDebug() << "[SendEmail] send";

    // First we need to create an SmtpClient object
    SmtpClient smtp("cp3.pcsgroup.solutions", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and password
    // for smtp authentification.
    smtp.setUser("atk");
    smtp.setPassword("AmteK_2017$");

    // Now we create a MimeMessage object. This is the email.
    MimeMessage message;

    EmailAddress sender("s.mora@amtek.it", "QT Kiosk");
    message.setSender(&sender);

    EmailAddress to("s.mora@amtek.it", "Kiosk user");
    message.addRecipient(&to);

    message.setSubject("Notifica dal Locker");

    // Now add some text to the email.
    // First we create a MimeText object.
    MimeText text;
    text.setText("NOTIFICA DAL LOCKER AMtek,\n\nSemplice notifca dal Locker AMtek.\nGrazie per l'attenzione\n\n");

    // Now add it to the mail
    message.addPart(&text);

    // Now we can send the mail
    if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        return -1;
    }

    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;
        return -2;
    }

    if (!smtp.sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return -3;
    }

    smtp.quit();
    return 1;
}
