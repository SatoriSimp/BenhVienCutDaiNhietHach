#pragma once
#include<iostream>

int minHealth(Entities* player1, Entities* player2, Entities* player3)
{
	if (((player1->health <= player2->health && player2->health > 0) || (player1->health > player2->health && player2->health <= 0)) && ((player1->health <= player3->health && player3->health > 0) || (player1->health > player3->health && player3->health <= 0)) && player1->health > 0) return 1;
	else if (((player2->health <= player1->health && player1->health > 0) || (player2->health > player1->health && player1->health <= 0)) && ((player2->health <= player3->health && player3->health > 0) || (player2->health > player3->health && player3->health <= 0)) && player2->health > 0) return 2;
	else return 3;
}

long damageOutput(int armor, int magicResistance, int physicDmg, int magicDmg) {
	if (armor > 950 && armor < 3000) armor = 950;
	else if (armor >= 3000) armor = 1000;
	if (magicResistance > 950 && magicResistance < 3000) magicResistance = 950;
	else if (magicResistance >= 3000) magicResistance = 1000;
	int physicTaken = physicDmg * (1000 - armor) / 1000;
	int magicTaken = magicDmg * (1000 - magicResistance) / 1000;
	return physicTaken + magicTaken;
}

int lifeSteal(int damage, int vamp) { return damage * vamp / 100; }

void bleedingDmg(Entities* target, Entities* caster)
{
	int reducedMR = target->magicRes * (100 - minhphanMRpen) / 100;
	if (reducedMR < 0) reducedMR = 0;
	int damageTaken2 = damageOutput(0, reducedMR, 0, (target->maxHealth * 10 / 100) + minhphanAP);
	if (caster->cooperSeal) damageTaken2 += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
	else if (caster->insult && target->health <= target->maxHealth * 5 / 10) damageTaken2 = damageTaken2 * 21 / 100;
	else if (caster->deathmatch)
	{
		int bonusDmg = 0;
		caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken2 * 15 / 100 : bonusDmg = bonusDmg;
		target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken2 * 15 / 100 : bonusDmg = bonusDmg;
		damageTaken2 += bonusDmg;
	}
	if (target->fragile) damageTaken2 = damageTaken2 * 12 / 10;
	if (target->range == -100) damageTaken2 /= 100;
	std::cout << "\nThis ability also triggered ";
	setColor(12);
	std::cout << "'Bleeding'";
	setColor(7);
	std::cout << " effect, deals an additional ";
	setColor(5);
	std::cout << damageTaken2 << " damage!\n";
	setColor(7);
	target->health -= damageTaken2;
	target->bleeding = false;
	caster->damageDealt += damageTaken2;
}

long runeDmg(Entities* target, Entities* caster, int damage)
{
	if (caster->cooperSeal) damage += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
	else if (caster->insult && target->health <= target->maxHealth / 2) damage = damage * 12 / 10;
	else if (caster->deathmatch)
	{
		int bonusDmg = 0;
		caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damage * 15 / 100 : bonusDmg = bonusDmg;
		target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damage * 15 / 100 : bonusDmg = bonusDmg;
		damage += bonusDmg;
	}
	return damage;
}

