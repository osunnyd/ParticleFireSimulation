
#include <SDL.h>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <math.h> // used for changing colors
using namespace std;
using namespace screen;
using namespace particles;
int main(int argc, char *argv[])
{
	srand(time(NULL)); // used so particles are always random for every creation

	Screen screen;
	if (screen.init() == false)
	{
		cout << "Error initializing SDL." << endl;
	}

	Swarm swarm; 

	//game loop; runs for as long as game is running
	while (true) // update particles; draw particles
	{
		//particles now change color instead of whole screen
		int elapsed = SDL_GetTicks(); // elapsed milliseconds

		screen.clear();
		swarm.update(); // update all particles

		unsigned char green = (unsigned char)((1 + sin(elapsed* 0.0001)) * 128); // used to smoothly change sin wave through whole screen
		unsigned char red = (unsigned char)((1 + sin(elapsed* 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + cos(elapsed* 0.0003)) * 128);

		//get swarm particles
		const Particles *const pParticles = swarm.getParticles();

		//plotting particles on screen
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particles particle = pParticles[i]; // getting individual particles one by one
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2; // add 1 so particle range is entire width
			int y = (particle.m_y + 1) * Screen::SCREEN_HEIGHT / 2; // add 1 so particle range is entire height
			screen.setPixel(x, y, red, green, blue); // particles are randomly changing colors uniformly 
		}

		screen.update(); // draws screen

		if (screen.processEvents() == false) // if user decides to close window
		{
			break; // stops game loop and proceed to close window
		}
	}
	
	screen.close(); 


	return 0;
}