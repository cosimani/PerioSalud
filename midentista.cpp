#include "midentista.h"
#include "ui_midentista.h"
#include "comun.h"

MiDentista::MiDentista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiDentista)
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    ui->fotoPerfil->descargarFotoDentista( Comun::getInstance()->getUsuario(), Comun::getInstance()->getClave() );

    ui->b1->setColor( "#673ab7" );  ui->b1->setTexto( "Solicitar turno" );
    ui->b2->setColor( "#3f51b5" );  ui->b2->setTexto( "Preguntar por mensaje" );
    ui->b3->setColor( "#009688" );  ui->b3->setTexto( "Enviar mail" );

}

MiDentista::~MiDentista()
{
    delete ui;
}
