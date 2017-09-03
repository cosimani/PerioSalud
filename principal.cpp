#include "principal.h"
#include "ui_principal.h"

#include "comun.h"

#include "midentista.h"
#include "visitas.h"
#include "miboca.h"

Principal::Principal(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::Principal),
                                        miDentista( NULL ),
                                        visitas( NULL ),
                                        miboca( NULL )
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    ui->pbMiDentista->setColor( "#e91e63" );  ui->pbMiDentista->setTexto( "Mi dentista" );
    ui->pbVisitas->setColor( "#9c27b0" );  ui->pbVisitas->setTexto( "Visitas" );
    ui->b3->setColor( "#673ab7" );  ui->b3->setTexto( "Técnicas de higiene" );
    ui->pbMiboca->setColor( "#3f51b5" );  ui->pbMiboca->setTexto( "Mi boca" );
    ui->b5->setColor( "#009688" );  ui->b5->setTexto( "Hora de cepillarse" );

    connect(ui->pbMiDentista, SIGNAL(clic()), this, SLOT(showMiDentista()));
    connect(ui->pbVisitas, SIGNAL(clic()), this, SLOT(showVisitas()));
    connect(ui->pbMiboca, SIGNAL(clic()), this, SLOT(showMiboca()));

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    QFont font("Angelina", this->width()/15);
    ui->lPaciente->setFont(font);
    ui->lPaciente->setText( "Paciente : " +
                            Comun::getInstance()->getNombre() + " " +
                            Comun::getInstance()->getApellido() + "  " );

}

Principal::~Principal()
{
    delete ui;
}

void Principal::resizeEvent( QResizeEvent* )
{
}

void Principal::showMiDentista()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
//    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
    //    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
    if ( miDentista == NULL )  // Para crearlo solo la primera vez
        miDentista = new MiDentista;

    miDentista->show();
}

void Principal::showVisitas()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
//    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
    //    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
    if ( visitas == NULL )  // Para crearlo solo la primera vez
        visitas = new Visitas;

    visitas->show();

}

void Principal::showMiboca()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
//    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
    //    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
    if ( miboca == NULL )  // Para crearlo solo la primera vez
        miboca = new Miboca;

    miboca->show();

}

