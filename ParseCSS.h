#pragma once
#include "DoublyLinkedList.h"
#include "InputMode.h"

void ParseCSS(DoublyLinkedList& mainList, String& input, InputMode* inputMode);

void ReadSelectors(DoublyLinkedList& mainList, String& selector, char letter, InputMode* inputMode);

void ReadAttributeName(DoublyLinkedList& mainList, Attribute& attribute, char letter, InputMode* inputMode);

void ReadAttributeValue(DoublyLinkedList& mainList, Attribute& attribute, char letter, InputMode* inputMode);

void DeleteWhiteSpaces(String& string);