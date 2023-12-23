#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "DefaultParams.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graph2->addGraph();
    ui->graph2->graph(0)->setPen(QPen(Qt::blue));
    ui->graph2->addGraph();
    ui->graph2->graph(1)->setPen(QPen(Qt::red));
    ui->graph3->addGraph();
    ui->graph3->graph(0)->setPen(QPen(Qt::black));
    ui->graph3->addGraph();
    ui->graph3->graph(1)->setPen(QPen(Qt::blue));
    ui->graph3->addGraph();
    ui->graph3->graph(2)->setPen(QPen(Qt::red));
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
        l_t2.clear();
        l_V1.clear();
        l_V2.clear();
        l_F1s.clear();
        l_F1m.clear();
        l_F1.clear();
        ui->graph1->yAxis->setRange(0, yBase);
        ui->graph1->xAxis->setRange(0, yBase);
        ui->graph1->xAxis->setTicks(false);
        ui->graph1->replot();

        ui->graph2->yAxis->setRange(-round(pow((fmax(m1, m2) * g * fmax(Y01, Y02) * 2 / fmax(m1, m2)), 0.5))*2, round(pow((fmax(m1, m2) * g * fmax(Y01, Y02) * 2 / fmax(m1, m2)), 0.5))*2);
        ui->graph2->xAxis->setRange(0, tBase);
        ui->graph2->graph(0)->setData(l_t1, l_V1);
        ui->graph2->graph(1)->setData(l_t2, l_V2);
        ui->graph2->replot();

        ui->graph3->yAxis->setRange(-(m1 * g * 2.8), (m1 * g * 2.8));
        ui->graph3->xAxis->setRange(0, tBase);
        ui->graph3->graph(0)->setData(l_t1, l_F1);
        ui->graph3->graph(1)->setData(l_t1, l_F1m);
        ui->graph3->graph(2)->setData(l_t1, l_F1s);
        ui->graph3->replot();
    }


}



void MainWindow::on_StartButton_clicked()
{
    if(Stop1 & Stop2){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
        l_t1.clear();
        l_t2.clear();
        l_V1.clear();
        l_V2.clear();
        l_F1s.clear();
        l_F1m.clear();
        l_F1.clear();
        ui->graph1->clearItems();
        ui->graph1->replot();
        ellipse1 = new QCPItemEllipse(ui->graph1);
        ellipse2 = new QCPItemEllipse(ui->graph1);
        ui->graph2->graph(0)->setData(l_t1, l_V1);
        ui->graph2->graph(1)->setData(l_t2, l_V2);
        ui->graph2->graph(0)->setData(l_t1, l_V1);
        ui->graph2->graph(1)->setData(l_t2, l_V2);
        ui->graph2->replot();
        ui->graph3->graph(0)->setData(l_t1, l_F1s);
        ui->graph3->graph(1)->setData(l_t1, l_F1m);
        ui->graph3->graph(2)->setData(l_t1, l_F1);
        ui->graph3->replot();
        Stop1=0;
        Stop2=0;
        Y1 = Y01;
        V1 = -V01;
        Y2 = Y02;
        V2 = -V02;
        t1 = 0;
        t2 = 0;

        timer->start(12);
    }
}


void MainWindow::on_StopButton_clicked()
{
    if(!Stop1 || !Stop2){
        Stop1 = 1;
        Stop2 = 1;
        timer->stop();
    }
}


void MainWindow::TimerSlot()
{
    if(!Stop1 || !Stop2){
        if((Y1 > 0) & (!Stop1)){
            t1 += Deltat;
            F1s = -0.5 * Cy1 * ((Pi * pow(D1,2))/4) * abs(V1) * V1;
            a1 = -g + (F1s/m1);
            V1 += a1 * Deltat;
            Y1 += V1 * Deltat;
            F1m = g * m1;
            F1 = F1m + F1s;
            l_t1.push_back(t1);
            l_V1.push_back(V1);
            l_F1.push_back(-F1);
            l_F1s.push_back(F1s);
            l_F1m.push_back(F1m);
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
            l_t2.push_back(t2);
            l_V2.push_back(V2);
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

    ellipse1->setAntialiased(true);
    ellipse1->setBrush(Qt::black);
    ellipse1->bottomRight->setCoords(yBase/4, Y1);
    ellipse1->topLeft->setCoords(yBase/4+(yBase/11), Y1+(yBase/11));
    ellipse2->setAntialiased(true);
    ellipse2->setBrush(Qt::black);
    ellipse2->bottomRight->setCoords((yBase/4)*3, Y2);
    ellipse2->topLeft->setCoords((yBase/4)*3-(yBase/11), Y2+(yBase/11));
    ui->graph1->replot();

    ui->graph2->graph(0)->setData(l_t1, l_V1);

    ui->graph2->graph(1)->setData(l_t2, l_V2);

    ui->graph2->replot();

    ui->graph3->graph(0)->setData(l_t1, l_F1s);

    ui->graph3->graph(1)->setData(l_t1, l_F1m);

    ui->graph3->graph(2)->setData(l_t1, l_F1);
    ui->graph3->replot();

    ui->V1->setText(QString::number(abs(V1)));
    ui->V2->setText(QString::number(abs(V2)));
    ui->t1->setText(QString::number(abs(t1)));
    ui->t2->setText(QString::number(abs(t2)));
}


