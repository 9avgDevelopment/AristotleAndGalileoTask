#ifndef FRAMELESSMODE_H
#define FRAMELESSMODE_H

#include <QDialog>


namespace Ui {
class FrameLessMode;
}

class FrameLessMode : public QDialog
{
    Q_OBJECT

public:
    explicit FrameLessMode(QWidget *parent = nullptr);
    ~FrameLessMode();
signals:
    void FrameLessReturn();

private slots:
    void on_FramelessButton_clicked();

private:
    Ui::FrameLessMode *ui;
};

#endif // FRAMELESSMODE_H
