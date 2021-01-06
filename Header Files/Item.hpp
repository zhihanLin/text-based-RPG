//
//  Item.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/18/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
class Item{
protected:
    //  for all Items
    string name;
    string desc;
    int qt;
    int maxQt;
    int buyValue;
    int sellValue;
    
    //  for equipment
    int level;
    
    
public:
    Item();
    Item(string name, int qt, int buyV);
    Item(int level);
    ~Item();
    //  function
    virtual string toString() const;
    //  setter
    void setName(string name)       { this->name = name;}
    void setDesc(string desc)       { this->desc = desc;}
    void setQt(int qt)              { this->qt = qt;}
    void setMaxQt(int maxQt)        { this->maxQt = maxQt;}
    void setBuyValue(int buyValue)  { this->buyValue = buyValue;}
    void setSellValue(int sellValue){ this->sellValue = sellValue;}
    void setLevel(int level)        { this->level = level;}
    //  getter
    string getName() const  { return this->name;}
    string getDesc()        { return this->desc;}
    int getQt() const       { return qt;}
    int getMaxQt()          { return this->maxQt;}
    int getBuyValue()       { return this->buyValue;}
    int getSellValue()      { return this->sellValue;}
    int getLevel()          { return this->level;}
    
    //  operator overloading
    friend ostream &operator<<(ostream &strm, Item &item);
};
#endif /* Item_hpp */
