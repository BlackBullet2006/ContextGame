#include <iostream>
#include "windows.h"
#include <iostream>
#include "windows.h"
using namespace std;


unsigned short GetChoice(unsigned short min, unsigned short max, const string& message)
{
    unsigned short choice;
    cout << message;
    cin >> choice;

    while (choice < min || choice > max || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Неверный выбор, попробуй снова: ";
        cin >> choice;
    }

    return choice;
}


class Npc {
protected:
    string name{ "персонаж" };
    unsigned int health{ 10 };
    float damage{ 5 };
    unsigned short lvl{ 1 };

public:
    virtual void GetInfo() {
        cout << "Имя - " << name << endl;
        cout << "Здоровье - " << health << endl;
        cout << "Урон - " << damage << endl;
    }

    virtual void Create() {}
};


class Warrior : protected virtual Npc {
protected:
    unsigned short strenght{ 31 };
    string weapons[4] = { "кастет", "дубинка", "клинок", "меч" };

public:
    Warrior() {
        name = "воин";
        health = 35;
        damage = 10;
    }

    Warrior(string name, unsigned int health, float damage) {
        cout << "кастомный конструктор война" << endl;
        this->name = name;
        this->health = health;
        this->damage = damage;
    }

    void GetWeapons() {
        cout << name << " взял в руки " << weapons[lvl - 1] << endl;
    }

    void GetInfo() override {
        Npc::GetInfo();
        cout << "Сила - " << strenght << endl;
        cout << "Доступное оружие - ";
        for (int i = 0; i < lvl; i++) {
            cout << weapons[i] << " ";
        }
        cout << endl;
    }

    void Create() override {
        cout << "Вы создали воина" << endl;
        cout << "Введите имя персонажа: ";
        cin >> name;
        GetInfo();
        GetWeapons();
    }

    bool operator == (const Warrior& warrior) const {
        return ((warrior.damage == this->damage) && (warrior.health == this->health) && (warrior.strenght == this->strenght));
    }
    bool Save() override {
        if (Npc::Save()) {
            ofstream saveSystem("save.bin", ios::binary | ios::app);
            if (saveSystem.is_open()) {
                saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
                for (int i = 0; i < 4; i++)
                {
                    saveSystem

                }
            }

        }
    }

    ~Warrior() {
        cout << name << " пал смертью храбрых" << endl;
    }
};


class Wizard : protected virtual Npc {
protected:
    unsigned short intellect = 27;
    string spell[4] = { "вспышка", "магическая стрела", "огненный шар", "метеоритный дождь" };

public:
    Wizard() {
        name = "волшебник";
        health = 23;
        damage = 15;
    }

    Wizard(string name, unsigned int health, float damage) {
        cout << "кастомный конструктор волшебника" << endl;
        this->name = name;
        this->health = health;
        this->damage = damage;
    }

    void GetInfo() override {
        Npc::GetInfo();
        cout << "Интеллект - " << intellect << endl;
        cout << "Доступные заклинания - ";
        for (int i = 0; i < lvl; i++) {
            cout << spell[i] << " ";
        }
        cout << endl;
    }

    void CastSpell() {
        cout << name << " применяет " << spell[lvl - 1] << endl;
    }

    void Create() override {
        cout << "Вы создали волшебника" << endl;
        cout << "Введите имя персонажа: ";
        cin >> name;
        GetInfo();
        CastSpell();
    }

    Wizard operator + (const Wizard& wizard) const {
        return Wizard(this->name, (this->health + wizard.health), (this->damage + wizard.damage));
    }

    ~Wizard() {
        cout << name << " испустил дух" << endl;
    }
};


class Paladin : public Warrior, public Wizard {
public:
    Paladin() {
        name = "паладин";
        health = 25;
        damage = 12;
        strenght = 27;
    }

    void GetInfo() override {
        Warrior::GetInfo();
        cout << "Интеллект - " << intellect << endl;
        cout << "Доступные заклинания - ";
        for (int i = 0; i < lvl; i++) {
            cout << spell[i] << " ";
        }
        cout << endl;
    }


    void Create() override {
        cout << "Вы создали паладина" << endl;
        cout << "Введите имя персонажа: ";
        cin >> name;
        GetInfo();
        CastSpell();
        GetWeapons();
    }
};


class Player {
public:
    void Create(Npc* player) {
        player->Create();
    }
    void Save(Npc* player) {
        player->S();
    }
};


int main() {
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


    unsigned short choise = GetChoice(1, 2, "Ты впервые тут? (1 - новый персонаж, 2 - загрузить)\n> ");

    if (choise == 1) {
        choise = GetChoice(1, 3, "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n> ");

        switch (choise) {
        case 1:
            player->Create(warrior);
            delete wizard1; delete wizard2; delete paladin;
            break;
        case 2:
            player->Create(wizard1);
            delete warrior; delete paladin;
            break;
        case 3:
            player->Create(paladin);
            delete warrior; delete wizard1;
            break;
        }
    }

    cout << "Сделаем остановку тут?\n\t1 - сщхранить игру\n\t2 - продолжить\n";
    cin >> choise;
    while (choise > 2 || choise < 1)
    {
        cout << "Наверное ты ошибся , повтори снова\n";
        cin >> choise;
    }
    cout << "Сделаем остановку тут?\n\t1 - сохранить игру\n\t2 - продолжить\n";
    cin >> choise;
    while (choise > 2 || choise < 1) {
        cout << "Наверное ты ошибся , повтори снова\n";
        cin >> choise;
    }

    

    delete warrior;
    warrior = nullptr;
    delete warrior2;
    warrior2 = nullptr;
    delete wizard1;
    wizard1 = nullptr;
    delete wizard2;
    wizard2 = nullptr;
    delete megaWizard;
    megaWizard = nullptr;
    delete paladin;
    paladin = nullptr;
    delete player;

    cout << "Сделаем остановку тут\n\t1-сохранить игру\n2-продолжить\n";
    unsigned short choice = GetChoice(1, 2);
    if (choice == 1)
    {
        if (warrior != nullptr) player->Save(warrior);
        if (warrior != nullptr) player->Save(megaWizard);
        if (warrior != nullptr) player->Save(paladin);

    }

    return 0;
}
