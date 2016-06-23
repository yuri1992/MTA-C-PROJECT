#include "lineinteperter.h"



int main() {

    /*
     * find-apt -MaxPrice 1500000
     * add-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 09 16
     * find-apt -MaxPrice 2000001
     * find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000 -s
     */
    ApartmentTable *db = NULL;
    db = initialProgramState();
    start(db);
    return 0;
}