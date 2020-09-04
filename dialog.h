#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "plotdata.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(PlotData *pd,QWidget *parent = nullptr);
    ~Dialog();
    void update();

public slots:
    void change();
    void selectionChanged();
    void add();

private slots:
    void on_deleteButton_clicked();

    void on_okButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::Dialog *ui;
    PlotData *plot_data;
};

#endif // DIALOG_H
