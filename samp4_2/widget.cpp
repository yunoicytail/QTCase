#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#define Pi 3.1415926

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->spinPeriod->setRange(0,255);
    //ui->spinPeriod->set
    //ui->spinDepth->clear();
}

Widget::~Widget()
{
    delete ui;
}

float Widget::calWaveNumber(double a, double b)
{
    //float c=a*b;
    double T=a;
    double h=b;
    double w,k0,k1;
    //double Pi = 3.1415926f;
    double g=9.81;
    w=2*Pi/T;
    k0=pow(w,2)/g;
    k1=k0+(pow(w,2)-g*k0*tanh(k0*h))/(g*tanh(k0*h)+k0*g*h*pow((1/cosh(k0*h)),2));
    while(fabs(k1-k0)>1e-10){
        k0=k1;
        k1=k0+(pow(w,2)-g*k0*tanh(k0*h))/(g*tanh(k0*h)+k0*g*h*pow((1/cosh(k0*h)),2));
    }
    return  k1;
}

void Widget::on_btnCal_clicked()
{
    double      wavePeriod=ui->spinPeriod->value();
    double      waterDepth=ui->spinDepth->value();
    double      waveNumber=calWaveNumber(wavePeriod,waterDepth);
    double      waveLength=2*Pi/waveNumber;
    double      waveVelocity=waveLength/wavePeriod;
    ui->spinWaveNumber->setValue(waveNumber);
    ui->spinWaveLength->setValue(waveLength);
    ui->spinWaveVelocity->setValue(waveVelocity);
}
