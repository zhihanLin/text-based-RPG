//
//  Dungeon.hpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#ifndef Dungeon_hpp
#define Dungeon_hpp

#include <stdio.h>
#include <vector>
#include <thread>
#include "Entity.hpp"
#include "Hero.hpp"
#include "Monster.hpp"
class Dungeon{
private:
    //  level range
    int levelMax;
    int levelMin;
    int numOfMonster;
    
    //  battle related
    int damage = 0;             //  temperaryly store damage from hero or monster
    int expGained = 0;          //  earned from each monster defeated
    int goldGained = 0;         //  earned from each monster defeated
    bool heroTurn;
    bool heroWin = false;       //  heros win when no monsters left
    bool monsterWin = false;    //  monsters win when all heros died
    vector<Monster> monsters;   
    vector<Monster>::iterator monster;
    vector<Hero>::iterator hero;
    
    
public:
    Dungeon(int min, int max, vector<Hero> &heros);
    ~Dungeon();
    //  function
    //  combat
    void combat(vector<Hero> &heros);
    bool anyHeroAlive(vector<Hero> &heros);
    void ckStatNGain(int index);         //  check monster's status, if dead, collect exp and gold
    void herosTurn(vector<Hero> &heros);
    void herosAttack(vector<Hero> &heros);
    void mageSpAtt(vector<Hero> &heros);
    void warriorSpAtt(vector<Hero> &heros);
    void priestSpAtt(vector<Hero> &heros);
    void dispHeroDmg(vector<Hero> &heros, int index, int damage);
    void monstersTurn(vector<Hero> &heros);
    void collectGNExp(vector<Hero> &heros, int exp, int gold);
    //  combat details
    string statToString(vector<Hero> &heros);
    void showStat(vector<Hero> heros);
    
    
    //  setter
    void setLvMax(int max)              { this->levelMax = max;}
    void setLvMin(int min)              { this->levelMin = min;}
    void setNumOfMon(vector<Hero> heros){ this->numOfMonster = (rand() % heros.size() + 1) + 1;}
    void setExpEarned(int exp)          { this->expGained += exp;}
    void setGoldEarned(int gold)        { this->goldGained += gold;}
        
    //  getter
    int getLvMax()                      { return levelMax;}
    int getLvMin()                      { return levelMin;}
    int getExpEarned()                  { return expGained;}
    int getGoldEarned()                 { return goldGained;}
};
#endif /* Dungeon_hpp */
