#include "foto.h"
#include "ui_foto.h"
#include <QPainter>
#include "datamanager.hpp"
#include "comun.h"

Foto::Foto(QWidget *parent) : QWidget(parent),
                              ui(new Ui::Foto),
                              manager( new QNetworkAccessManager( this ) ),
                              tipoFoto( NINGUNA )
{
    ui->setupUi(this);

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    QFont font( "Angelina", this->width()/15, QFont::Bold );
    ui->lMail->setFont(font);
    ui->lNombreCompleto->setFont(font);

    connect( manager, SIGNAL( finished(QNetworkReply*) ), this, SLOT (slot_descargarFoto(QNetworkReply*) ) );

    connect( DataManager::getInstance(), SIGNAL( readyFotoDentista( QString,QString,QString,QString) ),
             this, SLOT( slot_dibujarFotoPerfil( QString,QString,QString,QString) ) );
}

Foto::~Foto()
{
    delete ui;
}

void Foto::setTexto(QString texto)
{
    ui->lNombreCompleto->setText( texto );
    ui->lMail->clear();
}

void Foto::setColor(QString color)
{
    this->color = QColor( color );
    this->repaint();
}


/**
 * @brief Foto::descargarFotoDentista Descarga la foto de perfil del dentista que tiene este usuario
 * @param usuario
 * @param clave
 */
void Foto::descargarFotoDentista(QString usuario, QString clave)
{
    tipoFoto = API_VAYRA;

    // Para que no descargue nuevamente la foto si ya se descargo antes
    if ( foto.isNull() )
        DataManager::getInstance()->requestFotoDentista( usuario, clave );
}

void Foto::dibujarFotoDeDisco(QString recurso)
{
    tipoFoto = DISCO;

    ui->lNombreCompleto->clear();
    ui->lMail->clear();

    foto.load( recurso );
    this->repaint();
}

void Foto::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    color.setAlpha( 190 );
    painter.fillRect( 0,0, this->width(), this->height(), color );

    foto = foto.scaled( this->width(), this->height() );

    painter.drawImage( 0, 0, foto );
}

void Foto::slot_descargarFoto(QNetworkReply *reply)
{
    foto = QImage::fromData( reply->readAll() );
    repaint();
}

void Foto::slot_dibujarFotoPerfil( QString nombre, QString apellido, QString mail, QString url_foto )
{
    if ( tipoFoto == API_VAYRA )  {
        // le pongo el .simplified() porque aparece un \n en la url que complica la descarga
        manager->get( QNetworkRequest( QUrl( url_foto.simplified() ) ) );

        Comun::getInstance()->setNombreApellidoDentista( nombre, apellido, mail );

        ui->lNombreCompleto->setText( nombre + " " + apellido );
        ui->lMail->setText( mail );
    }
}
