#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent) {}
// Методы для подключения к базе данных
bool DataBase::connectToDataBase(const QString &file)
{
    // Перед подключением к базе данных производим проверку на её существование.
    if(!QFile(file).exists()){
        return false;
    }

    return this->openDataBase(file);
}
// Метод для открытия базы данных
bool DataBase::openDataBase(const QString &path)
{
    if (path == ""){
        return false;
    }

    if (db.databaseName() == path && db.isOpen()){
        return true;
    }

    if (db.isOpen()){
        closeDataBase();
    }
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует.
     * Если не существуею то создаётся пустой файл.
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(!db.open()){
        qDebug().noquote() << "DataBase error! ";
        qDebug().noquote() << db.lastError();
        return false;
    }

    return true;
}
// Метод для отправки запросов в базу данных
bool DataBase::sqlQuery(const QString &str)
{
    if (str == "" || !db.isOpen())
        return false;
    // Запрос SQL формируется передаваемой строкой
    QSqlQuery query;
    query.prepare(str);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug().noquote() << "DataBase error! ";
        qDebug().noquote() << query.lastError().text();
        return false;
    }

    emit sqlData(query);
    return true;
}
// Метод закрытия базы данных
void DataBase::closeDataBase()
{
    db.close();
}
// Метод добавления записи в таблицу
bool DataBase::onAdd()
{
    if (oneContact.name == "" || oneContact.phone == "" || !db.isOpen()) {
        return false;
    }

    QDateTime dt = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare("INSERT INTO Contacts ( Date, Time, Name, Phone ) "
                  "VALUES (:Date, :Time, :Name, :Phone )");
    query.bindValue(":Date",  dt.date());
    query.bindValue(":Time",  dt.time());
    query.bindValue(":Name",  oneContact.name);
    query.bindValue(":Phone", oneContact.phone);
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "DataBase insert error!";
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
// Метод редактирования записи в таблице
bool DataBase::onUpdate()
{
    if (oneContact.name == "" || oneContact.phone == "" || !db.isOpen()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE  Contacts SET Name = :Name, Phone = :Phone WHERE ID = :id;");
    query.bindValue(":Name", oneContact.name);
    query.bindValue(":Phone", oneContact.phone);
    query.bindValue(":id", oneContact.id);

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "DataBase update error!";
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
// Метод удаления записи в таблице
bool DataBase::onDelete()
{
    if (oneContact.name == "" || oneContact.phone == "" || !db.isOpen()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Contacts WHERE ID = :id;");
    query.bindValue(":id", oneContact.id);
    query.exec();

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "DataBase delete error!";
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
