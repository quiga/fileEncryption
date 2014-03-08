//			###############################################################################
//			##
//			##	
//			##			Filename:  	typetext.cpp
//			##			Classname: 	typeText
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#include "typetext.h"

typeText::typeText(){}


QString typeText::readText(QString filePath){
    QFile inputFile(filePath);

    QString text = "";
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        in.setCodec("UTF-8");
        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            text.append('\n');
            text.append(line);
        }
        inputFile.close();
    }
    return text;
}


QString typeText::writeText(QString filePath, QByteArray data){
    QFile outFile(filePath);

    QString text = "";
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&outFile);
        out.setCodec("UTF-8");
        out<<QString(data);

        outFile.close();
    }
    return text;
}
