#include <iostream>
#include <fstream>
#include <cstring>
using std::cout;
using std::endl;
using std::cin;


constexpr int MAX_NAME_LENGTH = 50;
constexpr int MAX_FILE_LENGTH = 200;
char filename[MAX_FILE_LENGTH] = "pokemon.dat";
enum class Type {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GHOST,
    FLYING
};
struct Pokemon {
    char name[MAX_NAME_LENGTH] = "";
    Type type = Type::NORMAL;
    unsigned power = 10;
};
bool isValidPokemon(const Pokemon& pokemon)
{
    return !(pokemon.power < 10 || pokemon.power>1000);
}
bool isValidInteger()
{
    if (!cin.fail()) {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(1024, '\n');
        return false;
    }
}
Pokemon createPokemonFromConsole()
{
    Pokemon pokemon;

    cout << "Enter Pokemon Name(1-50 length): " << endl;
    cin >> pokemon.name;
    cout << "Enter Pokemon Type: " << endl;
    cout << "0) - Normal" << endl;
    cout << "1) - Fire" << endl;
    cout << "2) - Water" << endl;
    cout << "3) - Grass" << endl;
    cout << "4) - Electric" << endl;
    cout << "5) - Ghost" << endl;
    cout << "6) - Flying" << endl;

    unsigned choice;
    cin >> choice;
    if (!isValidInteger() || choice > 6)
    {
        cout << "Invalid Choice" << endl;

        return {};
    }
    pokemon.type = (Type)choice;
    cout << "Enter Pokemen Strength: " << endl;
    cin >> pokemon.power;

    if (!isValidPokemon(pokemon))
    {
        cout << "Invalid pokemon" << endl;
        return {};
    }

    return pokemon;
}
unsigned size(std::fstream& file)
{
    //cout << file.bad() << "AND" << file.fail() << "AND" << file.eof()<<endl;
    //file.clear();
    //cout << file.bad() << "AND" << file.fail() << "AND" << file.eof() << endl;
    int currentPos = file.tellg();

    file.seekg(0, std::ios::end);
    unsigned fileSize = file.tellg();
    file.seekg(currentPos);

    return fileSize;
}
unsigned getPokemonCount(std::fstream& file)
{
    unsigned fileSize = size(file);
    return fileSize / sizeof(Pokemon);
}
void savePokemonInFile(std::fstream& file, const Pokemon& pokemon)
{
    //cout << file.tellg() << "LETSSEE" << endl;
    unsigned pokemonCount = getPokemonCount(file);
    file.seekg(pokemonCount * sizeof(Pokemon));
    file.write((const char*)&pokemon, sizeof(pokemon));

}

const char* typeToString(const Type& type)
{
    switch (type)
    {
    case Type::NORMAL: {
        return "Normal";
    }
    case Type::FIRE: {
        return "Fire";
    }
    case Type::WATER: {
        return "Water";
    }
    case Type::GRASS: {
        return "Grass";
    }
    case Type::ELECTRIC: {
        return "Electric";
    }
    case Type::GHOST: {
        return "Ghost";
    }
    case Type::FLYING: {
        return "Flying";
    }
    }
}
void printPokemon(const Pokemon& pokemon)
{
    cout << pokemon.name << " " << typeToString(pokemon.type) << " " << pokemon.power << endl;
}
Pokemon at(std::fstream& in, int index)
{
    Pokemon pokemon;
    unsigned pokemonCount = getPokemonCount(in);
    index--;
    if (index < 0 || index >= pokemonCount)
    {
        cout << "Invalid Index" << endl;
        return {};
    }
    int currentPos = in.tellg();
    in.seekg(sizeof(pokemon) * index);
    in.read((char*)&pokemon, sizeof(pokemon));
    in.seekg(currentPos);
    return pokemon;

}
void swap(std::fstream& file, int i, int j)
{
    Pokemon pokemon1, pokemon2;
    unsigned pokemonCount = getPokemonCount(file);
    i--; // for graphical user interface
    j--; // user will not INPUT '0' as index
    if (pokemonCount == 1)
    {
        return;
    }
    if (i < 0 || i >= pokemonCount || j < 0 || j >= pokemonCount || j == i)
    {
        cout << "Incorrect indexes" << endl;
        return;
    }

    //find and get pokemon on this index
    pokemon1 = at(file, i + 1);
    pokemon2 = at(file, j + 1);
    int startingPosOut = file.tellp();
    //find and write pokemon on this index
    file.seekp(i * sizeof(pokemon2));
    file.write((const char*)&pokemon2, sizeof(pokemon2));

    //find and write pokemon on this index
    file.seekp(j * sizeof(pokemon1));
    file.write((const char*)&pokemon1, sizeof(pokemon1));
    file.seekp(startingPosOut);

}
void selectionSort(std::fstream& file)
{
    //cout << file.fail()<<endl;
    unsigned pokemonCount = getPokemonCount(file);
    // cout << file.fail() << endl;
    if (pokemonCount < 2) {
        return;
    }
    Pokemon poki1, poki2;
    for (int i = 0; i < pokemonCount - 1; i++)
    {
        int minIndex = i;
        poki1 = at(file, minIndex + 1); // for GUI user is working from [1......n], not from [0.....n];
        for (int j = i + 1; j < pokemonCount; j++)
        {
            poki2 = at(file, j + 1);
            if (poki1.power > poki2.power)
            {
                minIndex = j;
                poki1 = at(file, minIndex + 1);
            }
        }
        if (minIndex != i)
        {
            swap(file, minIndex + 1, i + 1);
        }
    }
}
void insert(std::fstream& file)
{

    Pokemon pokemon = createPokemonFromConsole();
    if (strcmp(pokemon.name, "") == 0) {
        return;
    }
    savePokemonInFile(file, pokemon);
    selectionSort(file);
    cout << "Pokemon Sorted and Saved Succesfully" << endl;

}
void printAllPokemons(std::fstream& in)
{
    unsigned pokemonCount = getPokemonCount(in);
    if (pokemonCount < 1)
    {
        cout << "There is no Pokemons to Print!!!" << endl;
        return;
    }
    for (int i = 0; i < pokemonCount; i++)
    {
        Pokemon poki = at(in, i + 1);
        printPokemon(poki);
    }
}
void getPokemonAndPrint(std::fstream& file)
{
    int index;
    cin >> index;
    Pokemon poki = at(file, index);
    if (!(strcmp(poki.name, "") == 0)) // is returned empty Pokemon, if is not print it
    {
        printPokemon(poki);
    }
}

