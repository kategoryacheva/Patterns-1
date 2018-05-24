#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "unit_description.h"
#include "appearance.h"
#include "exception.h"

#define EPS 0.0001

namespace Logic 
{
	const unsigned int AGRO_RANGE = 3;
	enum EDirection 
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	class CUnit;
	class Shot;

	class LogicObject 
	{
		public:
			virtual void set_appearance(Appearance::Appearance* repr) = 0;
			virtual void set_target(CUnit* target) = 0;
			virtual CUnit* get_target() = 0;
			virtual Appearance::s_point get_position() const = 0;
			virtual void set_position(int x, int y) = 0;
			virtual Unit::ClassOfUnit type() const = 0;
			virtual bool side() const = 0;
			virtual void decrease_hp(CUnit* enemy) = 0;
	};
	
	class Shot : public LogicObject 
	{
		public:
			Shot();
			SDL_Rect* rect();
			void set_appearance(Appearance::Appearance* repr) { /*in progress*/ }
			void set_target(CUnit* target) { /*in progress*/ }
			CUnit* get_target() { /*in progress*/ }
			Appearance::s_point get_position() const { /*in progress*/ }
			void set_position(int x, int y) { /*in progress*/ }
			Unit::ClassOfUnit type() const { /*in progress*/ }
			bool side() const { /*in progress*/ }
			void decrease_hp(CUnit* enemy) { /*in progress*/ }
	};

	class CUnit : public LogicObject 
	{
		private:
			Unit::BaseUnit* m_unit;
			Appearance::UnitAppearance* m_appearance;
			CUnit* m_target;
		public:
			CUnit(Unit::BaseUnit* unit, Appearance::UnitAppearance* appearance);
			CUnit* get_target();
			void set_target(CUnit* unit);
			Appearance::s_point get_position() const;
			void set_position(int x, int y);
			Appearance::UnitAppearance* appearance();
			Unit::ClassOfUnit type() const;
			void decrease_hp(CUnit* enemy);
			bool side() const;
			void set_appearance(Appearance::Appearance* repr) { /*in progress*/ } 
	};

	class UnitLogic 
	{
		public:
			virtual CUnit* get_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team) = 0;
			virtual void process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<LogicObject*> >* field) = 0;
	};

	class WarriorLogic : public UnitLogic 
	{
		public:
			CUnit* get_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team);
			void process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<LogicObject*> >* field);
	};

	class CaptainLogic 
	{
		private:
			std::vector<std::vector<CUnit*> > m_ateam;
			std::vector<std::vector<CUnit*> > m_bteam;
			std::vector<Shot*> m_shots;
			std::vector<std::vector<LogicObject*> >* m_field;
			void _update_units(std::vector<std::vector<CUnit*> >& allies, std::vector<std::vector<CUnit*> >& enemies,
					   Unit::ClassOfUnit type, UnitLogic* ulogic);
		public:
			CaptainLogic(std::vector<std::vector<LogicObject*> >* field);
			void add_unit(Appearance::UnitAppearance* repr);
			void update();
			static CUnit* enemy_in_range(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team, unsigned int range);
			static CUnit* nearest_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team, Unit::ClassOfUnit type);
			static Appearance::s_point distance(Appearance::s_point first, Appearance::s_point second);
	};
};

#endif
