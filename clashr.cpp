#include "clashr.h"
#include <QDebug>
clashR::clashR(QObject *parent) : QObject(parent)
{

}
void clashR::start()
{
    homedir=QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QDir dir;
    dir.mkpath(homedir+"/.config/OneClashR/clashr");
    QFile file(homedir+"/.config/OneClashR/config.yaml");
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
        QFile::copy(":/Country.mmdb",homedir+"/.config/OneClashR/clashr/Country.mmdb");
        QFile::copy(":/config.yaml",homedir+"/.config/OneClashR/clashr/config.yaml");
        isRuned=true;
    }else
    {
        isRuned=false;
    }
    YAML::Node f1 = YAML::LoadFile(homedir.toStdString()+"/.config/OneClashR/config.yaml");

    QString yamldir=homedir+"/.config/OneClashR/clashr/config.yaml";

    config = YAML::LoadFile(yamldir.toStdString());
    std::ofstream fout(yamldir.toStdString());
    config["external-controller"] = "127.0.0.1:9090";
    fout << config;
    fout.close();

    QString program = QCoreApplication::applicationDirPath()+"/clashr/clashr";
    QStringList arguments;
    arguments << "-d"<<homedir+"/.config/OneClashR/clashr";

    clashr->start(program,arguments);
    clashR::setsystemproxy();
}
void clashR::close()
{
    clashR::closesystemproxy();
    clashr->close();
}
int clashR::gethttpport()
{
    return  config["port"].as<int>();
}
int clashR::getsocksport()
{
    return  config["socks-port"].as<int>();
}
void clashR::setsystemproxy()
{
    int httpport=clashR::gethttpport();
    int socksport=clashR::getsocksport();
    QString cmd;
    cmd="gsettings set org.gnome.system.proxy.http host '127.0.0.1'";
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy.http port "+QString::number(httpport);
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy.https host '127.0.0.1'";
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy.https port "+QString::number(httpport);
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy.socks host '127.0.0.1'";
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy.socks port "+QString::number(socksport);
    system(cmd.toUtf8());
    cmd="gsettings set org.gnome.system.proxy mode 'manual'";
    system(cmd.toUtf8());
}
void clashR::closesystemproxy()
{
    system("gsettings set org.gnome.system.proxy mode 'none'");//取消系统代理
}
