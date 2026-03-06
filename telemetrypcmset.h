#ifndef TELEMETRYPCMSET_H
#define TELEMETRYPCMSET_H

#include <QDialog>

namespace Ui {
class Telemetrypcmset;
}

class Telemetrypcmset : public QDialog
{
    Q_OBJECT

public:
    explicit Telemetrypcmset(QWidget *parent = nullptr);
    ~Telemetrypcmset();

private:
    Ui::Telemetrypcmset *ui;
};

#endif // TELEMETRYPCMSET_H
