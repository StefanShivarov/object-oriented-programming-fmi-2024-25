#include "StringView.h"

StringView::StringView(const char* _begin, const char* _end) : begin(_begin), end(_end)
{
	
}

StringView::StringView(const char* str):begin(str),end(str + strlen(str))
{

}

StringView::StringView(const MyString& str) : StringView(str.c_str())
{

}

size_t StringView::length() const
{
	return end-begin;
}

const char StringView::operator[](size_t index) const
{
	if (begin + index > end) {
		throw std::length_error("Invalid index");
	}
	return begin[index];
}

StringView StringView::substr(size_t from, size_t count)
{
	if (begin + from + count >= end) {
		throw std::length_error("Invalid from or index");
	}
	return StringView(begin + from, begin + from + count);
}

std::ostream& operator<<(std::ostream& os, const StringView& st)
{
	const char* iter = st.begin;
	while (iter != st.end) {
		os << *iter;
		iter++;
	}
	return os;
}
