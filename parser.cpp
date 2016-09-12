#include "parser.h"
#include "_parser.h"

#include <QScriptValueIterator>

int i = 0;

QCoreApplication *qCoreApplication = new QCoreApplication(i, nullptr);

QScriptEngine *engine = new QScriptEngine();

namespace QJSTP
{
namespace Parser
{

QScriptValue parse(QString str)
{
    uint beg = 0;
    skipWhitespaces(str, beg);
    return parser[typeOf(str, beg)](str, beg);
}

QString stringify(QScriptValue obj)
{
    if (obj.isArray()) {
        return stringifyArr(obj);
    }
    else if (obj.isObject()) {
        return stringifyObj(obj);
    }
    else {
        return obj.toString();
    }
}

QString dump(QScriptValue obj)
{

}

QScriptValue interprete(QString str)
{
    QScriptValue result = engine->evaluate("(" + str + ")");
    postprocess(result);
    return result;
}

QString serialize(QScriptValue obj)
{

}

QScriptValue deserialize(QString str)
{

}

QScriptValue dataToObject(QScriptValue data, QScriptValue metadata)
{

}

QScriptValue objectToData(QScriptValue obj, QScriptValue metadata)
{

}

QScriptValue parseUndefined(QString &str, uint &beg)
{
    if (str[beg] == ',' || str[beg] == ']') {
        return QScriptValue::UndefinedValue;
    }
    if (str.mid(beg, 9) == "undefined") {
        beg += 9;
        return QScriptValue(QScriptValue::UndefinedValue);
    }
    return parseError(str, beg);
}

QScriptValue parseNull(QString &str, uint &beg)
{
    if (str.mid(beg, 4) == "null") {
        beg += 4;
        return QScriptValue::NullValue;
    }
    return parseError(str, beg);
}

QScriptValue parseBool(QString &str, uint &beg)
{
    if (str.mid(beg, 4) == "true") {
        beg += 4;
        return QScriptValue(true);
    }
    if (str.mid(beg, 5) == "false") {
        beg += 5;
        return QScriptValue(false);
    }
    return parseError(str, beg);
}

QScriptValue parseNumber(QString &str, uint &beg)
{
    uint size = 0;
    bool isIntPart = true;
    if (str[beg] == '+' || str[beg] == '-') ++size;
    while (!str[beg + size].isSpace() && size < str.length() - beg && str[beg + size] != ',') {
        if (str[beg + size].isNumber()) {
            ++size;
        } else if (str[beg + size] == '.' && isIntPart) {
            isIntPart = false;
            ++size;
        } else {
            break;
        }
    }
    if (size > 0) {
        beg += size;
        return QScriptValue(str.mid(beg - size, size).toDouble());
    }
    return parseError(str, beg);
}

QScriptValue parseString(QString &str, uint &beg)
{
    uint size = 1;
    QCharRef begSymbol = str[beg];
    ++beg;
    while (true) {
        if (size == str.length() - beg) {
            size = -1;
            break;
        }
        if (str[beg + size] == begSymbol && str[beg + size - 1] != '\\') { break; }
        ++size;
    }
    if (size > 0) {
        beg += size + 1;
        return QScriptValue(str.mid(beg - size - 1, size));
    }
    return parseError(str, beg);
}

QScriptValue parseArray(QString &str, uint &beg)
{
    QScriptValue result = engine->newArray();
    skipWhitespaces(str, beg);
    quint32 index = 0;
    while (beg < str.length()) {
        if (str[beg] == ']') {
            ++beg;
            return result;
        }
        ++beg;
        skipWhitespaces(str, beg);
        result.setProperty(index++, parser[typeOf(str, beg)](str, beg));
        skipWhitespaces(str, beg);
    }
    return parseError(str, beg);
}

QScriptValue parseObject(QString &str, uint &beg)
{
    QScriptValue result = engine->newObject();
    skipWhitespaces(str, beg);
    while (beg < str.length()) {
        if (str[beg] == '}') {
            ++beg;
            return result;
        }
        else {
            ++beg;
            skipWhitespaces(str, beg);
        }
        QString token = getTokenName(str, beg);
        result.setProperty(token, parser[typeOf(str, beg)](str, beg));
        skipWhitespaces(str, beg);
    }
    return result;
}

QScriptValue parseError(QString &str, uint &beg)
{

}

QScriptValue parseFunction(QString &str, uint &beg)
{

}

Type typeOf(QString &str, uint &beg)
{
    skipWhitespaces(str, beg);
    if (str[beg] == ',' || str[beg] == ']' || str[beg] == 'u')
        return UNDEFINED;
    if (str[beg] == 'n')
        return NUL;
    if (str[beg].isDigit() || str[beg] == '.' || str[beg] == '-' || str[beg] == '+')
        return NUMBER;
    if (str[beg] == 'f' && str[beg + 1] == 'u')
        return FUNCTION;
    if ((str[beg] == 'f' && str[beg + 1] == 'a') || str[beg] == 't')
        return BOOL;
    if (str[beg] == '\"' || str[beg] == '\'')
        return STRING;
    if (str[beg] == '[')
        return ARRAY;
    if (str[beg] == '{')
        return OBJECT;
    return ERROR;
}

void skipWhitespaces(QString &str, uint &beg)
{
    while (str[beg].isSpace()) { ++beg; }
}

QString getTokenName(QString &str, uint &beg)
{
    skipWhitespaces(str, beg);
    uint size = 0;
    for (size = 0; size < str.length() - beg && !str[beg + size].isSpace() && str[beg + size] != ':'; ++size);
    uint tmp = beg;
    beg += size;
    skipWhitespaces(str, beg);
    ++beg;
    return QString(str.mid(tmp, size));
}

QString stringifyObj(QScriptValue obj)
{
    QString str;
    QScriptValueIterator current(obj);
    str = "{";
    if (current.hasNext()) {
        current.next();
        str += (current.name() + ":" + stringify(current.value()));
    }
    while (current.hasNext()) {
        current.next();
        str += "," + current.name() + ":" + stringify(current.value());
    }
    str += "}";
    return str;
}

QString stringifyArr(QScriptValue obj)
{
    QString str;
    str = "[";
    if (obj.property("length").toNumber() != 0) {
        str += stringify(obj.property(0));
    }
    for (int i = 1; i < obj.property("length").toNumber(); ++i) {
        QScriptValue current = obj.property(i);
        str += ",";
        if (!current.isUndefined()) {
            str += stringify(current);
        }
    }
    str += "]";
    return str;
}
void postprocess(QScriptValue value)
{
    if (value.isObject()) {
        QScriptValueIterator current(value);
        if (current.hasNext()) {
            current.next();
            postprocess(current.value());
        }
    }
    else if (value.isArray()) {
        for (int i = 1; i < value.property("length").toNumber(); ++i) {
            if (!value.property(i).isValid()) {
                value.setProperty(i, QScriptValue::UndefinedValue);
            }
        }
    }
}

}
}
