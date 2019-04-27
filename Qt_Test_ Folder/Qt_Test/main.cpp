
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);

    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("Golden Cones Shape Application");

    QSpinBox *spinner = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);

   // spinner->

    return prog.exec();
}
