#include "texteditset.h"
#include "ui_texteditset.h"

TextEditSet::TextEditSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditSet)
{
    ui->setupUi(this);
}

TextEditSet::~TextEditSet()
{
    delete ui;
}
