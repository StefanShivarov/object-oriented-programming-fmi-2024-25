#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <string>
using namespace std;



class Observer {

public:
	virtual void update(const string& msg) = 0;
};
//saving in txt file
//Txt observer
class TxtObserver : public Observer {

	string fileName;
public:
	TxtObserver( const string& fileName) :fileName(fileName) {
	}
	
	void update(const string& msg) override
	{
		ofstream ofs(fileName,ios::app);
		ofs << msg << "\n";
	}
};
//saving in binary file
class BinaryObserver : public Observer {

	string fileName;
public:
	BinaryObserver(const string& fileName) : fileName(fileName) {
	}

	void update(const string& msg) override
	{
		ofstream ofs(fileName, ios::binary | ios::app);
		if (!ofs.is_open()) {
			return; // or throw
		}
		int size = msg.length()+1;
		ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
		ofs.write(msg.c_str(), size);
		
	}
};


//printing in to the console
class ConsoleObserver : public Observer {
public:
	void update(const string& msg) override
	{
		cout << msg << endl;
	}

};

class Client
{
	vector <std::shared_ptr<Observer>> observers;
	int state = 0; // example
public:
	int getState() const {
		return state;
	}
	void setState(int _state) {
		int oldState = state;
		state = _state;
		sendMessage("State has been changed from " + to_string(oldState) + " to" + to_string(state));
	}
	void addObserver(const shared_ptr<Observer>& obj) {
		observers.push_back(obj);
	}
	void removeObserver(const shared_ptr<Observer>& obj) {
		observers.erase(std::remove(observers.begin(), observers.end(), obj), observers.end());
	}

	void sendMessage(const string& msg) {
		for (auto& it : observers) {
			it->update(msg);
		}
	}
};
int main() {
		Client client;
		auto ob1 = std::make_shared<ConsoleObserver>();
		auto ob2 = std::make_shared<TxtObserver>("msg.txt");
		auto ob3 = std::make_shared<BinaryObserver>("msg.dat");
		client.addObserver(ob1);
		client.addObserver(ob2);
		client.addObserver(ob3);
		client.sendMessage("Welcome user!");
		client.sendMessage("Kak si pichaga");
		client.setState(5);
}


