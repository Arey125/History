#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include "plotdata.h"

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(Plot &p,QWidget *parent = nullptr);
    ~PlotDialog();
    void load();
    void updateColor();
    void update();

public slots:
    void colorClick();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::PlotDialog *ui;
    Plot *plot;
    QColor color;
};

#endif // PLOTDIALOG_H
