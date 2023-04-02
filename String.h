#pragma once
#include <iostream>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

class String {
private:
	char* array;
	int size;
public:
	String() {
		size = 1;
		array = new char[size];
		array[0] = '\0';
	}


	String(const char* source) {
		if (source == nullptr) {
			size = 1;
			array = new char[size];
			array[0] = '\0';
			return;
		}
		size = strlen(source) + 1;
		array = new char[size];
		memcpy(array, source, size);
		array[size - 1] = '\0';
	}


	String(const String& source) {
		size = source.size;
		array = new char[size];
		memcpy(array, source.array, size);
	}


	String(String&& source) {
		size = source.size;
		array = source.array;
		source.array = nullptr;
	}


	~String() {
		delete[] array;
	}


	int GetLength() const {
		return size;
	}


	const char* GetArray() const {
		return array;
	}


	void PushBack(char c) {
		char* temp = new char[size + 1];
		memcpy(temp, array, size);
		temp[size - 1] = c;
		temp[size] = '\0';
		delete[] array;
		array = temp;
		size++;
	}


	void Pop(int index) {
		for (char* i = array + index; i != array + size - 1; i++)
			*i = *(i + 1);
		size--;
	}


	void Clear() {
		delete[] array;
		size = 1;
		array = new char[size];
		array[0] = '\0';
	}


	String& operator=(const String& rightString) {
		if (this == &rightString)
			return *this;
		delete[] array;
		size = rightString.size;
		array = new char[size];
		memcpy(array, rightString.array, size);
		return *this;
	}


	String& operator=(String&& rightString) {
		if (this == &rightString)
			return *this;
		delete[] array;
		size = rightString.size;
		array = rightString.array;
		rightString.array = nullptr;
		rightString.size = 0;
		return *this;
	}


	bool operator==(const char* text) const {
		return !strcmp(array, text);
	}


	bool operator==(String& right) const {
		return !strcmp(array, right.array);
	}

	bool operator==(const String& right) const {
		return !strcmp(array, right.array);
	}


	char operator[](int index) const {
		return array[index];
	}


	friend std::ostream& operator<<(std::ostream& os, const String& string) {
		os << string.array;
		return os;
	}


	friend std::istream& operator>>(std::istream& is, String& string) {
		char* buffer = new char[INPUT_BUFFER_SIZE];
		char temp = -1;
		int i = 0;
		while (temp != '\n') {
			temp = getchar();
			buffer[i] = temp;
			i++;
		}
		buffer[i] = '\0';
		string = String{ buffer };
		delete[] buffer;
		return is;
	}


	friend String operator+(const String& leftString, const String& rightString) {
		int length = leftString.size + rightString.size - 1;
		char* buffer = new char[length];
		memcpy(buffer, leftString.array, leftString.size - 1);
		memcpy(buffer + leftString.size - 1, rightString.array, rightString.size);
		String temp = { buffer };
		temp.size = length;
		delete[] buffer;
		return temp;
	}
};