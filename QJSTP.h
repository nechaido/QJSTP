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

    enum Type {
        UNDEFINED = 0, NUL, BOOL, NUMBER, STRING, ARRAY, OBJECT, ERROR, FUNCTION
    };

    static QJSTP* qjstp;

    QCoreApplication* qCoreApplication;
    QScriptEngine* engine;

    QScriptValue(QJSTP::*parser[9])(QString&, uint&) = {
        &QJSTP::parseUndefined,
        &QJSTP::parseBool,
        &QJSTP::parseNull,
        &QJSTP::parseNumber,
        &QJSTP::parseString,
        &QJSTP::parseArray,
        &QJSTP::parseObject,
        &QJSTP::parseError,
        &QJSTP::parseFunction
    };

    QJSTP();

    QScriptValue parseUndefined (QString& str, uint &beg);
    QScriptValue parseNull (QString& str, uint &beg);
    QScriptValue parseBool (QString& str, uint &beg);
    QScriptValue parseNumber (QString& str, uint &beg);
    QScriptValue parseString (QString& str, uint &beg);
    QScriptValue parseArray (QString& str, uint &beg);
    QScriptValue parseObject (QString& str, uint &beg);
    QScriptValue parseError (QString& str, uint &beg);
    QScriptValue parseFunction (QString& str, uint &beg);

    inline Type typeOf (QString& str, uint &beg);
    inline void skipWhitespaces(QString& str, uint &beg);
    inline QString getTokenName(QString& str, uint &beg);

    QString stringifyObj (QScriptValue obj);
    QString stringifyArr (QScriptValue obj);

    void postprocess(QScriptValue);

};


#endif //QJSTP_QJSTP_H
