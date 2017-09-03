#include "database.hpp"

#include <QSqlError>

Database *Database::instance = NULL;

Database::Database( QObject *parent ) :
    QObject( parent )
{
    database = QSqlDatabase::addDatabase( "QSQLITE" );
}

Database *Database::getInstance()
{
    if( !instance )
    {
        instance = new Database();
    }
    return instance;
}

Database::~Database()
{
    delete instance;
}

bool Database::connectDatabase()
{
    database.setDatabaseName( "db.sqlite" );
    return database.open();
}

void Database::disconnectDatabase()
{
    database.close();
}

void Database::borrarTablas()  {
    if( this->connectDatabase() )  {
        QSqlQuery query( database );

        QString queryBorrarTablas;

        queryBorrarTablas = "drop table if exists inicio;";
        query.exec( queryBorrarTablas );

        qDebug() << query.lastError() << query.lastError();

    }

    this->disconnectDatabase();
}

int Database::checkLogin()
{

    if( this->connectDatabase() )
    {
        if( database.tables().contains( "inicio" ) )
        {
            qDebug() << "La tabla inicio ya esta creada";

            QSqlQuery query( database );
            query.exec( "SELECT * FROM inicio" );

            if ( query.size() == 0 )
                qDebug() << "La table inicio no tiene datos";

            while (query.next())  {
                qDebug() << query.value(0).toString() << query.value(1).toString();
            }

            this->disconnectDatabase();
            return 1;
        }
        else
        {
            QSqlQuery query( database );

            QString queryBorrarTablas;

            queryBorrarTablas = "drop table if exists inicio;";
            query.exec( queryBorrarTablas );

            qDebug() << query.lastError() << query.lastError();

            QString queryString;

            queryString = "create table inicio                       "
                          "(                                                "
                          "    usuario          varchar(100)    not null,   "
                          "    password         varchar(100)    not null    "
                          ");";

            bool ok = query.exec( queryString );

            this->disconnectDatabase();

            return ok ? 0 : -1;
        }
    }
    else
    {
        qDebug() << "No se conecto a la base";
        return -1;
    }
}

bool Database::saveData( QString usuario, QString password )
{
    if( this->connectDatabase() )
    {
        QSqlQuery query( database );

        if( !query.exec( "delete from inicio where 1=1;" ) )
        {
            return false;
        }

        QString queryString( QString( "insert into inicio ( usuario, password ) values ( '") +
                             QString( usuario ) +
                             QString( "', '" ) +
                             QString( password ) +
                             QString( "' );" ) );

        bool ok = query.exec( queryString );

        this->disconnectDatabase();

        return ok;
    }
    else
    {
        return false;
    }
}



QStringList Database::readData()
{
    QStringList results;

    if( this->connectDatabase() )
    {
        QSqlQuery query = database.exec( "select usuario, password from inicio limit 1;" );

        if( query.next() )
        {
            results.append( query.value( 0 ).toString() );
            results.append( query.value( 1 ).toString() );
        }
        else
        {
            results.append( "" );
            results.append( "" );
        }

        this->disconnectDatabase();
    }
    else
    {
        results.append( "" );
        results.append( "" );
    }

    return results;
}

