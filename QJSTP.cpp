//
// Created by nechaido on 4/9/16.
//

#include "QJSTP.h"

QScriptValue QJSTP::parse(QString str)
{

}

QString QJSTP::stringify(QScriptValue obj)
{

}

QString QJSTP::dump(QScriptValue obj)
{

}

QScriptValue QJSTP::interprete(QString str)
{
    return engine.evaluate("(" + str + ")");
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
