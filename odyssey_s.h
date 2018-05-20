#ifndef ODYSSEY_S_H
#define ODYSSEY_S_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class Odyssey_S;
}

class Odyssey_S : public QMainWindow
{
    Q_OBJECT

public:
    explicit Odyssey_S(QWidget *parent = 0);
    ~Odyssey_S();

public slots:
    /**
     * @brief Método para establecer la comunicación con el cliente
     *
     */
    void conexion_nueva();
    /**
     * @brief Método para leer los datos enviado por el cliente
     *
     */
    void leer_socketcliente();

    /**
     * @brief Método para leer los datos enviado por el cliente
     *
     */
    void leer_socketLogin();
    /**
     * @brief Método para leer los datos enviado por el cliente
     *
     */
    void leer_socketSingin();

    /**
     * @brief Método para crear el ficheros
     *
     */
    void createFile();



private:
    Ui::Odyssey_S *ui;
    QTcpServer *tcpservidor; /**< TCP_Servidor */
    QTcpSocket *tcpcliente[2]; /**< TCP_Cliente */
};

#endif // ODYSSEY_S_H
