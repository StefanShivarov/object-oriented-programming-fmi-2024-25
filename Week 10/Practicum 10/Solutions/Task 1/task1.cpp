#include <iostream>
#include <fstream>
#include "MyString.h"
// NAPRAVETE GO S RAZDELNA!!!!!
class Ticket
{
private:

	MyString str;
	double price = 0;

public:

	Ticket(const MyString& str, double price) : str(str), price(price) {}

	double getPrice() const
	{

		return price;

	}

	const MyString& getStr() const
	{

		return str;

	}
};

class StudentTicket : public Ticket
{
public:

	StudentTicket(const MyString& str, double price) : Ticket(str, price / 2) {}

	void print() const
	{
		std::cout << getStr();
		std::cout << getPrice() << std::endl;

	}

};

class GroupTicket : public Ticket
{
public:

	GroupTicket(const MyString& str, double price) : Ticket(str, 0.8 * price) {}

	void print() const
	{

		std::cout << getStr();
		std::cout << getPrice() << std::endl;

	}
};

int main()
{
	StudentTicket st("Person1", 10);
	GroupTicket gt("GroupTicket", 12);

	st.print();
	gt.print();

	return 0;

}