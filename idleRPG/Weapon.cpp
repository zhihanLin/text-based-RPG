//
//  Weapon.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Weapon.hpp"
Weapon::Weapon(){
    this->name = "N/A";
}
Weapon::Weapon(const int &level) : Item(level){
    int index;
    index = rand() % (weaponName.size());
    this->name = weaponName[index];
    this->level = level;
    this->maxDamage = level * 5;
    this->minDamage = maxDamage / 2;
    
    setQt(1);
    setBuyValue(getLevel() * 300 + getLevel() * 30);
    setSellValue(getBuyValue() / 2);
}
Weapon::Weapon(const string &name, const int &level) : Item(level){
    
    this->name = name;
    this->level = level;
    this->maxDamage = level * 5;
    this->minDamage = maxDamage / 2;
    
    setQt(1);
    setBuyValue(getLevel() * 2000 + getLevel() * 200);
    setSellValue(getBuyValue() / 2);
}
Weapon::~Weapon(){
    
}

string Weapon::toString(){
    stringstream ss;
    ss << left << setw(10) << this->getName() << " - Lv" << this->getLevel() << " Damage:" << getMinDamage() << "~" << getMaxDamage();
    return ss.str();
}
