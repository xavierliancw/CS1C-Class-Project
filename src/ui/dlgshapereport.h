#ifndef DLGSHAPEREPORT_H
#define DLGSHAPEREPORT_H

#include <QDialog>
#include <functional>
#include <QFile>
#include <QTextStream>

namespace Ui {
class DLGShapeReport;
}

class DLGShapeReport : public QDialog
{
    Q_OBJECT

public:

    explicit DLGShapeReport(QWidget *parent = nullptr,
                            std::function<void()> authSuccessCallback = [](){});
    void saveToFile();
    /**
      * @brief The desturctor deletes the ui when it goes out of scope, so that no memory leaks take place.
      */
    ~DLGShapeReport();

private slots:
    void createShapeFileReport();

private:
    Ui::DLGShapeReport *ui;
    std::function<void()> authCallback;
};
#endif // DLGSHAPEREPORT_H
