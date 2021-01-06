//
//  Game.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/17/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Game.hpp"

Game::Game(){
    
}
Game::~Game(){
    
}
void Game::menu(){
    //  if first hero hit level 20, found a random major team mate
    if (heros[0].getLevel() >= 15 && lv15Recruitment){
        createHero();
        lv15Recruitment = false;
    }
    //  if first hero hit level 30, found another random major team mate
    else if (heros[0].getLevel() >= 30 && lv30Recruitment){
        createHero();
        lv30Recruitment = false;
    }
    
    system("clear");
    cout << "\t  M E N U\n"        << endl;
    cout << "\t  1. Status"        << endl;
    cout << "\t  2. Iventory"      << endl;
    cout << "\t  3. Shop"          << endl;
    cout << "\t  4. Dungeon"       << endl;
    cout << "\t  5. Save"          << endl;
    cout << "\t  6. Load"          << endl;
    cout << "\t  7. Quit"          << endl;
    
    //  validate user's choice
    choiceBetween(1, 7);
    cout << endl;
    switch (choice) {
        //  display hero's status
        case 1:{
            system("clear");
            cout << heros.size() << " hero(s) in team" << endl << endl;
            for (int i = 0; i < heros.size(); i++)  heros[i].showStatus();
            pause();
        break;
        }
        //  display inventory, apply equipment
        case 2:{
            system("clear");
            //  display inventory
            menu_inventory();
            //  local variables used for searching euipment on inventory
            string itemName = "";
            int itemLevel = 0;
            
            cout << "  Do you want to apply a equipment for hero?" << endl
                 << "  1. Weapon   2.Armor  3.Main Menu"           << endl;
            //  user choice with validation
            choiceBetween(1, 3);
            while (choice != 3) {
                tryAgain = true;
                while (tryAgain) {
                    cout << "  For which hero?"                    << endl
                         << "  =========================="         << endl;
                    //  diplay brief hero status
                    for (int i = 0; i < heros.size(); i++) {
                        cout << "  " << i + 1 << ". " << setfill(' ')
                             << left  << setw(8) << heros[i].getName() << heros[i].getMajor()
                             << right << setw(6) << "Lv." << heros[i].getLevel() << endl;
                    }
                    cout << "  ==========================" << endl << endl;
                    
                    choiceBetween(1, heros.size());
                    cout << "  Enter the name of equipment: ";
                    cin >> itemName;
                    cout << "  Enter the level of equipenmt: ";
                    cin >> itemLevel;
                    //  search function return a item named "N/A" if no match item was found
                    if (backPack.searchEquipment(itemName, itemLevel)->getName() != "N/A") {
                        if(choice == 1){
                            //  apply weapon to desired hero
                            menu_applyWeapon(choice, itemName, itemLevel);
                        }else if (choice == 2){
                            //  apply weapon to desired hero
                            menu_applyArmor(choice, itemName, itemLevel);
                        }
                    }else{
                        cout << "  Not match equipment was found"   << endl;
                    }
                    cout << "  Apply equipment for another hero? "  << endl
                         << "  1. Yes   2. No"                      << endl;
                    choiceBetween(1, 2);
                    if (choice == 2){
                        //  choice = 3 will break the while loop, then back to menu
                        choice = 3;
                    }
                }
            }
            pause();
            break;
        }
        //  open up a shop, sell and buy items
        case 3:{
            //  temporarily store name and quantity for selling
            string itemName;
            int itemLevel;
            int qt;
            int goldEarned;
            //  open up a shop base on hero's level
            Shop shop(heros[0].getLevel());
            
            tryAgain = true;
            while (tryAgain) {
                system("clear");
                //  display all Items on shop's shelf
                shop.displayShelf();
                cout << "  Golds: " << heros[0].getGold() << endl << endl;
                cout << "  Do you want to sell or buy? "  << endl
                     << "  1. Sell  2. Buy  3. Menu"      << endl;
                //  choice with validation
                choiceBetween(1, 3);
                switch (choice) {
                    //  sell
                    case 1:{
                        system("clear");
                        bool tryAgain = true;
                        //  display inventory
                        menu_inventory();
                        cout << "  Which do you want sell? enter item name and quantity: " << endl;
                        while (tryAgain) {
                            cout << setfill(' ');
                            cout << left << setw(6) << "  Name: ";
                            cin  >> itemName;
                            cout << left << setw(6) << "  Level(enter 0 for item other than equipment): ";
                            cin  >> itemLevel;
                            cout << left << setw(6) << "  Qt: ";
                            cin  >> qt;
                            //  sell items for golds
                            goldEarned = shop.sell(backPack, itemName, itemLevel, qt);
                            //  deposit golds
                            heros[0].setGold(heros[0].getGold() + goldEarned);
                            cout << "  -- Gold + " << goldEarned  << " --" << endl << endl;
                            cout << "  Anything else to sell?"             << endl
                                 << "  1. Yes   2.No"                      << endl;
                            choiceBetween(1, 2);
                            if (choice == 2)  tryAgain = false;
                            }
                        this->tryAgain = true;
                        break;
                    }
                    //  buy
                    case 2:{
                        int index = 0;
                        tryAgain = true;
                        while (tryAgain) {
                            system("clear");
                            shop.displayShelf();
                            cout << "  Golds: " << heros[0].getGold()   << endl << endl;
                            cout << setfill(' ');
                            cout << left << setw(6) << "  Enter Item#: ";
                            cin  >> index;
                            if (heros[0].getGold() >= shop.shelf[index - 1].getBuyValue() * shop.shelf[index - 1].getQt()) {
                                shop.purchase(heros, backPack, index);
                            }else{
                                cout << "  -- Insufficient golds --"   << endl << endl;
                            }
                            cout << "  Anything else want to buy?"     << endl
                                 << "  1. Yes   2.No"                  << endl;
                            choiceBetween(1, 2);
                            if (choice == 1)  tryAgain = true;
                        }
                        this->tryAgain = true;
                        break;
                    }
                    //  main menu
                    case 3:
                        tryAgain = false;
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        //  combat, level up, earn golds
        case 4:{
            int times = 0;
            system("clear");
            cout << " \t = DUNGEON ="        << endl
                 << "\t  ------------------ "  << endl
                 << "\t | 1.  Lv1  ~ Lv5   |"  << endl
                 << "\t | 2.  Lv6  ~ Lv10  |"  << endl
                 << "\t | 3.  Lv11 ~ Lv15  |"  << endl
                 << "\t | 4.  Lv16 ~ Lv20  |"  << endl
                 << "\t | 5.  Lv21 ~ Lv25  |"  << endl
                 << "\t | 6.  Lv26 ~ Lv30  |"  << endl
                 << "\t | 7.  Lv31 ~ Lv35  |"  << endl
                 << "\t | 8.  Lv36 ~ Lv40  |"  << endl
                 << "\t | 9.  Lv41 ~ Lv45  |"  << endl
                 << "\t | 10. Lv46 ~ Lv50  |"  << endl
                 << "\t | 0.  Main Menu    |"  << endl
                 << "\t  ------------------ "  << endl
                 << "  Where'd you wanna go? How much you wanna risk?" << endl;
            
            //  validate user's choice
            choiceBetween(0, 10);
            cout << "How many times? ";
            do {
                cin >> times;
                if (times <= 0) cout << "Be serious!!" << endl;
            }while (times <= 0);
           
            //  combat for desired times
            if(choice != 0){
                for (int i = 0; i < times; i++){
                Dungeon dungeon((choice * 5) - 4, choice * 5, heros);
                dungeon.combat(heros);
                }
            }
            pause();
            break;
        }
        case 5:
            save();
            break;
        case 6:
            load();
            break;
        case 7:{
            setPlaying(false);
            save();
            break;
        }
        default:
            break;
    }
}
//  get user's input with validation
void Game::choiceBetween(const int &begin, const int &end){
    this->tryAgain = true;
    while (this->tryAgain) {
        try {
            cout << "  Choice: ";
            cin >> this->choice;
            if (this->choice < begin | this->choice > end) throw InvalidMenuChoice(this->choice);
            tryAgain = false;
        }catch (InvalidMenuChoice e){
            cout << " " << e.getValue() << " is no a valid menu choice dude!" << endl;
        }
    }
}
//  display inventory
void Game::menu_inventory(){
    cout << "  =========Inventory=====" << endl;
    backPack.displayInventory();
    cout << "\n   Gold: " << heros[0].getGold() << endl;
    cout << "  " << right << setfill('=') << setw(19) << "" << endl << endl;
}

//  apply weapon for selected hero
void Game::menu_applyWeapon(const int&index, string &itemName, int &itemLevel){
        //  take off current weapon and store it into inventory
        backPack.appandItem(heros[choice - 1].takeOffWeapon());
        //  remove weapon form inventory
        backPack.deleteItem(itemName,itemLevel ,1);
        //  apply new weapon
        heros[index - 1].applayWeapon(Weapon(itemName, itemLevel));
        //  update hero's status after applying new weapon
        heros[index - 1].updateStatus();
}
//  apply armor for selected hero
void Game::menu_applyArmor(const int&index, string &itemName, int &itemLevel){
        //  take off current armor and store it into inventory
        backPack.appandItem(heros[choice - 1].takeOffArmor());
        //  remove armor form inventory
        backPack.deleteItem(itemName,itemLevel ,1);
        //  apply new armor
        heros[index - 1].applayArmor(Armor(itemName, itemLevel));
        //  update hero's status after applying new armor
        heros[index - 1].updateStatus();
}



//  create a hero and insert to the team
void Game::createHero(){
    system("clear");
    string name = " ";
    string major = " ";
    cout << "  ********************" << endl
         << "  *     New Hero     *" << endl
         << "  ********************" << endl;
    cout << "  Give it a name: ";
    cin  >> name;
    
    //  roll a random major between mage, warrior, priest
    switch ((rand() % 3) + 1) {
        case 1:
            major = "Mage";
            break;
        case 2:
            major = "Warrior";
            break;
        case 3:
            major = "Priest";
            break;
        default:
            break;
    }
    heros.push_back(Hero(name, major));
}

//  save all heros into text file
void Game::save(){
    herosOut.open("/Users/Shared/Previously Relocated Items/Security/C++/idleRPG/HerosData.txt", ios::out);
    //  read file to check any exist record,
    herosIn.open("/Users/Shared/Previously Relocated Items/Security/C++/idleRPG/HerosData.txt", ios::in);
    if (!herosIn) {
        cout << "invalid path" << endl;
    }
    // if so, temporarily store them in quque to limit the total number of records within 10
    while (getline(herosIn, record).good()) {
        herosRecords.push_back(record);
    }
    system("clear");
    for (it = heros.begin();it != heros.end(); it++) {
        cout << "  -------------------------"         << endl << " "
             << it->getName()  << " - "
             << it->getMajor() << " - Lv."
             << it->getLevel() << endl
             << "  -------------------------"         << endl;
        cout << "  Do you want to save this record? " << endl
             << "\t1. Yes\t2.No\t 3.Main Menu"      << endl;
        // validate user's choice
        choiceBetween(1, 3);
        //  process choice
        switch (choice) {
            //  yes
            case 1:{
                //  cover current hero by record
                if (herosRecords.size() >= 10) {
                    herosRecords.pop_front();
                    herosRecords.push_back(it->stringToSave());
                }else{
                    herosRecords.push_back(it->stringToSave());
                }
                break;
            }
            //  no
            case 2:{
                break;
            }
            // back to main menu
            case 3:{
                it = heros.end();
                break;
            }
            default:
                break;
        }
    }
   
    //  write out records from the begining of file
    herosOut.seekp(0L, ios::beg);
    for (auto it = herosRecords.begin(); it != herosRecords.end(); it++) {
        herosOut << *it;
    }
    herosIn.close();
    herosOut.close();
}

//  load hero record into selected hero
void Game::load(){
    Hero tempHero;
    bool nextRecord = true;
    
    herosIn.open("/Users/Shared/Previously Relocated Items/Security/C++/idleRPG/HerosData.txt", ios::in);
    if (herosIn.fail()) {
        cout << "invalid path or file does exist" <<endl;
    }
    //  go through all heros
    for (it = heros.begin(); it != heros.end(); it++) {
        choice = 0;
        system("clear");
        //  display curren  hero
        cout << "  Loading record ---> "<< it->getName() << endl;
        //  back to the begining of file
        herosIn.seekg(0L, ios::beg);
        do{
            cout << " " << endl;
            if (!herosIn.eof()) {
                //  read record into temporary hero
                herosIn >> tempHero;
                tempHero.updateStatus();
                
                cout << "  -------------------------"         << endl << " "
                     << tempHero.getName()  << " - "
                     << tempHero.getMajor() << " - Lv."
                     << tempHero.getLevel() << endl
                     << "  -------------------------"         << endl;
                cout << "  Do you want to load this record? " << endl
                     << "\t1. Yes\t2.No\t 3.Main Menu"      << endl;
                // validate user's choice
                choiceBetween(1, 3);
                //  process choice
                switch (choice) {
                    //  yes
                    case 1:{
                        //  cover current hero by record
                        *it = tempHero;
                        it->updateStatus();
                        nextRecord = false;
                        break;
                    }
                    //  no
                    case 2:{
                        nextRecord = true;
                        break;
                    }
                    // back to main menu
                    case 3:{
                        nextRecord = false;
                        break;
                    }
                    default:
                        break;
                }
            //  If reach end of file, no more records
            }else{
                nextRecord = false;
                cout << "No more records" << endl;
            }
        }while (!herosIn.eof() && nextRecord);
        pause();
    }
    herosIn.close();
}

//  pause screen
void Game::pause(){
    cout << "Press enter to continue..." << endl;
    cin.ignore();
    cin.get();
}
