#include <iostream>
#include "windows.h"
#include "BaseClass.h"
#include "StartClass.h"
#include "Evil.h"

using namespace std;


//фабрика для создания персонажей

enum class CharacterType {
    UNKNOWN = 0,
    WARRIOR,
    WIZARD,
    PALADIN
};

unique_ptr<Npc> CreateCharacter(CharacterType type)
{
    switch (type)
    {
    case CharacterType::UNKNOWN:
        return make_unique<Npc>();
        break;
    case CharacterType::WARRIOR:
        return make_unique<Warrior>();
        break;
    case CharacterType::WIZARD:
        return make_unique<Wizard>();
        break;
    case CharacterType::PALADIN:
        return make_unique<Paladin>();
        break;
    default:
        invalid_argument("Неизвестный тип персонажа");
        break;
    }
}






























//модификаторы доступа:
// private - приватный, запрещает доступ к свойствам и классам
//           за пределами самого класса
// protected - защищенный, можно передавать свойства и методы
//        в классы наследники, но все еще нельзя использовать
//        в основном потоке программы
// public - публичный, общедоступный, можно использовать везде


//базовый класс - абстрактный (класс у которого все методы виртуальные)



int main()
{
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

   /* Warrior* warrior = new Warrior();
    Warrior* warrior2 = new Warrior();
    cout << (*warrior == *warrior2) << endl;

    Wizard* wizard = new Wizard();
    Paladin* paladin = new Paladin();
    */
    Player* player = new Player();

    cout << "Привет, путник\nПрисядь у костра и расскажи о себе\n";
    cout << "Ты впервые тут? (1 - новый персонаж, 2 - загрузить)\n";
    

    /*
    unsigned short maxChoise = 3;
    unsigned short TestChoise(unsigned short maxChoise, string text);
    {
        unsigned short choise = 1;
        cin >> choise;
        while (choise > maxChoise || choise < 1)
        {
            cout << "Наверное ты ошибся, повтори снова\n";
            cin >> choise;
        }
        return choise;


    };

    */

  
     if (TextChoise(2, "Наверное ты ошибся, повтори снова"))
     {
         cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n";
         unique_ptr<Npc> character;

         switch (TextChoise(3, "Такого еще не было в наших краях\nНе мог бы ты повторить\n"))
         {
         case 1:
                 character = CreateCharater(CharacterType::WARRIOR);
                 break;
         case 2: 
             character = CreateCharater(CharacterType::WIZARD);
             break;
         case 3:
             character = CreateCharater(CharacterType::PALADIN);
             break;


     

/*
        switch (choise)
        {
        case 1: {
            player->Create(warrior);
            delete wizard;
            wizard = nullptr;
            delete paladin;
            paladin = nullptr;
            break;
        }
        case 2: {
            player->Create(wizard);
            delete warrior;
            warrior = nullptr;
            delete paladin;
            paladin = nullptr;
            cout << " " << endl;
            break;
        }
        case 3: {
            player->Create(paladin);
            delete warrior;
            warrior = nullptr;
            delete wizard;
            wizard = nullptr;
            break;
        }
        }

    }

    else
    {
        player->Load(warrior);
    }

    cout << "сделаем остановку тут?\n\t1 - сохранить игру\n\t2 - продолжить\n";
    cin >> choise;
    if (choise == 1)
    {
        if (warrior != nullptr) player->Save(warrior);
        if (wizard != nullptr) player->Save(wizard);
        if (paladin != nullptr) player->Save(paladin);
    }
*/


    return 0;
}
