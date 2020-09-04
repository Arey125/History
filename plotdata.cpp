#include "plotdata.h"

PlotData::PlotData()
{

}

void PlotData::load(QString file_path)
{
    QFile plot_data(file_path);
    plot_data.open(QFile::ReadOnly);
    QTextStream in(&plot_data);
    int n;
    in >> n;
    for (int i = 0;i < n;i++)
        plots.push_back(Plot(in));
    plot_data.close();
}

void PlotData::save(QString file_path)
{
    QFile plot_data(file_path);
    plot_data.open(QFile::WriteOnly);
    QTextStream out(&plot_data);
    int n = plots.size();
    out << n << endl;
    for (int i = 0;i < n;i++)
        plots[i].save(out);
    plot_data.close();
}

PlotData::PlotData(QString file_path)
{
    load(file_path);
}
