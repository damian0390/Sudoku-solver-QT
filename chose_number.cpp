#include "chose_number.h"
#include "ui_chose_number.h"

Chose_number::Chose_number(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chose_number)
{
    ui->setupUi(this);
}

int Chose_number::getNumber(){return number;}

Chose_number::~Chose_number()
{
    delete ui;
}

void Chose_number::on_pushButton_clicked()
{
    number = 1;
    close();
}


void Chose_number::on_pushButton_2_clicked()
{
    number = 2;
    close();
}


void Chose_number::on_pushButton_3_clicked()
{
    number = 3;
    close();
}


void Chose_number::on_pushButton_4_clicked()
{
    number = 4;
    close();
}


void Chose_number::on_pushButton_5_clicked()
{
    number = 5;
    close();
}


void Chose_number::on_pushButton_6_clicked()
{
    number = 6;
    close();
}


void Chose_number::on_pushButton_7_clicked()
{
    number = 7;
    close();
}


void Chose_number::on_pushButton_8_clicked()
{
    number = 8;
    close();
}


void Chose_number::on_pushButton_9_clicked()
{
    number = 9;
    close();
}



void Chose_number::on_Clear_clicked()
{
    number = 0;
    close();
}

