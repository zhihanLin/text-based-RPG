//
//  Monster.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Entity.hpp"
class Monster : public Entity{
private:
    int exp;
public:
    
    Monster(const string &name,const int &level);
    ~Monster();
    
    //  function
    int attack();
    void takeAttack(const int &damage);
    string toString();
    void showStatus();
    
    //  setter
    void setExp(int exp) { this->exp = exp; }
    
    //  getter
    int getExp()         {return this->exp; }
};
#endif /* Monster_hpp */
