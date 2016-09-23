#ifndef CONNECTION_H
#define CONNECTION_H

#include <QAbstractSocket>
#include <functional>

#include "parser.h"


namespace QJSTP
{

class Connection: public QObject
{
    Q_OBJECT

public:
    typedef std::function<void(QScriptValue)> handler;
    typedef std::function<QScriptValue(QScriptValue)> method;

    static const QByteArray TERMINATOR;

    Connection(const QString &address, quint16 port, bool useSSL = false);
    Connection(const QString &address, quint16 port, QHash<QString, QList<QPair<QString, method>>> methods, bool useSSL = false);
    Connection(const QString &address, quint16 port, QHash<QString, QList<QPair<QString, method>>> methods, QAbstractSocket *transport);

    void call(QString interface, QString method, QScriptValue parameters, handler callback = NULL);
    void event(QString interface, QString method, QScriptValue parameters, QList<handler> callbacks = {});
    void handshake(QString name, handler callback = NULL);
    void handshake(QString name, QScriptValue parameters, handler callback = NULL);
    void inspect(QString interface, handler callback = NULL);

    const QList<QString> getInterfaces();
    const QList<QString> getMethods(QString interface);

    void addMethod(QString interface, QString methodName, method func);

    //    void state();
    //    void stream();
    //    void health();

    QAbstractSocket *socket;

private:

    QByteArray buffer;

    QString sessionId;
    quint64 packageId;

    QHash <quint64, QList<handler>> callbacks;

    QHash<QString, QList<QString>> serverMethods;
    QHash<QString, QList<QPair<QString, method>>> methods;

    static const QString HANDSHAKE;
    static const QString CALL;
    static const QString CALL_BACK;
    static const QString EVENT;
    static const QString INSPECT;

//    static const QString STATE;
//    static const QString STREAM;
//    static const QString HEALTH;

    void onHandshakeReturn(QScriptValue parameters);
    void onInspectReturn(QString interface, QScriptValue parameters);

    void onCall(QScriptValue parameters);
    void onEvent(QScriptValue parameters);
    void onInspect(QScriptValue parameters);

private slots :
    void onConnected();
    void onData();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

};

}

#endif // CONNECTION_H
