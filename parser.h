#include <QtCore>
#include <QScriptEngine>
#include <QScriptValue>

#ifndef PARSER_H
#define PARSER_H

namespace QJSTP {

class Parser
{

public:

    static Parser* initialize();

    QScriptValue parse (QString str);
    QString stringify (QScriptValue obj);

    QString dump (QScriptValue obj);

    QScriptValue interprete (QString str);
    QString serialize (QScriptValue obj);

    QScriptValue deserialize (QString str);

    QScriptValue dataToObject (QScriptValue data, QScriptValue metadata);
    QScriptValue objectToData (QScriptValue obj, QScriptValue metadata);

private:

    static Parser* self;

    enum Type {
        UNDEFINED = 0, NUL, BOOL, NUMBER, STRING, ARRAY, OBJECT, ERROR, FUNCTION
    };

    QCoreApplication* qCoreApplication;
    QScriptEngine* engine;

    QScriptValue(Parser::*parser[9])(QString&, uint&) = {
        &Parser::parseUndefined,
        &Parser::parseBool,
        &Parser::parseNull,
        &Parser::parseNumber,
        &Parser::parseString,
        &Parser::parseArray,
        &Parser::parseObject,
        &Parser::parseError,
        &Parser::parseFunction
    };

    Parser();

    QScriptValue parseUndefined (QString& str, uint &beg);
    QScriptValue parseNull (QString& str, uint &beg);
    QScriptValue parseBool (QString& str, uint &beg);
    QScriptValue parseNumber (QString& str, uint &beg);
    QScriptValue parseString (QString& str, uint &beg);
    QScriptValue parseArray (QString& str, uint &beg);
    QScriptValue parseObject (QString& str, uint &beg);
    QScriptValue parseError (QString& str, uint &beg);
    QScriptValue parseFunction (QString& str, uint &beg);

    Type typeOf (QString& str, uint &beg);
    void skipWhitespaces(QString& str, uint &beg);
    QString getTokenName(QString& str, uint &beg);

    QString stringifyObj (QScriptValue obj);
    QString stringifyArr (QScriptValue obj);

    void postprocess(QScriptValue);
};

}

#endif // PARSER_H
