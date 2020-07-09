#include "fileproptsdialog.h"
#include "qtablewidgetadjuster.h"
#include "ui_fileproptsdialog.h"
#include <iostream>

using namespace std;

FileProptsDialog::FileProptsDialog(QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileProptsDialog)
{
    ui->setupUi(this);

    setWindowTitle(fileName);
    
    table = ui->tableWidget;
    filepropts = getFilePropts(fileName.toStdString());

    fillTable();

    QTableWidgetAdjuster *adjuster = new QTableWidgetAdjuster(table);
    adjuster->adjustTableau();
}

FileProptsDialog::~FileProptsDialog()
{
    delete ui;
}

void FileProptsDialog::fillTable()
{
    if(table == nullptr) return;    
    
    table->clear();
    table->setColumnCount(2); // name, value
    
    addHeaders();
    
    for(Field field: filepropts.list){
        addField(field.name, field.value);
    }
    
    return;
}

void FileProptsDialog::addHeaders()
{   
    QString nameHeader = "Name";
    QString valHeader = "Value";
    
    addField(nameHeader, valHeader);
}

void FileProptsDialog::addField(QString name, QString val)
{
    addItem(name, Column::Name);
    addItem(val, Column::Value);
}

void FileProptsDialog::addNameColItem(QString val)
{
    addItem(val, Column::Name);
}

void FileProptsDialog::addValueColItem(QString val)
{
    addItem(val, Column::Value);    
}

void FileProptsDialog::addItem(QString val, FileProptsDialog::Column col)
{
    QTableWidgetItem *item = new QTableWidgetItem(val);
    
    int row = table->rowCount();
    if(col == Column::Name){
        table->setRowCount(row+1); // we are assume a new row
    }else {
        row --; // index is -1 the count
    }
    
    table->setItem(row, int(col), item);
    
    return;
}

void FileProptsDialog::on_tableWidget_cellActivated(int row, int column)
{
    QTableWidgetItem *item = table->item(row,column);
    QString txt = item->text();
    ui->label->setText(txt);
}
