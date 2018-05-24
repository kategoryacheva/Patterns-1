#ifndef VIEW_H
#define VIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "field.h"
#include "exception.h"

#define INIT_WINDOW_WIDTH 1000
#define INIT_WINDOW_HEIGHT 1000

class View 
{
	private:
		SDL_DisplayMode m_display_mode;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		Field::Field* m_field;
		Unit::ClassOfUnit m_active_type;
		Field::element m_next_iter;
		bool m_active_side;
		SDL_Rect m_active_type_rect;
		void _set_represent_rect(Unit::ClassOfUnit type, SDL_Rect* rect, bool side) const;
		void _renew_cycle();
		void _redraw();
		void _process_events();
	public:
		View() {} 
		void init();
		~View();
		struct ColorWarrior 
		{
			static const int red = 230;
			static const int green = 255;
			static const int blue = 0;
		};
		struct ColorSpaceship
		{
			static const int red = 105;
			static const int green = 99;
			static const int blue = 188;
		};
};

#endif
