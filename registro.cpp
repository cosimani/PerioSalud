#include "registro.h"
#include "ui_registro.h"

#include "datamanager.hpp"
#include "database.hpp"

Registro::Registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);

    ui->background->setImage( "background.jpg", FILL );

    QPalette palette = this->palette();
    palette.setColor( QPalette::WindowText, QColor( 255, 255, 255 ) );
    this->setPalette( palette );

    ui->startButton->setFixedHeight( 2 * ui->startButton->sizeHint().height() );

    ui->leUsuario->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_]+" ), this ) );
    ui->lePassword->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_]+" ), this ) );
    ui->leRePassword->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_]+" ), this ) );

    connect( ui->lePassword, SIGNAL( textChanged( QString ) ), SLOT( slot_matchPasswords( QString ) ) );
    connect( ui->leRePassword, SIGNAL( textChanged( QString ) ), SLOT( slot_matchPasswords( QString ) ) );

    connect( ui->showPasswordsCheckBox, SIGNAL( toggled( bool ) ), SLOT( slot_changePasswordEchoMode( bool ) ) );

    ui->leNombre->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z ]+" ), this ) );
    ui->leApellido->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z ]+" ), this ) );
    ui->leMail->setValidator(new QRegExpValidator( QRegExp( "[A-Za-z0-9_@.]+" ), this ) );

    // Pide los dentistas para cargarlos en el Combo Box
    DataManager::getInstance()->requestListaDentistas();

    connect( DataManager::getInstance(), SIGNAL( readyListaDentistas(QStringList) ),
             this, SLOT( slot_cargarDentistasEnComboBox(QStringList) ) );


//    connect( ui->leNombre, SIGNAL( textChanged( QString ) ), SLOT( lineEditChanged( QString ) ) );
//    connect( ui->leApellido, SIGNAL( textChanged( QString ) ), SLOT( lineEditChanged( QString ) ) );
//    connect( ui->leMail, SIGNAL( textChanged( QString ) ), SLOT( lineEditChanged( QString ) ) );

    connect( ui->startButton, SIGNAL( pressed() ), this, SLOT( slot_start() ) );

    connect( DataManager::getInstance(), SIGNAL( availableName( bool ) ),
             this, SLOT( slot_publicarEnLabel( bool ) ) );
}

Registro::~Registro()
{
    delete ui;
}

bool Registro::slot_matchPasswords( QString )
{
    bool ok = ( ui->lePassword->text() == ui->leRePassword->text() );
    if( !ok )
    {
        ui->lError->setText( "Las contraseñas no coinciden" );
    }
    else
    {
        ui->lError->clear();
    }
    return ok;
}

void Registro::slot_lineEditChanged( QString )
{
    ui->lError->clear();
}

bool Registro::slot_validateFields()
{
    QString usuario( ui->leUsuario->text().toLower().simplified() );
    QString password( ui->lePassword->text() );
    QString rePassword( ui->leRePassword->text() );

    QString nombre( ui->leNombre->text().toLower().simplified() );
    QString apellido( ui->leApellido->text().toLower().simplified() );
    QString mail( ui->leMail->text().toLower().simplified() );

    bool error = ( usuario.isEmpty() ||
                   password.isEmpty() ||
                   rePassword.isEmpty() ||
                   nombre.isEmpty() ||
                   apellido.isEmpty() ||
                   mail.isEmpty() );

    if( error )
    {
        ui->lError->setText( "Algún campo está incompleto" );
    }
    else
    {
        ui->lError->clear();
    }

    return !error;
}

void Registro::slot_changePasswordEchoMode( bool checked )
{
    ui->lePassword->setEchoMode( checked ? QLineEdit::Normal : QLineEdit::Password );
    ui->leRePassword->setEchoMode( checked ? QLineEdit::Normal : QLineEdit::Password );
}

void Registro::slot_start()
{
    if( !slot_validateFields() ) return;
    if( !this->slot_matchPasswords( "" ) ) return;

    ui->leUsuario->setEnabled( false );
    ui->lePassword->setEnabled( false );
    ui->leRePassword->setEnabled( false );
    ui->leNombre->setEnabled( false );
    ui->leApellido->setEnabled( false );
    ui->leMail->setEnabled( false );
    ui->startButton->setEnabled( false );
    ui->cbDentistas->setEnabled( false );

    QString usuario( ui->leUsuario->text().toLower().simplified() );
    QString password( ui->lePassword->text() );
    QString nombre( ui->leNombre->text().simplified() );
    QString apellido( ui->leApellido->text().simplified() );
    QString mail( ui->leMail->text().toLower().simplified() );

    Database::getInstance()->saveData( usuario, password );

    QString id_dentista = "-1";
    int indexActual = ui->cbDentistas->currentIndex();  // El primer index es 1, luego 2, 3, 4, etc
    if ( idDentistasEnComboBox.size() >= indexActual )  {
        id_dentista = idDentistasEnComboBox.at( indexActual ).second;
    }

    if( !DataManager::getInstance()->requestInit( usuario,
                                                  password,
                                                  nombre,
                                                  apellido,
                                                  mail,
                                                  id_dentista ) )
    {
        qDebug() << "No se pudo iniciar el juego";
    }
}

void Registro::slot_cargarDentistasEnComboBox( QStringList dentistas )
{
    while ( dentistas.size() > 0 )  {

        QStringList unSoloDentista( dentistas.at( 0 ).split( "||" ) );

        if ( unSoloDentista.size() == 3 )  {
            QString id_dentista = unSoloDentista.at( 0 );
            QString nombre = unSoloDentista.at( 1 );
            QString apellido = unSoloDentista.at( 2 );

            ui->cbDentistas->addItem( nombre + " " + apellido );

            QPair< int, QString > par;

            par.first = ui->cbDentistas->count() - 1;
            par.second = id_dentista;

            idDentistasEnComboBox.append( par );

            qDebug() << idDentistasEnComboBox;
        }

        dentistas.removeFirst();
    }

}

void Registro::slot_publicarEnLabel(bool exito)
{
    if ( ! exito )  {
        ui->lError->setText( "Usuario o mail ya se encuentran en uso." );

        ui->leUsuario->setEnabled( true );
        ui->lePassword->setEnabled( true );
        ui->leRePassword->setEnabled( true );
        ui->leNombre->setEnabled( true );
        ui->leApellido->setEnabled( true );
        ui->leMail->setEnabled( true );
        ui->startButton->setEnabled( true );
        ui->cbDentistas->setEnabled( true );

//        ui->leUsuario->clear();
//        ui->lePassword->clear();
//        ui->leRePassword->clear();
//        ui->leNombre->clear();
//        ui->leApellido->clear();
//        ui->leMail->clear();
    }
}
