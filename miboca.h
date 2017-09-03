#ifndef MIBOCA_H
#define MIBOCA_H

#include <QWidget>

namespace Ui {
class Miboca;
}

class Miboca : public QWidget
{
    Q_OBJECT

public:
    explicit Miboca(QWidget *parent = 0);
    ~Miboca();

private:
    Ui::Miboca *ui;
};

#endif // MIBOCA_H
