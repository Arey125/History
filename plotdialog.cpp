#include "plotdialog.h"
#include "ui_plotdialog.h"
#include <QtDebug>
#include <QColorDialog>

PlotDialog::PlotDialog(Plot &p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(colorClick()));
    plot = &p;
    load();
}

void PlotDialog::updateColor()
{
    int r,g,b;
    color.getRgb(&r,&g,&b);
    auto str = QString("background-color:rgb(%1,%2,%3);").arg(r).arg(g).arg(b);
    ui->pushButton->setStyleSheet(str);
}

void PlotDialog::load()
{
    ui->nameEdit->setText(plot->name);
    ui->unitEdit->setText(plot->unit);
    color = plot->color;
    updateColor();
    auto table = ui->tableWidget;
    table->setVerticalHeaderLabels({"x","y"});
    int n = plot->x.size();
    table->setRowCount(2);
    table->setColumnCount(n);
    for(int i = 0;i < n;i++)
    {
        table->setItem(0,i,new QTableWidgetItem(QString::number(plot->x[i])));
        table->setItem(1,i,new QTableWidgetItem(QString::number(plot->y[i])));
    }
}

void PlotDialog::update()
{
    plot->name = ui->nameEdit->text();
    plot->unit = ui->unitEdit->text();
    plot->color = color;
    auto table = ui->tableWidget;
    int n = ui->tableWidget->columnCount();
    plot->x = QVector<double>(n);
    plot->y = QVector<double>(n);
    for(int i = 0;i < n;i++)
    {
        plot->x[i] = table->takeItem(0,i)->text().toDouble();
        plot->y[i] = table->takeItem(1,i)->text().toDouble();
    }
}

void PlotDialog::colorClick()
{
    color = QColorDialog::getColor(color);
    updateColor();
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::on_addButton_clicked()
{
    int n = ui->tableWidget->columnCount();
    ui->tableWidget->insertColumn(n);
    ui->tableWidget->setItem(0,n,new QTableWidgetItem(QString::number(0)));
    ui->tableWidget->setItem(1,n,new QTableWidgetItem(QString::number(0)));
}

void PlotDialog::on_deleteButton_clicked()
{
    auto ranges = ui->tableWidget->selectedRanges();
    QSet<int> col_set;
    for(auto range : ranges)
    {
        for (int i = 0;i < range.columnCount();i++)
            col_set.insert(range.leftColumn() + i);
    }
    QVector<int> col(col_set.begin(),col_set.end());
    reverse(col.begin(),col.end());
    for (int val : col)
        ui->tableWidget->removeColumn(val);
}

void PlotDialog::on_okButton_clicked()
{
    update();
    close();
}

void PlotDialog::on_cancelButton_clicked()
{
    close();
}
