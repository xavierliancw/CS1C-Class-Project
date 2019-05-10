#ifndef DLGSHAPEREPORT_H
#define DLGSHAPEREPORT_H

#include <QDialog>
#include "models/ishape.h"
#include <QJsonArray>
#include "models/jsonshape.h"
#include <QJsonDocument>
#include <vector>
#include "util/customsorts.h"

namespace Ui {class DLGShapeReport;}

/**
 * @brief Dialog that displays a report about the current status of the canvas.
 *
 */
class DLGShapeReport : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param parent: Parent pointer
     * @param shapes: Shapes to display report for.
     */
    explicit DLGShapeReport(QWidget *parent, QVector<IShape*> shapes);
    /**
     * @brief Destructor.
     *
     */
    ~DLGShapeReport();

private:
    Ui::DLGShapeReport *ui;
    QVector<IShape*> shapes;
    void triggerSort();
};

#endif // DLGSHAPEREPORT_H
