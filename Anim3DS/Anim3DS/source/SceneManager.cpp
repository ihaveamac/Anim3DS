/* This file is part of Anim3DS!

Copyright (C) 2017 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

#include "SceneManager.h"

SceneManager* SceneManager::Instance = NULL;

SceneManager* SceneManager::instance()
{
		if (!Instance)   
			Instance = new SceneManager;

		return Instance;
}

// Scene Manager Data initialization
void SceneManager::Start()
{
	m_out = false;
	ReadData();
}

// We read the data from our .sav
void SceneManager::ReadData()
{	
	m_times_we_have_run_the_program = 1;
	
	// We try to read the .sav file
	std::ifstream myReadFile(DATA_FILE);

	// If it exists
	if (myReadFile)
	{
		// We set our data and call to the splashScreen
		myReadFile >> m_times_we_have_run_the_program;
		m_actualScene = new SplashScreen();
	}
	else // If it doesn't exists
	{
		// We create the .sav file
		std::ofstream outfile(DATA_FILE);
		outfile << m_times_we_have_run_the_program;
		outfile.close();

		// First time we don't need to show the splashscreen. If we want, we can but meh
		m_actualScene = new GameScreen();
	}
}

// We set the new scene
void SceneManager::setActualScene(SCENES _scene)
{
	// We delete the pointer of the actual scene
	delete (m_actualScene);

	// We set the new scene
	switch (_scene)
	{
	case SPLASH:
		m_actualScene = new SplashScreen();
		break;
	case GAME:
		m_actualScene = new GameScreen();
		break;
	}
}

// We call every function needed: Check User inputs, Update the game, and of course, paint everything
void SceneManager::Update()
{
	if (!m_actualScene)
	{
		return;
	}

	m_actualScene->CheckInputs();
	m_actualScene->Update();
	m_actualScene->Draw();
}

// We check if we are exiting
bool SceneManager::isOut()
{
	return m_out;
}

// Simple exiting
void SceneManager::exitGame()
{
	m_out = true;
}

// We save and exit the program
void SceneManager::SaveDataAndExit()
{
	m_times_we_have_run_the_program++;

	// We overwrite our .sav file with new data
	std::ofstream outfile(DATA_FILE);
	outfile << m_times_we_have_run_the_program;
	outfile.close();

	m_out = true;

	//delete(m_actualScene);
}