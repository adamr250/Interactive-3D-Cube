
#ifndef CUBE3D_H
#define CUBE3D_H

#include <QWidget>
#include <QMainWindow>
#include <QSlider>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im_cp;

    struct Mat {
        float macierz[4][4] = { {1,0,0,0},
                               {0,1,0,0},
                               {0,0,1,0},
                               {0,0,0,1}};
    } translacjaM, skalowanieM, pochylenieM, obrotOX_M, obrotOY_M, obrotOZ_M, obrotXYZ_M,
        result_M, jednostkowa_M, tmpTranslacjaM;

    //Mat mnozenie(Mat, Mat);

    explicit Ekran(QWidget *parent = nullptr);

    void wstawPiksel(int x, int y, int r, int g, int b);
    void rysujLinie(int x_1, int y_1, int x_2, int y_2, int r, int g, int b)
    {
        int deltax = x_2 - x_1;
        int deltay = y_2 - y_1;
        int err = 0;
        int y = y_1;
        int x = x_1;
        int for_1 = x_1, for_2 = x_2;

        if(x_2 < x_1){
            deltax = x_1 - x_2;
        }
        if(y_2 < y_1){
            deltay = y_1 - y_2;
        }
        if(x_1 <= x_2 && deltax >= deltay) {
            //qDebug("here_1");
            if(y_2 < y_1){
                deltay = y_1 - y_2;
            }
            for (x=for_1; x<=for_2; x++)
            {
                wstawPiksel(x, y, r, g, b);
                err = err + deltay;
                if (2*err >= deltax)
                {
                    if(y_2 > y_1){
                        y++;
                    } else y--;
                    err = err - deltax;
                }
            }
        } else if(x_1 > x_2 && deltax >= deltay){
            //qDebug("here 2");
            deltax = x_1 - x_2;

            if(y_2 < y_1){
                deltay = y_1 - y_2;
            }

            for (x=for_1; x>=for_2; x--)
            {
                wstawPiksel(x, y, r, g, b);
                err = err + deltay;
                if (2*err >= deltax)
                {
                    if(y_2 > y_1){
                        y++;
                    } else y--;
                    err = err - deltax;
                }
            }
        } else if (deltax < deltay && y_1 <= y_2){
            //qDebug("here 3");
            int for_1 = y_1, for_2 = y_2;

            if(x_2 < x_1){
                deltax = x_1 - x_2;
            }
            if(y_2 < y_1){
                deltay = y_1 - y_2;
                for_1 = y_2;
                for_2 = y_1;
            }
            for (y=for_1; y<=for_2; y++)
            {
                wstawPiksel(x, y, r, g, b);
                err = err + deltax;
                if (2*err >= deltay)
                {
                    if(x_2 > x_1){
                        x++;
                    } else x--;
                    err = err - deltay;
                }
            }
        } else /*if (x_1 > x_2 && deltax < deltay)*/{
            //qDebug("here 4");
            int for_1 = y_1, for_2 = y_2;

            if(x_2 < x_1){
                deltax = x_1 - x_2;
            }
            if(y_2 < y_1){
                deltay = y_1 - y_2;
            }
            for (y=for_1; y>=for_2; y--)
            {
                wstawPiksel(x, y, r, g, b);
                err = err + deltax;
                if (2*err >= deltay)
                {
                    if(x_2 > x_1){
                        x++;
                    } else x--;
                    err = err - deltay;
                }
            }
        }
        update();
    }
    void rysujBryle();

    bool jestWidoczne(int n);

    void pow_WidoczneCheckBox(bool isChecked);

    void translacja_X(int x);
    void translacja_Y(int y);
    void translacja_Z(int z);

    void skalowanie_X(int x);
    void skalowanie_Y(int x);
    void skalowanie_Z(int x);

    void obrotOX(int alfa);
    void obrotOY(int alfa);
    void obrotOZ(int alfa);

    void skladanieMacierzy();

    void przeksztalcenia(Mat);

    void mnozenie(Mat A, Mat B);

protected:
    void paintEvent(QPaintEvent *);
    //    void mousePressEvent(QMouseEvent *);
    //    void mouseMoveEvent(QMouseEvent *);
    //    void mouseReleaseEvent(QMouseEvent *);

};

#endif // CUBE3D_H
