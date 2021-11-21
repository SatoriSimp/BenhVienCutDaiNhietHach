#include<iostream>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#pragma comment(lib, "winmm.lib")

HANDLE h = GetStdHandle(((DWORD)-11));

#define color(n) SetConsoleTextAttribute(h, n);

class Entities
{
public:
	std::string role, trait, talent, spell_1, spell_2;
	//attribute
	bool isPlayer, isEnemy, isNeutral;
	//player speciality
	bool emergencyOn = false, readytoDodge = false, genesisUsed = false, healingBanned = false, bleeding = false, song = false;
	bool obtainingSunblade = true, resistanceBonus = false, summonShitcom = false, buffed = false, antiDeath = false, specialForce = false, fighter = false, anhquoc = false;
	//enemy speciality
	bool spiritMark = false, challengeMode = false, predatorMode = false, divine = false, welcome = false, hypnotized = false;
	//rune def
	bool reincarnation = false, cooperSeal = false, autoProtect = false;
	//rune offe
	bool insult = false, deathmatch = false, exploit = false;
	//standard attribute
	int health, attackDmg, abilityPower, armor, magicRes, range, omniVamp, mana, maxHealth, baseAD = 0, baseAP = 0, baseAR = 0, baseMR = 0, critUp = 0, ARpen = 0, MRpen = 0;
	//player speciality
	int sunBlade = 0, shield = 0, b, fructure = 0, autoDestruct = 0, adrenaile = 0, defBoost = 0;
	//enemy speciality
	int possessTalent = 0, possessTalent2 = 0, poisoned = 0, SpiritMark = 0, fragile = 0, solo = false;
};

void retardInput()
{
	std::cout << "\nBruh wtf are you doing?\n\n";
}

Entities createSoldier() {
	srand(time(NULL));
	std::string randomChar = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b' };

	std::cout << "\nChoose unit's role:\n1. Fighter: Slow & steady\n2. Defender: Have increased HP and Resistances by sacrificing their own damage\n";
	std::cout << "3. Maskman: High attack damage, easier to obtain a critical strike and has extended range, but somewhat squishy\n4. Caster: Capable of dealing decent amount of magic damage, regardless of target's armor\n";
	std::cout << "5. Specialist: Decent stats and less likely to be attacked\n6. Anh Quoc: Recommend for whoever wishes to test their luck\n7. Minh Phan: Destroy the battlefield with his own weight";
	std::cout << "\n8. Bao Duong: For people who has no brain and prefers using normal attacks\n9. Phong Vinh: ROCC SOLID\nA. Luu Bao: Uses quantity to destroy quality\nB. Supporter: Provides decent healing and utility\nR: Random character\n";
	std::cout << "Your choice: ";

	Entities soldier;

	char choice;
	std::cin >> choice;
	if (choice == 'R' || choice == 'r')
	{
		int randomSelect = rand() % (randomChar.length() - 1 + 1) + 1;
		choice = randomChar[randomSelect - 1];
	}

	int hp = 1, ad = 1, ap = 0, ar = 1, mr = 1, rng = 0, vamp = 0, mageForce = 0;

	switch (choice)
	{
	case '1':
		std::cout << "You chose Fighter class!";
		soldier.role = "Fighter";
		hp = 2570;       ad = 225;
		ar = 110;        mr = 60;
		rng = 1;
		soldier.talent = "Increasing Danger: Gain bonus damage and lethality base on battle's duration";
		soldier.spell_1 = "Juggernaunt: Enhance the weapon and deals physic damage equal 150% AD + 200% bonus AD + 35% target's HP, ignore 50% armor (can not crit)";
		soldier.spell_2 = "Unshakable Solidarity: Reduced 90% damage taken this turn and decreases target's armor by 3 + 5%. Then attack with 50% AD";
		break;
	case '2':
		std::cout << "You chose Defender class!";
		soldier.role = "Defender";
		hp = 3333;      ad = 100;
		ar = 160;       mr = 130;
		rng = 2;        ap = 0;
		soldier.talent = "Spiky: Whenever got attacked, reflects 20 (+ 30% armor) magic damage to the attacker";
		soldier.spell_1 = "Reinforcement: Immediately restore 200 HP, then permanently gains 15 armor and 15 magic resist";
		soldier.spell_2 = "Rock Solid: Deals (20% max health + 100% armor + 100% magic resist + 25% target's missing health) physic damage";
		break;
	case '3':
		std::cout << "You chose Maskman class!";
		soldier.role = "Maskman";
		hp = 1750;      ad = 530;      vamp = 10;
		ar = 60;        mr = 40;       soldier.critUp = 35;
		rng = 3;         ap = 0;
		soldier.talent = "Ranged Supremacy: Crit chance increases to 50% and gains 10% life steal (capped at 50%).\n               Cut Down (Unique): Deals increased damage (up to 100%) against target with greater max health than this unit";
		soldier.spell_1 = "Final Tatic: Next attack instead deals 180% damage and guarantee a crit. Heal yourself for 50 + 25% damage dealt";
		soldier.spell_2 = "Blood Rage: Permanently gain 50 AD and 10% life steal, then attack with 100% AD";
		break;
	case '4':
		std::cout << "You chose Caster class!";
		soldier.role = "Caster";
		hp = 1925;      ad = 20;       mageForce = 1;
		ap = 520;       ar = 50;
		mr = 30 + 70;   rng = 4;
		soldier.talent = "Quick Charge (Unique): Normal attacks instead recover 2 mana, this unit also gains 1 bonus mana at the start of battle (which is 4)";
		soldier.spell_1 = "Volcano: Consume all mana, then gain 300 ability power and attacks an enemy with 200% AP. Damage type change to 'True', each mana spent increases damage output by 30 + 15% (can critical for 200% damage)";
		soldier.spell_2 = "Solo - Genesis: Doesn't attack this round, resistances drop to 0 and take extra 100% damage, but prevents HP from falling below 1. After this skill ends, gains 6 + 1 mana per 75 damage taken. Can only activate once throughout the battle\n               Teamfight - Meteorite: Deals 230% AP magic damage to all enemies, damage output is calculated based on the enemy with LEAST magic resist. This damage can not be blocked nor grazed, and can not trigger other effects";
		break;
	case '5':
		std::cout << "You chose Specialist class!";
		soldier.role = "Specialist";
		hp = 2222;     ad = 200;      soldier.emergencyOn = true;
		ap = 0;        ar = 80;
		mr = 80;       rng = 5;
		soldier.talent = "Camouflage (Unique): 20% to dodge the attack, instead take 0 damage. Or 30% to graze it, take half of damage";
		soldier.spell_1 = "Reflection: Convert 30% current HP as true damage. Then gains 'Specialist force' in the next turn: Damage taken reduced to 0, and heals for 70% damage you're supposed to take";
		soldier.spell_2 = "Emergency Recuperation: Once in the battle, when Hp drops to 0, restores (1000 health + 100% damage taken) HP, 3 mana and dodge the next attack (Automatically activated)";
		break;
	case '6':
		std::cout << "You chose Super Idol!";
		soldier.role = "Anh Quoc";
		hp = 1888;      ad = 333;
		ap = 0;         ar = 66;
		mr = 44;        rng = 6;
		soldier.talent = "Legend of Tohno: Normal attack receives one of these following buff: Cannot be dodged, deals 200% damage and ignore target's armor, restore 15% max health (can crit for 30% HP) or recover 1 bonus mana.";
		soldier.spell_1 = "Serious Mode: Immediately deals 600% AD physic damage and 600% AD magic damage to enemy.\nThis skill has 60% chance to fail, instead deals to self 30% max HP. Every 5% missing health increases success chance by 5%.";
		soldier.spell_2 = "Tactical Defend: Gains 20% damage reduction next turn, then attacks with 100% AD.\nIf having below 50% HP, the damage reduction increases by a random amount, up to 100%.";
		break;
	case '7':
		std::cout << "You chose Minh Phan!";
		soldier.role = "Minh Phan Dong";
		hp = 2750;      ad = 0;        soldier.healingBanned = true;
		ap = 250;       ar = 140;
		mr = 120;       rng = 7;
		soldier.talent = "Meat Shield: This unit take 20% less damage from all sources\n               Nitro User Supremacy (Unique): When this unit is on the battlefield, all non-friendly healing effects will be neutralized.";
		soldier.spell_1 = "Body Slam: Aggressively charges forward, deals 250 + 150% AP magic damage. Against target with 'Bleeding' status, damage increased to 750 + 450% AP";
		soldier.spell_2 = "Haemorrhage: Affects the enemy with 'Bleeding', 'Bleeding' enemy have their magic resist reduced by 60 + 20% and causes the next source of damage deals an additional 20% HP magic damage.";
		break;
	case '8':
		std::cout << "You chose Bao Duong!";
		soldier.role = "Duong Lee";
		hp = 2150;      ad = 296;
		ap = 0;         ar = 102;
		mr = 78;        rng = 8;
		soldier.talent = "Sword Rain: After every turn, receives 1 Sun Blade, stores up to 4. Every existing Sun Blade increases crit chance by 7%.\nWhenever this unit uses a basic attack, attacks an additional time with each Sun Blade owns";
		soldier.spell_2 = "Five Signs of the Dying Deva: Multiplies current Sun Blade by 5, then attack enemy with 20% armor penetration. After this skill ends, removes all Sun Blades and forbids this unit from obtaining Sun Blade this turn";
		soldier.spell_1 = "Menacing Slash: Immediately generates 1 Sun Blade, then auto attack the enemy.\n If this unit already reached maxium Sun Blades, briefly gains 30% omni vamp and deals additional magic damage equals 5% max health each strike";
		break;
	case '9':
		std::cout << "You chose Phong Vinh!";
		soldier.role = "Phong Vinh";
		hp = 2611;      ad = 178;       soldier.shield = 2;
		ap = 0;         ar = 130;       soldier.summonShitcom = true;
		mr = 110;       rng = 9;
		soldier.talent = "Rock Dealer: Starts the battle with 2 'Shield' and gains 1 'Shield' every 4 turns, each shield can block 1 instance of damage.\n               When a shield breaks, restores 20% max health.\n               Range is an Advantage (Unique): Gains bonus attack damage bases on current health's difference betweens this unit and their opponent (Only the highest effect of this type is applied)";
		soldier.spell_1 = "Crag Splitter: 'Bind' the target this turn, then deals 444% AD physic damage and restores 6% max health\n(Targets with 'Bind' can not dodge nor graze incoming attack).";
		soldier.spell_2 = "Summon - Shitcom: This unit summons their best tactical equipment to block damage. Shitcom has 2000 health, 200 armor and 0 magic resist.\n               Overheat: Shitcom continously deals 75 true damage to all enemies. When its health drops to 0, explodes and deal 1200 true damage.\n               (Summoning Shitcom doesn't cost mana, but can only activate once)";
		break;
	case 'A': case 'a':
		std::cout << "You chose Luu Bao!";
		soldier.role = "Luu Bao";
		hp = 1980;      ad = 65;        soldier.fructure = 3;
		ap = 280;       ar = 80;
		mr = 95;        rng = 10;
		soldier.talent = "Mechanical Egineer: Can rapidly manufactures and commands 'Machine' in combat (up to 3).\n               Machine: Costs 1 structure point to deploy and will attack enemy everyturn using their chainsaw (starts with 3 and gains 1 point every 5 turns). Has 1500 HP, 270 attack damage, 90 armor, 1 magic resist and more likely to be attacked.\n               Sneak Shot: Whenever a friendly unit uses their first skill, all Machines attack the target one additional time\n               Emergency Repair: When there is atleast 1 'Machine', normal attack instead heals the machine with least HP for 100% AP";
		soldier.spell_1 = "Chainsaw Extension Module: Commands all 'Machine' to attack the enemy, each deals 300% ATK + 4% max HP physic damage. When there're more than 2 'Machine', all 'Machine' attack with 50% armor penetration";
		soldier.spell_2 = "Upstream Circuit Breaker: All 'Machine' HP +100%, Resistances +200, ATK +170%. After 2 turns, automatically retreat from battle.";
		break;
	case 'B': case 'b':
		std::cout << "You chose Supporter!";
		soldier.role = "Supporter";
		hp = 1250;      ad = 0;
		ap = 250;       ar = 50;
		mr = 50;        rng = 11;
		soldier.talent = "Skill Aura - Support: In teamfight mode, attack instead restores HP of ally equals 100% AP and grants to them 1 mana, self is less likely to be attacked. In solo mode, all skills are locked and can not be used";
		soldier.spell_2 = "Enkephalin: Ignores 'Grievous Wound', immediately recovers HP of all allies by 200 + 100% AP and grants to them 1 mana. One targeted ally is bonus healed for 200 + 50% AP";
		soldier.spell_1 = "Adrenaline: Attacks an ally for 1000 physic damage. Afterwards, grants to them 100% AD and 100% AP, lasts 2 turn";
		break;
		/*
	case 'C': case 'c':
		std::cout << "You chose The Singer!";
		soldier.role = "The Singer";
		hp = 1580;      ad = 20;	soldier.song = true;
		ap = 265;       ar = 65;
		mr = 80;        rng = 12;
		soldier.talent  = "Encore: When this unit finishes their turn, has 30% chance to obtain another turn.";
		soldier.spell_1 = "Duetto: Deals 200 + 150% magic damage to the target and applies 20% 'Fragile' in 2 turns. If this ability is used more than 2 times in a round: Starting from the second use, mana cost is reduced to 0. (Target with 'Fragile' has to take more damage)";
		soldier.spell_2 = "Song of the night Sparrow (can only activate once): Resurrects all fallen enemies, restores 100% of their HP and applies 'Hypnotize' to them. 'Hypnotized' enemies will lose all of their traits, gradually lose HP over time and instead attack their allies.";
		break;
		*/
	default:
		std::cout << "You chose Luu Bao the Corrupting Brain!";
		soldier.role = "Luu Bao the Corrupting Brain";
		soldier.talent = "Ruler of the Galaxy: Luu Bao is the strongest being in the history.\nDue to that, his stats must be reduced to 1 to ensure the balance.";
		soldier.spell_1 = "Unstoppable Force: Luu Bao is already too strong, so there's no need to provide him any skill";
		soldier.spell_2 = "Reincarnation: Consumes all mana to heal for 1 HP. His maxium health also increased by 1!";
		break;
	}

	soldier.health = hp;            soldier.attackDmg = ad;         soldier.abilityPower = ap;
	soldier.armor = ar;             soldier.magicRes = mr;          soldier.range = rng;
	soldier.baseAR = ar;            soldier.baseMR = mr;			soldier.baseAP = soldier.abilityPower;
	soldier.omniVamp = vamp;        soldier.mana = 3 + mageForce;   soldier.genesisUsed = false;
	soldier.isPlayer = true;        soldier.isEnemy = false;        soldier.isNeutral = false;
	soldier.maxHealth = soldier.health;         soldier.baseAD = soldier.attackDmg;
	std::cout << "\n" "\nBasic stats:\n" "\n";
	color(14);
	std::cout << "Class: " << soldier.role;
	color(10);
	std::cout << "\nHealth: " << soldier.health;
	color(12);
	std::cout << "\nAttack damage: " << soldier.attackDmg;
	color(5);
	std::cout << "\nAbility power: " << soldier.abilityPower;
	color(4);
	std::cout << "\nLife steal: " << soldier.omniVamp << "%";
	color(6);
	std::cout << "\nArmor: " << soldier.armor;
	color(11);
	std::cout << "\nMagic resist: " << soldier.magicRes;
	color(15);
	std::cout << "\n\nTalent      >> ";
	color(7);
	std::cout << soldier.talent;
	color(15);
	std::cout << "\nFirst skill >> ";
	color(7);
	std::cout << soldier.spell_1;
	color(15);
	std::cout << "\nLast skill  >> ";
	color(7);
	std::cout << soldier.spell_2 << std::endl;
	system("pause");

	return soldier;
}

void printPlayerInfo(Entities* soldier)
{
	std::cout << "\n" "\nGetting info:\n" "\n";
	color(14);
	std::cout << "Class: " << soldier->role;
	color(10);
	std::cout << "\nHealth: " << soldier->health;
	color(12);
	std::cout << "\nAttack damage: " << soldier->attackDmg;
	color(5);
	std::cout << "\nAbility power: " << soldier->abilityPower;
	color(4);
	std::cout << "\nLife steal: " << soldier->omniVamp << "%";
	color(6);
	std::cout << "\nArmor: " << soldier->armor;
	color(11);
	std::cout << "\nMagic resist: " << soldier->magicRes;
	color(15);
	std::cout << "\n\nTalent      >> ";
	color(7);
	std::cout << soldier->talent;
	color(15);
	std::cout << "\nFirst skill >> ";
	color(7);
	std::cout << soldier->spell_1;
	color(15);
	std::cout << "\nLast skill  >> ";
	color(7);
	std::cout << soldier->spell_2 << std::endl;
	system("pause");
}

void printEnemyInfo(Entities* enemy)
{
	std::cout << "\nYour enemy is: ";
	color(14);
	std::cout << enemy->role;
	color(7);
	std::cout << "\nTrait: ";
	std::cout << enemy->trait;
	std::cout << "\nBasic stats:";
	color(10);
	std::cout << "\nHealth: ";
	std::cout << enemy->health;
	color(12);
	std::cout << "\nAttack damage: ";
	std::cout << enemy->attackDmg;
	color(13);
	std::cout << "\nAbility power: ";
	std::cout << enemy->abilityPower;
	color(6);
	std::cout << "\nArmor: ";
	std::cout << enemy->armor;
	color(11);
	std::cout << "\nMagic resist: ";
	std::cout << enemy->magicRes << std::endl;
	color(7);
}

