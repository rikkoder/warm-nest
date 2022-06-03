#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hostelersform.h"
#include "staffsform.h"
#include "complaintsform.h"
#include "remarkinput.h"
#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent, Connector *conn): QMainWindow(parent) , ui(new Ui::MainWindow) {
    if (conn == nullptr) std::cerr << "danger with nlptr";

    ui->setupUi(this);
    this->setMinimumSize(700, 600);

    this->conn = conn;
    this->conn->initDB();

    this->setCentralWidget(ui->tabWidget);
    ui->tabWidget->showFullScreen();
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(tabs::HOSTELERS, "Hostelers");
    ui->tabWidget->setTabText(tabs::STAFFS, "Staffs");
    ui->tabWidget->setTabText(tabs::COMPLAINTS, "Complaints");
    ui->tabWidget->setTabText(tabs::ABOUT, "About App");

    initializeHostelersTable();
    initializeStaffsTable();
    initializeComplaintsTable();
    // initialize about_app
    ui->about_app->setLayout(ui->about_app_layout);
    ui->about_app_text->setOpenExternalLinks(true);

    on_tabWidget_currentChanged(tabs::HOSTELERS);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index) {
    if (index == tabs::HOSTELERS) {
        sql::ResultSet *res = conn->getAllHostelers();
        uint64_t rows = res->rowsCount();
        ui->hostelers_table->setRowCount(rows);

        uint64_t r = 0;
        while (res->next()) {
            QTableWidgetItem *room = new QTableWidgetItem(tr(res->getString(1)));
            QTableWidgetItem *roll = new QTableWidgetItem(QString::number(res->getUInt64(2)));
            QTableWidgetItem *name = new QTableWidgetItem(tr(res->getString(3)));
            QTableWidgetItem *branch = new QTableWidgetItem(tr(res->getString(4)));
            QTableWidgetItem *phone = new QTableWidgetItem(QString::number(res->getUInt64(5)));
            QTableWidgetItem *email = new QTableWidgetItem(tr(res->getString(6)));
            QTableWidgetItem *emergency = new QTableWidgetItem(QString::number(res->getUInt64(7)));
            QTableWidgetItem *remark = new QTableWidgetItem(tr(res->getString(8)));

            // make table contents uneditable
            room->setFlags(room->flags() & ~Qt::ItemIsEditable);
            roll->setFlags(roll->flags() & ~Qt::ItemIsEditable);
            name->setFlags(name->flags() & ~Qt::ItemIsEditable);
            branch->setFlags(branch->flags() & ~Qt::ItemIsEditable);
            phone->setFlags(phone->flags() & ~Qt::ItemIsEditable);
            email->setFlags(email->flags() & ~Qt::ItemIsEditable);
            emergency->setFlags(emergency->flags() & ~Qt::ItemIsEditable);
            remark->setFlags(remark->flags() & ~Qt::ItemIsEditable);



            ui->hostelers_table->setItem(r, 0, room);
            ui->hostelers_table->setItem(r, 1, roll);
            ui->hostelers_table->setItem(r, 2, name);
            ui->hostelers_table->setItem(r, 3, branch);
            ui->hostelers_table->setItem(r, 4, phone);
            ui->hostelers_table->setItem(r, 5, email);
            ui->hostelers_table->setItem(r, 6, emergency);
            ui->hostelers_table->setItem(r, 7, remark);

            r++;
        }
    } else if (index == tabs::STAFFS) {
        sql::ResultSet *res = conn->getAllStaffs();
        uint64_t rows = res->rowsCount();
        ui->staffs_table->setRowCount(rows);

        uint64_t r = 0;
        while (res->next()) {
            QTableWidgetItem *floor_block = new QTableWidgetItem(tr(res->getString(1)));
            QTableWidgetItem *staff_id = new QTableWidgetItem(tr(res->getString(2)));
            QTableWidgetItem *name = new QTableWidgetItem(tr(res->getString(3)));
            QTableWidgetItem *designation = new QTableWidgetItem(tr(res->getString(4)));
            QTableWidgetItem *phone = new QTableWidgetItem(QString::number(res->getUInt64(5)));
            QTableWidgetItem *email = new QTableWidgetItem(tr(res->getString(6)));
            QTableWidgetItem *remark = new QTableWidgetItem(tr(res->getString(7)));

            // make table contents uneditable
            floor_block->setFlags(floor_block->flags() & ~Qt::ItemIsEditable);
            staff_id->setFlags(staff_id->flags() & ~Qt::ItemIsEditable);
            name->setFlags(name->flags() & ~Qt::ItemIsEditable);
            designation->setFlags(designation->flags() & ~Qt::ItemIsEditable);
            phone->setFlags(phone->flags() & ~Qt::ItemIsEditable);
            email->setFlags(email->flags() & ~Qt::ItemIsEditable);
            remark->setFlags(remark->flags() & ~Qt::ItemIsEditable);

            ui->staffs_table->setItem(r, 0, floor_block);
            ui->staffs_table->setItem(r, 1, staff_id);
            ui->staffs_table->setItem(r, 2, name);
            ui->staffs_table->setItem(r, 3, designation);
            ui->staffs_table->setItem(r, 4, phone);
            ui->staffs_table->setItem(r, 5, email);
            ui->staffs_table->setItem(r, 6, remark);

            r++;
        }
    } else if (index == tabs::COMPLAINTS) {
        sql::ResultSet *res = conn->getAllComplaints();
        uint64_t rows = res->rowsCount();
        std::cout << "\ncomplaint rows: " << rows << '\n';
        ui->complaints_table->setRowCount(rows);

        uint64_t r = 0;
        while (res->next()) {
            QTableWidgetItem *complaint_id = new QTableWidgetItem(QString::number(res->getUInt64(1)));
            QTableWidgetItem *date = new QTableWidgetItem(tr(res->getString(2)));
            QTableWidgetItem *roll = new QTableWidgetItem(QString::number(res->getUInt64(3)));
            QTableWidgetItem *name = new QTableWidgetItem(tr(res->getString(4)));
            QTableWidgetItem *room = new QTableWidgetItem(tr(res->getString(5)));
            QTableWidgetItem *phone = new QTableWidgetItem(QString::number(res->getUInt64(6)));
            QTableWidgetItem *category = new QTableWidgetItem(tr(res->getString(7)));
            QTableWidgetItem *complaint = new QTableWidgetItem(tr(res->getString(8)));
            QTableWidgetItem *status = new QTableWidgetItem(res->getBoolean(9) ? "Resolved" : "Pending");
            QTableWidgetItem *remark = new QTableWidgetItem(tr(res->getString(10)));

            // make table contents uneditable
            complaint_id->setFlags(complaint_id->flags() & ~Qt::ItemIsEditable);
            date->setFlags(date->flags() & ~Qt::ItemIsEditable);
            roll->setFlags(roll->flags() & ~Qt::ItemIsEditable);
            name->setFlags(name->flags() & ~Qt::ItemIsEditable);
            room->setFlags(room->flags() & ~Qt::ItemIsEditable);
            phone->setFlags(phone->flags() & ~Qt::ItemIsEditable);
            category->setFlags(category->flags() & ~Qt::ItemIsEditable);
            complaint->setFlags(complaint->flags() & ~Qt::ItemIsEditable);
            status->setFlags(status->flags() & ~Qt::ItemIsEditable);
            remark->setFlags(remark->flags() & ~Qt::ItemIsEditable);

            ui->complaints_table->setItem(r, 0, complaint_id);
            ui->complaints_table->setItem(r, 1, date);
            ui->complaints_table->setItem(r, 2, roll);
            ui->complaints_table->setItem(r, 3, name);
            ui->complaints_table->setItem(r, 4, room);
            ui->complaints_table->setItem(r, 5, phone);
            ui->complaints_table->setItem(r, 6, category);
            ui->complaints_table->setItem(r, 7, complaint);
            ui->complaints_table->setItem(r, 8, status);
            ui->complaints_table->setItem(r, 9, remark);

            r++;
        }
    } else {
        // do nothing
    }
}

