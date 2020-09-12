#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "classes/glwindow.h"
#include "util.h"
#include "keyaction.h"
#include "player.h"
#include "skybox.h"
#include "texturemanager.h"
#include "scenemanager.h"
#include "terrain.h"
#include "sound.h"
#include "house.h"
#define X_CRATE -0.0f
#define Z_CRATE 20.0f
#define CUBE_MAP_COUNT 19
#include <math.h>

const int cube_map[CUBE_MAP_COUNT][2] = {
	{2, 1},
	{1, 1},
	{0, 1},
	{-1, 1},
	{-1, 2},
	{-1, 3},
	{0, 3},
	{0, 4},
	{0, 5},
	{-1, 5},
	{-2, 5},
	{-3, 5},
	{-3, 4},
	{-3, 3},
	{-3, 2},
	{-3, 1},
	{-3, 0},
	{-3, -1},
	{-3, -2}
};

class RenderWindow: public GLWindowBase
{
private:
	SkyBox * skybox;
	Player* player;
	TextureManager * texman;
	SceneManager* sceneman;
	char str[255];
	Sound walking_snd;
	Sound running_snd;
	GLfloat light_position[4];

	/* jump test */
	bool jump;
	bool running;
	float vel;
private:

	void loadObjects()
	{
		Model * model;
		player = new Player(this);
		player->setConstantVelocity(false);
		player->scale(0.5f, 4.0f, 0.5f);
		// surge caindo
		player->setYDist(2.1f);
		// move o player para frente da casa
		player->setXDist(-40.0f);
		player->setZDist(10.0f);
//		player->setXDist(-10.0f);
//		player->setZDist(25.0f);
		player->setYAngle(-90.0f); // olha para a frente da casa
		skybox = new SkyBox();
		skybox->load();
		player->setMoveAction(sceneman);
		// add terrain
		sceneman->add(new Terrain(texman));
		// add house
		model = new House(texman);
		sceneman->add(model);
		// add well
		model = new Model(texman);
		model->load("../res/well/well.obj");
		model->translate(-10.0f, 0.0f, 0.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE - 2 * 5.0f, 4.0f, Z_CRATE + 1 * 5.0f);
		sceneman->add(model);
		for(int i = 0; i < CUBE_MAP_COUNT; i++)
		{
			// add crate
			model = new Model(texman);
			model->load("../res/crate/crate.obj");
			model->translate(X_CRATE - cube_map[i][0] * 5.0f, 0.0f, Z_CRATE + cube_map[i][1] * 5.0f);
			sceneman->add(model);
			// add crate
			model = new Model(texman);
			model->load("../res/crate/crate.obj");
			model->translate(X_CRATE - cube_map[i][0] * 5.0f, 2.0f, Z_CRATE + cube_map[i][1] * 5.0f);
			sceneman->add(model);			
		}
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 10.0f, 0.0f, Z_CRATE + -10.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 8.0f, 0.0f, Z_CRATE + -10.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 10.0f, 0.0f, Z_CRATE + -8.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 10.0f, 2.0f, Z_CRATE + -10.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 12.0f, 0.0f, Z_CRATE + -12.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 12.0f, 0.0f, Z_CRATE + -10.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 10.0f, 0.0f, Z_CRATE + -12.0f);
		sceneman->add(model);
		// add crate
		model = new Model(texman);
		model->load("../res/crate/crate.obj");
		model->translate(X_CRATE + 12.0f, 2.0f, Z_CRATE + -12.0f);
		sceneman->add(model);
		// add vase
		model = new Model(texman);
		model->load("../res/vase/vase.obj");
		model->translate(-18.5f, 1.12979f, 6.0f);
		sceneman->add(model);
		// add desk
		model = new Model(texman);
		model->load("../res/desk/desk.obj");
		model->translate(-18.5f, 0.0f, 6.0f);
		sceneman->add(model);
		// add chair chesterfield
		model = new Model(texman);
		model->load("../res/chair_chesterfield/chair_chesterfield.obj");
		model->translate(-12.0f, 0.0f, 12.0f);
		sceneman->add(model);
		// add chair
		model = new Model(texman);
		model->load("../res/chair/chair.obj");
		model->translate(-5.0f, 0.0f, 12.0f);
		sceneman->add(model);
		// add couch
		model = new Model(texman);
		model->load("../res/couch/couch.obj");
		model->translate(-5.0f, 0.0f, 5.0f);
		sceneman->add(model);
		// add trash
		model = new Model(texman);
		model->load("../res/trash/trash.obj");
		model->translate(-5.0f, 0.0f, 3.0f);
		sceneman->add(model);
		// add tree
		/*model = new Model(texman);
		model->load("../res/tree/tree_oak.obj");
		model->translate(10.0f, 0.0f, -2.0f);
		sceneman->add(model);*/

