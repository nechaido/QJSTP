//
// Created by nechaido on 4/9/16.
//

#include "QJSTP.h"
#include <QScriptValueIterator>

#include <iostream>

QJSTP* QJSTP::qjstp;

QScriptValue QJSTP::parse(QString str)
{

}

QString QJSTP::stringify(QScriptValue obj)
{
    if (obj.isArray()){
        return stringifyArr(obj);
    } else if (obj.isObject()) {
        return stringifyObj(obj);
    } else {
        return obj.toString();
    }
}

QString QJSTP::dump(QScriptValue obj)
{

}

QScriptValue QJSTP::interprete(QString str)
{
    return engine->evaluate("(" + str + ")");
}

QString QJSTP::serialize(QScriptValue obj)
{

}

QScriptValue QJSTP::deserialize(QString str)
{

}

QScriptValue QJSTP::dataToObject(QScriptValue data, QScriptValue metadata)
{

}

QScriptValue QJSTP::objectToData(QScriptValue obj, QScriptValue metadata)
{

}

QJSTP *QJSTP::initialize()
{
    return qjstp != nullptr ? qjstp : (qjstp = new QJSTP());
}

QJSTP::QJSTP()
{
    int i = 0;
    qCoreApplication = new QCoreApplication(i, nullptr);
    engine = new QScriptEngine();
}

QString QJSTP::stringifyObj(QScriptValue obj)
{
    QString str;
    QScriptValueIterator current(obj);
    str = "{";
    if (current.hasNext()){
        current.next();
        str.append(current.name() + ":" + stringify(current.value()));
    }
    while (current.hasNext()){
        current.next();
        str.append(",");
        str.append(current.name());
        str.append(":");
        str.append(stringify(current.value()));
    }
    str.append("}");
    return str;
}

QString QJSTP::stringifyArr(QScriptValue obj)
{
    QString str;
    QScriptValueIterator current(obj);
    str = "[";
    if (current.hasNext()){
        current.next();
        str.append(stringify(current.value()));
    }
    while (current.hasNext()){
        current.next();
        str.append(",");
        str.append(stringify(current.value()));
    }
    str.append("]");
    return str;
}




