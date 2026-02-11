#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{}

User::User(const int userId, std::string name, std::string email) : m_id(userId), m_name(std::move(name)), m_email(std::move(email)) {}

void User::setId(int userId) {
    m_id = userId;
}

int User::getId() const {
    return m_id;
}

void User::setName(std::string name) {
    m_name = std::move(name);
}

std::string User::getName() const {
    return m_name;
}

void User::setEmail(std::string email) {
    m_email = std::move(email);
}

std::string User::getEmail() const {
    return m_email;
}
