#include "connection.h"

namespace QJSTP
{

const QByteArray Connection::TERMINATOR = QByteArray::fromRawData("\0", 1);

const QString Connection::HANDSHAKE = "handshake";
const QString Connection::CALL = "call";
const QString Connection::CALL_BACK = "callback";
const QString Connection::EVENT = "event";
const QString Connection::INSPECT = "inspect";

//const QString Connection::STATE = "state";
//const QString Connection::STREAM = "stream";
//const QString Connection::HEALTH = "health";

QByteArray getMessage(QString type, quint64 id);
QByteArray getMessage(QString type, quint64 id, QString name);
QByteArray getMessage(QString type, quint64 id, QScriptValue parameters);
QByteArray getMessage(QString type, quint64 id, QString name, QScriptValue parameters);
QByteArray getMessage(QString type, quint64 id, QString interface, QString method);

Connection::Connection(QString address, quint16 port)
    : address(address), port(port)
{
    socket = new QTcpSocket(this);
    callbacks = new QHash<quint64, handler>();
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onData()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}

void Connection::call(QString interface, QString method, QScriptValue parameters, handler callback)
{

}

void Connection::callback(quint64 id, QScriptValue parameters)
{

}

void Connection::event(QString interface, QString method, QScriptValue parameters, QList <handler> callbacks)
{

}

void Connection::handshake(QString name, QScriptValue parameters, handler callback)
{
    socket->connectToHost(address, port);
    if (socket->waitForConnected()) {
        QByteArray message;
        if (parameters.isNull() || parameters.isUndefined()) {
             message = getMessage(HANDSHAKE, packageId, name);
        } else {
            message = getMessage(HANDSHAKE, packageId, name, parameters);
        }
        socket->write(message);
        callbacks->insert(packageId, callback);
        packageId++;
    }
}

void Connection::inspect(QString interface, handler callback)
{

}

QByteArray getMessage(QString type, quint64 id)
{
    QByteArray message = "{" + type.toUtf8() + ":[" + QString::number(id).toUtf8() + "]}" + Connection::TERMINATOR;
    return message;
}

QByteArray getMessage(QString type, quint64 id, QString name)
{
    return QByteArray("{" + type.toUtf8() + ":[" + QString::number(id).toUtf8() + ",'" + name.toUtf8() + "']}" + Connection::TERMINATOR);
}

QByteArray getMessage(QString type, quint64 id, QString name, QScriptValue parameters)
{
    return QByteArray("{" + type.toUtf8() + ":[" + QString::number(id).toUtf8() + ",'" + name.toUtf8() + "'],"
            + Parser::stringify(parameters).toUtf8() + "}" + Connection::TERMINATOR);
}

QByteArray getMessage(QString type, quint64 id, QScriptValue parameters) {

}

QByteArray getMessage(QString type, quint64 id, QString interface, QString method)
{

}

}


