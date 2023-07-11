#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Field;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void choseNumber();
    bool checkValue(int x, int y);
    void eliminate(int x, int y, int num);
    void eliminate_x(int y, int num);
    void eliminate_y(int x, int num);
    void eliminate_square(int x, int y, int num);
    void display();

private slots:

    void on_F11_clicked();

    void on_F12_clicked();

    void on_F13_clicked();

    void on_F14_clicked();

    void on_F15_clicked();

    void on_F16_clicked();

    void on_F17_clicked();

    void on_F18_clicked();

    void on_F19_clicked();

    void on_F21_clicked();

    void on_F22_clicked();

    void on_F23_clicked();

    void on_F24_clicked();

    void on_F25_clicked();

    void on_F26_clicked();

    void on_F27_clicked();

    void on_F28_clicked();

    void on_F29_clicked();

    void on_F31_clicked();

    void on_F32_clicked();

    void on_F33_clicked();

    void on_F34_clicked();

    void on_F35_clicked();

    void on_F36_clicked();

    void on_F37_clicked();

    void on_F38_clicked();

    void on_F39_clicked();

    void on_F41_clicked();

    void on_F42_clicked();

    void on_F43_clicked();

    void on_F44_clicked();

    void on_F45_clicked();

    void on_F46_clicked();

    void on_F47_clicked();

    void on_F48_clicked();

    void on_F49_clicked();

    void on_F51_clicked();

    void on_F52_clicked();

    void on_F53_clicked();

    void on_F54_clicked();

    void on_F55_clicked();

    void on_F56_clicked();

    void on_F57_clicked();

    void on_F58_clicked();

    void on_F59_clicked();

    void on_F61_clicked();

    void on_F62_clicked();

    void on_F63_clicked();

    void on_F64_clicked();

    void on_F65_clicked();

    void on_F66_clicked();

    void on_F67_clicked();

    void on_F68_clicked();

    void on_F69_clicked();

    void on_F71_clicked();

    void on_F72_clicked();

    void on_F73_clicked();

    void on_F74_clicked();

    void on_F75_clicked();

    void on_F76_clicked();

    void on_F77_clicked();

    void on_F78_clicked();

    void on_F79_clicked();

    void on_F81_clicked();

    void on_F82_clicked();

    void on_F83_clicked();

    void on_F84_clicked();

    void on_F85_clicked();

    void on_F86_clicked();

    void on_F87_clicked();

    void on_F88_clicked();

    void on_F89_clicked();

    void on_F91_clicked();

    void on_F92_clicked();

    void on_F93_clicked();

    void on_F94_clicked();

    void on_F95_clicked();

    void on_F96_clicked();

    void on_F97_clicked();

    void on_F98_clicked();

    void on_F99_clicked();

    void on_Clear_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QString> res = {"","1","2","3","4","5","6","7","8","9"};
    std::vector<std::vector<Field>> vec;
    int number;
};

struct Field{
    Field(){
        pos = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        disp = false;
    }

    std::vector<int> pos;
    bool disp;
};
#endif // MAINWINDOW_H
