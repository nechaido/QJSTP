//
// Created by nechaido on 4/9/16.
//

#ifndef QJSTP_QJSTP_H
#define QJSTP_QJSTP_H

#include <QtCore>
#include <QScriptEngine>
#include <QScriptValue>


class QJSTP
{

public:

    static QJSTP* initialize();

    QScriptValue parse (QString str);
    QString stringify (QScriptValue obj);

    QString dump (QScriptValue obj);

    QScriptValue interprete (QString str);
    QString serialize (QScriptValue obj);

    QScriptValue deserialize (QString str);

    QScriptValue dataToObject (QScriptValue data, QScriptValue metadata);
    QScriptValue objectToData (QScriptValue obj, QScriptValue metadata);

private:

    static QJSTP* qjstp;

    QCoreApplication* qCoreApplication;
    QScriptEngine* engine;

    QJSTP();

    QString stringifyObj (QScriptValue obj);
    QString stringifyArr (QScriptValue obj);
};


#endif //QJSTP_QJSTP_H
