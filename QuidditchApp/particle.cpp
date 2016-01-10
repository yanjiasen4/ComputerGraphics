#include"particle.h"

const float gravity = -1.8;

ParticleSystem::ParticleSystem(int count)
{
	active = false;
	pCount = count;
}

ParticleSystem::~ParticleSystem()
{
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
		delete (*iter);
}

void ParticleSystem::init(GLfloat xx, GLfloat yy, GLfloat zz)
{
	x = xx;
	y = yy;
	z = zz;
	srand(unsigned(time(0)));
	Color colors[3] = { { 0,0,1,1 },{ 1,0,1,1 } };
	for (int i = 0; i < pCount; i++)
	{
		float vx = (rand() % 10 - 5.0) / 100;
		float vy = (rand() % 10 - 5.0) / 100;
		float vz = (rand() % 10 - 5.0) / 100;
		float ax = (rand() % 20 - 10.0) / 1000;
		float ay = (rand() % 20 - 10.0) / 1000;
		float az = (rand() % 20 - 10.0) / 1000;
		Color cl = colors[rand() % 2];
		Vector3D pos = Vector3D(xx, yy, zz);
		Vector3D spd = Vector3D(vx, vy, vz);
		Vector3D acl = Vector3D(ax, ay, az);
		Particle *tmp = new Particle(
			pos,
			spd,
			acl,
			cl,
			0.0f,
			5.5 + 0.05*(rand() % 10),
			0.05f
			);
		//cout << tmp->velocity.x<< endl;
		particles.push_back(tmp);
	}
	mySphere = gluNewQuadric();
}

void ParticleSystem::activate()
{
	active = true;
}

void ParticleSystem::applyGravity()
{
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
		(*iter)->acceleration = Vector3D(0, 0, gravity);
}

void ParticleSystem::aging(float dt)
{
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
	{
		(*iter)->age += dt;
		//cout << (*iter)->age << endl;
		if ((*iter)->age > (*iter)->life)
		{
			active = false;
			(*iter)->position = Vector3D(0, 0, 0);
			//(*iter)->age = 0.0;
			(*iter)->velocity = Vector3D(((rand() % 30) - 15.0f), ((rand() % 30) - 11.0f), ((rand() % 30) - 15.0f));
		}
	}
}

void ParticleSystem::update(float dt)
{
	aging(dt);
	applyGravity();
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
	{
		(*iter)->position = (*iter)->position + (*iter)->velocity*dt;
		(*iter)->velocity = (*iter)->velocity + (*iter)->acceleration*dt;
	}
}

void ParticleSystem::render()
{
	glDisable(GL_DEPTH_TEST);
	if (isActive())
	{
		for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
		{
			if ((*iter)->active)
			{
				float alpha = 1 - (*iter)->age / (*iter)->life;//calculate the alpha value according to the age of particle.  
				Vector3D tmp = (*iter)->position;
				glColor4f((*iter)->color.r, (*iter)->color.g, (*iter)->color.b, alpha);
				glPushMatrix();
				glTranslatef(tmp.x, tmp.y, tmp.z);
				//cout << (*iter)->position.x<<tmp.x << tmp.y << tmp.z << endl;
				gluSphere(mySphere, (*iter)->size, 32, 16);
				glPopMatrix();
			}
		}
	}
	glEnable(GL_DEPTH_TEST);
	//glAccum(GL_ACCUM, 0.5f);
}

bool ParticleSystem::isActive()
{
	return active;
}


Particle::Particle(Vector3D vp, Vector3D vv, Vector3D va, Color cl, float ag, float lf, float sz) : position(vp),velocity(vv),acceleration(va)
{
	color = cl;
	age = ag;
	life = lf;
	size = sz;
	active = true;
}

Particle::Particle(float x, float y, float z, float sx, float sy, float sz, float ax, float ay, float az, float cr, float cg, float cb, float ag, float lf, float r)
{
	position = Vector3D(x, y, z);
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
	color.r = cr;
	color.g = cg;
	color.b = cb;
	color.alpha = 1.0f;
	age = ag;
	life = lf;
	size = r;
	active = true;
}

Spark::~Spark()
{
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
		delete (*iter);
}

void Spark::init(GLfloat xx, GLfloat yy, GLfloat zz)
{
	particles.clear();
	x = xx;
	y = yy;
	z = zz;
	srand(unsigned(time(0)));
	for (int i = 0; i<pCount; i++)		
	{
		float vx = float((rand() % 50) - 26.0f)/25;
		float vy = float((rand() % 50) - 26.0f)/25;
		float vz = float((rand() % 50) - 26.0f)/25;
		int randColor = rand() % 11;
		Color cl = colors[randColor];
		float life = 2.0 + rand() % 8;
		Vector3D pos = Vector3D(x, y, z);
		Vector3D spd = Vector3D(vx, vy, vz);
		Vector3D acl = Vector3D(0.0f, 0.0f, -0.8f);
		Particle *tmp = new Particle(
			pos,
			spd,
			acl,
			cl,
			0.0f, life,
			0.1f
			);
		particles.push_back(tmp);
	}
}

void Spark::update(float dt)
{
	aging(dt);
	//applyGravity();
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
	{
		(*iter)->position = (*iter)->position + (*iter)->velocity*dt;
		(*iter)->velocity = (*iter)->velocity + (*iter)->acceleration*dt;
	}
}

void Spark::render()
{
	if (isActive())
	{
		
		glEnable(GL_TEXTURE_2D);	
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, TEX_PARTICLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
		{
			if ((*iter)->active)
			{
				float x = (*iter)->position.x;
				float y = (*iter)->position.y;
				float z = (*iter)->position.z;
				Color color = (*iter)->color;
				float alpha = 1.0 - (*iter)->age / (*iter)->life;
				//cout << color.r << ends << color.g << ends << color.b << endl;
				glColor4f(color.r, color.g, color.b, alpha);
				//cout << (*iter)->age << endl;
				//glColor4f(1, 0, 0, alpha);
				float sz = 0.5;
				glPushMatrix();
				glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1, 1); glVertex3f(x + sz / 2, y + sz / 2, z);
				glTexCoord2d(0, 1); glVertex3f(x - sz / 2, y + sz / 2, z);
				glTexCoord2d(1, 0); glVertex3f(x + sz / 2, y - sz / 2, z);
				glTexCoord2d(0, 0); glVertex3f(x - sz / 2, y - sz / 2, z);
				glEnd();
				glPopMatrix();
			}
		}
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}

void Spark::aging(float dt)
{
	for (vector<Particle*>::iterator iter = particles.begin(); iter != particles.end(); iter++)
	{
		(*iter)->age += dt;
		if ((*iter)->age > (*iter)->life)
			active = false;
	}
}

