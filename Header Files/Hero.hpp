//
//  Hero.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Hero_hpp
#define Hero_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <array>
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Entity.hpp"
#include "Inventory.hpp"


class Hero : public Entity{
private:
    string major;
    
    int exp;
    int expNext;
    int maxSp;
    int currSp;
    
    int strength;
    int intelligence;
    int stamina;
    
    array<Weapon, 1> weapon;
    array<Armor, 1> armor;
    
protected:
    //  setters
    void setMajor(string major)             { this->major = major;}
    void setExpNext(int expNext)            { this->expNext = expNext;}
    void setMaxSp(int maxSp)                { this->maxSp = maxSp;}
    void setCurrSp(int currSp)              { this->currSp = (currSp > 3) ? 3 : currSp;};
    
    void setStrength(int strength)          { this->strength = strength;}
    void setIntelligence(int intelligence)  { this->intelligence = intelligence;}
    void setStamina(int stamina)            { this->stamina = stamina;}
    
public:
    Hero(){}
    Hero(string name, string major);
    ~Hero();
    
    //  function
    string toString();
    void showStatus();
    virtual void levelUp();
    void updateStatus();        //  update status after leveling up
    string stringToSave();
    int attack();
    void takeAttack(const int &damage);
    
    void applayWeapon(const Weapon &weapon);
    void applayArmor(const Armor &armor);
    Weapon takeOffWeapon();
    Armor takeOffArmor();
    friend class Dungeon;
    
    //  setter
    void setExp(int exp)    { this->exp = exp;}
    
    //  getter
    string getMajor()       { return this->major;}
    int getExp()            { return this->exp;}
    int getExpNext()        { return this->expNext;}
    int getMaxSp()          { return this->maxSp;}
    int getCurrSp()         { return this->currSp;}
    int getStrength()       { return this->strength;}
    int getIntelligence()   { return this->intelligence;}
    int getStamina()        { return this->stamina;}
    
    // operator overloading
    Hero &operator= (const Hero &right);
    friend ostream &operator<<(ostream &strm, const Hero &hero);
    friend istream &operator>>(istream &strm, Hero &hero);
};
#endif /* Hero_hpp */
