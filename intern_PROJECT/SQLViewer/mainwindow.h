#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>

#include "database.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

protected:
    QMenuBar* menuBar;

    QTableView* sqlView;

    QTextEdit* sqlEdit;
    QTextEdit* sqlResults;
    QLineEdit* nameContact;
    QLineEdit* phoneNumber;
    QPushButton* addContact;
    QPushButton* updateContact;
    QPushButton* deleteContact;

    QSqlQueryModel* sqlModel;

    QWidget* creatDBWidget;
    QLineEdit* fileName;
    QLineEdit* dirName;
    QPushButton* openDir;
    QPushButton* okBtn;
    QPushButton* exitBtn;
    QGridLayout* gridForCreatDBWidget;

    void initMenus();

    void onCreat();
    void onConnection();
    void onDisconnection();
    void onExit();

    void onRunning();

    void onCreatTable();
    void onSelectAllDataInTable();

    void contactWidgetEnable(bool flag);
    void contactWidgetConnect();
private:
    DataBase* db;

    QString databaseName;
    QString databaseFullPath;
public slots:
    void onSqlQueryValue(QSqlQuery& query);
    void onOpenDirForCreatDataBaseWidget();
    void onOkForCreatDataBaseWidget();
    void onExitForCreatDataBaseWidget();
    void onContactAdd();
    void onContactUpdate();
    void onContactDelete();
    void onTableViewDoubleClicked(const QModelIndex& mi);
};

#endif // MAINWINDOW_H
