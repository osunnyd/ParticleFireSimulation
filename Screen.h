#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <iomanip> // used for hexadecimal values
#include <SDL.h>
using namespace std;
namespace screen {
	class Screen
	{
	private:
		//use m_variable for member variabes and to show that they are instance variables
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer;
	public:
		//need only for one screen class instead of multiple screens 
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;
		Screen();
		bool init(); // return true or false for window to stay open or close
		void close(); // deallocation code
		bool processEvents(); // event processing
		void clear();

		// x,y are coordinates hat will be colored by the rgb Uints
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue); 
		
		void update();
		~Screen();
	};
}
#endif // !SCREEN_H



