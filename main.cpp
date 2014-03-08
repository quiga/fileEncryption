//			###############################################################################
//			##
//			##	
//			##			Filename:  	main.cpp
//			##			Classname: 	
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#include "crypto.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Crypto c;
    QObject::connect(&c, SIGNAL(lostData(QString)), &a, SLOT(quit()));

    c.init(a.arguments());


    /*
    QByteArray out = readText(PATH + QString("temp.txt")).trimmed().toUtf8();

    QByteArray outBase64 = out.toBase64();

    writeBinary(encrypt(outBase64, pass), PATH + QString("temp"));

    QByteArray in;
    QByteArray inBase64;
    inBase64 = decrypt(readBinary(PATH + QString("temp")), pass);
    in =  QByteArray::fromBase64(inBase64);
    //qDebug()<<inBase64;
    //qDebug()<<in;
    writeText(in, PATH + QString("temp_2.txt"));
    //qDebug()<<in;
*/

    return a.exec();
}



