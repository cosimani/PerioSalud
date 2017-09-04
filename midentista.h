#ifndef MIDENTISTA_H
#define MIDENTISTA_H

#include <QWidget>

class Visitas;

namespace Ui {
class MiDentista;
}

class MiDentista : public QWidget
{
    Q_OBJECT

public:
    explicit MiDentista(QWidget *parent = 0);
    ~MiDentista();


private:
    Ui::MiDentista *ui;

    Visitas * visitas;

private slots:
    void showVisitas();

};

#endif // MIDENTISTA_H
