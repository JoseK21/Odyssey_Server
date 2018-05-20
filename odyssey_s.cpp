#include "odyssey_s.h"
#include "ui_odyssey_s.h"

#include <QNetworkInterface>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonDocument>
#include <string.h>
#include <iostream>
#include <fstream>



QString xml;
QString xml2;
QString folder1 = "/home/josek/FolderOdyssey";
QString folder2 =  "/home/josek/FolderOdyssey/AudioFile";
std::string user = "/home/josek/FolderOdyssey/Users.json";

std::ofstream ficheroSalida;

int j=0;
Odyssey_S::Odyssey_S(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Odyssey_S)
{

    createFile();
    ui->setupUi(this);
    tcpservidor = new QTcpServer(this);
    tcpservidor->setMaxPendingConnections(3);
    for(int i = 0; i< tcpservidor->maxPendingConnections();i++){
        tcpcliente[i] = new QTcpSocket(this);
    }

    QHostAddress hostadd("192.168.0.109");
            tcpservidor->listen(hostadd,8888);
            connect(tcpservidor,SIGNAL(newConnection()),this, SLOT(conexion_nueva()));


}

/**
 * @brief Método para borrar la llamada de la creación de la ventana
 *
 */
Odyssey_S::~Odyssey_S()
{
    delete ui;
}


void Odyssey_S::createFile(){
   if (QDir(folder1).exists() == false){
       QDir().mkdir(folder1);
       std::ofstream userFile(user);
       userFile.close();

       qDebug()<<"FolderOdyssey created with Users.json";

       if (QDir(folder2).exists() == false){
           QDir().mkdir(folder2);
           std::string metadata = folder2.append("/Metadata.json").toStdString();
           std::ofstream metadataFile(metadata);
           metadataFile.close();
           qDebug()<<"AudioFile created with Metadata.json";
       }
   }


}

/**
 * @brief Método para crear una nueva conexión
 *
 */
void Odyssey_S::conexion_nueva(){


    if(j==0){
        tcpcliente[j] = tcpservidor->nextPendingConnection();
        connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketLogin()));
        ui->label_Custumer->setText("Connected : Login");
        qDebug()<< "j: "+j;


    }
    if(j==1){
        tcpcliente[j] = tcpservidor->nextPendingConnection();
        connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketSingin()));
        ui->label_Custumer->setText("Connected : Sig in");
        qDebug()<< "j: "+j;


    }
    if(j==2){
        tcpcliente[j] = tcpservidor->nextPendingConnection();
        connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketcliente()));
        ui->label_Custumer->setText("Connected : Interface");
        qDebug()<< "j: "+j;


    }

    j++;
}

/**
 * @brief Método hacer la comunicación del socket Login_Server
 *
 */
void Odyssey_S::leer_socketLogin() {       //Recibe los datos del cliente
    if(tcpcliente[0]->bytesAvailable() > 0){
        qDebug() << "Socket Login ";
        QByteArray buffer;
        buffer.resize( tcpcliente[0]->bytesAvailable());
        tcpcliente[0]->read( buffer.data(),buffer.size() );

        if(QString (buffer)!="\n"){ //Condición para no pasar "basura" del socket
            ui->plainTextEdit->setReadOnly(true);
            ui->plainTextEdit->appendPlainText("Login :"+ QString(buffer));
        xml = QString (buffer)+"\n";

        QString uSerLogin,fuSerLogin= "";

        QString input(buffer);
        QByteArray bytes = input.toUtf8();
        QDomDocument doc;
        doc.setContent(bytes);
        QDomNodeList start;
        int length=0;
        int lengthInner;
        start = doc.elementsByTagName("username");
        length = start.length();

        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Username: " << attribute.value();
                uSerLogin=attribute.value();
            }
        }
        start = doc.elementsByTagName("fullname");
        length = start.length();
        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Fullname: " << attribute.value();
                fuSerLogin=attribute.value();
            }
        }


        //Intento de cargar desde el archivo .json
/*

        QFile file("/home/josek/FolderOdyssey/Users.json");
           if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << "file error";
               return;
           }
           const QByteArray ba = file.readAll();
           file.close();

           QJsonParseError err;
           QJsonDocument docm = QJsonDocument::fromJson(ba, &err);

           QJsonObject json = docm.object();


 QJsonValue values = json.value(QString("Age"));
QJsonObject items = values.toObject();

           qDebug() << values.toArray();

           qWarning() << tr("client") << item["description"];
                 QJsonValue subobj = item["description"];
                 qWarning() << subobj.toString();


               foreach(const QString& key, json.keys()) {
                   QJsonValue value = json.value(QString("UserName"));
                   qDebug() << "Key = " << key << ", Value = " ;
               }


               */

        tcpcliente[0]->write( xml.toLatin1().data() , xml.toLatin1().size());
        }
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion <socket Login>");
    }

    //QString toclient  = "<client><username>"+uSerLogin+"</username><password>"+fuSerLogin+"</password><acces>"+acces+"</acces></client>";



}

