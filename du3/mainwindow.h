#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "selectfolder_df.h"
#include "filefinder.h"
#include "gifplayer.h"
#include "delselectorlistwidget.h"
#include "dupstatswidget.h"
#include "delsatswidget.h"

namespace Ui {

class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Page{Home, FindDuplicates, Output, About, Help};

    enum class OutputState{Scanning, Default, DupStats, Deleting, DelStats};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void gotopage(Page page);

    void setOutputState(OutputState state);

    QStringList findFiles();

    void showDelList(vector<DelDupSet> delDupSetList);

    void clearDelList();

    void findDuplicates();

    void deleteDuplicates();

    OutputState currentOutputState();

    void startAnimation();

    void stopAnimation();

    void resetWidgets();

private slots:
    void on_pushButton_mp_definition_clicked();

    void on_pushButton_dp_findduplicates_clicked();

    void on_pushButton_dp_addfolder_clicked();

    void on_pushButton_op_delete_clicked();
    
private:
    Ui::MainWindow *ui;

    SelectFolders_dialog_df selfolder_dialog;

    FileFinder_fd fileFinder;

    GifPlayer *scaningAnimation;

    GifPlayer *deletingduplicates;
    
    DelSelectorListWidget *delListWidget;

    DupStatsWidget *dupStatsWidget;
    
    DelStatsWidget *delStatsWidget;
};

#endif // MAINWINDOW_H
