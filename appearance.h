#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <SDL2/SDL_rect.h>
#include "unit_description.h"

namespace Appearance 
{
	const int cell = 15;
	struct s_point 
	{
		int x, y;
	};
	class Appearance 
	{
		public:
			virtual SDL_Rect* rect() = 0;
			virtual Unit::ClassOfUnit type() const = 0;
			virtual bool side() const = 0;
			virtual int x() const = 0;
			virtual int y() const = 0;
			virtual void add_x(int add) = 0;
			virtual void add_y(int add) = 0;
	};
	class UnitAppearance : public Appearance 
	{
		private:
			SDL_Rect m_rect;
			Unit::ClassOfUnit m_type;
			bool m_side;
			s_point m_position;
		public:
			UnitAppearance(int x, int y, Unit::ClassOfUnit type, bool side) 
			{
				m_position.x = x / cell;
				m_position.y = y / cell;
				m_rect.x = (x / cell) * cell; 
				m_rect.y = (y / cell) * cell;
				m_rect.w = cell;
				m_rect.h = cell;
				m_type = type;
				m_side = side;
			}
			SDL_Rect* rect() { return &m_rect; }
			Unit::ClassOfUnit type() const { return m_type; }
			bool side() const { return m_side; }
			int x() const { return m_position.x; }
			int y() const { return m_position.y; }
			void add_x(int add) { m_position.x += add; }
			void add_y(int add) { m_position.y += add; }

	};
	class ShotAppearance : public Appearance 
	{
		private:
			SDL_Rect m_rect;
			bool m_side;
			s_point m_position;
		public:
			ShotAppearance(int x, int y, bool side) 
			{
				m_position.x = x / cell;
				m_position.y = y / cell;
				m_rect.x = (x / cell) * cell;
				m_rect.y = (y / cell) * cell;
				m_rect.w = cell;
				m_rect.h = cell;
				m_side = side;
			}
			SDL_Rect* rect() { return &m_rect; }
			Unit::ClassOfUnit type() const { return Unit::NOT_UNIT; }
			bool side() const { return m_side; }
			int x() const { return m_position.x; }
			int y() const {return m_position.y; }
			void add_x(int add) { m_position.x += add; }
			void add_y(int add) { m_position.y += add; }
	};
};
#endif
