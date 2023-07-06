#pragma once
#include "TextRenderer.h"

// Class to render text on screen for some duration
class TextRendererTimer : public TextRenderer{
	Uint32 renderEnd;

public:
	TextRendererTimer();
	void setTimer(int milliseconds);
	bool active();
};

