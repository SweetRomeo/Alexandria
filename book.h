#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <string>

enum class BookStatus {
    Available,
    Borrowed,
    Lost,
    Reserved
};

class Book
{
    int m_id;
    std::string m_title;
    std::string m_author;
    std::string m_isbn;
    BookStatus m_status;
public:
    Book(int id, std::string title, std::string author, std::string isbn, const BookStatus& status);
    [[nodiscard]] int getId()const;
    void setId(int id);
    [[nodiscard]] std::string getTitle()const;
    void setTitle(const std::string& title);
    [[nodiscard]] std::string getAuthor()const;
    void setAuthor(const std::string& author);
    [[nodiscard]] std::string getIsbn()const;
    void setIsbn(const std::string& isbn);
    [[nodiscard]] BookStatus getStatus()const;
    void setStatus(const BookStatus& status);
signals:
};

#endif // BOOK_H
