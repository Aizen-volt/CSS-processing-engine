#include <iostream>
#include "DoublyLinkedList.h"
#include "ParseCSS.h"
#include "ParseCommand.h"
#include "InputMode.h"

#define CSS_MODE 0
#define COMMANDS_MODE 1
#define READ_SELECTORS 0
#define READ_ATTRIBUTES_NAME 1
#define READ_ATTRIBUTES_VALUE 2


void GetInput(DoublyLinkedList& mainList) {
    
    InputMode inputMode = { CSS_MODE, READ_SELECTORS, 0, 0 };

    String input;
    char c = '\0';
    while (true) {
        while (true) {
            c = getchar();
            if (c == '\n')
                break;
            if (c == EOF)
                return;
            input.PushBack(c);
        }
        if (inputMode.parseMode == CSS_MODE)
            ParseCSS(mainList, input, &inputMode);
        else
            ParseCommand(mainList, input, &inputMode);
        input.Clear();
    }
}


int main()
{
    DoublyLinkedList mainList;
    mainList.AddNewNode();

    GetInput(mainList);

    return 0;
}