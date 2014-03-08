//			###############################################################################
//			##
//			##	
//			##			Filename:  	crypto.cpp
//			##			Classname: 	Crypto
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#include "crypto.h"
#include "ui_crypto.h"

Crypto::Crypto(QWidget *parent) : QMainWindow(parent), ui(new Ui::Crypto)
{
    ui->setupUi(this);
}

void Crypto::init(QStringList params){
    if (params.size() > 0) {
        for (int i = 0; i < params.size(); ++i) {
            QString param = params.at(i);
            if(param.at(0) == QChar('-')){
                if(!param.compare("-file", Qt::CaseInsensitive)){
                    qDebug() << params.at(i+1);
                } else if(!param.compare("-folder", Qt::CaseInsensitive)){
                    qDebug() << "Folder: " << params.at(i+1);
                    folder = params.at(i+1);
                } else if(!param.compare("-pwd", Qt::CaseInsensitive)){
                    qDebug() << "Pass: " << params.at(i+1);
                    pass = params.at(i+1);
                }
//                else if(!param.compare("-outfolder", Qt::CaseInsensitive)){
//                    qDebug() << params.at(i+1);
//                } else if(!param.compare("-infolder", Qt::CaseInsensitive)){
//                    qDebug() << params.at(i+1);
//                }
            }
        }
    }

    if(pass == "" || folder == ""){
        qDebug() << "exit";
        emit lostData(QString("hiányzó adat"));
    }


    AbstractTypes *txt = new typeText();
    interfaces.insert("txt", txt);
    interfaces.insert("h",   txt);
    interfaces.insert("cpp", txt);
    interfaces.insert("gui", txt);
    interfaces.insert("pl",  txt);
    interfaces.insert("css", txt);

    QCA::init();

    if(!QCA::isSupported("sha512")){
        qDebug()<<"Error! SHA-512 algorithm is not supported!";
    }

    if(!QCA::isSupported("aes256-cbc")){
        qDebug()<<"Error! aes256-cbc algorithm is not supported!";
    }

    show();
}

Crypto::~Crypto()
{
    delete ui;
}

QByteArray Crypto::hash(QByteArray data){
    QCA::Hash hash("sha512");
    hash.update(data);
    return hash.final().toByteArray();
}

QList<QByteArray> Crypto::split(QByteArray data, int length){
    QList<QByteArray> lista;

    for(int i=0;i<=data.size()/length;i++){
        lista.append(data.mid(i*length, length));
    }
    return lista;
}

void Crypto::encryptFile(QFileInfo file){
    AbstractTypes *obj = interfaces.value(QString(file.suffix()));
    if(obj!=NULL){
        QByteArray out = obj->readText(PATH+folder+file.fileName()).toUtf8().toBase64();
        writeBinary(encrypt(out, pass), PATH+folder+file.fileName());
    }
}

void Crypto::encryptFolder(){
    QDir dir(PATH+folder);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        encryptFile(list.at(i));
    }
}

void Crypto::writeBinary(QByteArray arr, QString filePath){
    QFile f(filePath + OUTFORMAT);

    f.open(QIODevice::WriteOnly);
    QDataStream out(&f);
    out.setByteOrder(QDataStream::LittleEndian); // *** set little endian byte order
    out<<arr;

    f.close();
}


QByteArray Crypto::readBinary(QString filePath){
    QFile f(filePath + OUTFORMAT);

    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian); // *** set little endian byte order

    QByteArray arr;
    in>>arr;

    f.close();

    return arr;
}

QByteArray Crypto::encrypt(QByteArray data, QString _pass){
    QByteArray chiperKey = hash(_pass.toLocal8Bit());
    key =  QCA::SymmetricKey(chiperKey.left(64));
    iv = QCA::InitializationVector(chiperKey.right(64));
    QCA::Cipher cipher(CODEC,QCA::Cipher::CBC,QCA::Cipher::DefaultPadding, QCA::Encode,key, iv);

    QList<QByteArray> lista = split(data, 15);

    QCA::SecureArray encrypted;
    foreach (QByteArray item, lista) {
        cipher.setup(QCA::Encode, key, iv);
        QCA::SecureArray secureData = cipher.update(item);
        QCA::SecureArray encryptedData = cipher.final();
        if (!cipher.ok()) {
            qDebug() << "Encryption failed !";
            return "";
        }
        encrypted.append(encryptedData);
    }
    return encrypted.toByteArray();
}

QByteArray Crypto::decrypt(QByteArray data, QString _pass){
    QByteArray chiperKey = hash(_pass.toLocal8Bit());
    key =  QCA::SymmetricKey(chiperKey.left(64));
    iv = QCA::InitializationVector(chiperKey.right(64));
    QCA::Cipher cipher = QCA::Cipher(CODEC,QCA::Cipher::CBC,QCA::Cipher::DefaultPadding, QCA::Decode,key,iv);

    QList<QByteArray> lista = split(data, 16);
    QCA::SecureArray encrypted;
    foreach (QByteArray item, lista) {
        if(item.size()>0){
            cipher.setup(QCA::Decode, key, iv);
            QCA::SecureArray encryptedData = cipher.process(item);
            if (!cipher.ok()) {
                qDebug() << "Decryption failed !";
                return "";
            }
            encrypted.append(encryptedData);
        }
    }
    return QString(encrypted.data()).toUtf8();
}