void MainWindow::initializeHostelersTable() {
    ui->delete_hosteler->setEnabled(false);
    ui->remark_hosteler->setEnabled(false);
    ui->searchbox_hosteler->setPlaceholderText("🔍 enter roll number..");

    // insert columns before labellling
    for (int i=0; i<8; i++) {
        ui->hostelers_table->insertColumn(i);
    }

    QStringList header;
    header << "Room" << "Roll" << "Name" << "Branch" << "Phone" << "Email" << "Emergency Contact" << "Remark";
    ui->hostelers_table->setHorizontalHeaderLabels(header);
    ui->hostelers_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->hostelers_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->hostelers->setLayout(ui->hostelers_layout);

    // toggle Delete button when rows are selected/deselected
    connect(ui->hostelers_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::rowsSelected);
}

void MainWindow::initializeStaffsTable() {
    ui->delete_staff->setEnabled(false);
    ui->remark_staff->setEnabled(false);
    ui->searchbox_staff->setPlaceholderText("🔍 enter staff id..");

    // insert columns before labelling
    for (int i=0; i<7; i++) {
        ui->staffs_table->insertColumn(i);
    }

    QStringList header;
    header << "Floor Block" << "Staff ID" << "Name" << "Designation" << "Phone" << "Email" << "Remark";
    ui->staffs_table->setHorizontalHeaderLabels(header);
    ui->staffs_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->staffs_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->staffs->setLayout(ui->staffs_layout);

    // toggle Delete button when rows are selected/deselected
    connect(ui->staffs_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::rowsSelected);
}

