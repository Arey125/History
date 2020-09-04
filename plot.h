#ifndef PLOT_H
#define PLOT_H

#include <QList>
#include <QColor>
#include <fstream>
#include <QTextStream>
#include <string>
#include <QFile>

using namespace std;

class Plot
{
public:
    QVector<double> x,y;
    QColor color;
    QString name;
    QString unit;

    Plot(QTextStream &out);
    Plot();

    void save(QTextStream &out);
};

#endif // PLOT_H
