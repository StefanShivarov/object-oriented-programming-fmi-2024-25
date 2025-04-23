#pragma once
#include "MyString.h"
class StringView
{
	const char* begin;
	const char* end;

public:

	StringView(const char* _begin, const char* _end);
	StringView(const char* str);
	StringView(const MyString& str);

	size_t length() const;
	const char operator[](size_t index) const;

	StringView substr(size_t from, size_t index);

	friend std::ostream& operator<<(std::ostream& os, const StringView& st);



};

