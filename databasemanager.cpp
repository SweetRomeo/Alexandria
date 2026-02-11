#include "databasemanager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &dbPath) {
    (void)openConnection(dbPath);
}

DatabaseManager::~DatabaseManager() {
    closeConnection();
}

bool DatabaseManager::openConnection(const std::string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Failed while opening the DataBase " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Successfully opened the DataBase" << std::endl;
    return true;
}

bool DatabaseManager::createTables() {
    const std::string sqlBooks = "CREATE TABLE IF NOT EXISTS BOOKS("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "TITLE TEXT NOT NULL,"
                                 "AUTHOR TEXT NOT NULL,"
                                 "ISBN TEXT UNIQUE NOT NULL,"
                                 "STATUS INTEGER DEFAULT 0);";

    const std::string sqlUsers = "CREATE TABLE IF NOT EXISTS USERS("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "NAME TEXT NOT NULL,"
                                 "EMAIL TEXT UNIQUE NOT NULL);";

    const std::string sqlTransactions = "CREATE TABLE IF NOT EXISTS TRANSACTIONS("
                                        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "USER_ID INTEGER,"
                                        "BOOK_ID INTEGER,"
                                        "BORROW_DATE TEXT,"
                                        "RETURN_DATE TEXT,"
                                        "FOREIGN KEY(USER_ID) REFERENCES USERS(ID),"
                                        "FOREIGN KEY(BOOK_ID) REFERENCES BOOKS(ID));";

    return executeQuery(sqlBooks) &&
           executeQuery(sqlUsers) &&
           executeQuery(sqlTransactions);
}

bool DatabaseManager::addUser(const User &user) const {
    const std::string sql = "INSERT INTO USERS (ID, NAME, EMAIL) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(stmt, 1, user.getId());
    sqlite3_bind_text(stmt, 2, user.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, user.getEmail().c_str(), -1, SQLITE_TRANSIENT);
    const bool result = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return result;
}

bool DatabaseManager::addBook(const Book &book) const {
    const std::string sql = "INSERT INTO BOOKS (TITLE, AUTHOR, ISBN, STATUS) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, book.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getIsbn().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, static_cast<int>(book.getStatus()));

    const auto result = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return result;
}

bool DatabaseManager::deleteBookById(const int bookId) const {
    std::string sql = "DELETE FROM BOOKS WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Sorgu hazirlanamadi: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, bookId);

    const auto rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool DatabaseManager::deleteUserById(const int userId) const {
    std::string sql = "DELETE FROM USERS WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Sorgu hazirlanamadi: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, userId);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool DatabaseManager::updateBookStatus(int bookId, BookStatus &newStatus) const {
    const std::string sql = "UPDATE BOOKS SET BOOK_ID = ? WHERE ID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, static_cast<int>(newStatus));
    sqlite3_bind_int(stmt, 2, bookId);

    const auto rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

std::vector<Book> DatabaseManager::getAllBooks() const {
    std::vector<Book> Books;
    std::string sql = "SELECT ID, TITLE, AUTHOR, ISBN, STATUS FROM BOOKS;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to create " << sqlite3_errmsg(db) << std::endl;
        return Books;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* titleText = sqlite3_column_text(stmt, 1);
        const unsigned char* authorText = sqlite3_column_text(stmt, 2);
        const unsigned char* isbnText = sqlite3_column_text(stmt, 3);

        std::string title = titleText ? reinterpret_cast<const char*>(titleText) : "";
        std::string author = authorText ? reinterpret_cast<const char*>(authorText) : "";
        std::string isbn = isbnText ? reinterpret_cast<const char*>(isbnText) : "";

        int statusInt = sqlite3_column_int(stmt, 4);
        auto status = static_cast<BookStatus>(statusInt);

        Books.emplace_back(id, title, author, isbn, status);
    }

    sqlite3_finalize(stmt);

    return Books;
}

bool DatabaseManager::executeQuery(const std::string &query) {
    if (const int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &zErrMsg); rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

void DatabaseManager::closeConnection() {
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}
