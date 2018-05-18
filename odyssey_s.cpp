#include "odyssey_s.h"
#include "ui_odyssey_s.h"

#include <QNetworkInterface>
#include <QtCore>
#include <QtXml>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <string.h>



QString xml;

Odyssey_S::Odyssey_S(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Odyssey_S)
{
    ui->setupUi(this);
    tcpservidor = new QTcpServer(this);
    tcpservidor->setMaxPendingConnections(5);
    for(int i = 0; i< tcpservidor->maxPendingConnections();i++){
        tcpcliente[i] = new QTcpSocket(this);
    }
    QHostAddress hostadd("172.18.64.35");
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

/**
 * @brief Método para crear una nueva conexión
 *
 */
void Odyssey_S::conexion_nueva(){

    static int j=0;
    tcpcliente[j] = tcpservidor->nextPendingConnection();
    connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketLogin()));
    j++;
    tcpcliente[j] = tcpservidor->nextPendingConnection();
    connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketSingin()));
    j++;
    tcpcliente[j] = tcpservidor->nextPendingConnection();
    connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketcliente()));

}

/**
 * @brief Método hacer la comunicación del socket Login_Server
 *
 */
void Odyssey_S::leer_socketLogin() {       //Recibe los datos del cliente
    if(tcpcliente[0]->bytesAvailable() > 0){
        QByteArray buffer;
        buffer.resize( tcpcliente[0]->bytesAvailable());
        tcpcliente[0]->read( buffer.data(),buffer.size() );

        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->appendPlainText("Login :"+ QString(buffer));

        qDebug() << ">>>>>> : "<<QString (buffer+"\n");
        xml = QString (buffer);

        tcpcliente[0]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion de ningun sockets cliente");
    }
}

/**
 * @brief Método hacer la comunicación del socket Singin_Server
 *
 */
void Odyssey_S::leer_socketSingin() {       //Recibe los datos del cliente
    if(tcpcliente[1]->bytesAvailable() > 0){
        QByteArray buffer;
        buffer.resize( tcpcliente[1]->bytesAvailable());
        tcpcliente[1]->read( buffer.data(),buffer.size() );

        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->appendPlainText("Login :"+ QString(buffer));

        qDebug() << ">>>>>> : "<<QString (buffer+"\n");
        xml = QString (buffer);
/*
        QString dataInto = QString(buffer);
        QJsonDocument doc = QJsonDocument::fromJson(dataInto.toUtf8());
        QJsonObject jsonObject = doc.object();
        jsonObject.insert("adress_memory", 12345);
        QJsonDocument docX(jsonObject);

        const QString strJson(docX.toJson(QJsonDocument::Compact).append("\n"));

*/

        tcpcliente[1]->write( xml.toLatin1().data() , xml.toLatin1().size()); //envio datos al cliente
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion de ningun sockets cliente");
    }
}

/**
 * @brief Método hacer la comunicación del socket Cliente/Interface_Server
 *
 */
void Odyssey_S::leer_socketcliente() {       //Recibe los datos del cliente
    if(tcpcliente[2]->bytesAvailable() > 0){
        QByteArray buffer;
        buffer.resize( tcpcliente[2]->bytesAvailable());
        tcpcliente[2]->read( buffer.data(),buffer.size() );
        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->appendPlainText( QString(buffer));
        qDebug() << ">>>>>> : "<<QString (buffer+"\n");
        xml = QString (buffer);
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
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion de ningun sockets cliente");
    }
}

void Odyssey_S::doXml(){

    QDomDocument document;
    QDomElement root = document.createElement("Element");

    document.appendChild(root);

    QFile file("C:\\Test\\MyXML.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() <<"Error_Failded to open file for writting";
        //return -1;
    }else{
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Finished";
    }




}

