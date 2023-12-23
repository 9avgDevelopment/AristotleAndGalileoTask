#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QTimer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_InitButton_clicked();

    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void TimerSlot();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QCPItemEllipse *ellipse1, *ellipse2;

    QVector<double> l_t1, l_t2, l_V1, l_V2, l_F1s, l_F1m, l_F1;


};
#endif // MAINWINDOW_H
