#ifndef ALGORITHMSET_H
#define ALGORITHMSET_H

#include <QMainWindow>

namespace Ui {
class algorithmSet;
}

class algorithmSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit algorithmSet(QWidget *parent = nullptr);
    ~algorithmSet();

private:
    Ui::algorithmSet *ui;
};

#endif // ALGORITHMSET_H
