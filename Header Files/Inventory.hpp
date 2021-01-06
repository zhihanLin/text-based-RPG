//
//  Inventory.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/18/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp

#include <stdio.h>
#include <list>
#include <iostream>
#include "Item.hpp"
using namespace std;
class Inventory{
private:
    struct Inven{
        Item item;
        struct Inven *next = nullptr;
    };
    
    Inven *head;
    
    //  "empty" item for return when no match found,  Item("N/A", 0, 0)
    Item none;
    
public:
    Inventory();
    ~Inventory();
    
    void appandItem(const Item &obj);
    void insertItem(const Item &obj);
    void deleteItem(const string &name, const int &level, const int &qt);
    void displayInventory();
    Item* searchEquipment(const string &name, const int &level);
};
#endif /* Inventory_hpp */
