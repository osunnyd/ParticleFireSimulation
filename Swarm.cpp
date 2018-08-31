#include "Swarm.h"

namespace particles {

	Swarm::Swarm()
	{
		m_particles = new Particles[NPARTICLES];
	}

	void Swarm::update()
	{
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			m_particles[i].update(); //gives the random particle movement
		}
	}

	Swarm::~Swarm()
	{
		delete [] m_particles; // deallocate particles
	}
}