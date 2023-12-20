#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "DefaultParams.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FrameLessWindow = new FrameLessMode();

    connect(FrameLessWindow, &FrameLessMode::FrameLessReturn, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_InitButton_clicked()
{
    Y01 = ui->Y01->text().toInt();
    Y02 = ui->Y02->text().toInt();
    V01 = ui->V02->text().toInt();
    V02 = ui->V02->text().toInt();
    Cy1 = ui->Cy1->text().toInt();
    Cy2 = ui->Cy2->text().toInt();
    m1 = ui->m1->text().toInt();
    m2 = ui->m2->text().toInt();
    D1 = ui->D1->text().toInt();
    D2 = ui->D2->text().toInt();
    yBase = ui->yBase->text().toInt();
    tBase = ui->tBase->text().toInt();
    Deltat = ui->Deltat->text().toInt();


}



void MainWindow::on_StartButton_clicked()
{

}


void MainWindow::on_StopButton_clicked()
{

}


void MainWindow::on_FramelessButton_clicked()
{
    FrameLessWindow->show();
    this->close();
}


