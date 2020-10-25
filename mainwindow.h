#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QMenu>

#include "widget.h"
DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Widget *w;
    QAction *system_proxy;
    QMenu *m_menu;
    clashR *clash=new clashR(this);


    virtual void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
