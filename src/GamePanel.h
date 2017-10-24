#ifndef __GAMEPANEL_H_
#define __GAMEPANEL_H_

#include "Shader.h"

#include "Panel.h"

#include "Canvas.h"

#include "Button.h"

#include "Rect.h"

class GamePanel : public Panel
{
	public:
		GamePanel(Window*, Camera*);
		~GamePanel();
		void render();
		void update();
		void setActive();
		Shader2t* shader;
		Canvas* canvas;
		Button* button;
};

#endif
