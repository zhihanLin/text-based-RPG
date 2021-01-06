//
//  InvalidMenuChoice.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/29/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "InvalidMenuChoice.hpp"
InvalidMenuChoice::InvalidMenuChoice(int value){
    setValue(value);
}
void InvalidMenuChoice::setValue(int value){
    this->value = value;
}
int InvalidMenuChoice::getValue(){
    return this->value;
}
