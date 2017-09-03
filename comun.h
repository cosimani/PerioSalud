#ifndef COMUN_H
#define COMUN_H

#include <QObject>

/**
 * @brief The Comun class es una clase que mantiene informacion comun para ser utilizada de cualquier lado
 */
class Comun : public QObject
{
    Q_OBJECT

private:
    static Comun *instance;
    explicit Comun( QObject *parent = NULL );

    QString nombre, apellido;
    QString usuario, clave;
    QString nombreDentista, apellidoDentista, mailDentista;

public:
    static Comun *getInstance();

    void setNombreApellido( QString nombre, QString apellido );
    void setUsuarioClave( QString usuario, QString clave );
    void setNombreApellidoDentista( QString nombre, QString apellido, QString mail );
    QString getNombre() const;
    QString getApellido() const;
    QString getUsuario() const;
    QString getClave() const;
    QString getNombreDentista() const;
    QString getApellidoDentista() const;
    QString getMailDentista() const;

    ~Comun();



signals:

public slots:


};

#endif // COMUN_H
