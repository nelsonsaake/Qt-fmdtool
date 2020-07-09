#include "globals.h"



template<typename T> char* as_bytes(T& in)
{
    void* addr = &in;	// get the address of the first byte
                        // of memory used to store the object
    return static_cast<char*>(addr); // treat that memory as bytes
}

void removeZeros (string &str)
{
    for(unsigned int i=0; i < str.size(); i++)
        if(str[i]==0)str.erase(i,1);
}

void badIO(istream &is)
{
    if(is.bad()) error("bad istream");
    if(is.fail()) is.clear();
}



QString yesNo (bool b)
{
    // returns yes if b is true
    // else return no

    return (b)? "yes":"no";
}

QString qstr (qint64 i)
{
    return qstr(to_string(i));
}

QString qstrd (double d)
{
    ostringstream oss;
    oss << d;
    return oss.str().c_str();
}

QString qstr (string str)
{
    return str.c_str();
}

string str (QString qstr)
{
    return qstr.toStdString();
}



string trim(string &s)
{
    // remove all '\0' characters
    // trim remove all white spaces at both ends

    removeZeros(s);
    s=str(qstr(s).trimmed());
    return s;
}

QString trim(QString qs)
{
    string s{str(qs)};
    return qstr(trim(s));
}



int nextInt(istream &is, int len)
{
    badIO(is);
    if(is.eof())error("ifs empty");

    if(len < 1 || len > 4) error("bad len,nextInt()");
    int out = 0;
    is.read(as_bytes(out), len);
    return out;
}

QString next(istream &is, int len)
{
    badIO(is);
    if(is.eof())error("ifs empty");
    else if(len<0)error("bad len, next()");

    string line="";
    char ch=0;
    for(int i=0; (i<len)&&is.get(ch); i++) line+=ch;
    return qstr(trim(line));
}

QString next(istream &is, char delim)
{
    badIO(is);
    if(is.eof())error("ifs empty");

    string line="";
    char ch=0;
    while(is.get(ch)&&ch!=delim) line+=ch;

    return qstr(trim(line));
}

QString next(istream &is, int len, char delim)
{
    // we read from is len characters into line considering delim

    badIO(is);
    if(is.eof())error("ifs empty");
    else if(len<0)error("bad len, next()");

    string line="";
    char ch=0;
    for(int i=0; is.get(ch)&&(ch!=delim)&&(i<len); i++)
        line+=ch;

    return qstr(trim(line));
}



void error (string mg)
{
    throw(runtime_error{mg});
}

bool isalnum(QString val)
{
    for(char ch:str(val))
        if(!isalnum(ch)) return false;

    return true;
}

QString editS1(QString val)
{
    // we remove all punctuation
    // except those defined as "alsoAccepts"

    string in=str(trim(val));
    string out="";
    string alsoAccepts="'/-().,+*^%$#@\"_|{}[]\\~`!=";

    for(char ch:in) // for each char in "in"
    {
        if(isalnum(ch)) out+=ch; // add if alphabet || number
        else for(char ch2:alsoAccepts) if(ch==ch2)out+=ch; // add if !alnum but an alsoAccepts
    }

    return qstr(out);
}

ostream &operator <<(ostream &os, const QString &val)
{
    return os<<str(val);
}



double precision_2(double val)
{
    return int(val*100)/double(100);
}

QStringList formatFileSize(qint64 m)
{
    const double kilo = pow(10,3);
    const double mega = pow(10,6);
    const double giga = pow(10,9);
    const double tera = pow(10,12);

    double size;
    QString unit;

    if(m > tera){
        size = m/tera;
        unit = "tera bytes";
    }
    else if(m > giga){
        size = m/giga;
        unit = "giga bytes";
    }
    else if(m > mega){
        size = m/mega;
        unit = "mega bytes";
    }
    else if(m > kilo){
        size = m/kilo;
        unit = "kilo bytes";
    }

    return {qstrd(precision_2(size)), unit};
}

