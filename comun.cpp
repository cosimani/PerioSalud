#include "comun.h"

Comun *Comun::instance = NULL;

Comun::Comun(QObject *parent) : QObject(parent)
{

}

QString Comun::getMailDentista() const
{
    return mailDentista;
}

QString Comun::getApellidoDentista() const
{
    return apellidoDentista;
}

QString Comun::getNombreDentista() const
{
    return nombreDentista;
}

QString Comun::getClave() const
{
    return clave;
}

QString Comun::getUsuario() const
{
    return usuario;
}

Comun *Comun::getInstance()
{
    if( !instance )
    {
        instance = new Comun();
    }
    return instance;
}

Comun::~Comun()
{
    delete instance;
}

QString Comun::getApellido() const
{
    return apellido;
}

QString Comun::getNombre() const
{
    return nombre;
}

void Comun::setNombreApellido(QString nombre, QString apellido)
{
    this->nombre = nombre;
    this->apellido = apellido;
}

void Comun::setUsuarioClave(QString usuario, QString clave)
{
    this->usuario = usuario;
    this->clave = clave;
}

void Comun::setNombreApellidoDentista(QString nombre, QString apellido, QString mail)
{
    this->nombreDentista = nombre;
    this->apellidoDentista = apellido;
    this->mailDentista = mail;
}
