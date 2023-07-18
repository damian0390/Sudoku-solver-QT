#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chose_number.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int x = 0; x < 9; x++){
        vec.push_back({});
        for (int y = 0; y < 9; y++){
            Field f;
            vec[x].push_back(f);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choseNumber(){
    Chose_number ch;
    ch.setModal(true);
    if(ch.exec() == QDialog::Rejected){
        number = ch.getNumber();
    }
}

void MainWindow::checkValue(int x, int y){

    if (number == 0){
      vec[x-1][y-1].disp = false;
      fillAllValues();
      clearValues();
      solve();
      display();
    }

    else if (vec[x-1][y-1].disp){
      int temp = vec[x-1][y-1].pos[0];
      vec[x-1][y-1].disp = false;
      fillAllValues();
      clearValues();
      solve();
      for (auto num : vec[x-1][y-1].pos){
       if (num == number) {
           fillOne(x, y, num);
           display();
           return;
       }
    }
          fillOne(x, y, temp);
          display();
          QMessageBox::critical(this, "Wrong number", "You can not use this number here.");
    }
    else {
    for (auto num : vec[x-1][y-1].pos){
       if (num == number) {
           fillOne(x, y, num);
           display();
           return;
       }
      }
    QMessageBox::critical(this, "Wrong number", "You can not use this number here.");
    }
}

void MainWindow::fillOne(int x, int y, int num){
  vec[x-1][y-1].disp = true;
  vec[x-1][y-1].pos.clear();
  vec[x-1][y-1].pos.push_back(num);
  eliminate(x, y, num);
  solve();
}

void MainWindow::fillAllValues(){
  for (int x = 0; x < 9; x++){
    for (int y = 0; y < 9; y++){
      if (!vec[x][y].disp){
        vec[x][y].pos = {1,2,3,4,5,6,7,8,9};
      }
    }
  }
}

void MainWindow::clearValues(){
  for (int x = 0; x < 9; x++){
    for (int y = 0; y < 9; y++){
      if (vec[x][y].disp){
        eliminate(x+1, y+1, vec[x][y].pos[0]);
      }
    }
  }

}


void MainWindow::solve(){
  bool flag = false;
  for (int z = 0; z < 9; z++){
  solve_x(flag, z);
  solve_y(flag, z);
  }
  for (int xx = 0; xx < 9; xx += 3){
    for (int yy = 0; yy < 9; yy += 3){
      solve_square(flag, xx, yy);
    }
  }
  if (flag) solve();
}

void MainWindow::solve_x(bool &flag, int x){
  int y, counter;
  for (int num = 1; num <= 9; num++){
    counter = 0;
    for (int yy = 0; yy < 9; yy++){
      if (!vec[x][yy].disp){
        for (auto n : vec[x][yy].pos){
          if (n == num){
            counter++;
            y = yy;
            break;
          }
        }
      }
    }
    if (counter == 1){
      vec[x][y].disp = true;
      flag = true;
      vec[x][y].pos.clear();
      vec[x][y].pos.push_back(num);
      eliminate(x+1, y+1, num);
    }
  }

}

void MainWindow::solve_y(bool &flag, int y){
  int x, counter;
  for (int num = 1; num <= 9; num++){
    counter = 0;
    for (int xx = 0; xx < 9; xx++){
      if (!vec[xx][y].disp){
        for (auto n : vec[xx][y].pos){
          if (n == num){
            counter++;
            x = xx;
            break;
          }
        }
      }
    }
    if (counter == 1){
      vec[x][y].disp = true;
      flag = true;
      vec[x][y].pos.clear();
      vec[x][y].pos.push_back(num);
      eliminate(x+1, y+1, num);
    }
  }
}

void MainWindow::solve_square(bool &flag, int xx, int yy){
  int x, y, counter;
  for (int num = 1; num <= 9; num++){
    counter = 0;
    for (int tx = xx; tx < (xx+3); tx++){
      for (int ty = yy; ty < (yy+3); ty++){
        if (!vec[tx][ty].disp){
          for (auto n : vec[tx][ty].pos){
            if (n == num){
              counter++;
              x = tx;
              y = ty;
              break;
            }
          }
        }
      }
    }
    if (counter == 1){
      vec[x][y].disp = true;
      flag = true;
      vec[x][y].pos.clear();
      vec[x][y].pos.push_back(num);
      eliminate(x+1, y+1, num);
    }
  }
}



void MainWindow::eliminate_x(int y, int num){
    for (int i = 0; i < 9; i++){
        if (!vec[i][y-1].disp){
            for (size_t j = 0; j < vec[i][y-1].pos.size(); j++){
                if (vec[i][y-1].pos[j] == num){
                    vec[i][y-1].pos.erase(vec[i][y-1].pos.begin() + j);
                    if (vec[i][y-1].pos.size() == 1){
                        vec[i][y-1].disp = true;
                        eliminate(i+1, y, vec[i][y-1].pos[0]);
                    }
                }
            }
        }
    }
}

void MainWindow::eliminate_y(int x, int num){
    for (int i = 0; i < 9; i++){
        if (!vec[x-1][i].disp){
            for (size_t j = 0; j < vec[x-1][i].pos.size(); j++){
                if (vec[x-1][i].pos[j] == num){
                    vec[x-1][i].pos.erase(vec[x-1][i].pos.begin() + j);
                    if (vec[x-1][i].pos.size() == 1){
                        vec[x-1][i].disp = true;
                        eliminate(x, i+1, vec[x-1][i].pos[0]);
                    }
                }
            }
        }
    }
}

void MainWindow::eliminate_square(int x, int y, int num){
    int xx = 3*((x-1)/3);
    int yy = 3*((y-1)/3);
    for (int i = xx; i < (xx+3); i++){
        for (int j = yy; j < (yy+3); j++){
            if (!vec[i][j].disp){
                for (size_t k = 0; k < vec[i][j].pos.size(); k++){
                    if (vec[i][j].pos[k] == num){
                        vec[i][j].pos.erase(vec[i][j].pos.begin() + k);
                        if (vec[i][j].pos.size() == 1){
                            vec[i][j].disp = true;
                            eliminate(i+1, j+1, vec[i][j].pos[0]);
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::eliminate(int x, int y, int num){
    eliminate_x(y, num);
    eliminate_y(x, num);
    eliminate_square(x, y, num);
}

void MainWindow::display(){
    if (vec[0][0].disp) ui -> F11 -> setText(res[vec[0][0].pos[0]]);
        else ui -> F11 -> setText(res[0]);
    if (vec[0][1].disp) ui -> F12 -> setText(res[vec[0][1].pos[0]]);
        else ui -> F12 -> setText(res[0]);
    if (vec[0][2].disp) ui -> F13 -> setText(res[vec[0][2].pos[0]]);
        else ui -> F13 -> setText(res[0]);
    if (vec[0][3].disp) ui -> F14 -> setText(res[vec[0][3].pos[0]]);
        else ui -> F14 -> setText(res[0]);
    if (vec[0][4].disp) ui -> F15 -> setText(res[vec[0][4].pos[0]]);
        else ui -> F15 -> setText(res[0]);
    if (vec[0][5].disp) ui -> F16 -> setText(res[vec[0][5].pos[0]]);
        else ui -> F16 -> setText(res[0]);
    if (vec[0][6].disp) ui -> F17 -> setText(res[vec[0][6].pos[0]]);
        else ui -> F17 -> setText(res[0]);
    if (vec[0][7].disp) ui -> F18 -> setText(res[vec[0][7].pos[0]]);
        else ui -> F18 -> setText(res[0]);
    if (vec[0][8].disp) ui -> F19 -> setText(res[vec[0][8].pos[0]]);
        else ui -> F19 -> setText(res[0]);

    if (vec[1][0].disp) ui -> F21 -> setText(res[vec[1][0].pos[0]]);
        else ui -> F21 -> setText(res[0]);
    if (vec[1][1].disp) ui -> F22 -> setText(res[vec[1][1].pos[0]]);
        else ui -> F22 -> setText(res[0]);
    if (vec[1][2].disp) ui -> F23 -> setText(res[vec[1][2].pos[0]]);
        else ui -> F23 -> setText(res[0]);
    if (vec[1][3].disp) ui -> F24 -> setText(res[vec[1][3].pos[0]]);
        else ui -> F24 -> setText(res[0]);
    if (vec[1][4].disp) ui -> F25 -> setText(res[vec[1][4].pos[0]]);
        else ui -> F25 -> setText(res[0]);
    if (vec[1][5].disp) ui -> F26 -> setText(res[vec[1][5].pos[0]]);
        else ui -> F26 -> setText(res[0]);
    if (vec[1][6].disp) ui -> F27 -> setText(res[vec[1][6].pos[0]]);
        else ui -> F27 -> setText(res[0]);
    if (vec[1][7].disp) ui -> F28 -> setText(res[vec[1][7].pos[0]]);
        else ui -> F28 -> setText(res[0]);
    if (vec[1][8].disp) ui -> F29 -> setText(res[vec[1][8].pos[0]]);
        else ui -> F29 -> setText(res[0]);

    if (vec[2][0].disp) ui -> F31 -> setText(res[vec[2][0].pos[0]]);
        else ui -> F31 -> setText(res[0]);
    if (vec[2][1].disp) ui -> F32 -> setText(res[vec[2][1].pos[0]]);
        else ui -> F32 -> setText(res[0]);
    if (vec[2][2].disp) ui -> F33 -> setText(res[vec[2][2].pos[0]]);
        else ui -> F33 -> setText(res[0]);
    if (vec[2][3].disp) ui -> F34 -> setText(res[vec[2][3].pos[0]]);
        else ui -> F34 -> setText(res[0]);
    if (vec[2][4].disp) ui -> F35 -> setText(res[vec[2][4].pos[0]]);
        else ui -> F35 -> setText(res[0]);
    if (vec[2][5].disp) ui -> F36 -> setText(res[vec[2][5].pos[0]]);
        else ui -> F36 -> setText(res[0]);
    if (vec[2][6].disp) ui -> F37 -> setText(res[vec[2][6].pos[0]]);
        else ui -> F37 -> setText(res[0]);
    if (vec[2][7].disp) ui -> F38 -> setText(res[vec[2][7].pos[0]]);
        else ui -> F38 -> setText(res[0]);
    if (vec[2][8].disp) ui -> F39 -> setText(res[vec[2][8].pos[0]]);
        else ui -> F39 -> setText(res[0]);

    if (vec[3][0].disp) ui -> F41 -> setText(res[vec[3][0].pos[0]]);
        else ui -> F41 -> setText(res[0]);
    if (vec[3][1].disp) ui -> F42 -> setText(res[vec[3][1].pos[0]]);
        else ui -> F42 -> setText(res[0]);
    if (vec[3][2].disp) ui -> F43 -> setText(res[vec[3][2].pos[0]]);
        else ui -> F43 -> setText(res[0]);
    if (vec[3][3].disp) ui -> F44 -> setText(res[vec[3][3].pos[0]]);
        else ui -> F44 -> setText(res[0]);
    if (vec[3][4].disp) ui -> F45 -> setText(res[vec[3][4].pos[0]]);
        else ui -> F45 -> setText(res[0]);
    if (vec[3][5].disp) ui -> F46 -> setText(res[vec[3][5].pos[0]]);
        else ui -> F46 -> setText(res[0]);
    if (vec[3][6].disp) ui -> F47 -> setText(res[vec[3][6].pos[0]]);
        else ui -> F47 -> setText(res[0]);
    if (vec[3][7].disp) ui -> F48 -> setText(res[vec[3][7].pos[0]]);
        else ui -> F48 -> setText(res[0]);
    if (vec[3][8].disp) ui -> F49 -> setText(res[vec[3][8].pos[0]]);
        else ui -> F49 -> setText(res[0]);

    if (vec[4][0].disp) ui -> F51 -> setText(res[vec[4][0].pos[0]]);
        else ui -> F51 -> setText(res[0]);
    if (vec[4][1].disp) ui -> F52 -> setText(res[vec[4][1].pos[0]]);
        else ui -> F52 -> setText(res[0]);
    if (vec[4][2].disp) ui -> F53 -> setText(res[vec[4][2].pos[0]]);
        else ui -> F53 -> setText(res[0]);
    if (vec[4][3].disp) ui -> F54 -> setText(res[vec[4][3].pos[0]]);
        else ui -> F54 -> setText(res[0]);
    if (vec[4][4].disp) ui -> F55 -> setText(res[vec[4][4].pos[0]]);
        else ui -> F55 -> setText(res[0]);
    if (vec[4][5].disp) ui -> F56 -> setText(res[vec[4][5].pos[0]]);
        else ui -> F56 -> setText(res[0]);
    if (vec[4][6].disp) ui -> F57 -> setText(res[vec[4][6].pos[0]]);
        else ui -> F57 -> setText(res[0]);
    if (vec[4][7].disp) ui -> F58 -> setText(res[vec[4][7].pos[0]]);
        else ui -> F58 -> setText(res[0]);
    if (vec[4][8].disp) ui -> F59 -> setText(res[vec[4][8].pos[0]]);
        else ui -> F59 -> setText(res[0]);

    if (vec[5][0].disp) ui -> F61 -> setText(res[vec[5][0].pos[0]]);
        else ui -> F61 -> setText(res[0]);
    if (vec[5][1].disp) ui -> F62 -> setText(res[vec[5][1].pos[0]]);
        else ui -> F62 -> setText(res[0]);
    if (vec[5][2].disp) ui -> F63 -> setText(res[vec[5][2].pos[0]]);
        else ui -> F63 -> setText(res[0]);
    if (vec[5][3].disp) ui -> F64 -> setText(res[vec[5][3].pos[0]]);
        else ui -> F64 -> setText(res[0]);
    if (vec[5][4].disp) ui -> F65 -> setText(res[vec[5][4].pos[0]]);
        else ui -> F65 -> setText(res[0]);
    if (vec[5][5].disp) ui -> F66 -> setText(res[vec[5][5].pos[0]]);
        else ui -> F66 -> setText(res[0]);
    if (vec[5][6].disp) ui -> F67 -> setText(res[vec[5][6].pos[0]]);
        else ui -> F67 -> setText(res[0]);
    if (vec[5][7].disp) ui -> F68 -> setText(res[vec[5][7].pos[0]]);
        else ui -> F68 -> setText(res[0]);
    if (vec[5][8].disp) ui -> F69 -> setText(res[vec[5][8].pos[0]]);
        else ui -> F69 -> setText(res[0]);

    if (vec[6][0].disp) ui -> F71 -> setText(res[vec[6][0].pos[0]]);
        else ui -> F71 -> setText(res[0]);
    if (vec[6][1].disp) ui -> F72 -> setText(res[vec[6][1].pos[0]]);
        else ui -> F72 -> setText(res[0]);
    if (vec[6][2].disp) ui -> F73 -> setText(res[vec[6][2].pos[0]]);
        else ui -> F73 -> setText(res[0]);
    if (vec[6][3].disp) ui -> F74 -> setText(res[vec[6][3].pos[0]]);
        else ui -> F74 -> setText(res[0]);
    if (vec[6][4].disp) ui -> F75 -> setText(res[vec[6][4].pos[0]]);
        else ui -> F75 -> setText(res[0]);
    if (vec[6][5].disp) ui -> F76 -> setText(res[vec[6][5].pos[0]]);
        else ui -> F76 -> setText(res[0]);
    if (vec[6][6].disp) ui -> F77 -> setText(res[vec[6][6].pos[0]]);
        else ui -> F77 -> setText(res[0]);
    if (vec[6][7].disp) ui -> F78 -> setText(res[vec[6][7].pos[0]]);
        else ui -> F78 -> setText(res[0]);
    if (vec[6][8].disp) ui -> F79 -> setText(res[vec[6][8].pos[0]]);
        else ui -> F79 -> setText(res[0]);

    if (vec[7][0].disp) ui -> F81 -> setText(res[vec[7][0].pos[0]]);
        else ui -> F81 -> setText(res[0]);
    if (vec[7][1].disp) ui -> F82 -> setText(res[vec[7][1].pos[0]]);
        else ui -> F82 -> setText(res[0]);
    if (vec[7][2].disp) ui -> F83 -> setText(res[vec[7][2].pos[0]]);
        else ui -> F83 -> setText(res[0]);
    if (vec[7][3].disp) ui -> F84 -> setText(res[vec[7][3].pos[0]]);
        else ui -> F84 -> setText(res[0]);
    if (vec[7][4].disp) ui -> F85 -> setText(res[vec[7][4].pos[0]]);
        else ui -> F85 -> setText(res[0]);
    if (vec[7][5].disp) ui -> F86 -> setText(res[vec[7][5].pos[0]]);
        else ui -> F86 -> setText(res[0]);
    if (vec[7][6].disp) ui -> F87 -> setText(res[vec[7][6].pos[0]]);
        else ui -> F87 -> setText(res[0]);
    if (vec[7][7].disp) ui -> F88 -> setText(res[vec[7][7].pos[0]]);
        else ui -> F88 -> setText(res[0]);
    if (vec[7][8].disp) ui -> F89 -> setText(res[vec[7][8].pos[0]]);
        else ui -> F89 -> setText(res[0]);

    if (vec[8][0].disp) ui -> F91 -> setText(res[vec[8][0].pos[0]]);
        else ui -> F91 -> setText(res[0]);
    if (vec[8][1].disp) ui -> F92 -> setText(res[vec[8][1].pos[0]]);
        else ui -> F92 -> setText(res[0]);
    if (vec[8][2].disp) ui -> F93 -> setText(res[vec[8][2].pos[0]]);
        else ui -> F93 -> setText(res[0]);
    if (vec[8][3].disp) ui -> F94 -> setText(res[vec[8][3].pos[0]]);
        else ui -> F94 -> setText(res[0]);
    if (vec[8][4].disp) ui -> F95 -> setText(res[vec[8][4].pos[0]]);
        else ui -> F95 -> setText(res[0]);
    if (vec[8][5].disp) ui -> F96 -> setText(res[vec[8][5].pos[0]]);
        else ui -> F96 -> setText(res[0]);
    if (vec[8][6].disp) ui -> F97 -> setText(res[vec[8][6].pos[0]]);
        else ui -> F97 -> setText(res[0]);
    if (vec[8][7].disp) ui -> F98 -> setText(res[vec[8][7].pos[0]]);
        else ui -> F98 -> setText(res[0]);
    if (vec[8][8].disp) ui -> F99 -> setText(res[vec[8][8].pos[0]]);
        else ui -> F99 -> setText(res[0]);
}


void MainWindow::on_F11_clicked()
{
    choseNumber();  checkValue(1, 1);
}


void MainWindow::on_F12_clicked()
{
    choseNumber();  checkValue(1, 2);
}


void MainWindow::on_F13_clicked()
{
    choseNumber();  checkValue(1, 3);
}


void MainWindow::on_F14_clicked()
{
    choseNumber();  checkValue(1, 4);
}


void MainWindow::on_F15_clicked()
{
    choseNumber();  checkValue(1, 5);
}


void MainWindow::on_F16_clicked()
{
    choseNumber();  checkValue(1, 6);
}


void MainWindow::on_F17_clicked()
{
    choseNumber();  checkValue(1, 7);
}


void MainWindow::on_F18_clicked()
{
    choseNumber();  checkValue(1, 8);
}


void MainWindow::on_F19_clicked()
{
    choseNumber();  checkValue(1, 9);
}


void MainWindow::on_F21_clicked()
{
    choseNumber();  checkValue(2, 1);
}


void MainWindow::on_F22_clicked()
{
    choseNumber();  checkValue(2, 2);
}


void MainWindow::on_F23_clicked()
{
    choseNumber();  checkValue(2, 3);
}


void MainWindow::on_F24_clicked()
{
    choseNumber();  checkValue(2, 4);
}


void MainWindow::on_F25_clicked()
{
    choseNumber();  checkValue(2, 5);
}


void MainWindow::on_F26_clicked()
{
    choseNumber();  checkValue(2, 6);
}


void MainWindow::on_F27_clicked()
{
    choseNumber();  checkValue(2, 7);
}


void MainWindow::on_F28_clicked()
{
    choseNumber();  checkValue(2, 8);
}


void MainWindow::on_F29_clicked()
{
    choseNumber();  checkValue(2, 9);
}


void MainWindow::on_F31_clicked()
{
    choseNumber();  checkValue(3, 1);
}


void MainWindow::on_F32_clicked()
{
    choseNumber();  checkValue(3, 2);
}


void MainWindow::on_F33_clicked()
{
    choseNumber();  checkValue(3, 3);
}


void MainWindow::on_F34_clicked()
{
    choseNumber();  checkValue(3, 4);
}


void MainWindow::on_F35_clicked()
{
    choseNumber();  checkValue(3, 5);
}


void MainWindow::on_F36_clicked()
{
    choseNumber();  checkValue(3, 6);
}


void MainWindow::on_F37_clicked()
{
    choseNumber();  checkValue(3, 7);
}


void MainWindow::on_F38_clicked()
{
    choseNumber();  checkValue(3, 8);
}


void MainWindow::on_F39_clicked()
{
   choseNumber();  checkValue(3, 9);
}


void MainWindow::on_F41_clicked()
{
    choseNumber();  checkValue(4, 1);
}


void MainWindow::on_F42_clicked()
{
    choseNumber();  checkValue(4, 2);
}


void MainWindow::on_F43_clicked()
{
    choseNumber();  checkValue(4, 3);
}


void MainWindow::on_F44_clicked()
{
    choseNumber();  checkValue(4, 4);
}


void MainWindow::on_F45_clicked()
{
    choseNumber();  checkValue(4, 5);
}


void MainWindow::on_F46_clicked()
{
    choseNumber();  checkValue(4, 6);
}


void MainWindow::on_F47_clicked()
{
   choseNumber();  checkValue(4, 7);
}


void MainWindow::on_F48_clicked()
{
    choseNumber();  checkValue(4, 8);
}


void MainWindow::on_F49_clicked()
{
    choseNumber();  checkValue(4, 9);
}


void MainWindow::on_F51_clicked()
{
   choseNumber();  checkValue(5, 1);
}


void MainWindow::on_F52_clicked()
{
    choseNumber();  checkValue(5, 2);
}


void MainWindow::on_F53_clicked()
{
    choseNumber();  checkValue(5, 3);
}


void MainWindow::on_F54_clicked()
{
    choseNumber();  checkValue(5, 4);
}


void MainWindow::on_F55_clicked()
{
    choseNumber();  checkValue(5, 5);
}


void MainWindow::on_F56_clicked()
{
    choseNumber();  checkValue(5, 6);
}


void MainWindow::on_F57_clicked()
{
    choseNumber();  checkValue(5, 7);
}


void MainWindow::on_F58_clicked()
{
    choseNumber();  checkValue(5, 8);
}


void MainWindow::on_F59_clicked()
{
    choseNumber();  checkValue(5, 9);
}


void MainWindow::on_F61_clicked()
{
    choseNumber();  checkValue(6, 1);
}


void MainWindow::on_F62_clicked()
{
    choseNumber();  checkValue(6, 2);
}


void MainWindow::on_F63_clicked()
{
    choseNumber();  checkValue(6, 3);
}


void MainWindow::on_F64_clicked()
{
    choseNumber();  checkValue(6, 4);
}


void MainWindow::on_F65_clicked()
{
    choseNumber();  checkValue(6, 5);
}


void MainWindow::on_F66_clicked()
{
    choseNumber();  checkValue(6, 6);
}


void MainWindow::on_F67_clicked()
{
   choseNumber();  checkValue(6, 7);
}


void MainWindow::on_F68_clicked()
{
   choseNumber();  checkValue(6, 8);
}


void MainWindow::on_F69_clicked()
{
    choseNumber();  checkValue(6, 9);
}


void MainWindow::on_F71_clicked()
{
    choseNumber();  checkValue(7, 1);
}


void MainWindow::on_F72_clicked()
{
    choseNumber();  checkValue(7, 2);
}


void MainWindow::on_F73_clicked()
{
   choseNumber();  checkValue(7, 3);
}


void MainWindow::on_F74_clicked()
{
    choseNumber();  checkValue(7, 4);
}


void MainWindow::on_F75_clicked()
{
    choseNumber();  checkValue(7, 5);
}


void MainWindow::on_F76_clicked()
{
   choseNumber();  checkValue(7, 6);
}


void MainWindow::on_F77_clicked()
{
   choseNumber();  checkValue(7, 7);
}


void MainWindow::on_F78_clicked()
{
    choseNumber();  checkValue(7, 8);
}


void MainWindow::on_F79_clicked()
{
    choseNumber();  checkValue(7, 9);
}


void MainWindow::on_F81_clicked()
{
    choseNumber();  checkValue(8, 1);
}


void MainWindow::on_F82_clicked()
{
    choseNumber();  checkValue(8, 2);
}


void MainWindow::on_F83_clicked()
{
    choseNumber();  checkValue(8, 3);
}


void MainWindow::on_F84_clicked()
{
    choseNumber();  checkValue(8, 4);
}


void MainWindow::on_F85_clicked()
{
    choseNumber();  checkValue(8, 5);
}


void MainWindow::on_F86_clicked()
{
   choseNumber();  checkValue(8, 6);
}


void MainWindow::on_F87_clicked()
{
   choseNumber();  checkValue(8, 7);
}


void MainWindow::on_F88_clicked()
{
    choseNumber();  checkValue(8, 8);
}


void MainWindow::on_F89_clicked()
{
    choseNumber();  checkValue(8, 9);
}


void MainWindow::on_F91_clicked()
{
    choseNumber();  checkValue(9, 1);
}


void MainWindow::on_F92_clicked()
{
    choseNumber();  checkValue(9, 2);
}


void MainWindow::on_F93_clicked()
{
    choseNumber();  checkValue(9, 3);
}


void MainWindow::on_F94_clicked()
{
   choseNumber();  checkValue(9, 4);
}


void MainWindow::on_F95_clicked()
{
   choseNumber();  checkValue(9, 5);
}


void MainWindow::on_F96_clicked()
{
    choseNumber();  checkValue(9, 6);
}


void MainWindow::on_F97_clicked()
{
   choseNumber();  checkValue(9, 7);
}


void MainWindow::on_F98_clicked()
{
   choseNumber();  checkValue(9, 8);
}


void MainWindow::on_F99_clicked()
{
    choseNumber();  checkValue(9, 9);
}


void MainWindow::on_Clear_clicked()
{
    vec.clear();
    for (int x = 0; x < 9; x++){
        vec.push_back({});
        for (int y = 0; y < 9; y++){
            Field f;
            vec[x].push_back(f);
        }
    }
    display();
}