Entities createBlankTarget()
{
	Entities b;
	b.role = "blank";
	b.health = 0;   b.maxHealth = 0;
	b.armor = 0;    b.magicRes = 0;
	b.attackDmg = 0;    b.abilityPower = 0;     b.omniVamp = 0;
	b.isPlayer = false;     b.isNeutral = true;     b.isEnemy = false;
	return b;
}

Entities createGoblinA() {
	srand(time(NULL));
	Entities goblin;
	goblin.attackDmg = rand() % (150 - 110 + 1) + 110;      goblin.abilityPower = 0;
	goblin.armor = rand() % (30 - 20 + 1) + 20;             goblin.magicRes = goblin.armor - 15;
	goblin.omniVamp = 0;
	goblin.isEnemy = true;      goblin.isPlayer = false;    goblin.isNeutral = false;
	int randomSlect = rand() % (15 - 1 + 1) + 1;

	switch (randomSlect)
	{
	case 1: case 2: case 3:
		goblin.trait = "Common species, can be seen really oftens. A single goblin is weak and easy to take down.\nHowever, goblins usually come with group, making them more dangerous and cause serious harm!";
		goblin.role = "Common goblin";
		goblin.health = rand() % (1600 - 500 + 1) + 500;
		goblin.range = 50;
		break;
	case 4: case 5: case 6:
		goblin.role = "Goblin hob";
		goblin.trait = "A more dangerous version of standard goblin. They are stronger and much harder to kill! Proceed with caution.";
		goblin.attackDmg += rand() % (70 - 50 + 1) + 50;
		goblin.health = rand() % (3000 - 1500 + 1) + 1500;
		goblin.armor += 10;
		goblin.range = 51;
	case 7: case 8: case 9:
		goblin.role = "Goblin shaman";
		goblin.trait = "They are slightly smarter than a normal goblin, capable of casting spell to deal magic damage.";
		goblin.health = rand() % (2100 - 1000 + 1) + 1000;
		goblin.abilityPower = 250;      goblin.magicRes += 50;
		goblin.range = 52;
		break;
	case 10: case 11: case 12:
		goblin.role = "Goblin champion";
		goblin.trait = "An extremely dangerous form of goblin. They have been trained through much of battles, their strength and health are outstanding. Avoid fighting them as much as possible!";
		goblin.attackDmg += rand() % (200 - 140 + 1) + 140;
		goblin.armor += 70;             goblin.magicRes += 40;
		goblin.health = rand() % (5500 - 4000 + 1) + 4000;
		goblin.range = 53;
		break;
	default:
		goblin.role = "Senior goblin shaman";
		goblin.trait = "A more dangerous form of goblin shaman, they can use heavy-magic to deal serious wound and ignore 20% target's magic resist";
		goblin.abilityPower = 500;      goblin.magicRes += 100;
		goblin.health = rand() % (4000 - 3000 + 1) + 3000;
		goblin.range = 54;
		break;
	}
	goblin.maxHealth = goblin.health;
	printEnemyInfo(&goblin);
	return goblin;
}

Entities createShitCom()
{
	Entities pc;
	pc.role = "Shitcom";
	pc.health = 2000;       pc.maxHealth = pc.health;
	pc.armor = 200;         pc.magicRes = 1;
	pc.abilityPower = 0;    pc.omniVamp = 0;
	pc.range = 91;          pc.attackDmg = 0;
	pc.isNeutral = true;    pc.isPlayer = true;     pc.isEnemy = false;
	return pc;
}

Entities createMachine()
{
	Entities machine;
	machine.role = "Machine";
	machine.health = 1500;    machine.maxHealth = machine.health;
	machine.abilityPower = 0; machine.attackDmg = 270;
	machine.armor = 90;       machine.magicRes = 1;
	machine.range = 92;       machine.omniVamp = 0;
	machine.isEnemy = false;  machine.isPlayer = true;  machine.isNeutral = true;
	return machine;
}

Entities createGoblinChamp() {
	srand(time(NULL));
	Entities goblin;
	goblin.role = "Goblin champion";
	goblin.trait = "An extremely dangerous form of goblin. They have been trained through much of battles, their strength and health are outstanding. Avoid fighting them as much as possible!";
	goblin.health = rand() % (6000 - 4000 + 1) + 4000;
	goblin.attackDmg = 120 + goblin.health * 8 / 100;                   goblin.abilityPower = 0;
	goblin.armor = rand() % (200 - 150 + 1) + 150;                      goblin.magicRes = goblin.armor - 22;
	goblin.isEnemy = true;           goblin.isPlayer = false;           goblin.isNeutral = false;
	goblin.omniVamp = 0;
	goblin.maxHealth = goblin.health;
	goblin.range = 53;
	printEnemyInfo(&goblin);
	return goblin;
}

Entities createSeniorShaman() {
	srand(time(NULL));
	Entities goblin;
	goblin.role = "Senior goblin shaman";
	goblin.trait = "A more dangerous form of goblin shaman, they can use heavy-magic to deal serious wound and ignore target's magic resist\nTalent: Gains 20% magic penetration";
	goblin.attackDmg = 100;                             goblin.omniVamp = 0;
	goblin.armor = rand() % (100 - 50 + 1) + 50;        goblin.magicRes = 100 + goblin.armor * 4 / 3;
	goblin.abilityPower = 300 + goblin.magicRes;        goblin.health = rand() % (4000 - 3000 + 1) + 3000;
	goblin.isEnemy = true;      goblin.isPlayer = false;        goblin.isNeutral = false;
	goblin.maxHealth = goblin.health;
	goblin.range = 54;
	printEnemyInfo(&goblin);
	return goblin;
}

Entities createZombieOrc() {
	srand(time(NULL));
	Entities orc;
	orc.role = "Zombified Orc";
	orc.trait = "Rotten kind of life-form. Has massive strength and resistance, capable of self-healing bases on damage dealt. However, they gradually lose HP and resistances over time.\nTalent: Attack ignores 40% armor and heals themself for 60% damage dealt, but loses 5% max HP and 20% current resistances every turn\n";
	orc.health = rand() % (12000 - 9000 + 1) + 9000; orc.omniVamp = 60;
	orc.attackDmg = rand() % (800 - 600 + 1) + 600;  orc.magicRes = 222;
	orc.armor = 300;                                 orc.abilityPower = 0;
	orc.isEnemy = true;      orc.isPlayer = false;        orc.isNeutral = false;
	orc.maxHealth = orc.health;
	orc.range = 55;
	printEnemyInfo(&orc);
	return orc;
}

Entities createExplosiveSlug()
{
	Entities slug;
	slug.role = "Explosive Slug";
	slug.trait = "A completely normal slug. What could possibly go wrong?\nCracked Shield: When this unit has more than 50% HP, greatly increases armor and magic resist. When this unit has below 50% health, greatly increases attack damage. Upon death, causes an explosion that deals 400 + 20% target's HP true damage and ignores Shields.\n";
	slug.attackDmg = rand() % (200 - 150 + 1) + 150;    slug.omniVamp = 0;
	slug.armor = rand() % (1100 - 1000 + 1) + 1000;     slug.magicRes = slug.armor * 95 / 100;
	slug.abilityPower = 0;        slug.health = rand() % (8000 - 7000 + 1) + 7000;
	slug.isEnemy = true;          slug.isPlayer = false;        slug.isNeutral = false;
	slug.resistanceBonus = true;
	slug.maxHealth = slug.health;
	slug.range = 57;
	printEnemyInfo(&slug);
	return slug;
}

Entities createSneaker()
{
	srand(time(NULL));
	Entities dwarft;
	dwarft.role = "Senior Drawft";
	dwarft.trait = "A tiny, sneaky form of being. A normal drawft is usually weak and easy to be taken down, but this one knows how to exploit their enemy's weaknesses and blindspots, making them much harder to deal with\nTalent: Attack deals extra damage bases on target's missing health. Upon taking damage, has a chance to dodge or graze it!";
	dwarft.health = rand() % (5000 - 4000 + 1) + 4000;  dwarft.omniVamp = 0;
	dwarft.attackDmg = rand() % (300 - 200 + 1) + 200;  dwarft.magicRes = 65;
	dwarft.armor = 110;                                 dwarft.abilityPower = 0;
	dwarft.isEnemy = true;      dwarft.isPlayer = false;        dwarft.isNeutral = false;
	dwarft.maxHealth = dwarft.health;
	dwarft.range = 56;
	printEnemyInfo(&dwarft);
	return dwarft;
}

Entities createPhantom()
{
	srand(time(NULL));
	Entities phantom;
	phantom.role = "Phantom";
	phantom.trait = "Unknown creature, has unstable shape and capable of performing their former target's traits\nTrauma: Before the battle, this unit chooses one random playable character and possesses their talent (can not possess talent with 'Unique').";
	phantom.health = rand() % (7000 - 6000 + 1) + 6000; phantom.omniVamp = 0;
	phantom.attackDmg = rand() % (400 - 350 + 1) + 350; phantom.armor = rand() % (280 - 250 + 1) + 250;
	phantom.magicRes = phantom.armor / 2 + 5;           phantom.abilityPower = 0;
	phantom.isEnemy = true;     phantom.isNeutral = false;      phantom.isPlayer = false;
	phantom.maxHealth = phantom.health;
	phantom.range = 58;

	printEnemyInfo(&phantom);
	return phantom;
}

Entities createSpirit()
{
	srand(time(NULL));
	Entities spirit;
	spirit.role = "Vengeful Spirit";
	spirit.trait = "Deals art damage, weak against magic.\nDescription: A spirit, a soul, a phantasm,... Whatever it's called, this thing is definitely not pleasant at all.\nEmotional Absorption: At the start of battle and after every 5 turns, this unit marks their opponent, attack against marked target deals 18% max health's magic damage. After 3 turns, the mark activates, steals away 6 mana from its targets and restores 888 HP. Target that has less than required mana will take 9999 true damage.";
	spirit.health = rand() % (7900 - 7000 + 1) + 7000;        spirit.omniVamp = 0;
	spirit.attackDmg = 0;                                     spirit.armor = rand() % (300 - 250 + 1) + 250;
	spirit.magicRes = spirit.armor / 4 + 5;                   spirit.abilityPower = rand() % (300 - 250 + 1) + 250;
	spirit.isEnemy = true;     spirit.isNeutral = false;      spirit.isPlayer = false;
	spirit.maxHealth = spirit.health;
	spirit.range = 59;

	printEnemyInfo(&spirit);
	return spirit;
}

Entities createChimera()
{
	srand(time(NULL));
	Entities chimera;
	chimera.role = "Chimera";
	chimera.trait = "A monstrous creature with parts from multiple animals, capable of switching form during battle\n\nTwilight: This unit has 2 unique form - 'Predator' and 'Divine Beast' (always starts the battle in 'Divine Beast' form) - and swaps between them every 5 turns.\n\nPredator: Has increased armor, gains 373 physic damage and extra critical chance, critical attack instead deals 250% damage (400% against target with less than 50% health). Before swapping form, 'Bind' their target then attacks with 1000 damage, ignores 60% armor and heals for 200% damage dealt\n\nDivine Beast: Attack damage drops to 0, gains 535 ability power and increased magic resist, attack against target with higher than 50% health deals an additional 16% current health damage. Before swapping form, removes all good effects from their opponent.\n";
	chimera.health = rand() % (20000 - 18000 + 1) + 18000;       chimera.omniVamp = 0;
	chimera.attackDmg = 0;                                       chimera.armor = rand() % (200 - 150 + 1) + 150;
	chimera.magicRes = chimera.armor + 400;                      chimera.abilityPower = 535;
	chimera.isEnemy = true;     chimera.isNeutral = false;       chimera.isPlayer = false;
	chimera.maxHealth = chimera.health;                          chimera.divine = true;
	chimera.range = 100;

	printEnemyInfo(&chimera);
	return chimera;
}

Entities createAplha()
{
	srand(time(NULL));
	Entities alpha;
	alpha.role = "Henry Fat";
	alpha.trait = "Doesn't attack 'Poisoned' targets\nWarm Welcome: Immediately deals 30% max health true damage and ignores 'Shield' at the start of the battle to all friendly units\nNeurotoxin: Attack poisons non-summoned target, deals 200-500 magic damage bases on missing health and applies 60% 'Grievous Wound' every turn in 3 turns. Targets that are not poisoned instead take 400% damage\nSpace Out: When there isn't any target to attack, Resistances +250% and restores 500 HP each turn.";
	alpha.health = rand() % (7777 - 6666 + 1) + 6666;          alpha.omniVamp = 0;
	alpha.attackDmg = 320;                                     alpha.armor = rand() % (200 - 150 + 1) + 150;
	alpha.magicRes = alpha.armor * 6 / 10;                     alpha.abilityPower = 0;
	alpha.isEnemy = true;     alpha.isNeutral = false;         alpha.isPlayer = false;
	alpha.maxHealth = alpha.health;                            alpha.welcome = true;
	alpha.baseAR = alpha.armor, alpha.baseMR = alpha.magicRes;
	alpha.range = 60;

	printEnemyInfo(&alpha);
	return alpha;
}

Entities createSinger()
{
	srand(time(NULL));
	Entities singer;
	singer.role = "The Singer";
	singer.trait = "Some kind of undetectable lifeform, their voice are just pure trauma.\nDuetto: Attack applies 20% 'Fragile' in 2 turns (Target with 'Fragile' has to take more damage, bonus damage is calculated based on the exact amount).\nEncore: When a 'Fragile' effect runs out, has 50% chance for it to reset the duration.\nSoloist: When this unit is the only enemy alive, ATK +20%, Resisitance -70% and attack turns into AoE damage\nSong of the night Sparrow: Upon death, resurrects all fallen enemies (excluding self), restores 100% of their HP and applies 'Fragile' to all friendly units in 10 turns.";
	singer.song = true;
	singer.health = rand() % (14000 - 13000 + 1) + 13000;      singer.omniVamp = 0;
	singer.attackDmg = 30;                                     singer.armor = rand() % (700 - 550 + 1) + 550;
	singer.magicRes = singer.armor * 12 / 10;                  singer.abilityPower = 150;
	singer.isEnemy = true;     singer.isNeutral = false;       singer.isPlayer = false;
	singer.maxHealth = singer.health;						   singer.baseAP = 150;
	singer.baseAR = singer.armor;							   singer.baseMR = singer.magicRes;
	singer.range = 61;
	printEnemyInfo(&singer);
	return singer;
}

Entities createShinigami()
{
	srand(time(NULL));
	Entities singer;
	singer.role = "Reaper";
	singer.trait = "What? How?\nScythe: Attack prioritizes non-summoned target with least HP, ignores standard precedence\nReap: Every 3 turns, performs an AoE attack that deals 150% magic damage. The damage scales with 100% target's missing health but won't be greater than 450% ATK. If this attack takes down atleast 1 non-summon target, this unit can immediately recast it";
	singer.health = rand() % (10000 - 9000 + 1) + 9000;        singer.omniVamp = 0;
	singer.attackDmg = 366;                                    singer.armor = rand() % (400 - 350 + 1) + 350;
	singer.magicRes = singer.armor * 7 / 10;                   singer.abilityPower = 0;
	singer.isEnemy = true;     singer.isNeutral = false;       singer.isPlayer = false;
	singer.maxHealth = singer.health;						   singer.baseAP = 0;
	singer.baseAR = singer.armor;							   singer.baseMR = singer.magicRes;
	singer.range = 62;
	printEnemyInfo(&singer);
	return singer;
}

Entities shitcom = createBlankTarget(), machineA = createBlankTarget(), machineB = createBlankTarget(), machineC = createBlankTarget();

void printHealthBar(Entities* target, int colour)
{
	if (target->health > target->maxHealth) target->health = target->maxHealth;
	else if (target->health < 0)
	{
		target->health = 0;
		target->fragile = 0;
		target->bleeding = false;
		target->poisoned = false;
		target->SpiritMark = 0;
	}
	color(colour);
	std::cout << '\n' << target->role << "'s health: ";
	std::cout << target->health << '\n';
	int playerMissingHealth = target->maxHealth - target->health, player2percentHealth = target->maxHealth * 2 / 100;
	int playerMissingBar = playerMissingHealth / player2percentHealth;
	//Print player health bar
	printf("[");
	for (int i = 0; i < 50 - playerMissingBar; i++) printf("=");
	for (int i = 0; i < playerMissingBar; i++) printf(" ");
	printf("]   ");
	std::cout << target->health * 100 / target->maxHealth << " %";
	if (target->bleeding)
	{
		color(12);
		printf("	Bleeding");
	}
	if (target->poisoned)
	{
		color(13);
		printf("	Poisoning");
	}
	if (target->SpiritMark > 0)
	{
		color(5);
		std::cout << "	Marked: ";
		target->SpiritMark >= 2 ? std::cout << target->SpiritMark << " turns left until the mark activates" : std::cout << "activates in the next turn";
	}
	if (target->fragile > 0)
	{
		color(11);
		printf("	Fragile");
	}
	printf("\n\n");
	color(7);
}

int damageOutput(int armor, int magicResistance, int physicDmg, int magicDmg) {
	int physicTaken = (armor >= 0) ? physicDmg * 100 / (100 + armor) : physicDmg * 2 - 100 / (100 - armor);
	int magicTaken = (magicResistance >= 0) ? magicDmg * 100 / (100 + magicResistance) : magicDmg * 2 - 100 / (100 - magicResistance);
	return physicTaken + magicTaken;
}

int lifeSteal(int damage, int vamp) { return damage * vamp / 100; }

