#ifndef TELEMETRYCHANNELSET_H
#define TELEMETRYCHANNELSET_H

#include <QDialog>

namespace Ui {
class TelemetryChannelset;
}

class TelemetryChannelset : public QDialog
{
    Q_OBJECT

public:
    explicit TelemetryChannelset(QWidget *parent = nullptr);
    ~TelemetryChannelset();

private:
    Ui::TelemetryChannelset *ui;
};

#endif // TELEMETRYCHANNELSET_H
