/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//                                                                                                                            //
//  idleRPG                                                                                                                   //
//                                                                                                                            //
//  Player can explore dungeon with up to three heros in team.                                                                //
//  At the begining of game, first hero hit Lv15 and Lv30,                                                                    //
//  One of Three majors, Mage, Warrior, Priest, will be randomly generated and added to team.                                 //
//  Combat is automatic, information will be displayed after each turn of attack.                                             //
//                                                                                                                            //
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * MENU CHOICE * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//                                                                                                                            //
//  Status:      dispalys each hero's status                                                                                  //
//  Inventory:   displays items and golds in inventory, and apply weapon and armor, it is shared buy all heros in team        //
//  Shop:        provides weapon and armor for heros to gain attack or HP. Refreshed each time visit                          //
//  Dungeon:     provides monsters of the range from Lv.1 to Lv.50,                                                           //
//               the number of monsters will be equal to or 1 ~ 2 greater than the number of heros in team                    //
//               player choose dungeon level and how many time to explore, combat will be done automaticly                    //
//               exp and golds will be gain when victory, 1/10 amout will be earnd if only partial monsters are defeat        //
//               no exp nor golds if heros team is defeat                                                                     //
//  Save:        saves up to 10 selected hero's status into file.                                                             //
//               function of saving inventory is temporarily unavailable due to ``lack of time``                              //
//               * known bug *: old record will be earased on first time of saving.                                           //
//                              if you have records, load it first before tring to save new records when you start your game  //
//  Load:        loads records from file. Number of record can be loaded is base on number of heros in team                   //
//               will be improved in future                                                                                   //
//  Quit:        exit the game, save will be called before exiting                                                            //
//                                                                                                                            //
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * MENU CHOICE * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//                                                                                                                            //
//  Created by ZHIHAN LIN on 4/17/20.                                                                                         //
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.                                                                         //
//                                                                                                                            //
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <ctime>
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    srand(time(0));
    Game game;
    game.createHero();
    
    while (game.getPlaying()) {
        game.menu();
        
    }
    
    return 0;
}
