#include "svcjson.h"

#include <QFile>
#include <QJsonDocument>
#include <QTextStream>

SVCJson::JsonFileSystemError::JsonFileSystemError(const std::string& msg):
    std::runtime_error(msg) {}
SVCJson::JsonInvalidError::JsonInvalidError(const std::string& msg):
    std::runtime_error(msg) {}

SVCJson* SVCJson::instance = nullptr;

SVCJson::SVCJson()
{}

SVCJson* SVCJson::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SVCJson();
    }
    return instance;
}

void SVCJson::persistJSONToLocalFileSystem(QJsonObject jsonObj, QString localFilePath)
{
    QJsonDocument jsonDoc(jsonObj);
    QString jsonStr = jsonDoc.toJson();

    QFile jsonFile(localFilePath);

    if(!jsonFile.open(QIODevice::WriteOnly))
    {
        QString err = "Could not open: " + localFilePath;
        throw JsonFileSystemError(err.toUtf8().constData());
    }
    jsonFile.write(jsonStr.toLocal8Bit());
    jsonFile.close();
}

void SVCJson::persistJSONToLocalFileSystem(QJsonArray jsonObj, QString localFilePath)
{
    QJsonDocument jsonDoc(jsonObj);
    QString jsonStr = jsonDoc.toJson();

    QFile jsonFile(localFilePath);

    if(!jsonFile.open(QIODevice::WriteOnly))
    {
        QString err = "Could not open: " + localFilePath;
        throw JsonFileSystemError(err.toUtf8().constData());
    }
    jsonFile.write(jsonStr.toLocal8Bit());
    jsonFile.close();
}

QJsonArray SVCJson::readJsonArrayFile(QString localFilePath)
{
    QFile file_obj(localFilePath);
    QTextStream file_text(&file_obj);
    QString json_string;
    QByteArray json_bytes = json_string.toLocal8Bit();
    QJsonDocument jsonDoc = extractJSONDocumentFrom(localFilePath);
    if (!jsonDoc.isArray())
    {
        throw JsonInvalidError("Json file is not a top level array type.");
    }
    return jsonDoc.array();
}

QJsonObject SVCJson::readJsonObjectFile(QString localFilePath)
{
    QJsonDocument jsonDoc = extractJSONDocumentFrom(localFilePath);
    if (!jsonDoc.isObject())
    {
        throw JsonInvalidError("Json file is not a top level object type.");
    }
    return jsonDoc.object();
}

QJsonDocument SVCJson::extractJSONDocumentFrom(QString localFilePath)
{
    QFile file_obj(localFilePath);
    QTextStream file_text(&file_obj);
    QString rawJsonStr;
    QByteArray rawJsonBytes;

    //Open file and read it into a json doc
    if(!file_obj.open(QIODevice::ReadOnly))
    {
        QString err = "Could not open: " + localFilePath;
        throw JsonFileSystemError(err.toUtf8().constData());
    }
    rawJsonStr = file_text.readAll();
    rawJsonBytes = rawJsonStr.toLocal8Bit();
    file_obj.close();
    return QJsonDocument::fromJson(rawJsonBytes);
}
