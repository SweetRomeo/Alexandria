#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QDir>

// Constructor: Veritabanı bağlantısını kurar
DatabaseManager::DatabaseManager(const std::string &dbPath) {
    // Qt'de veritabanı bağlantısı ekliyoruz
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(dbPath));

    if (!db.open()) {
        qCritical() << "Veritabanı açılamadı:" << db.lastError().text();
    } else {
        qDebug() << "Veritabanı başarıyla açıldı:" << QString::fromStdString(dbPath);
        // Tablolar yoksa oluştur
        createTables();
    }
}

DatabaseManager::~DatabaseManager() {
    // Qt veritabanı bağlantısını otomatik yönetir, ancak açıkça kapatmak istersen:
    QString connectionName;
    {
        auto db = QSqlDatabase::database();
        connectionName = db.connectionName();
        if (db.isOpen()) {
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
}

// Qt kullandığımız için openConnection metoduna artık dışarıdan ihtiyaç duymayabiliriz
// ama yapıyı bozmamak için bırakıyorum.
bool DatabaseManager::openConnection(const std::string &dbPath) {
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) return true;

    db.setDatabaseName(QString::fromStdString(dbPath));
    return db.open();
}

bool DatabaseManager::createTables() {
    QSqlQuery query;
    bool success = true;

    // BOOKS Tablosu
    QString sqlBooks = "CREATE TABLE IF NOT EXISTS BOOKS ("
                       "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "TITLE TEXT NOT NULL, "
                       "AUTHOR TEXT NOT NULL, "
                       "ISBN TEXT UNIQUE NOT NULL, "
                       "STATUS INTEGER DEFAULT 0)";

    if (!query.exec(sqlBooks)) {
        qCritical() << "Books tablosu oluşturulamadı:" << query.lastError();
        success = false;
    }

    // USERS Tablosu
    QString sqlUsers = "CREATE TABLE IF NOT EXISTS USERS ("
                       "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "NAME TEXT NOT NULL, "
                       "EMAIL TEXT UNIQUE NOT NULL)";

    if (!query.exec(sqlUsers)) {
        qCritical() << "Users tablosu oluşturulamadı:" << query.lastError();
        success = false;
    }

    // TRANSACTIONS Tablosu
    QString sqlTransactions = "CREATE TABLE IF NOT EXISTS TRANSACTIONS ("
                              "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "USER_ID INTEGER, "
                              "BOOK_ID INTEGER, "
                              "BORROW_DATE TEXT, "
                              "RETURN_DATE TEXT, "
                              "FOREIGN KEY(USER_ID) REFERENCES USERS(ID), "
                              "FOREIGN KEY(BOOK_ID) REFERENCES BOOKS(ID))";

    if (!query.exec(sqlTransactions)) {
        qCritical() << "Transactions tablosu oluşturulamadı:" << query.lastError();
        success = false;
    }

    return success;
}

bool DatabaseManager::addUser(const User &user) const {
    QSqlQuery query;
    // Qt'de ? yerine :parametreIsmi kullanmak (Oracle stili) daha okunaklıdır.
    query.prepare("INSERT INTO USERS (NAME, EMAIL) VALUES (:name, :email)");

    // NOT: ID autoincrement olduğu için insert sorgusuna ID'yi manuel eklememeliyiz,
    // veritabanı kendi atamalıdır. Eğer User nesnesinde ID zorunluysa ona göre düzenlenir.

    query.bindValue(":name", QString::fromStdString(user.getName()));
    query.bindValue(":email", QString::fromStdString(user.getEmail()));

    if (!query.exec()) {
        qCritical() << "Kullanıcı eklenemedi:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::addBook(const Book &book) const {
    QSqlQuery query;
    query.prepare("INSERT INTO BOOKS (TITLE, AUTHOR, ISBN, STATUS) "
                  "VALUES (:title, :author, :isbn, :status)");

    query.bindValue(":title", QString::fromStdString(book.getTitle()));
    query.bindValue(":author", QString::fromStdString(book.getAuthor()));
    query.bindValue(":isbn", QString::fromStdString(book.getIsbn()));
    query.bindValue(":status", static_cast<int>(book.getStatus()));

    if (!query.exec()) {
        qCritical() << "Kitap eklenemedi:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::deleteBookById(const int bookId) const {
    QSqlQuery query;
    query.prepare("DELETE FROM BOOKS WHERE ID = :id");
    query.bindValue(":id", bookId);

    if (!query.exec()) {
        qCritical() << "Kitap silinemedi:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::deleteUserById(const int userId) const {
    QSqlQuery query;
    query.prepare("DELETE FROM USERS WHERE ID = :id");
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qCritical() << "Kullanıcı silinemedi:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::updateBookStatus(int bookId, BookStatus newStatus) const {
    QSqlQuery query;
    // Düzeltme: Orijinal kodda SET BOOK_ID = ? vardı, bu muhtemelen hataydı.
    // Doğrusu SET STATUS = ? olmalı.
    query.prepare("UPDATE BOOKS SET STATUS = :status WHERE ID = :id");

    query.bindValue(":status", static_cast<int>(newStatus));
    query.bindValue(":id", bookId);

    if (!query.exec()) {
        qCritical() << "Kitap durumu güncellenemedi:" << query.lastError();
        return false;
    }
    return true;
}

std::vector<Book> DatabaseManager::getAllBooks() const {
    std::vector<Book> books;
    QSqlQuery query("SELECT ID, TITLE, AUTHOR, ISBN, STATUS FROM BOOKS");

    if (!query.exec()) {
        qCritical() << "Kitaplar getirilemedi:" << query.lastError();
        return books;
    }

    while (query.next()) {
        int id = query.value("ID").toInt();
        std::string title = query.value("TITLE").toString().toStdString();
        std::string author = query.value("AUTHOR").toString().toStdString();
        std::string isbn = query.value("ISBN").toString().toStdString();
        int statusInt = query.value("STATUS").toInt();
        auto status = static_cast<BookStatus>(statusInt);

        // Book sınıfının constructor yapısına göre nesneyi oluşturup listeye atıyoruz
        books.emplace_back(id, title, author, isbn, status);
    }

    return books;
}

// executeQuery helper fonksiyonuna Qt yapısında genelde ihtiyaç kalmaz
// çünkü QSqlQuery kendi içinde bunu halleder ama uyumluluk için:
bool DatabaseManager::executeQuery(const std::string &queryStr) {
    QSqlQuery query;
    if (!query.exec(QString::fromStdString(queryStr))) {
        qCritical() << "Sorgu hatası:" << query.lastError();
        return false;
    }
    return true;
}

void DatabaseManager::closeConnection() {
    QString connectionName = QSqlDatabase::database().connectionName();
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase(connectionName);
    qDebug() << "Veritabanı bağlantısı kapatıldı.";
}
