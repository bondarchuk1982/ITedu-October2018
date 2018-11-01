#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , menuBar(new QMenuBar)
    , sqlView(new QTableView)
    , sqlEdit(new QTextEdit)
    , sqlResults(new QTextEdit)
    , nameContact(new QLineEdit("Name"))
    , phoneNumber(new QLineEdit("Phone number"))
    , addContact(new QPushButton("Add"))
    , updateContact(new QPushButton("Update"))
    , deleteContact(new QPushButton("Delete"))
    , sqlModel(new QSqlQueryModel(sqlView))
    , db(new DataBase)
{
    initMenus();

    sqlResults->setReadOnly(true);
    sqlResults->setMaximumHeight(100);

    sqlView->setModel(sqlModel);
    sqlView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(sqlView, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(onTableViewDoubleClicked(const QModelIndex&)));

    QSplitter* vSplitter = new QSplitter(Qt::Vertical);
    vSplitter->addWidget(sqlView);
    vSplitter->addWidget(sqlEdit);
    vSplitter->setStretchFactor(0, 3);
    vSplitter->setStretchFactor(1, 1);

    QSplitter* hSplitter = new QSplitter(Qt::Horizontal);
    hSplitter->addWidget(nameContact);
    hSplitter->addWidget(phoneNumber);
    hSplitter->addWidget(addContact);
    hSplitter->addWidget(updateContact);
    hSplitter->addWidget(deleteContact);
    hSplitter->setStretchFactor(0, 1);
    hSplitter->setStretchFactor(1, 1);

    contactWidgetEnable(false);
    contactWidgetConnect();

    QVBoxLayout* vlayo = new QVBoxLayout;
    vlayo->setMargin(0);
    vlayo->setSpacing(5);
    vlayo->addWidget(menuBar);
    vlayo->addWidget(vSplitter);
    vlayo->addWidget(hSplitter);
    vlayo->addWidget(sqlResults);

    this->setLayout(vlayo);

    connect(db, SIGNAL(sqlData(QSqlQuery&)), SLOT(onSqlQueryValue(QSqlQuery&)));
}
void MainWindow::initMenus()
{
    auto menuDatabase = menuBar->addMenu("&Database");
    menuDatabase->addAction("Creat", this, &MainWindow::onCreat);
    menuDatabase->addAction("Connect", this, &MainWindow::onConnection);
    menuDatabase->addAction("Disconnect", this, &MainWindow::onDisconnection);
    menuDatabase->addSeparator();
    menuDatabase->addAction("E&xit", this, &MainWindow::onExit);

    auto menuQuery = menuBar->addMenu("Queries");
    menuQuery->addAction("Run", this, &MainWindow::onRunning, Qt::Key_F5);
}
void MainWindow::onCreat()
{
    creatDBWidget = new QWidget();

    fileName = new QLineEdit("myContacts.db");
    dirName  = new QLineEdit(QDir::currentPath());
    openDir  = new QPushButton("Open");
    okBtn    = new QPushButton("Ok");
    exitBtn  = new QPushButton("Exit");
    gridForCreatDBWidget = new QGridLayout;

    gridForCreatDBWidget->setMargin(2);
    gridForCreatDBWidget->setSpacing(2);

    gridForCreatDBWidget->addWidget(fileName, 0, 0, 1, 2);
    gridForCreatDBWidget->addWidget(dirName, 1, 0);
    gridForCreatDBWidget->addWidget(openDir, 1, 1);
    gridForCreatDBWidget->addWidget(okBtn, 2, 0);
    gridForCreatDBWidget->addWidget(exitBtn, 2, 1);

    connect(openDir, SIGNAL(clicked()), SLOT(onOpenDirForCreatDataBaseWidget()));
    connect(okBtn, SIGNAL(clicked()), SLOT(onOkForCreatDataBaseWidget()));
    connect(exitBtn, SIGNAL(clicked()), SLOT(onExitForCreatDataBaseWidget()));

    creatDBWidget->setLayout(gridForCreatDBWidget);
    creatDBWidget->show();
}
void MainWindow::onConnection()
{
    QFileDialog dialog(this);
    databaseFullPath = dialog.getOpenFileName();

    if (databaseFullPath != "") {
        if(!db->connectToDataBase(databaseFullPath)) {
            QMessageBox::critical(this, "Error!", "DataBase connect error!");
        }

        onSelectAllDataInTable();
        addContact->setEnabled(true);
        nameContact->setEnabled(true);
        phoneNumber->setEnabled(true);
    }
}
void MainWindow::onDisconnection()
{
    db->closeDataBase();
}
void MainWindow::onExit()
{
    this->close();
}
void MainWindow::onRunning()
{
    db->sqlQuery(sqlEdit->document()->toPlainText());
}