void savePokemon(std::ofstream& out, const Pokemon& poki)
{
    out << poki.name << " " << typeToString(poki.type) << " " << poki.power << endl;
}
Type textToType(const char* text)
{
    if (strcmp(text, "Normal") == 0) {
        return Type::NORMAL;
    }
    if (strcmp(text, "Fire") == 0) {
        return Type::FIRE;
    }
    if (strcmp(text, "Water") == 0) {
        return Type::WATER;
    }
    if (strcmp(text, "Grass") == 0) {
        return Type::GRASS;
    }
    if (strcmp(text, "Electric") == 0) {
        return Type::ELECTRIC;
    }
    if (strcmp(text, "Ghost") == 0) {
        return Type::GHOST;
    }
    if (strcmp(text, "Flying") == 0) {
        return Type::FLYING;
    }
}
void textify(std::fstream& in, const char* fileDest)
{

    std::ofstream out(fileDest);
    if (!out.is_open())
    {
        cout << "Error Ocured" << endl;
        return;
    }
    unsigned pokemonCount = getPokemonCount(in);

    for (int i = 0; i < pokemonCount; i++)
    {
        Pokemon poki = at(in, i + 1);
        savePokemon(out, poki);
    }
    cout << "Pokemons are saved succesfully" << endl;
    out.close();
}
Pokemon readPoki(std::ifstream& in)
{
    Pokemon poki;
    in >> poki.name;
    char type[1024];
    in >> type;
    poki.type = textToType(type);
    in >> poki.power;
    return poki;
}

bool untextify(std::fstream& file, const char* filenameToOpen)
{
    std::ifstream in(filenameToOpen);
    if (!in.is_open()) {
        cout << "Error(No such File)" << endl;
        return false;
    }
    file.close();
    file.open(filename, std::ios::out); // deleting previous ones
    if (!file.is_open())
    {
        cout << "Error";
        return false;;
    }

    while (true)
    {
        Pokemon poki = readPoki(in);
        if (in.eof())
        {
            break;
        }
        savePokemonInFile(file, poki);
    }
    cout << "Sucesfully Loaded and Deleted Previous Pokemons" << endl;
    in.close();
    file.close();
    return true;
}

void StartUp()
{

    /*std::ofstream createFile(filename, std::ios::binary);
    createFile.close();*/
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error Opening File" << endl;
        return;
    }
    while (true)
    {
        int choice;
        cout << "1) - Add Pokemon" << endl;
        cout << "2) - Get Pokemon From Index(index starts from 1 to n)" << endl;
        cout << "3) - Print All Pokemons" << endl;
        cout << "4) - Save All Pokemons in a file" << endl;
        cout << "5) - Load All Pokemons from existing file and work with this file" << endl;
        cout << "9) - Exit" << endl;
        cin >> choice;
        if (!isValidInteger()) {
            cout << "Invalid Input!!!" << endl;
            continue;
        }
        if (choice == 9)
        {
            exit(0);
        }
        else if (choice == 1)
        {
            insert(file);
        }
        else if (choice == 2)
        {
            cout << "Enter Index (Start from 1):  " << endl;
            getPokemonAndPrint(file);

        }
        else if (choice == 3)
        {
            printAllPokemons(file);
        }
        else if (choice == 4)
        {
            char filenameToSave[MAX_FILE_LENGTH];
            cout << "Enter a filename to save: " << endl;
            cin >> filenameToSave;
            textify(file, filenameToSave);
        }
        else if (choice == 5)
        {
            cout << "Enter a filename to load and work with: " << endl;
            char fileNameToOpen[MAX_FILE_LENGTH];
            cin >> fileNameToOpen;
            if (untextify(file, fileNameToOpen))
            {
                file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
            }
        }
        else {
            cout << "Wrong Choice!!!" << endl;
        }

    }
}

int main()
{
    StartUp();
}