void dealingDamage(Entities* attacker, Entities* gotAttacked, bool specialForce, bool fighterWill, int playerHealth, int enemyMaxHealth, bool painSupress, bool anhquocSupremacy) {
	int damageTaken = !painSupress ? damageOutput((*gotAttacked).armor * (100 - attacker->ARpen) / 100, (*gotAttacked).magicRes * (100 - attacker->ARpen) / 100, (*attacker).attackDmg, (*attacker).abilityPower) : damageOutput(0, 0, (*attacker).attackDmg, (*attacker).abilityPower);

	//Maskman talent
	if (attacker->range == 3)
	{
		int healthDifference = gotAttacked->maxHealth - attacker->maxHealth, dif_20PercentHP = attacker->maxHealth / 5;
		int bonusDmg = healthDifference / dif_20PercentHP;
		bonusDmg > 10 ? bonusDmg = 10 : bonusDmg;
		damageTaken += damageTaken * (bonusDmg * 10) / 100;
	}

	//Enemy normal attack effect
	if ((*attacker).role == "Senior goblin shaman") damageTaken = damageOutput((*gotAttacked).armor, (*gotAttacked).magicRes * 8 / 10, (*attacker).attackDmg, (*attacker).abilityPower);
	else if ((*attacker).role == "Zombified Orc") damageTaken = damageOutput((*gotAttacked).armor * 6 / 10, 0, (*attacker).attackDmg, 0);
	else if (attacker->role == "Senior Drawft")
	{
		int bonusDamage;
		bonusDamage = !attacker->challengeMode ? (gotAttacked->maxHealth - gotAttacked->health) * 3 / 10 : (gotAttacked->maxHealth - gotAttacked->health) * 45 / 100;
		damageTaken += damageOutput(gotAttacked->armor, 0, bonusDamage, 0);
	}
	else if (attacker->role == "Vengeful Spirit" && (gotAttacked->spiritMark || gotAttacked->SpiritMark > 0)) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, gotAttacked->maxHealth * 18 / 100);
	else if (attacker->role == "Chimera")
	{
		if (attacker->challengeMode) damageTaken = attacker->attackDmg + attacker->abilityPower;
		if (attacker->divine)
		{
			!attacker->challengeMode ? damageTaken += damageOutput(0, gotAttacked->magicRes, 0, gotAttacked->health * 16 / 100) : damageTaken += gotAttacked->health * 16 / 100;
		}
	}
	else if (attacker->range == 60)
	{
		!(gotAttacked->isNeutral) ? std::cout << gotAttacked->role << " is poisoned in the next 3 turns!\n", gotAttacked->poisoned = 3 : damageTaken *= 4;
	}
	else if (attacker->range == 61) gotAttacked->fragile = 2;

	int criticalStrike = rand() % (100 - 0 + 1) + 1;
	attacker->possessTalent == 8 || attacker->possessTalent2 == 8 ? criticalStrike = 100 : criticalStrike = criticalStrike;

	if (!gotAttacked->specialForce)
	{
		//Crit attack
		if (criticalStrike <= 15 + attacker->critUp && attacker->range != 8)
		{
			color(12);
			printf("CRITICAL STRIKE! The damage dealt is doubled up!\n");
			color(7);
			attacker->predatorMode ? (gotAttacked->health >= gotAttacked->maxHealth / 2 ? damageTaken *= 25 / 10 : damageTaken *= 4) : damageTaken *= 2;
			if (attacker->exploit) damageTaken += 135 + damageTaken / 10;
		}

		//Bao Duong's attack system
		if (attacker->range == 8 || attacker->possessTalent == 8 || attacker->possessTalent2 == 8)
		{
			int damagePerAtk = damageOutput(gotAttacked->armor, 0, attacker->attackDmg, 0), critTime = 0, dodgeTime = 0, grazeTime = 0;
			damageTaken = 0;
			int attackTimes = 1 + attacker->sunBlade;
			while (attackTimes > 0) {
				int critical = rand() % (100 - 1 + 1) + 1;
				attacker->possessTalent == 3 || attacker->possessTalent2 == 3 ? critical -= 20 : critical = critical;

				int evasion;
				gotAttacked->range == 56 || gotAttacked->role == "Specialist" ? evasion = rand() % (100 - 1 + 1) + 1 : evasion = 100;

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

			if (attacker->omniVamp >= 30) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, enemyMaxHealth / 4);
			if (attacker->exploit) damageTaken += 135 + damagePerAtk / 5;

			if (attacker->isPlayer) std::cout << attacker->role << " stroke the enemy ";
			else
			{
				color(14);  std::cout << attacker->role;
				color(7);   std::cout << " stroke " << gotAttacked->role << "'s ass ";
			}
			color(12);
			attacker->sunBlade != 0 ? std::cout << 1 + attacker->sunBlade << " times" : std::cout << "1 time";
			color(7);
			std::cout << " and did ";
			color(12);
			std::cout << critTime << " critical attacks!\n";
			color(7);

			if (gotAttacked->role == "Senior Drawft" || gotAttacked->role == "Specialist")
			{
				color(14);
				std::cout << gotAttacked->role;
				color(7);
				std::cout << " dodged ";
				color(14); std::cout << attacker->role;
				color(7); std::cout << "'s attacks ";

				color(10);
				dodgeTime > 1 ? std::cout << dodgeTime << " times" : std::cout << dodgeTime << " time";
				color(7);
				std::cout << " and grazed ";
				color(10);
				grazeTime > 1 ? std::cout << grazeTime << " times\n" : std::cout << grazeTime << " time!\n";
				color(7);
			}
		}

		if (attacker->cooperSeal) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, attacker->maxHealth * 8 / 100);
		else if (attacker->insult && gotAttacked->health <= gotAttacked->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
		else if (attacker->deathmatch)
		{
			int bonusDmg = 0;
			attacker->health <= attacker->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
			gotAttacked->health >= gotAttacked->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
			damageTaken += bonusDmg;
		}
		if (gotAttacked->fragile > 0) damageTaken = damageTaken * 12 / 10;
		//Specialist & Senior Drawft dodge system
		if (((*gotAttacked).role == "Specialist" || gotAttacked->role == "Senior Drawft") && attacker->range != 8)
		{
			int evasion = rand() % (100 - 1 + 1) + 1;
			if (gotAttacked->role == "Senior Drawft") evasion = rand() % (70 - 1 + 1) + 1;
			gotAttacked->challengeMode ? evasion -= 15 : evasion;

			if (evasion <= 20 || (*gotAttacked).readytoDodge)
			{
				damageTaken = 0;
				color(10);
				gotAttacked->isPlayer ? std::cout << "DODGED! You take no damage this round! " : std::cout << "DODGED! " << gotAttacked->role << " takes no damage this round! ";
				color(7);
				(*gotAttacked).readytoDodge = false;
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				gotAttacked->isPlayer ? std::cout << "GRAZED! You take half damage this round! " : std::cout << "GRAZED! " << gotAttacked->role << " takes half damage this round! ";
				color(7);
			}
		}

		//if ((*attacker).role == "Zombified Orc") healing += playerHealth * 7 / 100;

		//Caster's skill 2
		(painSupress || gotAttacked->antiDeath) ? damageTaken *= 2 : damageTaken;

		//Anh Quoc's talent
		if (attacker->role == "Anh Quoc" || attacker->possessTalent == 6 || attacker->possessTalent2 == 6)
		{
			int randomBuff = rand() % (3 - 1 + 1) + 1;
			switch (randomBuff)
			{
			case 1:
				if (criticalStrike <= 15) printf("But this unit damage is already massive so it won't be increased! ");
				color(13);
				if (attacker->isPlayer) std::cout << attacker->role << "'s attack deals true damage and can not be dodged nor grazed!\n";
				else
				{
					color(14);
					std::cout << attacker->role;
					color(13);
					std::cout << " deals increased true damage!\n";
				}
				color(7);
				attacker->isPlayer ? damageTaken = damageOutput(0, 0, (*attacker).attackDmg * 2, 0) : damageTaken = damageOutput(0, 0, (*attacker).attackDmg * 15 / 10, 0);
				break;
			case 2:
				if (criticalStrike > 15)
				{
					if (attacker->isPlayer) std::cout << attacker->role << " are healed for ";
					else {
						color(14);
						std::cout << attacker->role;
						color(7);
						std::cout << " is healed for ";
					}
					color(2);
					int CopyHeal = attacker->maxHealth * 7 / 100;
					if (attacker->isPlayer) CopyHeal = attacker->maxHealth * 15 / 100;
					if (attacker->poisoned) CopyHeal = CopyHeal * 4 / 10;
					if (attacker->healingBanned) CopyHeal = 0;
					std::cout << CopyHeal << " HP!\n";
					color(7);
					(*attacker).health + CopyHeal > attacker->maxHealth ? (*attacker).health = attacker->maxHealth : (*attacker).health += CopyHeal;
				}
				else
				{
					if (attacker->isPlayer) std::cout << attacker->role << " is double-healed for ";
					else {
						color(14);
						std::cout << attacker->role;
						color(7);
						std::cout << " is double-healed for ";
					}
					color(2);
					int CopyHeal = attacker->maxHealth * 15 / 100;
					if (attacker->isPlayer) CopyHeal = attacker->maxHealth * 3 / 10;
					if (attacker->poisoned) CopyHeal = CopyHeal * 4 / 10;
					if (attacker->healingBanned) CopyHeal = 0;
					std::cout << CopyHeal << " HP!\n";
					color(7);

					(*attacker).health + CopyHeal > attacker->maxHealth ? (*attacker).health = attacker->maxHealth : (*attacker).health += CopyHeal;
				}
				break;
			case 3:
				if (attacker->isPlayer)
				{
					color(11);
					std::cout << attacker->role << " receives 1 bonus mana!\n";
					color(7);
					(*attacker).mana++;
				}
				else {
					color(14);
					std::cout << attacker->role;
					color(11);
					std::cout << " took 1 mana from " << gotAttacked->role << "\n";
					gotAttacked->mana--;
					gotAttacked->mana < 0 ? gotAttacked->mana = 0 : gotAttacked->mana;
					color(7);
				}
				break;
			}
		}

		// Anh Quoc's skill 2
		if ((anhquocSupremacy || gotAttacked->anhquoc) && (*attacker).isEnemy)
		{
			int weirdFlex = rand() % (8 - 3 + 1) + 3;
			if ((*gotAttacked).health > (1888 / 2))
			{
				damageTaken = damageTaken * 8 / 10;
			}
			else
			{
				damageTaken = damageTaken * (8 - weirdFlex) / 10;
				std::cout << gotAttacked->role << "'s damage taken this turn is reduced by ";
				color(12);
				std::cout << (10 - 8 + weirdFlex) * 10 << "%\n";
				color(7);
			}
			gotAttacked->anhquoc = false;
		}

		//Phong Vinh's shield
		if (gotAttacked->shield > 0)
		{
			damageTaken = 0;
			int restore = gotAttacked->isPlayer ? gotAttacked->maxHealth / 5 : gotAttacked->maxHealth / 10;
			if (gotAttacked->poisoned > 0) restore = restore * 4 / 10;
			if (gotAttacked->healingBanned) restore = 0;
			std::cout << "This damage is blocked, " << gotAttacked->role << " restores ";
			color(2);
			std::cout << restore << " health!\n";
			color(7);
			gotAttacked->health + restore <= gotAttacked->maxHealth ? gotAttacked->health += restore : gotAttacked->health = gotAttacked->maxHealth;
			gotAttacked->shield--;
		}

		//Life steal
		int healing = lifeSteal(damageTaken, (*attacker).omniVamp);
		if (attacker->poisoned > 0) healing = healing * 4 / 10;

		//Minh phan's bleeding effect & talent
		if ((*gotAttacked).bleeding)
		{
			if (attacker->range == 7) damageTaken = damageOutput(gotAttacked->armor, gotAttacked->magicRes * 8 / 10 - 60, attacker->attackDmg, attacker->abilityPower);
			int bleedingDmg = damageOutput(0, ((*gotAttacked).magicRes * 8 / 10) - 60, 0, gotAttacked->maxHealth * 2 / 10);

			if (attacker->insult && gotAttacked->health <= gotAttacked->maxHealth * 4 / 10) bleedingDmg = bleedingDmg * 112 / 100;
			else if (attacker->deathmatch)
			{
				int bonusDmg = 0;
				attacker->health <= attacker->maxHealth * 4 / 10 ? bonusDmg += bleedingDmg * 7 / 100 : bonusDmg = bonusDmg;
				gotAttacked->health >= gotAttacked->maxHealth * 6 / 10 ? bonusDmg += bleedingDmg * 8 / 100 : bonusDmg = bonusDmg;
				bleedingDmg += bonusDmg;
			}
			if (gotAttacked->fragile > 0) bleedingDmg = bleedingDmg * 12 / 10;
			(*gotAttacked).health -= bleedingDmg;
			std::cout << "This attack triggered ";
			color(12);
			std::cout << "'Bleeding' ";
			color(7);
			std::cout << "effect, deals additional ";
			color(5);
			std::cout << bleedingDmg << " damage!\n";
			color(7);
			(*gotAttacked).bleeding = false;
		}

		if (gotAttacked->range == 7 || gotAttacked->possessTalent == 7 || gotAttacked->possessTalent2 == 7) damageTaken = damageTaken * 8 / 10;

		//Fighter's skill 2
		if (fighterWill || gotAttacked->fighter)
		{
			(*attacker).isEnemy ? damageTaken /= 10 : damageTaken /= 2;
		}

		//Damage dealt
		(*gotAttacked).health -= damageTaken;

		//Minh Phan's passive
		if ((*attacker).healingBanned) healing = 0;

		//If the healing went beyond unit's max health, it's set to their max health
		if ((*attacker).isPlayer) (*attacker).health = ((*attacker).health + healing > attacker->maxHealth ? attacker->maxHealth : (*attacker).health + healing);
		else (*attacker).health = (*attacker).health + healing > enemyMaxHealth ? enemyMaxHealth : (*attacker).health + healing;

		//Send damage output
		if ((*attacker).isPlayer && (attacker->attackDmg > 0 || attacker->abilityPower > 0))
		{
			std::cout << attacker->role << " dealt to ";
			color(14);
			std::cout << (*gotAttacked).role << " ";
			color(7);
			if (attacker->abilityPower > attacker->attackDmg) { color(5); }
			else { color(12); }
			std::cout << damageTaken << " damage!\n";
			color(7);
		}
		else if (damageTaken > 0)
		{
			color(14);
			std::cout << (*attacker).role;
			color(7);
			std::cout << " dealt to " << gotAttacked->role << ' ';
			if (attacker->abilityPower > attacker->attackDmg) { color(5); }
			else { color(12); }
			std::cout << damageTaken << " damage!\n";
			color(7);
		}

		//Caster skill 2 activation
		if (painSupress || gotAttacked->antiDeath)
		{
			(*gotAttacked).health < 1 ? (*gotAttacked).health = 1 : (*gotAttacked).health;
			int manaBuff = 6 + damageTaken / 75;
			std::cout << "Due to the damage taken, you receive ";
			color(11);
			std::cout << manaBuff << " mana!\n";
			color(7);
			(*gotAttacked).mana += manaBuff;
			(*gotAttacked).genesisUsed = true;
		}

		//Specialist skill 2 activation
		if ((*gotAttacked).emergencyOn && (*gotAttacked).health < 0)
		{
			(*gotAttacked).health = 1000;
			(*gotAttacked).emergencyOn = false;
			color(11);
			if (gotAttacked->isPlayer)
			{
				std::cout << "The switch is on! You are healed for ";
				color(2);
				std::cout << 1000 + damageTaken << " HP ";
				color(11);
				std::cout << "and gains ";
				color(14);
				std::cout << "100% dodge";
				color(11);
				std::cout << " in the next turn!\n";
			}
			else
			{
				std::cout << "The switch is broken! " << gotAttacked->role << " is healed for ";
				color(2);
				std::cout << 1000 + damageTaken << " HP!\n";
			}
			color(7);
			(*gotAttacked).health += damageTaken;
			(*gotAttacked).mana += 3;
			(*gotAttacked).readytoDodge = true;
		}

		//Healing notification
		if ((*attacker).isPlayer && (*attacker).omniVamp > 0)
		{
			std::cout << "You also healed for ";
			color(2);
			std::cout << healing << " HP!\n";
			color(7);
		}
		else if (!(*attacker).isPlayer && (*attacker).omniVamp > 0)
		{
			color(14);
			std::cout << (*attacker).role;
			color(7);
			std::cout << " also healed themself for ";
			color(2);
			std::cout << healing << " HP!\n";
			color(7);
		}

		//Defender's talent
		if (gotAttacked->role == "Defender" || gotAttacked->possessTalent == 2 || gotAttacked->possessTalent2 == 2)
		{
			int damageReflect = damageOutput(0, (*attacker).magicRes, 0, 20 + (*gotAttacked).armor * 3 / 10);
			if (gotAttacked->cooperSeal) damageTaken += damageOutput(0, attacker->magicRes, 0, gotAttacked->maxHealth * 8 / 100);
			else if (gotAttacked->insult && attacker->health <= attacker->maxHealth * 4 / 10) damageReflect = damageReflect * 112 / 100;
			else if (gotAttacked->deathmatch)
			{
				int bonusDmg = 0;
				gotAttacked->health <= gotAttacked->maxHealth * 4 / 10 ? bonusDmg += damageReflect * 7 / 100 : bonusDmg = bonusDmg;
				attacker->health >= attacker->maxHealth * 6 / 10 ? bonusDmg += damageReflect * 8 / 100 : bonusDmg = bonusDmg;
				damageReflect += bonusDmg;
			}

			(*attacker).health -= damageReflect;
			std::cout << gotAttacked->role << " reflected to " << (*attacker).role << " ";
			color(5);
			std::cout << damageReflect << " damage!\n";
			color(7);
		}
	}
	//Specialist's skill 1
	else
	{
		if (criticalStrike <= 15 || (criticalStrike <= 50 && attacker->predatorMode))
		{
			attacker->predatorMode && (gotAttacked->health < gotAttacked->maxHealth / 2) ? damageTaken *= 4 : attacker->predatorMode ? damageTaken *= 25 / 10 : damageTaken *= 2;
			color(10);
			std::cout << "CRITICAL STRIKE! " << gotAttacked->role << "'s healed as twice as normal, how cheat!\n";
			color(7);
		}
		damageTaken = damageTaken * 7 / 10;
		if (gotAttacked->poisoned > 0) damageTaken = damageTaken * 4 / 10;
		(*gotAttacked).health + damageTaken < gotAttacked->maxHealth ? (*gotAttacked).health += damageTaken : (*gotAttacked).health = gotAttacked->maxHealth;
		std::cout << (*attacker).role << " tried to attack " << gotAttacked->role << ", but their attack has been adsorbed and instead heal ";
		color(2);
		std::cout << damageTaken << " HP!\n";
		color(7);
		gotAttacked->specialForce = false;
	}
}

