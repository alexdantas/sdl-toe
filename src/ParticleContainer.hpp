#ifndef PARTICLECONTAINER_H_DEFINED
#define PARTICLECONTAINER_H_DEFINED

#include <vector>
#include "SDLManager.hpp"
#include "Particle.hpp"
#include "Sprite.hpp"

class ParticleContainer
{
public:
	ParticleContainer(std::string filename);
	virtual ~ParticleContainer();
	int getNumberOfParticles();
	void addParticle(int x=0, int y=0);
	void show();

private:
	std::vector<Particle*> container;
	Sprite* sprite;
	int size;
};

#endif /* PARTICLECONTAINER_H_DEFINED */

