#include "BaseClass.h"

string Npc::GetName()
{
    return name;
}
unsigned int Npc::GetHealth()
{
    return health;
}
float Npc::GetDamage()
{
    return damage;
}
unsigned int Npc::GetLvl()
{
    return lvl;
}
void Npc::GetInfo() //метод класса
{
    cout << "»м€ - " << name << endl;
    cout << "«доровье - " << health << endl;
    cout << "”рон - " << damage << endl;
}
bool Npc::Save()
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
Npc Npc::Load()
{
    ifstream loadSystem("save.bin", ios::binary);
    Npc npc; //временное хранилище дл€ считывани€ данных из файла
    if (loadSystem.is_open())
    {
        loadSystem.read(reinterpret_cast<char*>(&npc.name), sizeof(npc.name));
        loadSystem.read(reinterpret_cast<char*>(&npc.health), sizeof(npc.health));
        loadSystem.read(reinterpret_cast<char*>(&npc.damage), sizeof(npc.damage));
        loadSystem.read(reinterpret_cast<char*>(&npc.lvl), sizeof(npc.lvl));
    }
    else
    {
        cout << "св€зь с базой нарушена\nѕам€ть утерена" << endl;
        return npc;
    }
    loadSystem.close();
    return npc;


};
void Player::Create(Npc* player)
{
    player->Create();
}
void Player::Save(Npc* player)
{
    player->Save();
}
void Player::Load(Npc* player)
{
    player->Load();
}