void useSpell_1(Entities* caster, Entities* target, Entities* machineA, Entities* machineB, Entities* machineC, int maxHP) {
	int damageTaken;
	int mana = (*caster).mana;
	std::cout << caster->role << " used their first spell!\n";
	switch ((*caster).range)
	{
	case 1:
	{
		//Deals bonus physic dmg equal 35% max HP, ignore 50% armor but can not crit
		int bonusDmg = maxHP * 35 / 100, passiveDmg = (*caster).attackDmg - 205;
		damageTaken = damageOutput(((*target).armor * (100 - caster->ARpen) / 100) / 2, (*target).magicRes, bonusDmg + (*caster).attackDmg * 15 / 10 + passiveDmg * 2, 0);

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
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
		std::cout << caster->role << " dealt ";
		color(12);
		std::cout << damageTaken << " damage!\n";
		color(7);
		if (target->bleeding)
		{				
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			std::cout << "\nThis ability also triggered ";
			color(12)
			std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 2:
	{
		//Permanently increase armor and magic res by 15, then restore 200 HP
		caster->baseAR += 15, caster->baseMR += 15;
		caster->armor += 15, caster->magicRes += 15;
		if (caster->poisoned == 0) (*caster).health + 200 < caster->maxHealth ? (*caster).health += 200 : (*caster).health = caster->maxHealth;
		else (*caster).health + 80 < caster->maxHealth ? (*caster).health += 80 : (*caster).health = caster->maxHealth;
		std::cout << caster->role << "'s HP has been restored, resistances ";
		color(1);
		std::cout << "increased by 15!\n";
		color(7);
		break;
	}
	case 3:
	{
		//Next attack deals 180% damage and guarantee a crit, ignore 25% armor. Then briefly gains 25% lifesteal
		damageTaken = damageOutput((target->armor * (100 - caster->ARpen) / 100) * 3 / 4, 0, ((*caster).attackDmg * 18 / 10) * 2, 0);

		//Maskman talent: Every 20% difference max health increases damage output by 10% (cap at 1000%)
		if (caster->range == 3)
		{
			int healthDifference = target->maxHealth - caster->maxHealth, dif_20PercentHP = caster->maxHealth / 5;
			int bonusDmg = healthDifference / dif_20PercentHP;
			bonusDmg > 10 ? bonusDmg = 10 : bonusDmg;
			damageTaken += damageTaken * (bonusDmg * 10) / 100;
		}

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
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		int heal = damageTaken / 4 + 50 + lifeSteal(damageTaken, (*caster).omniVamp);
		if (caster->poisoned > 0) heal = heal * 4 / 10;

		(*target).health -= damageTaken;
		(*caster).health += heal;

		caster->health > caster->maxHealth ? caster->health = caster->maxHealth : caster->health;
		std::cout << caster->role << " dealt ";
		color(12);
		std::cout << damageTaken << " damage ";
		color(7);
		std::cout << " and healed for ";
		color(2);
		std::cout << heal << " HP!\n";
		color(7);
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 4:
	{
		/*
		Consume all Mana to use
		Converts 200% physic damage to ability power, attacks deals true damage. Each mana spent increases damage by 30 + 20%
		(can crit for 200% damage each)
		*/
		caster->mana += 3;
		damageTaken = damageOutput(0, 0, (*caster).attackDmg, ((*caster).abilityPower + 300) * 2);
		int Sto = damageTaken;
		while (caster->mana > 0)
		{
			damageTaken += 30 + Sto * 15 / 100;
			if ((rand() % (100 - 1 + 1) + 1) <= 25) damageTaken += 30 + Sto * 15 / 100;
			caster->mana--;
		}

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
			int evasion = rand() % (100 - 1 + 1) + 1;
			if (evasion <= 20)
			{
				damageTaken = 0;
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
		std::cout << caster->role << " consumed all mana to deal ";
		color(11);
		std::cout << damageTaken << " true damage!\n";
		color(7);
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 5:
	{
		/*
		Sacrifice 25% current HP to deal the exact amount of true damage (no lower than 100)
		For exchange, gain 100% evasion and heal for 70% damage taken next turn
		*/
		int healthSac = (*caster).health * 3 / 10;
		(*caster).health -= healthSac;
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
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
		std::cout << "\n" << caster->role << " sacrificed ";
		color(2);
		std::cout << healthSac << " health ";
		color(7);
		std::cout << "to deal ";
		color(11);
		std::cout << damageTaken << " damage!\n";
		color(7);
		caster->specialForce = true;
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			target->health -= damageTaken;
			target->bleeding = false;
		}
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
					color(10);
					std::cout << "\nDODGED! " << target->role << " takes no damage this round! ";
					color(7);
				}
				else if (evasion <= 50)
				{
					damageTaken /= 2;
					color(10);
					std::cout << "\nGRAZED! " << target->role << " takes half damage this round! ";
					color(7);
				}
			}
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}

			(*target).health -= damageTaken;
			color(4);
			std::cout << "\nPOWER OVERWHELMED!";
			color(7);
			std::cout << caster->role << " dealt ";
			color(11);
			std::cout << damageTaken << " damage";
			color(7);
			printf(" total!\n");
			if (target->bleeding)
			{				
				int reduceRes = 60 + (*target).magicRes / 5;
				damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
				std::cout << "\nThis ability also triggered ";
				color(12)
				std::cout << "'Bleeding'";
				color(7);
				std::cout << " effect, deals an additional ";
				color(5);
				std::cout << damageTaken << " damage!\n";
				color(7);
				target->health -= damageTaken;
				target->bleeding = false;
			}
		}
		else
		{
			(*caster).health -= 1888 * 3 / 10;
			color(4);
			std::cout << "\nPOWER OVERLOADED!";
			color(7);
			std::cout << caster->role << " instead took ";
			color(12);
			std::cout << 1888 * 3 / 10 << " damage!\n";
			color(7);
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
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			bodySlam *= 3;
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			target->health -= damageTaken;
			target->bleeding = false;
		}

		damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, bodySlam);
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
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		std::cout << damage;
		color(5);
		std::cout << damageTaken << " damage!\n";
		color(7);
		(*target).health -= damageTaken;
		break;
	}
	case 8:
	{
		if (caster->sunBlade < 4)
		{
			color(11);
			std::cout << caster->role << " obtained 1 Sun Blade!\n";
			color(7);
			caster->sunBlade++;
			dealingDamage(&(*caster), &(*target), 0, 0, caster->health, 0, 0, 0);
		}
		else
		{
			color(7);
			std::cout << caster->role << " gained ";
			color(4);
			std::cout << "30% omni vamp";
			color(7);
			std::cout << " this round and each attack deals ";
			color(5);
			printf("additional magic damage!\n");
			color(7);
			caster->omniVamp = 30;
			dealingDamage(&(*caster), &(*target), 0, 0, caster->health, maxHP, 0, 0);
			caster->omniVamp = 0;
		}
		break;
	}
	case 9:
	{
		damageTaken = damageOutput(target->armor * (100 - caster->ARpen) / 100, 0, caster->attackDmg * 444 / 100, 0);
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
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		
		int restore = caster->maxHealth * 6 / 100;
		if (caster->poisoned > 0) restore = restore * 4 / 10;
		std::cout << caster->role << " brandish their hammer, deals ";
		color(12);
		std::cout << damageTaken << " damage ";
		color(7);
		std::cout << "and restore ";
		color(2);
		std::cout << restore << " health!\n";
		color(7);
		caster->health + restore > caster->maxHealth ? caster->health = caster->maxHealth : caster->health += restore;
		target->health -= damageTaken;
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 10:
	{
		int machineDmg = 0;
		if (machineA->health > 0) machineDmg += machineA->attackDmg * 3 + target->maxHealth * 2 / 50;
		if (machineB->health > 0) machineDmg += machineB->attackDmg * 3 + target->maxHealth * 2 / 50;
		if (machineC->health > 0) machineDmg += machineC->attackDmg * 3 + target->maxHealth * 2 / 50;

		machineDmg >= machineA->attackDmg * 6 + target->maxHealth * 2 / 25 ? damageTaken = damageOutput((target->armor * (100 - caster->ARpen) / 100) / 2, 0, machineDmg, 0) : damageTaken = damageOutput(target->armor * (100 - caster->ARpen) / 100, 0, machineDmg, 0);
		machineDmg >= machineA->attackDmg * 6 + target->maxHealth * 2 / 25 ? std::cout << "RESONANT! All machines attacked! Deals " : std::cout << "Machine attacked! Deals ";
		
		if (target->fragile > 0) damageTaken = damageTaken * 12 / 10;

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		color(12);
		std::cout << damageTaken << " damage!\n";
		color(7);
		target->health -= damageTaken;
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);

			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 12:
	{
		damageTaken = damageOutput(0, target->magicRes * (100 - caster->ARpen) / 100, 0, 200 + caster->abilityPower * 15 / 10);
		target->fragile = 2;
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
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
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
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);

			target->health -= damageTaken;
			target->bleeding = false;
		}
		
		color(14);
		std::cout << caster->role, color(7);
		std::cout << " dealt ", color(5);
		std::cout << damageTaken << " damage ", color(7);
		std::cout << "to ", color(14);
		std::cout << target->role, color(7);
		std::cout << " and affects ", color(11);
		std::cout << "'Fragile'", color(7);
		std::cout << " to them!\n";
		target->health -= damageTaken;
		break;
	}
	default:
		std::cout << "\nLuu Bao breathes, dealing an uncounttable amount of damage!\n";
		break;
	}
	if ((*target).emergencyOn && (*target).health < 0)
	{
		color(5);
		std::cout << "The switch is broken! " << target->role << " is healed for ";
		color(2);
		std::cout << 1000 + damageTaken << " HP!\n";
		color(7);
		(*target).health += damageTaken;
		(*target).mana += 3;
		(*target).readytoDodge = true;
		target->emergencyOn = false;
	}
}

