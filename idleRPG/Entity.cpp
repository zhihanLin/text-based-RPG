//
//  Entity.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Entity.hpp"
bool Entity::isAlive(){
    bool status = (this->getCurrHp() > 0) ? true : false;
    return status;
}
