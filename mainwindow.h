#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <framelessmode.h>
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

    void on_FramelessButton_clicked();

private:
    Ui::MainWindow *ui;

    FrameLessMode *FrameLessWindow;


};
#endif // MAINWINDOW_H
