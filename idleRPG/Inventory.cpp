//
//  Inventory.cpp
//  idleRPG
//
//  Created by ZHIHAN LIN on 4/18/20.
//  Copyright © 2020 ZHIHAN LIN. All rights reserved.
//

#include "Inventory.hpp"
Inventory::Inventory(){
    head = nullptr;
}
Inventory::~Inventory(){
    //  to move through inventory
    Inven *itemPtr;
    
    //  point to the next item
    Inven *nextItem;
    
    //  position itemPtr at the head of inventory
    itemPtr = head;
    
    //  while itemptr is not at the end of inventory
    while (itemPtr != nullptr) {
        //  save a pointer to the next item
        nextItem = itemPtr->next;
        
        //  delete current item
        delete itemPtr;
        
        //  position itemPtr at the next item
        itemPtr = nextItem;
    }
}


void Inventory::appandItem(const Item &obj){
    //  to point to a new item
    Inven *newItem;
    //  to move through inventory
    Inven *invenPtr;
    
    //  allocate a new space in inventory and store Item there
    newItem = new Inven;
    newItem->item = obj;
    newItem->next = nullptr;
    
    //  if list is empty, make newItem hte first item
    if(!head){
        head = newItem;
    }
    //  otherwise, insert newItem at the end
    else{
        //  Initialize invenPtr to head of inventory
        invenPtr = head;
        
        //  find the last item in the inventory
        while (invenPtr->next) {
            invenPtr = invenPtr->next;
        }
        
        //  insert newItem at the end
        invenPtr->next = newItem;
    }
}
void Inventory::insertItem(const Item &obj){
    //  potint to a new item
    Inven *newItem;
    //  to go through inventory
    Inven *itemPtr;
    //  point to previousItem
    Inven *previousItem = nullptr;
    
    //  allocate a new space in inventory and store item there
    newItem = new Inven;
    newItem->item = obj;
    
    //  if list is empty, make newItem hte first item
    if(!head){
        head = newItem;
    }
    //  othewise, insert newItem
    else{
        //  position itemPtr at the head of list
        itemPtr = head;
        
        //  Initialize previousItem to nullptr
        previousItem = nullptr;
        
        //  insert item alphabetically by its name
        while (itemPtr != nullptr && itemPtr->item.getName() < obj.getName()){
            previousItem = itemPtr;
            itemPtr = itemPtr->next;
        }
        
        //  if the new item is to be the first in the inventory, insert it before all other items
        if(previousItem == nullptr){
            head = newItem;
            newItem->next = itemPtr;
        }
        // otherwise insert after the previous
        else{
            previousItem->next = newItem;
            newItem->next = itemPtr;
        }
    }
    
    
}
void Inventory::deleteItem(const string &name, const int &level, const int &qt){
    //  to go through the inventory
    Inven *itemPtr;
    //  to point to the previous item
    Inven * previousItem = nullptr;
    
    //  if the invnetory is empty, nothing happands
    if(!head)
        return;
    
    //  determine if the first node is the one.
    if(head->item.getName() == name){
        //  if item is used up, delete it from inventory
        if ((head->item.getQt() - qt) <= 0) {
            itemPtr = head->next;
            head = itemPtr;
        }
        //  otherwise decrese its quantity
        else{
            head->item.setQt(head->item.getQt() - qt);
        }
    }else{
        //  Initialize itemPtr to head of inventory
        itemPtr = head;
        
        //  skip all items whose name is not same to obj
        while (itemPtr != nullptr && (itemPtr->item.getName() != name && itemPtr->item.getLevel() != level)){
            previousItem = itemPtr;
            itemPtr = itemPtr->next;
        }
        //  if itemptr is not at the end of the inventory, link the previous item to hte item after itemPtr, then delete itemPtr
        if (itemPtr){
            if ((itemPtr->item.getQt() - qt) <= 0) {
                previousItem->next = itemPtr->next;
                delete itemPtr;
            }else{
                itemPtr->item.setQt(itemPtr->item.getQt() - qt);
            }
        }
    }
    
}
void Inventory::displayInventory(){
    //  to go through the inventory
    Inven *itemPtr;
    
    //  position itemPtr at the head of the inventory
    itemPtr = head;
    //  while itemPtr points to a item, go through the inventory
    while (itemPtr) {
        //  display the item itemPtr points to
        cout << "  " << itemPtr->item << endl;
        
        //  move to the next item
        itemPtr = itemPtr->next;
    }
}

Item* Inventory::searchEquipment(const string &name, const int &level){
    
    //  to go through the inventory
    Inven *itemPtr = nullptr;
    //  to point to the previous item
    Inven *previousItem = nullptr;
    
    //  if the invnetory is empty, return "none" item
    if(!head)
        return &this->none;
    
    //  determine if the first item is the one.
    if(head->item.getName() == name){
        //  if so, return the address of item
        return &head->item;
        
    }else{
        //  Initialize itemPtr to head of inventory
        itemPtr = head;
        
        //  skip all items whose name is not match
        while (itemPtr != nullptr && (itemPtr->item.getName() != name && itemPtr->item.getLevel() != level)){
            previousItem = itemPtr;
            itemPtr = itemPtr->next;
        }
        //  return the address found
        if (itemPtr){
            return &itemPtr->item;
        }
    }
    //  if nothing match, return "none" item
    return &this->none;
}
