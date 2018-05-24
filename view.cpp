#include "view.h"
#include <iostream>

void View::init() 
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
		throw new InitFailed(std::string(SDL_GetError()));
	int request = SDL_GetDesktopDisplayMode(0, &m_display_mode);
	m_window = SDL_CreateWindow("SimpleGame", 0, 0, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(m_window == NULL) 
		throw new WindowCreationFailed(std::string(SDL_GetError())); 
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_field = new Field::CField(INIT_WINDOW_HEIGHT / Appearance::cell, INIT_WINDOW_WIDTH / Appearance::cell);
	m_active_type = Unit::WARRIOR;
	m_active_type_rect.x = 0;
	m_active_type_rect.y = 0;
	m_active_type_rect.h = Appearance::cell;
	m_active_type_rect.w = Appearance::cell;
	m_active_side = false;

	_process_events();
}

void View::_set_represent_rect(Unit::ClassOfUnit type, SDL_Rect* rect, bool side) const 
{
	switch(type) 
	{
		case Unit::WARRIOR:
			SDL_SetRenderDrawColor(m_renderer, ColorWarrior::red, ColorWarrior::green, ColorWarrior::blue, 0);
			break;
		case Unit::SPACESHIP:
			SDL_SetRenderDrawColor(m_renderer, ColorSpaceship::red, ColorSpaceship::green, ColorSpaceship::blue, 0);
			break;
		case Unit::NOT_UNIT:
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0);
			break;
	}
	if(side) 
		SDL_RenderFillRect(m_renderer, rect); 
	SDL_RenderDrawRect(m_renderer, rect); 
}

void View::_redraw() 
{
	m_field->renew();
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
	while(m_field->get_next(&m_next_iter)) 
		_set_represent_rect((*m_next_iter)->type(), (*m_next_iter)->rect(), (*m_next_iter)->side());
	_set_represent_rect(m_active_type, &m_active_type_rect, m_active_side);
	SDL_RenderPresent(m_renderer);
}

void View::_process_events() 
{
	SDL_Event event;
	bool quit = false;
	while(!quit) 
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT) quit = true;
		else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
		{
			if(!m_field->element_exists(event.button.x, event.button.y))
				m_field->add_element(new Appearance::UnitAppearance(event.button.x, event.button.y, m_active_type,
										     	     m_active_side));
		}
		else if(event.type == SDL_KEYDOWN) 
		{
			if(event.key.keysym.sym == SDLK_SPACE) 
				m_active_side = m_active_side ? 0 : 1;
			else if(event.key.keysym.sym == SDLK_w)
				m_active_type = Unit::WARRIOR;
			else if(event.key.keysym.sym == SDLK_z)
				m_active_type = Unit::SPACESHIP;
			else if(event.key.keysym.sym == SDLK_u) 
				m_field->pop_element();
			else if(event.key.keysym.sym == SDLK_RETURN) 
			{
				quit = true;
				m_field->activate_logic();
				_renew_cycle();
			}
		}
		_redraw();
	}
}

void View::_renew_cycle() 
{
	bool quit = false;
	while(!quit) 
	{
		m_field->renew_positions();
		_redraw();
	}
}

View::~View() 
{
	delete m_field;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
