#ifndef SVCJSON_H
#define SVCJSON_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <stdexcept>
#include <string>

/**
 * @brief Service singleton that facilitates JSON serialization and deserialization to and from the
 * local filesystem through the Qt SDK.
 *
 */
class SVCJson
{
    static SVCJson* instance; /**< Singleton instance. */
    /**
     * @brief Private constructor.
     *
     */
    SVCJson();

    /**
     * @brief Reads JSON from a local file.
     *
     * @param localFilePath: Path to the local file (can be just the file name and extension if
     * the file isn't in any subdirectory).
     * @return QJsonDocument: The QJsonDocument that contains the raw JSON read from the file.
     */
    QJsonDocument extractJSONDocumentFrom(QString localFilePath);
public:
    //Custom errors
    /**
     * @brief Runtime error that occurs when this service encounters a problem with the local
     * filesystem.
     *
     */
    class JsonFileSystemError : public std::runtime_error
    {
    public:
        /**
         * @brief Constructor.
         *
         * @param msg: Error message.
         */
        JsonFileSystemError(const std::string& msg);
    };
    /**
     * @brief Runtime error that occurs when this service encounters a problem with serializing
     * or deserializing JSON data.
     *
     */
    class JsonInvalidError: public std::runtime_error
    {
    public:
        /**
         * @brief Constructor.
         *
         * @param msg: Error message.
         */
        JsonInvalidError(const std::string& msg);
    };

    /**
     * @brief Function to retrieve the instance of this singleton service.
     *
     * @return SVCJson
     */
    static SVCJson* getInstance();

    //Services
    /**
     * @brief Saves a JSON object to the local filesystem, creating directories and/or a new file
     * if necessary.
     *
     * @param jsonObj: The JSON object to write.
     * @param localFilePath: The path to save to (e.g. "jsonfolder/myjsoniwantsaved.json").
     */
    void persistJSONToLocalFileSystem(QJsonObject jsonObj, QString localFilePath);
    /**
     * @brief Saves a JSON array to the local filesystem, creating directories and/or a new file if
     * necessary.
     *
     * @param jsonArr: The JSON array to write.
     * @param localFilePath: The path to save to (e.g. "jsonfolder/myjsoniwantsaved.json").
     */
    void persistJSONToLocalFileSystem(QJsonArray jsonArr, QString localFilePath);
    /**
     * @brief Reads a JSON object from a file in the local file system.
     *
     * @param localFilePath: The path to read from (e.g. "jsonfolder/myjsoniwanttoread.json").
     * @return QJsonArray: Raw JSON.
     */
    QJsonArray readJsonArrayFile(QString localFilePath);
    /**
     * @brief Reads a JSON array from a file in the local file system.
     *
     * @param localFilePath: The path to read from (e.g. "jsonfolder/myjsoniwanttoread.json").
     * @return QJsonObject: Raw JSON.
     */
    QJsonObject readJsonObjectFile(QString localFilePath);
};

#endif // SVCJSON_H
