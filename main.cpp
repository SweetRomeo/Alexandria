#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Qt uygulamasını başlatır (Event loop ve GUI ayarları)
    QApplication a(argc, argv);

    // Alexandria projesinin ana penceresini oluşturur
    MainWindow w;

    // Pencereyi ekranda gösterir
    w.show();

    // Uygulama döngüsüne girer (Kapatılana kadar çalışır)
    return a.exec();
}
