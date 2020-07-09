#include "delselectorlistwidget.h"
#include "fileproptsdialog.h"
#include <thread>

using namespace std;

DelSelectorListWidget::DelSelectorListWidget(QVBoxLayout *vl, vector<DelDupSet> delDupSetList)
    : vl(vl), delDupSetList(delDupSetList)
{
    addDelDupSetListToView();
}

DelSelectorListWidget::~DelSelectorListWidget()
{
    clear();
}

QCheckBox *DelSelectorListWidget::addCheckbox(bool isCheck, QHBoxLayout *hl)
{
    QCheckBox *checkbox = new QCheckBox();

    children.push_back(checkbox);

    checkbox->setChecked(isCheck);

    checkbox->setFixedWidth(20);

    hl->addWidget(checkbox);

    connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged()));

    return checkbox;
}

QLabel *DelSelectorListWidget::addLabel(QString str, QHBoxLayout *hl)
{
    QString link = QString("<a href='%1' style='color: /*silver*/'>%1</a>").arg(str);

    QLabel *label = new QLabel(link);

    // label->setStyleSheet("QLabel{color: silver;} QLabel:hover{color: white;}");

    children.push_back(label);

    QFont f = label->font();

    f.setLetterSpacing(QFont::AbsoluteSpacing,2);

    f.setWordSpacing(5);

    label->setFont(f);

    label->setWordWrap(true);

    hl->addWidget(label);

    connect(label, SIGNAL(linkActivated(QString)), this, SLOT(showFilePropts(QString)));

    return label;
}

void DelSelectorListWidget::addDelDupSetToView(DelDupSet dupSet)
{
    for(DelFile df: dupSet.vdf){

        QHBoxLayout *hl = new QHBoxLayout;

        layouts.push_back(hl);

        QCheckBox *isDelete = addCheckbox(df.isDelete, hl);

        QLabel *label = addLabel(df.name,hl);

        vl->addLayout(hl);

        DelWidget *dfv = new DelWidget(df.name, label, isDelete);

        delWidgets.push_back(dfv);
    }

    vl->addWidget(line());    
}

void DelSelectorListWidget::addDelDupSetListToView()
{
    for(DelDupSet dds: delDupSetList){
        addDelDupSetToView(dds);
    }
}

void DelSelectorListWidget::addToViewIAT()
{
    QEventLoop qel;
    bool isFinished = false;

    std::thread t(
        [&isFinished, &qel, this]{
            addDelDupSetListToView();

            qel.quit();

            isFinished = true;
        }
    );

    if(!isFinished) qel.exec();
    t.join();
}

void DelSelectorListWidget::showFilePropts(QString file)
{
    FileProptsDialog *pd = new FileProptsDialog(file);
    pd->show();
}

void DelSelectorListWidget::checkBoxStateChanged()
{
    emit listChanged(&delWidgets);
}

QFrame *DelSelectorListWidget::line()
{
    QFrame *line = new QFrame();

    lines.push_back(line);

    line->setObjectName(QString::fromUtf8("line"));

    line->setGeometry(QRect(320, 150, 118, 3));

    line->setFrameShape(QFrame::HLine);

    line->setFrameShadow(QFrame::Sunken);

    line->setStyleSheet("background-color: rgb(200,200,200);");

    return line;
}

vector<DelWidget *> *DelSelectorListWidget::getDelListWidget()
{
    return &delWidgets;
}

void DelSelectorListWidget::deleteChildrenWidgets()
{
    for(QWidget *child : children){
        child->deleteLater();
    }

    children.clear();
}

void DelSelectorListWidget::deleteLines()
{
    for(QFrame *line : lines){
        line->deleteLater();
    }

    lines.clear();
}

void DelSelectorListWidget::deleteLayouts()
{
    for(QLayout *layout : layouts){
        layout->deleteLater();
    }

    layouts.clear();
}

QStringList DelSelectorListWidget::getDelList()
{
    QStringList delList;

    for(DelWidget *del: delWidgets){
        if(del->isDelete->isChecked()){
            delList << del->name;
        }
    }

    return delList;
}

void DelSelectorListWidget::clear()
{
    deleteChildrenWidgets();

    deleteLines();

    deleteLayouts();

    delWidgets.clear();
}
