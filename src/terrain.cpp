#include "terrain.h"
#include "util.h"
#include <GL/gl.h>
#define TVQ_COUNT 5

const float vqc[6 * TVQ_COUNT] = {
	// chão
	1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	// limites
	1.0f, 50.0f, 1.0f,
	-1.0f, 0.0f, 0.95f,
	1.0f, 50.0f, 1.0f,
	0.95f, 0.0f, -1.0f,
	1.0f, 50.0f, -0.95f,
	-1.0f, 0.0f, -1.00f,
	-0.95f, 50.0f, 1.0f,
	-1.0f, 0.0f, -1.00f,
};

Terrain::Terrain(TextureManager* texman): Model(texman)
{
	load("../res/terrain/terrain.obj");
	delete[] vq;
	vq_count = TVQ_COUNT;
	vq = new float[6 * vq_count];
	memcpy(vq, vqc, 6 * vq_count * sizeof(float));
	scale(100.0f, 1.0f, 100.0f);
}
