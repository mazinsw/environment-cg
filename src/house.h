#ifndef _HOUSE_H_
#define _HOUSE_H_
#include "model.h"

class House: public Model
{
private:
	bool saveMode;
protected:
	
public:
	House(TextureManager * texman);
	virtual void render();
	virtual unsigned int getVertexCount();
};

#endif /* _HOUSE_H_ */