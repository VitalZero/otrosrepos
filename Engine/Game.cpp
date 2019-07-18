/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	soundPad(L"sounds\\arkpad.wav"),
	soundBrick(L"sounds\\arkbrick.wav"),
	pad(Vec2(400.0f, 550.0f), 50.0f, 8.0f),
	ball(Vec2(400.0f, 400.0f), Vec2(-300.0f, -300.0f), pad),
	wall( 135.0f, 70.0f, float(Graphics::ScreenWidth) -135.0f, float(Graphics::ScreenHeight), 5)
{
	const Color colors[6] = { Colors::Blue, Colors::Cyan, Colors::Red, Colors::Green, Colors::Magenta, Colors::Yellow};
	const Vec2 topLeft(wall.GetRect().left, wall.GetRect().top+50);

	int i = 0;
	int type = 0;

	for (int y = 0; y < bricksDown; ++y)
	{
		if (y == 2)
			type = 1;
		else
			type = 0;

		for (int x = 0; x < bricksAcross; ++x)
		{
			bricks[i] = Brick(RectF(
				Vec2(float(x) * brickWidth, float(y) * brickHeight) + topLeft,
				brickWidth, brickHeight), colors[y], type);
			++i;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	

	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (!ball.Died())
	{
		ball.Update(dt);
		pad.Update(wnd.kbd, dt);
	}

	pad.DoWallCollision(wall.GetRect());

	bool collisionHappened = false;
	float curColDist;
	int curColIndex;

	for (int i = 0; i < nBricks; ++i)
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			const float newCurColDist = (ball.GetPos() - bricks[i].GetCenter()).GetLengthSq();

			if (collisionHappened)
			{
				if (newCurColDist <  curColDist)
				{
					curColDist = newCurColDist;
					curColIndex = i;
				}
			}
			else
			{
				curColDist = newCurColDist;
				curColIndex = i;
				collisionHappened = true;
			}
		}
	}

	if (collisionHappened)
	{
		pad.ResetCoolDown();
		bricks[curColIndex].ExecuteBallCollision(ball);
		soundBrick.Play();
	}

	if (pad.DoBallCollision(ball))
	{
		soundPad.Play();
	}

	if (ball.DoWallCollision(wall.GetRect()) )
	{
		pad.ResetCoolDown();
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	

	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	if (!ball.Died())
	{
		ball.Draw(gfx);
		pad.Draw(gfx);
	}

	wall.Draw(gfx);
}