/**
 * @brief Método hacer la comunicación del socket Singin_Server
 *
 */
void Odyssey_S::leer_socketSingin() {       //Recibe los datos del cliente
    if(tcpcliente[1]->bytesAvailable() > 0){
        QByteArray buffer;
        buffer.resize( tcpcliente[1]->bytesAvailable());
        tcpcliente[1]->read( buffer.data(),buffer.size() );     //lee los datos del cliente
        if(QString (buffer)!="\n"){ //Condición para no pasar "basura" del socket
            ui->plainTextEdit->setReadOnly(true);
            ui->plainTextEdit->appendPlainText("Sing_In > "+ QString(buffer));
        xml = QString (buffer)+"\n";
        xml2= QString(buffer);

        QString nada = QString("SI")+"\n";

        QString uSer,fuSer,aSer,pSer,gSer,fSer = "";

        QString input(buffer);
        QByteArray bytes = input.toUtf8();
        QDomDocument doc;
        doc.setContent(bytes);
        QDomNodeList start;
        int length=0;
        int lengthInner;
        start = doc.elementsByTagName("username");
        length = start.length();

        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Username: " << attribute.value();
                uSer=attribute.value();
            }
        }
        start = doc.elementsByTagName("fullname");
        length = start.length();
        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Fullname: " << attribute.value();
                fuSer=attribute.value();
            }
        }

        doc.setContent(bytes);
        start = doc.elementsByTagName("age");
        length = start.length();
        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Age: " << attribute.value();
                aSer=attribute.value();
            }

        }

        start = doc.elementsByTagName("password");
        length = start.length();
        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Password: " << attribute.value();
                pSer=attribute.value();
            }
        }

        start= doc.elementsByTagName("genre");
        length = start.length();

        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Genre: " << attribute.value();
                gSer=attribute.value();
            }
        }

        start = doc.elementsByTagName("friends");
        length = start.length();
        for (int i = 0; i < length; i++){
            auto node = start.at(i);
            auto map = node.attributes();
            lengthInner = map.length();
            for (int j = 0; j < lengthInner; j++){
                auto mapItem = map.item(j);
                auto attribute = mapItem.toAttr();
                qDebug() << "Friends: " << attribute.value();
                fSer=attribute.value();
            }
        }

        QJsonObject addressObject;
        addressObject.insert("UserName", uSer);
        addressObject.insert("Fullname", fuSer);
        addressObject.insert("Age", aSer);
        addressObject.insert("Password", pSer);



        QJsonArray friendArray;

        QStringList list = fSer.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        qDebug() << "Amigos:";
        for(int o =0; o<list.length();o++){
            qDebug() << list[o];
            friendArray.push_back(list[o]);
        }
        addressObject.insert("Friends", friendArray);

        QJsonArray genreArray;
        qDebug() << "generos:";
        QStringList list1 = gSer.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for(int o =0; o<list1.length();o++){
            qDebug() << list1[o];
            genreArray.push_back(list1[o]);
        }
        addressObject.insert("Genre", genreArray);




        QJsonDocument docXML(addressObject);
            qDebug() << docXML.toJson();


        std::ofstream userFile(user,std::ostream::app);

        userFile << docXML.toJson().toStdString() << std::endl;

        userFile.close();
        //tcpcliente[1]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
        tcpcliente[1]->write( nada.toLatin1().data() , nada.toLatin1().size()); //envio datos al cliente
        }
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion <socket Sing in> ");
    }
}

/**
 * @brief Método hacer la comunicación del socket Cliente/Interface_Server
 *
 */
void Odyssey_S::leer_socketcliente() {       //Recibe los datos del cliente
    if(tcpcliente[2]->bytesAvailable() > 0){
        qDebug() << "Socket Main Interface ";
        ui->plainTextEdit->appendPlainText("Main Interface*");

        QByteArray buffer;
        buffer.resize( tcpcliente[2]->bytesAvailable());
        tcpcliente[2]->read( buffer.data(),buffer.size() );
        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->appendPlainText( QString(buffer));
        xml = QString (buffer)+"\n";


        QString inputC1(buffer);
        QByteArray bytesC1 = inputC1.toUtf8();
            QDomDocument doc;
            doc.setContent(bytesC1);
            QDomNodeList start = doc.elementsByTagName("password");
            int length = start.length();
            int lengthInner;
            for (int i = 0; i < length; i++){
                auto node = start.at(i);
                auto map = node.attributes();
                lengthInner = map.length();
                for (int j = 0; j < lengthInner; j++){
                    auto mapItem = map.item(j);
                    auto attribute = mapItem.toAttr();
                    qDebug() << "Value: " << attribute.value();
                }
        }

        tcpcliente[2]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion <socket  Main Interface>");
    }
}

