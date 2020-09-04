#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <qcustomplot.h>
#include "plotdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void replot();
    void updateUnits();

public slots:
    void change();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *changeButton;
    QCustomPlot *plot;
    PlotData plot_data;
    double xmx,xmn;
    map<QString,double> ymx;
    map<QString,double> ymn;
    QString unit;
    QVector<QString> units;
};
#endif // MAINWINDOW_H
