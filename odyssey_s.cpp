#include "odyssey_s.h"
#include "ui_odyssey_s.h"

#include <QJsonObject>
#include <QJsonDocument>

Odyssey_S::Odyssey_S(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Odyssey_S)
{
    ui->setupUi(this);
    tcpservidor = new QTcpServer(this);
    tcpservidor->setMaxPendingConnections(1);

    tcpcliente = new QTcpSocket(this);

    tcpservidor->listen(QHostAddress::LocalHost,8888);
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
    tcpcliente = tcpservidor->nextPendingConnection();
    connect(tcpcliente,SIGNAL(readyRead()),this, SLOT(leer_socketcliente()));
    ui->label_3->setText("Connected Client Odyssey");
}
/**
 * @brief Método para leer los msj del cliente
 *
 */
void Odyssey_S::leer_socketcliente() {       //Recibe los datos del cliente
    if(tcpcliente->bytesAvailable() > 0){
        QByteArray buffer;
        buffer.resize( tcpcliente->bytesAvailable());
        tcpcliente->read( buffer.data(),buffer.size() );
        ui->plainTextEdit->setReadOnly(true);
        ui->plainTextEdit->appendPlainText( QString (buffer));

        qDebug() << "Buffer : "<<QString (buffer);

        QString dataInto = QString(buffer);
        QJsonDocument doc = QJsonDocument::fromJson(dataInto.toUtf8());
        QJsonObject jsonObject = doc.object();

       // jsonObject.insert("adress_memory", QString::number(value));
        QJsonDocument docX(jsonObject);
        const QString strJson(docX.toJson(QJsonDocument::Compact));


        tcpcliente->write( strJson.toLatin1().data() , strJson.toLatin1().size()); //envio datos al cliente

        //on_client_clicked(strJson);
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion de ningun sockets cliente");
    }
}


/**
 * @brief Método para establecer una conexión con el cliente 1
 *
 */
/*
void Odyssey_S::on_client_clicked(const QString dato)
{
    tcpcliente->write( dato.toLatin1().data() , dato.toLatin1().size()); //envio datos al cliente
}*/
