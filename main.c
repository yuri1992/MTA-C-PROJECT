#include "lineinteperter.h"
#include "history.h"


int main() {

    /*
     * Apartment Manager Program
     * First Year 2016, Advance Computer Since (c)
     * 316961101 - Yuri Ritvin
     * 302527916 - Ronny Tzur
     */
    History hist;
    ApartmentTable *db = NULL;
    db = initialProgramState(&hist);
    start(db, &hist);
    return 0;
}