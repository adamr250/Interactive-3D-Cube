
#include "cube3d.h"
#include "ui_cube3d.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QWidget>
#include <QVector>

int square[6][4][4], squareBackup[6][4][4];
int d = 500;
int viewer[3]= {0, 0, -d};
float x_translacja=0, y_translacja=0, z_translacja=0;
float x_skalowanie=1, y_skalowanie=1, z_skalowanie=1;

bool isChecked = false;

Ekran::Ekran(QWidget *parent)
    : QWidget(parent)
{
    im = QImage(800, 500, QImage::Format_RGB32);
    im_cp = im.copy();

    for (int y = 0; y < im.height(); ++y) {
        uchar *p = im.scanLine(y);
        for (int x = 0; x < im.width(); ++x) {
            p[x*4]   = 0;
            p[x*4+1] = 0;
            p[x*4+2] = 0;
            p[x*4+3] = 255;
        }
    }

    //    Point[0][0] = -100;  Point[1][0] = -100;  Point[2][0] = -100;  Point[3][0] = 1;
    //    Point[0][1] = 100;   Point[1][1] = -100;  Point[2][1] = -100;  Point[3][1] = 1;
    //    Point[0][2] = 100;   Point[1][2] = 100;   Point[2][2] = -100;  Point[3][2] = 1;
    //    Point[0][3] = -100;  Point[1][3] = 100;   Point[2][3] = -100;  Point[3][3] = 1;

    //    Point[0][4] = -100;  Point[1][4] = -100;  Point[2][4] = 100;  Point[3][4] = 1;
    //    Point[0][5] = 100;   Point[1][5] = -100;  Point[2][5] = 100;  Point[3][5] = 1;
    //    Point[0][6] = 100;   Point[1][6] = 100;   Point[2][6] = 100;  Point[3][6] = 1;
    //    Point[0][7] = -100;  Point[1][7] = 100;   Point[2][7] = 100;  Point[3][7] = 1;



    square[0][0][0] = -100;  square[0][0][1] = -100;  square[0][0][2] = -100;  square[0][0][3] = 1;
    square[0][1][0] = 100;  square[0][1][1] = -100;  square[0][1][2] = -100;  square[0][1][3] = 1;
    square[0][2][0] = 100;  square[0][2][1] = 100;  square[0][2][2] = -100;  square[0][2][3] = 1;
    square[0][3][0] = -100;  square[0][3][1] = 100;  square[0][3][2] = -100;  square[0][3][3] = 1;

    square[1][0][0] = 100;  square[1][0][1] = -100;  square[1][0][2] = -100;  square[1][0][3] = 1;
    square[1][1][0] = 100;  square[1][1][1] = -100;  square[1][1][2] = 100;  square[1][1][3] = 1;
    square[1][2][0] = 100;  square[1][2][1] = 100;  square[1][2][2] = 100;  square[1][2][3] = 1;
    square[1][3][0] = 100;  square[1][3][1] = 100;  square[1][3][2] = -100;  square[1][3][3] = 1;

    square[2][0][0] = -100;  square[2][0][1] = -100;  square[2][0][2] = -100;  square[2][0][3] = 1;
    square[2][1][0] = -100;  square[2][1][1] = -100;  square[2][1][2] = 100;  square[2][1][3] = 1;
    square[2][2][0] = 100;  square[2][2][1] = -100;  square[2][2][2] = 100;  square[2][2][3] = 1;
    square[2][3][0] = 100;  square[2][3][1] = -100;  square[2][3][2] = -100;  square[2][3][3] = 1;

    square[3][0][0] = -100;  square[3][0][1] = -100;  square[3][0][2] = -100;  square[3][0][3] = 1;
    square[3][1][0] = -100;  square[3][1][1] = 100;  square[3][1][2] = -100;  square[3][1][3] = 1;
    square[3][2][0] = -100;  square[3][2][1] = 100;  square[3][2][2] = 100;  square[3][2][3] = 1;
    square[3][3][0] = -100;  square[3][3][1] = -100;  square[3][3][2] = 100;  square[3][3][3] = 1;

    square[4][0][0] = -100;  square[4][0][1] = 100;  square[4][0][2] = -100;  square[4][0][3] = 1;
    square[4][1][0] = 100;  square[4][1][1] = 100;  square[4][1][2] = -100;  square[4][1][3] = 1;
    square[4][2][0] = 100;  square[4][2][1] = 100;  square[4][2][2] = 100;  square[4][2][3] = 1;
    square[4][3][0] = -100;  square[4][3][1] = 100;  square[4][3][2] = 100;  square[4][3][3] = 1;

    square[5][0][0] = -100;  square[5][0][1] = -100;  square[5][0][2] = 100;  square[5][0][3] = 1;
    square[5][1][0] = -100;  square[5][1][1] = 100;  square[5][1][2] = 100;  square[5][1][3] = 1;
    square[5][2][0] = 100;  square[5][2][1] = 100;  square[5][2][2] = 100;  square[5][2][3] = 1;
    square[5][3][0] = 100;  square[5][3][1] = -100;  square[5][3][2] = 100;  square[5][3][3] = 1;

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                squareBackup[i][j][k] = square[i][j][k];
            }
        }
    }



    rysujBryle();
}

