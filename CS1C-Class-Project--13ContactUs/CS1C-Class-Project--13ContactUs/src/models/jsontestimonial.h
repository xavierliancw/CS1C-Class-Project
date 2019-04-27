#ifndef JSONTESTIMONIAL_H
#define JSONTESTIMONIAL_H
#include <QJsonObject>
#include "dtotestimonial.h"

struct JSONTestimonial
{
    static QString getKeyDisplayName() {return "displayName";}
    static QString getKeyTxt() {return "txt";}
    static QString getKeyTimestamp() {return "timestamp_unix";}
public:
    static DTOTestimonial* fromJSON(const QJsonObject &json)
    {
        DTOTestimonial* dto = new DTOTestimonial();
        QString keyDisplayName = getKeyDisplayName();
        QString keyTxt = getKeyTxt();
        QString keyTimestamp = getKeyTimestamp();
        if (json.contains(keyDisplayName) && json[keyDisplayName].isString())
        {
            dto->displayName = json[keyDisplayName].toString().toUtf8().constData();
        }
        if (json.contains(keyTxt) && json[keyTxt].isString())
        {
            dto->txt = json[keyTxt].toString().toUtf8().constData();
        }
        if (json.contains(keyTimestamp))
        {
            dto->timestamp_unix = json[keyTimestamp].toInt();
        }
        return dto;
    }

    static QJsonObject toJSON(const DTOTestimonial obj)
    {
        QJsonObject newJson = QJsonObject();
        QString keyDisplayName = getKeyDisplayName();
        QString keyTxt = getKeyTxt();
        QString keyTimestamp = getKeyTimestamp();

        newJson[keyDisplayName] = QString::fromStdString(obj.displayName);
        newJson[keyTxt] = QString::fromStdString(obj.txt);
        newJson[keyTimestamp] = obj.timestamp_unix;

        return newJson;
    }
};

#endif // JSONTESTIMONIAL_H
