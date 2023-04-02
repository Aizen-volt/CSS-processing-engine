#include "ParseCSS.h"

#define CSS_MODE 0
#define COMMANDS_MODE 1
#define READ_SELECTORS 0
#define READ_ATTRIBUTES_NAME 1
#define READ_ATTRIBUTES_VALUE 2
#define BLOCK_ENDED 3

void ParseCSS(DoublyLinkedList& mainList, String& input, InputMode* inputMode) {

    DeleteWhiteSpaces(input);

    if (input.GetLength() <= 1)
        return;

    if (input == "????") {
        inputMode->parseMode = COMMANDS_MODE;
        return;
    }

    String selector;
    Attribute attribute;

    int length = input.GetLength();

    for (int i = 0; i < length - 1; i++) {
        switch (inputMode->cssReadMode)
        {
        case READ_SELECTORS:
            ReadSelectors(mainList, selector, input[i], inputMode);
            break;
        case READ_ATTRIBUTES_NAME:
            ReadAttributeName(mainList, attribute, input[i], inputMode);
            break;
        case READ_ATTRIBUTES_VALUE:
            ReadAttributeValue(mainList, attribute, input[i], inputMode);
            break;
        default:
            break;
        }
    }
    if (inputMode->cssReadMode == READ_SELECTORS && selector.GetLength() > 1) {
        DeleteWhiteSpaces(selector);
        mainList.AddSelector(selector, inputMode->currentNode, inputMode->currentBlock);
    }
}


void ReadSelectors(DoublyLinkedList& mainList, String& selector, char letter, InputMode* inputMode) {
    if (letter == ',') {
        DeleteWhiteSpaces(selector);
        mainList.AddSelector(selector, inputMode->currentNode, inputMode->currentBlock);
        selector.Clear();
        return;
    }
    if (letter == '{') {
        if (selector.GetLength() > 1) {
            DeleteWhiteSpaces(selector);
            mainList.AddSelector(selector, inputMode->currentNode, inputMode->currentBlock);
            selector.Clear();
        }
        inputMode->cssReadMode = READ_ATTRIBUTES_NAME;
        return;
    }
    selector.PushBack(letter);
}


void ReadAttributeName(DoublyLinkedList& mainList, Attribute& attribute, char letter, InputMode* inputMode) {
    if (letter == ':') {
        inputMode->cssReadMode = READ_ATTRIBUTES_VALUE;
        return;
    }
    if (letter == '}') {
        if (mainList.AddNewBlock(mainList[inputMode->currentNode])) {
            inputMode->currentNode++;
            inputMode->currentBlock = 0;
        }
        else
            inputMode->currentBlock++;
        inputMode->cssReadMode = READ_SELECTORS;
        return;
    }
    attribute.name.PushBack(letter);
}


void ReadAttributeValue(DoublyLinkedList& mainList, Attribute& attribute, char letter, InputMode* inputMode) {
    if (letter == ';') {
        DeleteWhiteSpaces(attribute.name);
        DeleteWhiteSpaces(attribute.value);
        if (mainList.FindAttribute(attribute, inputMode->currentNode, inputMode->currentBlock) == false)
            mainList.AddAttribute(attribute, inputMode->currentNode, inputMode->currentBlock);
        inputMode->cssReadMode = READ_ATTRIBUTES_NAME;
        attribute.name.Clear();
        attribute.value.Clear();
        return;
    }
    if (letter == '}') {
        if (attribute.name.GetLength() > 1) {
            DeleteWhiteSpaces(attribute.name);
            DeleteWhiteSpaces(attribute.value);
            if (mainList.FindAttribute(attribute, inputMode->currentNode, inputMode->currentBlock) == false)
                mainList.AddAttribute(attribute, inputMode->currentNode, inputMode->currentBlock);
        }

        if (mainList.AddNewBlock(mainList[inputMode->currentNode])) {
            inputMode->currentNode++;
            inputMode->currentBlock = 0;
        }
        else
            inputMode->currentBlock++;
        inputMode->cssReadMode = READ_SELECTORS;
        return;
    }
    attribute.value.PushBack(letter);
}


void DeleteWhiteSpaces(String& string) {
    while (isspace(string[0])) {
        string.Pop(0);
    }
    if (string.GetLength() > 2) {
    int end = string.GetLength() - 2;
    while (isspace(string[end])) {
        string.Pop(end);
        end--;
    }
    }
}