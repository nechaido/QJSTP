#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <functional>
#include "parser.h"

namespace QJSTP
{

class Connection: public QObject
{
public:
    typedef std::function<void(QScriptValue)> handler;

    Connection(QString address, quint16 port);

    void call(QString interface, QString method, QScriptValue parameters, handler callback);
    void callback(quint64 id, QScriptValue parameters);
    void event(QString interface, QString method, QScriptValue parameters, QList <handler> callbacks);
//    void state();
//    void stream();
    void handshake(QString name, QScriptValue parameters, handler callback);
//    void health();
    void inspect(QString interface, handler callback);

private:
    QTcpSocket *socket;

    QString sessionId;
    quint64 packageId;

    QString address;
    qint16 port;

    QHash <quint64, handler> *callbacks;

    static const QString TERMINATOR;

private slots :
    void onConnected();
    void onData();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
};

}

#endif // CONNECTION_H
