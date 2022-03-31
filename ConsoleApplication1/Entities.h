#pragma once

class Entities
{
public:
	std::string role, trait, talent, spell_1, spell_2, quotes = "", tags, nation;
	//attribute
	bool isPlayer, isEnemy, isNeutral;
	//player speciality
	bool emergencyOn = false, readytoDodge = false, genesisUsed = false, healingBanned = false, bleeding = false, extension = false;
	bool obtainingSunblade = true, resistanceBonus = false, summonShitcom = false, buffed = false, antiDeath = false, specialForce = false, fighter = false, anhquoc = false;
	//enemy speciality
	bool challengeMode = false, predatorMode = false, divine = false, welcome = false, solo = false, standBy = false, combat = false, firstStrike = false, floating = false;
	//rune def
	bool reincarnation = false, cooperSeal = false, autoProtect = false;
	//rune offe
	bool insult = false, deathmatch = false, exploit = false;
	//standard attribute
	int attackDmg, abilityPower, armor, magicRes, range, omniVamp, mana, baseAD = 0, baseAP = 0, baseAR = 0, baseMR = 0, critUp = 0, ARpen = 0, MRpen = 0;
	short turn = 0;
	long health, maxHealth;
	//player speciality
	int sunBlade = 0, shield = 0, b, fructure = 0, autoDestruct = 0, adrenaile = 0, defBoost = 0;
	//enemy speciality
	int possessTalent = 0, possessTalent2 = 0, poisoned = 0, spiritMark = 0, fragile = 0, shockwave = 1, taunt = 0, stack = 0;

	unsigned long long damageDealt = 0, healingDone = 0;
};

void printPlayerInfo(Entities* soldier)
{
	std::cout << "\n" "\nGetting info:\n" "\n";
	setColor(LI_YELLOW);
	std::cout << "Class: " << soldier->role;
	setColor(WHITE);
	std::cout << "\nNation: " << soldier->nation;
	setColor(CIRNO);
	std::cout << "\nRoles: " << soldier->tags;
	setColor(LI_GREEN);
	std::cout << "\nHealth: " << soldier->health;
	setColor(RED);
	std::cout << "\nAttack damage: " << soldier->attackDmg;
	setColor(PURPLE);
	std::cout << "\nAbility power: " << soldier->abilityPower;
	setColor(BO_RED);
	std::cout << "\nLife steal: " << soldier->omniVamp << "%";
	setColor(DA_YELLOW);
	std::cout << "\nArmor: " << soldier->armor;
	setColor(LI_CIRNO);
	std::cout << "\nMagic resist: " << soldier->magicRes;
	setColor(LI_WHITE);
	std::cout << "\n\nTalent      >> ";
	setColor(WHITE);
	std::cout << soldier->talent;
	setColor(LI_WHITE);
	std::cout << "\nFirst skill >> ";
	setColor(WHITE);
	std::cout << soldier->spell_1;
	setColor(LI_WHITE);
	std::cout << "\nLast skill  >> ";
	setColor(WHITE);
	std::cout << soldier->spell_2 << std::endl;
	system("pause");
}

void printEnemyInfo(Entities* enemy)
{
	if (enemy->role == "blank")
	{
		std::cout << "Invalid target!\n";
		return;
	}
	std::cout << "\nYour enemy is: ";
	setColor(LI_YELLOW);
	std::cout << enemy->role;
	setColor(WHITE);
	std::cout << "\nDescription: ";
	std::cout << enemy->trait;
	std::cout << "\nBasic stats:";
	setColor(LI_GREEN);
	std::cout << "\nHealth: ";
	std::cout << enemy->health;
	setColor(RED);
	std::cout << "\nAttack damage: ";
	std::cout << enemy->attackDmg;
	setColor(PURPLE);
	std::cout << "\nAbility power: ";
	std::cout << enemy->abilityPower;
	setColor(DA_YELLOW);
	std::cout << "\nArmor: " << enemy->armor;
	setColor(LI_CIRNO);
	std::cout << "\nMagic resist: " << enemy->magicRes << "\n";
	setColor(WHITE);
}

