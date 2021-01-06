//
//  Armor.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Armor_hpp
#define Armor_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Item.hpp"
class Armor : public Item{
private:
    int gainHp;
    
    vector<string> armorName = {"Helmet", "Chain Mail", "Boot", "Vest", "Batman Suit"};
    
public:
    Armor();
    Armor(const int &level);
    Armor(const string &name, const int &level);
    ~Armor();

    // getter
    int getGainHp()  { return this->gainHp;}

    //  funtion
    virtual string toString();

};
#endif /* Armor_hpp */
