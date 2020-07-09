#ifndef SELECTFOLDER_DF_H
#define SELECTFOLDER_DF_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>

using namespace  std;

struct Folder{
    QString name;
    bool keep;
};

class FolderWidget : public QObject{
    // this folder widget is not just any folder widget
    // it particular to this application
    // it has a checkbox - if checked means we keep the contents
    // it as button that allows us to remove it
    //      so say, we selected it and we changed our mind

    Q_OBJECT

public:

    enum Constants{row, col1=0, col2, col3};

    FolderWidget(int id, QString name);

    void setup();

    bool isKeep();

    QString name();

    ~FolderWidget();

    QWidget* widget();

    int getId();

signals:
    void removingFolder(int i);

public slots:
    void sendRemovingFolderSignal();

private:
    int id;
    QLabel* label_name;
    QCheckBox* checkBox_keep;
    QPushButton* pushButton_removeFolder;
    QGridLayout* layoutBox_row;
    QWidget *folder;
};

struct SelectFolders_dialog_df : public QObject
{
    Q_OBJECT

    enum Col{NameCol, KeepCol, RemoveCol};

public:
    SelectFolders_dialog_df(QGridLayout *gl=nullptr);

    QString execGetDirDialog();

    void exec();

    vector<Folder> getFolders();

    QStringList getSelectedFolderNamesOnly();

    bool isChildFolder(QString folder, QString otherFolder);

    bool isChildOfAnotherFolder(QString folder);

    bool isParentOfAnotherFolder(QString folder);

protected:
    void nullGridLayoutError();

    void childExistsFolderError();

    void parentFolderExistsError();

    void addFolderToView(QString dirname);

    int nextId();
public slots:
    void selectedFolderRemoved(int id);

private:
    vector<FolderWidget *> selectedFolders;
    int id;

public:
    QGridLayout *gl;
};

#endif // SELECTFOLDER_DF_H
