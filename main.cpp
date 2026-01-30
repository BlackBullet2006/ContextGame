#include <iostream>
#include "windows.h"
#include "GameClasses.h"
#include "BaseClasses.h"
#include "Evil.h"
#include <fstream> 
using namespace std;

enum class ValueQuality
{
    мусор, обычное, редкое, мифическое, легендарное
};

struct Treasure
{
    Treasure() = default;
    string name{ "добыча" };
    ValueQuality quality = ValueQuality::мифическое;
    unsigned int price{ 0 };
    Treasure(ValueQuality quality)
    {
        switch (quality)
        {
        case ValueQuality::мусор:
            cout << "качество плохое\n";
            break;
        case ValueQuality::обычное:
            cout << "качество нормальное\n";
            break;
        case ValueQuality::редкое:
            cout << "качество хорошее\n";
            break;
        case ValueQuality::мифическое:
            cout << "качество отличное\n";
            break;
        case ValueQuality::легендарное:
            cout << "качество идеальное\n";
            break;
        default:
            break;
        }
    }
};

struct Cloth : Treasure
{
    Cloth(ValueQuality quality) : Treasure(quality) {};
    string valueSite[5]{ "обувь", "перчатки", "шлем", "нагрудник", "пояс" };
    string site{ NULL };
    unsigned short armor{ 1 };
};

enum class CharacterType {
    UNKNOWN = 0,
    WARRIOR,
    WIZARD,
    PALADIN
};

enum class EnemyType {
    АРНОЛЬД_НЕШВАРЦ = 1,
    НАГЛЫЙ_ДОББИ,
    СТАРЫЙ,
    БАБУЛЯ_ИЗ_КАЧАЛКИ,
    УБОРЩИЦА_ЛЮБА,
};

unsigned short TestChoise(unsigned short maxChoise, string text)
{
    unsigned short choise = 1;
    cin >> choise;
    while (choise > maxChoise || choise < 1)
    {
        cout << text << endl;
        cin >> choise;
    }
    return choise;
};

// основа для создания персонажей
static unique_ptr<Npc> CreateCharacter(CharacterType type)
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
        throw invalid_argument("неизвестный тип персонажа");
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Player* player = new Player();

    cout << "Привет, путник\nприсядь у костра и расскажи о себе\nТы впервые тут?\n\t1 - новый персонаж,\n\t2 - загрузить\n";
    if (TestChoise(2, "Наверное ты ошибся, повтори снова"))
    {
        cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник \n\t3 - Паладин\n";
        unique_ptr<Npc> character;
        switch (TestChoise(3, "Такого еще не было в наших краях\nНе мог бы ты повторить"))
        {
        case 1:
            character = CreateCharacter(CharacterType::WARRIOR);
            break;
        case 2:
            character = CreateCharacter(CharacterType::WIZARD);
            break;
        case 3:
            character = CreateCharacter(CharacterType::PALADIN);
            break;
        }
        player->Create(move(character));
    }
    else
    {
        ifstream loadSystem("save.txt", ios::binary);
        if (!loadSystem.is_open())
        {
            cout << "Связь с космосом потеряна\nПамять о ваших прошлых путешествиях повреждена\n";
        }
        else
        {
            //реализация загрузки
        }


    }

    // НАЧАЛО СЮЖЕТА
    cout << "\n--- НАЧАЛО ПРИКЛЮЧЕНИЯ ---\n";
    cout << "Вы встречаете врага - Наглый Добби!\n";
    cout << "Он требует у вас носки.\n\n";

    cout << "Ваши действия:\n";
    cout << "1 - Отдать носки\n";
    cout << "2 - Отказаться\n";
    cout << "3 - Атаковать Добби\n";

    unsigned short battleChoice = TestChoise(3, "Выберите вариант от 1 до 3:");

    if (battleChoice == 1)
    {
        cout << "Вы отдаете носки. Добби доволен и уходит.\n";
    }
    else if (battleChoice == 2)
    {
        cout << "Вы отказываетесь. Добби обижается и убегает.\n";
    }
    else
    {
        cout << "Вы атакуете Добби! Он испуганно убегает.\n";
    }

    cout << "\nПоздравляем! Вы успешно завершили первую встречу.\n";
    cout << "Возвращаемся в таверну...\n\n";
    // КОНЕЦ ДОБАВЛЕННОГО КОДА СЮЖЕТА

    //процесс игры

    //процесс игры

    cout << "Сделаем остановку тут?\n\t1 - сохранить игру\n\t2 - продолжить\n";
    if (TestChoise(2, "Нужно четко определиться с решением\nПовтори свой ответ"))
    {
        if (player->Save()) {
            cout << "Игра успешно сохранена!\n";
        }
        else {
            cout << "Ошибка сохранения.\n";
        }
    }
    return 0;
}

