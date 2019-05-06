#ifndef JSONCUSTOMERINQUIRY_H
#define JSONCUSTOMERINQUIRY_H
#include <QJsonObject>
#include "dtocustomerinquiry.h"

/**
 * @brief Tranformational object that facilitates JSON serialization and deserialization of
 * DTOCustomerInquiry objects through the Qt SDK.
 *
 */
struct JSONCustomerInquiry
{
    /**
     * @brief Creates a DTOCustomerInquiry object by deserializing a QJsonObject.
     *
     * @param json: The JSON to deserialize.
     * @return DTOCustomerInquiry
     */
    static DTOCustomerInquiry* fromJSON(const QJsonObject &json)
    {
        DTOCustomerInquiry* dto = new DTOCustomerInquiry();
        if (json.contains(keyEmail) && json[keyEmail].isString())
        {
            dto->custEmail = json[keyEmail].toString().toUtf8().constData();
        }
        if (json.contains(keyInquiry) && json[keyInquiry].isString())
        {
            dto->inquiryTxt = json[keyInquiry].toString().toUtf8().constData();
        }
        if (json.contains(keyTimestamp))
        {
            dto->timestamp_unix = json[keyTimestamp].toInt();
        }
        return dto;
    }

    /**
     * @brief Creates a QJsonObject by serializing a DTOCustomerInquiry object.
     *
     * @param obj: The testimonial POCO to serialize.
     * @return QJsonObject
     */
    static QJsonObject toJSON(const DTOCustomerInquiry obj)
    {
        QJsonObject newJson = QJsonObject();

        newJson[keyEmail] = QString::fromStdString(obj.custEmail);
        newJson[keyInquiry] = QString::fromStdString(obj.inquiryTxt);
        newJson[keyTimestamp] = obj.timestamp_unix;

        return newJson;
    }
private:
    static const QString keyEmail;
    static const QString keyInquiry;
    static const QString keyTimestamp;
};

#endif // JSONCUSTOMERINQUIRY_H
