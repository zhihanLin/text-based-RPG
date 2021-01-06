//
//  Armor.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Armor.hpp"
Armor::Armor(){
    this->name = "N/A";
}
Armor::Armor(const int &level) : Item(level){
    int index;
    index = rand() % (armorName.size());
    this->name = armorName[index];
    this->level = level;
    this->gainHp = level * 5;
    
    setQt(1);
    setBuyValue(getLevel() * 500 + getLevel() * 50);
    setSellValue(getBuyValue() / 2);
}
Armor::Armor(const string &name, const int &level) : Item(level){
    
    this->name = name;
    this->level = level;
    this->gainHp = level * 5;
    
    setQt(1);
    setBuyValue(getLevel() * 200 + getLevel() * 20);
    setSellValue(getBuyValue() / 2);
}
Armor::~Armor(){
    
}

string Armor::toString(){
    stringstream ss;
    ss << left << setw(10) << this->getName() << " - Lv" << this->getLevel() << " HP:" << getGainHp();
    return ss.str();
}


