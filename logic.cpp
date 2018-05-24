#include "logic.h"

using namespace Logic;

CUnit* WarriorLogic::get_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team) 
{
	CUnit* enemy = NULL;
	CUnit* target = cur_unit->get_target();
	if(!target) 
	{
		enemy = CaptainLogic::enemy_in_range(cur_unit, enemy_team, AGRO_RANGE);
		if(!enemy_team[Unit::SPACESHIP].empty()) 
			enemy = CaptainLogic::nearest_enemy(cur_unit, enemy_team, Unit::SPACESHIP);
		else
			enemy = CaptainLogic::nearest_enemy(cur_unit, enemy_team, Unit::WARRIOR);
	}
	return enemy;
}

void WarriorLogic::process_enemy(CUnit* cur_unit, CUnit* enemy, std::vector<std::vector<LogicObject*> >* field) 
{
	cur_unit->set_target(enemy);
	if(!enemy) 
		return;
	Appearance::s_point dist = CaptainLogic::distance(cur_unit->get_position(), enemy->get_position());
	Appearance::s_point position = cur_unit->get_position();
	Appearance::s_point old_position = cur_unit->get_position();
	if(std::abs(dist.x) > std::abs(dist.y)) 
		position.x += dist.x / std::abs(dist.x);
	else if(std::abs(dist.x) <= std::abs(dist.y)) 
		position.y += dist.y / std::abs(dist.y);
	if(position.x < 0 || position.x >= field->size() || position.y < 0 || position.y >= (*field)[0].size())
		return;
	if((*field)[position.x][position.y] == NULL) 
	{
		(*field)[position.x][position.y] = (*field)[old_position.x][old_position.y];
		(*field)[old_position.x][old_position.y] = NULL;
		cur_unit->set_position(position.x, position.y);
	}
	else if((*field)[position.x][position.y]->type() != Unit::NOT_UNIT) 
		(*field)[position.x][position.y]->decrease_hp(cur_unit);
	else 
	{
		//in progress(shot in the cell)
	}
}

CUnit::CUnit(Unit::BaseUnit* unit, Appearance::UnitAppearance* appearance) 
{
	m_unit = unit;
	m_appearance = appearance;
	m_target = NULL;
}

Appearance::UnitAppearance* CUnit::appearance() 
{
	return m_appearance;
}

CUnit* CUnit::get_target() 
{
	return m_target;
}

void CUnit::set_target(CUnit* unit) 
{
	m_target = unit;
}

Appearance::s_point CUnit::get_position() const 
{
	Appearance::s_point res;
	res.x = m_appearance->x();
	res.y = m_appearance->y();
	return res; 
}

void CUnit::set_position(int x, int y) 
{
	m_appearance->add_x(x);
	m_appearance->add_y(y);
}

Unit::ClassOfUnit CUnit::type() const 
{
	return m_unit->get_class();
}

bool CUnit::side() const 
{
	return m_appearance->side();
}

void CUnit::decrease_hp(CUnit* enemy) 
{
	m_unit->decrease_hp(enemy->m_unit->get_damage());
}

CaptainLogic::CaptainLogic(std::vector<std::vector<LogicObject*> >* field) 
{
	m_field = field;
	m_ateam.reserve(3);
	m_bteam.reserve(3);
	std::srand(time(NULL));
}

void CaptainLogic::add_unit(Appearance::UnitAppearance* repr) 
{
	if(repr->type() > 2)
		throw new ExInvalidUnit("unit class is greater than 2");
	CUnit* unit = new CUnit(Unit::Creator::create_unit(repr->type()), repr);
	if(!unit->side()) 
		m_ateam[repr->type()].push_back(unit);
	else 
		m_bteam[repr->type()].push_back(unit);
}

void CaptainLogic::update() 
{
	WarriorLogic* logic = new WarriorLogic;
	_update_units(m_ateam, m_bteam, Unit::WARRIOR, logic);
	_update_units(m_bteam, m_ateam, Unit::WARRIOR, logic); 
	delete logic;
}

void CaptainLogic::_update_units(std::vector<std::vector<CUnit*> >& allies, std::vector<std::vector<CUnit*> >& enemies,
				  Unit::ClassOfUnit type, UnitLogic* ulogic) 
{
	for(size_t i = 0; i < allies[type].size(); ++i) 
	{
		CUnit* cur_unit = allies[type][i];
		CUnit* enemy = ulogic->get_enemy(cur_unit, enemies);
		ulogic->process_enemy(cur_unit, enemy, m_field);
	}
}

CUnit* CaptainLogic::enemy_in_range(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team, unsigned int range) 
{
	Appearance::s_point cur_unit_pos = cur_unit->get_position();
	for(size_t i = 0; i < 3; ++i) 
	{
		for(size_t j = 0; j < enemy_team[i].size(); ++j) 
		{
			CUnit* enemy_unit = enemy_team[i][j];
			Appearance::s_point dist_point = CaptainLogic::distance(cur_unit_pos, enemy_unit->get_position());
			unsigned int dist = (unsigned int)std::sqrt(dist_point.x * dist_point.x + dist_point.y * dist_point.y);
			if(dist <= range) 
				return enemy_team[i][j];
		}
	}
}

CUnit* CaptainLogic::nearest_enemy(CUnit* cur_unit, std::vector<std::vector<CUnit*> >& enemy_team, Unit::ClassOfUnit type) 
{
	Appearance::s_point cur_unit_pos = cur_unit->get_position();
	CUnit* best_unit = NULL;
	double min_dist = 10000000.0;
	for(size_t i = 0; i < enemy_team[type].size(); ++i) 
	{
		CUnit* enemy_unit = enemy_team[type][i];
		Appearance::s_point dist_point = CaptainLogic::distance(cur_unit_pos, enemy_unit->get_position());
		double dist = std::sqrt(dist_point.x * dist_point.x + dist_point.y * dist_point.y);
		if(min_dist > dist) 
		{
			min_dist = dist;
			best_unit = enemy_unit;
		}
	}
	return best_unit;
}

Appearance::s_point CaptainLogic::distance(Appearance::s_point first, Appearance::s_point second) 
{
	Appearance::s_point res;
	res.x = second.x - first.x;
	res.y = second.y - first.y;
	return res;
}
