#include "Obstacule.h"

#include "Utilities/Utils.h"

namespace game
{
	namespace obstacule
	{
		const float separation = 1.7f;

		void Move(Obstacule& o);

		Obstacule Create(float x, float y, float width, float height, float speed, bool isAlive)
		{
			Obstacule newO;

			Rectangle newR;

			newR.x = x - width / 2;
			newR.y = y - height / 2;

			newR.width = width;
			newR.height = height;

			newO.body1 = newR;
			newO.body1.y += newO.body1.height / separation;

			newO.body2 = newR;
			newO.body2.y -= newO.body2.height / separation;

			newO.dir = Vector2{ 0, 0 };

			newO.speed = speed;
			newO.isAlive = isAlive;

			return newO;
		}

		void Update(Obstacule& o)
		{
			o.dir.x = -1.f;

			Move(o);
		}

		void Draw(Obstacule& o)
		{
			DrawRect(o.body1, RED);
			DrawRect(o.body2, RED);
		}

		void SetPosition(Obstacule& o, Vector2 newPos)
		{
			o.body1.x = newPos.x;
			o.body1.y = newPos.y + o.body1.height / separation;

			o.body2.x = newPos.x;
			o.body2.y = newPos.y - o.body2.height / separation;
		}

		void Move(Obstacule& o)
		{
			o.body1.x += o.dir.x * o.speed * GetFrameTime();
			o.body1.y += o.dir.y * o.speed * GetFrameTime();

			o.body2.x += o.dir.x * o.speed * GetFrameTime();
			o.body2.y += o.dir.y * o.speed * GetFrameTime();
		}
	}
}