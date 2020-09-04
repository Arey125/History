#include "dialog.h"
#include "ui_dialog.h"
#include "plotdialog.h"

Dialog::Dialog(PlotData *pd,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonBox->buttons()[1]->setText("Отмена");
    connect(ui->changeButton,SIGNAL(clicked()),this,SLOT(change()));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(add()));
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,this,&Dialog::selectionChanged);

    selectionChanged();
    update();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::add()
{
    plot_data->plots.push_back(Plot());
    auto dialog = new PlotDialog(plot_data->plots.back(),this);
    dialog->exec();
    delete(dialog);
    update();
}

void Dialog::update()
{
    ui->listWidget->clear();
    for (auto &plot_item : plot_data->plots)
        ui->listWidget->addItem(plot_item.name + ", " + plot_item.unit);
}

void Dialog::selectionChanged()
{
    if (ui->listWidget->selectedItems().size() == 0)
    {
        ui->changeButton->setDisabled(1);
        ui->deleteButton->setDisabled(1);
    }
    else
    {
        ui->changeButton->setDisabled(0);
        ui->deleteButton->setDisabled(0);
    }
}

void Dialog::change()
{
    int num = ui->listWidget->currentRow();
    auto dialog = new PlotDialog(plot_data->plots[num],this);
    dialog->exec();
    delete(dialog);
    update();
}

void Dialog::on_deleteButton_clicked()
{
    int num = ui->listWidget->currentRow();
    plot_data->plots.erase(plot_data->plots.begin() + num);
    update();
}

void Dialog::on_okButton_clicked()
{
    close();
}

void Dialog::on_resetButton_clicked()
{

}
