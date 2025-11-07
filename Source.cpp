#include <iostream> 
#include "windows.h" 
#include "BaseClass.h" 
#include "StartClass.h" 
#include "Evil.h" 

using namespace std;

//модификаторы доступа: 
// private - приватный, запрещает доступ к свойствам и классам 
//           за пределами самого класса 
// protected - защищенный, можно передавать свойства и методы 
//        в классы наследники, но все еще нельзя использовать 
//        в основном потоке программы 
// public - публичный, общедоступный, можно использовать везде 

//базовый класс - абстрактный (класс у которого все методы виртуальные) 

enum class ValueQuality
{
    мусор=0, обычное, редкое, мифическое, легедарное
};

struct Treasure
{
    string name{ "добыча" };
    ValueQuality quality = ValueQuality::мусор;
    unsigned int price{ 0 };
    
    Treasure(ValueQuality quality)
    {
        switch (quality)
        {
        case ValueQuality::мусор:
            cout << "качество плохое\n";
            break;
        case ValueQuality::обычное:
            cout << "качество средненькое\n";
            break;
        case ValueQuality::редкое:
            cout << "качество хорошее\n";
            break;
        case ValueQuality::мифическое:
            cout << "качество крутое\n";
            break;
        case ValueQuality::легедарное:
            cout << "качество идеальное\n";
            break;
        default:
            break;
        }
    }  // добавлена закрывающая скобка для конструктора
};

// Убрана дублирующая структура Treasure

struct Cloth : Treasure
{
    string valueSite[5]{ "обувь"," перчатки", "шлем", "нагрудник", "пояс" };
    string site{ "" };  // исправлено: было NULL для string
    unsigned short armor{ 1 };
    
    // Добавлен конструктор для инициализации базового класса
    Cloth() : Treasure(ValueQuality::мусор) {}
};

int main()  // исправлено: убрана точка с запятой после main()
{
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Warrior* warrior = new Warrior();
    Warrior* warrior2 = new Warrior();
    cout << (*warrior == *warrior2) << endl;

    Wizard* wizard = new Wizard();
    Paladin* paladin = new Paladin();
    Player* player = new Player();

    cout << "Привет, путник\nПрисядь у костра и расскажи о себе\n";
    cout << "Ты впервые тут? (1 - новый персонаж, 2 - загрузить)\n";
    unsigned short choise = 1;
    cin >> choise;
    while (choise > 2 || choise < 1)
    {
        cout << "Наверное ты ошибся, повтори снова\n";
        cin >> choise;
    }
/*
    Treasure treasure;
    treasure.name = "древняя тарелка";
    treasure.price = 30;
    treasure.quality = treasure.valueQuality[3];
    cout << treasure.name << '\n' << treasure.price << '\n' << treasure.quality << '\n';
*/
    Cloth cloth;

    cloth.armor = 10;
    cloth.site = cloth.valueSite[2];
    cloth.name = "Шлем властелина подземелий";
    cloth.price = 50;
    cout << cloth.name << '\n' << cloth.site << '\n' << cloth.armor << '\n' << cloth.price << '\n';

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

    if (choise == 1)
    {
        cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n";

        // тут будет вызвана функция 
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
            delete wizard;
            wizard = nullptr;
            delete paladin;
            paladin = nullptr;
            break; }
        case 2: {
            player->Create(wizard);
            delete warrior;
            warrior = nullptr;
            delete paladin;
            paladin = nullptr;
            cout << " " << endl;
            break; }
        case 3: {
            player->Create(paladin);
            delete warrior;
            warrior = nullptr;
            delete wizard;
            wizard = nullptr;
            break; }
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

    return 0;
}
