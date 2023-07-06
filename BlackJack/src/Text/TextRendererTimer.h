#pragma once
#include "TextRenderer.h"
#include "..\Timer\Timer.h"

// Class to render text on screen for some duration
class TextRendererTimer : public TextRenderer, public Timer {

public:
	TextRendererTimer();

};

