//
//  Shop.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Shop_hpp
#define Shop_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include "Inventory.hpp"
#include "Item.hpp"
#include "Hero.hpp"
class Shop{
private:
    //  number of item in shop
    int numOfItem;
    int shopLevel;
    
    int goldEarned;
    
    vector<Item> shelf;
    vector<Item>::iterator shelfIt;
public:
    //  shop refresh items base on hero's level
    Shop(int level);
    ~Shop();
    
    int sell(Inventory &inventory, string itemName, int itemLevel, int qt);
    void purchase(vector<Hero> &heros,Inventory &inventory, int index);
    string toString();
    void displayShelf();
    
    friend class Game;
};
#endif /* Shop_hpp */
