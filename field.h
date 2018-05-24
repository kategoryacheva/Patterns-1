#ifndef CField_H
#define CField_H
#include <vector>
#include <iterator>
#include <SDL2/SDL_rect.h>
#include "logic.h"
#include "unit_description.h"
#include "appearance.h"

namespace Field 
{
	typedef std::vector<Appearance::Appearance*>::iterator element;
	class CField 
	{
		private:
			std::vector<std::vector<Logic::LogicObject*> > m_field;
			std::vector<Appearance::Appearance*> m_elements;
			element m_next_element;
			Logic::CaptainLogic* m_logic;
		public:
			CField(size_t vsize, size_t hsize);
			~CField();
			bool get_next(element* next);
			void renew();
			void add_element(Appearance::Appearance* appearance);
			void pop_element();
			void renew_positions();
			bool element_exists(int x, int y) const;
			void activate_logic();
	};
}
#endif 
