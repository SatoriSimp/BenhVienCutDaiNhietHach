#pragma once
#include<iostream>
#include<ctime>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<algorithm>
#include<vector>
#include<random>
#include<chrono>
#include<filesystem>
#include<fstream>
/*
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
*/

HANDLE h = GetStdHandle(((DWORD)-11));

#define setColor(n) SetConsoleTextAttribute(h, n)
#define RED 12
#define LI_YELLOW 14
#define CIRNO 9
#define LI_GREEN 10
#define GREEN 2
#define WHITE 15
#define BO_RED 4
#define PURPLE 5
#define LI_PURPLE 13
#define DA_YELLOW 6
#define LI_CIRNO 11
#define GRAY 8
#define WHITE 7
#define LI_WHITE 15

#pragma comment(lib, "winmm.lib")


short pack = 0, risk = 0;
bool skipTurnBanned = false, forbidInteruptMenuTheme = false, phalanx = false, allySupport = false;
bool runningProgram = true, reduceManaRequirement = false, recollectOpStart = false, recollectOperationAccomplish = false, towerMode = false;
int fighterBaseAD = 0,
	minhphanAP = 0, minhphanMRpen = 0;
bool flag = false;
int turn = 0;

int avoidRetardInput(std::string notif)
{
	int input, failureCount = 0;
	std::cout << notif;
	std::cin >> input;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		failureCount++;
		setColor(12);
		if (failureCount <= 3)
		{
			std::cout << "\nInvalid input detected! Please try again.\n";
		}
		else
		{
			std::cout << "\nWhat the fuck are you actually trying to prove, you scumbag piece of shit?\nDoes someone there still think their parents'd be of proud of their kid growing up to be this kind of living trashbag messing around with my program? Fuck you and hope you get what you deserve, brainless deadass piece of living hell!\n";
			Sleep(8000);
			printf("\nOh and I'm removing Mudrock from support unit also, because, yes, fuck you.\n");
		}
		setColor(7);
		std::cout << notif;
		std::cin >> input;
	}
	return input;
}

int avoidRetardInput(std::string notif, short lowerEnd, short upperEnd)
{
	int input, failureCount = 0;
	std::cout << notif;
	std::cin >> input;
	while (std::cin.fail() || input > upperEnd || input < lowerEnd)
	{
		std::cin.clear();
		std::cin.ignore();
		failureCount++;
		setColor(12);
		if (failureCount <= 3)
		{
			std::cout << "\nInvalid input detected! Please try again.\n";
		}
		else
		{
			std::cout << "\nWhat the fuck are you actually trying to prove, you scumbag piece of shit?\nI hope your parents're proud of their children grew up to be this kind of living trashbag messing around with my program. Fuck you and hope you get what you deserve. Dear random brainless deadass fucker!\n";
			Sleep(8000);
			printf("\nOh and I'm removing Mudrock from support unit, because, yes, fuck you.\n");
		}
		setColor(7);
		std::cout << notif;
		std::cin >> input;
	}
	return input;
}

#include ".\Headers\Entities.h"
#include ".\Headers\Enemies.h"
#include ".\Headers\Player_Entities.h"
#include ".\Headers\Damage_and_spell.h"
#include ".\Headers\playerDataFunctions.h"
#include ".\Headers\battleProgress.h"
#include ".\Headers\menu_choices.h"
