#include "algorithmset.h"
#include "ui_algorithmset.h"

algorithmSet::algorithmSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::algorithmSet)
{
    ui->setupUi(this);
}

algorithmSet::~algorithmSet()
{
    delete ui;
}
