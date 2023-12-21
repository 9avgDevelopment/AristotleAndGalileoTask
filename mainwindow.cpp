#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "DefaultParams.h"
#include <QtMath>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_InitButton_clicked()
{   if(Stop1 & Stop2){
        Y01 = ui->Y01->text().toDouble();
        Y02 = ui->Y02->text().toDouble();
        V01 = ui->V01->text().toDouble();
        V02 = ui->V02->text().toDouble();
        Cy1 = ui->Cy1->text().toDouble();
        Cy2 = ui->Cy2->text().toDouble();
        m1 = ui->m1->text().toDouble();
        m2 = ui->m2->text().toDouble();
        D1 = ui->D1->text().toDouble();
        D2 = ui->D2->text().toDouble();
        yBase = ui->yBase->text().toDouble();
        tBase = ui->tBase->text().toDouble();
        Deltat = ui->Deltat->text().toDouble();

        Y1 = Y01;
        V1 = V01;
        Y2 = Y02;
        V2 = V02;
        t1 = 0;
        t2 = 0;
        l_t1.clear();
        l_V1.clear();
        l_Y1.clear();
        l_F1m.clear();
        l_F1s.clear();
        l_F1.clear();
        ui->graph1->clearGraphs();
        ui->graph1->yAxis->setRange(0, yBase);
        ui->graph1->xAxis->setRange(0, 3);
        ui->graph1->xAxis->setTicks(false);
        ui->graph1->replot();

        ui->graph2->clearGraphs();
        ui->graph2->yAxis->setRange(-round(pow((fmax(m1, m2) * g * fmax(Y01, Y02) * 2 / fmax(m1, m2)), 0.5))*2, round(pow((fmax(m1, m2) * g * fmax(Y01, Y02) * 2 / fmax(m1, m2)), 0.5))*2);
        ui->graph2->xAxis->setRange(0, tBase);
        ui->graph2->replot();

        ui->graph3->clearGraphs();
        ui->graph3->yAxis->setRange(-(m1 * g * 1.4), (m1 * g * 1.4));
        ui->graph3->xAxis->setRange(0, tBase);
        ui->graph3->replot();
    }


}



void MainWindow::on_StartButton_clicked()
{
    if(Stop1 & Stop2){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
        ui->graph1->clearGraphs();
        ui->graph2->clearGraphs();
        ui->graph3->clearGraphs();
        Stop1=0;
        Stop2=0;
        timer->start(12);

        Y1 = Y01;
        V1 = V01;
        Y2 = Y02;
        V2 = V02;
        t1 = 0;
        t2 = 0;
        l_V1.clear();
        l_V2.clear();
        l_Y1.clear();
        l_Y2.clear();
        l_t1.clear();
        l_t2.clear();
    }
}


void MainWindow::on_StopButton_clicked()
{
    if(!Stop1 & !Stop2){
        Stop1 = 1;
        Stop2 = 1;
        timer->stop();
    }
}


void MainWindow::TimerSlot()
{
    if(!Stop1 & !Stop2){
        if((Y1 > 0) & (!Stop1)){
            t1 += Deltat;
            F1s = -0.5 * Cy1 * ((Pi * pow(D1,2))/4) * abs(V1) * V1;
            a1 = -g + (F1s/m1);
            V1 += a1 * Deltat;
            Y1 += V1 * Deltat;
            F1m = -g * m1;
            F1 = F1m + F1s;
            l_t1.push_back(t1);
            l_V1.push_back(V1);
            l_Y1.push_back(Y1);
            l_F1m.push_back(F1m);
            l_F1s.push_back(F1s);
            l_F1.push_back(F1);
        }
        else{
            Stop1=1;
        }

        if((Y2 > 0) & (!Stop2)){
            t2 += Deltat;
            F2s = -0.5 * Cy2 * ((Pi * pow(D2,2))/4) * abs(V2) * V2;
            a2 = -g + (F2s/m2);
            V2 += a2 * Deltat;
            Y2 += V2 * Deltat;
            F2m = -g * m2;
            F2 = F2m + F2s;
            l_t2.push_back(t2);
            l_V2.push_back(V2);
            l_Y2.push_back(Y2);
            l_F2m.push_back(F2m);
            l_F2s.push_back(F2s);
            l_F2.push_back(F2);
        }
        else{
            Stop2=1;
        }
    }
    else{
        Stop1 = 1;
        Stop2 = 1;
        timer->stop();
    }

    ui->graph1->setAutoAddPlottableToLegend(1);
    ui->graph1->addGraph();
    ui->graph1->graph(0)->addData(1, 5);
    ui->graph1->replot();

    ui->graph2->addGraph();
    ui->graph2->graph(0)->setPen(QPen(Qt::blue));
    ui->graph2->graph(0)->addData(l_t1, l_V1);

    ui->graph2->addGraph();
    ui->graph2->graph(1)->setPen(QPen(Qt::red));
    ui->graph2->graph(1)->addData(l_t2, l_V2);

    ui->graph2->replot();

    ui->graph3->addGraph();
    ui->graph3->graph(0)->setPen(QPen(Qt::black));
    ui->graph3->graph(0)->addData(l_t1, l_F1s);

    ui->graph3->addGraph();
    ui->graph3->graph(1)->setPen(QPen(Qt::blue));
    ui->graph3->graph(1)->addData(l_t1, l_F1m);

    ui->graph3->addGraph();
    ui->graph3->graph(2)->setPen(QPen(Qt::red));
    ui->graph3->graph(2)->addData(l_t1, l_F1);

    ui->graph3->replot();

    ui->V1->setText(QString::number(abs(V1)));
    ui->V2->setText(QString::number(abs(V2)));
    ui->t1->setText(QString::number(abs(t1)));
    ui->t2->setText(QString::number(abs(t2)));
}


