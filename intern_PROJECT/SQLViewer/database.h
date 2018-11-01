#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>
#include <QtWidgets>
#include <QWidget>

class DataBase : public QObject
{
    Q_OBJECT
public:
    struct Contact
    {
        qint32 id = 0;
        QDate date;
        QTime time;
        QString name;
        QString phone;
    };

    explicit DataBase(QObject *parent = nullptr);

    Contact oneContact;

    // Методы для непосредственной работы с базой данных
    bool connectToDataBase(const QString& file);
    bool openDataBase(const QString& path);
    bool sqlQuery(const QString& str);
    void closeDataBase();

    bool onAdd();
    bool onUpdate();
    bool onDelete();
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase db;
signals:
    void sqlData(QSqlQuery& query);
public slots:
};

#endif // DATABASE_H
