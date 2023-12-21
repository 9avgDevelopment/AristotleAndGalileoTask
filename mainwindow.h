#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

    QVector<double> l_V1, l_V2, l_Y1, l_Y2, l_a1sz, l_t1, l_t2, l_F1s, l_F2s, l_F1m, l_F2m, l_F1, l_F2;

    QTimer *timer;

};
#endif // MAINWINDOW_H
