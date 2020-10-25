#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>  //Dtk::Widget::moveToCenter(&w); 要调用它，就得引用DWidgetUtil
#include <QTranslator>
#include <QDebug>
#include "clashr.h"

DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication a(argc, argv);
    QTranslator translator;
    translator.load(a.applicationDirPath()+"/translations/OneClashR_" + QLocale::system().name());
     a.setAttribute(Qt::AA_UseHighDpiPixmaps);
     a.loadTranslator();
     a.setOrganizationName("deepin");
     a.setApplicationVersion(DApplication::buildVersion("1.0"));
     //a.setApplicationAcknowledgementPage("https://你的网站");
     //a.setProductIcon(QIcon(":/images/icon.svg"));  //设置Logo
     //a.setProductName("DtkDemo");
     a.setApplicationName("OneClashR"); //只有在这儿修改窗口标题才有效

    MainWindow w;
    w.setMinimumWidth(725);
    w.setMinimumHeight(500);

    w.show();


    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);


    return a.exec();
}
