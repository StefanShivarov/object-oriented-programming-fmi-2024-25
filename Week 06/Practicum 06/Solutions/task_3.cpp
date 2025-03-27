#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
// TRQBVA S RAZDELNA
class Game
{
private:
	char* title = nullptr;
	double price = 0;
	bool isAvailable = false;
	void setTitle(const char* title) {
		if (!title || this->title == title) return;
		delete[] this->title;
		this->title = new char[strlen(title) + 1];
		strncpy(this->title, title, strlen(title));
		this->title[strlen(title)] = '\0';

	}
	void setPrice(double price) {
		if (price < 0) return;
		this->price = price;

	}

	void setIsAvailable(bool isAvailable) {
		this->isAvailable = isAvailable;

	}

	void copyFrom(const Game& other) {

		title = new char[strlen(other.title) + 1];
		strncpy(title, other.title, strlen(other.title));
		title[strlen(other.title)] = '\0';

		price = other.price;
		isAvailable = other.isAvailable;

	}

	void free() {
		delete[] title;
		title = nullptr;
		price = 0;
		isAvailable = false;
	}

public:

	Game() = default;

	Game(const Game& other) {
		copyFrom(other);
	}

	Game(const char* title, double price, bool isAvailable) {
		setTitle(title);
		setPrice(price);
		setIsAvailable(isAvailable);
	}

	Game& operator = (const Game& other) {
		if (this != &other) 
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	~Game() {
		free();
	}

	bool isFree() const {
		return price == 0;
	}

	void print() const {
		std::cout << title << " ";
		std::cout << price << " ";
		
		if(isAvailable) std::cout << "is available" << std::endl;
		else std::cout << "is not available" << std::endl;
	}

	const char* getTitle() const {
		return title;
	}

	double getPrice() const {
		return price;
	}

	bool isGameAvailable() const {
		return isAvailable;
	}

	void writeGameToFile(std::ofstream& file){

		int sizeOfTitle = strlen(title);

		file.write((const char*)&sizeOfTitle, sizeof(int));
		file.write((const char*)title, sizeOfTitle);

		file.write((const char*)&price, sizeof(double));
		file.write((const char*)&isAvailable, sizeof(bool));

	}

	void readGameFromFile(std::ifstream& file){

		int sizeOfTitle = 0;

		file.read((char*)&sizeOfTitle, sizeof(int));
		delete[] title;
		title = new char[sizeOfTitle + 1];
		file.read((char*)title, sizeOfTitle);
		title[sizeOfTitle] = '\0';

		file.read((char*)&price, sizeof(double));
		file.read((char*)&isAvailable, sizeof(bool));

	}

};

class GamePlatform 
{
private:

	Game* games = nullptr;
	int countOfGames = 0;
	int capacity = 8;

	void copyFrom(const GamePlatform& other) 
	{
		games = new Game[other.capacity];
		capacity = other.capacity;
		countOfGames = other.countOfGames;

		for (int i = 0; i < countOfGames; i++){
			games[i] = other.games[i];
		}

	}

	void free() 
	{

		delete[] games;
		games = nullptr;
		countOfGames = 0;
		capacity = 8;

	}

	void resize(int newCapacity) 
	{
		if (newCapacity <= capacity) return;
		Game* newGames = new Game[newCapacity];
		for (int i = 0; i < countOfGames; i++){
			newGames[i] = games[i];
		}

		delete[] games;
		games = newGames;
		capacity = newCapacity;
	}

public:

	GamePlatform() {
		countOfGames = 0;
		capacity = 8;
		games = new Game[capacity];

	}

	GamePlatform(const GamePlatform& other) {
		copyFrom(other);

	}

	GamePlatform& operator = (const GamePlatform& other) 
	{
		if (this != &other) 
		{
			free();
			copyFrom(other);
		}
		return *this;

	}
	~GamePlatform() {
		free();
	}

	void addGame(const Game& game) {
		if (countOfGames == capacity) resize(capacity * 2);
		games[countOfGames] = game;
		countOfGames += 1;

	}

	void removeGame(const Game& game){
		for (int i = 0; i < countOfGames; i++){
			if(!strcmp(games[i].getTitle(), game.getTitle()) &&
				games[i].getPrice() == game.getPrice() &&
				games[i].isGameAvailable() == game.isGameAvailable())
			{

				std::swap(games[i], games[countOfGames - 1]);
				countOfGames -= 1;
				break;

			}

		}

	}

	void removeGame(int index) 
	{
		if (index < 0 || index >= countOfGames) throw std::logic_error("Error");
		Game gameToBeRemoved = games[index];
		removeGame(gameToBeRemoved);

	}

	void printGames() const {

		for (int i = 0; i < countOfGames; i++){
			games[i].print();

		}

		std::cout << std::endl;

	}

	void printGameByIndex(int index) const{
		if (index < 0 || index >= countOfGames) throw std::logic_error("Error");
		games[index].print();

	}

	void printCheapestGame() const {
		int index = 0;
		double currentPrice = games[0].getPrice();
		for (int i = 1; i < countOfGames; i++)
		{

			if (games[i].getPrice() < currentPrice) 
			{
				index = i;
				currentPrice = games[i].getPrice();
			}

		}
		printGameByIndex(index);

	}

	void printMostExpensiveGame() const{
		int index = 0;
		double currentPrice = games[0].getPrice();

		for (int i = 1; i < countOfGames; i++)
		{

			if (games[i].getPrice() > currentPrice)
			{
				index = i;
				currentPrice = games[i].getPrice();
			}

		}
		printGameByIndex(index);

	}

	void printAllFreeGames() const 
	{
		for (int i = 0; i < countOfGames; i++){

			if (games[i].isFree()) printGameByIndex(i);

		}

	}

	void writeToFile(const char* fileName) 
	{
		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;
		file.write((const char*)&countOfGames, sizeof(int));
		for (int i = 0; i < countOfGames; i++){
			games[i].writeGameToFile(file);
		}
		file.close();

	}

	void readFromFile(const char* fileName){

		free();
		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) return;

		file.read((char*)&countOfGames, sizeof(int));
		games = new Game[countOfGames];
		capacity = countOfGames;

		for (int i = 0; i < countOfGames; i++){
			games[i].readGameFromFile(file);
		}
		file.close();

	}

};

int main()
{

	Game game1("Game1", 10, true);
	Game game2("Game2", 16, true);
	Game game3("Game3", 101, false);
	Game game4("Game4", 0, true);
	Game game5("Game5", 76, true);
	Game game6("Game6", 5, true);
	Game game7("Game7", 33, false);
	Game game8("Game8", 45, false);
	Game game9("Game9", 0, true);
	Game game10("Game10", 56, true);

	GamePlatform gp;
	gp.addGame(game1);
	gp.addGame(game2);
	gp.addGame(game3);
	gp.addGame(game4);
	gp.addGame(game5);
	gp.addGame(game6);
	gp.addGame(game7);
	gp.addGame(game8);
	gp.addGame(game9);
	gp.addGame(game10);

	gp.printGames();
	gp.printGameByIndex(7);
	gp.printAllFreeGames();
	gp.printMostExpensiveGame();
	gp.printCheapestGame();

	std::cout << std::endl;

	gp.removeGame(game1);
	gp.removeGame(3);
	gp.printGames();

	gp.writeToFile("result.dat");

	GamePlatform newGp;
	newGp.readFromFile("result.dat");
	newGp.printGames();

	return 0;

}
