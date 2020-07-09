#ifndef TAG_H
#define TAG_H

#include "duplicatefinder/globals.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "fileProperties.h"

using namespace std;

typedef Field Frame;

struct Tag
{
    int tagSize;
    vector<Frame> frames;
};

struct ReadTag
{
    QString nextS(int len);
    int nextI(int size=4);

    int readFrameLen();
    int readTagLen();
    void readFrame();
    void readFrames();
    void readTag();

    ReadTag(ifstream &ifs, Tag &tag);

    Tag &tag;
    ifstream &ifs;
    int bytesRead=0;
};

string findName (const string &);

#endif // TAG_H

