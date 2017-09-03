#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class Registro;
class Principal;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;

    Registro * registro;

    Principal * principal;

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void slot_lineEditChanged(QString);
    bool slot_validateFields();
    void slot_start();
    void slot_registrar();
    void slot_init( QString exito, QString usuario, QString password, QString nombre, QString apellido );
};

#endif // LOGIN_H
