
#include <QApplication>
#include <QApplication>
#include <QStringList>
#include "cube3d.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QHBoxLayout layout;
    QWidget w;

    w.setLayout(&layout);

    Ekran e;

    QWidget panel;
    layout.addWidget(&e);
    layout.addWidget(&panel);
    layout.setStretch(0, 4);
    layout.setStretch(1, 1);

    //------tworzenie-sliderow--------------------------------
    QSlider *translacja_X = new QSlider(Qt::Horizontal);
    translacja_X->setMinimum(-100);
    translacja_X->setMaximum(100);
    translacja_X->setValue(0);

    QSlider *translacja_Y = new QSlider(Qt::Horizontal);
    translacja_Y->setMinimum(-100);
    translacja_Y->setMaximum(100);
    translacja_Y->setValue(0);

    QSlider *translacja_Z = new QSlider(Qt::Horizontal);
    translacja_Z->setMinimum(-200);
    translacja_Z->setMaximum(200);
    translacja_Z->setValue(0);

    QSlider *skalowanie_X = new QSlider(Qt::Horizontal);
    skalowanie_X->setMinimum(-100);
    skalowanie_X->setMaximum(100);
    skalowanie_X->setValue(0);

    QSlider *skalowanie_Y = new QSlider(Qt::Horizontal);
    skalowanie_Y->setMinimum(-100);
    skalowanie_Y->setMaximum(100);
    skalowanie_Y->setValue(0);

    QSlider *skalowanie_Z = new QSlider(Qt::Horizontal);
    skalowanie_Z->setMinimum(-100);
    skalowanie_Z->setMaximum(100);
    skalowanie_Z->setValue(0);

    QSlider *obrotOX = new QSlider(Qt::Horizontal);
    obrotOX->setMinimum(-360);
    obrotOX->setMaximum(360);
    obrotOX->setValue(0);

    QSlider *obrotOY = new QSlider(Qt::Horizontal);
    obrotOY->setMinimum(-360);
    obrotOY->setMaximum(360);
    obrotOY->setValue(0);

    QSlider *obrotOZ = new QSlider(Qt::Horizontal);
    obrotOZ->setMinimum(-360);
    obrotOZ->setMaximum(360);
    obrotOZ->setValue(0);

    QCheckBox *pow_widoczne = new QCheckBox("Powierzchnie widoczne");
    //--------------------------------------------------------------------

    QLabel *translacja = new QLabel();
    translacja->setText("translacja");

    QLabel *skalowanie = new QLabel();
    skalowanie->setText("skalowanie");

    QLabel *obrot = new QLabel();
    obrot->setText("obrot");

    QVBoxLayout panelLayer;
    panel.setLayout(&panelLayer);
    panelLayer.addWidget(translacja);
    panelLayer.addWidget(translacja_X);
    panelLayer.addWidget(translacja_Y);
    panelLayer.addWidget(translacja_Z);

    panelLayer.addWidget(skalowanie);
    panelLayer.addWidget(skalowanie_X);
    panelLayer.addWidget(skalowanie_Y);
    panelLayer.addWidget(skalowanie_Z);

    panelLayer.addWidget(obrot);
    panelLayer.addWidget(obrotOX);
    panelLayer.addWidget(obrotOY);
    panelLayer.addWidget(obrotOZ);

    panelLayer.addWidget(pow_widoczne);
    panelLayer.addStretch();

    QObject::connect(translacja_X, &QSlider::valueChanged, &e, &Ekran::translacja_X);
    QObject::connect(translacja_Y, &QSlider::valueChanged, &e, &Ekran::translacja_Y);
    QObject::connect(translacja_Z, &QSlider::valueChanged, &e, &Ekran::translacja_Z);

    QObject::connect(skalowanie_X, &QSlider::valueChanged, &e, &Ekran::skalowanie_X);
    QObject::connect(skalowanie_Y, &QSlider::valueChanged, &e, &Ekran::skalowanie_Y);
    QObject::connect(skalowanie_Z, &QSlider::valueChanged, &e, &Ekran::skalowanie_Z);

    QObject::connect(obrotOX, &QSlider::valueChanged, &e, &Ekran::obrotOX);
    QObject::connect(obrotOY, &QSlider::valueChanged, &e, &Ekran::obrotOY);
    QObject::connect(obrotOZ, &QSlider::valueChanged, &e, &Ekran::obrotOZ);

    QObject::connect(pow_widoczne, &QCheckBox::clicked, &e, &Ekran::pow_WidoczneCheckBox);

    w.resize(1028, 522);
    w.show();
    return a.exec();
}

