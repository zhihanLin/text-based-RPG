//
//  Game.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include "Inventory.hpp"
#include "Dungeon.hpp"
#include "InvalidMenuChoice.hpp"
#include "Shop.hpp"

using namespace std;

class Game{
private:
    //  for menu
    int choice;
    bool tryAgain = false;
    
    bool ifPlaying = true;
    bool lv15Recruitment = true;
    bool lv30Recruitment = true;
protected:
    vector<Hero> heros;
    vector<Hero> newHeros;
    vector<Hero>::iterator it;
    
    
    
    //  for save and load
    ofstream herosOut;
    ifstream herosIn;
    //  temporarily store record in queue,
    //  10 records of heros are allowed,
    //  the latest record will push out the oldest one
    string record;
    deque<string> herosRecords;

    
public:
    Inventory backPack;
    
    Game();
    ~Game();
    
    //  function
    void menu();
    void choiceBetween(const int &begin, const int &end);
    void menu_inventory();
    void menu_applyWeapon(const int &index, string &itemName, int &itemLevel);
    void menu_applyArmor(const int &index, string &itemName, int &itemLevel);
    void createHero();
    void save();    // 10 records are allowed
    void load();
    void pause();
    //  setter
    void setPlaying(bool tf) {  this->ifPlaying = tf; }
    //  gettet
    bool getPlaying()   {  return this->ifPlaying;  }
    
};
#endif /* Game_hpp */
