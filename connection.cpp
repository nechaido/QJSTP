#include "connection.h"

namespace QJSTP
{

const QString Connection::TERMINATOR = "\0";

Connection::Connection(QString address, quint16 port)
    : address(address), port(port)
{
    socket = new QTcpSocket(this);
    callbacks = new QHash<quint64, function>();
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onData()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}

void Connection::call(QString interface, QString method, QScriptValue parameters, function callback)
{

}

void Connection::callback(quint64 id, QScriptValue parameters)
{

}

void Connection::event(QString interface, QString method, QScriptValue parameters, QVector <function> callbacks)
{

}

void Connection::handshake(QString name, QScriptValue parameters, function callback)
{

}

void Connection::inspect(QString interface, function callback)
{

}

}