		sceneman->add(new House(texman));
		walking_snd.load("../res/walk.wav");
		running_snd.load("../res/run.wav");
	}

protected:
	bool onInit(int argc, char** argv)
	{
		// qualidade do anti serrilhado
#ifdef WIN32
//		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
#endif
		return GLWindowBase::onInit(argc, argv);
	}

	virtual void getWindowInfo(int& width, int& height, int& bpp, bool& fullscreen, bool& resizable)
	{
		GLWindowBase::getWindowInfo(width, height, bpp, fullscreen, resizable);
	}

	virtual void onResize(int newWidth, int newHeight)
	{
		onCreate();
	}

	void setup3DScene()
	{
		int width = getWidth(), height = getHeight();
		if (height == 0)									// Prevent A Divide By Zero
			height = 1;
		glViewport(0, 0, width, height);					// Set The Current Viewport
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		gluPerspective(45.0f, (GLfloat)width / height, 0.01f, 200.0f);
		// Calculate The Aspect Ratio Of The Window
		glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	virtual void onCreate()
	{
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };

		if(skybox == NULL)
			loadObjects();
		setup3DScene();
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		// Habilita teste de profundidade
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		// Habilita luz
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glShadeModel(GL_SMOOTH);
		// Habilita cor nor objetos
		glEnable(GL_COLOR_MATERIAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	}

	/**
	 * Muda a direção do player
	 */
	void onMouseMove(int x, int y)
	{
		player->updateAngle(x, y);
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		bool moving = player->isMoving();
		switch(key)
		{
		case SDLK_d:
			player->updateState(DIR_RIGHT, false);
			break;
		case SDLK_a:
			player->updateState(DIR_LEFT, false);
			break;
		case SDLK_w:
			player->updateState(DIR_UP, false);
			break;
		case SDLK_s:
			player->updateState(DIR_DOWN, false);
			break;
		case SDLK_SPACE:
			if(!jump)
			{
				jump = true;
				vel = 0.28;
			}
			break;
		case SDLK_LSHIFT:
			running = true;
			player->setVelocityLimit(0.2f);
			if(moving)
			{
				walking_snd.stop();
				running_snd.play();
			}
			break;
		default:
			GLWindowBase::onKeyDown(key, state);
		}
		if(!moving && player->isMoving())
		{
			if(running)
				running_snd.play();
			else
				walking_snd.play();
		}
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyUp(int key, int state)
	{
		bool moving = player->isMoving();
		switch(key)
		{
		case SDLK_d:
			player->updateState(DIR_RIGHT, true);
			break;
		case SDLK_a:
			player->updateState(DIR_LEFT, true);
			break;
		case SDLK_w:
			player->updateState(DIR_UP, true);
			break;
		case SDLK_s:
			player->updateState(DIR_DOWN, true);
			break;
		case SDLK_LSHIFT:
			running = false;
			player->setVelocityLimit(0.1f);
			if(moving)
			{
				running_snd.stop();
				walking_snd.play();
			}
			break;
		default:
			GLWindowBase::onKeyUp(key, state);
		}
		if(moving && !player->isMoving())
		{
			walking_snd.stop();
			running_snd.stop();
		}
	}

	virtual void render()
	{
		// limpa o buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// luz do sol
		if(light_position[0] <= -8.0f)
			light_position[0] = 8.0f;
		light_position[0] -= 0.01f;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glPushMatrix();
		player->look();

		glPushMatrix();
		skybox->render();
		glPopMatrix();

		player->move();
		if(jump)
			vel -= 0.01;
		/* jump test */
		if(!player->setYDist(player->getYDist() + vel))
		{
			if(jump)
			{
				jump = false;
				vel = -0.01f;
			}
		}
		else if(!jump)
			jump = true;
		sceneman->render();
		glPopMatrix();
		// mostra os desenhos
		swapBuffers();
		sprintf(str, "FPS: %.2f", getFPS());
		setTitle(str);
	}

public:
	RenderWindow()
	{
		texman = new TextureManager();
		sceneman = new SceneManager();
		skybox = NULL;
		player = NULL;
		jump = true;
		vel = -0.01f;
		light_position[0] = 0.0f;
		light_position[1] = 1.0f;
		light_position[2] = 1.0f;
		light_position[3] = 0.0f;
		running = false;
	}
	~RenderWindow()
	{
		if(player != NULL)
			delete player;
		if(skybox != NULL)
			delete skybox;
		delete sceneman;
		delete texman;
	}
};

int main(int argc, char *argv[])
{
	RenderWindow lp;

	lp.setTitle("Environment");
	return lp.start(argc, argv);
}

