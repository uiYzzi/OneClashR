#include "widget.h"
#include "clashr.h"
#include "ui_widget.h"
#include <QNetworkAccessManager>
#include <DGuiApplicationHelper>
#include <DMainWindow>
#include <QDebug>
#include <QWebEngineSettings>
#include <QTranslator>
#include <QProcess>
#include <QStandardPaths>
#include <QDir>
#include <fstream>
#include <yaml-cpp/yaml.h>
using namespace std;
DWIDGET_USE_NAMESPACE
extern QColor main_color;
extern int httpport;
extern int socksport;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);


    main_color=DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
    // 初始化菜单数组
    left_list[0]=ui->menu_Overview;
    left_list[1]=ui->menu_Proxies;
    left_list[2]=ui->menu_Rules;
    left_list[3]=ui->menu_Connections;
    left_list[4]=ui->menu_Config;
    left_list[5]=ui->menu_Logs;
    left_list[6]=ui->menu_Subscribe;

    left_list[0]->setIcon(QIcon(":/icon/Overview.svg"));
    left_list[1]->setIcon(QIcon(":/icon/Proxies.svg"));
    left_list[2]->setIcon(QIcon(":/icon/Rules.svg"));
    left_list[3]->setIcon(QIcon(":/icon/Connections.svg"));
    left_list[4]->setIcon(QIcon(":/icon/Config.svg"));
    left_list[5]->setIcon(QIcon(":/icon/Logs.svg"));
    left_list[6]->setIcon(QIcon(":/icon/Subscribe.svg"));

    connect(ui->menu_Overview,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(0);});
    connect(ui->menu_Proxies,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(1);});
    connect(ui->menu_Rules,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(2);});
    connect(ui->menu_Connections,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(3);});
    connect(ui->menu_Config,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(4);});
    connect(ui->menu_Logs,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(5);});
    connect(ui->menu_Subscribe,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(6);});
    connect(ui->lineEdit,SIGNAL(returnPressed()), this, SLOT(downloadconfig()));

    ui->webfoot->hide();
    ui->webEngineView->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);
    ui->webEngineView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->stackedWidget->setCurrentIndex(0);

    //让程序适配浅色模式和深色模式 Adapt the program to light and dark model
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&Widget::setTheme);
}
void Widget::downloadconfig()
{
    //QNetworkAccessManager *manager = new QNetworkAccessManager(this);//下载管理
    system("wget -O "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toUtf8()+"/.config/OneClashR/clashr/config.yaml "+ui->lineEdit->text().toUtf8());
    system("notify-send 订阅下载完毕,请手动重启一下本软件");

}
void Widget::updateUI()
{
    QTranslator translator;
    if(QLocale::system().name()=="zh_CN"){
        menuUrl[0]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/";
        menuUrl[1]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/proxies";
        menuUrl[2]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/rules";
        menuUrl[3]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/connections";
        menuUrl[4]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/configs";
        menuUrl[5]="qrc:/yacd/zh_CN/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/logs";
    }else {
        menuUrl[0]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/";
        menuUrl[1]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/proxies";
        menuUrl[2]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/rules";
        menuUrl[3]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/connections";
        menuUrl[4]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/configs";
        menuUrl[5]="qrc:/yacd/en-US/index.html?theme="+theme+"&hostname=127.0.0.1&port=9090#/logs";
    }


    for (int i=0;i<7;i++) {
        left_list[i]->setFont(QFont("",11));
        left_list[i]->setFixedHeight(38);
        if(themeIsDark){
            left_list[i]->setStyleSheet("text-align:left;padding-left:12px;color:#FFFFFF;border:0px");
        }else {
            left_list[i]->setStyleSheet("text-align:left;padding-left:12px;color:#252525;border:0px");
        }
    }

    left_list[nowMenu]->setStyleSheet("text-align:left;padding-left:12px;color:#FFFFFF;background-color:"+main_color.name()+";border-radius:8;border:0px");
    if(nowMenu<=5)
    {
        ui->webEngineView->setUrl(menuUrl[nowMenu]);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

// 菜单切换逻辑
void Widget::chooseLeftMenu(int index)
{
    nowMenu=index;

    updateUI();
    left_list[index]->setStyleSheet("text-align:left;padding-left:12px;color:#FFFFFF;background-color:"+main_color.name()+";border-radius:8;border:0px");
    if(nowMenu==6)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}
void Widget::setTheme(DGuiApplicationHelper::ColorType themes)
{
    //这个函数在程序运行之初就会被调用一次，而后每次更换主题颜色时被调用。 This function is called at the beginning of the program and then every time the theme color is changed.
    if(themes==DGuiApplicationHelper::LightType){ //在这个位置设置两种不同的样式 Set two different styles at this location
        //浅色模式 Light Mode
        qDebug()<<"Lighe";
        themeIsDark=false;
        theme="light";
        ui->webfoot->setStyleSheet("background-color:#FFFFFF");
        ui->widget_menuList->setStyleSheet("background-color:#FFFFFF;");
        ui->label_2->setStyleSheet("font-size:22pt;color:#222222;padding-left:19px;font-weight: bold;");
        ui->lineEdit->setStyleSheet("background-color:#FFFFFF;");
        updateUI();
    }else {
        //深色模式 Dark Mode
        qDebug()<<"Dark";
        themeIsDark=true;
        theme="dark";
        ui->webfoot->setStyleSheet("background-color:#252525");
        ui->widget_menuList->setStyleSheet("background-color:#282828;");
        ui->label_2->setStyleSheet("font-size:22pt;color:#DDDDDD;padding-left:19px;font-weight: bold;");
        ui->lineEdit->setStyleSheet("background-color:#2D2D30;");
        updateUI();
    }
}


Widget::~Widget()
{
    delete ui;
}
