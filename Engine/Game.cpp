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
	ball(Vec2(400.0f, 400.0f), Vec2(-300.0f, -300.0f)),
	pad(Vec2(400.0f, 550.0f), 50.0f, 10.0f), 
	wall( 102.5f, 50.0f, float(Graphics::ScreenWidth) -102.5f, float(Graphics::ScreenHeight), 5)
{
	const Color colors[5] = { Colors::Blue, Colors::Cyan, Colors::Red, Colors::Green, Colors::Magenta };
	const Vec2 topLeft(wall.GetRect().left, wall.GetRect().top);

	int i = 0;
	for (int y = 0; y < bricksDown; ++y)
	{
		for (int x = 0; x < bricksAcross; ++x)
		{
			bricks[i] = Brick(RectF(
				Vec2(float(x) * brickWidth, float(y) * brickHeight) + topLeft,
				brickWidth, brickHeight), colors[y]);
			++i;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	dt = ft.Mark();

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
		bricks[curColIndex].ExecuteBallCollision(ball);
		soundBrick.Play();
	}

	if (padCollision)
	{
		++padTimer;
	}
	else
	{
		if (pad.DoBallCollision(ball))
		{
			padCollision = true;
			soundPad.Play();
		}
	}
	if (padTimer >= 20)
	{
		padCollision = false;
		padTimer = 0;
	}


	if (ball.DoWallCollision(wall.GetRect()) )
	{
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
