#include "midentista.h"
#include "ui_midentista.h"
#include "comun.h"
#include "visitas.h"

MiDentista::MiDentista(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MiDentista),
                                          visitas( NULL )
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    ui->fotoPerfil->descargarFotoDentista( Comun::getInstance()->getUsuario(), Comun::getInstance()->getClave() );

    ui->pbVisitas->setColor( "#673ab7" );  ui->pbVisitas->setTexto( "Solicitar turno" );
    ui->b2->setColor( "#3f51b5" );  ui->b2->setTexto( "Enviar mensaje" );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    QFont font("Angelina", this->width()/15);
    ui->lPaciente->setFont(font);
    ui->lPaciente->setText( "Paciente : " +
                            Comun::getInstance()->getNombre() + " " +
                            Comun::getInstance()->getApellido() + "  " );

    connect(ui->pbVisitas, SIGNAL(clic()), this, SLOT(showVisitas()));



}

MiDentista::~MiDentista()
{
    delete ui;
}

void MiDentista::showVisitas()
{
    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
//    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
    //    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
    if ( visitas == NULL )  // Para crearlo solo la primera vez
        visitas = new Visitas;

    visitas->show();

}

