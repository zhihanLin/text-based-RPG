//
//  Dungeon.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Dungeon.hpp"
Dungeon::Dungeon(int min, int max, vector<Hero> &heros){
    setLvMin(min);
    setLvMax(max);
    setNumOfMon(heros);
    //  create a team of monsters;
       for (int i = 0; i < numOfMonster; i++) {
           monsters.push_back(Monster("C++", (rand() % (this->levelMax - this->levelMin + 1)) + this->levelMin));
       }
       
       //  create iterator for both teams
       monster = monsters.begin();
       hero = heros.begin();
}
Dungeon::~Dungeon(){
    
}

//  function
//  the main body of combat
void Dungeon::combat(vector<Hero> &heros){
   
    
    //  toss a coin, 1 heros go first, 0 monsters go first
    if(rand() % 2 == 1){
        heroTurn = true;
    }else{
        heroTurn = false;
    }
    //  combat begin!
    //  counter for rounds, both hero and monster have taken a turn is considered as a round
    int count = 0;
    while (!heroWin && !monsterWin) {
        //  display simple status for combat
        std::this_thread::sleep_for(std::chrono::seconds {2});
        if(count % 2 == 0) showStat(heros);
        count++;
        
        if (heroTurn && anyHeroAlive(heros) && numOfMonster) {
            //  heros team attack monsters one by one
            herosTurn(heros);
            //  end hero's turn
            heroTurn = false;
            std::this_thread::sleep_for(std::chrono::seconds {1});
        }else if (!heroTurn && monsters.size() > 0){
            //  monsters team attack heros one by one
            monstersTurn(heros);
            //  end monster's turn
            heroTurn = true;
            std::this_thread::sleep_for(std::chrono::seconds {1});
        }
        //  end of combat
        if (heroWin) {
            showStat(heros);
            cout << endl << "\t = VICTORY =" << endl;
            collectGNExp(heros, expGained, goldGained);
            //  if exp meet exp for next, hero level up
            for (hero = heros.begin(); hero != heros.end(); hero++) {
                while(hero->getExp() >= hero->getExpNext()) {
                    hero->levelUp();
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds {2});
        }else if (monsterWin){
            cout  << endl << "\t = DEFEAT =" << endl;
            collectGNExp(heros, expGained / 10 , goldGained / 10);
            //  if exp meet exp for next, hero level up
            for (hero = heros.begin(); hero != heros.end(); hero++) {
                while(hero->getExp() >= hero->getExpNext()) {
                    hero->levelUp();
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds {2});
        }
    }
}

//  if no hero alive, monster win
bool Dungeon::anyHeroAlive(vector<Hero> &heros){
    //  check if any hero alive
    bool status = false;
    for (hero = heros.begin(); hero != heros.end(); hero++) {
        if (hero->isAlive()) {
            status = true;
        }
    }
    if (!status) {
        monsterWin = true;
    }
    hero = heros.begin();
    return status;
}

//  check monster's status, if dead, collect exp and gold
void Dungeon::ckStatNGain(int index){
    //  check if the monster been attack is dead,
    if (!(monster + index)->isAlive()) {
        //  if so, collect exp and gold.
        setExpEarned((monster + index)->getExp());
        setGoldEarned((monster + index)->getGold());
        //  and remove it from the team,
        monsters.erase(monster + index);
        //  if all monsters died, heros win, end combat
        if(--numOfMonster == 0){
            heroWin = true;
        }
    }
}

//  hero's actions on its turn
void Dungeon::herosTurn(vector<Hero> &heros){
    std::this_thread::sleep_for(std::chrono::seconds {1});
    cout << endl << "\t- Hero's turn-" << endl << endl;
    //  each heros on the team attack monsters
    for (hero = heros.begin(); hero != heros.end(); hero++) {
        if(hero->getCurrHp() > 0){
            //  when sp != 3, hero use normal attack
            if ((hero->getCurrSp() != hero->getMaxSp()) && !heroWin) {
                herosAttack(heros);
            }
            //  when sp == 3, hero use special attack
            else if ((hero->getCurrSp() == hero->getCurrSp())  && !heroWin ){
                //  Mage's special gives two monsters 1.5X maxdamage
                if(hero->getMajor() == "Mage"){
                    mageSpAtt(heros);
                }
                //  Warrior's special gives one monster 2X maxdamage
                else if (hero->getMajor() == "Warrior"){
                    warriorSpAtt(heros);
                }
                //  Priest's special heals three heros by the amount of 1.2X maxdamage
                else if (hero->getMajor() == "Priest"){
                    priestSpAtt(heros);
                }
            }
        }
        if (heroWin) break;
    }
    hero = heros.begin();
}

//  hero's normal attack
void Dungeon::herosAttack(vector<Hero> &heros){
    //  select a random monster on monster's team
    int index = rand() % this->numOfMonster;
    //  monster takes attack form hero
    this->damage = hero->attack();
    (monster + index)->takeAttack(damage);
    //  display damage hero made
    dispHeroDmg(heros, index, damage);
    monster = monsters.begin();
    //  check the attacked monster's status
    ckStatNGain(index);
    
}
//  hero's spacial attack
//  Mage's special gives two monsters 1.5X maxdamage
void Dungeon::mageSpAtt(vector<Hero> &heros){
    
    //  select first random monster on monster's team
    int index = rand() % numOfMonster;
    //  monster takes attack form hero
    (monster + index)->takeAttack(hero->getSpecialDamage());
    dispHeroDmg(heros, index, hero->getSpecialDamage());
    hero->setCurrSp(0);
    ckStatNGain(index);
    //  if there are more than one monster, attack next monster
    if (numOfMonster >= 2) {
        //  select second random monster on monster's team
        index = rand() % numOfMonster;
        //  monster takes attack form hero
        (monster + index)->takeAttack(hero->getSpecialDamage());
        dispHeroDmg(heros, index, damage);
        hero->setCurrSp(0);
        ckStatNGain(index);
    }
}
//  Warrior's special gives one monster 2X maxdamage
void Dungeon::warriorSpAtt(vector<Hero> &heros){
    int index = rand() % numOfMonster;
    //  monster takes attack form hero
    (monster + index)->takeAttack(hero->getSpecialDamage());
    dispHeroDmg(heros, index, hero->getSpecialDamage());
    hero->setCurrSp(0);
    ckStatNGain(index);
}
//  Priest's special heals three heros by the amount of 1.2X maxdamage
void Dungeon::priestSpAtt(vector<Hero> &heros){
    
    cout << " *** " << hero->getName() << " heals heros ***" << endl;
    std::this_thread::sleep_for(std::chrono::seconds {2});
    for (int i = 0; i < heros.size(); i++) {
        //  if hero is alive, heal this hero with certain amount of hp
        if (heros[i].isAlive()) {
            int tempHp = heros[i].getCurrHp() + hero->getSpecialDamage();
            tempHp = (tempHp <= heros[i].getMaxHp()) ? tempHp : heros[i].getMaxHp();
            heros[i].setCurrHp(tempHp);
            
            cout << " *** " << hero->getName() << " HP+" << hero->getSpecialDamage() << " ***" << endl;
        }
    }
    hero->setCurrSp(0);
}
//  display hero damage to consolo
void Dungeon::dispHeroDmg(vector<Hero> &heros,int index, int damage){
    std::this_thread::sleep_for(std::chrono::seconds {2});
    //  emphasize special attack
    if (hero->getCurrSp() == 3) cout << " *** " << hero->getName() << " used special ***" << endl;
    //  display damage
    cout << " " << hero->getName() << " attack --> " << (monster + index)->getName() << " - Lv" << (monster + index)->getLevel() << endl
         << " " << (monster +index)->getName() << " HP-" << damage << endl;
}
//  monster's actions on its turn
void Dungeon::monstersTurn(vector<Hero> &heros){
    std::this_thread::sleep_for(std::chrono::seconds {1});
    cout << endl << "\t- Monster's turn-" << endl << endl;
    //  each heros on the team attack monsters
    for (monster = monsters.begin(); monster != monsters.end(); monster++) {
        //  select a random alive hero on hero's team
        int index = 0;
        do{
             index = rand() % heros.size();
        }while ((hero + index)->getCurrHp() == 0 && anyHeroAlive(heros));
        
        if (!monsterWin){
            
            this->damage = monster->attack();
            //  hero takes attack from monster
            (hero + index)->takeAttack(damage);
            std::this_thread::sleep_for(std::chrono::seconds {2});
            cout << " " << monster->getName() << " - Lv" << monster->getLevel() << " attack --> " << (hero + index)->getName()  << endl
                 << " " << (hero + index)->getName() << " HP-" << this->damage << endl;
            
            //  hero gain 1 sp if get attacked
            (hero + index)->setCurrSp(hero->getCurrSp() + 1);
            hero = heros.begin();
        }else{
            
            break;
        }
    }
    monster = monsters.begin();
}

//  collect all exp and gold form combat if heros win, otherwise, 1/10 will be collected
void Dungeon::collectGNExp(vector<Hero> &heros, int exp, int gold){
    
    //  each team member will gain exp
    for (hero = heros.begin() ; hero != heros.end(); hero++) {
        hero->setExp(hero->getExp() + expGained);
        hero->setCurrHp(hero->getMaxHp());
    }
    //  team leader is in charge of gold... hhhhh ^_^
    hero = heros.begin();
    hero->setGold(hero->getGold() + goldGained);
    //  display exp and golds earned to consolo
    cout << "\t EXP + "    << expGained    << endl
         << "\t Golds + "  << goldGained   << endl;
     
}

string Dungeon::statToString(vector<Hero> &heros){
    stringstream ss;
    ss  << endl << " ============================" << endl;
    for(int i = 0; i < heros.size(); i++){
        ss  << "  " << hero[i].getName()          << " - Lv" << hero[i].getLevel()    << endl
            << "  HP: "  << hero[i].getCurrHp()   << " / "   << hero[i].getMaxHp()
            << "  | SP: " << hero[i].getCurrSp()   << " / "   << hero[i].getMaxSp()    << endl;
    }
    ss  << " ============================" << endl;
    for(int i = 0; i < monsters.size(); i++){
        ss  << "  " << monster[i].getName()       << " - Lv" << monster[i].getLevel() << endl
            << "  HP: " << monster[i].getCurrHp() << " / "   << monster[i].getMaxHp() << endl;
    }
    ss  << endl << " ============================" << endl;
    
    return ss.str();
}
void Dungeon::showStat(vector<Hero> heros){
    system("clear");
    cout << statToString(heros);
}
