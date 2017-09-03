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
};

#endif // VISITAS_H
