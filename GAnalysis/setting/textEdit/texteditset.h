#ifndef TEXTEDITSET_H
#define TEXTEDITSET_H

#include <QMainWindow>
//#include"setting/settingmainwindow.h"
namespace Ui {
class TextEditSet;
}

class TextEditSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditSet(QWidget *parent = nullptr);
    ~TextEditSet();

private:
    Ui::TextEditSet *ui;
};

#endif // TEXTEDITSET_H
