#ifndef MIDENTISTA_H
#define MIDENTISTA_H

#include <QWidget>

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
};

#endif // MIDENTISTA_H
