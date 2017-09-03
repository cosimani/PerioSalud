#include "login.h"
#include "ui_login.h"

#include "registro.h"
#include "datamanager.hpp"
#include "database.hpp"
#include "principal.h"
#include "comun.h"

Login::Login(QWidget *parent) :
                                QWidget(parent),
                                ui(new Ui::Login),
                                registro( NULL ),
                                principal( NULL )
{
    ui->setupUi(this);

    ui->logo->soyLogo();  // Emi
    ui->background->setImage( "background.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    ui->startButton->setFixedHeight( 2 * ui->startButton->sizeHint().height() );
    ui->pbRegistrate->setFixedHeight( 2 * ui->pbRegistrate->sizeHint().height() );

    ui->leUsuario->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_]+" ), this ) );
    ui->lePassword->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_]+" ), this ) );

    connect( ui->leUsuario, SIGNAL( textChanged( QString ) ), SLOT( slot_lineEditChanged( QString ) ) );
    connect( ui->lePassword, SIGNAL( textChanged( QString ) ), SLOT( slot_lineEditChanged( QString ) ) );

    connect( ui->pbRegistrate, SIGNAL( pressed() ), SLOT( slot_registrar() ) );
    connect( ui->startButton, SIGNAL( pressed() ), SLOT( slot_start() ) );

    connect( DataManager::getInstance(), SIGNAL( readyInit(QString,QString,QString,QString,QString) ),
             this, SLOT( slot_init(QString,QString,QString,QString,QString) ) );

    QStringList data( Database::getInstance()->readData() );
    if( data.size() == 2 )
    {
        ui->leUsuario->setText( data.at( 0 ) );
        ui->lePassword->setText( data.at( 1 ) );
    }

    this->setAttribute(Qt::WA_DeleteOnClose);


}

Login::~Login()
{
    delete ui;
}

void Login::resizeEvent( QResizeEvent* )
{
    QImage logo;
    logo.load( ":/resources/images/ubp.png" );
    ui->logo->setFixedSize( this->width(), logo.height() * this->width() / ( float )logo.width() );
}

void Login::slot_lineEditChanged( QString )
{
    ui->lError->clear();
}

bool Login::slot_validateFields()
{
    QString usuario( ui->leUsuario->text().toLower().simplified() );
    QString password( ui->lePassword->text() );

    bool error = usuario.isEmpty() || password.isEmpty();

    if( error )
    {
        ui->lError->setText( "Completa los campos" );
    }
    else
    {
        ui->lError->clear();
    }

    return !error;
}

void Login::slot_start()
{
    if( !slot_validateFields() )
    {
        return;
    }

    ui->leUsuario->setEnabled( false );
    ui->lePassword->setEnabled( false );
    ui->startButton->setEnabled( false );

    QString usuario( ui->leUsuario->text().toLower().simplified() );
    QString password( ui->lePassword->text() );

    if( !DataManager::getInstance()->requestLogin( usuario, password ) )
    {
        qDebug() << "Solicitud inicial incorrecta";
    }
    else
    {
        qDebug() << "Solicitud inicial correcta";
    }
}

void Login::slot_registrar()  {

    //    Si no se hace close() ni hide(), entonces con el boto atras de celu, se vuelve a mostrar el widget anterior
    //    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
    //    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
    if ( registro == NULL )  // Para crearlo solo la primera vez
        registro = new Registro;

    registro->show();

}

void Login::slot_init( QString exito, QString usuario, QString password, QString nombre, QString apellido )
{
    if ( exito == "exito" )  {
        qDebug() << "slot_init" << "exito" << usuario << password << nombre << apellido;

        Database::getInstance()->saveData( usuario, password );

        Comun::getInstance()->setNombreApellido( nombre, apellido );
        Comun::getInstance()->setUsuarioClave( usuario, password );

//    Si no se hace close() ni hide(), entonces con el boton atras de celu, se vuelve a mostrar el widget anterior
    this->close();  // Ojo que al estar seteado con this->setAttribute(Qt::WA_DeleteOnClose); se destruye con close()
//    this->hide();  // Se oculta pero no se destruye, y con el boton atras del celu, no vuelve sino que se cierra
        if ( principal == NULL )  // Para crearlo solo la primera vez
            principal = new Principal;

        principal->show();


    }
}
