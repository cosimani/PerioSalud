#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

class MiDentista;
class Visitas;
class Miboca;

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::Principal *ui;
    MiDentista * miDentista;
    Visitas * visitas;
    Miboca * miboca;


private slots:
    void showMiDentista();
    void showVisitas();
    void showMiboca();
};

#endif // PRINCIPAL_H