void printHealthBar(Entities* target, int colour)
{
	if (target->role == "blank") return;
	if (target->range == 101 || target->range == 150) colour = 12;
	if (target->health > target->maxHealth) target->health = target->maxHealth;
	else if (target->health < 0)
	{
		target->health = 0;
		target->fragile = 0;
		target->bleeding = false;
		target->poisoned = false;
		target->spiritMark = 0;
	}
	setColor(colour);
	std::cout << '\n' << target->role << "'s health: ";
	std::cout << target->health << '\n';
	int playerMissingHealth = target->maxHealth - target->health, player2percentHealth = target->maxHealth * 2 / 100;
	int playerMissingBar = playerMissingHealth / player2percentHealth;
	int percentHP = target->health * 100 / target->maxHealth;
	//Print player health bar
	printf("[");
	if (target->health > 0 && target->health != target->maxHealth) {
		for (int i = 0; i < 50 - playerMissingBar; i++) printf("=");
		for (int i = 0; i < playerMissingBar; i++) printf(" ");
	}
	else {
		for (int i = 0; i < 50; i++) { target->health == 0 ? printf(" ") : printf("="); }
	}
	printf("]   ");
	std::cout << percentHP << " %";
	if (target->health > 0)
	{
		if (target->shield > 0)
		{
			setColor(2);
			percentHP == 100 ? printf("   Current 'Shield': ") : percentHP >= 10 ? printf("    Current 'Shield': ") : printf("     Current 'Shield': ");
			std::cout << target->shield << "  ";
		}
		if (target->combat)
		{
			setColor(14);
			percentHP == 100 ? printf("   Current Shockwaves: ") : percentHP >= 10 ? printf("    Current Shockwaves: ") : printf("     Current Shockwaves: ");
			std::cout << target->shockwave << "  ";
		}
		if (target->specialForce)
		{
			setColor(CIRNO);
			percentHP == 100 ? printf("   Reflecting  ") : percentHP >= 10 ? printf("    Reflecting  ") : printf("     Reflecting  ");
		}
		if (target->adrenaile)
		{
			setColor(14);
			percentHP == 100 ? printf("   ATK-up  ") : percentHP >= 10 ? printf("    ATK-up  ") : printf("     ATK-up  ");
		}
		if (target->standBy)
		{
			setColor(8);
			percentHP == 100 ? printf("   Stand-by  ") : percentHP >= 10 ? printf("    Stand-by  ") : printf("     Stand-by  ");
		}
		if (target->taunt)
		{
			setColor(6);
			target->standBy ? printf("  Taunted  ") : (percentHP == 100 ? printf("   Taunted  ") : percentHP >= 10 ? printf("    Taunted  ") : printf("     Taunted  "));
		}
		if (target->bleeding)
		{
			setColor(12);
			target->standBy || target->taunt > 0 ? printf("  Bleeding  ") : (percentHP == 100 ? printf("   Bleeding  ") : percentHP >= 10 ? printf("    Bleeding  ") : printf("     Bleeding  "));
		}
		if (target->poisoned)
		{
			setColor(13);
			target->adrenaile > 0 ? printf("  Poisoning  ") : (percentHP == 100 ? printf("   Poisoning  ") : percentHP >= 10 ? printf("    Poisoning  ") : printf("     Poisoning  "));
		}
		if (target->fragile)
		{
			setColor(11);
			target->adrenaile > 0 || target->poisoned ? printf("  Fragile  ") : (percentHP == 100 ? printf("   Fragile  ") : percentHP >= 10 ? printf("    Fragile  ") : printf("     Fragile  "));
		}
		if (target->spiritMark)
		{
			setColor(5);
			target->adrenaile > 0 || target->poisoned || target->fragile > 0 ? printf("  Marked: ") : (percentHP == 100 ? printf("   Marked: ") : percentHP >= 10 ? printf("    Marked: ") : printf("     Marked: "));
			target->spiritMark >= 2 ? std::cout << target->spiritMark << " turns left until the mark activates" : std::cout << "activates in the next turn";
		}
	}
	printf("\n\n");
	setColor(7);
}

