#include "utils/lineinteperter.h"

int main() {
    COMMAND *cmd;
    char str[100] = "find-apt -MinNumRooms 3 -MaxNumRooms 5 -MaxPrice 1750000";
    cmd = commandLineInterperter(str);
    debugCommand(*cmd);

    char str2[100] = "find-apt -MaxPrice 1500000";
    cmd = commandLineInterperter(str2);
    debugCommand(*cmd);

    char str3[100] = "add-apt \"adadasdsaadasd adasdsaas\" 20000 12222 2444 2";
    cmd = commandLineInterperter(str3);
    debugCommand(*cmd);
    return 0;
}