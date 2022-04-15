#pragma once
bool inTurn = false;

void playerChoice(Entities* player, Entities* ally1, Entities* ally2, Entities* enemy1, Entities* enemy2, Entities* enemy3)
{
	srand(time(NULL));
	short storeDmg;
	if (!inTurn)
	{
		storeDmg = player->attackDmg;
		player->attackDmg += player->attackDmg / 20 * player->sunBlade;
		inTurn = true;
	}

currentChoice:

	if (enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0) return;
	if ((enemy1->floating && enemy2->health <= 0 && enemy3->health <= 0) || (enemy2->floating && enemy1->health <= 0 && enemy3->health <= 0) || (enemy3->floating && enemy2->health <= 0 && enemy1->health <= 0)) return;

	int mana1_2 = 3, mana1_1;



	(player->range == 7 || player->range == 6 || player->range == 8 || player->range == 12) ? mana1_1 = 2 : mana1_1 = 3;

	switch (player->range)
	{
	case 1: case 7:
		mana1_2 = 1;
		break;
	case 4: case 8: case 2:
		mana1_2 = 3;
		break;
	case 6:
		mana1_2 = rand() % (12 - 4 + 1) + 4;
		break;
	case 5: case 9: case 10:
		mana1_2 = 0;
		break;
	case 3: case 13:
		mana1_2 = 2;
		break;
	case 11:
		mana1_2 = 5;
		break;
	}

	char choice1;
	setColor(14);
	std::cout << "\nChoose " << player->role << " action:", setColor(7);
	player->range != 4 ? std::cout << "\n1. Normal attack (+1 mana)" : std::cout << "\n1. Normal attack (+2 mana)";

	if (player->range == 8)
	{
		setColor(14);
		std::cout << "  Current Sunblade: " << player->sunBlade, setColor(7);
	}

	if (player->range == 9 || player->shield > 0)
	{
		setColor(2);
		std::cout << "  Current Shield: " << player->shield, setColor(7);
	}
	std::cout << "\n2. Use first spell (-" << mana1_1 << " mana)\n3. Use last spell (-" << mana1_2 << " mana)\n4. Check this unit stats\n5. Check specific enemy stats\n";
	if (player->range != 10) std::cout << "Other: Skip this turn (+3 mana)\n";
	else
	{
		setColor(14);
		std::cout << "6. Deploy machine (-1 structure point)    Current Structure point: " << player->fructure;
		setColor(7);
		std::cout << "\nOther. Skip this turn (+3 mana)\n";
	}
	setColor(11);
	std::cout << "\nCurrent mana: " << player->mana, setColor(7);
	std::cout << "\nYour choice: ";
	std::cin >> choice1;

	switch (choice1)
	{
	case '1':
		if (player->range != 11)
		{
			if ((player->range == 10 && !(machineA.health > 0 || machineB.health > 0 || machineC.health > 0) || player->range != 10))
			{
				Entities* choosenEnemy = nullptr;
				bool confirmDead = false;
				while (!choosenEnemy || (choosenEnemy->health <= 0 && !confirmDead) || choosenEnemy->floating)
				{
					std::string targetList = "Choose target:";
					if (enemy1->health > 0) targetList += "\n1. " + enemy1->role;
					if (enemy2->health > 0) targetList += "\n2. " + enemy2->role;
					if (enemy3->health > 0) targetList += "\n3. " + enemy3->role;
					targetList += "\n4. Cancel operation";
					targetList += "\nYour choice : ";
					int target = avoidRetardInput(targetList, 1, 4);
					if (target == 4)
					{
						goto currentChoice;
						break;
					}
					target == 1 ? choosenEnemy = enemy1 : target == 2 ? choosenEnemy = enemy2 : choosenEnemy = enemy3;
					if (choosenEnemy->health > 0 && !choosenEnemy->floating)
					{
						dealingDamage(player, choosenEnemy, 0, 0, player->maxHealth, choosenEnemy->maxHealth, 0, 0);
						printHealthBar(choosenEnemy, 5);
						if (choosenEnemy->health <= 0) confirmDead = true;
					}
					else
					{
						setColor(BO_RED);
						choosenEnemy->floating ?
							std::cout << "This unit can not be targeted, try choosing another one instead!\n" :
							std::cout << "This unit is already gone, try choosing another one!\n";
						setColor(7);
					}
				}
				player->range == 4 ? player->mana += 2 : player->mana++;
				choosenEnemy = nullptr;
				free(choosenEnemy);
			}
			else if (player->range == 10)
			{
				Entities* target = nullptr;
				bool confirmDead = false;
				while (!target || (target->health <= 0 && !confirmDead) || target->floating)
				{
					std::string targetList = "Choose target for machine to attack:";
					if (enemy1->health > 0) targetList += "\n1. " + enemy1->role;
					if (enemy2->health > 0) targetList += "\n2. " + enemy2->role;
					if (enemy3->health > 0) targetList += "\n3. " + enemy3->role;
					targetList += "\n4. Cancel operation";
					targetList += "\nYour choice : ";
					int targetLock = avoidRetardInput(targetList, 1, 4);
					if (targetLock == 4)
					{
						goto currentChoice;
						break;
					}
					Entities* machineHealed = nullptr;
					setColor(14);
					std::cout << player->role;
					setColor(7);
					std::cout << " healed the machine with least HP for ";
					setColor(2);
					std::cout << player->abilityPower << " HP!\n";
					setColor(7);
					if (machineA.health < machineB.health && ((machineA.health < machineC.health && machineC.health > 0) || (machineA.health > machineC.health && machineC.health <= 0)) && machineA.health > 0)
					{
						machineA.health + player->abilityPower > 1500 ? machineA.health = 1500 : machineA.health += player->abilityPower;
						machineHealed = &machineA;
					}
					else if (machineB.health < machineA.health && ((machineB.health < machineC.health && machineC.health > 0) || (machineB.health > machineC.health && machineC.health <= 0)) && machineB.health > 0)
					{
						machineB.health + player->abilityPower > 1500 ? machineB.health = 1500 : machineB.health += player->abilityPower;
						machineHealed = &machineB;
					}

					else if (machineC.health > 0)
					{
						machineC.health + player->abilityPower > 1500 ? machineC.health = 1500 : machineC.health += player->abilityPower;
						machineHealed = &machineC;
					}
					targetLock == 1 ? target = enemy1 : targetLock == 2 ? target = enemy2 : target = enemy3;
					if (target->health > 0 && !target->floating)
					{
						if (machineA.health > 0) dealingDamage(&machineA, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (machineB.health > 0) dealingDamage(&machineB, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (machineC.health > 0) dealingDamage(&machineC, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (target->health <= 0) confirmDead = true;
					}
					else
					{
						setColor(BO_RED);
						target->floating ?
							std::cout << "This unit can not be targeted, try choosing another one instead!\n" :
							std::cout << "This unit is already gone, try choosing another one!\n";
						setColor(7);
					}
				}
				target = nullptr;
				free(target);
				player->mana++;
				printf("\n");
			}
		}
		else
		{
			Entities* healedTarget = nullptr;
			int targetChoose, healing = player->abilityPower;
			if (player->autoProtect) healing = healing * 115 / 100;
			std::string targetList = "Choose ally to heal:";
			if (ally1->health > 0) targetList += "\n1. " + ally1->role;
			if (ally2->health > 0) targetList += "\n2. " + ally2->role;
			if (player->health > 0) targetList += "\n3. " + player->role;
			targetList += "\n4. Cancel operation";
			targetList += "\nYour choice : ";
			targetChoose = avoidRetardInput(targetList, 1, 4);
			if (targetChoose == 4) { goto currentChoice; }
			else
			{
				targetChoose == 1 ? healedTarget = ally1 : targetChoose == 2 ? healedTarget = ally2 : healedTarget = player;
				healedTarget->poisoned > 0 ? healing = healing * 4 / 10 : healing = healing;
				setColor(2);
				healedTarget->range != 11 ? std::cout << '\n' << player->role << " healed " << healedTarget->role << ' ' : std::cout << player->role << " healed themself for ";
				std::cout << healing << " HP and ", setColor(6);
				std::cout << "granted to them 1 mana!\n", setColor(7);
				if (healedTarget->health > 0) healedTarget->health += healing;
				else
				{
					setColor(12);
					printf("You can not heal the deads, fools!\n"), setColor(7);
					goto currentChoice;
				}
				if (healedTarget->health > healedTarget->maxHealth) healedTarget->health = healedTarget->maxHealth;
				player->healingDone += healing;
				healedTarget->mana++;
				player->mana++;
				printHealthBar(healedTarget, 2);
				healedTarget = nullptr;
				free(healedTarget);
				printf("\n");
			}
		}
		break;
	case '2':
	{
		if (player->mana >= mana1_1)
		{
			if (player->range != 11)
			{
				Entities* targetLock = nullptr;
				bool confirmDeath = false;
				if (player->range != 2)
				{
					while (!targetLock || (targetLock->health <= 0 && !confirmDeath) || targetLock->floating)
					{
						std::string targetList = "Choose target:";
						if (enemy1->health > 0) targetList += "\n1. " + enemy1->role;
						if (enemy2->health > 0) targetList += "\n2. " + enemy2->role;
						if (enemy3->health > 0) targetList += "\n3. " + enemy3->role;
						targetList += "\n4. Cancel operation";
						targetList += "\nYour choice : ";
						int target = avoidRetardInput(targetList, 1, 4);
						if (target == 4)
						{
							goto currentChoice;
							break;
						}
						target == 1 ? targetLock = enemy1 : target == 2 ? targetLock = enemy2 : targetLock = enemy3;
						if (targetLock->health > 0 && !targetLock->floating)
						{
							player->mana -= mana1_1;
							useSpell_1(player, targetLock, &machineA, &machineB, &machineC, targetLock->maxHealth);
							if (machineA.health > 0) dealingDamage(&machineA, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (machineB.health > 0) dealingDamage(&machineB, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (machineC.health > 0) dealingDamage(&machineC, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (player->range == 5) printHealthBar(player, 2);
							printHealthBar(targetLock, 5);
							if (targetLock->health <= 0) confirmDeath = true;
						}
						else
						{
							setColor(BO_RED);
							targetLock->floating ?
								std::cout << "This unit can not be targeted, try choosing another one instead!\n" :
								std::cout << "This unit is already gone, try choosing another one!\n";
							setColor(7);
						}
					}
				}
				else
				{
					player->mana -= mana1_1;
					useSpell_1(player, enemy1, &machineA, &machineB, &machineC, enemy1->maxHealth);
					printHealthBar(player, 2);
				}
				targetLock = nullptr;
				free(targetLock);
			}
			else
			{
				Entities* buffed = nullptr;
				bool confirmDeath = false;
				while (!buffed || (buffed->health <= 0 && !confirmDeath))
				{
					std::string targetList = "Choose allied target:";
					if (ally1->health > 0) targetList += "\n1. " + ally1->role;
					if (ally2->health > 0) targetList += "\n2. " + ally2->role;
					if (player->health > 0) targetList += "\n3. " + player->role;
					targetList += "\n4. Cancel operation";
					targetList += "\nYour choice : ";
					int target = avoidRetardInput(targetList, 1, 4);
					if (target == 4)
					{
						goto currentChoice;
						break;
					}
					target == 1 ? buffed = ally1 : target == 2 ? buffed = ally2 : buffed = player;
					if (buffed->health > 0)
					{
						player->mana -= mana1_1;
						int drugDamage = damageOutput(buffed->armor, 0, 1000, 0);
						setColor(12);
						std::cout << "Drug gained! " << buffed->role << " took " << drugDamage << " damage and has dramatically increased damage!\n";
						setColor(7);
						buffed->health -= drugDamage;
						printHealthBar(buffed, 12);
						buffed->adrenaile = 2;
						if (buffed->health <= 0) confirmDeath = true;
					}
					else std::cout << "This ally is already gone, choose another one instead!\n";
				}
				buffed = nullptr;
				free(buffed);
			}
		}
		else
		{
			std::cout << "Spell cast failed! You don't have enough mana!\n";
			playerChoice(player, ally1, ally2, enemy1, enemy2, enemy3);
			return;
		}
		break;
	}
	case '3':
	{
		if (player->mana >= mana1_2) {
			if ((player->range != 9 && player->range != 4) || (player->range == 4 && !player->genesisUsed) || (player->range == 9 && player->summonShitcom))
			{
				if (player->range == 11)
				{
					Entities* extraHealed = nullptr;
					while (!extraHealed || extraHealed->health < 0)
					{
						std::string targetList = "Choose ally to heal them extra:";
						if (ally1->health > 0) targetList += "\n1. " + ally1->role;
						if (ally2->health > 0) targetList += "\n2. " + ally2->role;
						if (player->health > 0) targetList += "\n3. " + player->role;
						targetList += "\nYour choice: ";
						int target = avoidRetardInput(targetList, 1, 3);
						target == 1 ? extraHealed = ally1 : target == 2 ? extraHealed = ally2 : extraHealed = player;
						if (extraHealed->health > 0)
						{
							player->mana -= mana1_2;
							int baseHealing = 200 + player->abilityPower, bonusHealing = 200 + player->abilityPower / 2;
							if (player->autoProtect)
							{
								baseHealing = baseHealing * 115 / 100;
								bonusHealing = bonusHealing * 115 / 100;
							}
							player->health > 0 ? player->health += baseHealing, player->healingDone += baseHealing : player->health = 0;
							ally1->health > 0 ? ally1->health += baseHealing, player->healingDone += baseHealing, ally1->mana++ : ally1->health = 0;
							ally2->health > 0 ? ally2->health += baseHealing, player->healingDone += baseHealing, ally2->mana++ : ally2->health = 0;

							extraHealed->health > 0 ? extraHealed->health += bonusHealing, player->healingDone += bonusHealing : extraHealed->health = 0;
							setColor(2);
							std::cout << "All allies restored " << baseHealing << " HP!\n" << extraHealed->role << " is healed for " << baseHealing + bonusHealing << " HP!\n";
							setColor(7);
							printHealthBar(player, 10);
							printHealthBar(ally1, 10);
							printHealthBar(ally2, 10);
						}
						else printf("This ally is already gone, try choosing another one!\n");
					}
					extraHealed = nullptr;
					free(extraHealed);
				}
				else if (player->range == 12)
				{
					Entities* buffed = nullptr;
					while (!buffed || buffed->health <= 0)
					{
						std::string targetList = "Choose allied target:";
						if (ally1->health > 0) targetList += "\n1. " + ally1->role;
						if (ally2->health > 0) targetList += "\n2. " + ally2->role;
						if (player->health > 0) targetList += "\n3. " + player->role;
						targetList += "\n4. Cancel operation";
						targetList += "\nYour choice : ";
						int target = avoidRetardInput(targetList, 1, 4);
						if (target == 4)
						{
							goto currentChoice;
							break;
						}
						target == 1 ? buffed = ally1 : target == 2 ? buffed = ally2 : buffed = player;
						if (buffed->health > 0)
						{
							player->mana -= mana1_2;
							setColor(2);
							std::cout << buffed->role << " gained 1 Shield!\n";
							setColor(7);
							buffed->shield++;
							buffed->poisoned = 0;
							buffed->fragile = 0;
						}
						else std::cout << "This ally is already gone, choose another one instead!\n";
					}
				}
				else if (player->range == 4 || player->range == 2)
				{
					player->mana -= mana1_2;
					useSpell2_2(player, enemy1, enemy2, enemy3);
					printHealthBar(enemy1, 5);
					printHealthBar(enemy2, 5);
					printHealthBar(enemy3, 5);
				}
				else
				{
					Entities* targetSpell = nullptr;
					bool confirmDead = false;
					int target;
					if (player->range != 9)
					{
						while ((!targetSpell || targetSpell->health <= 0) && !confirmDead || targetSpell->floating)
						{
							std::string targetList = "Choose target:";
							if (enemy1->health > 0) targetList += "\n1. " + enemy1->role;
							if (enemy2->health > 0) targetList += "\n2. " + enemy2->role;
							if (enemy3->health > 0) targetList += "\n3. " + enemy3->role;
							targetList += "\n4. Cancel operation";
							targetList += "\nYour choice : ";
							int target = avoidRetardInput(targetList, 1, 4);
							if (target == 4)
							{
								goto currentChoice;
								break;
							}
							target == 1 ? targetSpell = enemy1 : target == 2 ? targetSpell = enemy2 : targetSpell = enemy3;
							if (targetSpell->health > 0 && !targetSpell->floating)
							{
								player->mana -= mana1_2;
								useSpell_2(player, targetSpell, targetSpell->maxHealth, player->mana, player->health);
								if (targetSpell->health <= 0) confirmDead = true;
							}
							else
							{
								setColor(BO_RED);
								targetSpell->floating ?
									std::cout << "This unit can not be targeted, try choosing another one instead!\n" :
									std::cout << "This unit is already gone, try choosing another one!\n";
								setColor(7);
							}
						}
					}
					else useSpell_2(player, enemy1, enemy1->maxHealth, player->mana, player->health);

					if (player->range == 6 || player->range == 2 || player->range == 8 || player->range == 1 || player->range == 3)
					{
						if (player->range == 6) printHealthBar(player, 2);
						printHealthBar(targetSpell, 5);
					}
					else if (player->range == 10)
					{
						if (machineA.autoDestruct > 0 || machineB.autoDestruct > 0 || machineC.autoDestruct > 0)
						{
							setColor(12);
							printf("\nSpell error! Machine is already in destruction mode!\n");
							setColor(7);
							goto currentChoice;
						}
						else
						{
							Entities* machineX = nullptr;
							for (int i = 1; i <= 3; i++)
							{
								i == 1 ? machineX = &machineA : i == 2 ? machineX = &machineB : machineX = &machineC;
								if (machineX->health > 0 && machineX->autoDestruct == 0)
								{
									machineX->autoDestruct = 2;
									machineX->maxHealth *= 2;
									machineX->health *= 2;
									machineX->attackDmg = machineX->attackDmg * 27 / 10;
									machineX->armor += 200, machineX->magicRes += 200;
									dealingDamage(machineX, targetSpell, 0, 0, player->health, targetSpell->maxHealth, 0, 0);
								}
							}
							machineX = nullptr;
							free(machineX);
						}
					}
				}
			}
			else
			{
				std::cout << "Spell cast failed! This spell is no longer usable!\n";
				goto currentChoice;
			}
		}
		else
		{
			std::cout << "Spell cast failed! You don't have enough mana!\n";
			goto currentChoice;
		}

		break;
	}
	case '4':
		printPlayerInfo(player);
		goto currentChoice;
		break;
	case '5':
	{
		Entities* checkStats = nullptr;
		char select;
		std::cout << "Choose enemy to check its stats:\n1. " << enemy1->role << "\n2. " << enemy2->role << "\n3. " << enemy3->role << "\nEnter your choice: ";
		std::cin >> select;
		select == '1' ? checkStats = enemy1 : select == '2' ? checkStats = enemy2 : checkStats = enemy3;
		printEnemyInfo(checkStats);
		checkStats = nullptr;
		free(checkStats);
		goto currentChoice;
		break;
	}
	case '6':
	{
		if (player->range == 10)
		{
			if (player->fructure != 0)
			{
				int number = avoidRetardInput("Enter number of machines to summon (maxium 3): ", 1, 3);
				number > player->fructure ? number = player->fructure : number;
				for (int i = 1; i <= number; i++) {
					if (player->fructure >= 1) {
						setColor(10);
						std::cout << "Summoned new Machine!\n";

						if (machineA.health <= 0) machineA = createMachine();
						else if (machineB.health <= 0) machineB = createMachine();
						else if (machineC.health <= 0) machineC = createMachine();
						else
						{
							std::cout << "All machines are being deloyed, summoning broke!\n";
							break;
						}
						setColor(7);
						player->fructure--;
					}
					else
					{
						std::cout << "Summoning failed! You don't have enough structure point\n";
						goto currentChoice;
						break;
					}
				}
			}
			else
			{
				std::cout << "Summoning failed! You don't have enough structure point\n";
				goto currentChoice;
				break;
			}
			break;
		}
	}
	default:
		if (!skipTurnBanned)
		{
			std::cout << player->role << " skipped this turn and gained";
			if (player->range == 12)
			{
				printf(" 2 mana!\n");
				player->mana += 2;
			}
			else
			{
				printf(" 3 mana!\n");
				player->mana += 3;
			}
		}
		else
		{
			setColor(12);
			std::cout << "\nThis action has been neutralized!\nTry choosing another one.\n";
			setColor(7);
			goto currentChoice;
		}
		break;
	}

	if (player->range == 8 && player->obtainingSunblade && player->sunBlade < 4)
	{
		setColor(9);
		std::cout << '\n' << player->role << " obtained 1 Sun Blade!\n", setColor(7);
		player->sunBlade++;
	}
	else if (!player->obtainingSunblade)
	{
		setColor(9);
		std::cout << '\n' << player->role << " can not obtain any Sun Blade this turn!\n", setColor(7);
		player->obtainingSunblade = true;
	}
	if (player->fragile > 0)
	{
		player->fragile--;
		if (player->fragile == 0)
		{
			int reset = rand() % (100 - 1 + 1) + 1;
			if (reset <= 50) player->fragile = 2;
		}
	}
	player->attackDmg = storeDmg;
	inTurn = false;
}

void battleStart_3v3(Entities* player1, Entities* player2, Entities* player3, Entities* enemy1, Entities* enemy2, Entities* enemy3)
{
	bool instaDelete = true;
	const unsigned short certainSleepTime = (player2->role == "blank" ? 1 : 3);
	setColor(14);
	std::cout << "\n|==============================|\n";
	std::cout << "|         BATTLE START!        |\n";
	std::cout << "|==============================|\n\n";
	setColor(7);
	system("pause");
	srand(time(NULL));
	int turn = 0, towerRound = 0;
	bool specialForce = false, fighterWill = false, painSupress = false, anhquocSupremacy = false;
	bool emBladeInDiary = false;

	Entities* luubao, * pvinh, * anhQuoc, * duongLe, * minhphan, * supporter, * fighter, * caster, * defender, * alter;
	player1->range == 10 ? luubao = player1 : player2->range == 10 ? luubao = player2 : player3->range == 10 ? luubao = player3 : luubao = nullptr;
	player1->range == 8 ? duongLe = player1 : player2->range == 8 ? duongLe = player2 : player3->range == 8 ? duongLe = player3 : duongLe = nullptr;
	player1->range == 9 ? pvinh = player1 : player2->range == 9 ? pvinh = player2 : player3->range == 9 ? pvinh = player3 : pvinh = nullptr;
	player1->range == 6 ? anhQuoc = player1 : player2->range == 6 ? anhQuoc = player2 : player3->range == 6 ? anhQuoc = player3 : anhQuoc = nullptr;
	player1->range == 7 ? minhphan = player1 : player2->range == 7 ? minhphan = player2 : player3->range == 7 ? minhphan = player3 : minhphan = nullptr;
	player1->range == 11 ? supporter = player1 : player2->range == 11 ? supporter = player2 : player3->range == 11 ? supporter = player3 : supporter = nullptr;
	player1->range == 1 ? fighter = player1 : player2->range == 1 ? fighter = player2 : player3->range == 1 ? fighter = player3 : fighter = nullptr;
	player1->range == 4 ? caster = player1 : player2->range == 4 ? caster = player2 : player3->range == 4 ? caster = player3 : caster = nullptr;
	player1->range == 2 ? defender = player1 : player2->range == 2 ? defender = player2 : player3->range == 2 ? defender = player3 : defender = nullptr;
	player1->range == 12 ? alter = player1 : player2->range == 12 ? alter = player2 : player3->range == 12 ? alter = player3 : alter = nullptr;

	Entities* slug, * chimera, * phantom, * zombieOrc, * spirit, * henryFat, * singer, * shinigami, * Free, * en_soldier, * en_leader, * pos_def, * em_blade, * EoE, * cor_blade = nullptr, * cor_cas = nullptr;
	enemy1->role == "Explosive Slug" ? slug = enemy1 : enemy2->role == "Explosive Slug" ? slug = enemy2 : enemy3->role == "Explosive Slug" ? slug = enemy3 : slug = nullptr;
	enemy1->role == "Chimera" ? chimera = enemy1 : enemy2->role == "Chimera" ? chimera = enemy2 : enemy3->role == "Chimera" ? chimera = enemy3 : chimera = nullptr;
	enemy1->role == "Phantom" ? phantom = enemy1 : enemy2->role == "Phantom" ? phantom = enemy2 : enemy3->role == "Phantom" ? phantom = enemy3 : phantom = nullptr;
	enemy1->role == "Zombified Orc" ? zombieOrc = enemy1 : enemy2->role == "Zombified Orc" ? zombieOrc = enemy2 : enemy3->role == "Zombified Orc" ? zombieOrc = enemy3 : zombieOrc = nullptr;
	enemy1->role == "Vengeful Spirit" ? spirit = enemy1 : enemy2->role == "Vengeful Spirit" ? spirit = enemy2 : enemy3->role == "Vengeful Spirit" ? spirit = enemy3 : spirit = nullptr;
	enemy1->role == "Henry Fat" ? henryFat = enemy1 : enemy2->role == "Henry Fat" ? henryFat = enemy2 : enemy3->role == "Henry Fat" ? henryFat = enemy3 : henryFat = nullptr;
	enemy1->role == "The Singer" ? singer = enemy1 : enemy2->role == "The Singer" ? singer = enemy2 : enemy3->role == "The Singer" ? singer = enemy3 : singer = nullptr;
	enemy1->role == "Reaper" ? shinigami = enemy1 : enemy2->role == "Reaper" ? shinigami = enemy2 : enemy3->role == "Reaper" ? shinigami = enemy3 : shinigami = nullptr;
	enemy1->role == "Free" ? Free = enemy1 : enemy2->role == "Free" ? Free = enemy2 : enemy3->role == "Free" ? Free = enemy3 : Free = nullptr;
	enemy1->role == "Enraged Possessed Soldier" ? en_soldier = enemy1 : enemy2->role == "Enraged Possessed Soldier" ? en_soldier = enemy2 : enemy3->role == "Enraged Possessed Soldier" ? en_soldier = enemy3 : en_soldier = nullptr;
	enemy1->role == "Enraged Possessed Bone-Thrower" ? en_leader = enemy1 : enemy2->role == "Enraged Possessed Bone-Thrower" ? en_leader = enemy2 : enemy3->role == "Enraged Possessed Bone-Thrower" ? en_leader = enemy3 : en_leader = nullptr;
	enemy1->role == "Possessed Heavy Defender" ? pos_def = enemy1 : enemy2->role == "Possessed Heavy Defender" ? pos_def = enemy2 : enemy3->role == "Possessed Heavy Defender" ? pos_def = enemy3 : pos_def = nullptr;
	enemy1->range == 101 ? em_blade = enemy1 : em_blade = nullptr;
	enemy1->range == 150 ? EoE = enemy1 : EoE = nullptr;

	//module system
	/*
	Entities* applyModule = nullptr;
	for (int i = 1; i <= 3; i++)
	{
		i == 1 ? applyModule = player1 : i == 2 ? applyModule = player2 : applyModule = player3;
		if (!applyModule->extension) continue;
		std::string moduleBonus, moduleName;
		switch (applyModule->range)
		{
		case 1:
			moduleName = "Tale of Sword and Shield";
			moduleBonus = "Max health +200\nResistances +30\nSkills deal an additional 15% damage.";
			applyModule->maxHealth += 200, applyModule->health += 200;
			applyModule->armor += 30, applyModule->baseAR += 30;
			applyModule->baseMR += 30, applyModule->magicRes += 30;
			break;
		case 3:
			moduleName = "Strengthened Crossbow";
			moduleBonus = "Armor penetration +15%\nCrit chance +15%\nCritical attack now deals 230% damage.";
			applyModule->ARpen += 15, applyModule->critUp += 15;
			break;
		case 6:
			break;
		}
		setColor(applyModule->range);
		std::cout << applyModule->role << "'s module applied: " << moduleName << "\nOn-equip effects:\n" << moduleBonus;
		setColor(7);
	}
	applyModule = nullptr;
	free(applyModule);
	*/

	if (minhphan)
	{
		setColor(14);
		printf("\nMinh Phan is now on the battle, no healing shall be allowed!\n");
		setColor(7);
		enemy1->healingBanned = true, enemy2->healingBanned = true, enemy3->healingBanned = true;
		system("pause");
	}

	if (player1->nation == "101 Logistic Gang" && player1->nation == player2->nation && player2->nation == player3->nation)
	{
		Entities* playerX = nullptr;
		for (int i = 1; i <= 3; i++)
		{
			i == 1 ? playerX = player1 : i == 2 ? playerX = player2 : playerX = player3;
			if (pvinh) playerX->shield++;
			if (anhQuoc) playerX->mana += 3;
			if (duongLe) { playerX->ARpen += 10; playerX->MRpen += 10; }
			if (minhphan) {
				playerX->baseAR += 70;
				playerX->armor = playerX->baseAR;
				playerX->baseMR += 100;
				playerX->magicRes = playerX->baseMR;
			}
		}
		playerX = nullptr;
		free(playerX);
	}

	if (defender)
	{
		defender->maxHealth = defender->maxHealth * 115 / 100;
		defender->health = defender->maxHealth;
	}

	if (alter)
	{
		player1->baseAD = player1->baseAD * 12 / 10, player1->attackDmg = player1->attackDmg * 12 / 10, player1->critUp += 10;
		player2->baseAD = player2->baseAD * 12 / 10, player2->attackDmg = player2->attackDmg * 12 / 10, player2->critUp += 10;
		player3->baseAD = player3->baseAD * 12 / 10, player3->attackDmg = player3->attackDmg * 12 / 10, player3->critUp += 10;
		player1->baseAP = player1->baseAP * 12 / 10, player1->abilityPower = player1->abilityPower * 12 / 10;
		player2->baseAP = player2->baseAP * 12 / 10, player2->abilityPower = player2->abilityPower * 12 / 10;
		player3->baseAP = player3->baseAP * 12 / 10, player3->abilityPower = player3->abilityPower * 12 / 10;
	}

	Entities* marked = nullptr;

	if (henryFat)
	{
		setColor(13);
		std::cout << henryFat->role << " took their move and deals to all units 30% max HP true damage!\n", setColor(7);
		player1->health -= player1->maxHealth * 3 / 10;
		player2->health -= player2->maxHealth * 3 / 10;
		player3->health -= player3->maxHealth * 3 / 10;
	}

	if (em_blade)
	{
		player1->poisoned = 100;
		player2->poisoned = 100;
		player3->poisoned = 100;
		if (recollectOpStart) emBladeInDiary = true;
	}

	if (singer && singer->challengeMode)
	{
		Entities* buff = nullptr;
		for (int i = 1; i <= 3; i++)
		{
			i == 1 ? buff = enemy1 : i == 2 ? buff = enemy2 : buff = enemy3;
			buff->baseAD = buff->baseAD * 15 / 10, buff->attackDmg = buff->attackDmg * 15 / 10;
			buff->baseAP = buff->baseAP * 15 / 10, buff->abilityPower = buff->abilityPower * 15 / 10;
		}
		buff = nullptr;
		free(buff);
	}

	if (Free && Free->challengeMode) skipTurnBanned = true;

	//Tha battle, overall
	while ((player1->health > 0 || player2->health > 0 || player3->health > 0) && (enemy1->health > 0 || enemy2->health > 0 || enemy3->health > 0))
	{

		int lowestHP = minHealth(player1, player2, player3);
		Entities* gotAtked = lowestHP == 1 ? player1 : lowestHP == 2 ? player2 : player3;

		if (singer && !singer->solo && singer->health > 0 && ((singer == enemy1 && enemy2->health <= 0 && enemy3->health <= 0) || (singer == enemy2 && enemy1->health <= 0 && enemy3->health <= 0) || (singer == enemy3 && enemy1->health <= 0 && enemy2->health <= 0)))
		{
			PlaySound(TEXT("ost\\dawnseeker.wav"), NULL, SND_ASYNC);
			setColor(12);
			printf("\nSoloist: The Singer no longer possess \"Low-altitude hovering\", instead has significantly increased ATK and inflicts AoE attacks\n");
			singer->solo = true;
			singer->floating = false;
			singer->baseAP = singer->baseAP * 12 / 10, singer->abilityPower = singer->baseAP;
			singer->MRpen = 25;
			Sleep(3000);
		}

		//Poison kissu
		int playerRemain = 0, poisonedPlayer = 0;

		if (henryFat)
		{
			for (int i = 0; i < 3; i++)
			{
				Entities* poisoned = nullptr;
				i == 0 ? poisoned = player1 : i == 1 ? poisoned = player2 : poisoned = player3;
				poisoned->health > 0 ? playerRemain++ : playerRemain = playerRemain;
				if (poisoned->health > 0 && poisoned->poisoned > 0)
				{
					int poisonBaseDmg = 200 + ((poisoned->maxHealth - poisoned->health) * 700 / poisoned->maxHealth);
					poisonBaseDmg > 500 ? poisonBaseDmg = 500 : poisonBaseDmg = poisonBaseDmg;
					int poisonDmg = damageOutput(0, poisoned->magicRes, 0, poisonBaseDmg);
					if (henryFat->challengeMode)
					{
						poisonDmg = poisonDmg * 15 / 10;
						poisonDmg < 300 ? poisonDmg = 300 : poisonDmg = poisonDmg;
					}
					if (poisoned->fragile > 0) poisonDmg = poisonDmg * 12 / 10;
					setColor(14);
					std::cout << "Poison triggers! " << poisoned->role << " took " << poisonDmg << " damage!\n", setColor(7);
					poisoned->health -= poisonDmg;
					poisoned->poisoned--;
					poisonedPlayer++;
					henryFat->damageDealt += poisonDmg;
				}
			}
			if (poisonedPlayer == playerRemain && henryFat->health > 0)
			{
				std::cout << "All units are poisoned, Henry Fat has significantly increased Resistances and restore HP every turn!\n";
				henryFat->health += minhphan ? 0 : 500;
				henryFat->armor = henryFat->baseAR * 25 / 10;
				henryFat->magicRes = henryFat->baseMR * 25 / 10;
			}
			else
			{
				henryFat->armor = henryFat->baseAR;
				henryFat->magicRes = henryFat->baseMR;
			}
		}

		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (spirit)
		{
			if (spirit->health > 0)
			{
				if (spirit->turn % 5 == 0)
				{
					marked = nullptr;
					while (!marked || marked->health <= 0)
					{
						int toMark = rand() % (3 - 1 + 1) + 1;
						toMark == 1 ? marked = player1 : toMark == 2 ? marked = player2 : marked = player3;
					}
					marked->spiritMark = 3;
					setColor(13);
					std::cout << spirit->role << " marked " << marked->role << "! In the next 2 turns, this unit is more vulnerable to damage!\n", setColor(7);
				}
				if (marked && marked->spiritMark == 1)
				{
					int manaCost = spirit->challengeMode ? 8 : 6;
					if (reduceManaRequirement) manaCost--;
					setColor(13);
					std::cout << "Mark activated! ";
					if (marked->mana >= manaCost)
					{
						int healing = spirit->challengeMode ? 1333 : 888;
						if (minhphan) healing = 0;
						marked->mana -= manaCost;
						spirit->health += healing;
						spirit->healingDone += healing;
						std::cout << spirit->role << " took " << manaCost << " mana from " << marked->role << " and healed themself for " << healing << " HP!\n";
					}
					else
					{
						std::cout << marked->role << " didn't have enough mana!\n";
						marked->health -= 9999;
						spirit->damageDealt += marked->maxHealth;
					}
					marked->spiritMark = 0;
					setColor(7);
				}
				else if (marked && marked->spiritMark > 0)
				{
					marked->health > 0 ? marked->spiritMark-- : marked->spiritMark = 0;
				}
			}
			else
			{
				player1->spiritMark = 0;
				player2->spiritMark = 0;
				player3->spiritMark = 0;
			}
		}

		if (turn % 4 == 0 && turn != 0)
		{
			if (pvinh && pvinh->health > 0)
			{
				setColor(10);
				std::cout << pvinh->role << " gained 1 Shield!\n";
				pvinh->shield++;
				setColor(7);
				system("pause");
			}

			if (phantom && (phantom->possessTalent == 9 || phantom->possessTalent2 == 9) && phantom->health > 0)
			{
				setColor(5);
				std::cout << '\n' << phantom->role << " gained 1 Shield!\n";
				phantom->shield++;
				setColor(7);
				system("pause");
			}
		}

		if (luubao && luubao->health > 0 && luubao->turn % 5 == 0 && luubao->turn != 0)
		{
			setColor(11);
			std::cout << "Luu Bao gained 1 Structure point!\n";
			setColor(7);
			luubao->fructure++;
			system("pause");
		}

		if (chimera && chimera->health > 0 && chimera->turn % 5 == 0 && chimera->turn != 0)
		{
			if (chimera->divine)
			{
				setColor(14);
				std::cout << '\n' << chimera->role;
				setColor(7);
				std::cout << " switched to ";
				setColor(12);
				std::cout << "'Predator' mode\n";
				setColor(7);
				std::cout << "Before leaving, they removed all of your good effects, cheer!\n";
				chimera->divine = false;
				chimera->predatorMode = true;
				chimera->critUp = 35;
				chimera->armor += 400;
				chimera->magicRes -= 400;
				chimera->abilityPower = 0;
				!(singer && singer->challengeMode) ? chimera->attackDmg = 573 : chimera->attackDmg = 573 * 15 / 10;
				if (pvinh) pvinh->shield = 0;
				if (duongLe) duongLe->sunBlade = 0;
				system("pause");
			}
			else {
				setColor(14);
				std::cout << '\n' << chimera->role;
				setColor(7);
				std::cout << " switched to ";
				setColor(5);
				std::cout << "'Divine Beast' mode\n";
				setColor(7);
				std::cout << "Before leaving, they dealt to ", setColor(14);
				std::cout << gotAtked->role, setColor(7);
				chimera->divine = true;
				chimera->predatorMode = false;
				chimera->critUp = 0;
				chimera->armor -= 400;
				chimera->magicRes += 400;
				chimera->attackDmg = 0;
				!(singer && singer->challengeMode) ? chimera->abilityPower = 535 : chimera->abilityPower = 535 * 15 / 10;
				int lastEmbrace = damageOutput(gotAtked->armor * 4 / 10, 0, 1000, 0);
				if (gotAtked->fragile > 0) lastEmbrace = lastEmbrace * 12 / 10;
				if (gotAtked->shield > 0)
				{
					lastEmbrace = 0;
					gotAtked->shield--;
					gotAtked->health += gotAtked->maxHealth / 5;
				}
				gotAtked->health -= lastEmbrace;
				chimera->damageDealt += lastEmbrace;
				setColor(12);
				lastEmbrace > 0 ? std::cout << " " << lastEmbrace << " damage " : std::cout << " 0 damage (blocked by shield) ";
				setColor(7);
				if (minhphan) lastEmbrace = 0;
				chimera->health += lastEmbrace * 2;
				chimera->healingDone += lastEmbrace * 2;
				std::cout << "and healed themself ";
				setColor(10);
				std::cout << lastEmbrace * 2 << " HP!\n";
				setColor(7);
				system("pause");
			}
		}

		if (pos_def && pos_def->health > 0 && turn % 3 == 2)
		{
			setColor(14);
			std::cout << pos_def->role << " taunts all allies this turn!\n", setColor(7);
			player1->taunt = 1, player2->taunt = 1, player3->taunt = 1;
		}

		if (emBladeInDiary)
		{
			if (player1->range == 7 && player1->health <= 0)
			{
				*player1 = createSoldier('C');
				alter = player1;
				minhphan = nullptr;
				alter->reincarnation = true;
			}
			if (player2->range == 8 && player2->health <= 0)
			{
				*player2 = createSoldier('3');
				duongLe = nullptr;
				player2->exploit = true;
			}
			if (player3->range == 9 && player3->health <= 0)
			{
				*player3 = createSoldier('2');
				pvinh = nullptr;
				defender = player3;
				defender->cooperSeal = true;
			}
		}
		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (pvinh && pvinh->health > 0)
		{
			int healthDiff1 = abs(enemy1->health - pvinh->health), healthDiff2 = abs(enemy2->health - pvinh->health), healthDiff3 = abs(enemy3->health - pvinh->health);
			int healthDiff = max(healthDiff1, max(healthDiff2, healthDiff3));
			int bonusDmg = healthDiff * 8 / 100;
			if (pvinh->adrenaile > 0) pvinh->attackDmg = pvinh->baseAD * 2;
			else pvinh->attackDmg = pvinh->baseAD;
			pvinh->attackDmg += bonusDmg;
		}

		if (player1->health > 0)
		{
			if (player1->adrenaile > 0)
			{
				player1->adrenaile--;
				if (player1->range != 9)
				{
					player1->attackDmg = player1->baseAD;
					player1->abilityPower = player1->baseAP;
				}
				player1->attackDmg *= 2, player1->abilityPower *= 2;
				if (player1->taunt)
				{
					dealingDamage(player1, pos_def, 0, 0, player1->health, pos_def->maxHealth, 0, 0);
					player1->taunt--;
				}
				else playerChoice(player1, player2, player3, enemy1, enemy2, enemy3);
				if (player1->range != 9)
				{
					player1->attackDmg = player1->baseAD;
					player1->abilityPower = player1->baseAP;
				}
			}
			else
			{
				if (player1->taunt)
				{
					dealingDamage(player1, pos_def, 0, 0, player1->health, pos_def->maxHealth, 0, 0);
					player1->taunt--;
				}
				else playerChoice(player1, player2, player3, enemy1, enemy2, enemy3);
			}
		}
		if (player2->health > 0)
		{
			if (player2->adrenaile > 0)
			{
				player2->adrenaile--;
				if (player2->range != 9)
				{
					player2->attackDmg = player2->baseAD;
					player2->abilityPower = player2->baseAP;
				}
				player2->attackDmg *= 2, player2->abilityPower *= 2;
				if (player2->taunt)
				{
					dealingDamage(player2, pos_def, 0, 0, player2->health, pos_def->maxHealth, 0, 0);
					player2->taunt--;
				}
				else playerChoice(player2, player1, player3, enemy1, enemy2, enemy3);
				if (player2->range != 9)
				{
					player2->attackDmg = player2->baseAD;
					player2->abilityPower = player2->baseAP;
				}
			}
			else
			{
				if (player2->taunt)
				{
					dealingDamage(player2, pos_def, 0, 0, player2->health, pos_def->maxHealth, 0, 0);
					player2->taunt--;
				}
				else playerChoice(player2, player1, player3, enemy1, enemy2, enemy3);
			}
		}
		if (player3->health > 0)
		{
			if (player3->adrenaile > 0)
			{
				player3->adrenaile--;
				if (player3->range != 9)
				{
					player3->attackDmg = player3->baseAD;
					player3->abilityPower = player3->baseAP;
				}
				player3->attackDmg *= 2, player3->abilityPower *= 2;
				if (player3->taunt)
				{
					dealingDamage(player3, pos_def, 0, 0, player3->health, pos_def->maxHealth, 0, 0);
					player3->taunt--;
				}
				else playerChoice(player3, player1, player2, enemy1, enemy2, enemy3);
				if (player3->range != 9)
				{
					player3->attackDmg = player3->baseAD;
					player3->abilityPower = player3->baseAP;
				}
			}
			else
			{
				if (player3->taunt)
				{
					dealingDamage(player3, pos_def, 0, 0, player3->health, pos_def->maxHealth, 0, 0);
					player3->taunt--;
				}
				else playerChoice(player3, player1, player2, enemy1, enemy2, enemy3);
			}
		}

		if (emBladeInDiary)
		{
			if (player1->range == 7 && player1->health <= 0)
			{
				*player1 = createSoldier('C');
				alter = player1;
				minhphan = nullptr;
				alter->reincarnation = true;
			}
			if (player2->range == 8 && player2->health <= 0)
			{
				*player2 = createSoldier('3');
				duongLe = nullptr;
				player2->exploit = true;
			}
			if (player3->range == 9 && player3->health <= 0)
			{
				*player3 = createSoldier('2');
				pvinh = nullptr;
				defender = player3;
				defender->cooperSeal = true;
			}
		}
		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;
		//5k+ lines go go

		Entities* targeto = nullptr;

		//Enemies attack

		system("pause");

		if (Free && Free->health > 0)
		{
			(Free->health < Free->maxHealth && Free->standBy) || (Free->taunt > 0) || (Free == enemy1 && enemy2->health <= 0 && enemy3->health <= 0) || (Free == enemy2 && enemy1->health <= 0 && enemy3->health <= 0) || (Free == enemy3 && enemy1->health <= 0 && enemy2->health <= 0) ? Free->standBy = false, Free->combat = true : 1;
			if (Free->standBy)
			{
				const int baseHealing = 750;
				Entities* targetToHeal = nullptr;
				for (int i = 0; i < 3; i++)
				{
					i == 0 ? targetToHeal = enemy1 : i == 1 ? targetToHeal = enemy2 : targetToHeal = enemy3;
					if (targetToHeal->health <= 0 || !targetToHeal) continue;
					int realHealing = baseHealing;
					if (targetToHeal->health < targetToHeal->maxHealth / 4) realHealing *= 3;
					else if (targetToHeal->health < targetToHeal->maxHealth / 2) realHealing *= 2;
					targetToHeal->health += realHealing;
					setColor(14);
					std::cout << Free->role, setColor(11); std::cout << " healed ", setColor(14);
					std::cout << targetToHeal->role, setColor(11); std::cout << " for ", setColor(2);
					std::cout << realHealing << " HP!\n", setColor(7);
				}
			}
			else
			{
				int percent_maxHP = Free->maxHealth * 15 / 100;
				int shockwaveBonus = 1 + (Free->maxHealth - Free->health) / percent_maxHP;
				Free->shockwave = shockwaveBonus;
			}
		}		

		if (enemy1->health > 0 && (enemy1 != Free || (enemy1 == Free && enemy1->combat)))
		{
			if (cor_cas && cor_cas->health > 0 && enemy1 == em_blade)
			{
				int bonusDmg = cor_cas->maxHealth / 10;
				cor_cas->health -= bonusDmg;
				em_blade->abilityPower += bonusDmg;
			}

			if (enemy1->taunt == 0 || (enemy1->taunt != 0 && defender->health <= 0))
			{
				if (shinigami && enemy1 == shinigami)
				{
					if (shinigami->challengeMode || (shinigami->turn % 3 == 0 && shinigami->turn != 0)) useSpell2_2(enemy1, player1, player2, player3);
					else dealingDamage(enemy1, gotAtked, 0, 0, gotAtked->maxHealth, enemy1->maxHealth, 0, 0);
				}
				else
				{
					if (!enemy1->solo)
					{
						if (machineA.health <= 0 && machineB.health <= 0 && machineC.health <= 0 && shitcom.health <= 0)
						{
							playerRemain = 0, poisonedPlayer = 0;
							if (player1->health > 0) playerRemain++;
							else player1->poisoned = 0;
							if (player2->health > 0) playerRemain++;
							else player2->poisoned = 0;
							if (player3->health > 0) playerRemain++;
							else player3->poisoned = 0;
							if (player1->poisoned > 0) poisonedPlayer++;
							if (player2->poisoned > 0) poisonedPlayer++;
							if (player3->poisoned > 0) poisonedPlayer++;
							if (henryFat && henryFat == enemy1 && playerRemain == poisonedPlayer)
							{
								std::cout << "Henry Fat doesn't feel like attacking this round\n";
							}
							else
							{
								while (!targeto || targeto->health <= 0 || (henryFat && enemy1 == henryFat && targeto->poisoned > 0))
								{
									int targetChoice = rand() % (3 - 1 + 1) + 1;
									targetChoice == 1 ? targeto = player1 : targetChoice == 2 ? targeto = player2 : targeto = player3;
									if (targeto == player1 && ((targeto->range == 11 && (enemy1 != henryFat || !henryFat)) || (enemy1 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player3->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player2 : targeto = player3;
									}
									else if (targeto == player2 && ((targeto->range == 11 && (enemy1 != henryFat || !henryFat)) || (enemy1 == henryFat && targeto->poisoned > 0)) && (player1->health > 0 || player3->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player1 : targeto = player3;
									}
									else if (targeto == player3 && ((targeto->range == 11 && (enemy1 != henryFat || !henryFat)) || (enemy1 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player1->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player2 : targeto = player1;
									}
								}
							}
						}
						else
						{
							shitcom.health > 0 ? targeto = &shitcom : machineA.health > 0 ? targeto = &machineA : machineB.health > 0 ? targeto = &machineB : targeto = &machineC;
						}
						if (targeto) dealingDamage(enemy1, targeto, specialForce, fighterWill, targeto->maxHealth, enemy1->maxHealth, painSupress, anhquocSupremacy);
					}
					else
					{
						for (int i = 0; i < 7; i++)
						{
							switch (i)
							{
							case 1:
								targeto = player1;
								break;
							case 2:
								targeto = player2;
								break;
							case 3:
								targeto = player3;
								break;
							case 4:
								targeto = &machineA;
								break;
							case 5:
								targeto = &machineB;
								break;
							case 6:
								targeto = &machineC;
								break;
							default:
								targeto = &shitcom;
								break;
							}
							if (targeto->health > 0) dealingDamage(enemy1, targeto, specialForce, fighterWill, targeto->maxHealth, enemy1->maxHealth, painSupress, anhquocSupremacy);
							else continue;
						}
					}
				}
				enemy1->taunt = 0;
			}
			else
			{
				defender->armor = defender->baseAR * 28 / 10, defender->magicRes = defender->baseMR * 28 / 10;
				dealingDamage(enemy1, defender, 0, 0, defender->health, enemy1->maxHealth, 0, 0);
				defender->armor = defender->baseAR, defender->magicRes = defender->baseMR;
				enemy1->taunt--;
			}

			if (em_blade) em_blade->abilityPower = 0;
		}

		if (emBladeInDiary)
		{
			if (player1->range == 7 && player1->health <= 0)
			{
				*player1 = createSoldier('C');
				alter = player1;
				minhphan = nullptr;
				alter->reincarnation = true;
				player1->attackDmg += 100, player1->baseAD += 100;
				player1->armor += 200, player1->baseAR += 200;
				player1->mana += 3;
			}
			if (player2->range == 8 && player2->health <= 0)
			{
				*player2 = createSoldier('3');
				duongLe = nullptr;
				player2->exploit = true;
				player2->attackDmg += 100, player2->baseAD += 100;
				player2->armor += 200, player2->baseAR += 200;
				player2->mana += 3;
			}
			if (player3->range == 9 && player3->health <= 0)
			{
				*player3 = createSoldier('2');
				pvinh = nullptr;
				defender = player3;
				defender->cooperSeal = true;
				player3->attackDmg += 100, player3->baseAD += 100;
				player3->armor += 200, player3->baseAR += 200;
				player3->mana += 3;
			}
		}
		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (enemy2->health > 0 && (enemy2 != Free || (enemy2 == Free && enemy2->combat)))
		{
			if (cor_blade && cor_blade->health > 0 && em_blade->health < em_blade->maxHealth)
			{
				int healing = cor_blade->maxHealth * 15 / 100;
				em_blade->health += healing;
				cor_blade->health -= healing;
				cor_blade->healingDone += healing;
			}

			if (enemy2->health > 0) //avoid bug to happen on corruptedbladeweaver
			{
				if (enemy2->taunt == 0 || (enemy2->taunt != 0 && defender->health <= 0))
				{
					if (shinigami && enemy2 == shinigami)
					{
						if (shinigami->challengeMode || (shinigami->turn % 3 == 0 && shinigami->turn != 0)) useSpell2_2(enemy2, player1, player2, player3);
						else dealingDamage(enemy2, gotAtked, 0, 0, gotAtked->maxHealth, enemy2->maxHealth, 0, 0);
					}
					else
					{
						if (!enemy2->solo)
						{
							if (machineA.health <= 0 && machineB.health <= 0 && machineC.health <= 0 && shitcom.health <= 0)
							{
								playerRemain = 0, poisonedPlayer = 0;
								if (player1->health > 0) playerRemain++;
								else player1->poisoned = 0;
								if (player2->health > 0) playerRemain++;
								else player2->poisoned = 0;
								if (player3->health > 0) playerRemain++;
								else player3->poisoned = 0;
								if (player1->poisoned > 0) poisonedPlayer++;
								if (player2->poisoned > 0) poisonedPlayer++;
								if (player3->poisoned > 0) poisonedPlayer++;
								targeto = nullptr;
								if (henryFat && henryFat == enemy2 && playerRemain == poisonedPlayer)
								{
									std::cout << "Henry Fat doesn't feel like attacking this round\n";
								}
								else
								{
									while (!targeto || targeto->health <= 0 || (henryFat && enemy2 == henryFat && targeto->poisoned > 0))
									{
										int targetChoice = rand() % (3 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player1 : targetChoice == 2 ? targeto = player2 : targeto = player3;
										if (targeto == player1 && ((targeto->range == 11 && (enemy2 != henryFat || !henryFat)) || (enemy2 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player3->health > 0))
										{
											targetChoice = rand() % (2 - 1 + 1) + 1;
											targetChoice == 1 ? targeto = player2 : targeto = player3;
										}
										else if (targeto == player2 && ((targeto->range == 11 && (enemy2 != henryFat || !henryFat)) || (enemy2 == henryFat && targeto->poisoned > 0)) && (player1->health > 0 || player3->health > 0))
										{
											targetChoice = rand() % (2 - 1 + 1) + 1;
											targetChoice == 1 ? targeto = player1 : targeto = player3;
										}
										else if (targeto == player3 && ((targeto->range == 11 && (enemy2 != henryFat || !henryFat)) || (enemy2 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player1->health > 0))
										{
											targetChoice = rand() % (2 - 1 + 1) + 1;
											targetChoice == 1 ? targeto = player2 : targeto = player1;
										}
									}
								}
							}
							else
							{
								shitcom.health > 0 ? targeto = &shitcom : machineA.health > 0 ? targeto = &machineA : machineB.health > 0 ? targeto = &machineB : targeto = &machineC;
							}
							if (targeto) dealingDamage(enemy2, targeto, specialForce, fighterWill, targeto->maxHealth, enemy2->maxHealth, painSupress, anhquocSupremacy);
						}
						else
						{
							for (int i = 0; i < 7; i++)
							{
								switch (i)
								{
								case 1:
									targeto = player1;
									break;
								case 2:
									targeto = player2;
									break;
								case 3:
									targeto = player3;
									break;
								case 4:
									targeto = &machineA;
									break;
								case 5:
									targeto = &machineB;
									break;
								case 6:
									targeto = &machineC;
									break;
								default:
									targeto = &shitcom;
									break;
								}
								if (targeto->health > 0) dealingDamage(enemy2, targeto, specialForce, fighterWill, targeto->maxHealth, enemy2->maxHealth, painSupress, anhquocSupremacy);
								else continue;
							}
						}
					}
					enemy2->taunt = 0;
				}
				else
				{
					defender->armor = defender->baseAR * 28 / 10, defender->magicRes = defender->baseMR * 28 / 10;
					dealingDamage(enemy2, defender, 0, 0, defender->health, enemy2->maxHealth, 0, 0);
					defender->armor = defender->baseAR, defender->magicRes = defender->baseMR;
					enemy2->taunt--;
				}
			}
		}

		if (emBladeInDiary)
		{
			if (player1->range == 7 && player1->health <= 0)
			{
				*player1 = createSoldier('C');
				alter = player1;
				minhphan = nullptr;
				alter->reincarnation = true;
			}
			if (player2->range == 8 && player2->health <= 0)
			{
				*player2 = createSoldier('3');
				duongLe = nullptr;
				player2->exploit = true;
			}
			if (player3->range == 9 && player3->health <= 0)
			{
				*player3 = createSoldier('2');
				pvinh = nullptr;
				defender = player3;
				defender->cooperSeal = true;
			}
		}
		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (enemy3->health > 0 && (enemy3 != Free || (enemy3 == Free && enemy3->combat)))
		{
			if (enemy3->taunt == 0 || (enemy3->taunt != 0 && defender->health <= 0))
			{
				if (shinigami && enemy3 == shinigami)
				{
					if (shinigami->challengeMode || (shinigami->turn % 3 == 0 && shinigami->turn != 0)) useSpell2_2(enemy3, player1, player2, player3);
					else dealingDamage(enemy3, gotAtked, 0, 0, gotAtked->maxHealth, enemy3->maxHealth, 0, 0);
				}
				else
				{
					if (!enemy3->solo)
					{
						if (machineA.health <= 0 && machineB.health <= 0 && machineC.health <= 0 && shitcom.health <= 0)
						{
							playerRemain = 0, poisonedPlayer = 0;
							if (player1->health > 0) playerRemain++;
							else
							{
								player1->poisoned = 0;
								player1->spiritMark = 0;
							}
							if (player2->health > 0) playerRemain++;
							else
							{
								player2->poisoned = 0;
								player2->spiritMark = 0;
							}
							if (player3->health > 0) playerRemain++;
							else
							{
								player3->poisoned = 0;
								player3->spiritMark = 0;
							}
							if (player1->poisoned > 0) poisonedPlayer++;
							if (player2->poisoned > 0) poisonedPlayer++;
							if (player3->poisoned > 0) poisonedPlayer++;
							targeto = nullptr;
							if (henryFat == enemy3 && playerRemain == poisonedPlayer)
							{
								std::cout << "Henry Fat doesn't feel like attacking this round\n";
							}
							else
							{
								while (!targeto || targeto->health <= 0 || (henryFat && enemy3 == henryFat && targeto->poisoned > 0))
								{
									int targetChoice = rand() % (3 - 1 + 1) + 1;
									targetChoice == 1 ? targeto = player1 : targetChoice == 2 ? targeto = player2 : targeto = player3;
									if (targeto == player1 && ((targeto->range == 11 && (enemy3 != henryFat || !henryFat)) || (enemy3 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player3->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player2 : targeto = player3;
									}
									else if (targeto == player2 && ((targeto->range == 11 && (enemy3 != henryFat || !henryFat)) || (enemy3 == henryFat && targeto->poisoned > 0)) && (player1->health > 0 || player3->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player1 : targeto = player3;
									}
									else if (targeto == player3 && ((targeto->range == 11 && (enemy3 != henryFat || !henryFat)) || (enemy3 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player1->health > 0))
									{
										targetChoice = rand() % (2 - 1 + 1) + 1;
										targetChoice == 1 ? targeto = player2 : targeto = player1;
									}
								}
							}
						}
						else
						{
							shitcom.health > 0 ? targeto = &shitcom : machineA.health > 0 ? targeto = &machineA : machineB.health > 0 ? targeto = &machineB : targeto = &machineC;
						}
						if (targeto) dealingDamage(enemy3, targeto, specialForce, fighterWill, targeto->maxHealth, enemy3->maxHealth, painSupress, anhquocSupremacy);
					}
					else
					{
						for (int i = 0; i < 7; i++)
						{
							switch (i)
							{
							case 1:
								targeto = player1;
								break;
							case 2:
								targeto = player2;
								break;
							case 3:
								targeto = player3;
								break;
							case 4:
								targeto = &machineA;
								break;
							case 5:
								targeto = &machineB;
								break;
							case 6:
								targeto = &machineC;
								break;
							default:
								targeto = &shitcom;
								break;
							}
							if (targeto->health > 0) dealingDamage(enemy3, targeto, specialForce, fighterWill, targeto->maxHealth, enemy3->maxHealth, painSupress, anhquocSupremacy);
							else continue;
						}
					}
				}
				enemy3->taunt = 0;
			}
			else
			{
				defender->armor = defender->baseAR * 28 / 10, defender->magicRes = defender->baseMR * 28 / 10;
				dealingDamage(enemy3, defender, 0, 0, defender->health, enemy3->maxHealth, 0, 0);
				defender->armor = defender->baseAR, defender->magicRes = defender->baseMR;
				enemy3->taunt--;
			}
		}

		if (emBladeInDiary)
		{
			if (player1->range == 7 && player1->health <= 0)
			{
				*player1 = createSoldier('C');
				alter = player1;
				minhphan = nullptr;
				alter->reincarnation = true;
			}
			if (player2->range == 8 && player2->health <= 0)
			{
				*player2 = createSoldier('3');
				duongLe = nullptr;
				player2->exploit = true;
			}
			if (player3->range == 9 && player3->health <= 0)
			{
				*player3 = createSoldier('2');
				pvinh = nullptr;
				defender = player3;
				defender->cooperSeal = true;
			}
		}

		if (slug)
		{
			if (slug->health <= slug->maxHealth / 2 && slug->resistanceBonus)
			{
				slug->resistanceBonus = false;
				if (!slug->challengeMode)
				{
					slug->armor = slug->armor - 600 < 0 ? 0 : slug->armor - 600;
					slug->magicRes = slug->magicRes - 600 < 0 ? 0 : slug->magicRes - 600;
					slug->attackDmg += 500;
				}
				else
				{
					slug->armor = slug->armor - 1000 < 0 ? 0 : slug->armor - 1000;
					slug->magicRes = slug->magicRes - 1000 < 0 ? 0 : slug->magicRes - 1000;
					!(singer && singer->challengeMode) ? slug->attackDmg += 800 : slug->attackDmg += 1200;
				}
			}
			else if (slug->health <= 0)
			{
				setColor(14);
				std::cout << "TRUE ART IS AN EXPLOSION! " << slug->role << " exploded and dealt 1000 damage to all friendly units!\n", setColor(7);
				player1->shield <= 0 ? (player1->fragile > 0 ? player1->health -= 1200 : player1->health -= 1000) : (player1->shield--, player1->health += player1->maxHealth / 5);
				player2->shield <= 0 ? (player2->fragile > 0 ? player2->health -= 1200 : player2->health -= 1000) : (player2->shield--, player2->health += player2->maxHealth / 5);
				player3->shield <= 0 ? (player3->fragile > 0 ? player3->health -= 1200 : player3->health -= 1000) : (player3->shield--, player3->health += player3->maxHealth / 5);
				slug = nullptr;
				free(slug);
			}
		}

		if (singer && singer->health <= 0)
		{
			setColor(14);
			std::cout << singer->role << " resurrected all of their fallen allies and applies 'Fragile' to all friendly unit in 10 turns!\n", setColor(7);
			enemy1->role == "Explosive Slug" ? slug = enemy1 : enemy2->role == "Explosive Slug" ? slug = enemy2 : enemy3->role == "Explosive Slug" ? slug = enemy3 : slug = nullptr;
			enemy1->role == "Chimera" ? chimera = enemy1 : enemy2->role == "Chimera" ? chimera = enemy2 : enemy3->role == "Chimera" ? chimera = enemy3 : chimera = nullptr;
			enemy1->role == "Phantom" ? phantom = enemy1 : enemy2->role == "Phantom" ? phantom = enemy2 : enemy3->role == "Phantom" ? phantom = enemy3 : phantom = nullptr;
			enemy1->role == "Zombified Orc" ? zombieOrc = enemy1 : enemy2->role == "Zombified Orc" ? zombieOrc = enemy2 : enemy3->role == "Zombified Orc" ? zombieOrc = enemy3 : zombieOrc = nullptr;
			enemy1->role == "Vengeful Spirit" ? spirit = enemy1 : enemy2->role == "Vengeful Spirit" ? spirit = enemy2 : enemy3->role == "Vengeful Spirit" ? spirit = enemy3 : spirit = nullptr;
			enemy1->role == "Henry Fat" ? henryFat = enemy1 : enemy2->role == "Henry Fat" ? henryFat = enemy2 : enemy3->role == "Henry Fat" ? henryFat = enemy3 : henryFat = nullptr;
			if (enemy1->health <= 0 && enemy1 != singer) enemy1->health = enemy1->maxHealth;
			if (enemy2->health <= 0 && enemy2 != singer) enemy2->health = enemy2->maxHealth;
			if (enemy3->health <= 0 && enemy3 != singer) enemy3->health = enemy3->maxHealth;
			player1->health > 0 ? player1->fragile = 10 : player1->fragile = 0;
			player2->health > 0 ? player2->fragile = 10 : player2->fragile = 0;
			player3->health > 0 ? player3->fragile = 10 : player3->fragile = 0;
			singer = nullptr;
			free(singer);
		}

		targeto = nullptr;
		free(targeto);

		setColor(10);
		machineA.autoDestruct == 1 ? machineA.health = 0, printf("Machine A destroyed!\n"), machineA.autoDestruct = 0 : machineA.autoDestruct > 0 ? machineA.autoDestruct-- : machineA.autoDestruct;
		machineB.autoDestruct == 1 ? machineB.health = 0, printf("Machine B destroyed!\n"), machineB.autoDestruct = 0 : machineB.autoDestruct > 0 ? machineB.autoDestruct-- : machineB.autoDestruct;
		machineC.autoDestruct == 1 ? machineC.health = 0, printf("Machine C destroyed!\n"), machineC.autoDestruct = 0 : machineC.autoDestruct > 0 ? machineC.autoDestruct-- : machineC.autoDestruct;
		setColor(7);

		//shitcome
		if (shitcom.role != "blank")
		{
			if (shitcom.health > 0)
			{
				setColor(12);
				std::cout << "Shitcom slight burnt, dealing 75 damage to all enemies!\n", setColor(7);
				enemy1->fragile ? enemy1->health -= 75 * 12 / 10 : enemy1->health -= 75;
				enemy2->fragile ? enemy2->health -= 75 * 12 / 10 : enemy2->health -= 75;
				enemy3->fragile ? enemy3->health -= 75 * 12 / 10 : enemy3->health -= 75;
			}
			else
			{
				setColor(14);
				std::cout << "OVERHEAT! Shitcom performed an explosion, deals to all enemies 1200 true damage!\n", setColor(7);
				enemy1->fragile ? enemy1->health -= 1200 * 12 / 10 : enemy1->health -= 1200;
				enemy2->fragile ? enemy2->health -= 1200 * 12 / 10 : enemy2->health -= 1200;
				enemy3->fragile ? enemy3->health -= 1200 * 12 / 10 : enemy3->health -= 1200;
				shitcom = createBlankTarget();
			}
		}

		enemy1->fragile > 0 ? enemy1->fragile-- : 1;
		enemy2->fragile > 0 ? enemy2->fragile-- : 1;
		enemy3->fragile > 0 ? enemy3->fragile-- : 1;

		//Zombie orc
		if (zombieOrc && zombieOrc->health > 0 && !zombieOrc->challengeMode)
		{
			setColor(6);
			std::cout << "\nZombified Orc loses ", setColor(12);
			std::cout << zombieOrc->maxHealth / 20 << " HP", setColor(6);
			std::cout << ", ", setColor(14);
			std::cout << zombieOrc->armor / 5 << " armor ", setColor(6);
			std::cout << "and ", setColor(5);
			std::cout << zombieOrc->magicRes / 5 << " magic resist!\n", setColor(7);
			zombieOrc->health -= zombieOrc->maxHealth / 20;
			zombieOrc->armor -= zombieOrc->armor / 5;
			zombieOrc->magicRes -= zombieOrc->magicRes / 5;
		}

		//Enraged kinds - S
		if (en_soldier && en_soldier->health > 0 && (!en_soldier->challengeMode || (en_soldier->challengeMode && en_soldier->turn >= 3)))
		{
			setColor(6);
			std::cout << en_soldier->role << " loses ", setColor(12);
			std::cout << en_soldier->maxHealth / 10 << " HP!\n", setColor(7);
			en_soldier->health -= en_soldier->maxHealth / 10;
		}

		if (en_leader && en_leader->health > 0 && (!en_leader->challengeMode || (en_leader->challengeMode && en_leader->turn >= 3)))
		{
			setColor(6);
			std::cout << en_leader->role << " loses ", setColor(12);
			std::cout << en_leader->maxHealth * 15 / 100 << " HP!\n", setColor(7);
			en_leader->health -= en_leader->maxHealth * 15 / 100;
		}

		if (pos_def && pos_def->health > 0)
		{
			setColor(6);
			std::cout << pos_def->role << " restores ", setColor(12);
			std::cout << pos_def->maxHealth / 20 << " HP!\n", setColor(7);
			pos_def->health += pos_def->maxHealth / 20;
		}
		//Enraged - E

		//reincarnation rune
		Entities* reincarRune = nullptr;
		for (int i = 1; i <= 3; i++)
		{
			i == 1 ? reincarRune = player1 : i == 2 ? reincarRune = player2 : reincarRune = player3;
			if (!reincarRune->reincarnation || reincarRune->health <= 0) continue;
			setColor(2);
			int restore = reincarRune->maxHealth * 3 / 100;
			if (reincarRune->poisoned > 0) restore = restore * 4 / 10;
			std::cout << reincarRune->role << " restores " << restore << " HP!\n", setColor(7);
			reincarRune->health += restore;
		}
		reincarRune = nullptr;
		free(reincarRune);

		if (em_blade)
		{
			if (em_blade->health <= 0 && instaDelete)
			{
				em_blade->maxHealth = 21500;
				em_blade->health = em_blade->maxHealth;
				em_blade->role = "Emperors' Blade - The Pursuer";
				instaDelete = false;
				if (!recollectOpStart)
				{
					setColor(12);
					std::cout << "Collapsee! " << em_blade->role << " has significantly increased attributes and will perform AoE attack once in a while!\n", setColor(7);
					if (em_blade->challengeMode)
					{
						setColor(12);
						std::cout << "Arise! " << em_blade->role << " summons their soldiers!\n";
						setColor(7);
					}
					em_blade->attackDmg += 200;
					em_blade->baseAD += 200;
					em_blade->magicRes += 200;
					em_blade->armor += 222;
				}
				if (em_blade->challengeMode)
				{
					*enemy2 = createCorKnight(0);
					*enemy3 = createCorKnight_L(0);
					cor_blade = enemy2;
					cor_cas = enemy3;
				}
			}

			if (em_blade->turn % 3 == 2 && (!instaDelete || recollectOpStart))
			{
				setColor(8);
				std::cout << "His blade staining red...\n";
				setColor(7);
				Sleep(3000);
				em_blade->attackDmg = em_blade->attackDmg * 8 / 10;
				em_blade->solo = true;
				player1->poisoned = 10;
				player2->poisoned = 10;
				player3->poisoned = 10;
			}
			else
			{
				em_blade->attackDmg = em_blade->baseAD;
				em_blade->solo = false;
			}

		}

		if (EoE)
		{
			if (EoE->health <= 0 && EoE->role != "Essence of Evolution - Perfect Form")
			{
				EoE->health = EoE->maxHealth;
				EoE->role == "Essence of Evolution" ? EoE->role = "Essence of Evolution - Evolution Form" : EoE->role = "Essence of Evolution - Perfect Form";
			}

			if (EoE->health > 0)
			{
				if (EoE->role == "Essence of Evolution")
				{
					EoE->magicRes = 9999;
					EoE->attackDmg = EoE->baseAD * 16 / 10;
					EoE->abilityPower = EoE->baseAP * 13 / 10;
					EoE->health += 800;
				}
				else if (EoE->role == "Essence of Evolution - Evolution Form")
				{
					EoE->armor = 9999;
					EoE->magicRes = 650;
					EoE->attackDmg = EoE->baseAD * 14 / 10;
					EoE->abilityPower = EoE->baseAP * 18 / 10;
					if (EoE->challengeMode) EoE->health += 600;
					if (EoE->turn % 4 == 0)
					{
						*enemy2 = createMutant();
					}
				}
				else
				{
					EoE->attackDmg = 400, EoE->abilityPower = 400;
					EoE->ARpen = 100, EoE->MRpen = 100;
					EoE->armor = 1000, EoE->magicRes = 1000;
					EoE->critUp = -25;
					EoE->solo = true;
					if (EoE->challengeMode) EoE->floating = true;
					EoE->health -= !EoE->challengeMode ? (EoE->maxHealth * 12 / 100) : (EoE->maxHealth * 8 / 100);
					if (EoE->turn % 2 == 0)
					{
						*enemy2 = createMutant();
						*enemy3 = createMutant();
					}
				}
			}
		}

		printHealthBar(player1, 10);
		printHealthBar(player2, 1);
		printHealthBar(player3, 11);
		if (machineA.health > 0) printHealthBar(&machineA, 8);
		if (machineB.health > 0) printHealthBar(&machineB, 2);
		if (machineC.health > 0) printHealthBar(&machineC, 9);
		if (shitcom.health > 0) printHealthBar(&shitcom, 14);
		printHealthBar(enemy1, 5);
		printHealthBar(enemy2, 13);
		printHealthBar(enemy3, 6);
		if (fighter && fighter->health > 0)
		{
			setColor(6);
			std::cout << "Stay determined! Fighter gained 30 attack damage and subtract all enemy's armor by 15!\n", setColor(7);
			fighter->baseAD += 30, fighter->attackDmg += 30;
			enemy1->baseAR -= 15, enemy1->armor -= 15;
			enemy2->baseAR -= 15, enemy2->armor -= 15;
			enemy3->baseAR -= 15, enemy3->armor -= 15;
		}

		if (phantom && (phantom->possessTalent == 1 || phantom->possessTalent2 == 1) && phantom->health > 0)
		{
			setColor(6);
			std::cout << "Stay chaotic! Phantom gained 30 attack damage and subtract all friendly unit's armor by 8!\n", setColor(7);
			phantom->baseAD += 30, phantom->attackDmg += 30;
			player1->baseAR -= 8, player1->armor -= 8;
			player2->baseAR -= 8, player2->armor -= 8;
			player3->baseAR -= 8, player3->armor -= 8;
		}

		if (phantom && (phantom->possessTalent == 8 || phantom->possessTalent2 == 8) && phantom->sunBlade < 2 && phantom->health > 0)
		{
			setColor(9);
			std::cout << phantom->role << " obtained 1 Moon Blade!\n", setColor(7);
			phantom->sunBlade++;
		}

		if (caster && caster->antiDeath) caster->antiDeath = false;
		if (fighter && fighter->fighter) fighter->fighter = false;
		setColor(GRAY);
		std::cout << certainSleepTime << " seconds until the next turn...\n";
		setColor(14);
		std::cout << "Upcoming turn: " << turn + 1 << '\n';
		setColor(7);
		Sleep(certainSleepTime * 1000);

		enemy1->turn++,
			enemy2->turn++,
				enemy3->turn++,
					turn++,
				player1->turn++,
			player2->turn++,
		player3->turn++;

		if (towerMode)
		{
			if (enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0)
			{
				towerRound++;
				skipTurnBanned = false;
				player1->shield++, player2->shield++, player3->shield++;
				player1->spiritMark = 0, player2->spiritMark = 0, player3->spiritMark = 0;
				bool isChallengeMode = enemy1->challengeMode;
				/////////////////////////////////////////////////////////////////////////////////////////////////////																									
				*enemy1 = createBlankTarget(), * enemy2 = createBlankTarget(), * enemy3 = createBlankTarget();
				zombieOrc = nullptr;			pos_def = nullptr;
				singer = nullptr;				en_leader = nullptr;
				Free = nullptr;					en_soldier = nullptr;
				spirit = nullptr;				slug = nullptr;
				em_blade = nullptr;				EoE = nullptr;
				chimera = nullptr;				shinigami = nullptr;
				henryFat = nullptr;				singer = nullptr;

				std::vector<short> randomStuff;
				if ((towerRound <= 5 && !isChallengeMode) || (isChallengeMode && !towerRound))
				{
					for (int j = 1; j <= 5; j++) randomStuff.push_back(j);
				}
				else
				{
					for (int j = 4; j <= 12; j++) randomStuff.push_back(j);
				}
				unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
				std::shuffle(randomStuff.begin(), randomStuff.end(), std::default_random_engine(num));

				Entities* resurrectEnemy = nullptr;
				for (int i = 1; i <= 3; i++)
				{
					i == 1 ? resurrectEnemy = enemy1 : i == 2 ? resurrectEnemy = enemy2 : resurrectEnemy = enemy3;

					const unsigned short randomEnemySeed = randomStuff[i - 1];
					switch (randomEnemySeed)
					{
					case 1:
						*resurrectEnemy = createGoblinChamp(0);
						break;
					case 2:
						*resurrectEnemy = createSeniorShaman(0);
						break;
					case 4:
						*resurrectEnemy = createAplha(0);
						henryFat = resurrectEnemy;
						break;
					case 7:
						*resurrectEnemy = createChimera(0);
						chimera = resurrectEnemy;
						if (isChallengeMode) chimera->maxHealth += 5000, chimera->health += 5000;
						break;
					case 8:
						*resurrectEnemy = createShinigami(0);
						shinigami = resurrectEnemy;
						if (isChallengeMode)
						{
							shinigami->baseAD -= shinigami->baseAD / 4;
							shinigami->attackDmg = shinigami->baseAD;
						}
						break;
					case 6:
						*resurrectEnemy = createFree(0);
						Free = resurrectEnemy;
						if (isChallengeMode) skipTurnBanned = true;
						break;
					case 3:
						*resurrectEnemy = createZombieOrc(0);
						zombieOrc = resurrectEnemy;
						break;
					case 5:
						*resurrectEnemy = createSpirit(0);
						spirit = resurrectEnemy;
						break;
					case 9:
						*resurrectEnemy = createPosKnight(0);
						en_soldier = resurrectEnemy;
						if (isChallengeMode) resurrectEnemy->shield += 3;
						break;
					case 10:
						*resurrectEnemy = createPosDef(0);
						pos_def = resurrectEnemy;
						break;
					case 12:
						*resurrectEnemy = createSinger(0);
						singer = resurrectEnemy;
						break;
					case 11:
						*resurrectEnemy = createPosKnight_L(0);
						if (isChallengeMode) resurrectEnemy->shield += 3;
						en_leader = resurrectEnemy;
						break;
					}
					if (minhphan) resurrectEnemy->healingBanned = true;
				}
				if (isChallengeMode)
				{
					enemy1->challengeMode = true, enemy2->challengeMode = true, enemy3->challengeMode = true;
					if (pos_def)
					{
						const short bonusArmor = pos_def->armor / 5;
						enemy1->armor += bonusArmor;
						enemy2->armor += bonusArmor;
						enemy3->armor += bonusArmor;
					}
					if (singer)
					{
						enemy1->attackDmg += enemy1->attackDmg / 2, enemy1->abilityPower += enemy1->abilityPower / 2;
						enemy2->attackDmg += enemy2->attackDmg / 2, enemy2->abilityPower += enemy2->abilityPower / 2;
						enemy3->attackDmg += enemy3->attackDmg / 2, enemy3->abilityPower += enemy3->abilityPower / 2;
					}
				}
				resurrectEnemy = nullptr;
				free(resurrectEnemy);
				setColor(12);
				std::cout << "\nNew challengers appeared: " << enemy1->role << " / " << enemy2->role << " / " << enemy3->role << ".\n\n";
				std::cout << "Current renew round: ";
				towerRound <= 5 ? setColor(LI_GREEN) : towerRound < 10 ? setColor(LI_YELLOW) : setColor(BO_RED);
				std::cout << towerRound << '\n';
				setColor(8);
			}
		}
	}

	//Shows result
	unsigned long long seed = 0;
	for (int i = 0; i < 6; i++)
	{
		int seedNumber = rand() % (9 - 1 + 1) + 1;
		seed += seedNumber * pow(10, i);
	}
	std::ofstream matchHistory("match_history.txt", std::ofstream::out | std::ios::app);
	matchHistory << "\n\nMatch seed (randomly generated): " << seed;
	if ((player1->health > 0 || player2->health > 0 || player3->health > 0) && enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0)
	{
		std::cout << "YOU WON! Good job\n";
		Entities* quoteSpeaker;
		int playerQuote = rand() % (3 - 1 + 1) + 1;
		playerQuote == 1 ? quoteSpeaker = player1 : playerQuote == 2 ? quoteSpeaker = player2 : quoteSpeaker = player3;
		if (quoteSpeaker->quotes != "")
		{
			setColor(14);
			std::cout << "\"" << quoteSpeaker->quotes << "\"\n";
			setColor(7);
		}
		quoteSpeaker = nullptr;
		free(quoteSpeaker);
		collectData(enemy1, player1, player2, player3);
		if (recollectOpStart)
		{
			collectDiary(enemy1, player1);
			recollectOpStart = false;
		}
		matchHistory << "\nResult: Victory";
	}
	else
	{
		std::cout << "YOU LOSTT! Better luck next time\n";
		matchHistory << "\nResult: Defeated";
	}
	setColor(7);
	std::cout << "Match history saved in \"match_history.txt\"!\n", setColor(14);
	std::cout << "Match's Seed: " << seed, setColor(7);
	std::cout << "\nYou can view it along with other matches.\n";
	towerMode ? matchHistory << "\nType: Endless Mode\n"
		: enemy1->challengeMode ? matchHistory << "\nType: Challenge Mode\n"
		: matchHistory << "\nType: Normal Mode\n";
	matchHistory << "Risk Level: " << risk << "\nTotal turns: " << turn << "\n\nTeam Combination - Player:\n1. " << player1->role << "\nDamage dealt: " << player1->damageDealt << "\nHealing done: " << player1->healingDone;
	matchHistory << "\n2. " << player2->role << "\nDamage dealt: " << player2->damageDealt << "\nHealing done: " << player2->healingDone;
	matchHistory << "\n3. " << player3->role << "\nDamage dealt: " << player3->damageDealt << "\nHealing done: " << player3->healingDone;;
	matchHistory << "\n\nTeam Combination - Enemy:";
	matchHistory << "\n1. " << enemy1->role << "\nDamage dealt: " << enemy1->damageDealt << "\nHealing done: " << enemy1->healingDone;
	matchHistory << "\n2. " << enemy2->role << "\nDamage dealt: " << enemy2->damageDealt << "\nHealing done: " << enemy2->healingDone;
	matchHistory << "\n3. " << enemy3->role << "\nDamage dealt: " << enemy3->damageDealt << "\nHealing done: " << enemy3->healingDone;
	matchHistory << "\n\n=============================================================================================";
	matchHistory.close();

	skipTurnBanned = false, towerMode = false;
	recollectOpStart = false;
	machineA = createBlankTarget(); machineB = createBlankTarget(); machineC = createBlankTarget(); shitcom = createBlankTarget();
	*player1 = createBlankTarget(), * player2 = createBlankTarget(), * player3 = createBlankTarget();
	*enemy1 = createBlankTarget(), * enemy2 = createBlankTarget(), * enemy3 = createBlankTarget();
	system("pause");
}

