#include "MainMenu.h"

#include "GameLoop.h"

#include "UI/Button.h"
#include "Utilities/SoundManager.h"

namespace game::scenes::mainmenu
{
	const std::string GameVersion = "Version 1.0";
	const int maxButtons = 4;

	button::Button buttons[maxButtons];

	static bool wasOnTop[maxButtons] = {false};
	static bool isOnTop[maxButtons] = {false};



	void Init()
	{
		float x = (static_cast<float>(GetScreenWidth()) / 2.f);
		float y = 50;

		Rectangle graph = { x, y, button::ButtonWidth, button::ButtonHeight };

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i] = button::Create(graph);

			graph.y += button::ButtonHeight * 1.5f;
		}

		button::SetText(buttons[0], "1 Player");
		button::SetText(buttons[1], "2 Players");
		button::SetText(buttons[2], "Credits");
		button::SetText(buttons[3], "Exit");
	}



	void Input()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			if (button::IsPressed(buttons[i]))
			{
				AddToBuffer(utils::soundManager::Sounds::Click);
				currentScene = static_cast<Scene>(i + 1);
				if (static_cast<Scene>(i + 1) == Scene::GameplayMultiplayer)
				{
					ChangeMusic(utils::soundManager::Musics::Game);
					isMultiplayer = true;
					timer = 0;
				} else if (static_cast<Scene>(i + 1) == Scene::Gameplay)
				{
					ChangeMusic(utils::soundManager::Musics::Game);
					isMultiplayer = false;
				}
			}
		}
	}



	void Update()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			isOnTop[i] = button::MouseOnTop(buttons[i]);
			if (isOnTop[i])
			{
				if (!wasOnTop[i])
					AddToBuffer(utils::soundManager::Sounds::Hover);
				wasOnTop[i] = true;
			}
			else
				wasOnTop[i] = false;
		}
	}



	void Draw()
	{
		for (int i = 0; i < maxButtons; i++)
		{
			button::Draw(buttons[i]);
		}

		DrawText(GameVersion.c_str(), 1, screenHeight - 10, 10, BLACK);
	}



	void DeInit()
	{}
}