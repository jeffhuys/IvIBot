#include "task_display.h"

rom char *WelcomeLine1 = "- Running BOT - ";
rom char *WelcomeLine2 = "- Maze        - ";

OST_QUEUE queue;
OST_MSG buffer[10];

void Task_Display(void) {
    OST_MSG msg;
    char *str;

    XLCDInit(); // initialize the LCD module
    XLCDClear();
    XLCDPutRomString(WelcomeLine1); // Hello world
    XLCDL2home(); // home but no cursor
    XLCDPutRomString(WelcomeLine2);

    OS_Queue_Create(queue, buffer, 10);

    for (;;) {
        OS_Queue_Wait(queue, msg); // Wait for message and store it into msg
        str = msg;
        XLCDL1home(); // home but no cursor
        XLCDPutRomString((rom char*) str);

        OS_Queue_Wait(queue, msg); // Wait for message and store it into msg
        str = msg;
        XLCDL2home(); // home but no cursor
        XLCDPutRomString((rom char*) str);
    }
}

