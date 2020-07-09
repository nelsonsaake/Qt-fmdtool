#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <stdexcept>
#include <thread>
#include <sstream>
#include <QtCore>


using namespace std;


QString qstr (qint64 d);

QString qstrd (double i);

QString qstr (string str);

string str (QString qstr);


int nextInt(istream &is, int len);

QString next (istream &is, int len);

QString next (istream &is, char delim='\n');

QString next (istream &is, int len, char delim);


string trim(string &s);

QString trim(QString s);


void error (string mg);

bool isalnum(QString val);

QString editS1(QString val);

ostream &operator <<(ostream& os, const QString &str);



double precision_2(double val);

QStringList formatFileSize(qint64 m);

#endif // GLOBALS_H