void MainWindow::initializeComplaintsTable() {
    ui->delete_complaint->setEnabled(false);
    ui->remark_complaint->setEnabled(false);
    ui->searchbox_complaint->setPlaceholderText("🔍 enter complaint id..");

    // insert columns before labelling
    for (int i=0; i<10; i++) {
        ui->complaints_table->insertColumn(i);
    }

    QStringList header;
    header << "Complaint ID" << "Date" << "Roll No" << "Name" << "Room No" << "Phone" << "Category" << "Complaint" << "Status" << "Remark";
    ui->complaints_table->setHorizontalHeaderLabels(header);
    ui->complaints_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->complaints_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->complaints->setLayout(ui->complaints_layout);

    // toggle Delete button when rows are selected/deselected
    connect(ui->complaints_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::rowsSelected);
}

// toggle Delete and Remark button
void MainWindow::rowsSelected() {
    if (ui->hostelers_table->selectionModel()->selectedRows().length() == 0) {
        ui->delete_hosteler->setEnabled(false);
        ui->remark_hosteler->setEnabled(false);
    } else {
        ui->delete_hosteler->setEnabled(true);
        ui->remark_hosteler->setEnabled(true);
    }

    if (ui->staffs_table->selectionModel()->selectedRows().length() == 0) {
        ui->delete_staff->setEnabled(false);
        ui->remark_staff->setEnabled(false);
    } else {
        ui->delete_staff->setEnabled(true);
        ui->remark_staff->setEnabled(true);
    }

    if (ui->complaints_table->selectionModel()->selectedRows().length() == 0) {
        ui->delete_complaint->setEnabled(false);
        ui->remark_complaint->setEnabled(false);
        ui->resolve_complaint->setEnabled(false);
    } else {
        ui->delete_complaint->setEnabled(true);
        ui->remark_complaint->setEnabled(true);
        ui->resolve_complaint->setEnabled(true);
    }
}


// hostelers buttons
void MainWindow::on_add_hosteler_clicked() {
    HostelersForm hf(this->conn, this);
    hf.exec();

    // reload table;
    on_tabWidget_currentChanged(tabs::HOSTELERS);
}


void MainWindow::on_delete_hosteler_clicked() {
    // roll is 1st column (0 indexing)
    QModelIndexList rows = ui->hostelers_table->selectionModel()->selectedRows(1);
    uint64_t n = rows.length();

    std::string rolls[n];
    for (uint64_t i = 0; i < n; i++) {
        rolls[i] = rows[i].data().toString().toStdString();
    }

    QString msg;

    if (n <= 5) {
        msg = "Records for these roll numbers will be deleted :\n";
        for (uint64_t i=0; i<n; i++) msg += rows[i].data().toString() + '\n';
        msg += "\nAre you sure ?";
    } else {
        msg = "Records for " + QString::number(n) + " roll numbers will be deleted !\n\nAre you sure ?";
    }

    // user reply from confirm box to decide whether to delete the data or not
    if (QMessageBox::question(this, "Confirmation", msg) == QMessageBox::Yes) {
        conn->deleteHosteler(n, rolls);

        ui->hostelers_table->selectionModel()->reset();

        // reload table
        on_tabWidget_currentChanged(tabs::HOSTELERS);
    }
}


void MainWindow::on_search_hosteler_clicked() {
    QString roll = ui->searchbox_hosteler->text();
    if (invalid_roll(roll)) {
        alert("invalid roll number !");
        return;
    }

    // roll is 1st column (0 indexing)
    int col = 1;

    uint64_t rows = ui->hostelers_table->rowCount();
    uint64_t row = -1;
    for (uint64_t r = 0; r < rows; r++) {
        if (ui->hostelers_table->item(r, col)->text() == roll) {
            row = r;
            break;
        }
    }

    if (row != -1ull)
        ui->hostelers_table->selectRow(row);
    else
        alert("Record for " + roll + " not found !");
}


