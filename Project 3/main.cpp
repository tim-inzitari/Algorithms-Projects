// Tim Inzitari
// tsi3 4387347
// Algorithms Project 3
// 4/29/2019
#include "SCImage.h"

using namespace std;

int main(int argc, char*argv[])
{
    // Argument stuff
    if (argc < 3)
        cout<< "wrong format! should be \"a.exe HorizontalSeamsToRemove VerticalSeamsToRemove imageToProcess\"";
    else
    {
        int toRemoveVerticalSeam = atoi(argv[1]);
        int toRemoveHorizontalSeam = atoi(argv[2]);
        string dataFile = argv[3];
        // end argument stuff
        // remove .pgm from image

        SCImage image(dataFile);
        image.sC(toRemoveVerticalSeam,toRemoveHorizontalSeam);
        image.outputCarvImage(dataFile.substr(0,dataFile.length()-4));
    }// end arg else
    return 0;
}// end main
