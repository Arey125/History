#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QVector>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changeButton = ui->changeButton;
    connect(changeButton,SIGNAL(clicked()),this,SLOT(change()));
    plot = ui->plot;
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    plot->plotLayout()->addElement(0, 1, subLayout);
    subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0, 0, plot->legend);
    plot->plotLayout()->setColumnStretchFactor(1, 0.001);
    plot->legend->setVisible(true);
    //plot->legend->addElement(50,0,new QCPLayoutElement());
    plot_data.load("data/plot.txt");
    updateUnits();
    replot();
}

void MainWindow::replot()
{
    plot->clearGraphs();
    plot->legend->clear();
    xmx = -1000000000000,xmn = 1000000000000;
    ymx.clear();
    ymn.clear();

    //QVector<QPen> pens = {QPen(Qt::red),QPen(Qt::blue),QPen(Qt::green)};


    for (int i = 0;i < plot_data.plots.size();i++)
    {
        Plot &plot_item = plot_data.plots[i];
        QVector<double> &x = plot_item.x,
                    &y = plot_item.y;

        xmx = max(*max_element(x.begin(),x.end()),xmx);

        if (ymx.count(plot_item.unit))
            ymx[plot_item.unit] = max(*max_element(y.begin(),y.end()),ymx[plot_item.unit]);
        else
            ymx[plot_item.unit] = *max_element(y.begin(),y.end());

        xmn = min(*min_element(x.begin(),x.end()),xmn);

        if (ymn.count(plot_item.unit))
            ymn[plot_item.unit] = min(*min_element(y.begin(),y.end()),ymn[plot_item.unit]);
        else
            ymn[plot_item.unit] = *min_element(y.begin(),y.end());
        plot->addGraph();
        QPen pen(plot_item.color);
        if (plot_item.unit == unit)
            pen.setWidth(3);
        plot->graph(i)->setPen(pen);
        plot->graph(i)->setName(plot_item.name + ", " + plot_item.unit);
    }

    for (int i = 0;i < plot_data.plots.size();i++)
    {
        Plot &plot_item = plot_data.plots[i];
        auto x = plot_item.x;
        auto y = plot_item.y;
        double l1 = ymx[unit]-ymn[unit];
        double l2 = ymx[plot_item.unit]-ymn[plot_item.unit];
        for (auto &v : y)
            v = (v-ymn[plot_item.unit])*l1/l2 + ymn[unit];
        plot->graph(i)->setData(x,y);
        if (plot_item.unit != unit)
            continue;
        y = plot_item.y;
        int num = plot->graphCount();
        plot->addGraph();
        double p = 0,q = 0;
        double sx = 0,sy = 0;
        double b = 0;
        int n = x.size();
        for (int i = 0;i < n;i++)
        {
            p += n*x[i]*y[i];
            q += n*x[i]*x[i];
            sx += x[i];
            sy += y[i];
        }
        p -= sx*sy;
        q -= sx*sx;
        double k = p/q;
        for (int i = 0;i < n;i++)
            b += y[i] - k*x[i];
        b /= double(n);
        QVector<double> y1(n);
        for (int i = 0;i < n;i++)
            y1[i] = k*x[i] + b;
        QPen pen(plot_item.color);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        plot->graph(num)->setPen(pen);
        plot->graph(num)->setData(x,y1);
        plot->graph(num)->setName("Тренд ("+ plot_item.name + ")");
    }

    plot->xAxis->setRange(xmn,xmx);
    plot->xAxis->setLabel("год");
    plot->yAxis->setRange(ymn[unit],ymx[unit]);
    plot->legend->addElement(50,0,new QCPLayoutElement());

    plot->replot();
}

void MainWindow::updateUnits()
{
    QSet<QString> us;
    for (auto plot_item : plot_data.plots)
        us.insert(plot_item.unit);
    units = QVector<QString>(us.begin(),us.end());
    sort(units.begin(),units.end());
    ui->comboBox->clear();
    ui->comboBox->addItems(QStringList(units.toList()));
    unit = ui->comboBox->currentText();
}

void MainWindow::change()
{
    Dialog dialog(&plot_data,this);
    dialog.exec();
    updateUnits();
    replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &curUnit)
{
    unit = curUnit;
    replot();
}

void MainWindow::on_saveButton_clicked()
{
    plot_data.save("data/plot.txt");
}