void MainWindow::on_remark_hosteler_clicked() {
    // roll is 1st column (0 indexing)
    QModelIndexList rows = ui->hostelers_table->selectionModel()->selectedRows(1);
    uint64_t n = rows.length();

    std::string rolls[n];
    for (uint64_t i = 0; i < n; i++) {
        rolls[i] = rows[i].data().toString().toStdString();
    }

    QString label;

    if (n <= 5) {
        label = "Enter remarks for these roll numbers :\n";
        for (uint64_t i=0; i<n; i++) label += rows[i].data().toString() + '\n';
    } else {
        label = "Enter remarks for " + QString::number(n) + " roll numbers :";
    }

    RemarkInput ri(this, label);
    ri.exec();

    if (conn->remarkHosteler(n, rolls, ri.getRemark().toStdString()) == sqlerr::UNKNOWN) {
        alert("unknown error occurred !");
    }

    on_tabWidget_currentChanged(tabs::HOSTELERS);
}


// staffs buttons
void MainWindow::on_add_staff_clicked() {
    StaffsForm sf(this->conn, this);
    sf.exec();

    // reload table;
    on_tabWidget_currentChanged(tabs::STAFFS);
}


void MainWindow::on_delete_staff_clicked() {
    // staff_id is 1st column (0 indexing)
    QModelIndexList rows = ui->staffs_table->selectionModel()->selectedRows(1);
    uint64_t n = rows.length();

    std::string staff_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        staff_ids[i] = rows[i].data().toString().toStdString();
    }

    QString msg;

    if (n <= 5) {
        msg = "Records for these Staff IDs will be deleted :\n";
        for (uint64_t i=0; i<n; i++) msg += rows[i].data().toString() + '\n';
        msg += "\nAre you sure ?";
    } else {
        msg = "Records for " + QString::number(n) + " Staff IDs will be deleted !\n\nAre you sure ?";
    }

    // user reply from confirm box to decide whether to delete the data or not
    if (QMessageBox::question(this, "Confirmation", msg) == QMessageBox::Yes) {
        conn->deleteStaff(n, staff_ids);

        ui->staffs_table->selectionModel()->reset();

        // reload table
        on_tabWidget_currentChanged(tabs::STAFFS);
    }
}


void MainWindow::on_search_staff_clicked() {
    QString staff_id = ui->searchbox_staff->text();
    if (invalid_roll(staff_id)) {
       alert("Invalid staff_id");
       return;
    }

    // staff_id is 1st column (0 indexing)
    int col = 1;
    uint64_t rows = ui->staffs_table->rowCount();
    uint64_t row = -1;
    for (uint64_t r = 0; r < rows; r++) {
        if (ui->staffs_table->item(r, col)->text() == staff_id) {
            row = r;
            break;
        }
    }

    if (row != -1ull)
        ui->staffs_table->selectRow(row);
    else
        alert("Record for " + staff_id + " not found !");
}


void MainWindow::on_remark_staff_clicked() {
    // staff_id is 1st column (0 indexing)
    QModelIndexList rows = ui->staffs_table->selectionModel()->selectedRows(1);
    uint64_t n = rows.length();

    std::string staff_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        staff_ids[i] = rows[i].data().toString().toStdString();
    }

    QString label;

    if (n <= 5) {
        label = "Enter remarks for these Staff IDs :\n";
        for (uint64_t i=0; i<n; i++) label += rows[i].data().toString() + '\n';
    } else {
        label = "Enter remarks for " + QString::number(n) + " Staff IDs :";
    }

    RemarkInput ri(this, label);
    ri.exec();

    if (conn->remarkStaff(n, staff_ids, ri.getRemark().toStdString()) == sqlerr::UNKNOWN) {
        alert("unknown error occurred !");
    }

    on_tabWidget_currentChanged(tabs::STAFFS);
}


// complaints buttons
void MainWindow::on_add_complaint_clicked() {
    ComplaintsForm cf(this->conn, this);
    cf.exec();

    // reload table;
    on_tabWidget_currentChanged(tabs::COMPLAINTS);
}


