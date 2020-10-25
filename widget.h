#ifndef WIDGET_H
#define WIDGET_H
#include <QUrl>
#include "clashr.h"
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <DGuiApplicationHelper>//用来适配深色模式 Used to adapt to dark model
#include <DLabel>
DWIDGET_USE_NAMESPACE
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    QColor main_color;
    int httpport;
    int socksport;

    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool themeIsDark;

private:
    void setTheme(DGuiApplicationHelper::ColorType);
    void chooseLeftMenu(int index);
    void updateUI();
    void downloadconfig();
    QString theme;
    QUrl menuUrl[6];
    int nowMenu=0; //定位当前菜单
    QPushButton * left_list[7];
    Ui::Widget *ui;
};

#endif // WIDGET_H
