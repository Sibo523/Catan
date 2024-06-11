#include "Tile.h"
#include <stdexcept>
#include <iostream>

Tile::Tile(std::string tileType, int token)
    : type(tileType), numberToken(token){
    for (size_t i = 0; i < 6; i++){
        adjacentVertices.push_back(Vertex(-1,0));
    }
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
void Tile::printSettelments(){
    std::cout << "         " << (adjacentVertices[0].isSettled() ? "1" : "0") << "-1" << std::endl; // 1
    std::cout << "   " << (adjacentVertices[1].isSettled() ? "1" : "0") << "-2" << "     "; // 2
    std::cout << "   " << (adjacentVertices[2].isSettled() ? "1" : "0") << "-3" << std::endl; // 3
    std::cout << "      " << type + "-" + std::to_string(numberToken) << std::endl;
    std::cout << "   " << (adjacentVertices[3].isSettled() ? "1" : "0") << "-4" << "     "; // 4
    std::cout << "   " << (adjacentVertices[4].isSettled() ? "1" : "0") << "-5" << std::endl; // 5
    std::cout << "         " << (adjacentVertices[5].isSettled() ? "1" : "0") << "-6" << std::endl; // 6
}
void Tile::addVertex(Vertex v,size_t index)
{   
    if (index >= 7 || index < 1){
        throw std::invalid_argument("Index out of bounds");
    }
    adjacentVertices[index-1] = v;
}
Vertex Tile::getVertex(size_t index){
    if (index >= 7 || index < 1){
        throw std::invalid_argument("Index out of bounds");
    }
    return adjacentVertices[index-1];
}
Vertex* Tile::getVertexPointer(size_t index){
    if (index >= 7 || index < 1){
        throw std::invalid_argument("Index out of bounds");
    }
    return &adjacentVertices[index-1];
}

//ting means settlement
bool Tile::hasting(int x){
    if (adjacentVertices[x-1].isSettled()){ // sadge it has a settlement
        return true;
    }
    return false;
}
bool Tile::neighborSet(size_t index){ //returns true if one of the neighbors already have setllments means I can't build here
    switch (index)
    {
    case 1:
        return hasting(2) || hasting(3);
        break;

    case 2:
        return hasting(1) || hasting(4);
        break;
    
    case 3:
        return hasting(1) || hasting(5);
        break;

    case 4:
        return hasting(2) || hasting(6);
        break;

    case 5:
        return hasting(3) || hasting(6);
        break;

    case 6:
        return hasting(4) || hasting(5);
        break;
    
    default:
        std::cout<<"Index out of bounds";
        return false;
        break;
    }
}