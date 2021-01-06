//
//  InvalidMenuChoice.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/29/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef InvalidMenuChoice_hpp
#define InvalidMenuChoice_hpp

#include <stdio.h>
class InvalidMenuChoice{
private:
    int value;
public:
    InvalidMenuChoice(int value);
    void setValue(int value);
    int getValue();
};
#endif /* InvalidMenuChoice_hpp */
