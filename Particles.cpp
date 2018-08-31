#include "Particles.h"
#include <stdlib.h>
namespace particles {

	Particles::Particles()
	{
		// random coordinates of particles on screen
		m_x = ((2.0 * rand()) / RAND_MAX) - 1; // random number b/w -1 and 1
		m_y = ((2.0 * rand()) / RAND_MAX) - 1;
		
		//particles randomly moving on screen
		 m_xspeed = 0.001*(((2.0*rand()) / RAND_MAX) - 1);
		 m_yspeed = 0.001*(((2.0*rand()) / RAND_MAX) - 1);
	}

	void  Particles::update()
	{
		//update random particle location
		m_x += m_xspeed;
		m_y += m_yspeed;

		//particles bounce off sides and doesn't go off screen because speeds reverse it back into bounds
		if (m_x <= -1.0 || m_x >= 1.0)
		{
			//if condition for m_x particles to not go off screen
			m_xspeed = -m_xspeed; 
		}
		if (m_y <= -1.0 || m_y >= 1.0)
		{
			//if condition for m_y particles to not go off screen
			m_yspeed = -m_yspeed;
		}
	}

	 Particles::~Particles()
	{
	}
}