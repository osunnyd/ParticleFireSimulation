#ifndef SWARM_H
#define SWARM_H
#include "Particles.h"
namespace particles {
	class Swarm
	{
	private:
		Particles * m_particles; // particles instance variable
	public:
		const static int NPARTICLES = 5000;
		Swarm();
		void update();
		virtual ~Swarm();
		const Particles * const getParticles() { return m_particles; }; // getter for particles
	};
}

#endif SWARM_H