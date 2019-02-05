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
	ball(Vec2(400.0f + 40.0f, 400.0f), Vec2(-300.0f, -300.0f)),
	wall(0.0f, 0.0f, float(Graphics::ScreenWidth), float(Graphics::ScreenHeight)),
	pad(Vec2(400.0f, 550.0f), 50.0f, 15.0f)
{
	const Color colors[5] = { Colors::Blue, Colors::Cyan, Colors::Red, Colors::Green, Colors::Magenta };
	const Vec2 topLeft(40, 40);

	int i = 0;
	for (int y = 0; y < bricksDown; ++y)
	{
		for (int x = 0; x < bricksAcross; ++x)
		{
			bricks[i] = Brick( RectF(
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

	ball.Update(dt);
	pad.Update(wnd.kbd, dt);

	pad.DoWallCollision(wall);

	for (Brick& b : bricks)
	{
		if (b.DoBallCollision(ball))
		{
			soundBrick.Play();
			break;
		}
	}

	if (padCollision)
	{
		++padTimer;
	}
	if (padTimer >= 30)
	{
		padCollision = false;
		padTimer = 0;
	}

	if (pad.DoBallCollision(ball) && !padCollision)
	{
		padCollision = true;
		soundPad.Play();
	}

	if (ball.DoWallCollision(wall) )
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

	ball.Draw(gfx);
	pad.Draw(gfx);
}
