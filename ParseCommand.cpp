#include "ParseCommand.h"
#include "ParseCSS.h"

#define CSS_MODE 0
#define COMMANDS_MODE 1


void ParseCommand(DoublyLinkedList& mainList, const String& input, InputMode* inputMode) {

	if (input == "****") {
		inputMode->parseMode = CSS_MODE;
		return;
	}

	if (input == "?") {
		PrintBlocksCount(mainList);
		return;
	}

	//only three-argument commands left
	String arguments[3];
	SeparateArguments(input, arguments);

	switch (arguments[1][0])
	{
	case 'S':
		PrintSelector(mainList, arguments[0], arguments[2]);
		break;
	case 'A':
		PrintAttribute(mainList, arguments[0], arguments[2]);
		break;
	case 'E':
		mainList.PrintLastAttribute(arguments[0], arguments[2]);
		break;
	case 'D':
		DeleteSection(mainList, arguments[0], arguments[2], inputMode);
		break;
	default:
		break;
	}
}


void PrintBlocksCount(DoublyLinkedList& mainList) {
	cout << "? == " << mainList.PrintBlocksCount() - 1 << "\n";
}


void SeparateArguments(const String& input, String arguments[]) {
	int i = 0;
	for (int j = 0; j < 3; j++) {
		while (input[i] != ',') {
			if (input[i] == '\0')
				break;
			arguments[j].PushBack(input[i]);
			i++;
		}
		i++;
	}
}


void PrintSelector(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument) {
	if (isdigit(firstArgument[0])) {
		int sectionNumber = atoi(firstArgument.GetArray()) - 1 + mainList.blocksDeleted;

		int nodeNumber = sectionNumber / BLOCKS_IN_ARRAY;
		int blockNumber = sectionNumber % BLOCKS_IN_ARRAY;

		if (nodeNumber >= mainList.doublyLinkedListSize || blockNumber >= mainList[nodeNumber]->blocksInUse)
			return;

		if (mainList[nodeNumber]->blocks[blockNumber].deleted)
			return;

		if (secondArgument[0] == '?') {
			if ((nodeNumber >= mainList.doublyLinkedListSize || blockNumber >= mainList[nodeNumber]->blocksInUse - 1) && (sectionNumber + 1) % BLOCKS_IN_ARRAY != 0)
				return;
			cout << firstArgument << ",S,? == " << mainList[nodeNumber]->blocks[blockNumber].selectorsCount << "\n";
			return;
		}
		int selectorNumber = atoi(secondArgument.GetArray()) - 1;
		if (selectorNumber < mainList[nodeNumber]->blocks[blockNumber].selectorsCount) {
			cout << firstArgument << ",S," << secondArgument << " == " << mainList[nodeNumber]->blocks[blockNumber].selectors[selectorNumber]->data << "\n";
		}
		return;
	}
	mainList.CountSelector(firstArgument);
}


void PrintAttribute(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument) {
	if (isdigit(firstArgument[0])) {
		int sectionNumber = atoi(firstArgument.GetArray()) - 1 + mainList.blocksDeleted;

		int nodeNumber = sectionNumber / BLOCKS_IN_ARRAY;
		int blockNumber = sectionNumber % BLOCKS_IN_ARRAY;

		if (nodeNumber >= mainList.doublyLinkedListSize || blockNumber >= mainList[nodeNumber]->blocksInUse)
			return;

		if (mainList[nodeNumber]->blocks[blockNumber].deleted)
			return;

		if (secondArgument[0] == '?') {
			/*if ((nodeNumber >= mainList.doublyLinkedListSize || blockNumber >= mainList[nodeNumber]->blocksInUse - 1) && (sectionNumber + 1) % BLOCKS_IN_ARRAY != 0)
				return;*/
			cout << firstArgument << ",A,? == " << mainList[nodeNumber]->blocks[blockNumber].attributesCount << "\n";
			return;
		}

		mainList.PrintAttValue(firstArgument, secondArgument, nodeNumber, blockNumber);
		return;
	}
	mainList.CountAttribute(firstArgument);
}


void DeleteSection(DoublyLinkedList& mainList, const String& firstArgument, const String& secondArgument, InputMode* inputMode) {
	int sectionNumber = atoi(firstArgument.GetArray()) - 1 + mainList.blocksDeleted;

	int nodeNumber = sectionNumber / BLOCKS_IN_ARRAY;
	int blockNumber = sectionNumber % BLOCKS_IN_ARRAY;

	if (nodeNumber >= mainList.doublyLinkedListSize || blockNumber >= mainList[nodeNumber]->blocksInUse)
		return;

	if (mainList[nodeNumber]->blocks[blockNumber].deleted)
		return;

	if (secondArgument[0] == '*') {
		mainList.RemoveBlock(firstArgument, nodeNumber, blockNumber, true);
		return;
	}
	mainList.RemoveAttribute(firstArgument, secondArgument, nodeNumber, blockNumber);
	if (mainList[nodeNumber]->blocks[blockNumber].attributesCount == 0)
		mainList.RemoveBlock(firstArgument, nodeNumber, blockNumber, false);
}