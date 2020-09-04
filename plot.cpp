#include "plot.h"

Plot::Plot(QTextStream &in)
{
    int n;
    in >> n;
    int r,g,b;
    in >> r >> g >> b;
    color = QColor(r,g,b);
    in.readLine();
    name = in.readLine();
    unit = in.readLine();
    for (int i = 0;i < n;i++)
    {
        double a,b;
        in >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }
}

Plot::Plot()
{
    int r = 255,g = 0,b = 0;
    color = QColor(r,g,b);
    name = "";
    unit = "";
}

void Plot::save(QTextStream &out)
{
    int n = x.size();
    out << n << endl;
    int r,g,b;
    color.getRgb(&r,&g,&b);
    out << r << " " << g << " " << b << endl;
    out << name << endl << unit << endl;
    for (int i = 0;i < n;i++)
        out << x[i] << " " << y[i] << endl;
}
