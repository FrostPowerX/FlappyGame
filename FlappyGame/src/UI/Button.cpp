#include "Button.h"

#include "Utilities/Utils.h"

namespace button
{
	Button Create(Rectangle graph, std::string text, int fontSize, Color textColor)
	{
		Button newB;

		newB.graph = graph;

		SetPosition(newB, Vector2{ graph.x, graph.y });

		newB.text.text = text;
		newB.text.font = fontSize;
		newB.text.color = textColor;

		newB.isMouseOnTop = false;
		newB.isPressed = false;
		newB.isReleased = false;

		SetText(newB, text);

		return newB;
	}

	Vector2 GetCenterPosition(Button button)
	{
		Vector2 centerPosition;

		centerPosition.x = button.graph.x + (button.graph.width / 2);
		centerPosition.y = button.graph.y + (button.graph.height / 2);

		return centerPosition;
	}

	void SetPosition(Button& button, Vector2 newPosition)
	{
		button.graph.x = newPosition.x - (button.graph.width / 2);
		button.graph.y = newPosition.y - (button.graph.height / 2);
	}

	bool MouseOnTop(Button& button)
	{
		Vector2 mousePosition = GetMousePosition();

		float minValueX = button.graph.x;
		float minValueY = button.graph.y;

		float maxValueX = button.graph.x + button.graph.width;
		float maxValueY = button.graph.y + button.graph.height;

		bool onTopX = (mousePosition.x >= minValueX && mousePosition.x <= maxValueX);
		bool onTopY = (mousePosition.y >= minValueY && mousePosition.y <= maxValueY);

		if (onTopX && onTopY)
		{
			button.isMouseOnTop = true;
		}
		else
		{
			button.isMouseOnTop = false;
		}

		return true;
	}

	bool IsPressed(Button& button)
	{
		bool isReleassed = false;

		if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT))
			if (button.isMouseOnTop)
			{
				isReleassed = true;
			}

		if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
		{
			if (button.isMouseOnTop)
				button.isPressed = true;
			else
				button.isPressed = false;
		}
		else
			button.isPressed = false;

		return isReleassed;
	}

	void SetText(Button& button, std::string text)
	{
		button.text.text = text;

		button.text.position.x = button.graph.x + (button.graph.width / 2) - (MeasureText(button.text.text.c_str(), button.text.font) / 2);
		button.text.position.y = button.graph.y + (button.graph.height / 2) - (button.text.font / 2);
	}

	void Draw(Button button)
	{
		Color colorUsed;

		if (button.isPressed)
			colorUsed = GRAY;
		else if (button.isMouseOnTop)
			colorUsed = DARKGRAY;
		else
			colorUsed = BLACK;

		DrawRect(button.graph, colorUsed);

		text::Draw(button.text);
	}
}

