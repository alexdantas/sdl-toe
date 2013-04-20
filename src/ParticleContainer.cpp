#include "ParticleContainer.hpp"

ParticleContainer::ParticleContainer(std::string filename)
{
	this->sprite = new Sprite(filename);
	this->size = 0;
}
ParticleContainer::~ParticleContainer()
{
	delete this->sprite;
	for (int i = 0; i < this->size; i++)
	{
		delete this->container[i];
//		this->container.erase(this->container.begin() + i);
	}
}
int ParticleContainer::getNumberOfParticles()
{
	return this->size;
}
void ParticleContainer::addParticle(int x, int y)
{
	this->container.push_back(new Particle(x, y));
	this->size++;
}
void ParticleContainer::show()
{
	for (int i = 0; i < this->size; i++)
	{
		int x = this->container[i]->getX();
		int y = this->container[i]->getY();

		this->sprite->render(x, y);
	}
}

