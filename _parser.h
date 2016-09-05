#ifndef _PARSER_H
#define _PARSER_H

#include "QScriptValue"

namespace QJSTP
{
namespace Parser
{

enum Type
{
    UNDEFINED = 0, NUL, BOOL, NUMBER, STRING, ARRAY, OBJECT, ERROR, FUNCTION
};

QScriptValue parseUndefined(QString &str, uint &beg);
QScriptValue parseNull(QString &str, uint &beg);
QScriptValue parseBool(QString &str, uint &beg);
QScriptValue parseNumber(QString &str, uint &beg);
QScriptValue parseString(QString &str, uint &beg);
QScriptValue parseArray(QString &str, uint &beg);
QScriptValue parseObject(QString &str, uint &beg);
QScriptValue parseError(QString &str, uint &beg);
QScriptValue parseFunction(QString &str, uint &beg);

QScriptValue (*parser[9])(QString &, uint &) = {
    &parseUndefined,
    &parseBool,
    &parseNull,
    &parseNumber,
    &parseString,
    &parseArray,
    &parseObject,
    &parseError,
    &parseFunction
};

Type typeOf(QString &str, uint &beg);
void skipWhitespaces(QString &str, uint &beg);
QString getTokenName(QString &str, uint &beg);

QString stringifyObj(QScriptValue obj);
QString stringifyArr(QScriptValue obj);

void postprocess(QScriptValue);

}
}

#endif // _PARSER_H
