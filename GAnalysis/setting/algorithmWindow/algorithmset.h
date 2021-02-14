#ifndef ALGORITHMSET_H
#define ALGORITHMSET_H

#include <QMainWindow>
#include<QButtonGroup>
#include<QRadioButton>
#include<QPushButton>
#include "configure/appconfigure.h"
namespace Ui {
class algorithmSet;
}

class algorithmSet : public QMainWindow,public AppConfigure
{
    Q_OBJECT

public:
    explicit algorithmSet(QWidget *parent = nullptr);
    ~algorithmSet();

    void algorithmInit();

protected slots:
    void onButtonClicked(QAbstractButton *button);
private:
    QButtonGroup *m_pButtonGroup;

    QRadioButton *radioBtn_ZhuDian;//单选按钮——逐点比较法
    QRadioButton *radioBtn_DDA;//单选按钮——DDA

    QPushButton *resetBtn;//算法的默认设置按钮
private:
    Ui::algorithmSet *ui;
};

#endif // ALGORITHMSET_H
