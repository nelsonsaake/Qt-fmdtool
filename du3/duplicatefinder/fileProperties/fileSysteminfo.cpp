#include "fileProperties.h"
#include <QFileInfo>
#include <QDateTime>

QString formatSize (int in)
{
    string out = to_string(in);
    out += " bytes";
    return qstr(out);
}

void FilePropts::setFile()
{
    QFileInfo x (fileName.c_str());
    if(!x.exists()) return;

    add({"TAG","File System properties"});
    add({"Name", x.fileName()});
    add({"Extension", x.suffix()});
    add({"Path", x.path()});
    add({"Size", formatSize(x.size())});
    add({"Created", x.birthTime().toString()});
    add({"Last modified", x.lastModified().toString()});
    add({"Last Read", x.lastRead().toString()});
    add({"Owner", x.owner()});
    add({"Hidden", (x.isHidden())?"Yes" : "No"});
    add({"Absolute", (x.isAbsolute())?"Yes" : "No"});
    add({"Writable", (x.isWritable())?"Yes" : "No"});
    add({"Readable", (x.isReadable())?"Yes" : "No"});
    return;
}
