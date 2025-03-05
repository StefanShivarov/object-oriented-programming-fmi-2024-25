#include <iostream>
#include <fstream>
using std::endl;
using std::cout;
using std::cin;
struct Movie {
	char title[50];
	uint16_t year;
};
void saveMovies(const char* fileName, const Movie* movie, int size) {
	uint16_t arr[2] = { 4,1 };
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		return;
	}
	ofs.write((const char*)arr, sizeof(arr));
	ofs.write((const char*)movie, size * sizeof(Movie));
}
Movie* readMovies(const char* filename, int& size) {
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open()) {
		return nullptr;
	}
	size = 2;
	uint16_t* arr = new uint16_t[size];
	ifs.read((char*)arr, size * sizeof(arr[0]));
	Movie* movies = new Movie[size];
	for (int i = 0; i < size; i++) {
		// vinagi pochvame ot nachaloto i namirame tochnoto MOVIE!!!
		ifs.seekg(size * sizeof(arr[0]) + (arr[i] - 1) * sizeof(Movie),std::ios::beg);
		ifs.read((char*)&movies[i], sizeof(Movie));
	}
	delete[] arr;
	return movies;
}
int main() {
	Movie movies[4] = {
		{"Avengers Endgame",2019},
		{"Avengers Infinity War",2017},
		{"Star Wars",1999},
		{"The Hobbit",2018}
	};
	saveMovies("movie.dat", movies, 4);
	int size = 0;
	Movie* readedMovies = readMovies("movie.dat", size);
	for (int i = 0; i < size; i++) {
		cout << readedMovies[i].title << " " << readedMovies[i].year << endl;
	}

	delete[] readedMovies;

}
