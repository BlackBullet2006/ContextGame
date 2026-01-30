#include "GameClasses.h"

Warrior::Warrior()
{
	name = "Воин";
	health = 35;
	damage = 10;
};

Warrior::Warrior(std::string name, unsigned int health, float damage)
{
	cout << "Вызван параметризованный конструктор" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
};

void Warrior::GetWeapons()
{
	cout << name << " вооружен оружием класса '" << weapons[lvl - 1] << "'" << endl;
};

void Warrior::GetInfo()
{
	Npc::GetInfo();
	cout << "Сила - " << strenght << endl;
	cout << "Доступное оружие - ";
	for (int i = 0; i < lvl; i++)
	{
		cout << weapons[i] << endl;
	}
};
void Warrior::Create()
{
	cout << "Вы выбрали воина" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
};

bool Warrior::operator == (const Warrior& warrior) const
{
	return (warrior.damage == this->damage) &&
		(warrior.health == this->health) &&
		(warrior.strenght == this->strenght);
};

Warrior& Warrior::operator = (const Npc& npc)
{
	if (this != &npc)
	{
		this->name = npc.GetName();
		this->health = npc.GetHealth();
		this->damage = npc.GetDamage();
		this->lvl = npc.GetLvl();
		return *this;
	}
};

bool Warrior::Save()
{
	ofstream saveSystem("save.bin", ios::binary);
	if (saveSystem.is_open())
	{
		if (!Npc::Save())
		{
			cout << "Сохранение не удалось\nПопробуйте снова\n\n";
			return false;
		}

		saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
		saveSystem.close();
		return true;
	}
	else
	{
		cout << "Сохранение не удалось\nПопробуйте снова\n";
		return false;
	}
};

void Wizard::GetInfo()
{
	Npc::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Доступные заклинания на этом уровне - ";
	GetSpellsInfo();
}

bool Warrior::Load()
{
	ifstream loadSystem("save.bin", ios::binary);
	if (loadSystem.is_open())
	{
		if (!Npc::Load())
		{
			cout << "Сбой в системе загрузки\nДанные в файле повреждены или отсутствуют\n";
			return false;
		}
		loadSystem.read(reinterpret_cast<char*>(&strenght), sizeof(strenght));
	}
	else
	{
		cout << "Сбой в системе загрузки\nДанные в файле повреждены или отсутствуют\n";
		return false;
	}
	loadSystem.close();
	return true;
};
Warrior::~Warrior()
{
	cout << name << "был успешно удален" << endl;
};

Wizard::Wizard()
{
	name = "Волшебник";
	health = 23;
	damage = 15;
};

Wizard::Wizard(string name, unsigned int health, float damage)
{
	cout << "Работа параметризованного конструктора Волшебника" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
};

void Wizard::GetSpellsInfo()
{
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << " уровень:\n";
		// Выводим информацию о заклинании через оператор [] для каждого свойства (0-4)
		for (int j = 0; j < 5; j++)
		{
			cout << "  " << spells[i][j] << endl; // Предполагается, что spells[i] — это объект Spell
		}
		cout << endl;
	}
}

void Wizard::Create()
{
	cout << "Вы создаете волшебника" << endl;
	cout << "Укажите имя персонажа\t";
	cin >> name;
	GetInfo();
};

Wizard Wizard::operator + (const Wizard& wizard) const
{
	return Wizard(
		this->name,
		(this->health + wizard.health),
		(this->damage + wizard.damage)
	);
};

bool Wizard::Save()
{
	if (Npc::Save())
	{
		ofstream saveSystem("save.bin", ios::binary | ios::app); //используется режим дописывания (app)
		if (saveSystem.is_open())
		{
			saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
			for (int i = 0; i < 4; i++)
			{
				//saveSystem.write(reinterpret_cast<const char*>(&spell[i]), sizeof(spell[i]));
			}
			saveSystem.close();
			return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте снова\n";
			return false;
		}
	}
};

Wizard::~Wizard()
{
	cout << name << " исчез в никуда" << endl;
};

Wizard::Spell::Spell(string name, unsigned short damage,
	unsigned short price, bool isCurse, int timeCast)
{
	this->name = name;
	this->damage = damage;
	this->price = price;
	this->isCurse = isCurse;
	this->timeCast = timeCast;
}

string Wizard::Spell::operator[](unsigned index) const
{
	switch (index)
	{
	case 0: return "Название - " + name; break;
	case 1: return "Урон - " + to_string(damage); break;
	case 2: return "Стоимость маны - " + to_string(price) + " маны"; break;
	case 3:
	{
		if (isCurse)
		{
			return "Тёмное зло";
		}
		else {
			return "Обычное заклинание";
		}
		break;
	}
	case 4:
		return isCurse ? "Длительность проклятого эффекта - " + to_string(timeCast) :
			"Длительность заклинания - " + to_string(timeCast);
		break;
	default: return "Ошибка доступа к элементу по индексу"; break;
	}
}

unsigned short Wizard::Spell::CastSpell()
{
	cout << "Вы применяете " << name << " на цель" << endl;
	return damage;
}

Paladin::Paladin()
{
	name = "Паладин";
	health = 25;
	damage = 12;
	strenght = 27;
};

void Paladin::GetInfo()
{
	Warrior::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Список заклинаний на текущем уровне - ";
	GetSpellsInfo();
};

void Paladin::Create()
{
	cout << "Вы выбрали паладина" << endl;
	cout << "Укажите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
};

bool Paladin::Save()
{
	if (Warrior::Save())
	{
		ofstream saveSystem("save.bin", ios::binary | ios::app);
		if (saveSystem.is_open())
		{
			saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
			for (int i = 0; i < 4; i++)
			{
				//saveSystem.write(reinterpret_cast<const char*>(&spell[i]), sizeof(spell[i]));
			}
			saveSystem.close();
			return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте снова\n";
			return false;
		}
	}
};
