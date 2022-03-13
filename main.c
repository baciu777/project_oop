#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main()
{
    run_all_tests();
    Service* serv= init_serv();
    Vector* undoList = createVector(2);
    run(serv, undoList);
    distruge(serv);
    destroyVector(undoList, distruge_rp);
    _CrtDumpMemoryLeaks();
    return 0;

}
