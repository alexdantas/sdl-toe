#ifndef PARTICLE_H_DEFINED
#define PARTICLE_H_DEFINED

class Particle
{
public:
	Particle(int x=0, int y=0);
	virtual ~Particle();

	void show();
	int getX();
	int getY();

private:
	int x;
	int y;
};

#endif /* PARTICLE_H_DEFINED */
