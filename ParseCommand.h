#pragma once
#include "DoublyLinkedList.h"
#include "InputMode.h"

void ParseCommand(DoublyLinkedList& mainList, const String& input, InputMode* inputMode);

void PrintBlocksCount(DoublyLinkedList& mainList);

void SeparateArguments(const String& input, String arguments[]);

void PrintSelector(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument);

void PrintAttribute(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument);

void DeleteSection(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument, InputMode* inputMode);