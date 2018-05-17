#include "odyssey_s.h"
#include "ui_odyssey_s.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <string.h>

#include "thread.h"


QString xml = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>";

Odyssey_S::Odyssey_S(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Odyssey_S)
{
    ui->setupUi(this);
    tcpservidor = new QTcpServer(this);
    tcpservidor->setMaxPendingConnections(2);


    for(int i = 0; i< tcpservidor->maxPendingConnections();i++){
        tcpcliente[i] = new QTcpSocket(this);
    }

    QHostAddress hostadd("172.18.64.35");




    qDebug()<< xml;
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
    connect(tcpcliente[j],SIGNAL(readyRead()),this, SLOT(leer_socketcliente()));
    j++;
    ui->label_3->setText("Connected Client Odyssey");
}
/**
 * @brief Método para leer los msj del cliente
 *
 */
void Odyssey_S::leer_socketcliente() {       //Recibe los datos del cliente
    if(tcpcliente[0]->bytesAvailable() > 0){
        //data->filtro("int");
        QByteArray buffer;
        buffer.resize( tcpcliente[0]->bytesAvailable());
        tcpcliente[0]->read( buffer.data(),buffer.size() );
        ui->plainTextEdit->setReadOnly(true);        ui->plainTextEdit->appendPlainText( QString (buffer));
        qDebug() << "Buffer : "<<QString (buffer);


        xml += "<people>"
                    "<person>"
                          "<name>"+QString (buffer)+"</name><age>20</age></person>\n";

        QString dataInto = QString(buffer);
        QJsonDocument doc = QJsonDocument::fromJson(dataInto.toUtf8());
        QJsonObject jsonObject = doc.object();

        jsonObject.insert("adress_memory", 12345);

        QJsonDocument docX(jsonObject);
        const QString strJson(docX.toJson(QJsonDocument::Compact).append("\n"));

        on_client_clicked(xml);
    }
    else{
        ui->plainTextEdit->appendPlainText("No se puedo realizar la comunicacion de ningun sockets cliente");
    }
}


/**
 * @brief Método para establecer una conexión con el cliente
 *
 */


void Odyssey_S::on_client_clicked(const QString inf)
{
    tcpcliente[0]->write( inf.toLatin1().data() , inf.toLatin1().size()); //envio datos al cliente
}