void dealingDamage(Entities* attacker, Entities* gotAttacked) {
	short attackTime = 1, shieldcount = 0;
	long totalDmg = 0;
	if (attacker->role == "Phalanx Heavyshooter")
	{
		attackTime = phalanx ? 4 : 3;
	}
	for (short i = 1; i <= attackTime; i++)
	{
		bool preventCrit = false;
		/*
		if (!allySupport)
		{
			short tempOmni = 0;
			if (attacker->absoluteFocus > 5)
			{
				tempOmni = 5 * (attacker->absoluteFocus - 5);
				attacker->omniVamp += tempOmni;
				attacker->absoluteFocus = 5;
			}
			attacker->attackDmg += attacker->attackDmg * 3 / 10 * attacker->absoluteFocus;
			attacker->critUp += 15 * attacker->absoluteFocus;
			attacker->ARpen += 7 * attacker->absoluteFocus;
		}
		*/
		if (attacker->role == "blank" || attacker->role == "Dummy") return;
		int damageTaken = damageOutput(gotAttacked->armor * (100 - attacker->ARpen) / 100, gotAttacked->magicRes * (100 - attacker->ARpen) / 100, (*attacker).attackDmg, (*attacker).abilityPower);
		if (attacker->range == 101 && attacker->solo)
		{
			const int atk_scale = (attacker->challengeMode || !attacker->turn) ? 120 : 85;
			damageTaken = damageOutput(0, gotAttacked->magicRes / 2, 0, (attacker->attackDmg + attacker->abilityPower) * atk_scale / 100);
		}
		else if (attacker->range == -100 && !attacker->stack) damageTaken = gotAttacked->maxHealth / 5;
		//Maskman talent
		if (attacker->range == 3)
		{
			int healthDifference = gotAttacked->maxHealth - attacker->maxHealth, dif_20PercentHP = attacker->maxHealth / 5;
			int bonusDmg = healthDifference / dif_20PercentHP;
			bonusDmg > 10 ? bonusDmg = 10 : bonusDmg < 0 ? bonusDmg = 0 : bonusDmg;
			damageTaken += damageTaken * (bonusDmg * 10) / 100;
		}

		//Enemy normal attack effect
		if (attacker->range == 101 && gotAttacked->fragile)
		{
			damageTaken = 9999;
			preventCrit = true;
		}

		if (attacker->stack > 0)
		{
			if (attacker->range != -100)
			{
				attacker->attackDmg += 160;
				attacker->baseAD += 160;
			}
			attacker->stack--;
		}

		if (attacker->firstStrike)
		{
			if (attacker->range == 102)
			{
				gotAttacked->baseAR = gotAttacked->baseAR * 6 / 10;
				gotAttacked->armor = gotAttacked->armor * 6 / 10;
				gotAttacked->sunBlade = 0;
				gotAttacked->shield = 0;
				gotAttacked->adrenaile = 0;
			}
			else {
				damageTaken = attacker->abilityPower;
				gotAttacked->mana = 0;
			}
			attacker->firstStrike = false;
		}
		else if (attacker->role == "Senior Drawft")
		{
			int bonusDamage;
			bonusDamage = !attacker->challengeMode ? (gotAttacked->maxHealth - gotAttacked->health) * 3 / 10 : (gotAttacked->maxHealth - gotAttacked->health) / 2;
			damageTaken += damageOutput(gotAttacked->armor, 0, bonusDamage, 0);
		}
		else if (attacker->role == "Vengeful Spirit" && (gotAttacked->spiritMark > 0)) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, gotAttacked->maxHealth * 18 / 100);
		else if (attacker->role == "Chimera")
		{
			if (attacker->challengeMode) damageTaken = attacker->attackDmg + attacker->abilityPower;
			if (attacker->divine)
			{
				!(attacker->challengeMode) ? damageTaken += damageOutput(0, gotAttacked->magicRes, 0, gotAttacked->health * 16 / 100) : damageTaken += gotAttacked->health * 16 / 100;
			}
		}
		else if (attacker->range == 60)
		{
			setColor(LI_PURPLE);
			!(gotAttacked->isNeutral) ? std::cout << gotAttacked->role << " is poisoned in the next 3 turns!\n", gotAttacked->poisoned = 3 : damageTaken *= 4;
			setColor(WHITE);
		}
		else if (attacker->range == 151)
		{
			gotAttacked->baseAD -= 40, gotAttacked->attackDmg -= 40;
			gotAttacked->baseAP -= 40, gotAttacked->abilityPower -= 40;
			gotAttacked->baseAD <= 10 ? gotAttacked->baseAD = 10 : gotAttacked->baseAD;
			gotAttacked->attackDmg <= 10 ? gotAttacked->attackDmg = 10 : gotAttacked->attackDmg;
			gotAttacked->baseAP < 0 ? gotAttacked->baseAP = 0 : gotAttacked->baseAP;
			gotAttacked->abilityPower < 0 ? gotAttacked->abilityPower = 0 : gotAttacked->abilityPower;
		}
		else if (attacker->range == 61 || (attacker->range == 101 && gotAttacked->health <= gotAttacked->maxHealth / 2))
		{
			attacker->range == 101 ? gotAttacked->fragile = 20 : gotAttacked->fragile = 2;
		}
		int criticalStrike = rand() % (100 - 0 + 1) + 1;
		attacker->possessTalent == 8 || attacker->possessTalent2 == 8 ? criticalStrike = 100 : criticalStrike = criticalStrike;


		if (!gotAttacked->specialForce)
		{
			//Crit attack
			if (!preventCrit && criticalStrike <= 15 + attacker->critUp && attacker->range != 8 && attacker->range != 12 && attacker->range != -1)
			{
				if (attacker->range != 68)
				{
					setColor(12);
					printf("CRITICAL STRIKE! The damage dealt is doubled up!\n");
					setColor(7);
				}
				attacker->predatorMode ? (gotAttacked->health >= gotAttacked->maxHealth / 2 ? damageTaken *= 25 / 10 : damageTaken *= 4) : damageTaken *= 2;
				if (attacker->exploit) damageTaken += 135 + damageTaken / 10;
			}

			if (attacker->range == 63) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, (attacker->attackDmg / 2) * (attacker->shockwave));
			//Bao Duong's attack system
			if (attacker->sunBlade)
			{
				int damagePerAtk = damageOutput(gotAttacked->armor, 0, attacker->attackDmg, 0), critTime = 0, dodgeTime = 0, grazeTime = 0;
				damageTaken = 0;
				int attackTimes = 1 + attacker->sunBlade;
				while (attackTimes > 0) {
					int critical = rand() % (100 - 1 + 1) + 1;
					attacker->possessTalent == 3 || attacker->possessTalent2 == 3 ? critical -= 20 : critical = critical;

					int evasion;
					(gotAttacked->range == 56 || gotAttacked->role == "Specialist") ? evasion = rand() % (100 - 1 + 1) + 1 : evasion = 100;

					gotAttacked->challengeMode ? evasion -= 30 : evasion = evasion;

					damageTaken += damagePerAtk;

					if (critical <= 15 + attacker->sunBlade * 7 + attacker->critUp)
					{
						damageTaken += damagePerAtk;
						critTime++;
					}

					if (evasion <= 20)
					{
						critical > 15 + attacker->sunBlade * 7 ? damageTaken -= damagePerAtk : damageTaken -= damagePerAtk * 2;
						dodgeTime++;
					}
					else if (evasion <= 50)
					{
						critical > 15 + attacker->sunBlade * 7 ? damageTaken -= damagePerAtk / 2 : damageTaken -= damagePerAtk;
						grazeTime++;
					}

					attackTimes--;
				}

				if (attacker->omniVamp >= 40) damageTaken += damageOutput(0, gotAttacked->magicRes * (100 - attacker->MRpen) / 100, 0, gotAttacked->maxHealth / 10);
				if (attacker->exploit) damageTaken += 135 + damagePerAtk / 5;

				if (attacker->isPlayer) std::cout << attacker->role << " stroke the enemy ";
				else
				{
					setColor(14);  std::cout << attacker->role;
					setColor(7);   std::cout << " stroke " << gotAttacked->role << "'s ass ";
				}
				setColor(12);
				attacker->sunBlade != 0 ? std::cout << 1 + attacker->sunBlade << " times" : std::cout << "1 time";
				setColor(7);
				std::cout << " and did ";
				setColor(12);
				std::cout << critTime << " critical attacks!\n";
				setColor(7);

				if (gotAttacked->role == "Senior Drawft" || gotAttacked->role == "Specialist")
				{
					setColor(14);
					std::cout << gotAttacked->role;
					setColor(7);
					std::cout << " dodged ";
					setColor(14); std::cout << attacker->role;
					setColor(7); std::cout << "'s attacks ";

					setColor(10);
					dodgeTime > 1 ? std::cout << dodgeTime << " times" : std::cout << dodgeTime << " time";
					setColor(7);
					std::cout << " and grazed ";
					setColor(10);
					grazeTime > 1 ? std::cout << grazeTime << " times\n" : std::cout << grazeTime << " time!\n";
					setColor(7);
				}
			}

			damageTaken = runeDmg(gotAttacked, attacker, damageTaken);

			//Specialist & Senior Drawft dodge system
			if (((*gotAttacked).role == "Specialist" || gotAttacked->role == "Senior Drawft") && attacker->range != 8)
			{
				int evasion = rand() % (100 - 1 + 1) + 1;
				if (gotAttacked->role == "Senior Drawft") evasion = rand() % (70 - 1 + 1) + 1;
				gotAttacked->challengeMode ? evasion -= 15 : evasion;

				if (evasion <= 20 || (*gotAttacked).readytoDodge)
				{
					damageTaken = 0;
					setColor(10);
					gotAttacked->isPlayer ? std::cout << "DODGED! You take no damage this round! " : std::cout << "DODGED! " << gotAttacked->role << " takes no damage this round! ";
					setColor(7);
					(*gotAttacked).readytoDodge = false;
				}
				else if (evasion <= 50)
				{
					damageTaken /= 2;
					setColor(10);
					gotAttacked->isPlayer ? std::cout << "GRAZED! You take half damage this round! " : std::cout << "GRAZED! " << gotAttacked->role << " takes half damage this round! ";
					setColor(7);
				}
			}

			//Anh Quoc's talent
			if (attacker->role == "Anh Quoc" || attacker->possessTalent == 6 || attacker->possessTalent2 == 6)
			{
				int randomBuff = rand() % (3 - 1 + 1) + 1;
				switch (randomBuff)
				{
				case 1:
					if (criticalStrike <= 15) printf("But this unit damage is already massive so it won't be increased! ");
					setColor(13);
					if (attacker->isPlayer) std::cout << attacker->role << "'s attack deals true damage and can not be dodged nor grazed!\n";
					else
					{
						setColor(14);
						std::cout << attacker->role;
						setColor(13);
						std::cout << " deals increased true damage!\n";
					}
					setColor(7);
					attacker->isPlayer ? damageTaken = damageOutput(0, 0, (*attacker).attackDmg * 2, 0) : damageTaken = damageOutput(0, 0, (*attacker).attackDmg * 15 / 10, 0);
					break;
				case 2:
					if (criticalStrike > 15)
					{
						if (attacker->isPlayer) std::cout << attacker->role << " are healed for ";
						else {
							setColor(14);
							std::cout << attacker->role;
							setColor(7);
							std::cout << " is healed for ";
						}
						setColor(2);
						int CopyHeal = attacker->maxHealth * 7 / 100;
						if (attacker->isPlayer) CopyHeal = attacker->maxHealth * 15 / 100;
						if (attacker->poisoned) CopyHeal = CopyHeal * 4 / 10;
						if (attacker->healingBanned) CopyHeal = 0;
						std::cout << CopyHeal << " HP!\n";
						setColor(7);
						(*attacker).health + CopyHeal > attacker->maxHealth ? (*attacker).health = attacker->maxHealth : (*attacker).health += CopyHeal;
					}
					else
					{
						if (attacker->isPlayer) std::cout << attacker->role << " is double-healed for ";
						else {
							setColor(14);
							std::cout << attacker->role;
							setColor(7);
							std::cout << " is double-healed for ";
						}
						setColor(2);
						int CopyHeal = attacker->maxHealth * 15 / 100;
						if (attacker->isPlayer) CopyHeal = attacker->maxHealth * 3 / 10;
						if (attacker->poisoned) CopyHeal = CopyHeal * 4 / 10;
						if (attacker->healingBanned) CopyHeal = 0;
						std::cout << CopyHeal << " HP!\n";
						setColor(7);

						(*attacker).health + CopyHeal > attacker->maxHealth ? (*attacker).health = attacker->maxHealth : (*attacker).health += CopyHeal;
					}
					break;
				case 3:
					if (attacker->isPlayer)
					{
						setColor(11);
						std::cout << attacker->role << " receives 1 bonus mana!\n";
						setColor(7);
						(*attacker).mana++;
					}
					else {
						setColor(14);
						std::cout << attacker->role;
						setColor(11);
						std::cout << " took 1 mana from " << gotAttacked->role << "\n";
						gotAttacked->mana--;
						gotAttacked->mana < 0 ? gotAttacked->mana = 0 : gotAttacked->mana;
						setColor(7);
					}
					break;
				}
			}

			if (gotAttacked->fragile > 0 && attacker->range != 101)
			{
				damageTaken = gotAttacked->isPlayer ? damageTaken * 12 / 10 : damageTaken * 14 / 10;
			}

			//AlterVinh talent
			if (attacker->range == 12 && damageTaken < (attacker->abilityPower + attacker->attackDmg) / 2) damageTaken = (attacker->abilityPower + attacker->attackDmg) / 2;

			//Phong Vinh's shield
			if (gotAttacked->shield > 0)
			{
				damageTaken = 0;
				int restore = gotAttacked->isPlayer ? gotAttacked->maxHealth / 5 : gotAttacked->maxHealth / 10;
				if (gotAttacked->poisoned > 0) restore = restore * 4 / 10;
				if (gotAttacked->healingBanned) restore = 0;
				if (attacker->range == 68)
				{
					shieldcount++;
				}
				else
				{
					std::cout << "This damage is blocked, " << gotAttacked->role << " restores ";
					setColor(2);
					std::cout << restore << " health!\n";
					setColor(7);
				}
				gotAttacked->health + restore <= gotAttacked->maxHealth ? gotAttacked->health += restore : gotAttacked->health = gotAttacked->maxHealth;
				gotAttacked->shield--;
			}

			//Fighter's skill 2
			if (gotAttacked->fighter && !(attacker->range == 101 && attacker->solo) && !(attacker->range == 101 && gotAttacked->fragile))
			{
				(*attacker).isEnemy ? damageTaken /= 10 : damageTaken /= 2;
			}
			if (gotAttacked->range == -100) damageTaken /= 100;

			//Life steal
			int healing = lifeSteal(damageTaken, (*attacker).omniVamp);
			if (attacker->poisoned > 0) healing = healing * 4 / 10;

			//Minh phan's bleeding effect & talent
			if ((*gotAttacked).bleeding) bleedingDmg(gotAttacked, attacker);

			if ((gotAttacked->range == 7 || gotAttacked->possessTalent == 7 || gotAttacked->possessTalent2 == 7) && !(attacker->solo && attacker->range == 101) && !(attacker->range == 101 && gotAttacked->fragile)) 
				damageTaken = damageTaken * 8 / 10;

			//Damage dealt
			(*gotAttacked).health -= damageTaken;
			if (attacker->range == 67)
			{
				gotAttacked->maxHealth -= damageTaken;
				if (gotAttacked->maxHealth < 100) gotAttacked->maxHealth = 100;
			}

			// Emperors' Blade passive
			if (attacker->role == "Emperors' Blade - The Pursuer" && gotAttacked->health < gotAttacked->maxHealth / 2) gotAttacked->fragile = 10;

			//Minh Phan's passive
			if ((*attacker).healingBanned) healing = 0;

			//If the healing went beyond unit's max health, it's set to their max health
			attacker->health + healing > attacker->maxHealth ? attacker->health = attacker->maxHealth : attacker->health += healing;

			//Send damage output
			if (attacker->range != 68)
			{
				if ((*attacker).isPlayer && (attacker->attackDmg > 0 || attacker->abilityPower > 0))
				{
					std::cout << attacker->role << " dealt to ";
					setColor(14);
					std::cout << (*gotAttacked).role << " ";
					setColor(7);
					if (attacker->abilityPower > attacker->attackDmg) { setColor(5); }
					else { setColor(12); }
					std::cout << damageTaken << " damage!\n";
					setColor(7);
				}
				else if (damageTaken > 0)
				{
					setColor(14);
					std::cout << (*attacker).role;
					setColor(7);
					std::cout << " dealt to " << gotAttacked->role << ' ';
					if (attacker->abilityPower > attacker->attackDmg) { setColor(5); }
					else { setColor(12); }
					std::cout << damageTaken << " damage!\n";
					setColor(7);
				}
			}
			else totalDmg += damageTaken;

			//Specialist skill 2 activation
			if ((*gotAttacked).emergencyOn && (*gotAttacked).health < 0)
			{
				(*gotAttacked).health = 1000;
				(*gotAttacked).emergencyOn = false;
				setColor(11);
				if (gotAttacked->isPlayer)
				{
					std::cout << "The switch is on! You are healed for ";
					setColor(2);
					std::cout << 1000 + damageTaken << " HP ";
					setColor(11);
					std::cout << "and gains ";
					setColor(14);
					std::cout << "100% dodge";
					setColor(11);
					std::cout << " in the next turn!\n";
				}
				else
				{
					std::cout << "The switch is broken! " << gotAttacked->role << " is healed for ";
					setColor(2);
					std::cout << 1000 + damageTaken << " HP!\n";
				}
				setColor(7);
				(*gotAttacked).health += damageTaken;
				(*gotAttacked).mana += 3;
				(*gotAttacked).readytoDodge = true;
				gotAttacked->healingDone += damageTaken + 1000;
			}

			//Healing notification
			if ((*attacker).isPlayer && (*attacker).omniVamp > 0)
			{
				std::cout << "You also healed for ";
				setColor(2);
				std::cout << healing << " HP!\n";
				setColor(7);
			}
			else if (!(*attacker).isPlayer && (*attacker).omniVamp > 0)
			{
				setColor(14);
				std::cout << (*attacker).role;
				setColor(7);
				std::cout << " also healed themself for ";
				setColor(2);
				std::cout << healing << " HP!\n";
				setColor(7);
			}

			//Defender's talent
			if (gotAttacked->role == "Defender" || gotAttacked->possessTalent == 2 || gotAttacked->possessTalent2 == 2)
			{
				int damageReflect = damageOutput(0, attacker->magicRes, 0, 120 + (gotAttacked->armor * 6 / 10) + (gotAttacked->magicRes * 6 / 10));
				damageReflect = runeDmg(attacker, gotAttacked, damageReflect);
				if (attacker->fragile) damageReflect = damageReflect * 12 / 10;
				if (attacker->range == -100) damageReflect /= 100;
				attacker->health -= damageReflect;
				if (attackTime == 1)
				{
					std::cout << gotAttacked->role << " reflected to " << attacker->role << " ";
					setColor(5);
					std::cout << damageReflect << " damage!\n";
					setColor(7);
				}
				gotAttacked->damageDealt += damageReflect;
			}

			attacker->damageDealt += damageTaken;
			attacker->healingDone += healing;
		}
		//Specialist's skill 1
		else
		{
			if (criticalStrike <= 15 || (criticalStrike <= 50 && attacker->predatorMode))
			{
				attacker->predatorMode && (gotAttacked->health < gotAttacked->maxHealth / 2) ? damageTaken *= 4 : attacker->predatorMode ? damageTaken *= 25 / 10 : damageTaken *= 2;
				setColor(10);
				std::cout << "CRITICAL STRIKE! " << gotAttacked->role << "'s healed as twice as normal, how cheat!\n";
				setColor(7);
			}
			damageTaken = damageTaken * 7 / 10;
			if (gotAttacked->poisoned > 0) damageTaken = damageTaken * 4 / 10;
			(*gotAttacked).health + damageTaken < gotAttacked->maxHealth ? (*gotAttacked).health += damageTaken : (*gotAttacked).health = gotAttacked->maxHealth;
			std::cout << (*attacker).role << " tried to attack " << gotAttacked->role << ", but their attack has been adsorbed and instead heal ";
			setColor(2);
			std::cout << damageTaken << " HP!\n";
			setColor(7);
			gotAttacked->specialForce = false;
			gotAttacked->healingDone += damageTaken;
		}
	}
	if (attacker->range == 68)
	{
		setColor(LI_YELLOW);
		std::cout << attacker->role;
		setColor(7);
		std::cout << " attacked ", setColor(14);
		std::cout << gotAttacked->role, setColor(7);
		std::cout << " for a total of ", setColor(RED);
		std::cout << totalDmg << " damage!";
		if (shieldcount > 0)
		{
			setColor(LI_GREEN);
			std::cout << " (" << shieldcount << " of the attacks was blocked!)";
		}
		std::cout << '\n';
		setColor(7);
	}
}

