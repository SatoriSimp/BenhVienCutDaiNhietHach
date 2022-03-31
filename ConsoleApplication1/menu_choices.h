#pragma once

void chooseRune(Entities* player)
{
	if (player->role == "blank") return;
	int rune1, rune2, rune3, bigRune;
	setColor(14);
	std::cout << "Select " << player->role << "'s Rune!", setColor(7);
	rune1 = avoidRetardInput("\nChoose 1st rune:\n1. Max health +150\n2. Resistances +50\n3. Attack damage +30/+50 (adaptive)\n4. Recommended Rune (auto select)\nYour choice: ");

	if (rune1 != 4)
	{
		switch (rune1)
		{
		case 1:
			player->maxHealth += 150, player->health += 150;
			break;
		case 2:
			player->baseAR += 50, player->baseMR += 50;
			player->armor = player->baseAR, player->magicRes = player->baseMR;
			break;
		default:
			player->attackDmg > player->abilityPower ? player->baseAD += 30, player->attackDmg += 30 : player->abilityPower += 50, player->baseAP += 50;
			break;
		}
		rune2 = avoidRetardInput("\nChoose 2nd rune:\n1. Base mana +2\n2. Attack damage +30/+50 (adaptive)\n3. Crit chance +10%\nYour choice: ");
		switch (rune2)
		{
		case 2:
			player->attackDmg > player->abilityPower ? player->baseAD += 30, player->attackDmg += 30 : player->abilityPower += 50, player->baseAP += 50;
			break;
		default:
			player->critUp = 10;
			break;
		case 1:
			player->mana += 2;
			break;
		}
		rune3 = avoidRetardInput("\nChoose 3rd rune:\n1. Resistances +50\n2. Armor penetration +5%\n3. Magic penetration +5%\nYour choice: ");
		switch (rune3)
		{
		case 1:
			player->baseAR += 50, player->baseMR += 50;
			player->armor = player->baseAR, player->magicRes = player->baseMR;
			break;
		case 2:
			player->ARpen = 5;
			break;
		default:
			player->MRpen = 5;
			break;
		}
		rune1 > 3 ? rune1 = 3 : rune1, rune2 > 3 ? rune2 = 3 : rune2, rune3 > 3 ? rune3 = 3 : rune3;
		int sumRune = rune1 + rune2 + rune3;
		std::cout << "Final rune type: ";
		if (sumRune <= 5)
		{
			bigRune = avoidRetardInput("Defensive\n1. Reincarnation: After everyturn, restores 3% max health\n2. Cooper Seal: Attacks and abilities deal an additional magic damage equals 8% self max HP\n3. Solo - Auto Protect: In the first 3 turns of the battle, resistances +290%\n3. Teamfight - Creed Field: Healing grants to other allies has +15% effectiveness\nSelect: ");
			switch (bigRune)
			{
			case 1:
			{
				player->reincarnation = true;
				break;
			}
			case 2:
			{
				player->cooperSeal = true;
				break;
			}
			default:
			{
				player->autoProtect = true;
				break;
			}
			}
		}
		else
		{
			bigRune = avoidRetardInput("Offensive\n1. Insult to the Injury: Attack against target with less than 50% HP deals extra 20% damage\n2. Exploit Weaknesses: Critical attack deals an additional 135 + 10% true damage (multiple hits-attack only applies the bonus damage once)\n3. Deathmatch : Attack against target with more than 60% HP deals an additional 15% damage. When self has less than 40% health, attack deals extra 15% damage\nYour choice: ");
			switch (bigRune)
			{
			case 1:
			{
				player->insult = true;
				break;
			}
			case 2:
			{
				player->exploit = true;
				break;
			}
			default:
			{
				player->deathmatch = true;
				break;
			}
			}
		}
	}
	else
	{
		printf("\nRune pack selected: "), setColor(9);
		switch (player->range)
		{
		case 1: case 12:
			printf("ATK +30 / Mana +2 / Resistance +50 / Reincarnation");
			player->baseAD += 30, player->attackDmg += 30;
			player->mana += 2;
			player->baseAR += 50, player->baseMR += 50;
			player->armor += 50, player->magicRes += 50;
			player->reincarnation = true;
			break;
		case 2: case 5: case 10: case 7:
			player->range != 6 && player->range != 7 ? printf("HP +150 / Mana +2 / Resistance +50 / Cooper Seal") : printf("HP +150 / Mana +2 / Resistance +10 / Reincarnation");
			player->maxHealth += 150, player->health += 150;
			player->mana += 2;
			player->baseAR += 10, player->baseMR += 10;
			player->armor += 50, player->magicRes += 50;
			player->range != 6 && player->range != 7 ? player->cooperSeal = true : player->reincarnation = true;
			break;
		case 3:
			printf("ATK +30 / Crit chance +10% / Armor penetration +5% / Exploit Weaknesses");
			player->baseAD += 30, player->attackDmg += 30;
			player->critUp += 10, player->ARpen += 5;
			player->exploit = true;
			break;
		case 4:
			printf("ATK +50 / Mana +2 / Magic penetration +5% / Deathmatch");
			player->baseAP += 50, player->abilityPower += 50;
			player->mana += 2, player->MRpen += 5;
			player->deathmatch = true;
			break;
		case 6:
			printf("ATK +30 / Mana +2 / Armor penetration +5% / Insult to the Injury");
			player->baseAD += 30, player->attackDmg += 30;
			player->mana += 2;
			player->insult = true;
			break;
		case 8:
			printf("ATK +60 / Armor penetration +5% / Exploit Weaknesses");
			player->baseAD += 60, player->attackDmg += 60;
			player->ARpen += 5;
			player->exploit = true;
			break;
		case 9:
			printf("HP +150 / Mana +2 / Armor penetration +5% / Cooper Seal");
			player->maxHealth += 150, player->health += 150;
			player->mana += 2;
			player->ARpen += 5;
			player->cooperSeal = true;
			break;
		case 11:
			printf("ATK +50 / Mana +2 / Resistance +50 / Creedfield");
			player->baseAP += 50, player->abilityPower += 50;
			player->baseAR += 50, player->baseMR += 50;
			player->armor = player->baseAR, player->magicRes = player->baseMR;
			player->mana += 2, player->autoProtect = true;
			break;
		default:
			break;
		}
		printf("\n");
	}
}

