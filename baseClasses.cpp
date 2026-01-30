#pragma once
#include <fstream> 
#include <iostream>
#include <memory>

using namespace std;
//базовый класс - абстрактный (класс у которого все методы виртуальные)
class Npc
{
protected: // Защищенные поля (доступны в классе и наследниках)
	string name{ "персонаж" };       // Имя персонажа, по умолчанию "персонаж"
	unsigned int health{ 10 };       // Здоровье, по умолчанию 10
	float damage{ 5 };               // Урон, по умолчанию 5
	unsigned short lvl{ 1 };         // Уровень, по умолчанию 1
public: //публичный модификатор доступ (использовать метод можно в любом месте)

	//геттер - когда можно получить информацию о поле, но только для чтения (нельзя перезаписать)
	string GetName() const { return name; }     // Возвращает имя
	unsigned int GetHealth() const { return health; } // Возвращает здоровье
	float GetDamage() const { return damage; }   // Возвращает урон
	unsigned short GetLvl() const { return lvl; }   // Возвращает уровень

	//дружественные функции (friend) - может изменять private/protected поля
	friend void TakeDamage(Npc&, float damage);

	virtual void GetInfo() //метод класса 
	// Выводит информацию о персонаже
	{
		cout << "имя - " << name << endl;
		cout << "здоровье - " << health << endl;
		cout << "урон - " << damage << endl;
	}
	virtual void Create() {}; // Создание персонажа (пустой по умолчанию)
	virtual bool Save() {
		ofstream saveSystem("save.bin", ios::binary);
		if (saveSystem.is_open())
		{
			// Сохраняем длину имени
            size_t nameLength = name.length();
            saveSystem.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
            // Сохраняем само имя
            saveSystem.write(name.c_str(), nameLength);
            // Сохраняем остальные параметры
            saveSystem.write(reinterpret_cast<const char*>(&health), sizeof(health));
            saveSystem.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
            saveSystem.write(reinterpret_cast<const char*>(&lvl), sizeof(lvl));
            saveSystem.close();
            return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}
	};
	virtual bool Load()
	{
		ifstream loadSystem("save.bin", ios::binary);
		if (loadSystem.is_open())
		{
			size_t nameLength;
			loadSystem.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
			char* buffer = new char[nameLength + 1];
			loadSystem.read(buffer, nameLength);
			buffer[nameLength] = '\0';
			name = string(buffer);
			delete[] buffer;

			loadSystem.read(reinterpret_cast<char*>(&health), sizeof(health));
			loadSystem.read(reinterpret_cast<char*>(&damage), sizeof(damage));
			loadSystem.read(reinterpret_cast<char*>(&lvl), sizeof(lvl));
			loadSystem.close();
			return true;
		}
		else
		{
			cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
			return false;
		}
	};
	// Виртуальный деструктор
	virtual ~Npc() = default; //default - по умолчанию, чтобы не писать {} тело пустое

};

class Player
{
private:
	unique_ptr<Npc> currentCharacter{ nullptr }; // Умный указатель на текущего персонажа

public:
	// Создание персонажа (принимает готового персонажа)
	void Create(unique_ptr<Npc> player)
	{
		currentCharacter = move(player);  // Перемещаем владение
		currentCharacter->Create();       // Вызываем метод создания
	}

	// Создание персонажа (если уже есть)
	void Create()
	{
		if (currentCharacter != nullptr)
			currentCharacter->Create();
	}

	// Сохранение текущего персонажа
	bool Save()
	{
		return currentCharacter ? currentCharacter->Save() : false;
	}

	// Загрузка персонажа
	bool Load(unique_ptr<Npc> player)
	{
		if (player->Load()) {
			currentCharacter = move(player);
			return true;
		}
		return false;
	}

	// Получение указателя на персонажа
	Npc* GetCharacter() {
		return currentCharacter.get();
	}
};
