#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

#include<string.h>

// Constructor
ModuleFonts::ModuleFonts(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleFonts::~ModuleFonts()
{}

// Load new texture from file path
int ModuleFonts::Load(const char* path, const char* characters, uint rows)
{
	int id = -1;

	if (path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", path, MAX_FONTS);
		return id;
	}

	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture
	fonts[id].len = strlen(characters); // len: length of the table

										// TODO 1: Finish storing font data
	strcpy_s(fonts[id].table, characters);
	fonts[id].row_chars = fonts[id].len / rows;
	App->textures->GetSize(tex, fonts[id].char_w, fonts[id].char_h);
	fonts[id].char_w /= fonts[id].row_chars;
	fonts[id].char_h /= rows;

	LOG("Successfully loaded BMP font from %s", path);

	return id;
}

void ModuleFonts::Unload(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleFonts::BlitText(int x, int y, int font_id, const char* text, float scale) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		// TODO 2: Find the character in the table and its position in the texture, then Blit
		for (int j = 0; j < MAX_FONT_CHARS; j++)
		{
			if (text[i] == fonts[font_id].table[j])
			{
				int row = (j / fonts[font_id].row_chars) + 1;
				int column = (j + 1) - ((row - 1) * fonts[font_id].row_chars);
				SDL_Rect size;
				size.x = (column - 1) * fonts[font_id].char_w;
				size.y = (row - 1) * fonts[font_id].char_h;
				size.h = fonts[font_id].char_h;
				size.w = fonts[font_id].char_w;
				App->renderer->Blit(fonts[font_id].graphic, x + (i * fonts[font_id].char_w * scale), y, &size, scale);
				break;
			}
		}
	}
}
