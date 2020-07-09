#ifndef FILE_PROPERTIES_H
#define FILE_PROPERTIES_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "duplicatefinder/globals.h"

using namespace std;

struct Field
{
    QString name;
    QString value;

    Field (QString n="", QString v="")
        : name(n),
          value(v) {
    }
};

bool operator != (Field f1,Field f2);
bool operator == (Field f1,Field f2);

struct FilePropts
{
    FilePropts();

    bool isEmpty();
    void add(const Field &f);
    QString get(const QString &sp) const;

    void addExtTag();
    void addId3v2Tag();
    void addId3v1Tag();
    void setFile();

    string summary;
    string fileName;
    vector <Field> list;
};

FilePropts getFilePropts (string fileName);
bool operator == (FilePropts f1, FilePropts f2);

#endif // FILE_PROPERTIES_H

