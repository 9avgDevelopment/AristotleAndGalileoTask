#include "framelessmode.h"
#include "ui_framelessmode.h"

FrameLessMode::FrameLessMode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FrameLessMode)
{
    ui->setupUi(this);
}

FrameLessMode::~FrameLessMode()
{
    delete ui;
}

void FrameLessMode::on_FramelessButton_clicked()
{
    this->close();
    emit FrameLessReturn();
}

