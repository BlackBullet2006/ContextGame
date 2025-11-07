#pragma once
#include "BaseClass.h"

class Evil : public Npc {
public:
    Evil(string name) {
        this->name = name;
        health = 10;
        damage = 5;
    }
    Evil(string name, int health) : Evil(name) {
        this->health = health;
    }
    Evil(string name, int health, int damage) : Evil(name, health) {
        this->damage = damage;
    }

    void GetInfo() override {
        cout << endl;
        cout << "на вас напал " << name << endl;
        if (health >= 0 && damage < 0) {
            cout << "«доровье - " << health << endl;
        }
        if (health < 0 && damage >= 0) {
            cout << "урон - " << damage << endl;
        }
        if (health >= 0 && damage >= 0) {
            cout << "«доровье - " << health << endl;
            cout << "урон - " << damage << endl;
        }
    }
};
