#include "id3v2.h"
#include "duplicatefinder/globals.h"


QString ReadTag::nextS(int len)
{
    if(len<0) error("bad length, next()");
    QString out{next(ifs,int(len))};
    bytesRead+=len;
    return out;
}

int ReadTag::nextI(int size)
{
    int out=nextInt(ifs,size);
    bytesRead+=size;
    return out;
}

int ReadTag::readTagLen()
{
    int out = 0;
    for(int i = 4; i > 0; i--)
    {
        int n=nextI(1);
        n &= 0x7f;
        n <<= (8*(i-1));
        n >>= i-1;

        out |= n;
    }
    tag.tagSize = out;
    bytesRead += 4;
    return out;
}

int ReadTag::readFrameLen()
{
    int out = 0;
    for(int i = 4; i > 0; i--)
    {
        int n=nextI(1);
        n &= 0x7f;
        n <<= (8*(i-1));
       // n >>= i-1;

        out |= n;
    }
    bytesRead += 4;
    return out;
}

void ReadTag::readFrame()
{
    Frame frame;
    QString id=nextS(4);
    if(!isalnum(id)||id.isEmpty()) error("bad frame id, readFrame()");

    frame.name=qstr(findName(str(id)));
    int fLen=readFrameLen();             // frameLen
    nextS(2);                                    // skip 2 chars
    frame.value=nextS(fLen);

    if(id!= "APIC")
        tag.frames.push_back(frame);
}

void ReadTag::readFrames()
{    
    while(tag.tagSize>bytesRead) readFrame();
}

void ReadTag::readTag()
{
    if(nextS(3)!="ID3") error("-id3v2");  // is id3 tag?
    tag.frames.push_back({"TAG","ID3v2"});

    nextS(3); // skip three, ignore data
    readTagLen();
    readFrames();
}

ReadTag::ReadTag(ifstream &ifs, Tag &tag)
    : tag(tag), ifs(ifs)
{
    if(!ifs)error("ifs not good, ReadTag()!");
    readTag();    // compose tag using the file
}

void FilePropts::addId3v2Tag()
{
    Tag tag=Tag();
    try
    {
        ifstream is{fileName};
        ReadTag(is,tag);
    }
    catch(...){}

    for(Frame x:tag.frames) add({x.name, x.value});
    return;
}


