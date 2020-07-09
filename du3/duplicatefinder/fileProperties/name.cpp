#include "id3v2.h"

vector <string> frameIdTbl {
    "AENC", "APIC", "COMM", "COMR", "ENCR", "EQUA", "ETCO",
    "GEOB", "GRID", "IPLS", "LINK", "MCDI", "MLLT", "OWNE",
    "PRIV", "PCNT", "POPM", "POSS", "RBUF", "RVAD", "RVRB",
    "SYLT", "SYTC", "TALB", "TBPM", "TCOM", "TCON", "TCOP",
    "TDAT", "TDLY", "TENC", "TEXT", "TFLT", "TIME", "TIT1",
    "TIT2", "TIT3", "TKEY", "TLAN", "TLEN", "TMED", "TOAL",
    "TOFN", "TOLY", "TOPE", "TORY", "TOWN", "TPE1", "TPE2",
    "TPE3", "TPE4", "TPOS", "TPUB", "TRCK", "TRDA", "TRSN",
    "TRSO", "TSIZ", "TSRC", "TSSE", "TYER", "TXXX", "UFID",
    "USER", "USLT", "WCOM", "WCOP", "WOAF", "WOAR", "WOAS",
    "WORS", "WPAY", "WPUB", "WXXX"
};

vector <string> frameTbl {
    "Audio encryption", "Attached picture", "Comments",
    "Commercial ", "Encryption method registration",
    "Equalization", "Event timing codes",
    "General encapsulated object",
    "Group identification registration",
    "Involved people list", "Linked information",
    "Music CD identifier", "MPEG location lookup table",
    "Ownership ", "Private ", "Play counter",
    "Popularimeter", "Position synchronisation",
    "Recommended buffer size", "Relative volume adjustment",
    "Reverb", "text",
    "Synchronized tempo codes", "Album",
    "BPM (beats per minute)", "Composer", "Content type",
    "Copyright message", "Date", "Playlist delay",
    "Encoded by", "Lyricist", "File type",
    "Time", "Content group description",
    "Title",
    "Subtitle", "Initial key",
    "Language(s)", "Length", "Media type",
    "Original album",
    "Original filename",
    "Original lyricist(s)",
    "Original artist(s)",
    "Original release year", "Licensee",
    "Artist",
    "Band",
    "Conductor",
    "Interpreted, remixed, or otherwise modified by",
    "Part of a set", "Publisher",
    "Track number", "Recording dates",
    "Internet radio station name",
    "Internet radio station owner", "Size",
    "I S R C ",
    "Software/Hardware and settings used for encoding",
    "Year",
    "User add text",
    "Unique file identifier",
    "Terms of use",
    "Unsychronized lyric",
    "Commercial information",
    "Copyright",
    "Official audio file webpage",
    "Official artist",
    "Official audio source webpage",
    "Official internet radio station homepage",
    "Payment",
    "Publishers official webpage",
    "User defined URL link "
};

string findName (const string &id)
{
    // assuming that the each frameId has an corresponding frame name, both of the same index
    // we find the index of the id given(in frameIdTbl)
    // we use the index to get the frame name(from frameTbl) which we return
    // if the id is not in the table we return IUK
    // IUK : id unknown

    for(unsigned int i=0; i < frameIdTbl.size(); i++)
        if(id==frameIdTbl[i]) return frameTbl[i];
    return "IUK";
}
