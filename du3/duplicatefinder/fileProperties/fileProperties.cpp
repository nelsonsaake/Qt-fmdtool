#include "fileProperties.h"

FilePropts::FilePropts()
    : summary(""),
      fileName(""),
      list(vector<Field>())
{}

bool FilePropts::isEmpty()
{
    return false;
    // ? not fully dev
    return true;
}

void FilePropts::add(const Field &f)
{
    list.push_back(f);
}

QString FilePropts::get(const QString &sp)const
{
    // sp : search property
    // qs : QString
    // return the value of qs
    // if qs does not exist it throws an exception
    // exception type runtime_error

    QString qs=sp.toLower();
    for(const Field &f: list)
    {
        QString pn=f.name; // pn : property name
        if(pn.toLower()==qs) return f.value;
    }

   error("property not found.");
   return "";
}


bool operator == (Field f1, Field f2)
{
    return (f1.name == f2.name) && (f1.value == f2.value);
}

bool operator != (Field f1, Field f2)
{
    return !(f1 == f2);
}


FilePropts getFilePropts (string fileName)
{
    FilePropts filePropts;
    filePropts.fileName=trim(fileName);

    filePropts.setFile();
    filePropts.addId3v2Tag();
    filePropts.addId3v1Tag();

    return filePropts;
}

bool operator == (FilePropts f1, FilePropts f2)
{
    return (f1.fileName == f2.fileName);
}
