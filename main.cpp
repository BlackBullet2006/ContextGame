#pragma once
using namespace std;
#include <iostream>
#include<fstream>
#include "windows.h"

//модификаторы доступа:
// private - приватный, запрещает доступ к свойствам и классам
//           за пределами самого класса
// protected - защищенный, можно передавать свойства и методы
//        в классы наследники, но все еще нельзя использовать
//        в основном потоке программы
// public - публичный, общедоступный, можно использовать везде


//базовый класс - абстрактный (класс у которого все методы виртуальные)
class Npc
{
protected: //модификатор 0 защищенный (дает доступ внутри класса родителя и наследника)
    //но все еще не дает доступ в основном потоке программы
    string name{
        "персонаж"
    };
    unsigned int health{10};
    float damage{5};
    unsigned short lvl{1};
public: //публичный модификатор доступ (использовать метод можно в любом месте)
    string GetName()
    {
        return name;
    }
    unsigned int GenHealth()
    {
        return health;
    }
    float GetDamage()
    {
        return damage;
    }
    unsigned short GetLvl()
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
    bool Save() {
        ofstream saveSystem("save.bin", ios::binary);
        if (saveSystem.is_open())
        {
            saveSystem.write(reinterpret_cast<const char*>(&name), sizeof(name));
            saveSystem.write(reinterpret_cast<const char*>(&health), sizeof(health));
            saveSystem.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
            saveSystem.write(reinterpret_cast<const char*>(&lvl), sizeof(lvl));
            //записали набор характеристик и сохранили
            saveSystem.close();
            return true;
        }
        else
        {
            cout << "Сохранение не удалось\nПопробуйе позже\n";
            return false;
        }
   
    };
    Npc Load() 
    {
        ifstream loadSystem("save.bin", ios::binary);
        Npc npc;//временное хранилище для считывания из файла
        if (loadSystem.is_open())
        {
            loadSystem.read(reinterpret_cast<char*>(&npc.name), sizeof(npc.name));
            loadSystem.read(reinterpret_cast<char*>(&npc.health), sizeof(npc.health));
            loadSystem.read(reinterpret_cast<char*>(&npc.damage), sizeof(npc.damage));
            loadSystem.read(reinterpret_cast<char*>(&npc.lvl), sizeof(npc.lvl));
            //записали набор характеристик и сохранили
        }
        else
        {
            cout << "Связь с небесами нарушена\nПамять о ваших прошых путешествиях повреждена\n";
            return npc;
        }
        loadSystem.close();
        return npc;
    };

};

//наследование - использование доступных свойств
// и методов класса родителям (parent), классом наследником(child)
class Warrior : protected virtual Npc //наследование с модификатором доступа public
{
protected: //модификатор 0 (приватный - защищенный, доступ к полям, только внутри класса)
    unsigned short strenght{
        31
    };
    string weapons[4] = {
        "кастет",
        "дубинка",
        "клинок",
        "меч"
    };
public:
    //конструктор - метод, который вызывается в момент создания экземпляра
    //класса (вручную вызвать в основном потоке программы не можем)

    Warrior() //конструктор по умолчанию, когда нет аргументов
    {
        name = "воин";
        health = 35;
        damage = 10;
    }
    //кастомный конструктор
    Warrior(string name, unsigned int health, float damage)
    {
        cout << "кастомный конструктор война" << endl;
        this->name = name;
        this->health = health;
        this->damage = damage;
    }

    void GetWeapons()
    {
        cout << name << " взял в руки " << weapons[lvl - 1];
    }
    void GetInfo() override //полиморфизм (перегрузка для метода)
    {
        Npc::GetInfo();
        cout << "Сила - " << strenght << endl;
        cout << "Доступное оружие - ";
        for (int i = 0; i < lvl; i++)
        {
            cout << weapons[i] << endl;
        }
    }
    void Create() override
    {
        cout << "Вы создали война" << endl;
        cout << "Введите имя персонажа\t";
        cin >> name;
        GetInfo();
        GetWeapons();
    }
    //перегрузка операторов
    //перегрузка оператора сравнения (==)
    bool operator == (const Warrior& warrior) const
    {
        return ((warrior.damage == this->damage) && (warrior.health == this->health) &&
            (warrior.strenght == this->strenght));
    }

    bool Save() override
    {
        if (Npc::Save))
        {
            ofstream saveSystem("save.bin", ios::binary | ios::app);
            if (saveSystem.is_open())
            {
                saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
                for (int i = 0; i < 4; i++)
                {
                    saveSystem.write(reinterpret_cast<const char*>(&weapons), sizeof(weapons));
                }
                //записали набор характеристик и сохранили
                saveSystem.close();
                return true;
            }
            else
            {
                cout << "Сохранение не удалось\nПопробуйе позже\n";
                return false;
            }
        }
    }
    //деструктор - метод, который вызывается автоматически при высвобождении памяти
    //при окончании работы с экземпляром класса (нельзя вызвать вручную)
    ~Warrior() //деструктор всегда без аргументов
    {
        cout << name << " пал смертью храбрых" << endl;
    }
};



