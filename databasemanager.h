#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "sqlite3.h"
#include "book.h"
#include "user.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
    sqlite3 *db = nullptr;
    char *zErrMsg = nullptr;
public:
    explicit DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();
    [[nodiscard]]bool openConnection(const std::string& dbPath);
    void closeConnection();
    bool executeQuery(const std::string& query);
    bool createTables();
    [[nodiscard]] bool addUser(const User&) const;
    [[nodiscard]] bool addBook(const Book&) const;
    [[nodiscard]] bool deleteBookById(int bookId) const;
    [[nodiscard]] bool deleteUserById(int userId) const;
    [[nodiscard]] bool updateBookStatus(int bookId, BookStatus& newStatus) const;
    [[nodiscard]] std::vector<Book> getAllBooks() const;
signals:
};

#endif // DATABASEMANAGER_H
