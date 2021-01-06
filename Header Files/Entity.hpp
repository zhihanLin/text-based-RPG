//
//  Entity.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Entity{
protected:
    string name;
    int level;
    int maxHp;
    int currHp;
    
    int maxDamage;
    int minDamage;
    int specialDamage;
    
    int gold;

    //  setter
    void setName(string name)               { this->name = name;}
    void setLevel(int level)                { this->level = level;}
    void setMaxHp(int maxHp)                { this->maxHp = maxHp;}
    void setCurrHp(int currHp)              { this->currHp = currHp;}
    
    void setMaxDamage(int maxDamage)        { this->maxDamage = maxDamage;}
    void setMinDamage(int minDamage)        { this->minDamage = minDamage;}
    void setSpecialDamage(int specialDamage){ this->specialDamage = specialDamage;}
    
    void setGold(int gold)                  { this->gold = gold;}
public:
    //  fuction
    virtual string toString() = 0;
    virtual void showStatus() = 0;
    virtual int attack() = 0;
    virtual void takeAttack(const int&) = 0;
    bool isAlive();
    
    friend class Dungeon;
    friend class Game;
    friend class Shop;
    //  getter
    string getName()        { return this->name;}
    int getLevel()          { return this->level;}
    int getMaxHp()          { return this->maxHp;}
    int getCurrHp()         { return this->currHp;}
    
    int getMaxDamage()      { return this->maxDamage;}
    int getMinDamage()      { return this->minDamage;}
    int getSpecialDamage()  { return this->specialDamage;}
    
    int getGold()           { return this->gold;}
};
#endif /* Entity_hpp */
