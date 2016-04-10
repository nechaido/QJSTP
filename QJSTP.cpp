//
// Created by nechaido on 4/9/16.
//

#include "QJSTP.h"
#include <QScriptValueIterator>

#include <iostream>

QJSTP* QJSTP::qjstp;

QScriptValue QJSTP::parse(QString str)
{
    uint beg = 0;
    return parse(str, beg);
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

QScriptValue QJSTP::parse(QString &str, uint &beg){
    Type type;
    while (str[beg].isSpace()) { ++beg; }
    type = typeOf(str, beg);
    switch (type) {
        case UNDEFINED: return parseUndefined(str, beg);
        case NUL      : return parseNull(str, beg);
        case BOOL     : return parseBool(str, beg);
        case NUMBER   : return parseNumber(str, beg);
        case STRING   : return parseString(str, beg);
        case OBJECT   : return parseObject(str, beg);
        case ARRAY    : return parseArray(str, beg);
        case ERROR    : return parseError(str, beg);
    }
}

QScriptValue QJSTP::parseUndefined(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseNull(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseBool(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseNumber(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseString(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseArray(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseObject(QString &str, uint &beg)
{

}

QScriptValue QJSTP::parseError(QString &str, uint &beg)
{

}

QJSTP::Type QJSTP::typeOf(QString &str, uint &beg)
{
    if (str[beg] == ',' || str[beg] == ']' || str[beg] == 'u')
        return UNDEFINED;
    if (str[beg] == 'n')
        return NUL;
    if (str[beg].isDigit() || str[beg] == '.' || str[beg] == '-' || str[beg] == '+')
        return NUMBER;
    if (str[beg] == 'f' && str[beg+1] == 'u')
        return FUNCTION;
    if ((str[beg] == 'f' && str[beg+1] == 'a') || str[beg] == 't')
        return BOOL;
    if (str[beg] == '\"' || str[beg] == '\'')
        return STRING;
    if (str[beg] == '[')
        return ARRAY;
    if (str[beg] == '{')
        return OBJECT;
    return ERROR;
}

QString QJSTP::stringifyObj(QScriptValue obj)
{
    QString str;
    QScriptValueIterator current(obj);
    str = "{";
    if (current.hasNext()){
        current.next();
        str += (current.name() + ":" + stringify(current.value()));
    }
    while (current.hasNext()){
        current.next();
        str += "," + current.name() + ":" + stringify(current.value());
    }
    str += "}";
    return str;
}

QString QJSTP::stringifyArr(QScriptValue obj)
{
    QString str;
    str = "[";
    if (obj.property("length").toNumber() != 0){
        str += stringify(obj.property(0));
    }
    for (int i = 1; i < obj.property("length").toNumber(); ++i){
        QScriptValue current = obj.property(i);
        str += ",";
        if(!current.isUndefined()){
            str += stringify(current);
        }
    }
    str += "]";
    return str;
}




