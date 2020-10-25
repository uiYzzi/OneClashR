#include "mainwindow.h"
#include "widget.h"
#include "clashr.h"
#include <DMainWindow>
#include <DTitlebar>
#include <DGuiApplicationHelper>
#include <QDebug>
DWIDGET_USE_NAMESPACE
extern int httpport;
extern int socksport;

bool system_proxy_checkable;
MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_menu(new QMenu),
      system_proxy(new QAction(tr("Enable system proxy")))
{
    w = new Widget;
    clash->start();

    m_menu->addAction(system_proxy);

    system_proxy_checkable=true;
    system_proxy->setCheckable(true);
    system_proxy->setChecked(system_proxy_checkable);
    titlebar()->setMenu(m_menu);
    resize(w->size()); //设置窗口大小

    setCentralWidget(w);
    bool i=true;
    connect(system_proxy,&QAction::triggered,[=]()
    {
        qDebug()<<system_proxy_checkable;
        system_proxy_checkable=!system_proxy_checkable;
        qDebug()<<system_proxy_checkable;
        if(system_proxy_checkable)
        {
            system_proxy->setChecked(system_proxy_checkable);
            clash->setsystemproxy();
        }
        else
        {
            system_proxy->setChecked(system_proxy_checkable);
            clash->closesystemproxy();
        }
    });

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    clash->close();
}
MainWindow::~MainWindow()
{

}
