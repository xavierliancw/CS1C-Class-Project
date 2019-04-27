#ifndef SVCJSON_H
#define SVCJSON_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <stdexcept>
#include <string>

class SVCJson
{
    //Singleton implementation
    static SVCJson* instance;
    SVCJson();

    QJsonDocument extractJSONDocumentFrom(QString localFilePath);
public:
    //Custom errors
    class JsonFileSystemError : public std::runtime_error
    {
    public:
        JsonFileSystemError(const std::string& msg);
    };
    class JsonInvalidError: public std::runtime_error
    {
    public:
        JsonInvalidError(const std::string& msg);
    };

    //Singleton access
    static SVCJson* getInstance();

    //Services
    void persistJSONToLocalFileSystem(QJsonObject jsonObj, QString localFilePath);
    void persistJSONToLocalFileSystem(QJsonArray jsonObj, QString localFilePath);
    void asdf(QString file_path);
    QJsonArray readJsonArrayFile(QString localFilePath);
    QJsonObject readJsonObjectFile(QString localFilePath);
};

#endif // SVCJSON_H
