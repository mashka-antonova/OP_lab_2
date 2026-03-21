#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "appcontext.h"
#include "entrypoint.h"
#include "iterator.h"
}

#include <QMainWindow>

#define COLUMN_COUNT 7

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFile_clicked();
    void on_loadData_clicked();
    void on_calculateMetrix_clicked();
    void on_regionInput_editingFinished();

private:
    Ui::MainWindow *ui;
    AppContext context;

    QString errorText(Status error);
    void showError();
    void updateTable(const QString& region);

};

#endif // MAINWINDOW_H
