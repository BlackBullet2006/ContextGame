#include <iostream>
#include "windows.h"
#include "BaseClass.h"
#include "StartClasses.h"

using namespace std;

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
  setlocale(LC_ALL, "Rus");
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
  //создать уникальную функцию для проверки условия выбора
  cin >> choise;
  while (choise > 2 || choise < 1)
  {
    cout << "Наверное ты ошибся, повтори снова\n";
    cin >> choise;
  }
  if (choise == 1)
  {
    cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n";
    
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
