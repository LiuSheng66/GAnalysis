#include "algorithmset.h"
#include "ui_algorithmset.h"
#include<QDebug>
#include<QVBoxLayout>
algorithmSet::algorithmSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::algorithmSet)  
  ,m_pButtonGroup(new QButtonGroup)
  ,radioBtn_ZhuDian(new QRadioButton)
  ,radioBtn_DDA(new QRadioButton)
  ,resetBtn(new QPushButton)
{
    ui->setupUi(this);

    algorithmInit();
}

algorithmSet::~algorithmSet()
{
    delete ui;
}

void algorithmSet::algorithmInit()
{
    QVBoxLayout *pLayout = new QVBoxLayout();

    // 设置互斥,默认就是true
    m_pButtonGroup->setExclusive(true);

    // 设置文本
    radioBtn_ZhuDian->setFont(QFont("宋体",12));
    radioBtn_DDA->setFont(QFont("宋体",12));
    resetBtn->setFont(QFont("Times New Roman",12));
    radioBtn_ZhuDian->setText(QString::fromLocal8Bit("%1").arg("逐点比较法"));
    radioBtn_DDA->setText(QString::fromLocal8Bit("%1").arg("DDA(数字积分法)"));

    resetBtn->setText("Reset");

    pLayout->addWidget(radioBtn_ZhuDian);
    pLayout->addWidget(radioBtn_DDA);
    pLayout->addWidget(resetBtn);

    m_pButtonGroup->addButton(radioBtn_ZhuDian);
    m_pButtonGroup->addButton(radioBtn_DDA);

    pLayout->setSpacing(5);
    pLayout->setContentsMargins(50, 5, 200, 300);

    ui->tab->setLayout(pLayout);

    radioBtn_ZhuDian->setChecked(true);//设置默认的选择项，当时不代表配置文件选择项一模一样

    // 连接信号槽
    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

void algorithmSet::onButtonClicked(QAbstractButton *button)
{
    if(button==radioBtn_ZhuDian)
    {

    setConfi("C://Users//Administrator//Desktop//homework//CONFIG.ini","algorithmSet","fireMode","ZhuDian");
    };
    if(button==radioBtn_DDA)
    {
    setConfi("C://Users//Administrator//Desktop//homework//CONFIG.ini","algorithmSet","fireMode","DDA");
    };
}
