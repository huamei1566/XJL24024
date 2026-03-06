#include "telemetrypcmset.h"
#include "ui_telemetrypcmset.h"

Telemetrypcmset::Telemetrypcmset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Telemetrypcmset)
{
    ui->setupUi(this);
}

Telemetrypcmset::~Telemetrypcmset()
{
    delete ui;
}
