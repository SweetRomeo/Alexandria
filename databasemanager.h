#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase> // Qt SQL desteği
#include <string>
#include <vector>
#include "book.h"
#include "user.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    // Constructor & Destructor
    explicit DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    // Veritabanı Bağlantı Yönetimi
    [[nodiscard]] bool openConnection(const std::string& dbPath);
    void closeConnection();

    // Tablo Oluşturma
    bool createTables();

    // CRUD İşlemleri (Create, Read, Update, Delete)
    [[nodiscard]] bool addUser(const User& user) const;
    [[nodiscard]] bool addBook(const Book& book) const;
    [[nodiscard]] bool deleteBookById(int bookId) const;
    [[nodiscard]] bool deleteUserById(int userId) const;

    // Not: BookStatus enum olduğu için referans (&) yerine değer olarak geçmek daha performanslı ve temizdir.
    [[nodiscard]] bool updateBookStatus(int bookId, BookStatus newStatus) const;

    [[nodiscard]] std::vector<Book> getAllBooks() const;

    // Yardımcı Fonksiyon (Opsiyonel, geriye dönük uyumluluk için)
    bool executeQuery(const std::string& query);

private:
    // Artık 'sqlite3 *db' veya 'zErrMsg' tutmamıza gerek yok.
    // Qt, bağlantıları "connectionName" üzerinden yönetir.
    // Ancak bağlantının açık olup olmadığını kontrol etmek istersen
    // QSqlDatabase nesnesini burada saklayabilirsin ama zorunlu değil.
};

#endif // DATABASEMANAGER_H