void MainWindow::on_delete_complaint_clicked() {
    // complaint_id is 0th column (0 indexing)
    QModelIndexList rows = ui->complaints_table->selectionModel()->selectedRows(0);
    uint64_t n = rows.length();

    std::string complaint_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        complaint_ids[i] = rows[i].data().toString().toStdString();
    }

    QString msg;

    if (n <= 5) {
        msg = "Records for these Complaint IDs will be deleted :\n";
        for (uint64_t i=0; i<n; i++) msg += rows[i].data().toString() + '\n';
        msg += "\nAre you sure ?";
    } else {
        msg = "Records for " + QString::number(n) + " Complaint IDs will be deleted !\n\nAre you sure ?";
    }

    // user reply from confirm box to decide whether to delete the data or not
    if (QMessageBox::question(this, "Confirmation", msg) == QMessageBox::Yes) {
        conn->deleteComplaint(n, complaint_ids);

        ui->complaints_table->selectionModel()->reset();

        // reload table
        on_tabWidget_currentChanged(tabs::COMPLAINTS);
    }
}


void MainWindow::on_search_complaint_clicked() {
    QString complaint_id = ui->searchbox_complaint->text();
    if (invalid_complaint_id(complaint_id)) {
       alert("Invalid staff_id");
       return;
    }

    // complaint_id is 0th column (0 indexing)
    int col = 0;
    uint64_t rows = ui->complaints_table->rowCount();
    uint64_t row = -1;
    for (uint64_t r = 0; r < rows; r++) {
        if (ui->complaints_table->item(r, col)->text() == complaint_id) {
            row = r;
            break;
        }
    }

    if (row != -1ull)
        ui->complaints_table->selectRow(row);
    else
        alert("Record for " + complaint_id + " not found !");
}


void MainWindow::on_remark_complaint_clicked() {
    // complaint_id is 0th column (0 indexing)
    QModelIndexList rows = ui->complaints_table->selectionModel()->selectedRows(0);
    uint64_t n = rows.length();

    std::string complaint_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        complaint_ids[i] = rows[i].data().toString().toStdString();
    }

    QString label;

    if (n <= 5) {
        label = "Enter remarks for these Complaint IDs :\n";
        for (uint64_t i=0; i<n; i++) label += rows[i].data().toString() + '\n';
    } else {
        label = "Enter remarks for " + QString::number(n) + " Complaint IDs :";
    }

    RemarkInput ri(this, label);
    ri.exec();

    if (conn->remarkComplaint(n, complaint_ids, ri.getRemark().toStdString()) == sqlerr::UNKNOWN) {
        alert("unknown error occurred !");
    }

    on_tabWidget_currentChanged(tabs::COMPLAINTS);
}


void MainWindow::on_resolve_complaint_clicked() {
    // complaint_id is 0th column (0 indexing)
    QModelIndexList rows = ui->complaints_table->selectionModel()->selectedRows(0);
    uint64_t n = rows.length();

    std::string complaint_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        complaint_ids[i] = rows[i].data().toString().toStdString();
    }

    QString msg;

    if (n <= 5) {
        msg = "Complaints with these Complaint IDs will be resolved :\n";
        for (uint64_t i=0; i<n; i++) msg += rows[i].data().toString() + '\n';
        msg += "\nAre you sure ?";
    } else {
        msg = QString::number(n) + " Complaints will be resolved !\n\nAre you sure ?";
    }

    // user reply from confirm box to decide whether to delete the data or not
    if (QMessageBox::question(this, "Confirmation", msg) == QMessageBox::Yes) {
        conn->resolveComplaint(n, complaint_ids);

        // reload table
        on_tabWidget_currentChanged(tabs::COMPLAINTS);
    }
}


void MainWindow::on_deleteResolved_complaint_clicked() {
    // complaint_id is 0th column (0 indexing)
    QModelIndexList rows = ui->complaints_table->selectionModel()->selectedRows(0);
    uint64_t n = rows.length();

    std::string complaint_ids[n];
    for (uint64_t i = 0; i < n; i++) {
        complaint_ids[i] = rows[i].data().toString().toStdString();
    }

    QString msg = "Records for all resolved complaints will be deleted !\n\nAre you sure ?";

    // user reply from confirm box to decide whether to delete the data or not
    if (QMessageBox::question(this, "Confirmation", msg) == QMessageBox::Yes) {
        conn->deleteResolvedComplaints();

        // reload table
        on_tabWidget_currentChanged(tabs::COMPLAINTS);
    }
}

