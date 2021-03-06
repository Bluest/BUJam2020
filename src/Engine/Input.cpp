#include "Input.h"

bool Input::keyHold(const SDL_Keycode& _key)
{
	for (auto it = keysHeld.begin(); it != keysHeld.end(); it++)
	{
		if (*it == _key)
		{
			return true;
		}
	}

	return false;
}

bool Input::keyPress(const SDL_Keycode& _key)
{
	for (auto it = keysPressed.begin(); it != keysPressed.end(); it++)
	{
		if (*it == _key)
		{
			return true;
		}
	}

	return false;
}

bool Input::keyRelease(const SDL_Keycode& _key)
{
	for (auto it = keysReleased.begin(); it != keysReleased.end(); it++)
	{
		if (*it == _key)
		{
			return true;
		}
	}

	return false;
}

bool Input::mouseHold(const int& _button)
{
	for (auto it = mouseHeld.begin(); it != mouseHeld.end(); it++)
	{
		if (*it == _button)
		{
			return true;
		}
	}

	return false;
}

bool Input::mousePress(const int& _button)
{
	for (auto it = mousePressed.begin(); it != mousePressed.end(); it++)
	{
		if (*it == _button)
		{
			return true;
		}
	}

	return false;
}

bool Input::mouseRelease(const int& _button)
{
	for (auto it = mouseReleased.begin(); it != mouseReleased.end(); it++)
	{
		if (*it == _button)
		{
			return true;
		}
	}

	return false;
}

SDL_Point Input::mousePosition()
{
	SDL_Point position;
	SDL_GetMouseState(&position.x, &position.y);

	return position;
}

bool Input::processInput()
{
	keysPressed.clear();
	keysReleased.clear();
	mousePressed.clear();
	mouseReleased.clear();

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN: { processKeyDown(event.key.keysym.sym); break; }
		case SDL_KEYUP: { processKeyUp(event.key.keysym.sym); break; }
		case SDL_MOUSEBUTTONDOWN: { processMouseDown(event.button.button); break; }
		case SDL_MOUSEBUTTONUP: { processMouseUp(event.button.button); break; }
		case SDL_QUIT: { return false; }
		}
	}

	return true;
}

void Input::processKeyDown(const SDL_Keycode& _key)
{
	if (std::find(keysHeld.begin(), keysHeld.end(), _key) == keysHeld.end())
	{
		keysPressed.push_back(_key);
	}

	if (std::find(keysHeld.begin(), keysHeld.end(), _key) == keysHeld.end())
	{
		keysHeld.push_back(_key);
	}
}

void Input::processKeyUp(const SDL_Keycode& _key)
{
	keysReleased.push_back(_key);
	keysHeld.remove(_key);
}

void Input::processMouseDown(const int& _button)
{
	mousePressed.push_back(_button);
	mouseHeld.push_back(_button);
}

void Input::processMouseUp(const int& _button)
{
	mouseReleased.push_back(_button);
	mouseHeld.remove(_button);
}
