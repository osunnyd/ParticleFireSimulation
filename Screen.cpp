#include "Screen.h"

namespace screen
{
	Screen::Screen() : // initialization list for member variables
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL) 
	{
	}

	bool Screen::init() // return true or false for window to stay open or close
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
			return false;
		}

		//create a window with a window pointer; followed by name and screen dimensions
		m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_window == NULL) // if window doesn't open then just exit window
		{
			cout << "Window failed to initialize:" << SDL_GetError() << endl;
			SDL_Quit();
			return false; 
		}

		//rendering to the created window with a renderer pointer
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

		//creating the texture with m_texture by using m_renderer
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_BGRA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		// creating a texture using renderer pointer, pixelformat uses 1byte for each pixel, textureaccess_static writes value of pixels directly to texture

		//in case renderer and texture does not work
		if (m_renderer == NULL)
		{
			cout << "Could not create renderer:" << SDL_GetError() << endl;
			SDL_DestroyWindow(m_window); // destroys window pointer in case renderer fails
			SDL_Quit();
			return false;
		}

		if (m_texture == NULL)
		{
			cout << "Could not create texture:" << SDL_GetError() << endl;
			SDL_DestroyRenderer(m_renderer); // destroys created renderer pointer if texture pointer fails
			SDL_DestroyWindow(m_window); // destroys window pointer 
			SDL_Quit();
			return false;
		}

		//allocate enough memory for pixels
		// Uint32 is a type declared by SDL equivalent to an int guaranteed to be 32 bits
		m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

		// memset() sets block of memory with a particular value
		memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
		
		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{	//(BGRA)
		// check if pixel is being plotted off the screen
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		{
			return;
		}
		Uint32 color = 0; // unsigned 32bit int

		//add colors and shift left 8 bits accordingly
		color += blue;
		color <<= 8;
		color += green;
		color <<= 8;
		color += red;
		color <<= 8;
		color += 0xFF;

		//set value to buffer 
		m_buffer[(y*SCREEN_WIDTH + x)] = color; 
		// y*width = correct row
		// + x moves to the correct column / pixel
	}

	void Screen::clear()
	{
		memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32)); // helps to clear screen so particles move smoothly
	}

	void Screen::update()
	{// updates texture, updates whole thing, update raw pixel(buffer poniter), updating number of bytes b/w rows of pixel data
		// updates texture with pixel information contained in buffer
		SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer); // draws renderer on screen
	}

	void Screen::close() // deallocation code 
	{
		delete[] m_buffer; // delete allocated memory for pixels

		// delete renderer and texture pointers in order of what comes first
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window); // destroys window pointer
		SDL_Quit();
	}

	bool Screen::processEvents() // event processing
	{
		SDL_Event event; // event occurring

		while (SDL_PollEvent(&event)) // check for messages/events; processes event que
		{
			if (event.type == SDL_QUIT) // event.type is kind of like a struct; breaks encapsulation for effeciency
										// QUIT actually quits event when the user clicks the exit button in corner
			{
				return false; // quits window when user decides to close
			}
		}
		return true;
	}

	Screen::~Screen()
	{
	}

}