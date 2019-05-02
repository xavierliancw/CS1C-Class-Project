#ifndef JSONTESTIMONIAL_H
#define JSONTESTIMONIAL_H
#include <QJsonObject>
#include "dtotestimonial.h"

/**
 * @brief Tranformational object that facilitates JSON serialization and deserialization of
 * DTOTestimonial objects through the Qt SDK.
 *
 */
struct JSONTestimonial
{
    /**
     * @brief JSON key for the display name property.
     *
     * @return QString
     */
    static QString getKeyDisplayName() {return "displayName";}
    /**
     * @brief JSON key for the text property.
     *
     * @return QString
     */
    static QString getKeyTxt() {return "txt";}
    /**
     * @brief JSON key for the timestamp property.
     *
     * @return QString
     */
    static QString getKeyTimestamp() {return "timestamp_unix";}
public:
    /**
     * @brief Creates a DTOTestimonial object by deserializing a QJsonObject.
     *
     * @param json: The JSON to deserialize.
     * @return DTOTestimonial
     */
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

    /**
     * @brief Creates a QJsonObject by serializing a DTOTestimonial object.
     *
     * @param obj: The testimonial POCO to serialize.
     * @return QJsonObject
     */
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
