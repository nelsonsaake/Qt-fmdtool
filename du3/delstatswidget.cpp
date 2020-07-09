#include "delsatswidget.h"
#include "duplicatefinder/globals.h"

DelStatsWidget::DelStatsWidget(QLabel *label)
    : label(label)
{

}

void DelStatsWidget::setClearedSpace(qint64 clearedSpace)
{
    this->clearedSpace = clearedSpace;
}

QString DelStatsWidget::toHTML()
{
    QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\"font-size:12pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You have cleared:</p><p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:48pt;\">%1 </span><span style=\" font-size:16pt;\">%2 </span></p><p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt;\">%3 </span><span style=\" font-size:16pt;\">Bytes</span><br /></p></body></html>";

    QStringList cs = formatFileSize(clearedSpace);

    html = html.arg(cs[0], cs[1], qstr(clearedSpace));

    return html;
}

void DelStatsWidget::displayStats()
{
    label->setText(toHTML());
}

