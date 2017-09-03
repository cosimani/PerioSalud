#include "visitas.h"
#include "ui_visitas.h"

Visitas::Visitas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visitas)
{
    ui->setupUi(this);

    ui->background->setImage( "background.jpg", FILL );
}

Visitas::~Visitas()
{
    delete ui;
}
