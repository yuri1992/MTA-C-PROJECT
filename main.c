#include "lineinteperter.h"



int main() {
    ApartmentTable *db = NULL;
    db = initialProgramState();
    start(db);
    return 0;
}