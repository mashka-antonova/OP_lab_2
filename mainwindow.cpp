#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C" {
#include "appcontext.h"
#include "entrypoint.h"
#include "iterator.h"
#include "list.h"
}

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    context.list = nullptr;
    context.totalRows = 0;
    context.errorRows = 0;
    context.programmStatus = STATUS_OK;

    ui->tableWidget->setColumnCount(COLUMN_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels({
        "Year", "Region", "Nat.Growth", "Birth Rate",
        "Death Rate", "Dem.Weight", "Urbanization"
    });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    if (context.list != nullptr)
        disposeList(context.list);

    delete ui;
}

QString MainWindow::errorText(Status error){
    QString str;
    switch(error){
    case STATUS_OK:
        str = "";
        break;
    case ERR_MALLOC_FAILED:
        str = "Memory allocation failed";
        break;
    case ERR_FILE_OPEN:
        str = "Failed to open file";
        break;
    case ERR_EMPTY_DATA:
        str = "The loaded file is empty";
        break;
    case ERR_INVALID_REGION:
        str = "Invalid region";
        break;
    case ERR_INVALID_COLUMN:
        str = "Invalid column";
        break;
    case ERR_INVALID_HEADER:
        str = "Invalid header row";
        break;
    default:
        str = "Unknown error";
        break;
    }
    return str;
}

void MainWindow::showError(){
    ui->outputErrorLabel->setText(errorText(context.programmStatus));
}

void MainWindow::on_selectFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose CSV file", "", "CSV Files (*.csv);;All Files (*)");
    if (!fileName.isEmpty())
        ui->filePath->setText(fileName);
    else
        context.programmStatus = ERR_EMPTY_DATA;
}


void MainWindow::on_regionInput_editingFinished()
{

}

void MainWindow::on_loadData_clicked()
{

}


void MainWindow::on_calculateMetrix_clicked()
{

}




