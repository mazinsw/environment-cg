#include "house.h"
#include <string.h>
#include <GL/gl.h>
#define VQ_COUNT 6

const float vqc[6 * VQ_COUNT] = {
	5.0f, 2.0f, 5.0f,
	-5.0f, 0.0f, 4.616200f,
	5.0f, 2.0f, 5.0f,
	4.616200f, 0.0f, -5.0f,
	5.0f, 2.0f, -4.616200f,
	-5.0f, 0.0f, -5.0f,
	// lado da porta
	-4.616200f, 2.0f, 1.538733f,
	-5.0f, 0.0f, -5.0f,
	-4.616200f, 2.0f, 5.0f,
	-5.0f, 0.0f, 3.077467,
	// teto
	5.495297f, 3.536779f, 5.495297f,
	-5.495297f, 2.0f, -5.495297f,
};

House::House(TextureManager* texman): Model(texman)
{
	load("../res/house/house.obj");
	delete[] vq;
	vq_count = VQ_COUNT;
	vq = new float[6 * vq_count];
	memcpy(vq, vqc, 6 * vq_count * sizeof(float));
	saveMode = true;
	scale(2.0f, 2.0f, 2.0f);
	translate(-10.0f, 0.1f, 10.0f);
	saveMode = false;
}

void House::render()
{
	glPushMatrix();
	glTranslatef(-10.0f, 0.01f, 10.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	Model::render();
	glPopMatrix();
}

unsigned int House::getVertexCount()
{
	if(saveMode)
		return 0;
	return Model::getVertexCount();
}
