#include "telemetryradiofrequencyset.h"
#include "ui_telemetryradiofrequencyset.h"

TelemeTryradioFrequencyset::TelemeTryradioFrequencyset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelemeTryradioFrequencyset)
{
    ui->setupUi(this);
}

TelemeTryradioFrequencyset::~TelemeTryradioFrequencyset()
{
    delete ui;
}
