#include "field.h"

using namespace Field;

Field::Field(size_t vsize, size_t hsize) 
{
	m_logic = NULL;
	m_field.resize(hsize);
	for(size_t i = 0; i < hsize; ++i) 
	{
		m_field[i].resize(vsize);
		for(size_t j = 0; j < vsize; ++j) 
			m_field[i][j] = NULL; 
	}
}

Field::~Field() 
{
	if(m_logic) 
		delete m_logic;
}

bool Field::get_next(element* next) 
{
	if(m_elements.empty()) 
		return false;
	else if(m_next_element != m_elements.end()) 
	{
		*next = m_next_element++;
		return true;
	}
	else 
		return false;
}

void Field::renew() 
{
	if(!m_elements.empty())
		m_next_element = m_elements.begin();
}

void Field::add_element(Appearance::Appearance* appearance) 
{
	int x = appearance->x();
	int y = appearance->y();
	m_elements.push_back(appearance);
}

void Field::pop_element() 
{
	if(m_elements.empty()) 
		return;
	int x = (*(m_elements.end() - 1))->x();
	int y = (*(m_elements.end() - 1))->y();
	m_field[x][y] = NULL;
	m_elements.pop_back();
}

void Field::renew_positions() 
{
	m_logic->update();
}

bool Field::element_exists(int x, int y) const 
{
	return (m_field[x / Appearance::cell][y / Appearance::cell] != NULL);
}

void Field::activate_logic() 
{
	m_logic = new Logic::GeneralLogic(&m_field);
	for(size_t i = 0; i < m_elements.size(); ++i)
		m_logic->add_unit(dynamic_cast<Appearance::UnitAppearance*>(m_elements[i]));
}
