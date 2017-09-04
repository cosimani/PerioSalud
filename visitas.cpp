#include "visitas.h"
#include "ui_visitas.h"

#include "comun.h"
#include <QMessageBox>

Visitas::Visitas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visitas)
{
    ui->setupUi(this);

    ui->background->setImage( "background3.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    QFont font("Angelina", this->width()/15);
    ui->lPaciente->setFont(font);
    ui->lPaciente->setText( "Paciente : " +
                            Comun::getInstance()->getNombre() + " " +
                            Comun::getInstance()->getApellido() + "  " );

    connect(ui->calendario, SIGNAL(clicked(QDate)), this, SLOT(slot_clicked(QDate)));
    connect(ui->pbReservarTurno, SIGNAL(pressed()), this, SLOT(slot_reservarTurno()));

    ui->cbDiaHora->addItem( "Seleccione un día para ver horarios");
}

Visitas::~Visitas()
{
    delete ui;
}

void Visitas::slot_clicked(const QDate &date)
{
    ui->cbDiaHora->clear();

    int dia = date.day();
    int mes = date.month();

    QString sMes;

    switch ( mes ) {
    case 1:  sMes = "enero";  break;
    case 2:  sMes = "febrero";  break;
    case 3:  sMes = "marzo";  break;
    case 4:  sMes = "abril";  break;
    case 5:  sMes = "mayo";  break;
    case 6:  sMes = "junio";  break;
    case 7:  sMes = "julio";  break;
    case 8:  sMes = "agosto";  break;
    case 9:  sMes = "septiembre";  break;
    case 10:  sMes = "octubre";  break;
    case 11:  sMes = "noviembre";  break;
    case 12:  sMes = "diciembre";  break;

    default:
        break;
    }

    QStringList listaDias;
    listaDias << QString::number(dia) + " de " + sMes + " : 10:30 horas"
              << QString::number(dia) + " de " + sMes + " : 11:30 horas"
              << QString::number(dia) + " de " + sMes + " : 16:30 horas"
              << QString::number(dia) + " de " + sMes + " : 18:00 horas";

    ui->cbDiaHora->addItems( listaDias );
    ui->pbReservarTurno->setText( "Reservar turno" );
    ui->pbReservarTurno->setEnabled( true );
}

void Visitas::slot_reservarTurno()
{
    QMessageBox::information( this, "Reserva de turno!", "Su turno ha sido reservado con éxito. "
                              "Recibirá un mail con los datos de la reserva.");

    this->hide();

}

void Visitas::showEvent(QShowEvent *)
{
    ui->cbDiaHora->clear();
    ui->cbDiaHora->addItem( "Seleccione un día para ver horarios");
    ui->pbReservarTurno->setText( "Elija el día" );
    ui->pbReservarTurno->setEnabled( false );
}

