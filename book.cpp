#include "book.h"

Book::Book(const int id, std::string title, std::string author, std::string isbn, const BookStatus& status) : m_id(id), m_title(std::move(title)), m_author(std::move(author)), m_isbn(std::move(isbn)), m_status(status)
{
    if (m_title.empty()) {
        throw std::invalid_argument("Book title cannot be empty");
    }
    if (m_isbn.length() < 10) {
        throw std::invalid_argument("Invalid ISBN format");
    }
}

int Book::getId()const {
    return m_id;
}

void Book::setId(const int id)
{
    m_id = id;
}

std::string Book::getTitle()const {
    return m_title;
}

void Book::setTitle(const std::string& title) {
    m_title = title;
}

std::string Book::getAuthor()const {
    return m_author;
}

void Book::setAuthor(const std::string& author) {
    m_author = author;
}

std::string Book::getIsbn()const {
    return m_isbn;
}

void Book::setIsbn(const std::string& isbn) {
    m_isbn = isbn;
}

BookStatus Book::getStatus() const {
    return m_status;
}

void Book::setStatus(const BookStatus& status) {
    m_status = status;
}
