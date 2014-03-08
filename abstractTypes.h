//			###############################################################################
//			##
//			##	
//			##			Filename:  	abstractTypes.h
//			##			Classname: 	
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#ifndef ABSTRACTTYPES_H
#define ABSTRACTTYPES_H

#include <QObject>

class AbstractTypes:public QObject{
    Q_OBJECT

public:
    virtual QString readText(QString filePath)=0;
    virtual QString writeText(QString filePath, QByteArray data)=0;
};

#endif // ABSTRACTTYPES_H
