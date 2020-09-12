#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include "texture.h"

class SkyBox
{
private:
	Texture tex[5];
public:
	void load();
	void render();
};

#endif /* _SKYBOX_H_ */