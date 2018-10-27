#ifndef __ModuleFonts_H__
#define __ModuleFonts_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

class ModuleFonts : public Module
{
public:

	ModuleFonts(Application* app, bool start_enabled = true);
	virtual ~ModuleFonts();

	// Load Font
	int Load(const char* texture_path, const char* characters, uint rows = 1);
	void Unload(int font_id);

	// Create a surface from text
	void BlitText(int x, int y, int bmp_font_id, const char* text, float scale = 1.0f) const;

private:

	Font	 fonts[MAX_FONTS];
};


#endif // __ModuleFonts_H__
