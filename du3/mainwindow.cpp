#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listheightadjuster_df.h"
#include "delselectorlistwidget.h"
#include "deleteselector.h"
#include "dupstatswidget.h"
#include "deleter.h"
#include <QLabel>
#include <duplicatefinder/duplicates.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selfolder_dialog.gl = ui->gridLayout;

    QString lookingGif{":/img/animation/loading/1.gif"};
    scaningAnimation = new GifPlayer(
                lookingGif,
                ui->label_scanninganimation);

    QString deletingGif{":/img/animation/deleting/2.gif"};
    deletingduplicates = new GifPlayer(
                deletingGif,
                ui->label_deletinganimation);

    dupStatsWidget = new DupStatsWidget(ui->label_duplicatesummary);

    delStatsWidget = new DelStatsWidget(ui->label_deletesummary);

    delListWidget = nullptr;

    gotopage(Home);

    setOutputState(OutputState::Default);

    startAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::gotopage(Page page)
{
    ui->tabWidget->setCurrentIndex(page);
}

QStringList MainWindow::findFiles()
{
    QStringList searchareas = selfolder_dialog.getSelectedFolderNamesOnly();

    fileFinder.setSearchareas(searchareas);

    return fileFinder.findMusicFilesIAT();
}



void MainWindow::showDelList(vector<DelDupSet> delDupSetList)
{
    if(delListWidget == nullptr)
        delListWidget = new
                DelSelectorListWidget(ui->verticalLayout_duplicatesList, delDupSetList);

    connect(delListWidget, SIGNAL(listChanged(vector<DelWidget*>*)), dupStatsWidget, SLOT(refresh(vector<DelWidget*>*)));
}

void MainWindow::clearDelList()
{
    if(delListWidget == nullptr) return;

    if(dupStatsWidget != nullptr)
        disconnect(delListWidget, SIGNAL(listChanged(vector<DelWidget*>*)), dupStatsWidget, SLOT(refresh(vector<DelWidget*>*)));

    delListWidget->clear();

    delListWidget->~DelSelectorListWidget();

    delListWidget = nullptr;
}



void MainWindow::findDuplicates()
{
    setOutputState(OutputState::Scanning);
    startAnimation();

    vector<DupSet> dupSetList = DupFinder().findDupsIAT_df(findFiles());
    vector<Folder> vkf = selfolder_dialog.getFolders();

    DeleteSelector delSel;
    delSel.set(dupSetList, vkf);
    showDelList(delSel.getDelList());

    dupStatsWidget->set(delListWidget->getDelListWidget());
    dupStatsWidget->displayStats();

    stopAnimation();
    setOutputState(OutputState::DupStats);
}

void MainWindow::deleteDuplicates()
{
    setOutputState(OutputState::Deleting);

    startAnimation();

    qint64 freeableSpace = dupStatsWidget->freeableSpace();

    QStringList delList = delListWidget->getDelList();
    Deleter deleter(delList);
    deleter.deleteIAT();

    clearDelList();

    delStatsWidget->setClearedSpace(freeableSpace);

    delStatsWidget->displayStats();

    setOutputState(OutputState::DelStats);

    stopAnimation();
}



void MainWindow::setOutputState(MainWindow::OutputState state)
{
    ui->stackedWidget->setCurrentIndex(int(state));
}

MainWindow::OutputState MainWindow::currentOutputState()
{
    return OutputState(ui->stackedWidget->currentIndex());
}



void MainWindow::startAnimation()
{
    OutputState outputState = currentOutputState();

    switch(outputState){
    case OutputState::Scanning:
        scaningAnimation->start();
        break;
    case OutputState::Deleting:
        deletingduplicates->start();
        break;
    default:
        break;
    }

    return;
}

void MainWindow::stopAnimation()
{
    OutputState outputState = currentOutputState();

    switch(outputState){
    case OutputState::Scanning:
        scaningAnimation->stop();
        break;
    case OutputState::Deleting:
        deletingduplicates->stop();
        break;
    default:
        break;
    }

    return;
}


void MainWindow::resetWidgets()
{
    fileFinder = FileFinder_fd();

    clearDelList();

    setOutputState(OutputState::Default);
}


void MainWindow::on_pushButton_mp_definition_clicked()
{
    gotopage(FindDuplicates);
}

void MainWindow::on_pushButton_dp_findduplicates_clicked()
{
    QPushButton *btn_finddups = ui->pushButton_dp_findduplicates;

    btn_finddups->setEnabled(false);

    resetWidgets();

    gotopage(Output);

    findDuplicates();

    btn_finddups->setEnabled(true);
}

void MainWindow::on_pushButton_dp_addfolder_clicked()
{
    selfolder_dialog.exec();
}

void MainWindow::on_pushButton_op_delete_clicked()
{
    deleteDuplicates();
}
