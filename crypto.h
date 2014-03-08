//			###############################################################################
//			##
//			##	
//			##			Filename:  	crypto.h
//			##			Classname: 	Crypto
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#ifndef CRYPTO_H
#define CRYPTO_H

#include <QMainWindow>
#include <QtCrypto/QtCrypto>
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <QMap>
#include "abstractTypes.h"
#include "typetext.h"

#define CODEC "aes256"
#define PATH "/home/quiga/"
#define OUTFORMAT ".dat"

namespace Ui {
class Crypto;
}

class Crypto : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Crypto(QWidget *parent = 0);
    ~Crypto();

    void encryptFolder();
    void encryptFile(QFileInfo file);
    void init(QStringList params);

signals:
    void lostData(QString msg);



private:
    Ui::Crypto *ui;
    QCA::SymmetricKey key;
    QCA::InitializationVector iv;

    QMap<QString, AbstractTypes* > interfaces;
    QList<QByteArray> split(QByteArray data, int length);
    void writeBinary(QByteArray arr, QString filePath);
    QByteArray readBinary(QString filePath);
    QByteArray encrypt(QByteArray data, QString _pass);
    QByteArray decrypt(QByteArray data, QString _pass);
    QByteArray hash(QByteArray data);

    QString pass;
    QString folder;
};

#endif // CRYPTO_H
