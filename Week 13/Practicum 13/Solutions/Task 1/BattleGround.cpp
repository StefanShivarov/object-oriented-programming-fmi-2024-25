#include <stdio.h>
#include "Battleground.h"

BattleGround::BattleGround(){
    this->capacity = 8;
    this->beasts = new Beast*[this->capacity];
    this->size = 0;
}

BattleGround::BattleGround(const BattleGround& other){
    copy(other);
}

BattleGround::BattleGround(BattleGround&& other){
    move(std::move(other));
}

BattleGround::BattleGround(const Beast** beasts,size_t size){
    this->beasts = new Beast*[size];
    for(int i = 0;i<size;i++)
        this->beasts[i] = beasts[i]->clone();
    this->size = size;
    this->capacity = size;
}

BattleGround& BattleGround::operator=(const BattleGround& other){
    if(this!=&other){
        destroy();
        copy(other);
    }
    return *this;
}

BattleGround& BattleGround::operator=(BattleGround&& other){
    if(this!=&other){
        destroy();
        move(std::move(other));
    }
    return *this;
}

void BattleGround::move(BattleGround&& other){
    this->beasts = other.beasts;
    other.beasts = nullptr;
    this->size = other.size;
    this->capacity = other.capacity;
    other.size = other.capacity = 0;
}

void BattleGround::destroy(){
    for(int i = 0;i<size;i++)
        delete beasts[i];
    delete[] beasts;
}

void BattleGround::copy(const BattleGround& other){
    this->beasts = new Beast*[other.capacity];
    for(int i = 0;i<other.size;i++)
        this->beasts[i] = other.beasts[i]->clone();
    this->size = other.size;
    this->capacity = other.capacity;
}


void BattleGround::resize(size_t newCap){
    Beast** temp = new Beast*[newCap];
    for(int i = 0;i<size;i++)
        temp[i] = beasts[i];
    delete[] beasts;
    beasts = temp;
    this->capacity = newCap;
}


BattleGround::~BattleGround(){
    destroy();
}

Beast* BattleGround::getBeastOnIndex(size_t index) const{
    if(index >= size){
        throw std::invalid_argument("Index out of bounds!");
    }
    return beasts[index]->clone();
}


size_t BattleGround::beastsBeatenByMonster(const Beast* beast) const{
    size_t count = 0;
    for(int i = 0;i<size;i++){
        BattleOutput output = beasts[i]->beats(beast);
        if(output == BattleOutput::WIN)
            count++;
    }
    return count;
}
