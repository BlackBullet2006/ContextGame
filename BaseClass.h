#pragma once
#include <iostream> 
#include <fstream> 

using namespace std;

class Npc
{
protected: //модификатор 0 защищенный (дает доступ внутри класса родителя и наследника) 
    //но все еще не дает доступ в основном потоке программы 

    string name{ "персонаж" };
    unsigned int health{ 10 };
    float damage{ 5 };
    unsigned short lvl{ 1 };

public:    //публичный модификатор доступ (использовать метод можно в любом месте) 
    string GetName();
    unsigned int GetHealth();
    float GetDamage();
    unsigned int GetLvl();
    virtual void GetInfo();

    virtual void Create() {};
    virtual bool Save();

    Npc Load();




};
class Player
{
public:
    void Create(Npc* player);
    void Save(Npc* player);
    void Load(Npc* player);

};
