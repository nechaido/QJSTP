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

    static const QString TERMINATOR;

    Connection(QString address, quint16 port);

    void handshake(QString name, QScriptValue parameters, handler callback);
    void call(QString interface, QString method, QScriptValue parameters, handler callback);
    void callback(quint64 id, QScriptValue parameters);
    void event(QString interface, QString method, QScriptValue parameters, QList <handler> callbacks);
    void inspect(QString interface, handler callback);

    //    void state();
    //    void stream();
    //    void health();

private:
    QTcpSocket *socket;

    QString sessionId;
    quint64 packageId;

    QString address;
    qint16 port;

    QHash <quint64, handler> *callbacks;

    static const QString HANDSHAKE;
    static const QString CALL;
    static const QString CALL_BACK;
    static const QString EVENT;
    static const QString INSPECT;

//    static const QString STATE;
//    static const QString STREAM;
//    static const QString HEALTH;


private slots :
    void onConnected();
    void onData();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

};

}

#endif // CONNECTION_H
