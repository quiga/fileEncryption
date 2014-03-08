//			###############################################################################
//			##
//			##	
//			##			Filename:  	typetext.h
//			##			Classname: 	typeText
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#ifndef TYPETEXT_H
#define TYPETEXT_H

#include "abstractTypes.h"
#include <QDataStream>
#include <QFile>
#include <QTextStream>

class typeText : public AbstractTypes
{
    Q_OBJECT
public:
    typeText();
    QString readText(QString filePath);
    QString writeText(QString filePath, QByteArray data);
    
signals:
    
public slots:
    
};

#endif // TYPETEXT_H
