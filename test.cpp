#include "unit_description.h"
#include <iostream>

using namespace std;

void testUnits() {
	Unit::BaseUnit* unit = Unit::Creator::create_unit(Unit::WARRIOR);
	cout<< unit->get_class() << endl;
	cout<< unit->get_hp() << endl;
	cout<< unit->get_damage() << endl;
	unit->set_hp(200);
	cout<< unit->get_hp() << endl;
	unit->set_damage(1000);
	cout<< unit->get_damage() << endl;
	Unit::BaseUnit unit2(*unit);
	cout<< unit2.get_damage() << endl;
	Unit::BaseUnit unit3(100, 3, Unit::SPACESHIP);
	cout<< unit3.get_class() << endl;
	cout<< unit->get_hp() << endl;
	unit->decrease_hp(6);
	cout<< unit->get_hp() << endl;
	unit->decrease_hp(200);
	cout<< unit->get_hp() << endl;
}

void testArmy() {
	Unit::Army* army = Unit::Creator::create_army(Unit::SPACESHIP, 300);
	Unit::Army army2(*army);
	cout<< army2.get_damage() << endl;
	cout<< army2.get_hp() << endl;
	cout<< army2.get_class() << endl;
	cout << army->get_hp() << endl;
	army->decrease_hp(1000);
	cout << army->get_hp() << endl;
	cout << army2.get_hp() << endl;
	cout << army2.get_size() << endl;
	army2.unpick();
	cout << army2.get_size() << endl;
}

int main() {
	cout << "Unit:" << endl;
	testUnits();
	cout << "Army:" << endl;
	testArmy();
	return 0;
}
