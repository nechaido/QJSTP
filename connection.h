#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <functional>
#include "parser.h"

typedef std::function<void()> function;

namespace QJSTP
{

class Connection: public QObject
{
public:
    Connection(QString address, quint16 port);

    void call(QString interface, QString method, QScriptValue parameters, function callback);
    void callback(quint64 id, QScriptValue parameters);
    void event(QString interface, QString method, QScriptValue parameters, QVector <function> callbacks);
//    void state();
//    void stream();
    void handshake(QString name, QScriptValue parameters, function callback);
//    void health();
    void inspect(QString interface, function callback);

private:
    QTcpSocket *socket;

    QString sessionId;
    quint64 packageId;

    QString address;
    qint16 port;

    QHash <quint64, function> *callbacks;

    static const QString TERMINATOR;

private slots :
    void onConnected();
    void onData();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
};

}

#endif // CONNECTION_H
