#ifndef PARTICLES_H
#define PARTICLES_H

namespace particles {
	struct Particles // make variables public for effeciency 
	{
		// coordinates for particles
		double m_x; 
		double m_y;

		//speed and direction of particles
		double m_speed;
		double m_direction; 
	public:
		Particles();
		void update();
		virtual ~Particles();
	};
}

#endif PARTICLES_H
