#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

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

void MainWindow::on_loadData_clicked()
{
    std::string str = ui->filePath->text().toStdString();
    const char* cStr = str.c_str();

    if (str.empty())
        ui->outputErrorLabel->setText("File not uploaded");
    else {
        AppParams params;
        params.fileName = cStr;

        doOperation(LOAD_DATA, &context, &params);
        showError();
        int successRows = context.totalRows - context.errorRows;
        QMessageBox::information(this, "Результат загрузки",
                                 QString("Всего строк: %1\nУспешно считано: %2\nСтрок с ошибками: %3")
                                     .arg(context.totalRows)
                                     .arg(successRows)
                                     .arg(context.errorRows));
        updateTable(ui->regionInput->text().trimmed());
    }
}

void MainWindow::updateTable(const QString& region) {
    ui->tableWidget->setRowCount(0);
    bool isRegionFound = false;
    bool isRegionEmpty = region.isEmpty();

    Iterator it = begin(context.list);
    int row = 0;
    while (hasNext(&it)) {
        DemographicRecord* record = get(&it);
        QString recordRegion = QString::fromUtf8(record->region);

        if (isRegionEmpty || recordRegion.compare(region, Qt::CaseInsensitive) == 0) {
            if (!isRegionEmpty)
                isRegionFound = true;
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(record->year)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(recordRegion));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(record->natural_population_growth)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(record->birth_rate)));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(record->death_rate)));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(record->general_demographic_weight)));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(record->urbanization)));
            row++;
        }
        next(&it);
    }
    if (!isRegionEmpty && !isRegionFound)
        ui->regionErrorLabel->setText("This region does not exist");
    else
        ui->regionErrorLabel->clear();
}


void MainWindow::on_regionInput_editingFinished()
{

}

void MainWindow::on_calculateMetrix_clicked()
{

}




