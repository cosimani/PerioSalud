#ifndef FOTO_H
#define FOTO_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace Ui {
class Foto;
}

class Foto : public QWidget
{
    Q_OBJECT

public:
    explicit Foto(QWidget *parent = 0);
    ~Foto();

    enum TipoFoto  { DISCO, URL, API_VAYRA, NINGUNA };

    void setTexto( QString texto );
    void setColor( QString color );
    void descargarFotoDentista( QString usuario, QString clave );
    void dibujarFotoDeDisco( QString recurso );

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Foto *ui;

    QColor color;

    QImage foto;
    QNetworkAccessManager * manager;

    TipoFoto tipoFoto;

private slots:
    void slot_descargarFoto( QNetworkReply * reply );
    void slot_dibujarFotoPerfil( QString nombre, QString apellido, QString mail, QString url_foto );

};


#endif // FOTO_H
