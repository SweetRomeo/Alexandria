#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
    int m_id;
    std::string m_name;
    std::string m_email;
public:
    explicit User(QObject *parent = nullptr);
    User(int userId, std::string name, std::string email);
    ~User() = default;
    void setId(int userId);
    [[nodiscard]]int getId()const;
    void setName(std::string name);
    [[nodiscard]] std::string getName()const;
    void setEmail(std::string email);
    [[nodiscard]] std::string getEmail()const;
signals:
};

#endif // USER_H
