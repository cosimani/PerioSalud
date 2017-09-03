#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>
#include <QPair>

namespace Ui {
class Registro;
}

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = 0);
    ~Registro();

private:
    Ui::Registro *ui;
    QVector< QPair<int, QString> > idDentistasEnComboBox;  // Mantiene los pares indexComboBox - id_dentista

private slots:
    bool slot_matchPasswords(QString);
    void slot_lineEditChanged(QString);
    bool slot_validateFields();
    void slot_changePasswordEchoMode(bool checked);
    void slot_start();

    void slot_cargarDentistasEnComboBox( QStringList dentistas );

    void slot_publicarEnLabel( bool exito );
};

#endif // REGISTRO_H
