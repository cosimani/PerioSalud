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

    void setTexto( QString texto );
    void setColor( QString color );
    void setFile( QString file );
    void descargarFotoDentista( QString usuario, QString clave );

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Foto *ui;

    QColor color;

    QImage foto;
    QNetworkAccessManager * manager;

private slots:
    void slot_descargarFoto( QNetworkReply * reply );
    void slot_dibujarFotoPerfil( QString nombre, QString apellido, QString mail, QString url_foto );

};


#endif // FOTO_H
