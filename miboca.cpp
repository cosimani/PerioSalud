#include "miboca.h"
#include "ui_miboca.h"

#include "comun.h"

Miboca::Miboca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Miboca)
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

}

Miboca::~Miboca()
{
    delete ui;
}
