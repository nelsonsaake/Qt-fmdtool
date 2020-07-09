#ifndef FILEPROPTSDIALOG_H
#define FILEPROPTSDIALOG_H

#include <QDialog>
#include <QTableWidget>

#include <duplicatefinder/fileProperties/fileProperties.h>

namespace Ui {
class FileProptsDialog;
}

class FileProptsDialog : public QDialog
{
    Q_OBJECT
    enum class Column{Name, Value, BadColumn};
    
public:
    explicit FileProptsDialog(QString fileName, QWidget *parent = 0);
    ~FileProptsDialog();
    
    void fillTable();

    void addHeaders();

    void addField(QString name, QString val);

    void addNameColItem(QString val);

    void addValueColItem(QString val);

    void addItem(QString val, Column col);

private slots:
    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::FileProptsDialog *ui;

    FilePropts filepropts;

    QTableWidget *table;
};

#endif // FILEPROPTSDIALOG_H
