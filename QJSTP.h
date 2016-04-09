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

    static QScriptValue parse (QString str);
    static QString stringify (QScriptValue obj);

    static QString dump (QScriptValue obj);

    static QScriptValue interprete (QString str);
    static QString serialize (QScriptValue obj);

    static QScriptValue deserialize (QString str);

    static QScriptValue dataToObject (QScriptValue data, QScriptValue metadata);
    static QScriptValue objectToData (QScriptValue obj, QScriptValue metadata);

private:

    static QScriptEngine engine;

};


#endif //QJSTP_QJSTP_H
