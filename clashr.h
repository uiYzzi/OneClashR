#ifndef CLASHR_H
#define CLASHR_H
#include <QString>
#include <yaml-cpp/yaml.h>
#include <QStandardPaths>
#include <fstream>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>

class clashR : public QObject
{
    Q_OBJECT

public:
    explicit clashR(QObject *parent = nullptr);
    void start();
    void close();
    void setsystemproxy();
    void closesystemproxy();
private:
    bool isRuned;
    QString homedir;
    YAML::Node config;
    QProcess *clashr = new QProcess();
    int gethttpport();
    int getsocksport();

};

#endif // CLASHR_H
