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
    string GetName()
    {
        return name;
    }
    unsigned int GetHealth()
    {
        return health;
    }
    float GetDamage()
    {
        return damage;
    }
    unsigned int GetLvl()
    {
        return lvl;
    }
    virtual void GetInfo() //метод класса
    {
        cout << "Имя - " << name << endl;
        cout << "Здоровье - " << health << endl;
        cout << "Урон - " << damage << endl;
    }
    
    virtual void Create() {};
    virtual bool Save() 
    {
    
        ofstream saveSystem("save.bin", ios::binary);
        if (saveSystem.is_open()) 
        {
            saveSystem.write(reinterpret_cast<const char*>(&name), sizeof(name));
            saveSystem.write(reinterpret_cast<const char*>(&health), sizeof(health));
            saveSystem.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
            saveSystem.write(reinterpret_cast<const char*>(&lvl), sizeof(lvl));
            saveSystem.close();
            return true;
        }
        else
        {
            cout << "сохранение не удалось" << endl;
            return false;
        }
        saveSystem.close();
    };
    Npc Load() 
    {
        ifstream loadSystem("save.bin", ios::binary);
        Npc npc; //временное хранилище для считывания данных из файла
        if (loadSystem.is_open())
        {
            loadSystem.read(reinterpret_cast<char*>(&npc.name), sizeof(npc.name));
            loadSystem.read(reinterpret_cast<char*>(&npc.health), sizeof(npc.health));
            loadSystem.read(reinterpret_cast<char*>(&npc.damage), sizeof(npc.damage));
            loadSystem.read(reinterpret_cast<char*>(&npc.lvl), sizeof(npc.lvl));
        }
        else
        {
            cout << "связь с базой нарушена\nПамять утерена" << endl;
            return npc;
        }
        loadSystem.close();
        return npc;
    
    
    };



};
class Player
{
public:
    void Create(Npc* player)
    {
        player->Create();
    }
    void Save(Npc* player)
    {
        player->Save();
    }
    void Load(Npc* player)
    {
        player->Load();
    }
};
