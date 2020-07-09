#include "dupstatswidget.h"
#include <QFileInfo>

DupStatsWidget::DupStatsWidget(QLabel *label)
    :label(label)
{
}

void DupStatsWidget::set(vector<DelWidget *> *value)
{
    dupWidgets = value;
}

int DupStatsWidget::filesCount()
{
    return dupWidgets->size();
}

int DupStatsWidget::selectedFilesCount()
{
    int selCount=0;

    for(DelWidget *df : *dupWidgets){
        if(df->isDelete->isChecked()) selCount++;
    }

    return selCount;
}

int DupStatsWidget::unselectedFilesCount()
{
    return filesCount() - selectedFilesCount();
}

qint64 DupStatsWidget::freeableSpace()
{
    qint64 space = 0;

    for(DelWidget *df : *dupWidgets){
        if(df->isDelete->isChecked()){
            QFileInfo fileInfo(df->name);
            space += fileInfo.size(); //? check this qfileinfo takes time
        }
    }

    return space;
}

QString DupStatsWidget::toHTML()
{
    QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-size:12pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">Freeable space(selected files)</span>: </p><p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:48pt;\">%1 </span><span style=\" font-size:16pt;\">%2</span></p><p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt;\">%3 </span><span style=\" font-size:16pt;\">Bytes</span></p><p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p><p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt;\">%4 </span>files;<span style=\" font-size:20pt;\"> </span> <span style=\" font-size:20pt;\">%5 </span>Selected<br /><br /></p></body></html>";

    qint64 fs = freeableSpace();

    QStringList ffs = formatFileSize(fs);

    html = html.arg(ffs[0],ffs[1], qstr(fs), qstr(filesCount()), qstr(selectedFilesCount()));

    return html;
}

void DupStatsWidget::displayStats()
{
    label->setText(toHTML());
}

void DupStatsWidget::refresh(vector<DelWidget *> *dupWidgets)
{
    set(dupWidgets);

    displayStats();
}
