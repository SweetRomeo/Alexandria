#include "mainwindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog> // Kullanıcıdan veri almak için
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Alexandria - Kütüphane Yönetim Sistemi");
    resize(900, 600);

    // 1. Veritabanını Başlat
    // Proje klasöründe "alexandria.db" adında bir dosya oluşturacak.
    QString dbPath = QDir::currentPath() + "/alexandria.db";
    dbManager = new DatabaseManager(dbPath.toStdString());

    // 2. Arayüzü Kur
    setupUI();

    // 3. Mevcut kitapları listele
    loadBooks();
}

MainWindow::~MainWindow()
{
    delete dbManager; // Bellek temizliği
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Tablo Ayarları
    bookTable = new QTableWidget();
    bookTable->setColumnCount(5); // ID, Başlık, Yazar, ISBN, Durum
    QStringList headers = {"ID", "Kitap Adı", "Yazar", "ISBN", "Durum"};
    bookTable->setHorizontalHeaderLabels(headers);
    bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bookTable->setSelectionBehavior(QAbstractItemView::SelectRows); // Satır seçimi
    bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Düzenlemeyi kapat

    // Butonlar için yatay düzen (Yan yana olsunlar)
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    btnAddBook = new QPushButton("Yeni Kitap Ekle");
    btnAddBook->setIcon(QIcon::fromTheme("list-add")); // Varsa sistem ikonu

    btnDeleteBook = new QPushButton("Seçili Kitabı Sil");
    btnDeleteBook->setIcon(QIcon::fromTheme("list-remove"));

    buttonLayout->addWidget(btnAddBook);
    buttonLayout->addWidget(btnDeleteBook);

    // Sinyal-Slot Bağlantıları
    connect(btnAddBook, &QPushButton::clicked, this, &MainWindow::onAddBookClicked);
    connect(btnDeleteBook, &QPushButton::clicked, this, &MainWindow::onDeleteBookClicked);

    // Ana düzene ekleme
    mainLayout->addWidget(new QLabel("<h3>Kütüphane Envanteri</h3>"));
    mainLayout->addWidget(bookTable);
    mainLayout->addLayout(buttonLayout);
}

void MainWindow::loadBooks()
{
    // Tabloyu temizle (Satırları sil, başlıklar kalsın)
    bookTable->setRowCount(0);

    // Veritabanından kitapları çek
    std::vector<Book> books = dbManager->getAllBooks();

    // Her bir kitabı tabloya ekle
    for (const auto &book : books) {
        int row = bookTable->rowCount();
        bookTable->insertRow(row);

        // ID (std::to_string -> QString dönüşümü)
        bookTable->setItem(row, 0, new QTableWidgetItem(QString::number(book.getId())));

        // Kitap Bilgileri (std::string -> QString dönüşümü)
        bookTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
        bookTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
        bookTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.getIsbn())));

        // Durum (Enum -> String)
        QString statusStr = (book.getStatus() == BookStatus::Available) ? "Mevcut" : "Ödünç Verildi";
        bookTable->setItem(row, 4, new QTableWidgetItem(statusStr));
    }
}

void MainWindow::onAddBookClicked()
{
    // Basit bir veri girişi simülasyonu (İleride özel Dialog sınıfı yapılabilir)
    bool ok;
    QString title = QInputDialog::getText(this, "Kitap Ekle", "Kitap Adı:", QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;

    QString author = QInputDialog::getText(this, "Kitap Ekle", "Yazar:", QLineEdit::Normal, "", &ok);
    if (!ok || author.isEmpty()) return;

    QString isbn = QInputDialog::getText(this, "Kitap Ekle", "ISBN:", QLineEdit::Normal, "", &ok);
    if (!ok || isbn.isEmpty()) return;

    // Yeni Book nesnesi oluştur (ID veritabanında otomatik atanacak, buraya 0 verebiliriz)
    Book newBook(0, title.toStdString(), author.toStdString(), isbn.toStdString(), BookStatus::Available);

    // Veritabanına kaydet
    if (dbManager->addBook(newBook)) {
        QMessageBox::information(this, "Başarılı", "Kitap kütüphaneye eklendi.");
        loadBooks(); // Tabloyu yenile
    } else {
        QMessageBox::critical(this, "Hata", "Kitap eklenirken bir sorun oluştu!");
    }
}

void MainWindow::onDeleteBookClicked()
{
    // Seçili satır var mı kontrol et
    QList<QTableWidgetItem *> selectedItems = bookTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen silmek için bir kitap seçin.");
        return;
    }

    // Seçili satırın ID'sini al (0. sütun ID sütunu)
    int row = selectedItems.first()->row();
    int bookId = bookTable->item(row, 0)->text().toInt();

    // Kullanıcıdan onay iste
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Silme Onayı", "Bu kitabı silmek istediğinize emin misiniz?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (dbManager->deleteBookById(bookId)) {
            loadBooks(); // Listeyi yenile
        } else {
            QMessageBox::critical(this, "Hata", "Kitap silinemedi!");
        }
    }
}
