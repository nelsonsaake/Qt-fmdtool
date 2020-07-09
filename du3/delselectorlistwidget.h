#ifndef DUPLICATESLISTVIEWHANDLER_H
#define DUPLICATESLISTVIEWHANDLER_H

#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QtCore>
#include <vector>

using namespace std;

struct DelWidget {
   DelWidget(QString name, QLabel *label, QCheckBox *isDelete)
       : name(name), label(label), isDelete(isDelete) {}

   QString name;
   QLabel *label;
   QCheckBox *isDelete;
};

struct DelFile {
  QString name;
  bool isDelete;
};

struct DelDupSet {
    vector<DelFile> vdf;
};


class DelSelectorListWidget : public QObject
{
    Q_OBJECT

public:
    DelSelectorListWidget(QVBoxLayout *vl, vector<DelDupSet> delDupSetList);

    ~DelSelectorListWidget();

    QCheckBox *addCheckbox(bool isChecked, QHBoxLayout *hl);

    QLabel *addLabel(QString name, QHBoxLayout *hl);

    void addDelDupSetToView(DelDupSet dupSet);

    void addDelDupSetListToView();

    void addToViewIAT(); // IAT =  In Another Thread

    QFrame *line();

    vector<DelWidget *> *getDelListWidget();

    void deleteChildrenWidgets();

    void deleteLines();

    void deleteLayouts();

    QStringList getDelList();

    void clear();

signals:
    void listChanged(vector<DelWidget*> *delWidgets);

protected slots:
    void showFilePropts(QString file);

    void checkBoxStateChanged();
    
private:
    QVBoxLayout *vl;

    vector<DelWidget*> delWidgets;

    vector<DelDupSet> delDupSetList;

    vector<QWidget*> children;

    vector<QFrame*> lines;

    vector<QLayout*> layouts;
};

#endif // DUPLICATESLISTVIEWHANDLER_H
