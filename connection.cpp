#include "connection.h"

#include <QSslSocket>
#include <QScriptValueIterator>

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
QByteArray getMessage(QString type, quint64 id, QString interface, QString method, QScriptValue parameters);

Connection::Connection(QString address, quint16 port, bool useSSL)
    : callbacks(), serverMethods()
{
    if (useSSL) {
        socket = new QSslSocket(this);
    } else {
        socket = new QTcpSocket(this);
    }
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onData()));
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)()), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    socket->connectToHost(address, port);
}

void Connection::call(QString interface, QString method, QScriptValue parameters, handler callback)
{
    QByteArray message = getMessage(CALL, packageId, interface, method, parameters);
    socket->write(message);
    if (callback != NULL) {
        callbacks.insert(packageId, { callback });
    }
    packageId++;
}

void Connection::event(QString interface, QString method, QScriptValue parameters, QList <handler> callbacks)
{

}

void Connection::handshake(QString name, Connection::handler callback)
{
    QByteArray message;
    message = getMessage(HANDSHAKE, packageId, name);
    socket->write(message);
    QList<handler> packageCallbacks = { std::bind(&Connection::onHandshakeReturn, this, std::placeholders::_1) };
    if (callback != NULL) {
        packageCallbacks.append(callback);
    }
    callbacks.insert(packageId, { packageCallbacks });
    packageId++;
}

void Connection::handshake(QString name, QScriptValue parameters, handler callback)
{
    QByteArray message;
    message = getMessage(HANDSHAKE, packageId, name, parameters);
    socket->write(message);
    QList<handler> packageCallbacks = { std::bind(&Connection::onHandshakeReturn, this, std::placeholders::_1) };
    if (callback != NULL) {
        packageCallbacks.append(callback);
    }
    callbacks.insert(packageId, { packageCallbacks });
    packageId++;
}

void Connection::inspect(QString interface, handler callback)
{
    socket->write(getMessage(INSPECT, packageId, interface));
    QList<handler> packageCallbacks = { std::bind(&Connection::onInspectReturn, this, interface, std::placeholders::_1) };
    if (callback != NULL) {
        packageCallbacks.append(callback);
    }
    callbacks.insert(packageId, { packageCallbacks });
    packageId++;
}

const QList<QString> Connection::getInterfaces()
{
    return serverMethods.keys();
}

const QList<QString> Connection::getMethods(QString interface)
{
    return serverMethods.value(interface);
}

void Connection::onHandshakeReturn(QScriptValue parameters)
{
    if(parameters.property("ok").isValid()) {
        sessionId = parameters.property("ok").toString();
    }
}

void Connection::onInspectReturn(QString interface, QScriptValue parameters)
{
    QList<QString> methods;
    if (parameters.property("ok").isValid()) {
        QScriptValueIterator current(parameters.property("ok"));
        while (current.hasNext()) {
            current.next();
            methods.append(current.value().toString());
        }
        serverMethods.insert(interface, methods);
    }
}

void Connection::onCall(QScriptValue parameters)
{

}

void Connection::onEvent(QScriptValue parameters)
{

}

void Connection::onInspect(QScriptValue parameters)
{

}

void Connection::onConnected()
{

}

void Connection::onData()
{
    buffer.append(socket->readAll());
    socket->flush();
    int index = -1;
    while((index = buffer.indexOf(TERMINATOR)) > 0) {
        QByteArray message = buffer.mid(0, index);
        buffer.remove(0, index + 1);
        QScriptValue package = Parser::parse(message);
        QString packageType;
        if (package.property(HANDSHAKE).isValid()) {
            packageType = HANDSHAKE;
        } else if (package.property(CALL).isValid()) {
            packageType = CALL;
        } else if (package.property(CALL_BACK).isValid()) {
            packageType = CALL_BACK;
        } else if (package.property(EVENT).isValid()) {
            packageType = EVENT;
        } else if (package.property(INSPECT).isValid()) {
            packageType = INSPECT;
        }
        for (auto func : callbacks.value(package.property(packageType).property(0).toInt32())) {
            func(package);
        }
    }
}

void Connection::onDisconnected()
{

}

void Connection::onError(QAbstractSocket::SocketError socketError)
{

}

QByteArray getMessage(QString type, quint64 id)
{
    return "{" + type.toUtf8() + ":[" + QString::number(id).toUtf8() + "]}"
            + Connection::TERMINATOR;
}

QByteArray getMessage(QString type, quint64 id, QString name)
{
    return QByteArray("{" + type.toUtf8() + ":[" + QString::number(id).toUtf8()
                      + ",'" + name.toUtf8() + "']}" + Connection::TERMINATOR);
}

QByteArray getMessage(QString type, quint64 id, QString name, QScriptValue parameters)
{
    return QByteArray("{" + type.toUtf8() + ":[" + QString::number(id).toUtf8()
                      + ",'" + name.toUtf8() + "'],"
                      + Parser::stringify(parameters).toUtf8() + "}"
                      + Connection::TERMINATOR);
}

QByteArray getMessage(QString type, quint64 id, QScriptValue parameters) {

}

QByteArray getMessage(QString type, quint64 id, QString interface, QString method, QScriptValue parameters)
{
    QByteArray args = Parser::stringify(parameters).toUtf8();
    return QByteArray("{" + type.toUtf8() + ":[" + QString::number(id).toUtf8()
                      + ",'" + interface.toUtf8() + "']," + method.toUtf8()
                      + ":" + args + "}"
                      + Connection::TERMINATOR);
}

}