void chooseSong()
{
	setColor(8);
	bool errorChoice = false;
	int songSelection = avoidRetardInput("Choose song:\n1. Dusk dragon\n2. Towerfierce\n3. Lostmemory\n4. Church\n5. Shield\n6. Kalt'sit Team\n7. Random pick\n8. Select custom song\n0. No song pls im fine\nInput: ", 0, 8);
	if (songSelection != 8)
	{
		songSelection == 7 ? songSelection = rand() % (6 - 1 + 1) + 1 : songSelection = songSelection;
		songSelection != 0 ? printf("Now playing: ") : printf("No song was choosen!");
	}
	switch (songSelection)
	{
	case 0:
		PlaySound(NULL, NULL, NULL);
		break;
	case 1:
		PlaySound(TEXT("ost\\duskdragon.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Dusk dragon");
		break;
	case 2:
		PlaySound(TEXT("ost\\towerfierce.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Towerfierce");
		break;
	case 3:
		PlaySound(TEXT("ost\\lostmemory.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Lost memory");
		break;
	case 4:
		PlaySound(TEXT("ost\\church.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Church");
		break;
	case 5:
		PlaySound(TEXT("ost\\shield.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Shield");
		break;
	case 6:
		PlaySound(TEXT("ost\\kalt.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Kalt'sit Team");
		break;
	case 8:
		std::string foldName = "ost\\", tempSong;
		std::string songName;
		setColor(8);
		printf("\nEnter song's name to play (song must be placed in \"ost\" folder and saved as .wav format, there's no need to type the \".wav\" format down): ");
		setColor(13);
		std::cin >> songName;
		tempSong = foldName + songName;
		songName = tempSong;
		//songName._Copy_s('w', songName[std::size(songName) - 3], songName[std::size(songName)]);
		songName += ".wav";

		if (std::filesystem::exists(songName))
		{
			std::wstring song = std::wstring(songName.begin(), songName.end());
			LPCWSTR songPlay = song.c_str();
			PlaySound(songPlay, NULL, SND_LOOP | SND_ASYNC);
			Sleep(2000);
			std::cout << "\nNow playing: " << songName;
		}
		else
		{
			setColor(12);
			printf("\nError! No song was found!\n\n");
			errorChoice = true;
			chooseSong();
		}

		break;
	}
	if (!errorChoice) printf("\n\n");
	setColor(7);
}

void diaryProgress()
{
	setColor(10);
	printf("\nFinding diary");
	for (int i = 0; i < 4; i++)
	{
		Sleep(1000);
		if (i < 3) printf(".");
	}
	std::cout << std::endl;
	setColor(14);
	std::cout << "\n<<--------------------------DIARY OPENED!-------------------------->>\n", setColor(6);
	std::cout << "A small notebook was found slightly burnt in the corner of an abandoned house. It contains ones past.\nThough some pages are still missing and somewhat hard to read, recollecting it may still be doable.\nHowever, doing so requires a decent amount of knowledge and certain combat experience.\nProve that you're worthy, and you can perhaps reach to its true value...\n", setColor(7);

diaryList:
	reduceManaRequirement = false;
	std::fstream diaryDat("saves\\diary.dat");
	std::string importDiary;
	bool reCleared = false;
	bool proceedOperation = false, unlockedDiary = false;
	char diarySelect, startOP;
	std::cout << "\nPage 1. Unnamed diary #1\nPage 2. Unnamed diary #2\nPage 3. Unnamed diary #3\nX. Back to main menu\nOpen page: ";
	std::cin >> diarySelect;
	if (diarySelect == 'x' || diarySelect == 'X') return;
	printf("\nPress 'S' for fast skip, others to read manually: ");
	char skip;
	bool skippin = false;
	std::cin >> skip;
	if (skip == 'S' || skip == 's') skippin = true;
	switch (diarySelect)
	{
	case '1':
	{
		std::string intro = "\nPage number 1\n\nDate: 1/5/XX40\nWeather: Overall fresh\n\n<------------------------------------------------------------->\n";
		Sleep(1900);
		for (int i = 0; i < std::size(intro); i++)
		{
			int waitTime = 100;
			if (i < 14) { setColor(13); }
			else if (i < 54) { setColor(11); waitTime = waitTime * 3 / 4; }
			else { setColor(12); waitTime /= 5; }
			if (skippin) waitTime = 0;
			Sleep(waitTime);
			std::cout << intro[i];
		}
		Sleep(1000);
		std::string plainText;
		plainText += "\nThe soldiers finally returned home after 2 weeks. Their mission was about destroying a newborn goblin village.\nThough goblins usually ain't too hard to deal with, their trip took longer than I thought.\nMoreover, the expressions on their faces didn't seem good at all.";
		plainText += "\nI knew something was wrong, and asked them what happened.\nThey told many things, while the fear they're wearing still remains\nThe one with the sword told me that,";
		plainText += " there were only 2 goblins that seemed notable: one uses hammer and the other uses magic.";
		plainText += "\nThe one with the shield told me that, ";
		plainText += "the goblins somehow felt significantly stronger than usual.";
		plainText += "\nThe one holding a potion told me that, ";
		plainText += "their equipment felt like almost broken down, and their spirit were like halved.\n";
		plainText += "And finally, something eerie happened: out of the blue, ";
		plainText += "an Orc showed up";
		plainText += ".\nIts strength is madnessly terrifying as it destroyed eveything within range in just a blink of the eye.\nYet, here is the most scariest part: ", setColor(14);
		plainText += "\"it didn't even look alive\"!\n";
		plainText += "Having told me that, they fainted away.\n";
		for (int i = 0; i < std::size(plainText); i++)
		{
			if (!skippin)
			{
				if (i != 0 && (plainText[i - 1] == '.' || plainText[i - 1] == '\n' || plainText[i - 1] == ':')) Sleep(1000);
				else if (i != 0 && plainText[i - 1] == ',') Sleep(500);
				else Sleep(25);
			}
			if ((i >= 432 && i < 433 + 86) || (i >= 431 + 86 + 40 + 2 && i < 433 + 86 + 99 - 1) || (i >= 431 + 86 + 99 + 41 && i < 431 + 86 + 99 + 41 + 81 - 1) || (i >= 431 + 86 + 99 + 41 + 81 - 2 + 55 + 4 && i <= 431 + 86 + 99 + 41 + 81 - 2 + 57 + 19) || (i >= 431 + 86 + 99 + 41 + 81 - 2 + 57 + 19 + 141 && i <= 431 + 86 + 99 + 41 + 81 - 2 + 57 + 19 + 141 + 28))
			{
				setColor(14);
			}
			else
			{
				setColor(8);
			}
			std::cout << plainText[i];
		}

		setColor(6);
		std::ifstream diaryStuff("saves\\data.dat");
		std::string unlockCondition;
		short packCompleted = 0;
		while (diaryStuff >> unlockCondition)
		{
			if (unlockCondition == "NR" || unlockCondition == "CM" || unlockCondition == "RS") packCompleted++;
			if (packCompleted >= 3)
			{
				unlockedDiary = true;
				break;
			}
		}
		diaryStuff.close();
		if (unlockedDiary)
		{
			while (diaryDat >> importDiary)
			{
				if (importDiary == "RC_1_CLR") {
					reCleared = true;
					break;
				}
			}
			diaryDat.close();

			if (reCleared)
			{
				setColor(10);
				std::cout << "\nRecollection for this diary is already cleared!\nRedo it? (Y/N) ", setColor(14);
			}
			else
			{
				std::cout << "\nStart recollection now? (Y/N) ", setColor(12);
			}
			std::cin >> startOP;
			setColor(7);
			if (startOP == 'Y' || startOP == 'y')
			{
				setColor(8);
				Sleep(2000);
				std::string des = "\nIt was a long and exhausting trip, but, it doesn't matter anymore.\nThe warriors finally made it here - where that goblin village located.\nThey just need to destroy this thing, it should be real quick, goblins never been a big threat.\nBut, something feels ain't right...\n";
				std::string cond = "\nConditions:\n- Fixed squad: Player units are settled: Fighter, Defender, Maskman.\n- Enemies combination: Goblin Champion, Senior Shaman, Zombified Orc.\n- Goblin Champion and Senior Shaman have their HP and armor increased by 2000 and 200, respectively.\n- Zombified Orc no longer loses their attributes overtime.\n- Player units have -60% Resistances and -50% max health.\n- Runes are temporary disabled.\n\n";
				for (int i = 0; i < std::size(des); i++)
				{
					Sleep(25);
					if (i > 0 && (des[i - 1] == '\n' || des[i - 1] == '.')) Sleep(950);
					else if (i > 0 && des[i - 1] == ',') Sleep(550);
					std::cout << des[i];
				}
				Sleep(2000);
				setColor(6);
				std::cout << cond;
				setColor(7);
				system("pause");
				Entities player1 = createSoldier('2'), player2 = createSoldier('1'), player3 = createSoldier('3');
				Entities enemy1 = createGoblinChamp(0), enemy2 = createSeniorShaman(0), enemy3 = createZombieOrc(0);
				enemy1.challengeMode = true, enemy2.challengeMode = true, enemy3.challengeMode = true;
				enemy1.maxHealth += 2000, enemy1.health = enemy1.maxHealth;
				enemy1.armor += 200;
				enemy2.maxHealth += 2000, enemy2.health = enemy1.maxHealth;
				enemy2.armor += 200;
				enemy1.critUp -= 25, enemy2.critUp -= 25, enemy3.critUp -= 25;
				risk = 5;
				Entities* player = nullptr;
				for (int i = 1; i <= 3; i++)
				{
					i == 1 ? player = &player1 : i == 2 ? player = &player2 : player = &player3;
					player->baseAR = player->baseAR * 4 / 10, player->armor = player->baseAR;
					player->baseMR = player->baseMR * 4 / 10, player->magicRes = player->baseMR;
					player->maxHealth /= 2, player->health = player->maxHealth;
				}
				player = nullptr;
				free(player);
				Sleep(2000);
				PlaySound(TEXT("ost\\wallemdtown.wav"), NULL, SND_ASYNC | SND_LOOP);
				proceedOperation = true;
				recollectOpStart = true;
				battleStart_3v3(&player1, &player2, &player3, &enemy1, &enemy2, &enemy3);
			}
		}
		else
		{
			setColor(12);
			std::cout << "\nRecollection not yet available!\nUnlock condition: Complete atleast 3 packs in normal mode or more (" << packCompleted << "/3 completed)\n", setColor(7);
		}
		break;
	}
	case '2':
	{
		std::string intro = "\nPage number 2\n\nDate: 21/9/XX40\nWeather: Rainy\n\n<------------------------------------------------------------->\n";
		Sleep(1900);
		for (int i = 0; i < std::size(intro); i++)
		{
			int waitTime = 100;
			if (i < 14) { setColor(13); }
			else if (i < 48) { setColor(11); waitTime = waitTime * 3 / 4; }
			else { setColor(12); waitTime /= 5; }
			if (skippin) waitTime = 0;
			Sleep(waitTime);
			std::cout << intro[i];
		}
		std::string diary;
		diary += "\nSo I decided to go out for a walk.\nAfter some heavy rain, the air was so fresh that I couldn't help myself but to hang out.\nHaving wandered for a while, I found myself at the rear of the forest.\nFrom there, I heard a sound.\nIt sounded weird at first, but then ";
		diary += "it slowly became pleasing and somewhat familiar";
		diary += ".\nIn just a moment, I felt dizzy and unconsciously headed onto the place where the sound came from.\n";
		diary += "I couldn't resist myself. It sounds too peaceful. I want to hear it somemore. I want it. I...\n";
		diary += "\n\nWhen I finally regained my cognition. The very first thing I saw was a super high cliff, and I was standing on the rear of it.\nThe forest could not longer be seen, and I don't think there was any forest there in the first place\nJust one step forward and I could briefly enjoy the feeling of being a bird, before turn into grinded meat.\nShould I wake up a bit later...\nI will never leave my house ever again!\n";
		for (int i = 0; i < std::size(diary); i++)
		{
			if (!skippin)
			{
				if (i != 0 && (diary[i - 1] == '.' || diary[i - 1] == '\n' || diary[i - 1] == '-')) Sleep(1000);
				else if (i != 0 && diary[i - 1] == ',') Sleep(500);
				else Sleep(25);
			}
			if ((i > 262 && i < 262 + 48) || (i > 262 + 48 + 101 - 4 && i < 262 + 48 + 101 + 95 - 2))
			{
				setColor(14);
			}
			else
			{
				setColor(8);
			}
			std::cout << diary[i];
		}

		std::ifstream diaryStuff("saves\\data.dat");
		short currentLine = 0;
		std::string getData;
		while (diaryStuff >> getData)
		{
			currentLine++;
			if (currentLine == 5 && (getData == "CM" || getData == "RS")) unlockedDiary = true;
		}

		if (unlockedDiary)
		{
			while (diaryDat >> importDiary)
			{
				if (importDiary == "RC_2_CLR") {
					reCleared = true;
					break;
				}
			}
			diaryDat.close();

			if (reCleared)
			{
				setColor(10);
				std::cout << "\nRecollection for this diary is already cleared!\nRedo it? (Y/N) ", setColor(14);
			}
			else
			{
				setColor(6);
				std::cout << "\nStart recollection now? (Y/N) ", setColor(12);
			}
			std::cin >> startOP;
			setColor(7);
			if (startOP == 'Y' || startOP == 'y')
			{
				std::string des = "\nTwilight has overpassed, darkness began to asset its domination unto the boundless firmanent.\nDespite all of that, someone still hasn't found their way home.\nNo one ever considers it as a big deal. For them, things like that is just a commonsense in this crazy town, whatsoever.";
				std::string cond = "\n\nConditions:\n- Fixed squad: Player units are settled: Caster, Duong Le, Luu Bao.\n- Enemies combination: The Singer, Reaper, Chimera.\n- Reaper will always perform AoE attack.\n- Chimera instead starts the battle in 'Predator' mode.\n- Luu Bao has -1 structure point.\n- Runes are temporary disabled.\n\n";
				setColor(8);
				Sleep(2000);
				for (int i = 0; i < std::size(des); i++)
				{
					Sleep(25);
					if (i > 0 && (des[i - 1] == '\n' || des[i - 1] == '.')) Sleep(950);
					else if (i > 0 && des[i - 1] == ',') Sleep(550);
					std::cout << des[i];
				}
				Sleep(2000);
				setColor(6);
				std::cout << cond;
				setColor(7);
				system("pause");
				Entities player1 = createSoldier('4'), player2 = createSoldier('8'), player3 = createSoldier('a');
				Entities enemy1 = createSinger(0), enemy2 = createShinigami(0), enemy3 = createChimera(0);
				player3.fructure--;
				enemy2.challengeMode = true;
				enemy3.predatorMode = true, enemy3.divine = false;
				enemy3.armor += 400, enemy3.magicRes -= 400;
				enemy3.abilityPower = 0, enemy3.attackDmg = 535;
				Sleep(2000);
				PlaySound(TEXT("ost\\wallemdtown.wav"), NULL, SND_LOOP | SND_ASYNC);
				proceedOperation = true;
				recollectOpStart = true;
				battleStart_3v3(&player1, &player2, &player3, &enemy1, &enemy2, &enemy3);
			}
		}
		else
		{
			setColor(12);
			std::cout << "\nRecollection not yet available!\nUnlock condition: Complete pack number 5 in challenge mode or further (0/1 completed)\n";
			setColor(7);
		}
		break;
	}
	case '3':
	{
		std::string intro = "\nPage number 3\n\nDate: 17/3/XX41\nWeather: Unintelligible\n\n<------------------------------------------------------------->\n";
		Sleep(1900);
		for (int i = 0; i < std::size(intro); i++)
		{
			int waitTime = 100;
			if (i < 14) { setColor(13); }
			else if (i <= 54) { setColor(11); waitTime = waitTime * 3 / 4; }
			else { setColor(12); waitTime /= 5; }
			if (skippin) waitTime = 0;
			Sleep(waitTime);
			std::cout << intro[i];
		}
		std::string diary;
		diary += "\nI'm so sick of this, how could it be real? I don't wanna see this anymore!\n.\n.\n.\n";
		diary += "Date: 18/3/XX41\nWeather: Somewhat sunny\n\n";
		diary += "<------------------------------------------------------------->\n";
		diary += "\nI should write something about what happened.\nYesterday, a few villagers were found dead inside their own house.\nI could never forget what I saw. It was so traumatic: their corpses didn't even stay in a shape of a normal human should be. In fact, it wasn't look like any living creature in this world.\nAfter seeing that, I vomitted like immediately.\nNo one was courage enough to get close to these bodies, they just stood there, barely move for just an inch.\nHalf a day later, doctors finally arrived.\nAfter hours examining the bodies, they concluded that these villagers were ";
		diary += "poisoned to death";
		diary += ".\nYet the name of that poison, nor its mithridate, was never been found.\nAnd so on, their deaths were left unexplained.\nAfraid of thing like this may happen again, heroes were assigned to find & eliminate the cause of this tragedy.\nAnd this time, ";
		diary += "the finest consultant also joins this mission.\n";
		for (int i = 0; i < std::size(diary); i++)
		{
			if (!skippin)
			{
				if (i != 0 && (diary[i - 1] == '.' || diary[i - 1] == '\n' || diary[i - 1] == ':' || diary[i - 1] == '?' || diary[i - 1] == '!')) Sleep(1000);
				else if (i != 0 && diary[i - 1] == ',') Sleep(500);
				else Sleep(25);
			}

			if (i >= 91 - 9 && i < 92 + 42 - 11)
			{
				setColor(11);
			}
			else if (i >= 83 + 42 - 2 && i < 83 + 42 + 65 - 2)
			{
				setColor(12);
			}
			else if ((i >= 83 + 42 + 65 + 579 - 4 && i < 83 + 42 + 65 + 579 + 19 - 4) || (i >= 83 + 42 + 65 + 579 + 19 - 4 + 249 - 5))
			{
				setColor(14);
			}
			else
			{
				setColor(8);
			}
			std::cout << diary[i];
		}

		setColor(6);
		std::ifstream diaryStuff("saves\\data.dat");
		std::string dataExport;
		short packCompleted = 0, tribCompleted = 0;
		while (diaryStuff >> dataExport)
		{
			if (dataExport == "RS") { packCompleted++; tribCompleted++; }
			else if (dataExport == "NR" || dataExport == "CM") packCompleted++;
			if (packCompleted >= 5 && tribCompleted >= 1)
			{
				unlockedDiary = true;
				break;
			}
		}
		diaryStuff.close();
		if (unlockedDiary)
		{
			while (diaryDat >> importDiary)
			{
				if (importDiary == "RC_3_CLR") {
					reCleared = true;
					break;
				}
			}
			diaryDat.close();

			if (reCleared)
			{
				setColor(10);
				std::cout << "\nRecollection for this diary is already cleared!\nRedo it? (Y/N) ", setColor(14);
			}
			else
			{
				std::cout << "\nStart recollection now? (Y/N) ", setColor(12);
			}
			std::cin >> startOP;
			setColor(7);
			if (startOP == 'Y' || startOP == 'y')
			{
				setColor(8);
				Sleep(2000);
				std::string des = "\nI need backup. I need backup. I NEED BACKUP!";
				std::string cond = "\n\nConditions:\n- Fixed squad: Player units are settled: Supporter, Alter Vinh, Phong Vinh.\n- Enemies combination: Henry Fat, Vengeful Spirit, \"Free\".\n- Vengeful Spirit's mark requires atleast 7 mana.\n- Henry Fat's poison deals 50% more damage.\n- Player units can no longer skip their turn, and loses 100 magic resist.\n- Runes are temporary disabled.\n\n";
				for (int i = 0; i < std::size(des); i++)
				{
					Sleep(100);
					if (i > 0 && (des[i - 1] == '\n' || des[i - 1] == '.' || des[i - 1] == '!')) Sleep(900);
					else if (i > 0 && des[i - 1] == ',') Sleep(450);
					std::cout << des[i];
				}
				Sleep(2000);
				setColor(6);
				std::cout << cond;
				setColor(7);
				system("pause");
				Entities player1 = createSoldier('b'), player2 = createSoldier('c'), player3 = createSoldier('9');
				Entities enemy1 = createAplha(0), enemy2 = createSpirit(0), enemy3 = createFree(0);
				enemy1.challengeMode = true, enemy2.challengeMode = true, enemy3.challengeMode = true;
				player1.magicRes -= 100, player2.magicRes -= 100, player3.magicRes -= 100;
				//player1.mana += 20, player2.mana += 20, player3.mana += 20;
				Sleep(2000);
				if (std::filesystem::exists("ost\\rebel.wav")) PlaySound(TEXT("ost\\rebel.wav"), NULL, SND_ASYNC | SND_LOOP);
				else PlaySound(TEXT("ost\\wallemdtown.wav"), NULL, SND_ASYNC | SND_LOOP);
				proceedOperation = true, reduceManaRequirement = true;
				recollectOpStart = true;
				battleStart_3v3(&player1, &player2, &player3, &enemy1, &enemy2, &enemy3);
			}
		}
		else
		{
			setColor(12);
			std::cout << "\nRecollection not yet available!\nUnlock condition: Complete 5 packs, atleast 1 or more is completed in Tribulation Mode (" << packCompleted << "/5 completed) (" << tribCompleted << "/1 tribulation completed)\n", setColor(7);
		}
		break;
	}
	case '4':
	{
		std::string intro = "\nPage number 4\n\nDate: 21/6/XX43\nWeather: Perfect\n\n<------------------------------------------------------------->\n";
		Sleep(1900);
		for (int i = 0; i < std::size(intro); i++)
		{
			int waitTime = 100;
			if (i < 14) { setColor(13); }
			else if (i <= 54) { setColor(11); waitTime = waitTime * 3 / 4; }
			else { setColor(12); waitTime /= 5; }
			if (skippin) waitTime = 0;
			Sleep(waitTime);
			std::cout << intro[i];
		}
		std::string diary;
		diary += "\nJust who is this guy?\nHe suddenly showed up out from nowhere, marching into own town, by all himself alone.\nBut, it's clear as day that he's definitely up to no good.\n";
		diary += "I can tell it, no, everyone can tell it just by sensing the eerie atmostsphere omitting from \"that thing\"";
		for (int i = 0; i < std::size(diary); i++)
		{
			if (!skippin)
			{
				if (i != 0 && (diary[i - 1] == '.' || diary[i - 1] == '\n' || diary[i - 1] == ':' || diary[i - 1] == '?' || diary[i - 1] == '!')) Sleep(1000);
				else if (i != 0 && diary[i - 1] == ',') Sleep(500);
				else Sleep(25);
			}

			if (i >= 168 && i <= 168 + 106)
			{
				setColor(14);
			}
			else
			{
				setColor(8);
			}
			std::cout << diary[i];
		}

		setColor(6);
		std::ifstream diaryStuff("saves\\data.dat");
		std::string dataExport;
		short packCompleted = 0, currentLine = 0;
		while (diaryStuff >> dataExport)
		{
			currentLine++;
			if ((dataExport == "NR" || dataExport == "CM" || dataExport == "RS") && currentLine == 7) packCompleted++;
			if (packCompleted >= 1)
			{
				unlockedDiary = true;
				break;
			}
		}
		diaryStuff.close();
		if (unlockedDiary)
		{
			while (diaryDat >> importDiary)
			{
				if (importDiary == "RC_4_CLR") {
					reCleared = true;
					break;
				}
			}
			diaryDat.close();

			if (reCleared)
			{
				setColor(10);
				std::cout << "\nRecollection for this diary is already cleared!\nRedo it? (Y/N) ", setColor(14);
			}
			else
			{
				std::cout << "\nStart recollection now? (Y/N) ", setColor(12);
			}
			std::cin >> startOP;
			setColor(7);
		}
	}
	}

	if (!unlockedDiary)
	{
		setColor(10);
		system("pause");
		setColor(7);
	}

	if (proceedOperation) PlaySound(TEXT("ost\\lobby.wav"), NULL, SND_LOOP | SND_ASYNC);
	goto diaryList;
}

void storyModeStart()
{
	std::fstream getStoryData("saves\\story.dat");
	std::string storyProgess;
	getStoryData >> storyProgess;
	if (storyProgess == " " || !std::filesystem::exists("saves\\story.dat"))
	{
		std::cout << "\nWhoosp! Look like you haven't stored any progess on this mode yet. Perhaps you're new here, I'll give you a brief introduction about this mode.\n";
		system("pause");
		std::cout << "\nSee that message above? It's kinda annoying and won't fit for displaying character's dialogues, right?\n";
		Sleep(3000);
		printf("So, from now on, the aforementioned notification will be disabled, and you need to figure out when to continue by yourself..\n");
		_getch();
		printf("Well done, now you've learnt how story mode works.");
		_getch();
		printf("\nWhat happens next is up to you, good luck!");
		_getch();
	}
}

void gameStart()
{
	short modoChoice;
	setColor(12);
	std::cout << "\nSelect combat mode:\n1. Solo\n2. 3v3-Custom: Feel free to choose your units and enemies\n3. 3v3-Packed mode: Enemies units are locked and can not be changed, but you can experience enemies that can not be challenged normally\n4. 3v3 - Tower mode: Starts off normally, but wait, why do these enemies keep spawning...\n???. Stay tune, something wicked this way comes...\nYour choice: ";
	setColor(11);
	std::cin >> modoChoice;

	while (std::cin.fail() || modoChoice > 4 || modoChoice < 1)
	{
		std::cin.clear();
		std::cin.ignore();
		setColor(12);
		std::cout << "\nInvalid input! Recommend trying again";
		std::cout << "\nSelect combat mode:\n1. Solo\n2. 3v3-Custom: Feel free to choose your units and enemies\n3. 3v3-Packed mode: Enemies units are locked and can not be changed, but you can experience enemies that can not be challenged normally\n4. 3v3 - Tower mode: Starts off normally, but wait, why do these enemies keep spawning...\n???. Stay tune, something wicked this way comes...\nYour choice: ";
		setColor(LI_CIRNO);
		std::cin >> modoChoice;
	}


	if (modoChoice != 5)
	{
		if (modoChoice == 4)
		{
			modoChoice = 2;
			towerMode = true;
		}

		if (modoChoice > 5 || modoChoice <= 0) return;

		setColor(7);
		Entities player = createSoldier(), player2 = createBlankTarget(), player3 = createBlankTarget();
		Entities enemy = createBlankTarget(), enemy2 = createBlankTarget(), enemy3 = createBlankTarget();

		if (modoChoice != 1)
		{
			player2 = createSoldier(); player3 = createSoldier();
			while (player.range == player2.range || player2.range == player3.range || player.range == player3.range)
			{
				std::cout << "\nDO NOT choose existed role, nigga!\nNow choose again from the 2nd unit.\n";
				system("pause");
				player2 = createBlankTarget(), player3 = createBlankTarget();
				player2 = createSoldier(), player3 = createSoldier();
			}
		}

		if (modoChoice == 3)
		{
			std::vector<std::string> packList = { "The goblins incident", "Waiting game", "Shattering Force", "Phantom of the Night", "Deaf to all but the Song", "March of the Undeads", "[Boss fight] \"As the Empier's Shadow\"", "[Boss fight] \"Free Will\"" };
			std::fstream data("saves\\data.dat");
			if (data.peek() == ' ' || data.peek() == EOF)
			{
				std::ofstream createFile("saves\\data.dat");
				std::string addData = "PX";
				for (int j = 1; j <= std::size(packList); j++)
				{
					addData[1] = j + '0';
					createFile << addData;
					if (j < 7) createFile << '\n';
				}
				createFile.close();
			}
			data.close();
			printf("\nSelect pack:");
			for (int i = 0; i < std::size(packList); i++)
			{
				bool notCleared = true;
				std::ifstream data("saves\\data.dat", std::ifstream::out | std::ios::app);
				std::string getData;
				std::cout << "\n" << i + 1 << ". " << packList[i];
				short currentLine = 0;
				while (data >> getData)
				{
					//data >> getData;
					//std::cout << getData;
					if (currentLine == i && (getData == "NR" || getData == "CM" || getData == "RS"))
					{
						setColor(10);
						std::cout << " (Completed)";
						if (getData == "CM") std::cout << " (+ Challenge Mode)";
						else if (getData == "RS") std::cout << " (+ Challenge Mode & Risks)";
						notCleared = false;
						break;
					}
					currentLine++;
				}
				data.close();
				if (notCleared)
				{
					setColor(12);
					std::cout << " (Uncompleted)";
				}
				setColor(7);
			}
			std::cout << "\nYour choice: ";
			std::cin >> pack;
			while (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				setColor(12);
				std::cout << "Invalid input, now try again!", setColor(7);
				printf("\nSelect pack:\n1. The goblin incident\n2. Waiting game\n3. Dying Light\n4. Phantom in the Night\n5. Lullabye\n6. Fallen Army\n7. Bossfight: Blade\nYour choice: ");
				std::cin >> pack;
			}
			switch (pack)
			{
			case 1:
				enemy = createGoblinChamp(0), enemy2 = createSeniorShaman(0), enemy3 = createZombieOrc(0);
				break;
			case 2:
				enemy = createSneaker(0), enemy2 = createExplosiveSlug(0), enemy3 = createPosDef(0);
				break;
			case 3:
				enemy = createZombieOrc(0), enemy2 = createPosKnight(0), enemy3 = createPosKnight_L(0);
				break;
			case 4:
			{
				enemy = createPhantom(0), enemy2 = createAplha(0), enemy3 = createSpirit(0);
				Entities* currentEnemy = &enemy;
				srand(time(NULL));
				int talent = rand() % (9 - 1 + 1) + 1;
				currentEnemy->possessTalent = talent;
				setColor(12);
				std::cout << "\nTalent possessed: ";
				setColor(5);
				switch (talent)
				{
				case 1:
					std::cout << "After every turn, increases self ATK by 20 and subtracts opponent's armor by 5";
					break;
				case 2:
					std::cout << "After being injured, reflects 30 + 40% armor + 40% magic resist magic damage to the attacker";
					break;
				case 3:
					std::cout << "Increases crit chance by 50%, this unit also gains 10% life steal";
					currentEnemy->omniVamp = 10;
					break;
				case 4:
					std::cout << "Gains 300 ability power";
					currentEnemy->abilityPower += 300;
					break;
				case 5:
					std::cout << "Once in the battle, when HP drops to 0, restores 1000 + 100% damage taken HP";
					currentEnemy->emergencyOn = true;
					break;
				case 6:
					std::cout << "Attack receives one of these following buff: Deals 150% true damage, restores 7% HP or decreases target's mana by 1";
					break;
				case 7:
					std::cout << "Damage taken is reduced by 15%";
					break;
				case 9:
					std::cout << "Gains 2 shields at the start of battle and 1 shield every 5 turns. Each shield can block 1 instance of damage. When a shield breaks, restores 10% HP";
					currentEnemy->shield = 2;
					break;
				case 8:
					std::cout << "After every turn, generates 1 Moon Blade (stores up to 2), each Moon Blade increases crit chance by 7%. Whenever this unit attacks, attacks an additional with each Moon Blade owns.";
					break;
				}
				setColor(7);
				printf("\n");
				system("pause");
				currentEnemy = nullptr;
				free(currentEnemy);
				break;
			}
			case 5:
				enemy = createSinger(0), enemy2 = createFree(0), enemy3 = createShinigami(0);
				break;
			case 6:
				enemy2 = createPosKnight(0), enemy = createPosDef(0), enemy3 = createPosKnight_L(0);
				break;
			case 7:
				enemy = createBlade(1), enemy2 = createBlankTarget(), enemy3 = createBlankTarget();
				break;
			case 8:
				enemy = createEssence(1), enemy2 = createBlankTarget(), enemy3 = createBlankTarget();
				break;
			}
			setColor(12);
			if (pack != 7 && pack != 8) { std::cout << "\nEnemy combination: " << enemy.role << " / " << enemy2.role << " / " << enemy3.role << '\n'; }
			else std::cout << "\nElite enemy detected, proceed with caution!\n";
			setColor(7);
		}
		else
		{
			modoChoice == 2 ? modoChoice = 3 : modoChoice = 1;
			for (int i = 1; i <= modoChoice; i++)
			{
				Entities* currentEnemy;
				i == 1 ? currentEnemy = &enemy : i == 2 ? currentEnemy = &enemy2 : currentEnemy = &enemy3;
				char choice;
				printf("\nChoose enemy type (Choosing duplicated enemy in 3v3 is not banned, but can causes serious errors and I'm not fixing that):\nEnemies with the '*' symbol next to their name has their difficulty improves significantly in challenge mode, proceed with caution\n\n1. Dummy\n"), setColor(2);
				std::cout << "\nPhase A : Standard Mobs", setColor(7);
				std::cout << "\n2. Goblin Champion fight : easy\n3. Senior shaman : easy\n4. Zombified Orc* : quite tricky, but not that hard with some good counter picks\n5. Advanced Drawft : fun\n", setColor(14);
				std::cout << "\nPhase B : Enhanced mobs, comes up with niche special ability\n", setColor(7);
				std::cout << "6. Explosive Slug : better tank wins\n7. Phantom : pick and pray for a good RNG\n8. Vengeful Spirit : fun\n", setColor(6);
				std::cout << "\nPhase C : Advanced mobs, have respectable durability and tons of different behaviors\n", setColor(7);
				std::cout << "9. Chimera* : for people who loves suffering\nA. Henry Fat* : extra fun\nB. The Singer* : it sings\nC. Reaper* : it reaps\nD. \"Free\": Some weird flex\n", setColor(12);
				std::cout << "\nPhase D : Possessed mobs, some of their stats possesses incredibly high attribute - either offensive or defensive one, thus their performance on the battlefield is unignorable", setColor(7);
				std::cout << "\nE. Enraged Possessed Soldier* : Not recommended for non-tanki squad\nF. Enraged Possessed Bonethrower* : Not recommended for non-tanki squad\nG. Possessed Heavy Defender\n\nYour choice: ";
				std::cin >> choice;
				switch (choice)
				{
				case '1':
					*currentEnemy = createDummy();
					system("pause");
					break;
				case '2':
					*currentEnemy = createGoblinChamp(1);
					system("pause");
					break;
				case '3':
					*currentEnemy = createSeniorShaman(1);
					system("pause");
					break;
				case '4':
					*currentEnemy = createZombieOrc(1);
					system("pause");
					break;
				case '5':
					*currentEnemy = createSneaker(1);
					system("pause");
					break;
				case '6':
					*currentEnemy = createExplosiveSlug(1);
					system("pause");
					break;
				case '7':
				{
					*currentEnemy = createPhantom(1);
					system("pause");
					srand(time(NULL));
					int talent = rand() % (9 - 1 + 1) + 1;
					currentEnemy->possessTalent = talent;
					setColor(12);
					std::cout << "\nTalent possessed: ";
					setColor(5);
					switch (talent)
					{
					case 1:
						std::cout << "After every turn, increases self ATK by 20 and subtracts opponent's armor by 5";
						break;
					case 2:
						std::cout << "After being injured, reflects (20 + 30% armor) magic damage to the attacker";
						break;
					case 3:
						std::cout << "Increases crit chance by 50%, this unit also gains 10% life steal";
						currentEnemy->omniVamp = 10;
						break;
					case 4:
						std::cout << "Gains 300 ability power";
						currentEnemy->abilityPower += 300;
						break;
					case 5:
						std::cout << "Once in the battle, when HP drops to 0, restores 1000 + 100% damage taken HP";
						currentEnemy->emergencyOn = true;
						break;
					case 6:
						std::cout << "Attack receives one of these following buff: Deals 150% true damage, restores 7% HP or decreases target's mana by 1";
						break;
					case 7:
						std::cout << "Damage taken is reduced by 15%";
						break;
					case 9:
						std::cout << "Gains 2 shields at the start of battle and 1 shield every 5 turns. Each shield can block 1 instance of damage. When a shield breaks, restores 10% HP";
						currentEnemy->shield = 2;
						break;
					case 8:
						std::cout << "After every turn, generates 1 Moon Blade (stores up to 2), each Moon Blade increases crit chance by 7%. Whenever this unit attacks, attacks an additional with each Moon Blade owns.";
						break;
					}
					setColor(7);
					printf("\n");
					system("pause");
					break;
				}
				case '8':
					*currentEnemy = createSpirit(1);
					system("pause");
					break;
				case '9':
					*currentEnemy = createChimera(1);
					system("pause");
					break;
				case 'a': case 'A':
					*currentEnemy = createAplha(1);
					system("pause");
					break;
				case 'b': case 'B':
					*currentEnemy = createSinger(1);
					system("pause");
					break;
				case 'c': case 'C':
					*currentEnemy = createShinigami(1);
					system("pause");
					break;
				case 'd': case 'D':
					*currentEnemy = createFree(1);
					system("pause");
					break;
				case 'e': case 'E':
					*currentEnemy = createPosKnight(1);
					system("pause");
					break;
				case 'f': case 'F':
					*currentEnemy = createPosKnight_L(1);
					system("pause");
					break;
				case 'g': case 'G':
					*currentEnemy = createPosDef(1);
					system("pause");
					break;
				default:
					setColor(12);
					std::cout << "Invalid data detected!\nNo enemy was chosen\n", setColor(7);
					system("pause");
					i--;
					break;
				}
				currentEnemy->baseAR = currentEnemy->armor;
				currentEnemy->baseMR = currentEnemy->magicRes;
				currentEnemy = nullptr;
				free(currentEnemy);
			}
		}
		system("pause");

		int challMod = avoidRetardInput("\nBattle mode:\n1. Stay simple\n2. Challenge Mode\n3. Tribulation Mode\nYour choice: ");
		if (challMod == 1) std::cout << "\nNormal mode selected!\n";
		else
		{
			enemy.challengeMode = true;
			enemy2.challengeMode = true;
			enemy3.challengeMode = true;
			std::cout << "\nChallenge Mode selected!\n\n";
			setColor(12);
			for (int i = 0; i < modoChoice; i++)
			{
				Entities* currentEnemy = nullptr;
				i == 0 ? currentEnemy = &enemy : i == 1 ? currentEnemy = &enemy2 : currentEnemy = &enemy3;
				if (currentEnemy->role != "Dummy" && currentEnemy->role != "blank") std::cout << currentEnemy->role << " - ";
				switch (currentEnemy->range)
				{
				case 55:
					std::cout << "Undead the Undying: Zombified Orc no longer loses HP and resistances overtime!\n";
					break;
				case 56:
					std::cout << "Swift Action: Dwarft has significantly increased dodge & graze chance and bonus damage\n";
					break;
				case 57:
					std::cout << "Shell Defense: Slug's bonus armor, magic resist and attack damage from passive increased even greater.\n";
					currentEnemy->armor += 500;
					currentEnemy->magicRes += 500;
					break;
				case 58:
				{
					std::cout << "Specter: Phantom possesses up to 2 separate talents!\n";
					int talent = rand() % (9 - 1 + 1) + 1;
					currentEnemy->possessTalent2 = talent;
					if (currentEnemy->possessTalent == currentEnemy->possessTalent2 && currentEnemy->possessTalent < 9)
					{
						currentEnemy->possessTalent2++;
						talent++;
					}
					else if (currentEnemy->possessTalent == currentEnemy->possessTalent2)
					{
						currentEnemy->possessTalent2--;
						talent--;
					}
					setColor(12);
					std::cout << "Talent 2 possessed: ";
					setColor(5);
					switch (talent)
					{
					case 1:
						std::cout << "After every turn, increases self ATK by 20 and subtracts opponent's armor by 5";
						break;
					case 2:
						std::cout << "After being injured, reflects (20 + 30% armor) magic damage to the attacker";
						break;
					case 3:
						std::cout << "Increases crit chance by 50%, this unit also gains 10% life steal";
						currentEnemy->omniVamp = 10;
						break;
					case 4:
						std::cout << "Gains 300 ability power";
						currentEnemy->abilityPower += 300;
						break;
					case 5:
						std::cout << "Once in the battle, when HP drops to 0, restores 1000 + 100% damage taken HP";
						enemy.emergencyOn = true;
						break;
					case 6:
						std::cout << "Attack receives one of these following buff: Deals 150% true damage, restores 7% HP or decreases target's mana by 1";
						break;
					case 7:
						std::cout << "Damage taken is reduced by 15%";
						break;
					case 9:
						std::cout << "Gains 2 shields at the start of battle and 1 shield every 5 turns. Each shield can block 1 instance of damage. When a shield breaks, restores 10% HP";
						currentEnemy->shield = 2;
						break;
					case 8:
						std::cout << "After every turn, generates 1 Moon Blade (stores up to 2), each Moon Blade increases crit chance by 7%. Whenever this unit attacks, attacks an additional with each Moon Blade owns.";
						break;
					}
					setColor(12);
					printf("\n");
					break;
				}
				case 59:
					std::cout << "Hateful Spirit: Mana consumption increases to 8, healing increases to 1333 HP\n";
					break;
				case 60:
					std::cout << "Brodifacoum: Poison deals 150% damage and deals at least 300 damage, regardless of target's magic resist\n";
					break;
				case 61:
					std::cout << "Hymn of Battle: All enemy units ATK +50%\n";
					break;
				case 62:
					std::cout << "Bounty Harvest: Reaper has -25% ATK, but will always perform AoE attack\n";
					currentEnemy->attackDmg = currentEnemy->attackDmg * 3 / 4;
					break;
				case 63:
					std::cout << "Rule Breaker: Player units can no longer skip their turns\n";
					break;
				case 64: case 65:
					std::cout << "Enjoyment, even in Death: " << currentEnemy->role << " gains 3 layers of 'Shield' and won't naturally lose HP in the first 3 turns of battle\n";
					currentEnemy->shield = 3;
					break;
				case 66:
					std::cout << "Unyielding Shield: Other enemies gains bonus armor equals 20% of this unit's armor\n";
					enemy.armor += currentEnemy->armor / 5;
					enemy2.armor += currentEnemy->armor / 5;
					enemy3.armor += currentEnemy->armor / 5;
					break;
				case 100:
					std::cout << "Remember the Beast: Chimera has greatly increased HP and attack instead deals true damage\n";
					currentEnemy->health += 5000;
					currentEnemy->maxHealth += 5000;
					break;
				case 101:
					std::cout << "Corrupting Domination: Upon entering \"Pursuer\" state, summons \"Corrupted Bladeweaver\" and \"Corrupted Worldcurser\" to assist in combat";
					break;
				case 150:
					std::cout << "Witness true Evolution: During \"Evolution\" form, this unit regenerate its HP. During \"Perfect\" form, this unit loses HP at a decreased rate and becomes \"Low-altitude Hovering\"";
					break;
				default:
					if (currentEnemy->role != "Dummy" && currentEnemy->role != "blank")
					{
						std::cout << "This enemy has their basic stats increases by 150, HP increased by 2000\n";
						currentEnemy->abilityPower < currentEnemy->attackDmg ? currentEnemy->baseAD += 150, currentEnemy->attackDmg += 150 : currentEnemy->baseAP += 150, currentEnemy->abilityPower += 150;
						currentEnemy->armor += 150, currentEnemy->baseAR += 150, currentEnemy->baseMR += 150, currentEnemy->magicRes += 150;
						currentEnemy->maxHealth += 2000, currentEnemy->health += 2000;
					}
					break;
				}
				printf("\n");
			}

			if (challMod >= 3)
			{
				setColor(14);
				printf("Select level of risk (between 1 - 5): ");
				scanf_s("%i", &risk);
				risk > 5 ? risk = 5 : risk < 1 ? risk = 1 : risk;
				risk = 6 - risk;
				std::cout << "Risk selected!\n", setColor(12);
				switch (risk)
				{
				case 1:
				{
					std::cout << "\nTactical Combat - Anti Armor II: All friendly units has -60% Resistances\n";
					player.baseAR = player.baseAR * 4 / 10, player.armor = player.baseAR;
					player.baseMR = player.baseMR * 4 / 10, player.magicRes = player.baseMR;
					if (modoChoice != 1)
					{
						player2.baseAR = player2.baseAR * 4 / 10, player2.armor = player2.baseAR;
						player2.baseMR = player2.baseMR * 4 / 10, player2.magicRes = player2.baseMR;
						player3.baseAR = player3.baseAR * 4 / 10, player3.armor = player3.baseAR;
						player3.baseMR = player3.baseMR * 4 / 10, player3.magicRes = player3.baseMR;
					}
				}
				case 2:
				{
					if (risk >= 2)
					{
						std::cout << "\nTactical Combat - Anti Armor I: All friendly units has -30% Resistances\n";
						player.baseAR = player.baseAR * 7 / 10, player.armor = player.baseAR;
						player.baseMR = player.baseMR * 7 / 10, player.magicRes = player.baseMR;
						if (modoChoice != 1)
						{
							player2.baseAR = player2.baseAR * 7 / 10, player2.armor = player2.baseAR;
							player2.baseMR = player2.baseMR * 7 / 10, player2.magicRes = player2.baseMR;
							player3.baseAR = player3.baseAR * 7 / 10, player3.armor = player3.baseAR;
							player3.baseMR = player3.baseMR * 7 / 10, player3.magicRes = player3.baseMR;
						}
					}
				}
				case 3:
					std::cout << "\nOriginium Zone - Activation: All friendly unit has -50% max health\n";
					player.maxHealth /= 2, player.health = player.maxHealth;
					if (modoChoice != 1)
					{
						player2.maxHealth /= 2, player2.health = player2.maxHealth;
						player3.maxHealth /= 2, player3.health = player3.maxHealth;
					}
				case 4:
				{
					std::cout << "\nObjective - High Value Targets II: All friendly unit has -60% ATK and -15% Crit chance\n";
					player.baseAD = player.baseAD * 4 / 10, player.attackDmg = player.baseAD;
					player.baseAP = player.baseAP * 4 / 10, player.abilityPower = player.baseAP;
					player.critUp -= 15;
					if (modoChoice != 1)
					{
						player2.baseAD = player2.baseAD * 4 / 10, player2.attackDmg = player2.baseAD;
						player2.baseAP = player2.baseAP * 4 / 10, player2.abilityPower = player2.baseAP;
						player2.critUp -= 15, player3.critUp -= 15;
						player3.baseAD = player3.baseAD * 4 / 10, player3.attackDmg = player3.baseAD;
						player3.baseAP = player3.baseAP * 4 / 10, player3.abilityPower = player3.baseAP;
					}
				}
				case 5:
				{
					if (risk >= 5)
					{
						std::cout << "\nObjective - High Value Targets I: All friendly unit has -25% ATK and -10% Crit chance\n";
						player.baseAD = player.baseAD * 75 / 100, player.attackDmg = player.baseAD;
						player.baseAP = player.baseAP * 75 / 100, player.abilityPower = player.baseAP;
						player.critUp -= 10;
						if (modoChoice != 1)
						{
							player2.baseAD = player2.baseAD * 75 / 100, player2.attackDmg = player2.baseAD;
							player2.baseAP = player2.baseAP * 75 / 100, player2.abilityPower = player2.baseAP;
							player2.critUp -= 10, player3.critUp -= 10;
							player3.baseAD = player3.baseAD * 75 / 100, player3.attackDmg = player3.baseAD;
							player3.baseAP = player3.baseAP * 75 / 100, player3.abilityPower = player3.baseAP;
						}
					}
				}
				}
				setColor(6);
				risk = 6 - risk;
				std::cout << "\nRisk level: " << risk << "\n\n";
			}
			setColor(7);
		}

		if (modoChoice == 1)
		{
			chooseRune(&player);
			chooseSong();
			Entities pseudo_entity = createBlankTarget();
			battleStart_3v3(&player, &pseudo_entity, &pseudo_entity, &enemy, &pseudo_entity, &pseudo_entity);
		}
		else
		{
			for (int i = 0; i < modoChoice; i++)
			{
				Entities* runeChoose = nullptr;
				i == 0 ? runeChoose = &player : i == 1 ? runeChoose = &player2 : runeChoose = &player3;
				chooseRune(runeChoose);
				printf("\n");
			}
			/*
			if ((enemy.range == 61 || enemy2.range == 61 || enemy3.range == 61) && enemy.challengeMode)
			{
				setColor(8);
				std::cout << "Just what is that...\n", setColor(7);
				PlaySound(TEXT("requiem.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			*/
			if (enemy.range == 101)
			{
				PlaySound(NULL, NULL, NULL);
				setColor(8);
				std::cout << "Emperors' Blades enters the battle, be prepared!\n", setColor(7);
				Sleep(2000);
				enemy.challengeMode&& risk > 0 ? PlaySound(TEXT("ost\\emblade_extra.wav"), NULL, SND_LOOP | SND_ASYNC) : PlaySound(TEXT("ost\\emblade.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			else if (enemy.range == 150)
			{
				PlaySound(NULL, NULL, NULL);
				setColor(8);
				std::cout << "You can hear something cracked down...\n", setColor(7);
				PlaySound(TEXT("ost\\frontline.wav"), NULL, SND_LOOP | SND_ASYNC);
				Sleep(2000);
			}
			else chooseSong();
			battleStart_3v3(&player, &player2, &player3, &enemy, &enemy2, &enemy3);
		}
	}
	else storyModeStart();
}

void programIntroduction()
{
	setColor(GRAY);
	std::cout << "\nThis is some kind of common turn-base game, except for one thing: it has absolutely zero graphic, and you have is text and some gay ass color. End of story!";
	while (true)
	{
		short questionChoose = avoidRetardInput("\n\nChoose a thing you'd like to know more about:\n1. Game mechanics\n2. Return to main menu\nPick a choice: ", 1, 2);
		setColor(WHITE);
		if (questionChoose == 1)
		{
			setColor(LI_YELLOW);
			std::cout << "\nGame mechanics: Since you're already familiar with most of these things, I'll just explain about unclear stuffs\n\n", setColor(DA_YELLOW);
			std::cout << "A. Damage output calculation\n", setColor(GRAY);
			std::cout << "In case you don't know, I've secretly changed this formula since the previous one contains many issue and makes it really hard to adjust entities' attributes surrounding it.\nThe new formula is way easier to calculate and adjust (also more handleable for future contents as well)\n";
			setColor(RED);
			std::cout << "\nDamage calculation formula:\n<Total damage> = <Raw damage> * {1000 - [(<CRT> - <Flat CRT ignorance>) * (100 - <CRT penetration>) / 100]} / 1000\n\n", setColor(LI_GREEN);
			std::cout << "Notes:", setColor(2);
			std::cout << "\n+ CRT: stands for \"Corresponding resistance type\" - is either the number of armor (if damage type is physic damage) or magic resist (if damage type is magic damage)\n+ If one's CRT surpasses 1000, hypothetically, they receive from 0 to negative damage. But that sure ain't cool at all, thus, units whose CRT - after having been subtracted by CRT penetration - still surpass    more than 950 will be automatically set to 950, which means they're forced to receive at least 5% of the raw damage. However, in the event to which their CRT are extremely high, then they'll be absolutely immune to that type of damage.\n+ To simplify the formula, you just need to know: A unit gains X% damage reduction, where X is proportional to 10% amount of their CRT. In this case, assume that the enemy has 350 armor and take 1000 physic     damage, with no AR pen or lethality is given, that enemy possesses 35% physic damage reduction, which means they only receive 650 damage in total.";
			std::cout << std::endl;
			setColor(DA_YELLOW);
			system("pause");
			std::cout << "\n\nB. Entities' special status\n", setColor(GRAY);
			std::cout << "\"Status\" is undoubtedly one of the most interesting part in this kind of 'game', yet it's not easy to remember every of them as well as their effect, so let me summary it for you\n", setColor(LI_CIRNO);
			std::cout << "\n\nBuff status (or \"Good effects\"):\n\n";
			std::vector<std::string> buffEff = { "Shield", "Sunblade", "Reflecting", "ATK-up" };
			std::vector<std::string> buffDes = { "Blocks 1 instance of damage (set the damage to 0) and restores HP to the shield's owner equivalent to 20% of their max HP", "Effect owner gains increased (7 * N)% crit chance and the right to attack extra N times, given N is the current number of \"Sunblade\"", "Converts a certain amount of the next source of damage into health" , "Increases ATK (both AD and AP) by the % of effect" };
			for (int i = 0; i < buffEff.size(); i++)
			{
				short flexibleColorCode;
				switch (i)
				{
				case 0:
					flexibleColorCode = LI_GREEN;
					break;
				case 1:
					flexibleColorCode = LI_YELLOW;
					break;
				case 2:
					flexibleColorCode = CIRNO;
					break;
				default:
					flexibleColorCode = DA_YELLOW;
					break;
				}
				setColor(flexibleColorCode);
				std::cout << buffEff[i] << ": ";
				setColor(GRAY);
				std::cout << buffDes[i] << '\n';
			}

			setColor(BO_RED);
			std::cout << "\n\nDebuff status (or \"Bad effects\"):\n\n";
			std::vector<std::string> debuffEff = { "Fragile", "Marked", "Poisoning", "Bleeding", "Taunted", "Silent", "Bind" };
			std::vector<std::string> debuffDes = { "Amplifies the damage taken by affected unit by the exact % of effect", "Provided by \"Vengeful Spirit\", affected unit loses a certain amount of mana after a period of time, or being executed if they have less than required amount. In the event where the effect causer is      knocked down before the mark activates, it gets removed", "Provided by \"Henry Fat\", affected unit has to receive an amount of magic damage after everyturn, and reduce all incoming healing effect from them by 60%. In the event where the effect causer is       knocked down while the poison still persists, it will continue to cause damage until completely run out", "The next source of damage on affected unit removes this status and deals additional magic damage proportional to 20% of their max HP, this damage ignores up to 100 magic reist", "Affected unit is forced to use a normal attacker against the effect causer, regardless of their current state or trait", "Affected unit has their special abilities disabled during the effect duration", "Can not dodge nor graze incoming attacks" };
			for (int i = 0; i < debuffEff.size(); i++)
			{
				short flexibleColorCode;
				switch (i)
				{
				case 0:
					flexibleColorCode = LI_CIRNO;
					break;
				case 1:
					flexibleColorCode = PURPLE;
					break;
				case 2:
					flexibleColorCode = 13;
					break;
				case 3:
					flexibleColorCode = RED;
					break;
				case 4:
					flexibleColorCode = DA_YELLOW;
					break;
				case 5:
					flexibleColorCode = LI_WHITE;
					break;
				default:
					flexibleColorCode = WHITE;
					break;
				}
				setColor(flexibleColorCode);
				std::cout << debuffEff[i] << ": ";
				setColor(GRAY);
				std::cout << debuffDes[i] << '\n';
			}

			setColor(3);
			std::cout << "\n\nSpecial status:\n\n";
			std::vector<std::string> specEff = { "Stand-by / Combat-ready", "Rotting", "Low-altitude Hovering" };
			std::vector<std::string> specDes = { "Unit with status doesn't attack until being injured", "Unit with status gradually loses HP overtime", "Unit with status can not be targeted directly (AoE and in-direct source of damage works ultimately)" };
			for (int i = 0; i < specEff.size(); i++)
			{
				short flexibleColorCode;
				switch (i)
				{
				case 0:
					flexibleColorCode = LI_CIRNO;
					break;
				case 1:
					flexibleColorCode = BO_RED;
					break;
				default:
					flexibleColorCode = 13;
					break;
				}
				setColor(flexibleColorCode);
				std::cout << specEff[i] << ": ";
				setColor(GRAY);
				std::cout << specDes[i] << '\n';
			}

			setColor(GRAY);
		}
		else break;
	}
}

void mainMenu()
{
	PlaySound(TEXT("ost\\lobby.wav"), NULL, SND_ASYNC | SND_LOOP);
	setColor(6);
	std::cout << "Welcome to \"Benh Vien Cut Dai Nhiet Hach\"!\n1. Start now\n2. Diary\n3. Brief introduction & turtorial\nOthers: Exit\nChoose action: ";
	char menuSelect;
	setColor(10);
	std::cin >> menuSelect;
	setColor(7);
	switch (menuSelect)
	{
	case '1':
		gameStart();
		break;
	case '2':
		diaryProgress();
		break;
	case '3':
		programIntroduction();
		break;
	default:
		setColor(6);
		printf("\nWhat a pity, cya!\n");
		setColor(10);
		system("pause");
		runningProgram = false;
	}
}

