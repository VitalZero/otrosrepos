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
	ball(Vec2(60.0f, 60.0f), Vec2(300.0f, 300.0f) ),
	wall(0.0f, 0.0f, float(Graphics::ScreenWidth), float(Graphics::ScreenHeight) ),
	brick(RectF(400.0f, 400.0, 460.0f, 425.0f), Colors::Red)
{
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

	if (brick.DoBallCollision(ball))
	{
		soundBrick.StopOne();
		soundBrick.Play();
	}

	if (ball.DoWallCollision(wall) )
	{
		soundPad.StopOne();
		soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	brick.Draw(gfx);
	ball.Draw(gfx);
}
