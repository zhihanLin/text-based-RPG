//
//  Shop.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 5/3/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Shop.hpp"

//  shop refresh items base on hero's level
Shop::Shop(int level){
    this->shopLevel = level;
    for (int i = 0; i < 6; i++) {
        int index = ((rand() % 100) + 1);
        //  with 50% chance, generate apple x 10, 500 gold each, heals 20 % hp
        if (index <= 50) {
            shelf.push_back(Item("apple", index / 10 + 1, 500));
        }
        //  with 20% change, generate weapon of shoplevel
        else if(index > 50 && index <= 70){
            shelf.push_back(Weapon(shopLevel));
        }
        //  with 25% change, generate armor of shoplevel
        else if (index > 70 && index <= 95){
            shelf.push_back(Armor(shopLevel));
        }
        //  with 5% change, generate weapon of shoplevel + 5
        else if (index > 95){
            shelf.push_back(Weapon(shopLevel + 5));
        }
    }
}
Shop::~Shop(){
    
}
//  sell inventory for gold
int Shop::sell(Inventory &inventory, string itemName, int itemLevel, int qt){
    this->goldEarned = inventory.searchEquipment(itemName, itemLevel)->getSellValue() * qt;
    inventory.deleteItem(itemName, itemLevel, qt);
    return this->goldEarned;
}

void Shop::purchase(vector<Hero> &heros, Inventory &inventory, int index){
        inventory.insertItem(shelf[index - 1]);
        heros[0].setGold(heros[0].getGold() - shelf[index].getBuyValue());
        shelfIt = shelf.begin();
        shelf.erase((shelfIt + (index - 1)));
}

string Shop::toString(){
    stringstream ss;
    ss << " \t\t= SHOP ="          << endl
       << " ----------------------------- "  << endl
    << left << setw(18)<< "  Item" << "QT" << right << setw(9) << "G each" << endl
    << " ----------------------------- "  << endl;
    for (int i = 0; i < shelf.size(); i++) {
        ss << "  " << i + 1 << ". " << left << setw(12)
           << shelf[i].getName()
           << " X" << shelf[i].getQt()
           << right << setw(8)
           << shelf[i].getBuyValue() << "G"<< endl;
    }
    ss << " ----------------------------- "  << endl;
    return ss.str();
}
void Shop::displayShelf(){
    cout << toString();
}