//virtual - создает виртуализацию методов, классов
//при этом сам класс повторно не создается
class Wizard : public virtual Npc
{
protected: unsigned short intellect = 27;
         string spell[4] = {
             "вспышка",
             "магисческая стрела",
             "огненный шар",
             "метеоритный дождь"
         };
public: Wizard()
{
    name = "волшебник";
    health = 23;
    damage = 15;
}
      Wizard(string name, unsigned int health, float damage)
      {
          cout << "кастомный конструктор волшебника" << endl;
          this->name = name;
          this->health = health;
          this->damage = damage;
      }
      void GetInfo() override //полиморфизм (перегрузка для метода)
      {
          Npc::GetInfo();
          cout << "Интеллект - " << intellect << endl;
          cout << "Доступные заклинания в книге заклинаний - ";
          for (int i = 0; i < lvl; i++)
          {
              cout << spell[i] << endl;
          }
      }
      void CastSpell()
      {
          cout << name << "применяет " << spell[lvl - 1] << endl;
      }
      void Create() override
      {
          cout << "Вы создали волшебника" << endl;
          cout << "Введите имя персонажа\t";
          cin >> name;
          GetInfo();
          CastSpell();
      }
      Wizard operator + (const Wizard& wizard) const
      {
          return Wizard(
              this->name,
              (this->health + wizard.health),
              (this->damage + wizard.damage)
          );
      }
      bool Save() override
      {
          if (Npc::Save))
          {
              ofstream saveSystem("save.bin", ios::binary | ios::app);
              if (saveSystem.is_open())
              {
                  saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
                  for (int i = 0; i < 4; i++)
                  {
                      saveSystem.write(reinterpret_cast<const char*>(&spell), sizeof(spell));
                  }
                  //записали набор характеристик и сохранили
                  saveSystem.close();
                  return true;
              }
              else
              {
                  cout << "Сохранение не удалось\nПопробуйе позже\n";
                  return false;
              }
        }
      }

      ~Wizard() //деструктор всегда без аргументов
      {
          cout << name << " испустил дух" << endl;
      }
};

//множественное наследование
class Paladin : public Warrior, public Wizard
    //следующий родительственный класс добавляется через запятую
{
public: Paladin()
{
    name = "паладин";
    health = 25;
    damage = 12;
    strenght = 27;
}
      void GetInfo() override
      {
          Warrior::GetInfo();
          cout << "Интеллект - " << intellect << endl;
          cout << "Доступные заклинания в книге заклинаний - ";
          for (int i = 0; i < lvl; i++)
          {
              cout << spell[i] << endl;
          }
      }
      void Create() override
      {
          cout << "Вы создали паладина" << endl;
          cout << "Введите имя персонажа\t";
          cin >> name;
          GetInfo();
          CastSpell();
          GetWeapons();
      }
      bool Save() override
      {
          if (Npc::Save))
          {
              ofstream saveSystem("save.bin", ios::binary | ios::app);
              if (saveSystem.is_open())
              {
                  saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
                  for (int i = 0; i < 4; i++)
                  {
                      saveSystem.write(reinterpret_cast<const char*>(&weapons), sizeof(weapons));
                  }
                  //записали набор характеристик и сохранили
                  saveSystem.close();
                  return true;
              }
              else
              {
                  cout << "Сохранение не удалось\nПопробуйе позже\n";
                  return false;
              }
        }
      }
};

class Player
{
public: void Create(Npc* player)
{
    player->Create();
}
};

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Warrior* warrior = new Warrior();
    Warrior* warrior2 = new Warrior();


    cout << (*warrior == *warrior2) << endl;

    Wizard* wizard1 = new Wizard();
    Wizard* wizard2 = new Wizard();
    Wizard* megaWizard = new Wizard();
    *megaWizard = *wizard1 + *wizard2;
    megaWizard->GetInfo();


    Paladin* paladin = new Paladin();
    Player* player = new Player();

    cout << "Привет, путник\nПрисядь у костра и расскажи о себе\n";
    cout << "Ты впервые тут? (1 - новый персонаж, 2 - загрузить)\n";
    unsigned short choise = 1;
    //создать уникальную функцию для проверки условия выбора
    cin >> choise;
    while (choise > 2 || choise < 1)
    {
        cout << "Наверное ты ошибся, повтори снова\n";
        cin >> choise;
    }
    if (choise == 1)
    {
        cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин)";
        //-----------
        // тут уже будет вызвана ваша красивая функция
        cin >> choise;
        while (choise > 3 || choise < 1)
        {
            cout << "Такого еще не было в наших краях\nНе мог бы ты повторить\n";
            cin >> choise;
        }
        switch (choise)
        {
        case 1: {
          player->Create(warrior);
          delete megaWizard;
          megaWizard = nullptr;
          delete paladin;
          break; }
        case 2: {
          player->Create(megaWizard);
          delete warrior;
          megaWizard = nullptr;
          delete paladin;
          break; }
        case 3: {
          player->Create(paladin);
          delete warrior;
          megaWizard = nullptr;
          delete paladin;
          break; }
        }

    }
    else
    {
        warrior = player->Load(warrior);
    }
    {
        cout << "Нужно четко определиться с решением\nПовтори свой ответ\n";
        cin >> choise;
    }
    if (choise == 1)
    {
        if (warrior != nullptr)player->Save(warrior);
        if (warrior != nullptr)player->Save(megaWizard);
        if (warrior != nullptr)player->Save(paladin);
    }

    return 0;