void useSpell_1(Entities* caster, Entities* target, Entities* machineA, Entities* machineB, Entities* machineC, int maxHP) {
	int damageTaken = 0, damageTaken2 = 0;
	std::cout << caster->role << " used their first spell!\n";
	switch (caster->range)
	{
	case 1:
	{
		//Deals bonus physic dmg equal 20% max HP, ignore 50% armor but can not crit
		int bonusDmg = maxHP / 5, passiveDmg = caster->attackDmg - fighterBaseAD;
		damageTaken = damageOutput((target->armor * (100 - caster->ARpen) / 100) / 2, (*target).magicRes, bonusDmg + (*caster).attackDmg * 15 / 10 + passiveDmg * 2, 0);
		damageTaken = runeDmg(target, caster, damageTaken);
		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

		if (target->role == "Senior Drawft")
		{
			int evasion = rand() % (70 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				setColor(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				setColor(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				setColor(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				setColor(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		if (target->range == -100) damageTaken /= 100;
		(*target).health -= damageTaken;
		std::cout << caster->role << " dealt ";
		setColor(12);
		std::cout << damageTaken << " damage!\n";
		setColor(7);
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 2:
	{
		int healing = 300 + (caster->maxHealth - caster->health) / 5;
		if (caster->poisoned) healing = healing * 4 / 10;
		caster->health + healing < caster->maxHealth ? (*caster).health += healing : (*caster).health = caster->maxHealth;
		std::cout << caster->role << " restored " << healing << " HP!\n";
		setColor(7);
		break;
	}
	case 3:
	{
		//Next attack deals 180% damage and guarantee a crit, ignore 25% armor. Biefly benefits from 15% lifesteal
		damageTaken = damageOutput((target->armor * (100 - caster->ARpen) / 100) * 3 / 4, 0, ((*caster).attackDmg * 18 / 10) * 2, 0);

		//Maskman talent: Every 20% difference max health increases damage output by 10% (cap at 100%)
		int healthDifference = target->maxHealth - caster->maxHealth, dif_20PercentHP = caster->maxHealth / 5;
		int bonusDmg = healthDifference / dif_20PercentHP;
		bonusDmg > 10 ? bonusDmg = 10 : bonusDmg;
		damageTaken += damageTaken * (bonusDmg * 10) / 100;

		if (!caster->exploit) damageTaken = runeDmg(target, caster, damageTaken);
		else { damageTaken += damageTaken / 10 + 135; }

		if (target->fragile > 0) damageTaken = damageTaken * 14 / 10;

		if (target->role == "Senior Drawft")
		{
			int evasion = rand() % (70 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				setColor(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				setColor(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				setColor(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				setColor(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		int heal = damageTaken * 15 / 100 + 50 + lifeSteal(damageTaken, (*caster).omniVamp);
		if (caster->poisoned > 0) heal = heal * 4 / 10;
		if (target->range == -100) damageTaken /= 100;

		(*target).health -= damageTaken;
		(*caster).health += heal;

		caster->health > caster->maxHealth ? caster->health = caster->maxHealth : caster->health;
		std::cout << caster->role << " dealt ";
		setColor(12);
		std::cout << damageTaken << " damage";
		setColor(7);
		std::cout << " and healed for ";
		setColor(2);
		std::cout << heal << " HP!\n";
		setColor(7);
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 4:
	{
		//consume all mana
		//deals 200% ap 
		//every mana spent increases dmg by 80 + 40%
		//benefits from runes and other eff
		//deals magic dmg, 30% of the total dmg is treated as true dmg
		caster->mana += 3;
		damageTaken = caster->abilityPower * 2;
		int Sto = damageTaken;
		short manaConsumed = 0;
		while (caster->mana > 0)
		{
			if (manaConsumed >= 3) damageTaken += 80 + Sto * 45 / 100;
			caster->mana--;
			manaConsumed++;
		}

		damageTaken = runeDmg(target, caster, damageTaken);

		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;
		if (target->role == "Senior Drawft")
		{
			int evasion = rand() % (100 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				setColor(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				setColor(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				setColor(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				setColor(7);
			}
		}
		else if (target->range == 150) damageTaken = damageTaken * 3 / 4;
		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		int magicdmgTaken = damageTaken * 7 / 10,
			truedmgTaken = damageTaken - magicdmgTaken;
		
		damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, magicdmgTaken) + truedmgTaken;
		if (target->range == -100) damageTaken /= 100;
		target->health -= damageTaken;
		std::cout << caster->role << " consumed all mana to deal ";
		setColor(11);
		std::cout << damageTaken << " true damage!\n";
		setColor(7);
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 5:
	{
		/*
		Sacrifice 30% current HP to deal the exact amount of true damage (no lower than 100)
		For exchange, gain 100% evasion and heal for 70% damage taken next turn
		*/
		int healthSac = caster->health * 3 / 10;
		caster->health -= healthSac;
		damageTaken = healthSac;

		if (caster->cooperSeal) damageTaken += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
		else if (caster->insult && target->health <= target->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
		else if (caster->deathmatch)
		{
			int bonusDmg = 0;
			caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg += 0;
			target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg += 0;
			damageTaken += bonusDmg;
		}
		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

		damageTaken < 100 ? damageTaken = 100 : damageTaken = damageTaken;

		if (target->role == "Senior Drawft")
		{
			int evasion = rand() % (70 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				setColor(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				setColor(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				setColor(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				setColor(7);
			}
		}
		else if (target->range == 150) damageTaken = damageTaken * 3 / 4;

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->range == -100) damageTaken /= 100;
		(*target).health -= damageTaken;
		std::cout << "\n" << caster->role << " sacrificed ";
		setColor(2);
		std::cout << healthSac << " health ";
		setColor(7);
		std::cout << "to deal ";
		setColor(11);
		std::cout << damageTaken << " damage!\n";
		setColor(7);
		caster->specialForce = true;
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 6:
	{
		int spellSuccess = rand() % (100 - 1 + 1) + 1, maxHealth = 1888;
		int missingHealth = maxHealth - (*caster).health, percentHP5 = maxHealth * 5 / 100;
		int pity = 5 * (missingHealth / percentHP5);
		if (spellSuccess <= 40 + pity)
		{
			int damageTaken = damageOutput(target->armor * (100 - caster->ARpen) / 100, target->magicRes * (100 - caster->MRpen) / 100, (*caster).attackDmg * 6, (*caster).attackDmg * 6);

			if (caster->cooperSeal) damageTaken += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
			else if (caster->insult && target->health <= target->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
			else if (caster->deathmatch)
			{
				int bonusDmg = 0;
				caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
				target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
				damageTaken += bonusDmg;
			}
			if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

			if (target->role == "Senior Drawft")
			{
				int evasion = rand() % (70 - 1 + 1) + 1;
				if (evasion <= 20)
				{
					damageTaken = 0;
					setColor(10);
					std::cout << "\nDODGED! " << target->role << " takes no damage this round! ";
					setColor(7);
				}
				else if (evasion <= 50)
				{
					damageTaken /= 2;
					setColor(10);
					std::cout << "\nGRAZED! " << target->role << " takes half damage this round! ";
					setColor(7);
				}
			}
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", setColor(14);
				std::cout << target->role, setColor(7);
				std::cout << " restores ", setColor(2);
				std::cout << shieldHeal << " health!\n", setColor(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			if (target->range == -100) damageTaken /= 100;
			(*target).health -= damageTaken;
			setColor(4);
			std::cout << "\nPOWER OVERWHELMED! ";
			setColor(7);
			std::cout << caster->role << " dealt ";
			setColor(11);
			std::cout << damageTaken << " damage";
			setColor(7);
			printf(" total!\n");
			if (target->bleeding) bleedingDmg(target, caster);
		}
		else
		{
			(*caster).health -= 1888 * 3 / 10;
			setColor(4);
			std::cout << "\nPOWER OVERLOADED! ";
			setColor(7);
			std::cout << caster->role << " instead took ";
			setColor(12);
			std::cout << 1888 * 3 / 10 << " damage!\n";
			setColor(7);
		}
		break;
	}
	case 7:
	{
		int reduceRes = 0, bodySlam = 250 + (*caster).abilityPower * 15 / 10;

		std::string damage = "\nMinh Phan slammed his enemy, dealt: ";

		if ((*target).bleeding)
		{
			damage = "\nMinh Phan hit his enemy like a truck, dealt ";
			reduceRes = 60 + (*target).magicRes / 10;
			damageTaken2 = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
			if (caster->cooperSeal) damageTaken2 += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
			else if (caster->insult && target->health <= target->maxHealth * 4 / 10) damageTaken2 = damageTaken2 * 112 / 100;
			else if (caster->deathmatch)
			{
				int bonusDmg = 0;
				caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
				target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
				damageTaken2 += bonusDmg;
			}
			if (target->fragile > 0) damageTaken2 = damageTaken2 * 12 / 10;
			bodySlam *= 3;
			if (target->range == -100)
			{
				damageTaken2 /= 100;
				bodySlam /= 100;
			}
			if (target->shield > 0)
			{
				damageTaken2 = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", setColor(14);
				std::cout << target->role, setColor(7);
				std::cout << " restores ", setColor(2);
				std::cout << shieldHeal << " health!", setColor(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}

			std::cout << "\nThis ability also triggered ";
			setColor(12);
			std::cout << "'Bleeding'";
			setColor(7);
			std::cout << " effect, deals an additional ";
			setColor(5);
			std::cout << damageTaken2 << " damage!\n";
			setColor(7);
			target->health -= damageTaken2;
			target->bleeding = false;
		}

		damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, bodySlam);
		damageTaken = runeDmg(target, caster, damageTaken);

		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

		if (target->role == "Senior Drawft")
		{
			int evasion = rand() % (70 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				setColor(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				setColor(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				setColor(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				setColor(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->range == -100) damageTaken /= 100;
		std::cout << damage;
		setColor(5);
		std::cout << damageTaken << " damage!\n";
		setColor(7);
		(*target).health -= damageTaken;
		break;
	}
	case 8:
	{
		if (caster->sunBlade < 4)
		{
			setColor(LI_CIRNO);
			std::cout << caster->role << " obtained 1 Sun Blade!\n";
			setColor(7);
			caster->sunBlade++;
			dealingDamage(caster, target);
		}
		else
		{
			setColor(7);
			std::cout << caster->role << " gained ";
			setColor(4);
			std::cout << "40% omni vamp";
			setColor(7);
			std::cout << " this round and each attack deals ";
			setColor(5);
			printf("additional magic damage!\n");
			setColor(7);
			caster->omniVamp += 40;
			dealingDamage(caster, target);
			caster->omniVamp -= 40;
		}
		break;
	}
	case 9:
	{
		damageTaken = damageOutput(target->armor * (100 - caster->ARpen) / 100, 0, caster->attackDmg * 26 / 10, 0);
		damageTaken = runeDmg(target, caster, damageTaken);

		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;
		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->range == -100) damageTaken /= 100;
		int restore = caster->maxHealth * 9 / 100;
		if (caster->poisoned > 0) restore = restore * 4 / 10;
		std::cout << caster->role << " brandish their hammer, deals ";
		setColor(12);
		std::cout << damageTaken << " damage ";
		setColor(7);
		std::cout << "and restore ";
		setColor(2);
		std::cout << restore << " health!\n";
		setColor(7);
		caster->health + restore > caster->maxHealth ? caster->health = caster->maxHealth : caster->health += restore;
		target->health -= damageTaken;
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 10:
	{
		int machineDmg = 0;
		byte machineCount = 0;
		if (machineA->health > 0) { machineDmg += machineA->attackDmg * 3 + target->maxHealth * 2 / 50; machineCount++; }
		if (machineB->health > 0) { machineDmg += machineB->attackDmg * 3 + target->maxHealth * 2 / 50; machineCount++; }
		if (machineC->health > 0) { machineDmg += machineC->attackDmg * 3 + target->maxHealth * 2 / 50; machineCount++; }

		machineCount >= 2 ? damageTaken = damageOutput((target->armor * (100 - caster->ARpen) / 100) / 2, 0, machineDmg, 0) : damageTaken = damageOutput(target->armor * (100 - caster->ARpen) / 100, 0, machineDmg, 0);
		machineCount >= 2 ? std::cout << "RESONANT! All machines attacked! Deals " : std::cout << "Machine attacked! Deals ";

		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		if (target->range == -100) damageTaken /= 100;

		setColor(12);
		std::cout << damageTaken << " damage!\n";
		setColor(7);
		target->health -= damageTaken;
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 12:
	{
		damageTaken = damageOutput(0, target->magicRes * (100 - caster->ARpen) / 100, 0, 200 + caster->attackDmg * 15 / 10);
		if (damageTaken < caster->attackDmg / 2) damageTaken = caster->attackDmg / 2;
		target->fragile = 3;
		if (caster->cooperSeal) damageTaken += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
		else if (caster->insult && target->health <= target->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
		else if (caster->deathmatch)
		{
			int bonusDmg = 0;
			caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
			target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
			damageTaken += bonusDmg;
		}
		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;
		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->range == -100) damageTaken /= 100;
		setColor(14);
		std::cout << caster->role, setColor(7);
		std::cout << " dealt ", setColor(5);
		std::cout << damageTaken << " damage ", setColor(7);
		std::cout << "to ", setColor(14);
		std::cout << target->role, setColor(7);
		std::cout << " and affects ", setColor(11);
		std::cout << "'Fragile'", setColor(7);
		std::cout << " to them!\n";
		target->health -= damageTaken;
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 13:
	{
		damageTaken = runeDmg(target, caster, damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->abilityPower * 155 / 100 + target->armor));
		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;
		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", setColor(14);
			std::cout << target->role, setColor(7);
			std::cout << " restores ", setColor(2);
			std::cout << shieldHeal << " health!\n", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->range == -100) damageTaken /= 100;
		setColor(14);
		std::cout << caster->role, setColor(7);
		std::cout << " dealt ", setColor(5);
		std::cout << damageTaken << " damage ", setColor(7);
		std::cout << "to ", setColor(14);
		std::cout << target->role, setColor(7);


		target->health -= damageTaken;
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	default:
		std::cout << "\nLuu Bao breathes, dealing an uncounttable amount of damage!\n";
		break;
	}
	if ((*target).emergencyOn && (*target).health < 0)
	{
		setColor(5);
		std::cout << "The switch is broken! " << target->role << " is healed for ";
		setColor(2);
		std::cout << 1000 + damageTaken << " HP!\n";
		setColor(7);
		(*target).health += damageTaken;
		target->healingDone += damageTaken + 1000;
		(*target).mana += 3;
		(*target).readytoDodge = true;
		target->emergencyOn = false;
	}
	caster->damageDealt += damageTaken + damageTaken2;
}

void useSpell_2(Entities* caster, Entities* target, int maxHP, int mana, int playerHealth) {
	int damageTaken = 0, damageTaken2 = 0;
	int missingHealth = target->maxHealth - target->health;
	switch (caster->range)
	{
	case 1:
	{
		caster->fighter = true;
		int armorReduction = (*target).armor / 20 + 3;
		(*target).armor -= armorReduction;
		setColor(1);
		std::cout << caster->role << " stay focused, destroy target's armor by ";
		setColor(6);
		std::cout << armorReduction;
		setColor(1);
		std::cout << " and gain ";
		setColor(14);
		std::cout << "90% damage reduction ";
		setColor(1);
		std::cout << "this turn!\n";
		setColor(7);
		target->fighter = true;
		dealingDamage(caster, target);
		target->fighter = false;
		break;
	}
	case 3:
	{
		caster->baseAD += 50;
		caster->attackDmg += 50;
		caster->omniVamp = caster->omniVamp + 10 > 50 ? 50 : caster->omniVamp + 10;
		std::cout << caster->role << "'s attack damage is now increased to ";
		setColor(12);
		std::cout << caster->attackDmg;
		setColor(7);
		std::cout << "\nLife-steal is increased to ";
		setColor(4);
		std::cout << caster->omniVamp << "%\n";
		setColor(7);
		dealingDamage(caster, target);
		break;
	}
	case 4:
	{
		if (!caster->genesisUsed)
		{
			std::cout << caster->role << " take extra 100% damage this round, but won't be defeated by all means!\n";
			caster->antiDeath = true;
			caster->genesisUsed = true;
		}
		break;
	}
	case 5:
	{
		printf("This unit doesn't need such of thing, they will perform a normal attack instead\n");
		dealingDamage(caster, target);
		caster->mana++;
		break;
	}
	case 6:
	{
		setColor(12);
		std::cout << "Anh Quoc performs a bunch of auto attacks!\n", setColor(7);
		for (int i = 0; i < 6; i++) dealingDamage(caster, target);
		break;
	}
	case 7:
	{
		(*target).bleeding = true;
		std::cout << caster->role << " marked ", setColor(14);
		std::cout << target->role, setColor(7);
		std::cout << " with ", setColor(12);
		std::cout << "'Bleeding'" << std::endl;
		setColor(7);
		break;
	}
	case 8:
	{
		caster->sunBlade *= 4;
		int maxAR = target->armor;
		caster->ARpen += 15;
		dealingDamage(caster, target);
		caster->sunBlade = 0;
		caster->ARpen -= 15;
		caster->obtainingSunblade = false;
		break;
	}
	case 9:
	{
		setColor(10);
		std::cout << "Summoned new Shitcom!\n";
		setColor(7);
		shitcom = createShitCom();
		caster->summonShitcom = false;
		break;
	}
	case 10:
	{
		setColor(12);
		std::cout << "Destruction mode: All machines has dramatically increased stats, but will be automatically destroyed within 2 turns!\n";
		setColor(7);
		break;
	}
	default:
		printf("No data given\n");
		break;
	}
	if ((*target).emergencyOn && (*target).health < 0)
	{
		setColor(5);
		std::cout << "The switch is broken! " << target->role << " is healed for ";
		setColor(2);
		std::cout << 1000 + damageTaken << " HP!\n";
		setColor(7);
		(*target).health += damageTaken;
		target->healingDone += damageTaken;
		(*target).emergencyOn = false;
	}
	caster->damageDealt += damageTaken + damageTaken2;
}

void useSpell2_2(Entities* caster, Entities* target1, Entities* target2, Entities* target3)
{
	int baseDamageTaken;
	switch (caster->range)
	{
	case 2:
		setColor(14);
		std::cout << "Defender ", setColor(7);
		std::cout << "gains significantly increased resistances and 'Taunts' all enemies this turn!\n";
		target1->taunt = 1, target2->taunt = 1, target3->taunt = 1;
		break;
	case 4:
	{
		setColor(12);
		std::cout << "Meteorite fall!\n", setColor(7);
		int leastMR = min(target1->magicRes, min(target2->magicRes, target3->magicRes));
		baseDamageTaken = damageOutput(0, leastMR * (100 - caster->MRpen) / 100, 0, caster->abilityPower * 27 / 10);
		Entities* currentTarget = nullptr;
		for (int i = 1; i <= 3; i++)
		{
			i == 1 ? currentTarget = target1 : i == 2 ? currentTarget = target2 : currentTarget = target3;
			if (currentTarget->health <= 0) continue;

			int damageTaken = runeDmg(currentTarget, caster, baseDamageTaken);
			if (currentTarget->range == -100) damageTaken /= 100;
			currentTarget->health -= damageTaken;
			setColor(14);
			std::cout << caster->role, setColor(7);
			std::cout << " dealt to ", setColor(14);
			std::cout << currentTarget->role, setColor(5);
			std::cout << " " << damageTaken << " damage!\n", setColor(7);
			caster->damageDealt += damageTaken;
		}
		currentTarget = nullptr;
		free(currentTarget);
		break;
	}
	case 62:
	{
		if (target1->health <= 0 && target2->health <= 0 && target3->health <= 0)
		{
			setColor(12);
			return;
		}
		setColor(12);
		std::cout << "HARVEST! " << caster->role << " performs an AoE attack!\n";
		baseDamageTaken = caster->attackDmg * 133 / 100;
		bool killed = false;
		Entities* target = nullptr;
		for (int i = 0; i < 3; i++)
		{
			i == 0 ? target = target1 : i == 1 ? target = target2 : target = target3;
			if (target->health > 0)
			{
				int damageDeal = damageOutput(target->armor, 0, baseDamageTaken, 0);
				int missingHP = damageOutput(target->armor, 0, target->maxHealth - target->health, 0);
				damageDeal + missingHP > damageDeal * 3 ? damageDeal *= 3 : damageDeal += missingHP;
				if (target->fragile) damageDeal = damageDeal * 12 / 10;

				if (target->shield > 0)
				{
					target->shield--;
					damageDeal = 0;
					setColor(7);
					std::cout << "This damage is blocked! ", setColor(14);
					std::cout << target->role, setColor(7);
					std::cout << " restored ", setColor(2);
					std::cout << target->maxHealth / 5 << " HP!\n", setColor(7);
					target->health += target->maxHealth / 5;
					if (target->health > target->maxHealth) target->health = target->maxHealth;
				}

				if (target->range == 7) damageDeal = damageDeal * 8 / 10;
				else if (target->fighter) damageDeal /= 10;
				target->health -= damageDeal;
				setColor(14);
				std::cout << caster->role, setColor(7);
				std::cout << " dealt to ", setColor(14);
				std::cout << target->role, setColor(12);
				std::cout << " " << damageDeal << " damage!\n", setColor(7);
				if (target->health <= 0 && !target->emergencyOn) killed = true;
				else if (target->health <= 0 && target->emergencyOn)
				{
					std::cout << "The switch is on! " << target->role << " are healed for ";
					setColor(2);
					std::cout << 1000 + damageDeal << " HP ";
					setColor(11);
					std::cout << "and gains ";
					setColor(14);
					std::cout << "100% dodge";
					setColor(11);
					std::cout << " in the next turn!\n";
					target->health = 1000 + damageDeal;
					target->health > target->maxHealth ? target->health = target->maxHealth : target->health;
					target->mana += 3;
					target->readytoDodge = true;
					target->emergencyOn = false;
					target->healingDone += 1000 + damageDeal;
				}
				caster->damageDealt += damageDeal;
			}
		}
		target = nullptr;
		free(target);
		if (killed) useSpell2_2(caster, target1, target2, target3);
		break;
	}
	}
}
