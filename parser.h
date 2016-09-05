#include <QtCore>
#include <QScriptEngine>
#include <QScriptValue>

#ifndef PARSER_H
#define PARSER_H

namespace QJSTP {
namespace Parser {

QScriptValue parse (QString str);
QString stringify (QScriptValue obj);

QString dump (QScriptValue obj);

QScriptValue interprete (QString str);
QString serialize (QScriptValue obj);

QScriptValue deserialize (QString str);

QScriptValue dataToObject (QScriptValue data, QScriptValue metadata);
QScriptValue objectToData (QScriptValue obj, QScriptValue metadata);

}}

#endif // PARSER_H
