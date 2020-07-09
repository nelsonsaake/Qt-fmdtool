#include "fileProperties.h"


struct Id3v1Tag
{
    QString tag;
    QString title;
    QString artist;
    QString album;
    QString year;
    QString comment;
    QString genre;
};

vector <string> genreTbl
{ "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative", "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave", "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave", "Psychadelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", " "};

QString genre (int i = 0)
{
    if(i < 0 )return  "";
    int index = i%genreTbl.size();
    return qstr(genreTbl[index]);
}

Id3v1Tag getId3v1Tag (string &fileName)
{
    Id3v1Tag tag;
    ifstream ifs {fileName};
    if(!ifs) error("open file fail.");
    ifs.seekg(-128,ios::end); // start reading at the last but 128th byte

    //?? merge-able with addId3v1Tag()
    tag.tag = next(ifs,3);
    if(tag.tag!="TAG") error("-id3v1");

    tag.title = next(ifs,30);
    tag.artist = next(ifs,30);
    tag.album = next(ifs,30);
    tag.year = next(ifs,4);
    tag.comment = next(ifs,30);
    tag.genre = genre(nextInt(ifs,1));

    return tag;
}

void FilePropts::addId3v1Tag ()
{
    trim(fileName);
    Id3v1Tag x;

    try{x = getId3v1Tag(fileName);}
    catch(...){return;}

    add({"TAG","ID3v1"});
    add({"Title",x.title });
    add({"Artist",x.artist });
    add({"Album",x.album });
    add({"Speed",x.year });
    add({"Comment",x.comment });
    add({"Genre",x.genre });

    return;
}