//----------------------------------------------------------------------------
void Ekran::translacja_X(int x) {
    x_translacja = (im.width()/2)*((float)x/100);

    translacjaM.macierz[0][3] = x_translacja;
    translacjaM.macierz[1][3] = y_translacja;
    translacjaM.macierz[2][3] = z_translacja;

    skladanieMacierzy();
    //    przeksztalcenia(translacjaM);
}

void Ekran::translacja_Y(int y) {
    y_translacja = (im.height()/2)*((float)y/100);

    translacjaM.macierz[0][3] = x_translacja;
    translacjaM.macierz[1][3] = y_translacja;
    translacjaM.macierz[2][3] = z_translacja;

    skladanieMacierzy();
    //    przeksztalcenia(translacjaM);
}

void Ekran::translacja_Z(int z) {
    z_translacja = z*2;

    translacjaM.macierz[0][3] = x_translacja;
    translacjaM.macierz[1][3] = y_translacja;
    translacjaM.macierz[2][3] = z_translacja;

    skladanieMacierzy();
    //    przeksztalcenia(translacjaM);
}

void Ekran::skalowanie_X(int x) {
    x_skalowanie = pow(1.02, x);
    skalowanieM.macierz[0][0] = x_skalowanie;
    skalowanieM.macierz[1][1] = y_skalowanie;
    skalowanieM.macierz[2][2] = z_skalowanie;

    skladanieMacierzy();
}

void Ekran::skalowanie_Y(int y) {
    y_skalowanie = pow(1.02, y);
    skalowanieM.macierz[0][0] = x_skalowanie;
    skalowanieM.macierz[1][1] = y_skalowanie;
    skalowanieM.macierz[2][2] = z_skalowanie;

    skladanieMacierzy();
}

void Ekran::skalowanie_Z(int z) {
    z_skalowanie = pow(1.02, z);
    skalowanieM.macierz[0][0] = x_skalowanie;
    skalowanieM.macierz[1][1] = y_skalowanie;
    skalowanieM.macierz[2][2] = z_skalowanie;

    skladanieMacierzy();
}

void Ekran::obrotOX(int alfa) {
    float rad = (float)alfa * 0.0175;

    obrotOX_M.macierz[1][1] = cos(rad);
    obrotOX_M.macierz[1][2] = -sin(rad);
    obrotOX_M.macierz[2][1] = sin(rad);
    obrotOX_M.macierz[2][2] = cos(rad);

    //skladanieObrotu();
    skladanieMacierzy();
}

void Ekran::obrotOY(int alfa) {
    float rad = (float)alfa * 0.0175;

    obrotOY_M.macierz[0][0] = cos(rad);
    obrotOY_M.macierz[0][2] = sin(rad);
    obrotOY_M.macierz[2][0] = -sin(rad);
    obrotOY_M.macierz[2][2] = cos(rad);

    //skladanieObrotu();
    skladanieMacierzy();
}

void Ekran::obrotOZ(int alfa) {
    float rad = (float)alfa * 0.0175;

    obrotOZ_M.macierz[0][0] = cos(rad);
    obrotOZ_M.macierz[0][1] = -sin(rad);
    obrotOZ_M.macierz[1][0] = sin(rad);
    obrotOZ_M.macierz[1][1] = cos(rad);

    //skladanieObrotu();
    skladanieMacierzy();
}

void Ekran::mnozenie(Mat A, Mat B) {
    float tmp;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tmp = 0;
            for(int k = 0; k < 4; k++) {
                tmp += A.macierz[i][k] * B.macierz[k][j];
            }
            result_M.macierz[i][j] = tmp;
        }
    }
}

