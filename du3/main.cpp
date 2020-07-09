#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
start finding duplicates - let one finish before the next one starts - done
properties table - done
duplicate set list stats - done
delete list - what to keep - done
after delete stats - done
delete function - done
btn on remove - set alignment to right - done
space the duplicates list - done
clear widget list after delete --- tie the widgets to the delete button, like we did for the remove folder - didn't use suggestion - done


add folder - check redundancies - done not tested


put the displaying duplicate set list in another thread
interrupt the duplicates finding process when the user wants to
check the deleting animation the bin
*latency in the deleting. may set some animation to show that the things are been deleted
when no duplicate is found disable the delete button
put -> codes in function to enchance readerbility
check the part, the delete list goes off the screen, the app freezes for a minute


add gridline to where we add folder
change the delete animation
check the tabs of the tab widget
add some background image
*/
