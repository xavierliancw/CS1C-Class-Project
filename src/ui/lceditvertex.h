#ifndef LCEDITVERTEX_H
#define LCEDITVERTEX_H

#include <QWidget>
#include <functional>
#include <tuple>
#include <QIntValidator>

namespace Ui {class LCEditVertex;}

/**
 * @brief A list cell that edits a vertex's x and y coordinates.
 */
class LCEditVertex : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent: Parent pointer.
     * @param onCoordUpdateAct: Lambda that executes when either x or y coordinate gets updated.
     * @param onDelBtPressForIndex: Lambda that executes when the delete button is pressed.
     */
    explicit LCEditVertex(QWidget *parent,
                          std::function<void(int, QString, QString)> onCoordUpdateAct,
                          std::function<void(int)> onDelBtPressForIndex);
    /**
     * @brief Destructor.
     */
    ~LCEditVertex();

    /**
     * @brief Populates this cell with data.
     *
     * @param indexNum: The number that indicates which row this cell is in.
     * @param x: X coordinate to fill.
     * @param y: Y coordinate to fill.
     * @param delBtEnabled: Controls if delete button is enabled or not.
     */
    void populateWith(int indexNum, QString x, QString y, bool delBtEnabled);

private:
    Ui::LCEditVertex *ui;
    std::function<void(int, QString, QString)> coordUpdateAct;
    std::function<void(int)> delBtPressForIndex;
    QIntValidator *intValidator;
    int currentIndex = -1;

    void resetUI();
};

#endif // LCEDITVERTEX_H
