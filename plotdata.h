#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QList>
#include <string>
#include "plot.h"

class PlotData
{
public:
    QList<Plot> plots;

    PlotData();

    void load(QString file_path);
    void save(QString file_path);

    PlotData(QString file_path);
};

#endif // PLOTDATA_H