void Ekran::skladanieMacierzy() {
    mnozenie(skalowanieM, jednostkowa_M);
    mnozenie(obrotOZ_M, result_M);
    mnozenie(obrotOY_M, result_M);
    mnozenie(obrotOX_M, result_M);
    mnozenie(translacjaM, result_M);

    przeksztalcenia(result_M);
}

void Ekran::przeksztalcenia(Mat macierz) {
    float Tmp_M[4][4] = {{1,0,0,0},
                         {0,1,0,0},
                         {0,0,1,0},
                         {0,0,0,1}};
    float Final_M[4][4] = {{1,0,0,0},
                           {0,1,0,0},
                           {0,0,1,0},
                           {0,0,0,1}};
    float tmp;

    for(int i = 0; i < 4; i++ ) {
        for(int j = 0; j < 4; j++ ) {
            tmp = 0;
            for(int k = 0; k < 4; k++ ) {
                tmp += macierz.macierz[k][j] * Tmp_M[i][k];
            }
            Final_M[i][j] = tmp;
        }
    }

    for(int l = 0; l < 6; l++) {
        for(int i = 0; i < 4; i++ ) {
            for(int j = 0; j < 4; j++ ) {
                tmp = 0;
                for(int k = 0; k < 4; k++ ) {
                    tmp += Final_M[i][k] * squareBackup[l][j][k];
                }
                square[l][j][i] = tmp;
            }
        }
    }
    im = im_cp.copy();

    rysujBryle();
}

void Ekran::rysujBryle() {
    int convertedPoint[6][4][2];
    int r = 255, g = 255, b = 255;
    for (int i = 0; i<6; i++) {
        for(int j = 0; j < 4; j++) {
            convertedPoint[i][j][0] = (square[i][j][0]*d)/(square[i][j][2] + d) + im.width()/2;
            convertedPoint[i][j][1] = (square[i][j][1]*d)/(square[i][j][2] + d) + im.height()/2;
        }
        if(jestWidoczne(i) || isChecked == false) {
            rysujLinie(convertedPoint[i][0][0], convertedPoint[i][0][1], convertedPoint[i][1][0], convertedPoint[i][1][1], r, g, b);
            rysujLinie(convertedPoint[i][1][0], convertedPoint[i][1][1], convertedPoint[i][2][0], convertedPoint[i][2][1], r, g, b);
            rysujLinie(convertedPoint[i][2][0], convertedPoint[i][2][1], convertedPoint[i][3][0], convertedPoint[i][3][1], r, g, b);
            rysujLinie(convertedPoint[i][3][0], convertedPoint[i][3][1], convertedPoint[i][0][0], convertedPoint[i][0][1], r, g, b);
        }
    }

    update();
}

bool Ekran::jestWidoczne(int n) {
    int V[3] = {0, 0, 0};
    int N[3] = {0, 0, 0};
    int vectorWall1[3] = {0, 0, 0};
    int vectorWall2[3] = {0, 0, 0};
    long iloczyn = 0;

    int srodek[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        srodek[i]  = (square[n][0][i] + square[n][1][i] + square[n][2][i] + square[n][3][i]) / 4;
        vectorWall1[i] = square[n][3][i] - square[n][0][i];
        vectorWall2[i] = square[n][1][i] - square[n][0][i];
    }

    for(int i = 0; i < 3; i++) {
        V[i] = viewer[i] - srodek[i];
    }
    N[0] =  vectorWall1[1] * vectorWall2[2] - vectorWall2[1] * vectorWall1[2];
    N[1] =  vectorWall2[0] * vectorWall1[2] - vectorWall1[0] * vectorWall2[2];
    N[2] =  vectorWall1[0] * vectorWall2[1] - vectorWall2[0] * vectorWall1[1];

    iloczyn = N[0] * V[0] + N[1] * V[1] + N[2] * V[2];

    if(iloczyn < 0) {
        return false;
    } else {
        return true;
    }
}

void Ekran::pow_WidoczneCheckBox(bool tmpBool) {
    isChecked = tmpBool;
    im = im_cp.copy();
    rysujBryle();
}

//----------------------------------------------------------------------------
void Ekran::wstawPiksel(int x, int y, int r, int g, int b){
    if (x < 0 || y < 0 || x >= im.width() || y >= im.height()) {
        return;
    }
    uchar *p = im.scanLine(y);
    p[x*4]   = b;
    p[x*4+1] = g;
    p[x*4+2] = r;
    p[x*4+3] = 255;
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::darkGray);
    p.drawImage(0, 0, im);
}
