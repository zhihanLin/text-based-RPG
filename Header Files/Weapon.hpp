//
//  Weapon.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Item.hpp"
using namespace std;

class Weapon : public Item{
private:
    int minDamage;
    int maxDamage;
    
    vector<string> weaponName = {"Knife", "Sword", "Bat", "Mace", "Spear"};
    
public:
    Weapon();
    Weapon(const int &level);
    Weapon(const string &name, const int &level);
    ~Weapon();
    
    // getter
    int getMinDamage()  { return this->minDamage;}
    int getMaxDamage()  { return this->maxDamage;}
    
    //  funtion
    virtual string toString();
    
};
#endif /* Weapon_hpp */
