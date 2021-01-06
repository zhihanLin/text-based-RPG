//
//  Monster.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Monster.hpp"
Monster::Monster(const string &name, const int &level){
    setName(name);
    setLevel(level);
    setExp(getLevel() * 100);
    setMaxHp(getLevel() * 10 + getLevel() * 2);
    setCurrHp(getMaxHp());
    setMaxDamage(getLevel() * 2);
    setMinDamage(getLevel() * 1.5);
    setGold(getLevel() * 10);
}
Monster::~Monster(){
    
}
int Monster::attack(){
    return ((rand() % (getMaxDamage() - getMinDamage() + 1 )) + getMinDamage());
}
void Monster::takeAttack(const int &damage){
    int tempHp = getCurrHp() - damage;
    tempHp = (tempHp) >= 0 ? tempHp : 0;
    setCurrHp(tempHp);
}

string Monster::toString(){
    stringstream ss;
    ss  << "\t\t" << getName()                                         << endl
    << "---------------------"                                         << endl
    << " Level: "       << right << setw(3) << getLevel()              << endl
    << " HP: "          << getCurrHp()     << " / " << getMaxHp()      << endl;
    return ss.str();
}
void Monster::showStatus(){
    std::cout << toString();
}