void MainWindow::onCreatTable()
{
    db->sqlQuery("CREATE TABLE Contacts (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "Date NOT NULL, "
                              "Time NOT NULL, "
                              "Name VARCHAR(255) NOT NULL, "
                              "Phone VARCHAR(10) NOT NULL);");

    onSelectAllDataInTable();
    contactWidgetEnable(true);
}
void MainWindow::onSelectAllDataInTable()
{
    db->sqlQuery("SELECT * FROM Contacts;");
}

void MainWindow::contactWidgetEnable(bool flag)
{
    nameContact->setEnabled(flag);
    phoneNumber->setEnabled(flag);
    addContact->setEnabled(flag);
    updateContact->setEnabled(flag);
    deleteContact->setEnabled(flag);
}
void MainWindow::contactWidgetConnect()
{
    connect(addContact, SIGNAL(clicked()), SLOT(onContactAdd()));
    connect(updateContact, SIGNAL(clicked()), SLOT(onContactUpdate()));
    connect(deleteContact, SIGNAL(clicked()), SLOT(onContactDelete()));
}

void MainWindow::onContactAdd()
{
    if (nameContact->text() == "" || phoneNumber->text() == "") {
        return;
    }

    db->oneContact.name = nameContact->text();
    db->oneContact.phone = phoneNumber->text();

    if (db->onAdd()) {
        onSelectAllDataInTable();
    }
}
void MainWindow::onContactUpdate()
{
    if (nameContact->text() == "" || phoneNumber->text() == "") {
        return;
    }

    db->oneContact.name = nameContact->text();
    db->oneContact.phone = phoneNumber->text();

    if (db->onUpdate()) {
        onSelectAllDataInTable();
    }
}
void MainWindow::onContactDelete()
{
    if (nameContact->text() == "" || phoneNumber->text() == "") {
        return;
    }

    if (db->onDelete()) {
        onSelectAllDataInTable();
    }
}

void MainWindow::onTableViewDoubleClicked(const QModelIndex &mi)
{
    QModelIndex tmp = mi.model()->index(mi.row(), 0);
    QVariant var = tmp.data();
    db->oneContact.id = var.toInt();

    tmp = mi.model()->index(mi.row(), 1);
    var = tmp.data();
    db->oneContact.date = var.toDate();

    tmp = mi.model()->index(mi.row(), 2);
    var = tmp.data();
    db->oneContact.time = var.toTime();

    tmp = mi.model()->index(mi.row(), 3);
    var = tmp.data();
    db->oneContact.name = var.toString();
    nameContact->setText(var.toString());

    tmp = mi.model()->index(mi.row(), 4);
    var = tmp.data();
    db->oneContact.phone = var.toString();
    phoneNumber->setText(var.toString());

    updateContact->setEnabled(true);
    deleteContact->setEnabled(true);
}

void MainWindow::onOpenDirForCreatDataBaseWidget()
{
    creatDBWidget->hide();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                              dirName->text(),
                                              QFileDialog::ShowDirsOnly
                                              | QFileDialog::DontResolveSymlinks);
    if (dir != "") {
        dirName->setText(dir);
    }
    creatDBWidget->show();
}
void MainWindow::onOkForCreatDataBaseWidget()
{
    databaseFullPath = dirName->text() + "/" + fileName->text();

    if (db->openDataBase(databaseFullPath)) {
        databaseName = fileName->text();
        sqlResults->append("Data base is creat : ");
        sqlResults->append(databaseFullPath);
    }
    onCreatTable();

    onDisconnection();
    onExitForCreatDataBaseWidget();
}
void MainWindow::onExitForCreatDataBaseWidget()
{
    creatDBWidget->hide();
    delete creatDBWidget;
}
void MainWindow::onSqlQueryValue(QSqlQuery& query)
{
    sqlModel->setQuery(query);
    sqlResults->append(sqlModel->lastError().text());
}
