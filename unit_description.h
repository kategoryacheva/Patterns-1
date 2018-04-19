#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <cstdio>

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
			std::size_t army_size;
			long long army_hp;
			long long damage;
		public:
			Army() = delete;
			Army(long long hp, long long _damage, std::size_t sizeOfArmy, ClassOfUnit unit_class):
				BaseUnit(hp * sizeOfArmy, _damage * sizeOfArmy, unit_class),
				army_size(sizeOfArmy), army_hp(hp), damage(_damage) {}
			void unpick() {
				if (this->army_size >= 1)
					this->army_size -= 1;
				else
					this->army_size = 0;
			}
			size_t get_size() const {
				return army_size;
			}
	};

	class Creator {
		public:
			static BaseUnit* create_unit(ClassOfUnit unit_class) {
				BaseUnit* unit = NULL;
				if(unit_class == SPACESHIP)
					unit = new BaseUnit(200, 15, SPACESHIP);
				else if (unit_class == WARRIOR)
					unit = new BaseUnit(100, 5, WARRIOR);
				return unit;
			}
			static Army* create_army(ClassOfUnit unit_class, std::size_t sizeOfArmy) {
				Army* army = NULL;
				if (unit_class == SPACESHIP)
					army = new Army(200, 15, sizeOfArmy, SPACESHIP);
				else if (unit_class == WARRIOR)
					army = new Army(100, 5, sizeOfArmy, WARRIOR);
				return army;
			}
	};
};

#endif
