#include "telemetrychannelset.h"
#include "ui_telemetrychannelset.h"

TelemetryChannelset::TelemetryChannelset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelemetryChannelset)
{
    ui->setupUi(this);
}

TelemetryChannelset::~TelemetryChannelset()
{
    delete ui;
}
