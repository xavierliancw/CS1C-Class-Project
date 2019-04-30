#include "ui/winmain.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

void Write(QString Filename)
{
    QFile mFile(Filename);

    if (!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Could not open file for writing";
        return;
    }

    QTextStream out(&mFile);
    out << "Hello World";

    mFile.flush();
    mFile.close();
}

void Read(QString Filename)
{
    QFile mFile(Filename);

    if (!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Could not open file for reading";
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() << mText;

    mFile.close();
}

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    WINMain w;
    w.show();

    QString mFilename = ":E/test/myfile.txt";

    Write(mFilename);
    Read(mFilename);

    return prog.exec();
}
