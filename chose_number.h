#ifndef CHOSE_NUMBER_H
#define CHOSE_NUMBER_H

#include <QDialog>

namespace Ui {
class Chose_number;
}

class Chose_number : public QDialog
{
    Q_OBJECT

public:
    explicit Chose_number(QWidget *parent = nullptr);
    ~Chose_number();


    int getNumber();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_Clear_clicked();

private:
    Ui::Chose_number *ui;
    int number;
};

#endif // CHOSE_NUMBER_H
