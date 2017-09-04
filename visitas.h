#ifndef VISITAS_H
#define VISITAS_H

#include <QWidget>

namespace Ui {
class Visitas;
}

class Visitas : public QWidget
{
    Q_OBJECT

public:
    explicit Visitas(QWidget *parent = 0);
    ~Visitas();

private:
    Ui::Visitas *ui;

private slots:
    void slot_clicked(const QDate &date);
    void slot_reservarTurno();

protected:
    void showEvent(QShowEvent *);
};

#endif // VISITAS_H
