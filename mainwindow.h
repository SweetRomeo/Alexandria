#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "databasemanager.h" // Veritabanı sınıfını ekledik

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddBookClicked();    // Ekleme butonu
    void onDeleteBookClicked(); // Silme butonu (Yeni ekledik)

private:
    void setupUI();      // Arayüzü oluşturur
    void loadBooks();    // Veritabanından kitapları çeker ve tabloya yazar

    QWidget *centralWidget;
    QTableWidget *bookTable;
    QPushButton *btnAddBook;
    QPushButton *btnDeleteBook; // Silme butonu

    // Veritabanı yöneticimiz
    DatabaseManager *dbManager;
};

#endif // MAINWINDOW_H
