#include "odyssey_s.h"
#include "ui_odyssey_s.h"

#include <QNetworkInterface>
#include <QtCore>
#include <QtXml>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <string.h>
#include <iostream>
#include <fstream>



QString xml;
QString folder1 = "/home/josek/FolderOdyssey";
QString folder2 =  "/home/josek/FolderOdyssey/AudioFile";


int j=0;
Odyssey_S::Odyssey_S(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Odyssey_S)
{

    createFile();
/*
    ui->setupUi(this);
    tcpservidor = new QTcpServer(this);
    tcpservidor->setMaxPendingConnections(3);
    for(int i = 0; i< tcpservidor->maxPendingConnections();i++){
        tcpcliente[i] = new QTcpSocket(this);
        //connect(tcpservidor,SIGNAL(newConnection()),this, SLOT(conexion_nueva()));

    }
    QHostAddress hostadd("192.168.0.109");
    tcpservidor->listen(hostadd,8888);
    connect(tcpservidor,SIGNAL(newConnection()),this, SLOT(conexion_nueva()));
    */

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

       std::string user = folder1.append("/Users.json").toStdString();

       std::ofstream userFile(user);


       userFile << "User 1" << std::endl;
       userFile << "User 2" << std::endl;
       userFile << "User 3" << std::endl;
       userFile.close();

       qDebug()<<"FolderOdyssey created";

       if (QDir(folder2).exists() == false){
           QDir().mkdir(folder2);
           std::string metadata = folder2.append("/Metadata.json").toStdString();
           std::ofstream metadataFile(metadata);
           metadataFile << "metadata 1" << std::endl;
           metadataFile << "metadata 2" << std::endl;
           metadataFile.close();
           qDebug()<<"AudioFile created";
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
    if(j<3 || j<0){
        qDebug()<< "Exceso de sockets";
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
        tcpcliente[0]->write( xml.toLatin1().data() , xml.toLatin1().size());
        }
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion <socket Login>");    }


}

/**
 * @brief Método hacer la comunicación del socket Singin_Server
 *
 */
void Odyssey_S::leer_socketSingin() {       //Recibe los datos del cliente
    if(tcpcliente[1]->bytesAvailable() > 0){
        qDebug() << "Socket Sing_in ";
        QByteArray buffer;
        buffer.resize( tcpcliente[1]->bytesAvailable());
        tcpcliente[1]->read( buffer.data(),buffer.size() );     //lee los datos del cliente
        if(QString (buffer)!="\n"){ //Condición para no pasar "basura" del socket
            ui->plainTextEdit->setReadOnly(true);
            ui->plainTextEdit->appendPlainText("Sing_In > "+ QString(buffer));
        xml = QString (buffer)+"\n";
        tcpcliente[1]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
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
/*
        QString dataInto = QString(buffer);
        QJsonDocument doc = QJsonDocument::fromJson(dataInto.toUtf8());
        QJsonObject jsonObject = doc.object();
        jsonObject.insert("adress_memory", 12345);
        QJsonDocument docX(jsonObject);

        const QString strJson(docX.toJson(QJsonDocument::Compact).append("\n"));

*/

        tcpcliente[2]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion <socket  Main Interface>");
    }
}

