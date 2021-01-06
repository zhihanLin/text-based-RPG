//
//  Item.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/18/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Item.hpp"
Item::Item(){
    setName("");
    setQt(0);
    setBuyValue(0);
    setSellValue(0);
}
Item::Item(string name, int qt, int buyV){
    setName(name);
    setQt(qt);
    setBuyValue(buyV);
    setSellValue(getBuyValue() / 2);
}
Item::Item(int level){
    setLevel(level);
}
Item::~Item(){
    
}
string Item::toString() const{
    stringstream ss;
    ss  << "" << setfill(' ') << left << setw(8) << this->getName()  << "Lv. " << this->level << "  QT:"  << right << setw(3) << this->getQt();
    return ss.str();
}

ostream &operator<< (ostream &strm, Item &item){
    strm << item.toString();
    return strm;
}
