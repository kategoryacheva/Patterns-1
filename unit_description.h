#ifndef UNIT_H
#define UNIT_H

#include <vector>

namespace Unit {
	enum ClassOfUnit {
		SPACESHIP,
		WARRIOR,
		NOT_UNIT
	};

	class BaseUnit {
		protected:
			long long hp;
			long long damage;
			ClassOfUnit cl;
		public:
			BaseUnit() = delete;
			BaseUnit(long long unit_hp, long long unit_damage, ClassOfUnit unit_cl): 
				hp(unit_hp), damage(unit_damage), cl(unit_cl) {}
			BaseUnit(const BaseUnit& unit) {
				hp = unit.hp;
				damage = unit.damage;
				cl = unit.cl;
			}
			void set_hp(long long unit_hp) {
			    hp = unit_hp;
            		}
			void set_damage(long long unit_damage) {
			    damage = unit_damage;
            		}
			long long get_hp() const {
			    return hp;
            		}
			long long get_damage() const {
			    return damage;
            		}
			ClassOfUnit get_class() const {
			    return cl;
            		}
			void decrease_hp(long long injury) {
			    hp = std::max((long long)0, hp - injury);
			}
	};

	class Army : public BaseUnit {
		protected:
			size_t army_size;
			long long army_hp;
			long long damage;
		public:
			Army() = delete;
			Army(long long hp, long long _damage, size_t sizeOfArmy, ClassOfUnit unit_class):
				BaseUnit(hp * sizeOfArmy, _damage * sizeOfArmy, unit_class),
				army_size(sizeOfArmy), army_hp(hp), damage(_damage) {}
			std::vector<BaseUnit*> unpick() const {
				std::vector<BaseUnit*> units(army_size);
				long long unit_hp = hp / army_size;
				for (size_t i = 0; i < army_size - 1; ++i)
					units.push_back(new BaseUnit(unit_hp, damage, cl));
				unit_hp += hp - unit_hp * army_size;
				units.push_back(new BaseUnit(unit_hp, damage, cl));
				return units;
			}
	};

	class Creator {
		public:
			static BaseUnit* create_unit(ClassOfUnit unit_class) {
				BaseUnit* unit = NULL;
				if(unit_class == ClassOfUnit::SPACESHIP)
					unit = new BaseUnit(200, 15, ClassOfUnit::SPACESHIP);
				else if (unit_class == ClassOfUnit::WARRIOR)
					unit = new BaseUnit(100, 5, ClassOfUnit::WARRIOR);
				return unit;
			}
			static Army* create_army(ClassOfUnit unit_class, size_t sizeOfArmy) {
				Army* army = NULL;
				if (unit_class == ClassOfUnit::SPACESHIP)
					army = new Army(200, 15, sizeOfArmy, ClassOfUnit::SPACESHIP);
				else if (unit_class == ClassOfUnit::WARRIOR)
					army = new Army(100, 5, sizeOfArmy, ClassOfUnit::WARRIOR);
				return army;
			}
	};
};

#endif
