#include "lineinteperter.h"
#include "history.h"


int main() {

    /*
     * find-apt -MaxPrice 1500000
     add-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 09 16
     add-apt "Dizengoff 1 Tel Aviv" 3000000 4 28 09 16
     add-apt "Dizengoff 2 Tel Aviv" 1000000 4 28 09 16
     add-apt "Dizengoff 3 Tel Aviv" 4000000 4 28 09 16
     find-apt -Date 290916 -s
     * find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s
     */
    History hist;
    ApartmentTable *db = NULL;
    db = initialProgramState(&hist);
    start(db, &hist);
    return 0;
}