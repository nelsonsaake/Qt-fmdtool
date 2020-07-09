#include "selectfolder_df.h"
#include "QFileDialog"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

// === selectfolders_dialog_df ===

SelectFolders_dialog_df::SelectFolders_dialog_df(QGridLayout *gl)
    : id(0), gl(gl)
{
}


// --- select folders ---

QString SelectFolders_dialog_df::execGetDirDialog()
{
    // use dialog to select folders and return the name

    QFileDialog::Option options = QFileDialog::ShowDirsOnly;

    QString directory = QFileDialog::getExistingDirectory(
                nullptr,
                "Select Folder",
                "e:/",
                options);

    return directory;
}

void SelectFolders_dialog_df::exec()
{
    // this function will receive the name of a folder
    // if it's child or parent exists give an error
    // otherwise add a widget to represent the selected folder

    QString dir = execGetDirDialog();

    if(dir.isEmpty()) return;

    if(isChildOfAnotherFolder(dir)){
        parentFolderExistsError();
        return;
    }

    if(isParentOfAnotherFolder(dir)){
        childExistsFolderError();
        return;
    }

    addFolderToView(dir);
}


// --- adding a selected folder to the ui ---

void SelectFolders_dialog_df::addFolderToView(QString dirname)
{
    // here we add a widget to the screen that will represent a
    // folder

    if(this->gl==nullptr) {
        nullGridLayoutError();
        return;
    }

    FolderWidget *folder = new FolderWidget(nextId(),dirname);

    gl->addWidget(folder->widget());

    selectedFolders.push_back(folder);

    connect(folder, SIGNAL(removingFolder(int)), this, SLOT(selectedFolderRemoved(int)));
}

int SelectFolders_dialog_df::nextId(){
    id += 1;
    return id;
}


// --- when selected folder is to be removed ---

void SelectFolders_dialog_df::selectedFolderRemoved(int id)
{
    // when a folder is removed
    // the widget will be properly removed from the list
    // and properly destroyed

    for(int i=0; i<selectedFolders.size(); i++){

        FolderWidget *folder = selectedFolders[i];

        if(folder->getId()==id){
            folder->~FolderWidget();
            selectedFolders.erase(selectedFolders.begin()+i);
        }
    }
}


// --- for getting selected folders ---

vector<Folder> SelectFolders_dialog_df::getFolders()
{
    // this is were we get a list of the selected folders
    // we don't need the actual widgets just the data they represents
    // we just get the data from the widgets and return to the caller

    vector<Folder> vf;

    for(FolderWidget *folder: selectedFolders){

        if(folder == nullptr) continue;

        Folder df {
            folder->name(),
            folder->isKeep()
        };

        vf.push_back(df);
    }

    return vf;
}

QStringList SelectFolders_dialog_df::getSelectedFolderNamesOnly()
{
    // we just get the name of the folders and return it to the callers

    QStringList sl;

    for(FolderWidget *sf: selectedFolders){

        if(sf == nullptr) continue;

        sl << sf->name();
    }

    return sl;
}


// --- error checking ---

bool SelectFolders_dialog_df::isChildFolder(QString folder, QString otherFolder)
{
    return otherFolder.contains(folder);
}

bool SelectFolders_dialog_df::isChildOfAnotherFolder(QString folder)
{
    for(FolderWidget *kf: selectedFolders){

        if(kf == nullptr) continue;

        QString otherFolder = kf->name();

        if(isChildFolder(folder, otherFolder)) return true;
    }

    return false;
}

bool SelectFolders_dialog_df::isParentOfAnotherFolder(QString folder)
{
    for(FolderWidget *kf: selectedFolders){

        if(kf == nullptr) continue;

        QString child = kf->name();

        if(isChildFolder(child, folder)) return true;
    }

    return false;
}


// --- error messages ---

void SelectFolders_dialog_df::nullGridLayoutError()
{
    QMessageBox::warning(
                nullptr,
                "Error",
                "Error, trying to display the selected folder. The grid layout is a nullptr. Assign a grid layout",
                QMessageBox::Ok);
}

void SelectFolders_dialog_df::childExistsFolderError()
{
    QMessageBox::warning(
                nullptr,
                "Error",
                "Error, tyring to add folder. \nA parent folder of this folder is already selected. "
                "\nRemove parent folder to be able to add this one.",
                QMessageBox::Ok);
}

void SelectFolders_dialog_df::parentFolderExistsError()
{
    QMessageBox::warning(
                nullptr,
                "Error",
                "Error, tyring to add folder. \nA sub-folder is already selected. \nRemove sub-folder to be able to add this one.",
                QMessageBox::Ok);
}


// === folder widget ===

FolderWidget::FolderWidget(int id, QString name)
    : id(id),
      label_name(new QLabel(name)),
      checkBox_keep(new QCheckBox("Keep duplicates in this folder")),
      pushButton_removeFolder(new QPushButton("Remove Folder")),
      layoutBox_row(new QGridLayout),
      folder(new QWidget){

    setup();
    connect(pushButton_removeFolder, SIGNAL(clicked(bool)), this, SLOT(sendRemovingFolderSignal()));
}

void FolderWidget::setup(){

    layoutBox_row->addWidget(label_name, row, col1);
    layoutBox_row->addWidget(checkBox_keep, row, col2);
    layoutBox_row->addWidget(pushButton_removeFolder, row, col3, Qt::AlignRight);
    folder->setLayout(layoutBox_row);
}

// --- getters ---

bool FolderWidget::isKeep(){
    if(checkBox_keep==nullptr) return false;
    return checkBox_keep->isChecked();
}

QString FolderWidget::name(){
    return label_name->text();
}

FolderWidget::~FolderWidget(){
    label_name->deleteLater();
    checkBox_keep->deleteLater();
    pushButton_removeFolder->deleteLater();
    layoutBox_row->deleteLater();
    folder->deleteLater();
}

QWidget *FolderWidget::widget(){
    return folder;
}

int FolderWidget::getId(){
    return id;
}

void FolderWidget::sendRemovingFolderSignal(){
    emit removingFolder(id);
}