void useSpell_2(Entities* caster, Entities* target, int maxHP, int mana, int playerHealth) {
	int damageTaken;
	int missingHealth = maxHP - (*target).health;
	switch ((*caster).range)
	{
	case 1:
	{
		caster->fighter = true;
		int armorReduction = (*target).armor / 20 + 3;
		(*target).armor -= armorReduction;
		color(1);
		std::cout << caster->role << " stay focused, destroy target's armor by ";
		color(6);
		std::cout << armorReduction;
		color(1);
		std::cout << " and gain ";
		color(14);
		std::cout << "90% damage reduction ";
		color(1);
		std::cout << "this turn!\n";
		color(7);
		dealingDamage(&(*caster), &(*target), false, true, playerHealth, 0, false, 0);
		break;
	}
	case 2:
	{
		int shieldDamage = playerHealth / 5 + (*caster).armor + (*caster).magicRes + missingHealth / 4;

		damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, shieldDamage);
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
				color(10);
				std::cout << "DODGED! " << target->role << " takes no damage this round! ";
				color(7);
			}
			else if (evasion <= 50)
			{
				damageTaken /= 2;
				color(10);
				std::cout << "GRAZED! " << target->role << " takes half damage this round! ";
				color(7);
			}
		}

		if (target->shield > 0)
		{
			damageTaken = 0;
			int shieldHeal = target->maxHealth / 10;
			if (target->healingBanned) shieldHeal = 0;
			target->shield--;
			std::cout << "This damage is blocked! ", color(14);
			std::cout << target->role, color(7);
			std::cout << " restores ", color(2);
			std::cout << shieldHeal << " health!", color(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
		std::cout << caster->role << " brandished your shield and dealt ";
		color(5);
		std::cout << damageTaken << " damage!\n";
		color(7);
		if (target->bleeding)
		{
			int reduceRes = 60 + (*target).magicRes / 5;
			damageTaken = damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100 - reduceRes, 0, maxHP * 2 / 10);
			if (caster->cooperSeal) damageTaken += damageOutput(0, target->magicRes * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
			else if (caster->insult && target->health <= target->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
			else if (caster->deathmatch)
			{
				int bonusDmg = 0;
				caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
				target->health >= target->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
				damageTaken += bonusDmg;
			}
			if (target->shield > 0)
			{
				damageTaken = 0;
				int shieldHeal = target->maxHealth / 10;
				if (target->healingBanned) shieldHeal = 0;
				target->shield--;
				std::cout << "This damage is blocked! ", color(14);
				std::cout << target->role, color(7);
				std::cout << " restores ", color(2);
				std::cout << shieldHeal << " health!", color(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}
			std::cout << "\nThis ability also triggered ";
			color(12)
				std::cout << "'Bleeding'";
			color(7);
			std::cout << " effect, deals an additional ";
			color(5);
			std::cout << damageTaken << " damage!\n";
			color(7);
			target->health -= damageTaken;
			target->bleeding = false;
		}
		break;
	}
	case 3:
	{
		caster->baseAD += 50, caster->attackDmg += 50;          
		(*caster).omniVamp = (*caster).omniVamp + 10 > 50 ? 50 : (*caster).omniVamp + 10;
		std::cout << caster->role << "'s attack damage is now increased to ";
		color(12);
		std::cout << (*caster).attackDmg;
		color(7);
		std::cout << "\nLife-steal is increased to ";
		color(4);
		std::cout << (*caster).omniVamp << "%\n";
		color(7);
		dealingDamage(&(*caster), &(*target), false, false, playerHealth, 0, false, 0);
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
		printf("This unit doesn't need such of thing, you will use a normal attack instead\n");
		dealingDamage(&(*caster), &(*target), false, false, playerHealth, 0, false, 0);
		break;
	}
	case 6:
	{
		if ((*caster).health > caster->maxHealth / 2)
		{
			color(10);
			std::cout << caster->role << " take 20% less damage this turn, omg so pro!\n";
			color(7);
		}
		dealingDamage(&(*caster), &(*target), false, false, playerHealth, 0, false, true);
		break;
	}
	case 7:
	{
		(*target).bleeding = true;
		std::cout << caster->role << " subtracted enemy's magic resist by ";
		color(11);
		std::cout << 60 + (*target).magicRes / 5 << " and mark them with 'Bleeding'" << std::endl;
		color(7);
		break;
	}
	case 8:
	{
		caster->sunBlade *= 5;
		int maxAR = target->armor;
		target->armor = target->armor * 8 / 10;
		dealingDamage(&(*caster), &(*target), 0, 0, caster->health, 0, 0, 0);
		caster->sunBlade = 0;
		target->armor = maxAR;
		caster->obtainingSunblade = false;
		break;
	}
	case 9:
	{
		color(10);
		std::cout << "Summoned new Shitcom!\n";
		color(7);
		shitcom = createShitCom();
		caster->summonShitcom = false;
		break;
	}
	case 10:
	{
		color(12);
		std::cout << "Destruction mode: All machines has dramatically increased stats, but will be automatically destroyed within 2 turns!\n";
		color(7);
		break;
	}
	default:
		printf("No data given\n");
		break;
	}
	if ((*target).emergencyOn && (*target).health < 0)
	{
		color(5);
		std::cout << "The switch is broken! " << target->role << " is healed for ";
		color(2);
		std::cout << 1000 + damageTaken << " HP!\n";
		color(7);
		(*target).health += damageTaken;
		(*target).emergencyOn = false;
	}
}

void useSpell2_2(Entities* caster, Entities* target1, Entities* target2, Entities* target3)
{
	int baseDamageTaken;
	switch (caster->range)
	{
		case 4:
		{
			color(12);
			std::cout << "Meteorite fall!\n", color(7);
			int leastMR = min(target1->magicRes, min(target2->magicRes, target3->magicRes));
			baseDamageTaken = damageOutput(0, leastMR * (100 - caster->MRpen) / 100, 0, caster->abilityPower * 23 / 10);
			if (target1->health > 0)
			{
				int damageTaken = baseDamageTaken;
				if (caster->cooperSeal) damageTaken += damageOutput(0, leastMR * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
				else if (caster->insult && target1->health <= target1->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
				else if (caster->deathmatch)
				{
					int bonusDmg = 0;
					caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
					target1->health >= target1->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
					damageTaken += bonusDmg;
				}
				target1->health -= damageTaken;
				color(14);
				std::cout << caster->role, color(7);
				std::cout << " dealt to ", color(14);
				std::cout << target1->role, color(5);
				std::cout << " " << damageTaken << " damage!\n", color(7);
			}
			if (target2->health > 0)
			{
				int damageTaken = baseDamageTaken;
				if (caster->cooperSeal) damageTaken += damageOutput(0, leastMR * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
				else if (caster->insult && target2->health <= target2->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
				else if (caster->deathmatch)
				{
					int bonusDmg = 0;
					caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
					target2->health >= target2->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
					damageTaken += bonusDmg;
				}
				target2->health -= damageTaken;
				color(14);
				std::cout << caster->role, color(7);
				std::cout << " dealt to ", color(14);
				std::cout << target2->role, color(5);
				std::cout << " " << damageTaken << " damage!\n", color(7);
			}
			if (target3->health > 0)
			{
				int damageTaken = baseDamageTaken;
				if (caster->cooperSeal) damageTaken += damageOutput(0, leastMR * (100 - caster->MRpen) / 100, 0, caster->maxHealth * 8 / 100);
				else if (caster->insult && target3->health <= target3->maxHealth * 4 / 10) damageTaken = damageTaken * 112 / 100;
				else if (caster->deathmatch)
				{
					int bonusDmg = 0;
					caster->health <= caster->maxHealth * 4 / 10 ? bonusDmg += damageTaken * 7 / 100 : bonusDmg = bonusDmg;
					target3->health >= target3->maxHealth * 6 / 10 ? bonusDmg += damageTaken * 8 / 100 : bonusDmg = bonusDmg;
					damageTaken += bonusDmg;
				}
				target3->health -= damageTaken;
				color(14);
				std::cout << caster->role, color(7);
				std::cout << " dealt to ", color(14);
				std::cout << target3->role, color(5);
				std::cout << " " << damageTaken << " damage!\n", color(7);
			}
			break;
		}
		case 62:
		{
			baseDamageTaken = caster->attackDmg * 15 / 10;
			bool killed = false;
			Entities* target = nullptr;
			for (int i = 0; i < 3; i++)
			{
				i == 0 ? target = target1 : i == 1 ? target = target2 : target = target3;
				if (target->health > 0)
				{
					int damageDeal = damageOutput(0, target->magicRes, 0, baseDamageTaken);
					int missingHP = damageOutput(0, target->magicRes, 0, target->maxHealth - target->health);
					damageDeal + missingHP > damageDeal * 3 ? damageDeal *= 3 : damageDeal += missingHP;
					if (target->fragile) damageDeal = damageDeal * 12 / 10;
					if (target->shield > 0)
					{
						target->shield--;
						damageDeal = 0;
						std::cout << "This damage is blocked! ", color(14); 
						std::cout << target->role, color(7);
						std::cout << " restored ", color(2);
						std::cout << target->maxHealth / 5 << " HP!\n", color(7);
						target->health += target->maxHealth / 5;
					}
					target->health -= damageDeal;
					color(14);
					std::cout << caster->role, color(7);
					std::cout << " dealt to ", color(14);
					std::cout << target->role, color(5);
					std::cout << " " << damageDeal << " damage!\n", color(7);
					if (target->health <= 0 && !target->emergencyOn) killed = true;
				}
			}
			target = nullptr;
			free(target);
			if (killed) useSpell2_2(caster, target1, target2, target3);
			break;
		}
	}
}

void playerChoice(Entities* player, Entities* ally1, Entities* ally2, Entities* enemy1, Entities* enemy2, Entities* enemy3)
{
	srand(time(NULL));

	if (enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0) return;

	int mana1_2 = 3, mana1_1;

	(player->range == 7 || player->range == 6 || player->range == 8 || player->range == 12) ? mana1_1 = 2 : mana1_1 = 3;

	switch (player->range)
	{
	case 1: case 7:
		mana1_2 = 1;
		break;
	case 4: case 3: case 8: case 6: case 2:
		mana1_2 = 3;
		break;
	case 5: case 9: case 10:
		mana1_2 = 0;
		break;
	case 11:
		mana1_2 = 5;
		break;
	}

currentChoice:

	char choice1;
	int choice2;
	std::string sunblade = " ";
	color(14);
	std::cout << "\nChoose " << player->role << " action:", color(7);
	player->range != 4 ? std::cout << "\n1. Normal attack (+1 mana)" : std::cout << "\n1. Normal attack (+2 mana)";
	if (player->range == 8)
	{
		color(14);
		std::cout << "  Current Sunblade: " << player->sunBlade, color(7);
	}
	else if (player->range == 9)
	{
		color(2);
		std::cout << "  Current Shield: " << player->shield, color(7);
	}
	std::cout << "\n2. Use first spell (-" << mana1_1 << " mana)\n3. Use last spell (-" << mana1_2 << " mana)\n4. Check this unit stats\n5. Check specific enemy stats\n";
	if (player->range != 10) std::cout << "Other: Skip this turn (+3 mana)\n";
	else
	{
		color(14);
		std::cout << "6. Deploy machine (-1 structure point)    Current Structure point: " << player->fructure;
		color(7);
		std::cout << "\nOther. Skip this turn (+3 mana)\n";
	}
	color(11);
	std::cout << "\nCurrent mana: " << player->mana, color(7);
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
				while (!choosenEnemy || (choosenEnemy->health <= 0 && !confirmDead))
				{
					int target;
					std::cout << "Choose target:";
					if (enemy1->health > 0) std::cout << "\n1. " << enemy1->role;
					if (enemy2->health > 0) std::cout << "\n2. " << enemy2->role;
					if (enemy3->health > 0) std::cout << "\n3. " << enemy3->role;
					std::cout << "\nYour choice : ";				std::cin >> target;
					target == 1 ? choosenEnemy = enemy1 : target == 2 ? choosenEnemy = enemy2 : choosenEnemy = enemy3;
					if (choosenEnemy->health > 0)
					{
						dealingDamage(player, choosenEnemy, 0, 0, player->maxHealth, choosenEnemy->maxHealth, 0, 0);
						printHealthBar(choosenEnemy, 5);
						if (choosenEnemy->health <= 0) confirmDead = true;
					}
					else std::cout << "This unit is already gone, try choosing another one!\n";
				}
				player->range == 4 ? player->mana += 2 : player->mana++;
				choosenEnemy = nullptr;
				free(choosenEnemy);
			}
			else if (player->range == 10)
			{
				color(14);
				std::cout << player->role;
				color(7);
				std::cout << " healed the machine with least HP for ";
				color(2);
				std::cout << player->abilityPower << " HP!\n";
				color(7);
				if (machineA.health < machineB.health && ((machineA.health < machineC.health && machineC.health > 0) || (machineA.health > machineC.health && machineC.health <= 0)) && machineA.health > 0)
				{
					machineA.health + player->abilityPower > 1500 ? machineA.health = 1500 : machineA.health += player->abilityPower;
				}
				else if (machineB.health < machineA.health && ((machineB.health < machineC.health && machineC.health > 0) || (machineB.health > machineC.health && machineC.health <= 0)) && machineB.health > 0)
				{
					machineB.health + player->abilityPower > 1500 ? machineB.health = 1500 : machineB.health += player->abilityPower;
				}
				else if (machineC.health > 0)
				{
					machineC.health + player->abilityPower > 1500 ? machineC.health = 1500 : machineC.health += player->abilityPower;
				}

				Entities* target = nullptr;
				bool confirmDead = false;
				while (!target || (target->health <= 0 && !confirmDead))
				{
					int targetLock;
					std::cout << "Choose target for machine to attack:";
					if (enemy1->health > 0) std::cout << "\n1. " << enemy1->role;
					if (enemy2->health > 0) std::cout << "\n2. " << enemy2->role;
					if (enemy3->health > 0) std::cout << "\n3. " << enemy3->role;
					std::cout << "\nTarget: ";
					std::cin >> targetLock;
					targetLock == 1 ? target = enemy1 : targetLock == 2 ? target = enemy2 : target = enemy3;
					if (target->health > 0)
					{
						if (machineA.health > 0) dealingDamage(&machineA, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (machineB.health > 0) dealingDamage(&machineB, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (machineC.health > 0) dealingDamage(&machineC, target, 0, 0, player->health, target->maxHealth, 0, 0);
						if (target->health <= 0) confirmDead = true;
					}
					else std::cout << "This unit is already gone, select another!\n";
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
			std::cout << "Choose ally to heal:";
			if (ally1->health > 0) std::cout << "\n1. " << ally1->role;
			if (ally2->health > 0) std::cout << "\n2. " << ally2->role;
			if (player->health > 0) std::cout << "\n3. " << player->role;
			std::cout << "\nYour choice : ";
			std::cin >> targetChoose;
			targetChoose == 1 ? healedTarget = ally1 : targetChoose == 2 ? healedTarget = ally2 : healedTarget = player;
			healedTarget->poisoned > 0 ? healing = healing * 4 / 10 : healing = healing;
			color(2);
			healedTarget->range != 11 ? std::cout << '\n' << player->role << " healed " << healedTarget->role << ' ' : std::cout << player->role << " healed themself for ";
			std::cout << healing << " HP and ", color(6);
			std::cout << "granted to them 1 mana!\n", color(7);
			if (healedTarget->health > 0) healedTarget->health += healing;
			else
			{
				color(12);
				printf("You can not heal the deads, fools!\n"), color(7);
				goto currentChoice;
			}
			if (healedTarget->health > healedTarget->maxHealth) healedTarget->health = healedTarget->maxHealth;
			healedTarget->mana++;
			player->mana++;
			printHealthBar(healedTarget, 2);
			healedTarget = nullptr;
			free(healedTarget);
			printf("\n");
		}
		break;
	case '2':
	{
		if (player->mana >= mana1_1)
		{
			if (player->range != 11)
			{
				player->mana -= mana1_1;
				Entities* targetLock = nullptr;
				bool confirmDeath = false;
				if (player->range != 2)
				{
					while (!targetLock || (targetLock->health <= 0 && !confirmDeath))
					{
						int target;
						std::cout << "Choose target:";
						if (enemy1->health > 0) std::cout << "\n1. " << enemy1->role;
						if (enemy2->health > 0) std::cout << "\n2. " << enemy2->role;
						if (enemy3->health > 0) std::cout << "\n3. " << enemy3->role;
						std::cout << "\nYour choice : ";
						std::cin >> target;
						target == 1 ? targetLock = enemy1 : target == 2 ? targetLock = enemy2 : targetLock = enemy3;
						if (targetLock->health > 0)
						{
							useSpell_1(player, targetLock, &machineA, &machineB, &machineC, targetLock->maxHealth);
							if (machineA.health > 0) dealingDamage(&machineA, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (machineB.health > 0) dealingDamage(&machineB, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (machineC.health > 0) dealingDamage(&machineC, targetLock, 0, 0, player->health, targetLock->maxHealth, 0, 0);
							if (player->range != 5) printHealthBar(targetLock, 5);
							if (targetLock->health <= 0) confirmDeath = true;
						}
						else std::cout << "This target is already gone, choose another one instead!\n\n";
					}
				}
				else
				{
					useSpell_1(player, enemy1, &machineA, &machineB, &machineC, enemy1->maxHealth);
					printHealthBar(player, 2);
				}
				targetLock = nullptr;
				free(targetLock);
			}
			else
			{
				player->mana -= mana1_1;
				Entities* buffed = nullptr;
				bool confirmDeath = false;
				while (!buffed || (buffed->health <= 0 && !confirmDeath))
				{
					int target;
					std::cout << "Choose target:";
					if (ally1->health > 0) std::cout << "\n1. " << ally1->role;
					if (ally2->health > 0) std::cout << "\n2. " << ally2->role;
					if (player->health > 0) std::cout << "\n3. " << player->role;
					std::cout << "\nYour choice : ";
					std::cin >> target;
					target == 1 ? buffed = ally1 : target == 2 ? buffed = ally2 : buffed = player;
					if (buffed->health > 0)
					{
						int drugDamage = damageOutput(buffed->armor, 0, player->abilityPower * 4, 0);
						color(12);
						std::cout << "Drug gained! " << buffed->role << " took " << drugDamage << " damage and has dramatically increased damage!\n";
						color(7);
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
					player->mana -= mana1_2;
					Entities* extraHealed = nullptr;
					int target;
					std::cout << "Choose target:";
					if (ally1->health > 0) std::cout << "\n1. " << ally1->role;
					if (ally2->health > 0) std::cout << "\n2. " << ally2->role;
					if (player->health > 0) std::cout << "\n3. " << player->role;
					std::cout << "\nYour choice : ";
					std::cin >> target;
					target == 1 ? extraHealed = ally1 : target == 2 ? extraHealed = ally2 : extraHealed = player;
					int baseHealing = 200 + player->abilityPower, bonusHealing = 200 + player->abilityPower / 2;
					if (player->autoProtect)
					{
						baseHealing = baseHealing * 115 / 100;
						bonusHealing = bonusHealing * 115 / 100;
					}
					player->health > 0 ? player->health += baseHealing : player->health = 0;
					ally1->health > 0 ? ally1->health += baseHealing, ally1->mana++ : ally1->health = 0;
					ally2->health > 0 ? ally2->health += baseHealing, ally2->mana++ : ally2->health = 0;
					
					extraHealed->health > 0 ? extraHealed->health += bonusHealing : extraHealed->health = 0;
					color(2);
					std::cout << "All allies restored " << baseHealing << " HP!\n" << extraHealed->role << " is healed for " << baseHealing + bonusHealing << " HP!\n";
					color(7);
					printHealthBar(player, 10);
					printHealthBar(ally1, 10);
					printHealthBar(ally2, 10);
					extraHealed = nullptr;
					free(extraHealed);
				}
				else if (player->range == 4)
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
					int target;
					if (player->range != 9)
					{
						std::cout << "Choose target:";
						if (enemy1->health > 0) std::cout << "\n1. " << enemy1->role;
						if (enemy2->health > 0) std::cout << "\n2. " << enemy2->role;
						if (enemy3->health > 0) std::cout << "\n3. " << enemy3->role;
						std::cout << "\nYour choice : ";
						std::cin >> target;
						target == 1 ? targetSpell = enemy1 : target == 2 ? targetSpell = enemy2 : targetSpell = enemy3;
						player->mana -= mana1_2;
						useSpell_2(player, targetSpell, targetSpell->maxHealth, player->mana, player->health);
					}
					else useSpell_2(player, enemy1, enemy1->maxHealth, player->mana, player->health);

					if (player->range == 2 || player->range == 8 || player->range == 1 || player->range == 3) printHealthBar(targetSpell, 5);
					else if (player->range == 10)
					{
						if (machineA.health > 0)
						{
							machineA.autoDestruct = 3;
							machineA.maxHealth *= 2;
							machineA.health *= 2;
							machineA.attackDmg = machineA.attackDmg * 27 / 10;
							machineA.armor += 200, machineA.magicRes += 200;
							dealingDamage(&machineA, targetSpell, 0, 0, player->health, targetSpell->maxHealth, 0, 0);
						}
						if (machineB.health > 0)
						{
							machineB.autoDestruct = 3;
							machineB.maxHealth *= 2;
							machineB.health *= 2;
							machineB.attackDmg = machineB.attackDmg * 27 / 10;
							machineB.armor += 200, machineB.magicRes += 200;
							dealingDamage(&machineB, targetSpell, 0, 0, player->health, targetSpell->maxHealth, 0, 0);
						}
						if (machineC.health > 0)
						{
							machineC.autoDestruct = 3;
							machineC.maxHealth *= 2;
							machineC.health *= 2;
							machineC.attackDmg = machineC.attackDmg * 27 / 10;
							machineC.armor += 200, machineC.magicRes += 200;
							dealingDamage(&machineC, targetSpell, 0, 0, player->health, targetSpell->maxHealth, 0, 0);
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
				std::cout << "Enter number of machines to summon: ";
				int number;
				std::cin >> number;
				number > player->fructure ? number = player->fructure : number;
				for (int i = 1; i <= number; i++) {
					if (player->fructure >= 1) {
						color(10);
						std::cout << "Summoned new Machine!\n";

						if (machineA.health <= 0) machineA = createMachine();
						else if (machineB.health <= 0) machineB = createMachine();
						else if (machineC.health <= 0) machineC = createMachine();
						else
						{
							std::cout << "All machines are being deloyed, summoning broke!\n";
							break;
						}
						color(7);
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
		std::cout << player->role << " skipped this turn and gained 3 mana!\n";
		player->mana += 3;
		break;
	}

	if (player->range == 8 && player->obtainingSunblade && player->sunBlade < 4)
	{
		color(9);
		std::cout << '\n' << player->role << " obtained 1 Sun Blade!\n", color(7);
		player->sunBlade++;
	}
	else if (!player->obtainingSunblade)
	{
		color(9);
		std::cout << '\n' << player->role << " can not obtain any Sun Blade this turn!\n", color(7);
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
}

int minHealth(Entities* player1, Entities* player2, Entities* player3)
{
	if (((player1->health <= player2->health && player2->health > 0) || (player1->health > player2->health && player2->health <= 0)) && ((player1->health <= player3->health && player3->health > 0) || (player1->health > player3->health && player3->health <= 0)) && player1->health > 0) return 1;
	else if (((player2->health <= player1->health && player1->health > 0) || (player2->health > player1->health && player1->health <= 0)) && ((player2->health <= player3->health && player3->health > 0) || (player2->health > player3->health && player3->health <= 0)) && player2->health > 0) return 2;
	else return 3;
}

void battleStart_3v3(Entities* player1, Entities* player2, Entities* player3, Entities* enemy1, Entities* enemy2, Entities* enemy3)
{
	color(14);
	std::cout << "\n|==============================|\n";
	std::cout << "|         BATTLE START!        |\n";
	std::cout << "|==============================|\n\n";
	color(7);
	system("pause");
	srand(time(NULL));
	int turn = 0;
	bool specialForce = false, fighterWill = false, painSupress = false, anhquocSupremacy = false;

	Entities* luubao, * pvinh, * duongLe, * minhphan, *supporter, *fighter, *caster;
	player1->range == 10 ? luubao = player1 : player2->range == 10 ? luubao = player2 : player3->range == 10 ? luubao = player3 : luubao = nullptr;
	player1->range == 8 ? duongLe = player1 : player2->range == 8 ? duongLe = player2 : player3->range == 8 ? duongLe = player3 : duongLe = nullptr;
	player1->range == 9 ? pvinh = player1 : player2->range == 9 ? pvinh = player2 : player3->range == 9 ? pvinh = player3 : pvinh = nullptr;
	player1->range == 7 ? minhphan = player1 : player2->range == 7 ? minhphan = player2 : player3->range == 7 ? minhphan = player3 : minhphan = nullptr;
	player1->range == 11 ? supporter = player1 : player2->range == 11 ? supporter = player2 : player3->range == 11 ? supporter = player3 : supporter = nullptr;
	player1->range == 1 ? fighter = player1 : player2->range == 1 ? fighter = player2 : player3->range == 1 ? fighter = player3 : fighter = nullptr;
	player1->range == 4 ? caster = player1 : player2->range == 4 ? caster = player2 : player3->range == 4 ? caster = player3 : caster = nullptr;

	Entities* slug, * chimera, * phantom, * zombieOrc, * spirit, * henryFat, * singer, * shinigami;
	enemy1->role == "Explosive Slug" ? slug = enemy1 : enemy2->role == "Explosive Slug" ? slug = enemy2 : enemy3->role == "Explosive Slug" ? slug = enemy3 : slug = nullptr;
	enemy1->role == "Chimera" ? chimera = enemy1 : enemy2->role == "Chimera" ? chimera = enemy2 : enemy3->role == "Chimera" ? chimera = enemy3 : chimera = nullptr;
	enemy1->role == "Phantom" ? phantom = enemy1 : enemy2->role == "Phantom" ? phantom = enemy2 : enemy3->role == "Phantom" ? phantom = enemy3 : phantom = nullptr;
	enemy1->role == "Zombified Orc" ? zombieOrc = enemy1 : enemy2->role == "Zombified Orc" ? zombieOrc = enemy2 : enemy3->role == "Zombified Orc" ? zombieOrc = enemy3 : zombieOrc = nullptr;
	enemy1->role == "Vengeful Spirit" ? spirit = enemy1 : enemy2->role == "Vengeful Spirit" ? spirit = enemy2 : enemy3->role == "Vengeful Spirit" ? spirit = enemy3 : spirit = nullptr;
	enemy1->role == "Henry Fat" ? henryFat = enemy1 : enemy2->role == "Henry Fat" ? henryFat = enemy2 : enemy3->role == "Henry Fat" ? henryFat = enemy3 : henryFat = nullptr;
	enemy1->role == "The Singer" ? singer = enemy1 : enemy2->role == "The Singer" ? singer = enemy2 : enemy3->role == "The Singer" ? singer = enemy3 : singer = nullptr;
	enemy1->role == "Reaper" ? shinigami = enemy1 : enemy2->role == "Reaper" ? shinigami = enemy2 : enemy3->role == "Reaper" ? shinigami = enemy3 : shinigami = nullptr;


	if (minhphan)
	{
		color(14);
		printf("\nMinh Phan is now on the battle, no healing shall be allowed!\n");
		color(7);
		enemy1->healingBanned = true, enemy2->healingBanned = true, enemy3->healingBanned = true;
		system("pause");
	}

	Entities* marked = nullptr;

	if (henryFat)
	{
		color(13);
		std::cout << henryFat->role << " took their move and deals to all units 30% max HP true damage!\n", color(7);
		player1->health -= player1->maxHealth * 3 / 10;
		player2->health -= player2->maxHealth * 3 / 10;
		player3->health -= player3->maxHealth * 3 / 10;
	}

	if (singer && singer->challengeMode)
	{
		Entities* buff = nullptr;
		for (int i = 1; i <= 3; i++)
		{
			i == 1 ? buff = enemy1 : i == 2 ? buff = enemy2 : buff = enemy3;
			buff->baseAD = buff->baseAD * 15 / 10 + 100, buff->attackDmg = buff->attackDmg * 15 / 10 + 100;
			buff->baseAP = buff->baseAP * 15 / 10 + 100, buff->abilityPower = buff->abilityPower * 15 / 10;
		}
		buff = nullptr;
		free(buff);
	}

	//Tha battle, overall
	while ((player1->health > 0 || player2->health > 0 || player3->health > 0) && (enemy1->health > 0 || enemy2->health > 0 || enemy3->health > 0))
	{
		int lowestHP = minHealth(player1, player2, player3);
		Entities* gotAtked = lowestHP == 1 ? player1 : lowestHP == 2 ? player2 : player3;

		if (singer && !singer->solo && singer->health > 0 && ((singer == enemy1 && enemy2->health <= 0 && enemy3->health <= 0) || (singer == enemy2 && enemy1->health <= 0 && enemy3->health <= 0) || (singer == enemy3 && enemy1->health <= 0 && enemy2->health <= 0)))
		{
			color(12);
			std::cout << "Soloist: ";
			std::cout << singer->role;
			std::cout << " has increased ATK and attack now deals AoE damage, but significantly reduced resistance\n";
			singer->solo = true;
			singer->baseAP = 100 + singer->baseAP * 12 / 10, singer->abilityPower = singer->baseAP;
			singer->baseAR = singer->baseAR * 3 / 10, singer->baseMR = singer->baseMR * 3 / 10;
			singer->armor = singer->baseAR, singer->magicRes = singer->baseMR;
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
					int poisonBaseDmg = 200 + (((poisoned->maxHealth - poisoned->health) / poisoned->maxHealth) * 100 * 7);
					poisonBaseDmg > 500 ? poisonBaseDmg = 500 : poisonBaseDmg;
					int poisonDmg = damageOutput(0, poisoned->magicRes, 0, poisonBaseDmg);
					if (henryFat->challengeMode)
					{
						poisonDmg = poisonDmg * 25 / 10;
						poisonDmg < 200 ? poisonDmg = 200 : poisonDmg = poisonDmg;
					}
					if (poisoned->fragile > 0) poisonDmg = poisonDmg * 12 / 10;
					color(14);
					std::cout << "Poison triggers! " << poisoned->role << " took " << poisonDmg << " damage!\n", color(7);
					poisoned->health -= poisonDmg;
					poisoned->poisoned--;
					poisonedPlayer++;
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

		if (spirit && spirit->health > 0)
		{
			if (turn == 0 || turn % 5 == 0)
			{
				marked = nullptr;
				while (!marked || marked->health <= 0)
				{
					int toMark = rand() % (3 - 1 + 1) + 1;
					toMark == 1 ? marked = player1 : toMark == 2 ? marked = player2 : marked = player3;
				}
				marked->SpiritMark = 3;
				color(13);
				std::cout << spirit->role << " marked " << marked->role << "! In the next 2 turns, this unit is more vulnerable to damage!\n", color(7);
			}
			if (marked->SpiritMark == 1)
			{
				color(13);
				std::cout << "Mark activated! ";
				if ((marked->mana >= 6 && !spirit->challengeMode) || (marked->mana >= 8 && spirit->challengeMode))
				{
					int healing = spirit->challengeMode ? 1333 : 888;
					int manaCost = spirit->challengeMode ? 8 : 6;
					if (minhphan) healing = 0;
					!(spirit->challengeMode) ? marked->mana -= 6 : marked->mana -= 8;
					spirit->health += healing;
					std::cout << spirit->role << " took " << manaCost << " mana from " << marked->role << " and healed themself for " << healing << " HP!\n";
				}
				else
				{
					std::cout << marked->role << " didn't have enough mana!\n";
					marked->health -= 9999;
				}
				marked->SpiritMark = 0;
				color(7);
			}
			else if (marked->SpiritMark > 0)
			{
				marked->health > 0 ? marked->SpiritMark-- : marked->SpiritMark = 0;
			}
		}

		if (turn % 4 == 0 && turn != 0)
		{
			if (pvinh && pvinh->health > 0)
			{
				color(10);
				std::cout << pvinh->role << " gained 1 Shield!\n";
				pvinh->shield++;
				color(7);
				system("pause");
			}

			if (phantom && (phantom->possessTalent == 9 || phantom->possessTalent2 == 9) && phantom->health > 0)
			{
				color(5);
				std::cout << '\n' << phantom->role << " gained 1 Shield!\n";
				phantom->shield++;
				color(7);
				system("pause");
			}
		}

		if (turn % 5 == 0 && turn != 0)
		{
			if (luubao && luubao->range == 10 && luubao->fructure < 3 && luubao->health > 0)
			{
				color(11);
				std::cout << "Luu Bao gained 1 Structure point!\n";
				color(7);
				luubao->fructure++;
				system("pause");
			}

			if (chimera && chimera->health > 0)
			{
				if (chimera->divine)
				{
					color(14);
					std::cout << '\n' << chimera->role;
					color(7);
					std::cout << " switched to ";
					color(12);
					std::cout << "'Predator' mode\n";
					color(7);
					std::cout << "Before leaving, they removed all of your good effects, cheer!\n";
					chimera->divine = false;
					chimera->predatorMode = true;
					chimera->critUp = 35;
					chimera->armor += 400;
					chimera->magicRes -= 400;
					chimera->abilityPower = 0;
					chimera->attackDmg = 373;
					if (pvinh) pvinh->shield = 0;
					if (duongLe) duongLe->sunBlade = 0;
					system("pause");
				}
				else {
					color(14);
					std::cout << '\n' << chimera->role;
					color(7);
					std::cout << " switched to ";
					color(5);
					std::cout << "'Divine Beast' mode\n";
					color(7);
					std::cout << "Before leaving, they dealt to ", color(14);
					std::cout << gotAtked->role, color(7);
					chimera->divine = true;
					chimera->predatorMode = false;
					chimera->critUp = 0;
					chimera->armor -= 400;
					chimera->magicRes += 400;
					chimera->attackDmg = 0;
					chimera->abilityPower = 535;
					int lastEmbrace = damageOutput(gotAtked->armor * 4 / 10, 0, 1000, 0);
					if (gotAtked->fragile > 0) lastEmbrace = lastEmbrace * 12 / 10;
					if (gotAtked->shield > 0)
					{
						lastEmbrace = 0;
						gotAtked->shield--;
						gotAtked->health += gotAtked->maxHealth / 5;
					}
					gotAtked->health -= lastEmbrace;
					color(12);
					lastEmbrace > 0 ? std::cout << " " << lastEmbrace << " damage " : std::cout << " 0 damage (blocked by shield) ";
					color(7);
					if (minhphan) lastEmbrace = 0;
					chimera->health += lastEmbrace * 2;
					std::cout << "and healed themself ";
					color(10);
					std::cout << lastEmbrace * 2 << " HP!\n";
					color(7);
					system("pause");
				}
			}
		}

		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (pvinh && pvinh->health > 0)
		{
			int healthDiff1 = abs(enemy1->health - pvinh->health), healthDiff2 = abs(enemy2->health - pvinh->health), healthDiff3 = abs(enemy3->health - pvinh->health);
			int healthDiff = max(healthDiff1, max(healthDiff2, healthDiff3));
			int bonusDmg = healthDiff * 5 / 100;
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
				playerChoice(player1, player2, player3, enemy1, enemy2, enemy3);
				if (player1->range != 9)
				{
					player1->attackDmg = player1->baseAD;
					player1->abilityPower = player1->baseAP;
				}
			}
			else playerChoice(player1, player2, player3, enemy1, enemy2, enemy3);
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
				player2->attackDmg *= 2, player1->abilityPower *= 2;
				playerChoice(player2, player1, player3, enemy1, enemy2, enemy3);
				if (player1->range != 9)
				{
					player1->attackDmg = player1->baseAD;
					player1->abilityPower = player1->baseAP;
				}
			}
			else playerChoice(player2, player1, player3, enemy1, enemy2, enemy3);
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
				playerChoice(player3, player1, player2, enemy1, enemy2, enemy3);
				if (player1->range != 9)
				{
					player1->attackDmg = player1->baseAD;
					player1->abilityPower = player1->baseAP;
				}
			}
			else playerChoice(player3, player1, player2, enemy1, enemy2, enemy3);
		}
		//5k+ lines go go

		Entities* targeto = nullptr;

		//Enemies attack

		system("pause");

		if (enemy1->health > 0)
		{
			if (shinigami && enemy1 == shinigami)
			{
				if (shinigami->challengeMode || (turn % 3 == 0 && turn != 0)) useSpell2_2(enemy1, player1, player2, player3);
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
								if (targeto == player1 && ((targeto->range == 11 && (enemy1 != henryFat) || !henryFat) || (enemy1 == henryFat && targeto->poisoned > 0)) && (player2->health > 0 || player3->health > 0))
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
		}

		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (enemy2->health > 0)
		{
			if (shinigami && enemy2 == shinigami)
			{
				if (shinigami->challengeMode || (turn % 3 == 0 && turn != 0)) useSpell2_2(enemy2, player1, player2, player3);
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
		}

		if (player1->health <= 0 && player2->health <= 0 && player3->health <= 0) break;

		if (enemy3->health > 0)
		{
			if (shinigami && enemy3 == shinigami)
			{
				if (shinigami->challengeMode || (turn % 3 == 0 && turn != 0)) useSpell2_2(enemy3, player1, player2, player3);
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
							player1->SpiritMark = 0;
						}
						if (player2->health > 0) playerRemain++;
						else
						{
							player2->poisoned = 0;
							player2->SpiritMark = 0;
						}
						if (player3->health > 0) playerRemain++;
						else
						{
							player3->poisoned = 0;
							player3->SpiritMark = 0;
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
		}

		if (slug)
		{
			if (slug->health <= slug->maxHealth / 2 && slug->resistanceBonus)
			{
				slug->resistanceBonus = false;
				if (!slug->challengeMode)
				{
					slug->armor = slug->armor - 800 < 0 ? 0 : slug->armor - 800;
					slug->magicRes = slug->magicRes - 800 < 0 ? 0 : slug->magicRes - 800;
					slug->attackDmg += 500;
				}
				else
				{
					slug->armor = slug->armor - 1400 < 0 ? 0 : slug->armor - 1400;
					slug->magicRes = slug->magicRes - 1400 < 0 ? 0 : slug->magicRes - 1400;
					slug->attackDmg += 800;
				}
			}
			else if (slug->health <= 0)
			{
				color(14);
				std::cout << "TRUE ART IS AN EXPLOSION! " << slug->role << " exploded and dealt 1000 damage to all friendly units!\n", color(7);
				player1->shield <= 0 ? (player1->fragile > 0 ? player1->health -= 1200 : player1->health -= 1000) : (player1->shield--, player1->health += player1->maxHealth / 5);
				player2->shield <= 0 ? (player2->fragile > 0 ? player2->health -= 1200 : player2->health -= 1000) : (player2->shield--, player2->health += player2->maxHealth / 5);
				player3->shield <= 0 ? (player3->fragile > 0 ? player3->health -= 1200 : player3->health -= 1000) : (player3->shield--, player3->health += player3->maxHealth / 5);
				slug = nullptr;
				free(slug);
			}
		}
		
		if (singer && singer->health <= 0)
		{
			color(14);
			std::cout << singer->role << " resurrected all of their fallen allies and applies 'Fragile' to all friendly unit in 10 turns!\n", color(7);
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

		turn++;
		color(10);
		machineA.autoDestruct == 1 ? machineA.health = 0, printf("Machine A destroyed!\n"), machineA.autoDestruct = 0 : machineA.autoDestruct > 0 ? machineA.autoDestruct-- : machineA.autoDestruct;
		machineB.autoDestruct == 1 ? machineB.health = 0, printf("Machine B destroyed!\n"), machineB.autoDestruct = 0 : machineB.autoDestruct > 0 ? machineB.autoDestruct-- : machineB.autoDestruct;
		machineC.autoDestruct == 1 ? machineC.health = 0, printf("Machine C destroyed!\n"), machineC.autoDestruct = 0 : machineC.autoDestruct > 0 ? machineC.autoDestruct-- : machineC.autoDestruct;
		color(7);

		//shitcome
		if (shitcom.role != "blank")
		{
			if (shitcom.health > 0)
			{
				color(12);
				std::cout << "Shitcom slight burnt, deals to all enemies 75 damage!\n", color(7);
				enemy1->health -= 75, enemy2->health -= 75, enemy3->health -= 75;
			}
			else
			{
				color(14);
				std::cout << "OVERHEAT! Shitcom performed an explosion, deals to all enemies 1200 true damage!\n", color(7);
				enemy1->health -= 1200, enemy2->health -= 1200, enemy3->health -= 1200;
				shitcom = createBlankTarget();
			}
		}

		//Zombie orc
		if (zombieOrc && zombieOrc->health > 0 && !zombieOrc->challengeMode)
		{
			color(6);
			std::cout << "\nZombified Orc loses ", color(12);
			std::cout << zombieOrc->maxHealth / 20 << " HP", color(6);
			std::cout << ", ", color(14);
			std::cout << zombieOrc->armor / 5 << " armor ", color(6);
			std::cout << "and ", color(5);
			std::cout << zombieOrc->magicRes / 5 << " magic resist!\n", color(7);
			zombieOrc->health -= zombieOrc->maxHealth / 20;
			zombieOrc->armor -= zombieOrc->armor / 5;
			zombieOrc->magicRes -= zombieOrc->magicRes / 5;
		}

		if (player1->reincarnation && player1->health > 0)
		{
			color(2);
			int restore = player1->maxHealth * 3 / 100;
			if (player1->poisoned > 0) restore = restore * 4 / 10;
			std::cout << player1->role << " restores " << restore << " HP!\n", color(7);
			player1->health += restore;
		}
		if (player2->reincarnation && player2->health > 0)
		{
			color(2);
			int restore = player2->maxHealth * 3 / 100;
			if (player2->poisoned > 0) restore = restore * 4 / 10;
			std::cout << player2->role << " restores " << restore << " HP!\n", color(7);
			player2->health += restore;
		}
		if (player3->reincarnation && player3->health > 0)
		{
			color(2);
			int restore = player3->maxHealth * 3 / 100;
			if (player3->poisoned > 0) restore = restore * 4 / 10;
			std::cout << player3->role << " restores " << restore << " HP!\n", color(7);
			player3->health += restore;
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
			color(6);
			std::cout << "Stay determined! Fighter gained 20 attack damage and subtract all enemy's armor by 3!", color(7);
			fighter->baseAD += 20, fighter->attackDmg += 20;
			enemy1->baseAR -= 3, enemy1->armor -= 3;
			enemy2->baseAR -= 3, enemy2->armor -= 3;
			enemy3->baseAR -= 3, enemy3->armor -= 3;
		}
		if (phantom && (phantom->possessTalent == 1 || phantom->possessTalent2 == 1) && phantom->health > 0)
		{
			color(6);
			std::cout << "Stay chaotic! Phantom gained 20 attack damage and subtract all friendly unit's armor by 3!", color(7);
			phantom->baseAD += 20, phantom->attackDmg += 20;
			player1->baseAR -= 3, player1->armor -= 3;
			player2->baseAR -= 3, player2->armor -= 3;
			player3->baseAR -= 3, player3->armor -= 3;
		}
		else if (phantom && (phantom->possessTalent == 8 || phantom->possessTalent2 == 8) && phantom->sunBlade < 2 && phantom->health > 0)
		{
			color(9);
			std::cout << phantom->role << " obtained 1 Moon Blade!", color(7);
			phantom->sunBlade++;
		}

		if (caster && caster->antiDeath) caster->antiDeath = false;
		if (fighter && fighter->fighter) fighter->fighter = false;
		std::cout << "\n4 seconds until the next turn...\n";
		Sleep(4000);
	}

	//Shows result
	if ((player1->health > 0 || player2->health > 0 || player3->health > 0) && enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0)
	{
		std::cout << "YOU WON! Good job\n";
	}
	else std::cout << "YOU LOSTT! Better luck next time\n";
	system("pause");
}

int turn = 0;

void battleStart(Entities* player, Entities* enemy) {
	int enemyMaxHealth = (*enemy).health, playerHealth = (*player).health;
	int rottenDamage = enemy->maxHealth * 5 / 100;
	int manaCost;

	switch (player->range)
	{
	case 1: case 7:
		manaCost = 1;
		break;
	case 3: case 4: case 8:
		manaCost = 3;
		if (player->range == 4 && player->genesisUsed) manaCost = 0;
		break;
	case 2:
		manaCost = 4;
		break;
	case 5: case 6:
		manaCost = 3;
		break;
	default:
		manaCost = 0;
		break;
	}

	bool specialForce = false, fighterWill = false, painSupress = false, anhquocSupremacy = false;

	if ((*player).range == 7)
	{
		color(14);
		printf("\nMinh Phan is now on the battle, no healing shall be allowed!\n");
		color(7);
		system("pause");
	}

	if (enemy->welcome)
	{
		color(14);
		std::cout << enemy->role, color(7);
		std::cout << " welcomed you with a soft face.\nYou take ", color(12);
		std::cout << player->maxHealth * 3 / 10 << " damage!\n", color(7);
		player->health -= player->maxHealth * 3 / 10;
		enemy->welcome = false;
	}

	while ((*enemy).health > 0 && (*player).health > 0) {
		if (turn <= 3 && player->autoProtect)
		{
			player->armor = player->baseAR * 29 / 10;
			player->magicRes = player->baseMR * 29 / 10;
		}
		else player->armor = player->baseAR, player->magicRes = player->baseMR;

		if (player->poisoned > 0) enemy->armor = enemy->baseAR * 25 / 10, enemy->magicRes = enemy->baseMR * 25 / 10;

		if (turn % 4 == 0 && turn != 0)
		{
			if (player->range == 9)
			{
				color(10);
				std::cout << "\nYou gained 1 Shield!\n";
				player->shield++;
				color(7);
				system("pause");
			}
			if (enemy->possessTalent == 9 || enemy->possessTalent2 == 9)
			{
				color(5);
				std::cout << "\n" << enemy->role << " gained 1 Shield!\n";
				enemy->shield++;
				color(7);
				system("pause");
			}
		}
		else if (turn % 5 == 0 && turn != 0)
		{
			if (player->range == 10 && player->fructure < 3)
			{
				color(11);
				std::cout << "Gained 1 Structure point!\n";
				color(7);
				player->fructure++;
				system("pause");
			}

			if (enemy->divine && enemy->range == 100)
			{
				color(14);
				std::cout << '\n' << enemy->role;
				color(7);
				std::cout << " switched to ";
				color(12);
				std::cout << "'Predator' mode\n";
				color(7);
				std::cout << "Before leaving, they removed all of your good effects, cheer!\n";
				enemy->divine = false;
				enemy->predatorMode = true;
				enemy->critUp = 35;
				enemy->armor += 400;
				enemy->magicRes -= 400;
				enemy->abilityPower = 0;
				enemy->attackDmg = 373;
				player->shield = 0;
				player->sunBlade = 0;
				system("pause");
			}
			else if (enemy->range == 100) {
				color(14);
				std::cout << '\n' << enemy->role;
				color(7);
				std::cout << " switched to ";
				color(5);
				std::cout << "'Divine Beast' mode\n";
				color(7);
				std::cout << "Before leaving, they dealt to you ";
				enemy->divine = true;
				enemy->predatorMode = false;
				enemy->armor -= 400;
				enemy->critUp = 0;
				enemy->magicRes += 400;
				enemy->attackDmg = 0;
				enemy->abilityPower = 535;
				int lastEmbrace = damageOutput(player->armor * 4 / 10, 0, 1000, 0);
				if (player->shield > 0)
				{
					lastEmbrace = 0;
					player->shield--;
					player->health += player->maxHealth / 5;
				}
				player->health -= lastEmbrace;
				enemy->health += lastEmbrace * 2;
				color(12);
				lastEmbrace > 0 ? std::cout << lastEmbrace << " damage " : std::cout << "0 damage (blocked by shield) ";
				color(7);
				std::cout << "and healed themself ";
				color(10);
				std::cout << lastEmbrace * 2 << " HP!\n";
				color(7);
				system("pause");
			}
		}

		if (enemy->role == "Explosive Slug" && enemy->health < enemy->maxHealth / 2 && enemy->resistanceBonus)
		{
			enemy->resistanceBonus = false;
			if (!enemy->challengeMode)
			{
				enemy->armor = enemy->armor - 800 < 0 ? 0 : enemy->armor - 800;
				enemy->magicRes = enemy->magicRes - 800 < 0 ? 0 : enemy->magicRes - 800;
				enemy->attackDmg += 500;
			}
			else
			{
				enemy->armor = enemy->armor - 1400 < 0 ? 0 : enemy->armor - 1400;
				enemy->magicRes = enemy->magicRes - 1400 < 0 ? 0 : enemy->magicRes - 1400;
				enemy->attackDmg += 800;
			}
		}

		if (player->range == 9)
		{
			int healthDiff = enemy->health - player->health;
			healthDiff < 0 ? healthDiff *= -1 : healthDiff;
			int bonusDmg = healthDiff * 7 / 100;
			player->attackDmg = player->baseAD;
			player->attackDmg += bonusDmg;
		}

		char choice;

	playerInput:

		std::cout << "\nChoose attack method:\n1. Normal attacks ";
		(*player).range == 4 ? printf("(+2 Mana)") : printf("(+1 Mana)");
		if (player->range == 8) {
			color(14);
			std::cout << "  Current Sunblade: " << player->sunBlade;
			color(7);
		}
		else if (player->range == 9)
		{
			color(10);
			std::cout << "  Your shield: " << player->shield;
			color(7);
		}
		if (enemy->possessTalent == 8 || enemy->possessTalent2 == 8)
		{
			color(5);
			std::cout << "  " << enemy->role << "'s Moon Blade: " << enemy->sunBlade;
			color(7);
		}
		else if (enemy->possessTalent == 9 || enemy->possessTalent2 == 9)
		{
			color(5);
			std::cout << "  " << enemy->role << "'s shield: " << enemy->shield;
			color(7);
		}
		std::cout << "\n2. Cast first spell ";
		(player->range != 7 && player->range != 8 && player->range != 6) ? printf("(-3 mana)") : printf("(-2 mana)");
		std::cout << "\n3. Cast second spell (-" << manaCost << " Mana)\n4. Check your stats\n5. Check enemy's stats\n";
		if (player->range != 10) std::cout << "Other: Skip this turn (+3 mana)";
		else
		{
			std::cout << "6. Summon Machine (-1 structure point)";
			color(14);
			std::cout << "  Structure point: " << player->fructure;
			color(7);
			std::cout << "\nOther: Skip this turn (+3 mana)";
		}

		color(11);
		std::cout << "\nCurrent mana: " << (*player).mana;
		color(7);
		std::cout << "\nYour choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			if (machineA.health > 0 || machineB.health > 0 || machineC.health > 0)
			{
				std::cout << "You healed machine with lowest HP for ";
				color(2);
				std::cout << player->abilityPower << " HP!\n";
				if ((((machineA.health < machineB.health && machineB.health > 0) || (machineA.health > machineB.health && machineB.health <= 0)) && ((machineA.health < machineC.health && machineC.health > 0) || (machineA.health > machineC.health && machineC.health <= 0))) && machineA.health > 0)
				{
					machineA.health + player->abilityPower > 1500 ? machineA.health = 1500 : machineA.health += player->abilityPower;
				}
				else if ((((machineB.health < machineA.health && machineA.health > 0) || (machineB.health > machineA.health && machineA.health <= 0)) && ((machineB.health < machineC.health && machineC.health > 0) || (machineB.health > machineC.health && machineC.health <= 0))) && machineB.health > 0)
				{
					machineB.health + player->abilityPower > 1500 ? machineB.health = 1500 : machineB.health += player->abilityPower;
				}
				else if (machineC.health > 0)
				{
					machineC.health + player->abilityPower > 1500 ? machineC.health = 1500 : machineC.health += player->abilityPower;
				}
				color(7);
			}
			else dealingDamage(&(*player), &(*enemy), false, false, playerHealth, enemyMaxHealth, false, 0);
			(*player).range != 4 ? (*player).mana++ : (*player).mana += 2;
			break;
		case '2':
			if ((*player).mana >= 3 || (player->mana >= 2 && (player->range == 6 || player->range == 7 || player->range == 8)))
			{
				(*player).range != 7 && player->range != 8 && player->range != 6 ? (*player).mana -= 3 : (*player).mana -= 2;
				useSpell_1(&(*player), &(*enemy), &machineA, &machineB, &machineC, enemy->maxHealth);
				//if ((*player).role == "Caster") (*player).mana = 0;
				if ((*player).role == "Specialist") player->specialForce = true;
			}
			else
			{
				printf("Spell cast failed! You don't have enough mana");
				goto playerInput;
			}
			break;
		case '3':
		{
			if ((*player).mana >= manaCost) {
				useSpell_2(&(*player), &(*enemy), enemyMaxHealth, (*player).mana, playerHealth);
				if ((*player).role == "Fighter") fighterWill = true;
				else if ((*player).role == "Anh Quoc") anhquocSupremacy = true;
				else if ((*player).role == "Caster" && !(*player).genesisUsed) painSupress = true;

				if ((*player).genesisUsed)
				{
					std::cout << "\nSpell cast failed! This spell is no longer usable!\n";
					goto playerInput;
				}
				(*player).mana -= manaCost;
				if ((*player).role == "Specialist") (*player).mana++;
				else if (player->range == 9 && player->summonShitcom)
				{
					shitcom = createShitCom();
					player->summonShitcom = false;
				}
				else if (player->range == 9 && !player->summonShitcom) {
					color(6);
					std::cout << "But nobody came...\n";
					color(7);
					goto playerInput;
				}
				else if (player->range == 10) {
					if (machineA.role != "blank" && machineA.health > 0 && machineA.autoDestruct == 0)
					{
						machineA.autoDestruct = 3;      machineA.armor += 200;
						machineA.attackDmg *= 27 / 10;  machineA.magicRes += 200;
						machineA.maxHealth *= 2;        machineA.health *= 2;
					}
					if (machineB.role != "blank" && machineB.health > 0 && machineB.autoDestruct == 0)
					{
						machineB.autoDestruct = 3;      machineB.armor += 200;
						machineB.attackDmg *= 27 / 10;  machineB.magicRes += 200;
						machineB.maxHealth *= 2;        machineB.health *= 2;
					}
					if (machineC.role != "blank" && machineC.health > 0 && machineC.autoDestruct == 0)
					{
						machineC.autoDestruct = 3;      machineC.armor += 200;
						machineC.attackDmg *= 27 / 10;  machineC.magicRes += 200;
						machineC.maxHealth *= 2;        machineC.health *= 2;
					}
				}
			}
			else {
				printf("Spell cast failed! You don't have enough mana");
				goto playerInput;
			}
			break;
		}
		case '4':
		{
			std::cout << "\n" "\nHere is your current stats:\n" "\n";
			std::cout << "\n" "\nBasic stats:\n" "\n";
			color(14);
			std::cout << "Class: " << player->role;
			color(10);
			std::cout << "\nHealth: " << (*player).health;
			color(12);
			std::cout << "\nAttack damage: " << (*player).attackDmg;
			color(5);
			std::cout << "\nAbility power: " << (*player).abilityPower;
			color(4);
			std::cout << "\nLife steal: " << (*player).omniVamp << "%";
			color(6);
			std::cout << "\nArmor: " << (*player).armor;
			color(11);
			std::cout << "\nMagic resist: " << (*player).magicRes;
			color(15);
			std::cout << "\n\nTalent      >> ";
			color(7);
			std::cout << (*player).talent;
			color(15);
			std::cout << "\nFirst skill >> ";
			color(7);
			std::cout << (*player).spell_1;
			color(15);
			std::cout << "\nLast skill  >> ";
			color(7);
			std::cout << (*player).spell_2 << std::endl;
			system("pause");
			goto playerInput;
			//battleStart(&(*player), &(*enemy));

			break;
		}

		case '5':
		{
			printf("\nEnemy stats: ");
			printEnemyInfo(&(*enemy));
			system("pause");
			goto playerInput;
			//battleStart(&(*player), &(*enemy));
			break;
		}

		case '6':
		{
			if (player->range == 10)
			{
				std::cout << "Enter number of machines to summon: ";
				int number;
				std::cin >> number;
				number > player->fructure ? number = player->fructure : number;
				for (int i = 1; i <= number; i++) {
					if (player->fructure >= 1) {
						color(10);
						std::cout << "Summoned new Machine!\n";

						if (machineA.health <= 0) machineA = createMachine();
						else if (machineB.health <= 0) machineB = createMachine();
						else if (machineC.health <= 0) machineC = createMachine();
						else
						{
							std::cout << "All machines are being deloyed, summoning failed!\n";
							player->fructure++;
						}
						color(7);
						player->fructure--;
					}
					else
					{
						std::cout << "Summoning failed! You don't have enough structure point\n";
						goto playerInput;
						break;
					}
				}
				break;
			}
		}

		default:
			printf("You skipped this turn and instead gains 3 mana\n");
			player->mana += 3;
			break;
		}

		if (machineA.health > 0) dealingDamage(&machineA, &*enemy, 0, 0, machineA.health, enemy->maxHealth, 0, 0);
		if (machineB.health > 0) dealingDamage(&machineB, &*enemy, 0, 0, machineB.health, enemy->maxHealth, 0, 0);
		if (machineC.health > 0) dealingDamage(&machineC, &*enemy, 0, 0, machineC.health, enemy->maxHealth, 0, 0);

		if ((*enemy).health > 0)
		{
			if (player->range == 9 && shitcom.health > 0 && shitcom.role != "blank")
			{
				dealingDamage(&*enemy, &shitcom, 0, 0, shitcom.maxHealth, enemy->maxHealth, 0, 0);
				color(12);
				std::cout << "\nShitcom slightly burnt, dealt 75 damage!\n";
				enemy->health -= 75;
				color(7);
			}
			else if (machineA.role != "blank" || machineB.role != "blank" || machineC.role != "blank")
			{
				(machineA.health > 0) ? dealingDamage(&*enemy, &machineA, 0, 0, machineA.health, enemy->maxHealth, 0, 0)
					: (machineB.health > 0) ? dealingDamage(&*enemy, &machineB, 0, 0, machineB.health, enemy->maxHealth, 0, 0)
					: (machineC.health > 0) ? dealingDamage(&*enemy, &machineC, 0, 0, machineC.health, enemy->maxHealth, 0, 0)
					: dealingDamage(&*enemy, &*player, 0, 0, player->health, enemy->maxHealth, 0, 0);
			}
			else if (enemy->range == 60 && player->poisoned > 0)
			{
				int heal;
				player->range == 7 ? heal = 0 : heal = 500;
				std::cout << enemy->role << " is on their vacation, they recover ", color(10);
				std::cout << heal << " HP!\n", color(7);
				enemy->health += heal;
				enemy->health > enemy->maxHealth ? enemy->health = enemy->maxHealth : enemy->health = enemy->health;
			}
			else dealingDamage(&(*enemy), &(*player), specialForce, fighterWill, playerHealth, enemyMaxHealth, painSupress, anhquocSupremacy);
			painSupress = false;

			if ((*enemy).role == "Zombified Orc" && !enemy->challengeMode)
			{
				int rottenAR = (*enemy).armor / 5, rottenMR = (*enemy).magicRes / 5;
				rottenAR = rottenAR < 0 ? 0 : rottenAR;
				rottenMR = rottenMR < 0 ? 0 : rottenMR;
				color(4);
				std::cout << "This unit is no longer alive, they lose ";
				color(12);
				std::cout << rottenDamage << " health, ";
				color(6);
				std::cout << rottenAR << " armor";
				color(4);
				std::cout << " and ";
				color(11);
				std::cout << rottenMR << " magic resist.\n";
				color(7);
				(*enemy).health -= rottenDamage, (*enemy).armor -= rottenAR, (*enemy).magicRes -= rottenMR;
			}
		}

		if (player->range == 8 && player->sunBlade < 4)
		{
			color(9);
			if (player->obtainingSunblade)
			{
				std::cout << "\nYou obtained 1 Sun Blade!\n";
				player->sunBlade++;
			}
			else
			{
				std::cout << "\nYou're forbidden from receiving Sun Blade this round!\n";
				player->obtainingSunblade = true;
			}
			color(7);
		}
		else if (player->range == 9 && shitcom.health <= 0 && shitcom.role != "blank")
		{
			color(14);
			std::cout << "\nOVERHEATED! " << shitcom.role << " exploded and dealt 1200 true damage!\n";
			enemy->health -= 1200;
			color(7);
			shitcom.role = "blank";
		}

		if ((enemy->possessTalent == 8 || enemy->possessTalent2 == 8) && enemy->sunBlade < 2)
		{
			enemy->sunBlade++;
			color(9);
			std::cout << '\n' << enemy->role << " obtained 1 Moon Blade!\n";
			color(7);
		}
		else if (enemy->role == "Explosive Slug" && enemy->health <= 0)
		{
			color(14);
			std::cout << "\nTRUE ART IS AN EXPLOSION! " << enemy->role << " exploded and dealt " << 400 + player->maxHealth / 5 << " true damage!\n";
			player->health -= 400 + player->maxHealth / 5;
			color(7);
		}
		else if (enemy->role == "Vengeful Spirit")
		{
			if (turn % 6 == 0)
			{
				player->spiritMark = true;
				color(14);
				std::cout << enemy->role;
				color(7);
				std::cout << " marks you in the next 3 turns! During this time, you have to take extra damage!\n";
			}
			else if (turn % 6 == 3 && player->spiritMark)
			{
				player->spiritMark = false;
				color(5);
				std::cout << "\nMARK ACTIVATED! ";
				if ((!enemy->challengeMode && player->mana >= 6) || (player->mana >= 8 && enemy->challengeMode)) {
					if (!enemy->challengeMode)
					{
						player->mana -= 6;
						std::cout << enemy->role << " took 6 mana from you and healed themself for ";
						color(2);
						if (player->range != 7) {
							std::cout << "888 HP!\n";
							enemy->health += 888;
							enemy->health > enemy->maxHealth ? enemy->health = enemy->maxHealth : enemy->health;
						}
						else std::cout << "0 HP!\n";
					}
					else
					{
						player->mana -= 8;
						std::cout << enemy->role << " took 8 mana from you and healed themself for ";
						color(2);
						if (player->range != 7) {
							std::cout << "1333 HP!\n";
							enemy->health += 1333;
							enemy->health > enemy->maxHealth ? enemy->health = enemy->maxHealth : enemy->health;
						}
						else std::cout << "0 HP!\n";
					}
				}
				else {
					color(12);
					std::cout << "You didn't have enough mana!\n";
					player->health -= 9999;
				}
				color(7);
			}
			else if (player->spiritMark)
			{
				color(5);
				std::cout << 3 - turn % 6 << " turns left until the mark activate!\n";
				color(7);
			}
		}
		else if (enemy->range == 60 && player->poisoned > 0)
		{
			player->poisoned--;
			if (player->shield > 0) {
				std::cout << "This damage is blocked, you restore ", color(10);
				std::cout << player->maxHealth / 5 * 4 / 10 << " HP!\n", color(7);
				player->health += player->maxHealth / 5 * 4 / 10;
			}
			else
			{
				int poisonBaseDmg = 200, p_MissingHealth = (player->maxHealth - player->health) * 100 / player->maxHealth;
				poisonBaseDmg += p_MissingHealth * 7;
				if (poisonBaseDmg > 500) poisonBaseDmg = 500;
				int poisonDmg = damageOutput(0, player->magicRes, 0, poisonBaseDmg);
				std::cout << "Poison triggers, you take ", color(5);
				std::cout << poisonDmg << " damage!\n", color(7);
				player->health -= poisonDmg;
			}
		}

		if (player->emergencyOn && player->health < 0)
		{
			(*player).health = 1000;
			(*player).emergencyOn = false;
			color(11);
			std::cout << "The switch is on! You are healed for ";
			color(2);
			std::cout << 1000 + 600 << " HP ";
			color(11);
			std::cout << "and gains ";
			color(14);
			std::cout << "100% dodge";
			color(11);
			std::cout << " in the next turn!\n";
			color(7);
			(*player).health += 1000;
			(*player).mana += 3;
			(*player).readytoDodge = true;
		}

		if (player->health < 0) player->health = 0;
		printHealthBar(player, 2);

		if (player->range == 9 && shitcom.health > 0 && shitcom.role != "blank") printHealthBar(&shitcom, 14);
		else if (player->range == 10)
		{
			if (machineA.role != "blank" && machineA.health > 0) printHealthBar(&machineA, 14);
			if (machineB.role != "blank" && machineB.health > 0) printHealthBar(&machineB, 1);
			if (machineC.role != "blank" && machineC.health > 0) printHealthBar(&machineC, 11);
		}

		//Print enemy health bar
		if (enemy->health < 0) enemy->health = 0;
		printHealthBar(enemy, 13);

		specialForce = false, fighterWill = false, anhquocSupremacy = false;;
		if ((*player).role == "Fighter" && (*player).health > 0)
		{
			color(6);
			std::cout << "Stay determined! You gained ";
			color(12);
			std::cout << "20 attack damage ";
			color(6);
			std::cout << "and ";
			color(14);
			std::cout << "subtract enemy's armor by 5!\n";
			color(7);
			(*player).attackDmg += 20;
			(*enemy).armor -= 5;
		}

		if ((enemy->possessTalent == 1 || enemy->possessTalent2 == 1) && enemy->health > 0)
		{
			color(6);
			std::cout << "Stay chaotic! ";
			color(14);  std::cout << enemy->role;
			color(6);
			std::cout << " gained ";
			color(12);
			std::cout << "20 attack damage ";
			color(6);
			std::cout << "and ";
			color(14);
			std::cout << "subtract your armor by 5!\n";
			color(7);
			(*enemy).attackDmg += 20;
			(*player).armor -= 5;
		}

		if (player->reincarnation && turn != 0 && player->health > 0)
		{
			color(2);
			int heal = player->maxHealth * 3 / 100;
			if (player->poisoned > 0) heal = heal * 4 / 10;
			std::cout << "You restored " << heal << " HP!\n";
			color(7);
			player->health += heal;
			player->health > player->maxHealth ? player->health = player->maxHealth : player->health = player->health;
		}

		turn++;
		color(10);
		machineA.autoDestruct > 1 && machineA.health > 0 ? machineA.autoDestruct-- : machineA.autoDestruct == 1 ? printf("Machine A destroyed\n"), machineA.health = 0, machineA.autoDestruct = 0 : machineA.autoDestruct;
		machineB.autoDestruct > 1 && machineB.health > 0 ? machineB.autoDestruct-- : machineB.autoDestruct == 1 ? printf("Machine B destroyed\n"), machineB.health = 0, machineB.autoDestruct = 0 : machineB.autoDestruct;
		machineC.autoDestruct > 1 && machineC.health > 0 ? machineC.autoDestruct-- : machineC.autoDestruct == 1 ? printf("Machine C destroyed\n"), machineC.health = 0, machineC.autoDestruct = 0 : machineC.autoDestruct;
		color(7);
		system("pause");
	}

	if ((*enemy).health <= 0 && (*player).health > 0)
	{
		std::cout << "YOU WON! Good job\n";
		system("pause");
		system("cls");
		exit;
	}
	else
	{
		std::cout << "YOU LOST! Better luck next time...\n";
		system("pause");
		system("cls");
		exit;
	}
}

void chooseRune(Entities* player)
{
	int rune1, rune2, rune3, bigRune;
	color(14);
	std::cout << "Select " << player->role << "'s Rune!", color(7);
	std::cout << "\nChoose 1st rune:\n1. Max health +150\n2. Resistances +10\n3. Attack damage +12/+20 (adaptive)\nYour choice: ";
	std::cin >> rune1;
	switch (rune1)
	{
	case 1:
		player->maxHealth += 150, player->health += 150;
		break;
	case 2:
		player->armor += 10, player->magicRes += 10;
		break;
	default:
		player->attackDmg > player->abilityPower ? player->baseAD += 12, player->attackDmg += 12 : player->abilityPower += 20;
		break;
	}
	std::cout << "\nChoose 2nd rune:\n1. Base mana +2\n2. Attack damage +12/+20 (adaptive)\n3. Crit chance +10%\nYour choice: ";
	std::cin >> rune2;
	switch (rune2)
	{
	case 2:
		player->attackDmg > player->abilityPower ? player->baseAD += 12, player->attackDmg += 12 : player->abilityPower += 20;
		break;
	default:
		player->critUp = 10;
		break;
	case 1:
		player->mana += 2;
		break;
	}
	std::cout << "\nChoose 3rd rune:\n1. Resistances +10\n2. Armor penetration +5%\n3. Magic penetration +5%\nYour choice: ";
	std::cin >> rune3;
	switch (rune3)
	{
	case 1:
		player->armor += 10, player->magicRes += 10;
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
		std::cout << "Defensive\n1. Reincarnation: After everyturn, restores 3% max health\n2. Cooper Seal: Attacks and abilities deal an additional magic damage equals 8% self max HP\n";
		std::cout << "3. Solo - Auto Protect: In the first 3 turns of the battle, resistances +290%\n3. Teamfight - Creed Field: Healing grants to other allies has +15% effectiveness\nSelect: ";
		std::cin >> bigRune;
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
		std::cout << "Offensive\n1. Insult to the Injury: Attack against target with less than 40% HP deals an additional 12% damage\n2. Exploit Weaknesses: Critical attack deals an additional 135 + 10% true damage (multiple hits-attack only applies the bonus damage once)\n";
		std::cout << "3. Deathmatch : Attack against target with more than 60% HP deals an additional 8% damage. When self has less than 40% health, attack deals extra 7% damage\nYour choice: ";
		std::cin >> bigRune;
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

void chooseSong()
{
	color(8);
	int songSelection;
	std::cout << "Choose song:\n1. Dusk dragon\n2. Towerfierce\n3. Lostmemory\n4. Church\n5. Abyssal Hunters\n6. Lungmen battle\n7. Shield\n8. Wave...\n9. Random pick\n0. No song pls im fine\nInput: ";
	std::cin >> songSelection;
	songSelection == 9 ? songSelection = rand() % (8 - 1 + 1) + 1 : songSelection = songSelection;
	songSelection != 0 ? printf("Now playing: ") : printf("No song was choosen!");
	switch (songSelection)
	{
	case 1:
		PlaySound(TEXT("duskdragon.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Dusk dragon");
		break;
	case 2:
		PlaySound(TEXT("towerfierce.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Towerfierce");
		break;
	case 3:
		PlaySound(TEXT("lostmemory.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Lost memory");
		break;
	case 4:
		PlaySound(TEXT("church.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Church");
		break;
	case 5:
		PlaySound(TEXT("undertides.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Abyssal Hunters");
		break;
	case 6:
		PlaySound(TEXT("lungmen.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Lungmen Battle");
		break;
	case 7:
		PlaySound(TEXT("shield.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Shield");
		break;
	case 8:
		PlaySound(TEXT("dusktheme.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
		printf("Till the Wave Ends");
		break;
	}
	printf("\n\n");
	color(7);
}

void mainMenu() {
	int modoChoice;
	std::cout << "Select combat mode:\n1. Solo\n2. 3v3\nInput: ";
	std::cin >> modoChoice;
	Entities player = createSoldier(), player2 = createBlankTarget(), player3 = createBlankTarget();
	Entities enemy = createBlankTarget(), enemy2 = createBlankTarget(), enemy3 = createBlankTarget();

	if (modoChoice == 1) modoChoice = 1;
	else
	{
		modoChoice = 3; player2 = createSoldier(); player3 = createSoldier();
		if (player.range == player2.range || player2.range == player3.range || player.range == player3.range)
		{
			std::cout << "\nDO NOT choose existed role, nigga!\nNow choose again from the 2nd unit.";
			system("pause");
			player2 = createBlankTarget(), player3 = createBlankTarget();
			player2 = createSoldier(), player3 = createSoldier();
		}
	}

	for (int i = 1; i <= modoChoice; i++)
	{
		Entities* currentEnemy;
		i == 1 ? currentEnemy = &enemy : i == 2 ? currentEnemy = &enemy2 : currentEnemy = &enemy3;
		char choice;
		printf("\nChoose enemy type (Choosing duplicated enemy in 3v3 is not banned, but can causes serious errors and I'm not fixing that):\n1. Random\n2. Goblin Champion fight: easy\n3. Senior shaman: easy\n4. Zombified Orc: quite tricky, but not that hard with some good counter picks\n5. Advanced Drawft: fun\n6. Explosive Slug: better tank wins\n7. Phantom: pick and pray for a good RNG\n8. Vengeful Spirit: fun\n9. Chimera: for people who loves suffering\nA. Henry Fat: extra fun\nB. The Singer: it sings\nC. Reaper: it reaps\nYour choice: ");
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			*currentEnemy = createGoblinA();
			system("pause");
			break;
		case '2':
			*currentEnemy = createGoblinChamp();
			system("pause");
			break;
		case '3':
			*currentEnemy = createSeniorShaman();
			system("pause");
			break;
		case '4':
			*currentEnemy = createZombieOrc();
			system("pause");
			break;
		case '5':
			*currentEnemy = createSneaker();
			system("pause");
			break;
		case '6':
			*currentEnemy = createExplosiveSlug();
			system("pause");
			break;
		case '7':
		{
			*currentEnemy = createPhantom();
			system("pause");
			srand(time(NULL));
			int talent = rand() % (9 - 1 + 1) + 1;
			currentEnemy->possessTalent = talent;
			color(12);
			std::cout << "\nTalent possessed: ";
			color(5);
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
			color(7);
			printf("\n");
			system("pause");
			break;
		}
		case '8':
			*currentEnemy = createSpirit();
			system("pause");
			break;
		case '9':
			*currentEnemy = createChimera();
			system("pause");
			break;
		case 'a': case 'A':
			*currentEnemy = createAplha();
			system("pause");
			break;
		case 'b': case 'B':
			*currentEnemy = createSinger();
			system("pause");
			break;
		case 'c': case 'C':
			*currentEnemy = createShinigami();
			system("pause");
			break;
		default:
			retardInput();
			mainMenu();
			break;
		}
		currentEnemy = nullptr;
		free(currentEnemy);
	}
	system("pause");

	int challMod;
	std::cout << "\nBattle mode:\n1. Stay simple\n2. Demand a dick move\nInput: ";
	std::cin >> challMod;
	if (challMod == 1) std::cout << "\nBattle starto!\n";
	else
	{
		enemy.challengeMode = true;
		enemy2.challengeMode = true;
		enemy3.challengeMode = true;
		std::cout << "\nChallenge Mode selected!\n\n";
		color(12);
		for (int i = 0; i < modoChoice; i++)
		{
			Entities* currentEnemy = nullptr;
			i == 0 ? currentEnemy = &enemy : i == 1 ? currentEnemy = &enemy2 : currentEnemy = &enemy3;
			std::cout << currentEnemy->role << " - ";
			switch (currentEnemy->range)
			{
			case 55:
				std::cout << "Undead the Undying: Zombified Orc no longer loses HP and resistances overtime!\n";
				break;
			case 56:
				std::cout << "Dodge Up: Dwarft has significantly increased dodge & graze chance and bonus damage\n";
				break;
			case 57:
				std::cout << "Shell Defense: Slug's bonus armor, magic resist and attack damage from passive increased even greater.\n";
				enemy.armor += 500;         enemy.magicRes += 500;
				break;
			case 58:
			{
				std::cout << "Specter: Phantom possesses up to 2 separate talents!\n";
				int talent = rand() % (9 - 1 + 1) + 1;
				currentEnemy->possessTalent2 = talent;
				if (currentEnemy->possessTalent == currentEnemy->possessTalent2 && currentEnemy->possessTalent < 9)
				{
					enemy.possessTalent2++;
					talent++;
				}
				else if (currentEnemy->possessTalent == currentEnemy->possessTalent2)
				{
					currentEnemy->possessTalent2--;
					talent--;
				}
				color(12);
				std::cout << "Talent 2 possessed: ";
				color(5);
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
				color(12);
				printf("\n");
				break;
				
			}
			case 59:
				std::cout << "Hateful Spirit: Mana consumption increases to 8, healing increases to 1333 HP\n";
				break;
			case 60:
				std::cout << "Brodifacoum: Poison deals 250% damage and deals at least 200 damage, regardless of target's magic resist\n";
				break;
			case 61:
				std::cout << "Hymn of Battle: All enemy units ATK +50% (Unlimited duration)\n";
				break;
			case 62:
				std::cout << "Bounty Harvest: Reaper now always performs AoE attack\n";
				break;
			case 100:
				std::cout << "Remember the Beast: Chimera has greatly increased HP and attack instead deals true damage\n";
				currentEnemy->health += 4000;
				currentEnemy->maxHealth += 4000;
				break;
			default:
				std::cout << "This enemy has their basic stats increases by 100\n";
				currentEnemy->abilityPower < currentEnemy->attackDmg ? currentEnemy->baseAD += 100, currentEnemy->attackDmg += 100 : currentEnemy->baseAP += 100, currentEnemy->abilityPower += 100;
				currentEnemy->armor += 100, currentEnemy->baseAR += 100, currentEnemy->baseMR += 100, currentEnemy->magicRes += 100;
				currentEnemy->maxHealth += 1000, currentEnemy->health += 1000;
				break;
			}
			printf("\n");
		}
		color(7);
	}

	if (modoChoice == 1)
	{
		chooseRune(&player);
		chooseSong();
		battleStart(&player, &enemy);
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
		if ((enemy.range == 61 || enemy2.range == 61 || enemy3.range == 61) && enemy.challengeMode)
		{
			color(8);
			std::cout << "The Singer performs their own song, it's not your turn to decide\nNow playing: Art of Blade\n", color(7);
			PlaySound(TEXT("blade.wav"), NULL, SND_LOOP | SND_ASYNC);
		}
		else chooseSong();
		battleStart_3v3(&player, &player2, &player3, &enemy, &enemy2, &enemy3);
	}
}

int main() {
	mainMenu();
	//dit me quoc anh
	return 0;
}