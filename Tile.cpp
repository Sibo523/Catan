#include "Tile.h"
#include <stdexcept>
#include <iostream>

Tile::Tile(std::string tileType, int token)
    : type(tileType), numberToken(token){
    for (size_t i = 0; i < 6; i++){
        adjacentVertices.push_back(Vertex(-1,0));
    }
    // std::cout<< adjacentVertices.size()<<std::endl;
    
}

std::string Tile::getResource() const
{
    return type;
}
int Tile::getNumberToken() const
{
    return numberToken;
}
std::string Tile::toString() const
{
    return type + "-" + std::to_string(numberToken);
}
void Tile::print(){
    std::cout << "         "+adjacentVertices[0].getOwner()<<"-1"<<std::endl; // 1
    std::cout << "   "+adjacentVertices[1].getOwner()<<"-2"<<"     "; // 2
    std::cout <<"   "+ adjacentVertices[2].getOwner()<<"-3"<<std::endl; // 3
    std::cout<< "      "+type + "-" + std::to_string(numberToken)<<std::endl;
    std::cout <<"   "+ adjacentVertices[3].getOwner()<<"-4"<<"     "; // 4
    std::cout <<"   "+ adjacentVertices[4].getOwner()<<"-5"<<std::endl; // 5
    std::cout <<"         "+ adjacentVertices[5].getOwner()<<"-6"<<std::endl; // 6
}
void Tile::addVertex(Vertex v,size_t index)
{   
    if (index >= 6 || index < 0){
        throw std::invalid_argument("Index out of bounds");
    }
    adjacentVertices[index] = v;
}