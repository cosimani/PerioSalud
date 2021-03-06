#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database: public QObject
{
    Q_OBJECT

private:
    static Database *instance;
    explicit Database( QObject *parent = NULL );

    QSqlDatabase database;

    bool connectDatabase();
    void disconnectDatabase();

public:
    static Database *getInstance();
    ~Database();

    int checkLogin();

    bool saveData( QString usuario, QString password );

    QStringList readData();

    void borrarTablas();
};

#endif // DATABASE_HPP
