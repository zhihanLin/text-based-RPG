//
//  Hero.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Hero.hpp"
#include <math.h>

Hero::Hero(string name, string major){
    setMajor(major);
    setName(name);
    setLevel(1);
    setExp(0);
    
    setStrength(5);
    setIntelligence(5);
    setStamina(5);
   
    setGold(0);
    
    applayWeapon(Weapon(1));
    applayArmor(Armor(1));
    
    updateStatus();
}
Hero::~Hero(){
    
}
//  hero's level increase, hero's exp to next level increase too
void Hero::levelUp(){
    setLevel(getLevel() + 1);
    setExp(getExp() - getExpNext());
    
    //  every level up, hero gains 5 status points.
    if(this->major == "Mage"){
        setStrength(getStrength());
        setIntelligence(getIntelligence() + 4);
        setStamina(getStamina() + 1);
    } else if (this->major == "Warrior"){
        setStrength(getStrength() + 3);
        setIntelligence(getIntelligence());
        setStamina(getStamina() + 2);
    } else{
        setStrength(getStrength());
        setIntelligence(getIntelligence() + 2);
        setStamina(getStamina() + 3);
    }
    updateStatus();
}
//  update hero's status after level up, apply equipment or take off equipment
void Hero::updateStatus(){
    //  EXP and part status formula is from user @SurajSharma on GitHub
    setExpNext(
        static_cast<int>(50 / 3) * (pow(getLevel(), 3) - 6 * pow(getLevel(), 2) + (17 * getLevel() - 11)) + 100);
    setMaxHp((getStamina() * 5) + getStrength() + (getLevel() * 5) + this->armor[0].getGainHp());
    setCurrHp(getMaxHp());
    setMaxSp(3);
    setCurrSp(0);
    
    if (this->major == "Mage" || this->major == "Priest") {
        setMaxDamage(getIntelligence() * 2 + this->weapon[0].getMaxDamage());
        setMinDamage(getIntelligence() + 2 + this->weapon[0].getMinDamage());
    }else {
        setMaxDamage(getStrength() * 2 + this->weapon[0].getMaxDamage());
        setMinDamage(getStrength() + 2 + this->weapon[0].getMinDamage());
    }
    
    if (this->major == "Mage") {
        //  Mage's special gives two monsters 1.5X damage
        setSpecialDamage(getMaxDamage() * 1.5);
    }else if (this->major == "Warrior"){
        //  Warrior's special gives one monster 2X damage
        setSpecialDamage(getMaxDamage() * 2);
    }else{
        //  Priest's special heals three heros by 1.2X amount of damage
        setSpecialDamage(getMaxDamage()* 1.2);
    }
    
    
}
//  return a string of hero's status with formatting
string Hero::toString(){
    stringstream ss;
    ss  << "\t\t" << getName() << endl << "--------------------------------------"        << endl
        << left << setw(9) << " Major: "  << getMajor()                                 << endl
        << left << setw(9) << " Level: "  << getLevel()                                 << endl
        << left << setw(9) << " EXP: "    << getExp()       << " / " << getExpNext()    << endl
        << left << setw(9) << " HP: "     << getCurrHp()    << " / " << getMaxHp()      << endl
        << left << setw(9) << " Damage: " << getMinDamage() << " ~ " << getMaxDamage()  << endl
        << "--------------------------------------"                                     << endl
        << left << setw(9) << " STR: "    << getStrength()                              << endl
        << left << setw(9) << " INT: "    << getIntelligence()                          << endl
        << left << setw(9) << " STA: "    << getStamina()                               << endl
        << left << setw(9) << "--------------------------------------"                  << endl;
    if (weapon[0].getName() == "N/A") {
        ss << left << setw(9) << " Weapon: N/A" << endl;
    }else{
        ss << left << setw(9) << " Weapon: "   << weapon[0].toString() << endl;
    }
    if (armor[0].getName() == "N/A") {
        ss << left << setw(9) << " Armor: N/A" << endl << endl;
    }else{
        ss << left << setw(9) << " Armor: "   << armor[0].toString()   << endl;
    }
    ss << endl;
    return ss.str();
}
//  display hero's status
void Hero::showStatus(){
    cout << toString();
}

//  return damage between max and min damage
int Hero::attack(){
    return ((rand() % (getMaxDamage() - getMinDamage() + 1 )) + getMinDamage());
}
//  take attack from monster
void Hero::takeAttack(const int &damage){
    int tempHp = getCurrHp() - damage;
    tempHp = (tempHp) >= 0 ? tempHp : 0;
    setCurrHp(tempHp);
}


void Hero::applayWeapon(const Weapon &weapon){
    this->weapon[0] = weapon;
}
void Hero::applayArmor(const Armor &armor){
    this->armor[0]  = armor;
}
Weapon Hero::takeOffWeapon(){
    Weapon returnWeapon;
    Weapon noWeapon;
    returnWeapon = this->weapon[0];
    this->weapon[0] = noWeapon;
    
    return returnWeapon;
}
Armor Hero::takeOffArmor(){
    Armor returnArmor;
    Armor noArmor;
    returnArmor = this->armor[0];
    this->armor[0] = noArmor;
    
    return returnArmor;
}

//  return a string of hero's status for file output
string Hero::stringToSave(){
    stringstream ss;
    ss << this->major   << " " << this->name     << " " << this->level       << " "
       << this->exp     << " " << this->strength << " " << this->intelligence<< " "
       << this->stamina << " " << this->gold     << "\n";
    return ss.str();
}

// operator overloading

Hero &Hero::operator= (const Hero &right){
    setMajor(right.major);
    setName(right.name);
    setLevel(right.level);
    setExp(right.exp);
    
    setStrength(right.strength);
    setIntelligence(right.intelligence);
    setStamina(right.stamina);
    
    setGold(right.gold);
    
    this->updateStatus();
    return *this;
}
ostream &operator<<(ostream &strm, const Hero &hero){
    strm << hero.major   << " " << hero.name     << " " << hero.level       << " "
         << hero.exp     << " " << hero.strength << " " << hero.intelligence<< " "
         << hero.stamina << " " << hero.gold     << endl;
    return strm;
}
istream &operator>>(istream &strm, Hero &hero){
    string newMajor;
    string newName;
    int newLevel;
    int newExp;
    int newStrength;
    int newIntelligence;
    int newStamina;
    int newGold;
    
    strm >> newMajor   >> newName     >> newLevel
         >> newExp     >> newStrength >> newIntelligence
         >> newStamina >> newGold;
    
    hero.setMajor(newMajor);
    hero.setName(newName);
    hero.setLevel(newLevel);
    hero.setExp(newExp);
    hero.setStrength(newStrength);
    hero.setIntelligence(newIntelligence);
    hero.setStamina(newStamina);
    hero.setGold(newGold);
    return strm;
}

