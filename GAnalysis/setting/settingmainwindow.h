#ifndef SETTINGMAINWINDOW_H
#define SETTINGMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingMainWindow;
}

class SettingMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingMainWindow(QWidget *parent = nullptr);
    ~SettingMainWindow();

    void setLayout();
private:
    Ui::SettingMainWindow *ui;
};

#endif // SETTINGMAINWINDOW_H
