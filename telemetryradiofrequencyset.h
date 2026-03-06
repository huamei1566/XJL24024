#ifndef TELEMETRYRADIOFREQUENCYSET_H
#define TELEMETRYRADIOFREQUENCYSET_H

#include <QDialog>

namespace Ui {
class TelemeTryradioFrequencyset;
}

class TelemeTryradioFrequencyset : public QDialog
{
    Q_OBJECT

public:
    explicit TelemeTryradioFrequencyset(QWidget *parent = nullptr);
    ~TelemeTryradioFrequencyset();

private:
    Ui::TelemeTryradioFrequencyset *ui;
};

#endif // TELEMETRYRADIOFREQUENCYSET_H
