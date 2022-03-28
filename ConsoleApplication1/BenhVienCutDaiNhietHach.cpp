#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<algorithm>
#include<vector>
#include<random>
#include<chrono>
#include<filesystem>
#include<fstream>
#pragma comment(lib, "winmm.lib")

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
#define DA_YELLOW 6
#define LI_CIRNO 11
#define GRAY 8
#define WHITE 7
#define LI_WHITE 15

bool runningProgram = true, reduceManaRequirement = false, recollectOpStart = false, recollectOperationAccomplish = false, towerMode = false;
const int fighterBaseAD = 375;
bool flag = false;

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
	bool spiritMark = false, challengeMode = false, predatorMode = false, divine = false, welcome = false, solo = false, standBy = false, combat = false, firstStrike = false, floating = false;
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
	int possessTalent = 0, possessTalent2 = 0, poisoned = 0, SpiritMark = 0, fragile = 0, shockwave = 1, taunt = 0, stack = 0;

	unsigned long long damageDealt = 0, healingDone = 0;
};

long damageOutput(int armor, int magicResistance, int physicDmg, int magicDmg) {
	if (armor > 1000 && armor < 3000) armor = 950;
	else if (armor >= 3000) armor = 1000;
	if (magicResistance > 1000 && magicResistance < 3000) magicResistance = 950;
	else if (magicResistance >= 3000) magicResistance = 1000;
	int physicTaken = physicDmg * (1000 - armor) / 1000;
	int magicTaken = magicDmg * (1000 - magicResistance) / 1000;
	return physicTaken + magicTaken;
}

int lifeSteal(int damage, int vamp) { return damage * vamp / 100; }

//Manual choose
Entities createSoldier() {
	srand(time(NULL));
	std::string randomChar = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c'};

	setColor(BO_RED);
	std::cout << "\nChoose unit's role:\n";

	std::vector<char> solSymbol = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'R'};
	std::vector<std::string> solName = { "Fighter", "Defender", "Maskman", "Caster", "Specialist", "Anh Quoc", "Minh Phan", "Duong Le", "Phong Vinh", "Luu Bao", "Supporter", "Alter Vinh", "Random character"};
	std::vector<std::string> solDes = { "Starts off mediocre, but will slowly dominate the entire battlefield as the fight goes on", "Have increased HP and Resistances by sacrificing their own damage", "High attack damage, easier to obtain a critical strike and has healing potential, but somewhat squishy", "Insane strong damage burst on single target, or decent AoE damage", "Decent stats and less likely to be attacked", "Recommend for whoever wishes to test their luck", "Destroy the battlefield with his own weight", "For people who has no brain and prefers using normal attacks", "Be still, as a mountain, yet no maidens", "Uses quantity to destroy quality", "Provides decent healing and utility", "Applies buff and debuff, repeatively", "Pick any playable character"};

	for (int i = 0; i < solName.size(); i++)
	{
		i < solName.size() - 1 ? setColor(DA_YELLOW) : setColor(PURPLE);
		std::cout << solSymbol[i] << ". " << solName[i] << ": ";
		setColor(GRAY);
		std::cout << solDes[i] << '\n';
	}
	
	setColor(BO_RED);
	std::cout << "\nYour choice: ";

	Entities soldier;

	char choice;
	std::cin >> choice;
	setColor(LI_YELLOW);
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
		soldier.tags = "Support, DPS";
		soldier.nation = "Royal Warrior";
		hp = 2570;       ad = 375;
		ar = 450;        mr = 300;
		rng = 1;
		soldier.talent = "Increasing Danger: Gain bonus damage and lethality base on battle's duration";
		soldier.spell_1 = "Juggernaunt (3 mana): Enhance the weapon and deals physic damage equals 150% AD + 200% bonus AD + 35% target's HP, ignore 50% armor (can not crit)";
		soldier.spell_2 = "Unshakable Solidarity (1 mana): Reduces 90% damage taken this turn and decreases target's armor by 3 + 5%. Then attack with 50% AD";
		break;
	case '2':
		std::cout << "You chose Defender class!";
		soldier.role = "Defender";
		soldier.tags = "Survival, Defense, Crowd-control";
		soldier.nation = "Royal Warrior";
		hp = 3500;      ad = 100;
		ar = 650;       mr = 500;
		rng = 2;        ap = 0;
		soldier.talent = "Spiky: Whenever got attacked, reflects 50 (+40% armor) (+40% magic resist) magic damage to the attacker. This damage also benefits from runes\n               Moral Support: If this unit starts the battle in teamfight mode, max HP +15%";
		soldier.spell_1 = "Reinforcement (3 mana): Immediately restore 200 + 20% missing health";
		soldier.spell_2 = "Rock Solid: This ability has 2 uses, bases on what gamemode you're in\nSolo (4 mana): Brandishes the shield, deals (20% max health + 100% armor + 100% magic resist + 25% target's missing health) magic damage\nTeamfight (3 mana): Briefly increases self resistance by 180%, then 'Taunt' and 'Silent' all enemies in 1 turn. 'Taunted' enemies will prioritize attack this unit, regardless of their current state or trait";
		break;
	case '3':
		std::cout << "You chose Maskman class!";
		soldier.role = "Maskman";
		soldier.tags = "DPS, Survival";
		soldier.nation = "Royal Warrior";
		hp = 2100;      ad = 580;      vamp = 10;
		ar = 300;       mr = 250;       soldier.critUp = 45;
		rng = 3;        ap = 0;
		soldier.talent = "Sharp Eyes: Crit chance increases to 60% and gains 10% life steal (capped at 50%).\n               Cut Down (Unique): Deals increased damage against target with greater max health than this unit (bonus damage is capped at 100% at 200% greater max health)";
		soldier.spell_1 = "Armor Penetration Crossbow (3 mana): Next attack instead deals 180% damage, ignores 25% armor and guarantee a crit. This attack also benefits with bonus 50 + 15% omnivamp";
		soldier.spell_2 = "Absolute Focus (2 mana): Permanently gain 50 AD and 10% life steal, then attack with 100% AD";
		break;
	case '4':
		std::cout << "You chose Caster class!";
		soldier.role = "Caster";
		soldier.tags = "AoE, Nuker";
		soldier.nation = "Royal Warrior";
		hp = 2375;      ad = 55;       mageForce = 3;
		ap = 600;       ar = 250;
		mr = 400;   rng = 4;
		soldier.talent = "Quick Charge (Unique): Normal attacks instead recover 2 mana, this unit also gains 3 bonus mana at the start of battle";
		soldier.spell_1 = "Volcano: Consume all mana, then gain 150 ability power and attacks an enemy with 200% AP. Damage type change to 'True', each mana spent increases damage output by 50 + 20%";
		soldier.spell_2 = "Meteorite (3 mana): Deals 230% AP magic damage to all enemies, damage output is calculated based on the enemy with LEAST magic resist. This damage can not be blocked nor grazed, and can not trigger other effects";
		break;
	case '5':
		std::cout << "You chose Specialist class!";
		soldier.role = "Specialist";
		soldier.tags = "Survival";
		soldier.nation = "Self-government Lab";
		hp = 3333;     ad = 200;      soldier.emergencyOn = true;
		ap = 0;        ar = 100;
		mr = 100;       rng = 5;
		soldier.talent = "Camouflage (Unique): 20% to dodge the attack, instead take 0 damage. Or 30% to graze it, take half of damage";
		soldier.spell_1 = "Reflection (3 mana): Convert 30% current HP as true damage. Then gains 'Specialist force' in the next turn: Damage taken reduced to 0, and heals for 70% damage you're supposed to take";
		soldier.spell_2 = "Emergency Recuperation: Once in the battle, when HP drops to 0, restores (1000 + 100% damage taken) HP, 3 mana and dodge the next attack (Automatically activated)";
		break;
	case '6':
		std::cout << "You chose Super Idol!";
		soldier.role = "Anh Quoc";
		soldier.quotes = "Didn't miss the rate this time";
		soldier.tags = "Gambler, Self-destruct";
		soldier.nation = "101 Logistic Gang";
		hp = 2200;      ad = 444;
		ap = 0;          ar = 366;
		mr = 244;        rng = 6;
		soldier.talent = "Legend of Tohno: Normal attack receives one of these following buff: Cannot be dodged, deals 200% damage and ignore target's armor, restore 15% max health (can crit for 30% HP) or recover 1 bonus mana.";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +3 base mana";
		soldier.spell_1 = "Serious Mode (2 mana): Immediately deals 600% AD physic damage and 600% AD magic damage to enemy.\nThis skill has 60% chance to fail, instead deals to self 30% max HP. Every 5% missing health increases success chance by 5%.";
		soldier.spell_2 = "Spray and Pray (4 - 12 mana): Rapidly attack an enemy target 6 times, each attack triggers this unit's talent. The mana cost of this skill is randomly modified";
		break;
	case '7':
		std::cout << "You chose Minh Phan!";
		soldier.role = "Minh Phan Dong";
		soldier.quotes = "They suffered on my own account, love to see it. Now, where's the pida?";
		soldier.tags = "Defense, Support";
		soldier.nation = "101 Logistic Gang";
		hp = 2750;      ad = 30;  
		ap = 450;       ar = 420;
		mr = 420;       rng = 7;
		soldier.talent = "Meat Shield: This unit take 20% less damage from all sources\n               Noxious Wound (Unique): When this unit is on the battlefield, inflicts all enemy units with 100% 'Grievous Wound', unlimited duration.";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +70 Armor and +100 Magic resist";
		soldier.spell_1 = "Body Slam (2 mana): Aggressively charges forward, deals 250 + 150% AP magic damage. Against target with 'Bleeding' status, damage increased to 750 + 450% AP";
		soldier.spell_2 = "Haemorrhage (1 mana): Affects the enemy with 'Bleeding', causes the next source of damage deals an additional 20% HP magic damage. Damage from 'Bleeding' ignores 100 magic resist";
		break;
	case '8':
		std::cout << "You chose Bao Duong!";
		soldier.role = "Duong Lee";
		soldier.quotes = "Better call my mama again";
		soldier.tags = "DPS, Survival";
		soldier.nation = "101 Logistic Gang";
		hp = 2350;      ad = 370;
		ap = 0;         ar = 350;
		mr = 270;       rng = 8;
		soldier.talent = "Sword Rain: After every turn, receives 1 Sun Blade, stores up to 4. Every existing Sun Blade increases crit chance by 7%.\nWhenever this unit uses a basic attack, attacks an additional time with each Sun Blade owns";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +10% Armor & Magic penetration";
		soldier.spell_2 = "Five Signs of the Dying Deva (3 mana): Multiplies current Sun Blade by 4, then attack enemy with 15% armor penetration. After this skill ends, removes all Sun Blades and forbids this unit from obtaining Sun Blade this turn";
		soldier.spell_1 = "Menacing Slash (2 mana): Immediately generates 1 Sun Blade, then attack the enemy.\nIf this unit already reached maxium Sun Blades, the attack benefits from 40% omni vamp and deals additional magic damage equals 2% max health each strike";
		break;
	case '9':
		std::cout << "You chose Cong Binh Dap Da!";
		soldier.role = "Phong Vinh";
		soldier.tags = "Defense, DPS, Survival";
		soldier.nation = "101 Logistic Gang";
		soldier.quotes = "One step closer to my new lap, and fumo, and house, and light novel. What do you mean pida? Screw it";
		hp = 2850;      ad = 248;       soldier.shield = 2;
		ap = 0;         ar = 500;       soldier.summonShitcom = true;
		mr = 250;       rng = 9;
		soldier.talent = "Rock Dealer: Starts the battle with 2 'Shield' and gains 1 'Shield' every 4 turns, each shield can block 1 instance of damage.\n               When a shield breaks, restores 20% max health.\n               Range is an Advantage (Unique): Gains bonus attack damage bases on current health's difference betweens this unit and their opponent (Only the highest effect of this type is applied)";
		soldier.talent += "\n               Brother in Arms (Team):When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies 1 'Shield'";
		soldier.spell_1 = "Crag Splitter (3 mana): 'Bind' the target this turn, then deals 260% AD physic damage and restores 9% max health\n(Targets with 'Bind' can not dodge nor graze incoming attack).";
		soldier.spell_2 = "Summon - Shitcom: This unit summons their best tactical equipment to block damage. Shitcom has 2000 health, 200 armor and 0 magic resist.\n               Overheat: Shitcom continously deals 75 true damage to all enemies. When its health drops to 0, explodes and deal 1200 true damage.\n               (Summoning Shitcom doesn't cost mana, but can only activate once)";
		break;
	case 'A': case 'a':
		std::cout << "You chose Luu Bao!";
		soldier.role = "Luu Bao";
		soldier.nation = "The GangZ";
		soldier.tags = "Summon, Nuker, DPS";
		hp = 1880;      ad = 65;        soldier.fructure = 3;
		ap = 350;       ar = 210;
		mr = 350;        rng = 10;
		soldier.talent = "Mechanical Egineer (Unique): Can rapidly manufactures and commands 'Machine' in combat (up to 3).\n               Machine: Costs 1 structure point to deploy and will attack enemy everyturn using their chainsaw (starts with 3 and gains 1 point every 5 turns). Has 1500 HP, 270 attack damage, 90 armor, 1 magic resist and more likely to be attacked.\n               ";
		soldier.talent += "Sneak Shot: Whenever a friendly unit uses their first skill, all Machines attack the target one additional time\n               Emergency Repair: When there is atleast 1 'Machine', normal attack instead heals the machine with least HP for 100% AP";
		soldier.spell_1 = "Chainsaw Extension Module (3 mana): Commands all 'Machine' to attack the enemy, each deals 300% ATK + 4% max HP physic damage. When there're more than 2 'Machine', all 'Machine' attack with 50% armor penetration";
		soldier.spell_2 = "Destruction Mode: All 'Machine' HP +100%, Resistances +200, ATK +170%. After 2 turns, automatically retreat from battle.";
		break;
	case 'B': case 'b':
		std::cout << "You chose Supporter!";
		soldier.role = "Supporter";
		soldier.tags = "Support, Healing";
		soldier.nation = "Royal Warrior";
		hp = 1500;       ad = 0;
		ap = 300;        ar = 150;
		mr = 150;        rng = 11;
		soldier.talent = "Skill Aura - Support (Unique): In teamfight mode, attack instead restores HP of ally equals 100% AP and grants to them 1 mana, self is less likely to be attacked. In solo mode, all skills are locked and can not be used";
		soldier.spell_2 = "Enkephalin (5 mana): Ignores 'Grievous Wound', immediately recovers HP of all allies by 200 + 100% AP and grants to them 1 mana. One targeted ally is bonus healed for 200 + 50% AP";
		soldier.spell_1 = "Adrenaline (3 mana): Attacks an ally for 1000 physic damage. Afterwards, grants to them 100% AD and 100% AP, lasts 2 turn";
		break;
	case 'C': case 'c':
		std::cout << "You chose Withered Phong Vinh!\n\"Lanh cong dai...\"";
		soldier.role = "Alter Vinh";
		soldier.quotes = "These guys should have choosen dualboot, but they didn't. Now that they're regretting it";
		soldier.tags = "Support, Debuff";
		soldier.nation = "Substitute";
		hp = 2740;     ad = 595;	
		ap = 0;        ar = 515;
		mr = 297;       rng = 12;
		soldier.talent  = "Martial Poise: When this unit is on the battlefield, all allies gains +20% ATK and +10% Crit chance\n               Stable Esthesia: Normal attack and ability deal atleast 50% ATK, but can not crit\n               Leg-day: Skipping turn only regains 2 mana";
		soldier.spell_2 = "Harsh Training (3 mana): Removes all bad effects from self or an ally and grants to them 1 'Shield'. Each shield can block 1 instance of damage and restores 20% HP on break";
		soldier.spell_1 = "Radioactive (2 mana): Deals 200 + 150% AD as magic damage to an enemy and inflicts them with 20% 'Fragile' (up to 40% against normal attack), lasts 3 turns.";
		break;
	/*
	case 'd': case 'D':
		std::cout << "You chose Withered Duong Lee!\n\"He's on summer vacation, thus he sleeps\"";
		soldier.role = "Alter Duong";
		hp = 2150;     ad = 70;
		ap = 530;      ar = 100;
		mr = 75;       rng = 13;
		soldier.talent = "Nightmare: Attack against \"Sleeping\" enemies won't interrupt them and deals an additional true damage equals 50% AP + 8% target's HP";
		soldier.spell_1 = "Eternal Spring Dream: Put an enemies into \"Sleep\" in 2 turns, making them unable to attack or use special ability. Taking damage will immediately end their \"Sleeping\" status";
		soldier.spell_2 = "Spiritual Destruction: Attack all enemies, deals 125% AP magic damage and perform an additional attack against \"Sleeping\" target";
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
	soldier.baseAR = ar;            soldier.baseMR = mr;			soldier.baseAP = ap;
	soldier.omniVamp = vamp;        soldier.mana = 3 + mageForce;   soldier.genesisUsed = false;
	soldier.isPlayer = true;        soldier.isEnemy = false;        soldier.isNeutral = false;
	soldier.baseAD = ad;
	soldier.maxHealth = soldier.health;    
	std::cout << "\n" "\nBasic stats:\n" "\n";
	setColor(14);
	std::cout << "Class: " << soldier.role;
	setColor(15);
	std::cout << "\nNation: " << soldier.nation;
	setColor(9);
	std::cout << "\nRole: " << soldier.tags;
	setColor(10);
	std::cout << "\nHealth: " << soldier.health;
	setColor(12);
	std::cout << "\nAttack damage: " << soldier.attackDmg;
	setColor(5);
	std::cout << "\nAbility power: " << soldier.abilityPower;
	setColor(4);
	std::cout << "\nLife steal: " << soldier.omniVamp << "%";
	setColor(6);
	std::cout << "\nArmor: " << soldier.armor;
	setColor(11);
	std::cout << "\nMagic resist: " << soldier.magicRes;
	setColor(15);
	std::cout << "\n\nTalent      >> ";
	setColor(7);
	std::cout << soldier.talent;
	setColor(15);
	std::cout << "\nFirst skill >> ";
	setColor(7);
	std::cout << soldier.spell_1;
	setColor(15);
	std::cout << "\nLast skill  >> ";
	setColor(7);
	std::cout << soldier.spell_2 << std::endl;
	system("pause");

	return soldier;
}

Entities createSoldier(char choice)
{
	Entities soldier;

	int hp = 1, ad = 1, ap = 0, ar = 1, mr = 1, rng = 0, vamp = 0, mageForce = 0;

	switch (choice)
	{
	case '1':
	//	std::cout << "You chose Fighter class!";
		soldier.role = "Fighter";
		soldier.tags = "Support, DPS";
		soldier.nation = "Royal Warrior";
		hp = 2570;       ad = 375;
		ar = 450;        mr = 300;
		rng = 1;
		soldier.talent = "Increasing Danger: Gain bonus damage and lethality base on battle's duration";
		soldier.spell_1 = "Juggernaunt (3 mana): Enhance the weapon and deals physic damage equals 150% AD + 200% bonus AD + 35% target's HP, ignore 50% armor (can not crit)";
		soldier.spell_2 = "Unshakable Solidarity (1 mana): Reduces 90% damage taken this turn and decreases target's armor by 3 + 5%. Then attack with 50% AD";
		break;
	case '2':
	//	std::cout << "You chose Defender class!";
		soldier.role = "Defender";
		soldier.tags = "Survival, Defense, Crowd-control";
		soldier.nation = "Royal Warrior";
		hp = 3500;      ad = 100;
		ar = 650;       mr = 500;
		rng = 2;        ap = 0;
		soldier.talent = "Spiky: Whenever got attacked, reflects 50 (+40% armor) (+40% magic resist) magic damage to the attacker. This damage also benefits from runes\n               Moral Support: If this unit starts the battle in teamfight mode, max HP +15%";
		soldier.spell_1 = "Reinforcement (3 mana): Immediately restore 200 + 20% missing health";
		soldier.spell_2 = "Rock Solid: This ability has 2 uses, bases on what gamemode you're in\nSolo (4 mana): Brandishes the shield, deals (20% max health + 100% armor + 100% magic resist + 25% target's missing health) magic damage\nTeamfight (3 mana): Briefly increases self resistance by 180%, then 'Taunt' and 'Silent' all enemies in 1 turn. 'Taunted' enemies will prioritize attack this unit, regardless of their current state or trait";
		break;
	case '3':
	//	std::cout << "You chose Maskman class!";
		soldier.role = "Maskman";
		soldier.tags = "DPS, Survival";
		soldier.nation = "Royal Warrior";
		hp = 2100;      ad = 580;      vamp = 10;
		ar = 300;       mr = 250;       soldier.critUp = 45;
		rng = 3;        ap = 0;
		soldier.talent = "Sharp Eyes: Crit chance increases to 60% and gains 10% life steal (capped at 50%).\n               Cut Down (Unique): Deals increased damage against target with greater max health than this unit (bonus damage is capped at 100% at 200% greater max health)";
		soldier.spell_1 = "Armor Penetration Crossbow (3 mana): Next attack instead deals 180% damage, ignores 25% armor and guarantee a crit. This attack also benefits with bonus 50 + 15% omnivamp";
		soldier.spell_2 = "Absolute Focus (2 mana): Permanently gain 50 AD and 10% life steal, then attack with 100% AD";
		break;
	case '4':
	//	std::cout << "You chose Caster class!";
		soldier.role = "Caster";
		soldier.tags = "AoE, Nuker";
		soldier.nation = "Royal Warrior";
		hp = 2375;      ad = 55;       mageForce = 3;
		ap = 600;       ar = 250;
		mr = 400;   rng = 4;
		soldier.talent = "Quick Charge (Unique): Normal attacks instead recover 2 mana, this unit also gains 3 bonus mana at the start of battle";
		soldier.spell_1 = "Volcano: Consume all mana, then gain 300 ability power and attacks an enemy with 200% AP. Damage type change to 'True', each mana spent increases damage output by 50 + 20%";
		soldier.spell_2 = "Solo - Genesis: Doesn't attack this round, resistances drop to 0 and take extra 100% damage, but prevents HP from falling below 1. After this skill ends, gains 6 + 1 mana per 75 damage taken. Can only activate once throughout the battle\n               Teamfight - Meteorite (3 mana): Deals 230% AP magic damage to all enemies, damage output is calculated based on the enemy with LEAST magic resist. This damage can not be blocked nor grazed, and can not trigger other effects";
		break;
	case '5':
	//	std::cout << "You chose Specialist class!";
		soldier.role = "Specialist";
		soldier.tags = "Survival";
		soldier.nation = "Self-government Lab";
		hp = 3333;     ad = 200;      soldier.emergencyOn = true;
		ap = 0;        ar = 100;
		mr = 100;       rng = 5;
		soldier.talent = "Camouflage (Unique): 20% to dodge the attack, instead take 0 damage. Or 30% to graze it, take half of damage";
		soldier.spell_1 = "Reflection (3 mana): Convert 30% current HP as true damage. Then gains 'Specialist force' in the next turn: Damage taken reduced to 0, and heals for 70% damage you're supposed to take";
		soldier.spell_2 = "Emergency Recuperation: Once in the battle, when HP drops to 0, restores (1000 + 100% damage taken) HP, 3 mana and dodge the next attack (Automatically activated)";
		break;
	case '6':
	////	std::cout << "You chose Super Idol!";
		soldier.role = "Anh Quoc";
		soldier.quotes = "Didn't miss the rate this time";
		soldier.tags = "Gambler, Self-destruct";
		soldier.nation = "101 Logistic Gang";
		hp = 2200;      ad = 444;
		ap = 0;          ar = 366;
		mr = 244;        rng = 6;
		soldier.talent = "Legend of Tohno: Normal attack receives one of these following buff: Cannot be dodged, deals 200% damage and ignore target's armor, restore 15% max health (can crit for 30% HP) or recover 1 bonus mana.";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +3 base mana";
		soldier.spell_1 = "Serious Mode (2 mana): Immediately deals 600% AD physic damage and 600% AD magic damage to enemy.\nThis skill has 60% chance to fail, instead deals to self 30% max HP. Every 5% missing health increases success chance by 5%.";
		soldier.spell_2 = "Spray and Pray (4 - 12 mana): Rapidly attack an enemy target 6 times, each attack triggers this unit's talent. The mana cost of this skill is randomly modified";
		break;
	case '7':
	//	std::cout << "You chose Minh Phan!";
		soldier.role = "Minh Phan Dong";
		soldier.quotes = "They suffered on my own account, love to see it. Now, where's the pida?";
		soldier.tags = "Defense, Support";
		soldier.nation = "101 Logistic Gang";
		hp = 2750;      ad = 30;
		ap = 450;       ar = 420;
		mr = 420;       rng = 7;
		soldier.talent = "Meat Shield: This unit take 20% less damage from all sources\n               Noxious Wound (Unique): When this unit is on the battlefield, inflicts all enemy units with 100% 'Grievous Wound', unlimited duration.";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +70 Armor and +100 Magic resist";
		soldier.spell_1 = "Body Slam (2 mana): Aggressively charges forward, deals 250 + 150% AP magic damage. Against target with 'Bleeding' status, damage increased to 750 + 450% AP";
		soldier.spell_2 = "Haemorrhage (1 mana): Affects the enemy with 'Bleeding', causes the next source of damage deals an additional 20% HP magic damage. Damage from 'Bleeding' ignores 100 magic resist";
		break;
	case '8':
	//	std::cout << "You chose Bao Duong!";
		soldier.role = "Duong Lee";
		soldier.quotes = "Better call my mama again";
		soldier.tags = "DPS, Survival";
		soldier.nation = "101 Logistic Gang";
		hp = 2350;      ad = 320;
		ap = 0;         ar = 350;
		mr = 270;       rng = 8;
		soldier.talent = "Sword Rain: After every turn, receives 1 Sun Blade, stores up to 4. Every existing Sun Blade increases crit chance by 7%.\nWhenever this unit uses a basic attack, attacks an additional time with each Sun Blade owns";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies +10% Armor & Magic penetration";
		soldier.spell_2 = "Five Signs of the Dying Deva (3 mana): Multiplies current Sun Blade by 4, then attack enemy with 15% armor penetration. After this skill ends, removes all Sun Blades and forbids this unit from obtaining Sun Blade this turn";
		soldier.spell_1 = "Menacing Slash (2 mana): Immediately generates 1 Sun Blade, then attack the enemy.\nIf this unit already reached maxium Sun Blades, the attack benefits from 40% omni vamp and deals additional magic damage equals 2% max health each strike";
		break;
	case '9':
	//	std::cout << "You chose Cong Binh Dap Da!";
		soldier.role = "Phong Vinh";
		soldier.tags = "Defense, DPS, Survival";
		soldier.nation = "101 Logistic Gang";
		soldier.quotes = "One step closer to my new lap, and fumo, and house, and light novel. What do you mean pida? Screw it";
		hp = 2850;      ad = 248;       soldier.shield = 2;
		ap = 0;         ar = 500;       soldier.summonShitcom = true;
		mr = 250;       rng = 9;
		soldier.talent = "Rock Dealer: Starts the battle with 2 'Shield' and gains 1 'Shield' every 4 turns, each shield can block 1 instance of damage.\n               When a shield breaks, restores 20% max health.\n               Range is an Advantage (Unique): Gains bonus attack damage bases on current health's difference betweens this unit and their opponent (Only the highest effect of this type is applied)";
		soldier.talent += "\n               Brother in Arms (Team):When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies 1 'Shield'";
		soldier.spell_1 = "Crag Splitter (3 mana): 'Bind' the target this turn, then deals 260% AD physic damage and restores 9% max health\n(Targets with 'Bind' can not dodge nor graze incoming attack).";
		soldier.spell_2 = "Summon - Shitcom: This unit summons their best tactical equipment to block damage. Shitcom has 2000 health, 200 armor and 0 magic resist.\n               Overheat: Shitcom continously deals 75 true damage to all enemies. When its health drops to 0, explodes and deal 1200 true damage.\n               (Summoning Shitcom doesn't cost mana, but can only activate once)";
		break;
	case 'A': case 'a':
	//	std::cout << "You chose Luu Bao!";
		soldier.role = "Luu Bao";
		soldier.quotes = "The GangZ";
		soldier.tags = "Summon, Nuker, DPS";
		hp = 1880;      ad = 65;        soldier.fructure = 3;
		ap = 350;       ar = 210;
		mr = 350;        rng = 10;
		soldier.talent = "Mechanical Egineer (Unique): Can rapidly manufactures and commands 'Machine' in combat (up to 3).\n               Machine: Costs 1 structure point to deploy and will attack enemy everyturn using their chainsaw (starts with 3 and gains 1 point every 5 turns). Has 1500 HP, 270 attack damage, 90 armor, 1 magic resist and more likely to be attacked.\n               ";
		soldier.talent += "Sneak Shot: Whenever a friendly unit uses their first skill, all Machines attack the target one additional time\n               Emergency Repair: When there is atleast 1 'Machine', normal attack instead heals the machine with least HP for 100% AP";
		soldier.spell_1 = "Chainsaw Extension Module (3 mana): Commands all 'Machine' to attack the enemy, each deals 300% ATK + 4% max HP physic damage. When there're more than 2 'Machine', all 'Machine' attack with 50% armor penetration";
		soldier.spell_2 = "Destruction Mode: All 'Machine' HP +100%, Resistances +200, ATK +170%. After 2 turns, automatically retreat from battle.";
		break;
	case 'B': case 'b':
	//	std::cout << "You chose Supporter!";
		soldier.role = "Supporter";
		soldier.tags = "Support, Healing";
		soldier.nation = "Royal Warrior";
		hp = 1500;      ad = 0;
		ap = 270;       ar = 150;
		mr = 150;        rng = 11;
		soldier.talent = "Skill Aura - Support (Unique): In teamfight mode, attack instead restores HP of ally equals 100% AP and grants to them 1 mana, self is less likely to be attacked. In solo mode, all skills are locked and can not be used";
		soldier.spell_2 = "Enkephalin (5 mana): Ignores 'Grievous Wound', immediately recovers HP of all allies by 200 + 100% AP and grants to them 1 mana. One targeted ally is bonus healed for 200 + 50% AP";
		soldier.spell_1 = "Adrenaline (3 mana): Attacks an ally for 1000 physic damage. Afterwards, grants to them 100% AD and 100% AP, lasts 2 turn";
		break;
	case 'C': case 'c':
	//	std::cout << "You chose Withered Phong Vinh!\n\"Lanh cong dai...\"";
		soldier.role = "Alter Vinh";
		soldier.quotes = "These guys should have choosen dualboot, but they didn't. Now that they're regretting it";
		soldier.tags = "Support, Debuff";
		soldier.nation = "Substitute";
		hp = 2740;     ad = 595;
		ap = 0;        ar = 515;
		mr = 297;       rng = 12;
		soldier.talent = "Martial Poise: When this unit is on the battlefield, all allies gains +20% ATK and +10% Crit chance\n               Stable Esthesia: Normal attack and ability deal atleast 50% ATK, but can not crit\n               Leg-day: Skipping turn only regains 2 mana";
		soldier.spell_2 = "Harsh Training (3 mana): Removes all bad effects from self or an ally and grants to them 1 'Shield'. Each shield can block 1 instance of damage and restores 20% HP on break";
		soldier.spell_1 = "Radioactive (2 mana): Deals 200 + 150% AD as magic damage to an enemy and inflicts them with 20% 'Fragile' (up to 40% against normal attack), lasts 3 turns.";
		break;
		/*
		case 'd': case 'D':
			std::cout << "You chose Withered Duong Lee!\n\"He's on summer vacation, thus he sleeps\"";
			soldier.role = "Alter Duong";
			soldier.quotes = "I promised to show up before 5, but these guys was more troublesome than I thought, it's already 5:49. Hmmm, screw it! Gotta sleep somemore";
			hp = 2150;     ad = 70;
			ap = 530;      ar = 100;
			mr = 75;       rng = 13;
			soldier.talent = "Nightmare: Attack against \"Sleeping\" enemies won't interrupt them and deals an additional true damage equals 50% AP + 8% target's HP";
			soldier.spell_1 = "Eternal Spring Dream: Put an enemies into \"Sleep\" in 2 turns, making them unable to attack or use special ability. Taking damage will immediately end their \"Sleeping\" status";
			soldier.spell_2 = "Spiritual Destruction: Attack all enemies, deals 125% AP magic damage and perform an additional attack against \"Sleeping\" target";
			break;
			*/
	default:
	//	std::cout << "You chose Luu Bao the Corrupting Brain!";
		soldier.role = "Luu Bao the Corrupting Brain";
		soldier.talent = "Ruler of the Galaxy: Luu Bao is the strongest being in the history.\nDue to that, his stats must be reduced to 1 to ensure the balance.";
		soldier.spell_1 = "Unstoppable Force: Luu Bao is already too strong, so there's no need to provide him any skill";
		soldier.spell_2 = "Reincarnation: Consumes all mana to heal for 1 HP. His maxium health also increased by 1!";
		break;
	}

	soldier.health = hp;            soldier.attackDmg = ad;         soldier.abilityPower = ap;
	soldier.armor = ar;             soldier.magicRes = mr;          soldier.range = rng;
	soldier.baseAR = ar;            soldier.baseMR = mr;			soldier.baseAP = ap;
	soldier.omniVamp = vamp;        soldier.mana = 3 + mageForce;   soldier.genesisUsed = false;
	soldier.isPlayer = true;        soldier.isEnemy = false;        soldier.isNeutral = false;
	soldier.baseAD = ad;
	soldier.maxHealth = soldier.health;

	return soldier;
}

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

Entities createDummy()
{
	Entities b;
	b.role = "Dummy";
	b.trait = "A very normal dummy, mostly used for practice purpose. Although these were made with common straw that can be found anywhere, their unreasonable durability is somewhat mysterious and left unanswered";
	b.health = 50000;		b.maxHealth = 50000;
	b.armor = 0;			b.magicRes = 0;
	b.attackDmg = 0;		b.abilityPower = 0;     b.omniVamp = 0;
	b.isPlayer = false;     b.isNeutral = true;     b.isEnemy = true;
	b.range = -1;
	return b;
}

Entities createShitCom()
{
	Entities pc;
	pc.role = "Shitcom";
	pc.health = 3000;       pc.maxHealth = pc.health;
	pc.armor = 500;         pc.magicRes = 1;
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
	machine.abilityPower = 0; machine.attackDmg = 350;
	machine.armor = 300;      machine.magicRes = 100;
	machine.range = 92;       machine.omniVamp = 0;
	machine.isEnemy = false;  machine.isPlayer = true;  machine.isNeutral = true;
	return machine;
}

Entities createGoblinChamp(bool info) {
	srand(time(NULL));
	Entities goblin;
	goblin.role = "Goblin champion";
	goblin.trait = "An extremely dangerous form of goblin. They have been trained through much of battles, their strength and health are outstanding. That being said, goblins normally ain't no such a serious threat to deal with, so maybe it's not as frightening as it seems to be.";
	goblin.health = rand() % (6000 - 4000 + 1) + 4000;
	goblin.attackDmg = 550;												goblin.abilityPower = 0;
	goblin.armor = rand() % (400 - 350 + 1) + 350;                      goblin.magicRes = goblin.armor - 150;
	goblin.isEnemy = true;           goblin.isPlayer = false;           goblin.isNeutral = false;
	goblin.omniVamp = 0;
	goblin.maxHealth = goblin.health;
	goblin.range = 53;
	if (info) printEnemyInfo(&goblin);
	return goblin;
}

Entities createSeniorShaman(bool info) {
	srand(time(NULL));
	Entities goblin;
	goblin.role = "Senior goblin shaman";
	goblin.trait = "A more dangerous form of goblin shaman, they can use heavy-magic to cause serious injuries, thus it's recommended to prioritize attacking them first.\nTalent: Gains 20% magic penetration";
	goblin.attackDmg = 100;                             goblin.omniVamp = 0;
	goblin.armor = rand() % (200 - 150 + 1) + 150;      goblin.magicRes = 300 + goblin.armor;
	goblin.abilityPower = 100 + goblin.magicRes;        goblin.health = rand() % (4000 - 3000 + 1) + 3000;
	goblin.isEnemy = true;      goblin.isPlayer = false;        goblin.isNeutral = false;
	goblin.maxHealth = goblin.health;
	goblin.range = 54;
	if (info) printEnemyInfo(&goblin);
	return goblin;
}

Entities createZombieOrc(bool info) {
	srand(time(NULL));
	Entities orc;
	orc.role = "Zombified Orc";
	orc.trait = "Rotten kind of life-form. Has massive strength and resistance, capable of self-healing bases on damage dealt. However, they gradually lose HP and resistances over time.\nTalent: Attack ignores 40% armor and heals themself for 60% damage dealt, but loses 5% max HP and 20% current resistances every turn\n";
	orc.health = rand() % (12000 - 9000 + 1) + 9000;	  orc.omniVamp = 60;
	orc.attackDmg = rand() % (700 - 600 + 1) + 600;		  orc.magicRes = 575;
	orc.armor = 600;									  orc.abilityPower = 0;
	orc.isEnemy = true;      orc.isPlayer = false;        orc.isNeutral = false;
	orc.maxHealth = orc.health;
	orc.baseAR = orc.armor, orc.baseMR = orc.magicRes;
	orc.range = 55;
	if (info) printEnemyInfo(&orc);
	return orc;
}

Entities createExplosiveSlug(bool info)
{
	Entities slug;
	slug.role = "Explosive Slug";
	slug.trait = "A completely normal slug. What could possibly go wrong?\nCracked Shield: When this unit has more than 50% HP, greatly increases armor and magic resist. When this unit has below 50% health, greatly increases attack damage. Upon death, causes an explosion that deals 400 + 20% target's HP true damage and ignores Shields.\n";
	slug.attackDmg = rand() % (600 - 550 + 1) + 550;    slug.omniVamp = 0;
	slug.armor = rand() % (1150 - 1100 + 1) + 1100;     slug.magicRes = slug.armor * 85 / 100;
	slug.abilityPower = 0;        slug.health = rand() % (8000 - 7000 + 1) + 7000;
	slug.isEnemy = true;          slug.isPlayer = false;        slug.isNeutral = false;
	slug.resistanceBonus = true;
	slug.maxHealth = slug.health;
	slug.range = 57;
	if (info) printEnemyInfo(&slug);
	return slug;
}

Entities createSneaker(bool info)
{
	srand(time(NULL));
	Entities dwarft;
	dwarft.role = "Senior Drawft";
	dwarft.trait = "A tiny, sneaky form of being. A normal drawft is usually weak and easy to be taken down, but this one knows how to exploit their enemy's weaknesses and blindspots, making them much harder to deal with\nTalent: Attack deals extra damage bases on target's missing health. Upon taking damage, has a chance to dodge or graze it!";
	dwarft.health = rand() % (8000 - 7000 + 1) + 7000;  dwarft.omniVamp = 0;
	dwarft.attackDmg = rand() % (500 - 450 + 1) + 450;  dwarft.magicRes = 305;
	dwarft.armor = 420;                                 dwarft.abilityPower = 0;
	dwarft.isEnemy = true;      dwarft.isPlayer = false;        dwarft.isNeutral = false;
	dwarft.maxHealth = dwarft.health;
	dwarft.range = 56;
	if (info) printEnemyInfo(&dwarft);
	return dwarft;
}

Entities createPhantom(bool info)
{
	srand(time(NULL));
	Entities phantom;
	phantom.role = "Phantom";
	phantom.trait = "Unknown creature, has unstable shape and capable of performing their former target's traits\nTrauma: Before the battle, this unit chooses one random playable character and possesses their talent (can not possess talent with 'Unique').";
	phantom.health = rand() % (7000 - 6000 + 1) + 6000; phantom.omniVamp = 0;
	phantom.attackDmg = rand() % (400 - 350 + 1) + 350; phantom.armor = rand() % (380 - 350 + 1) + 350;
	phantom.magicRes = phantom.armor / 2 + 5;           phantom.abilityPower = 0;
	phantom.isEnemy = true;     phantom.isNeutral = false;      phantom.isPlayer = false;
	phantom.maxHealth = phantom.health;
	phantom.range = 58;

	if (info) printEnemyInfo(&phantom);
	return phantom;
}

Entities createSpirit(bool info)
{
	srand(time(NULL));
	Entities spirit;
	spirit.role = "Vengeful Spirit";
	spirit.trait = "Some reports about their existance has been confirmed a long time ago, their infamous kill potential is notable as they will attack anything within their sight. No one had an idea what made them so aggressive, but they all agree that challenging them while your lifeforce is not strong enough will guarantee a death sentence\n\"A spirit, a soul, a phantasm,... Whatever it's called, this thing is definitely not pleasant at all.\"";
	spirit.trait += "\nEmotional Adsorption: At the start of battle and after every 5 turns, this unit marks their opponent, attack against marked target deals 18% max health's magic damage. Aftec 3 turns, the mark activates, steals away 6 mana from its target and restores 888 HP. Target that has less than aforementioned quantity will take 9999 true damage.";
	spirit.health = rand() % (7900 - 7000 + 1) + 7000;        spirit.omniVamp = 0;
	spirit.attackDmg = 0;                                     spirit.armor = rand() % (700 - 650 + 1) + 650;
	spirit.magicRes = spirit.armor - 300;                     spirit.abilityPower = rand() % (300 - 250 + 1) + 250;
	spirit.isEnemy = true;     spirit.isNeutral = false;      spirit.isPlayer = false;
	spirit.maxHealth = spirit.health;
	spirit.range = 59;

	if (info) printEnemyInfo(&spirit);
	return spirit;
}

Entities createChimera(bool info)
{
	srand(time(NULL));
	Entities chimera;
	chimera.role = "Chimera";
	chimera.trait = "A monstrous creature with parts from multiple animals, capable of switching form during battle\n\nTwilight: This unit has 2 unique form - 'Predator' and 'Divine Beast' (always starts the battle in 'Divine Beast' form) - and swaps between them every 5 turns.\n\nPredator: Has increased armor, gains 573 physic damage and extra critical chance, critical attack instead deals 250% damage (400% against target with less than 50% health). Before swapping form, 'Bind' their target then attacks with 1000 damage, ignores 60% armor and heals for 200% damage dealt\n\nDivine Beast: Attack damage drops to 0, gains 535 ability power and increased magic resist, attack against target with higher than 50% health deals an additional 16% current health damage. Before swapping form, removes all good effects from their opponent.\n";
	chimera.health = rand() % (20000 - 18000 + 1) + 18000;       chimera.omniVamp = 0;
	chimera.attackDmg = 0;                                       chimera.armor = rand() % (300 - 250 + 1) + 250;
	chimera.magicRes = chimera.armor + 400;                      chimera.abilityPower = 535;
	chimera.isEnemy = true;     chimera.isNeutral = false;       chimera.isPlayer = false;
	chimera.maxHealth = chimera.health;                          chimera.divine = true;
	chimera.range = 100;
	chimera.baseAR = chimera.armor;								 chimera.baseMR = chimera.armor;
	if (info) printEnemyInfo(&chimera);
	return chimera;
}

Entities createAplha(bool info)
{
	srand(time(NULL));
	Entities alpha;
	alpha.role = "Henry Fat";
	alpha.trait = "A living creature with a humanoid appearance. Due to that, they can easily approach their target and slowly murder them using their poison. As the poison is faint, most of their victim won't recognize it until they're all collapsed and their death will be noted as 'Unexplained fever'. Eerie!\nWarm Welcome: Immediately deals 30% max health true damage and ignores 'Shield' at the start of the battle to all friendly units\nNeurotoxin: Attack poisons non-summoned target, deals 200-500 magic damage bases on missing health and applies 60% 'Grievous Wound' every turn in 3 turns. This unit won't attack 'Poisoning' targets. Targets that can not be poisoned instead take 400% damage\nSpace Out: When there isn't any target to attack, Resistances +250% and restores 500 HP each turn.";
	alpha.health = rand() % (7777 - 6666 + 1) + 6666;          alpha.omniVamp = 0;
	alpha.attackDmg = 320;                                     alpha.armor = rand() % (400 - 350 + 1) + 350;
	alpha.magicRes = alpha.armor * 4 / 10;                     alpha.abilityPower = 0;
	alpha.isEnemy = true;     alpha.isNeutral = false;         alpha.isPlayer = false;
	alpha.maxHealth = alpha.health;                            alpha.welcome = true;
	alpha.baseAR = alpha.armor, alpha.baseMR = alpha.magicRes;
	alpha.range = 60;

	if (info) printEnemyInfo(&alpha);
	return alpha;
}

Entities createSinger(bool info)
{
	srand(time(NULL));
	Entities singer;
	singer.role = "The Singer";
	singer.trait = "Unknown entity, unclear background, no recent report was found, but there's once a myth about a mysterious creature that shares the same properties with this one:\nThey appear in a black coat, humming an unknown yet pleasing melody. They travel from place to place, bringing their songs to anywhere they came\nEveryone in the country felt in love with these songs, they sang it in every party, celebration or even around the campfire.\nThose days was really enjoyable, but the fun never lasts too long\nJust a few months later, war occurred.\nThe strange thing is, all soldiers in that country - for some reasons - lost all the will to fight, to defense their own hometown. Their bodies no longer response, they could barely pick up their weapon.\nWhat happened next is just the whole tragedy: the vanguards couldn't swing their swords, archers couldn't string their bows. They stood there, looked at the battlefield, stared at eachothers, whispered some weird words, before getting crushed\nEveryone knew that they're dead meat, yet they didn't run, resist, or even felt scared.\nInstead, they started singing...\n\n\"At the end of it all, consciousness began to escape from my mind\nI saw the town I once hated riddled with holes, but this brought me no joy\nThere, I see a wandering traveler\nI hear a strange song, yet somewhat familiar\nI see our mountains\"\n\nDuetto: Attack applies 20% 'Fragile' in 2 turns (Target with 'Fragile' has to take more damage, bonus damage is calculated based on the exact amount).\nEncore: When a 'Fragile' effect runs out, has 50% chance for it to reset the duration.\nHymn of Respite: Becomes \"Low-altitude Hovering\" (can not be targeted), effect lasts until this unit enters \"Soloist\" form\nSoloist: When this unit is the only enemy alive, ATK +20%, attack now deals AoE damage and ignores up to 25% magic resist\nDeaf to all but the Song: Upon death, resurrects all fallen enemies (excluding self), restores 100% of their HP and applies 'Fragile' to all friendly units in 10 turns.";
	singer.health = 12345;									   singer.omniVamp = 0;
	singer.attackDmg = 30;                                     singer.armor = 600;
	singer.magicRes = 750;									   singer.abilityPower = 325;
	singer.isEnemy = true;     singer.isNeutral = false;       singer.isPlayer = false;
	singer.maxHealth = singer.health;						   singer.baseAP = 350;
	singer.baseAR = singer.armor;							   singer.baseMR = singer.magicRes;
	singer.range = 61;										   singer.floating = true;
	if (info) printEnemyInfo(&singer);
	return singer;
}

Entities createShinigami(bool info)
{
	srand(time(NULL));
	Entities reaper;
	reaper.role = "Reaper";
	reaper.trait = "The most ancient so-called creature that has been existed for centuries. With the scythe that has tasted many deaths by their \"hands\", they'll take away the life of even the most fragile creature. Their appearance may appears modern, yet the method they use is primitive at their root: Always go for the weaks first\n";
	reaper.trait += "Scythe: Attack prioritizes non-summoned target with least HP, regardless of their likelihood of being targetted\nReap: In the 4th turn and every 3 turns afterwards, performs an AoE attack that deals 133% ATK and deals extra physic damage equivalent to 100% target's missing health (won't surpass 399% ATK). If this attack takes down atleast 1 non-summon target, this unit will immediately recast it";
	reaper.health = rand() % (10000 - 9000 + 1) + 9000;        reaper.omniVamp = 0;
	reaper.attackDmg = 555;                                    reaper.armor = rand() % (500 - 450 + 1) + 450;
	reaper.magicRes = reaper.armor * 6 / 10;                   reaper.abilityPower = 0;
	reaper.isEnemy = true;     reaper.isNeutral = false;       reaper.isPlayer = false;
	reaper.maxHealth = reaper.health;						   reaper.baseAP = 0;
	reaper.baseAR = reaper.armor;							   reaper.baseMR = reaper.magicRes;
	reaper.range = 62;
	if (info) printEnemyInfo(&reaper);
	return reaper;
}

Entities createFree(bool info)
{
	srand(time(NULL));
	Entities Free;
	Free.role = "Free";
	Free.trait = "A creature that loves to wander around and has no stable behaviour. Due to the fact that no one has ever been attacked by this creature, it is essentially harmless if you don't disturb it. However, further reports showed that it does help increasing the amount of other monsters by healing and saving them. So it looks like you have no other choice...\n\"They don't seem to adore any commonsense at all\""; 
	Free.trait += "\nWaiting Game: Starts the battle in 'Standby' mode and doesn't attack, but continously heals other enemies for 750 HP each turn, this healing is unaffected by 'Grievous Wound' and will increase its value up to 100% against target with less than 50% max HP, further increase to 200% if the target is below 25% HP.\nUnbound: After being injured, enters 'Combat-ready' mode and start attacking, each attack follows with a shockwave that deals magic damage equals 50% ATK. Every 15% HP loss increases the amount of shockwave by 1";
	Free.health = rand() % (8000 - 7000 + 1) + 7000;           Free.omniVamp = 0;
	Free.attackDmg = 420;									   Free.armor = rand() % (550 - 500 + 1) + 500;
	Free.magicRes = Free.armor - 150;						   Free.abilityPower = 0;
	Free.isEnemy = true;     Free.isNeutral = false;           Free.isPlayer = false;
	Free.maxHealth = Free.health;						       Free.baseAP = 0;
	Free.baseAR = Free.armor;							       Free.baseMR = Free.magicRes;
	Free.range = 63;										   Free.standBy = true;
	if (info) printEnemyInfo(&Free);
	return Free;
}

Entities createPosKnight(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Enraged Possessed Soldier";
	knight.trait = "Used to be normal soldier, but has completely given in to primal madness as their lifeforce is consumed. The appearance of such an aberration on the battllefield is almost beyond imagination\n\"Something fell down from their pocket, it's a letter written by hand, yet impossible to read\"\nFinal Warcry: Has extremely high ATK and gradually loses HP overtime";
	knight.health = rand() % (8000 - 7000 + 1) + 7000;         knight.omniVamp = 0;
	knight.attackDmg = rand() % (1800 - 1750 + 1) + 1750;      knight.armor = rand() % (600 - 560 + 1) + 560;
	knight.magicRes = knight.armor * 13 / 10 + 15;             knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.ARpen = 15;
	knight.range = 64;
	if (info) printEnemyInfo(&knight);
	return knight;
}

Entities createPosKnight_L(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Enraged Possessed Bone-Thrower";
	knight.trait = "Used to be normal archer, but has completely given in to primal madness as their lifeforce is consumed. They will even rip out anything inside their bodies to throw because of their deadened sense of pain\n\"That bow laying on the ground seems completely broken down, there's a name inscribed on it\"\nFinal Warcry: Has ridiculously high ATK, increased crit chance and armor penetration. Gradually loses even more HP overtime";
	knight.health = rand() % (6000 - 5500 + 1) + 5500;         knight.omniVamp = 0;
	knight.attackDmg = rand() % (2200 - 2100 + 1) + 2100;      knight.armor = rand() % (400 - 390 + 1) + 390;
	knight.magicRes = knight.armor * 13 / 10 + 15;             knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.ARpen = 25;										   knight.critUp = 25;
	knight.range = 65;
	if (info) printEnemyInfo(&knight);
	return knight;
}

Entities createCorKnight(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Corrupted Bladeweaver";
	knight.trait = "A warrior that can not be seen or summoned using regular methods. Few reports show that they usually come in pair, and serve under a mysterious blade wielder.\nTheir loyalty is absolute and known as unshakable. Should their master ever needs their help, they'll even sacrifice their own life in order to support him\nCommand - Meltdown: First attack of this unit permanently decreases target's armor by 40% and removes all current buffs on them. Whenever \"Emperors' Blade - The Pursuer\" is injured, drains 15% of self HP to heal him for an equivalent amount";
	knight.health = rand() % (7000 - 6000 + 1) + 6000;         knight.omniVamp = 0;
	knight.attackDmg = rand() % (800 - 650 + 1) + 650;         knight.armor = rand() % (750 - 720 + 1) + 720;
	knight.magicRes = knight.armor + 200;					   knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.ARpen = 15;										   knight.firstStrike = true;
	knight.range = 102;
	if (info) printEnemyInfo(&knight);
	return knight;
}

Entities createCorKnight_L(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Corrupted Wolrdcruser";
	knight.trait = "A caster that can not be seen or summoned using regular methods. Few reports show that they usually come in pair, and serve under a mysterious blade wielder.\nTheir loyalty is absolute and known as unshakable. Should their master ever needs their help, they'll even sacrifice their own life in order to support him\nCommand - Meltdown: First attack of this unit deals true damage and removes all mana of its target. Whenever \"Emperors' Blade - The Pursuer\" attacks, drains 10% of self HP to deal an equivalent amount of magic damage to its target";
	knight.health = rand() % (6000 - 5000 + 1) + 5000;         knight.omniVamp = 0;
	knight.attackDmg = 0;									   knight.armor = rand() % (550 - 520 + 1) + 520;
	knight.magicRes = knight.armor + 400;				       knight.abilityPower = rand() % (1100 - 1050 + 1) + 1050;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.ARpen = 15;										   knight.firstStrike = true;
	knight.range = 103;
	if (info) printEnemyInfo(&knight);
	return knight;
}

Entities createPosDef(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Possessed Heavy Defender";
	knight.trait = "A heavy defender that has been controlled by an unknown entity, capable of regenerating rapidly. Well-protected by elite tactical gear, the appearance of such an aberration on the battlefield is almost beyond imagination.\n\nShield-up: Has extremely high armor. Regenerates 5% max HP every turn and ignores 'Grievous Wound'. Every 3 turns, taunts all non-summed friendly units, forces them to use a normal attack against this unit";
	knight.health = rand() % (10000 - 8500 + 1) + 8500;        knight.omniVamp = 0;
	knight.attackDmg = rand() % (300 - 200 + 1) + 200;         knight.armor = rand() % (900 - 850 + 1) + 850;
	knight.magicRes = rand() % (300 - 250 + 1) + 250;          knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.range = 66;
	if (info) printEnemyInfo(&knight);
	return knight;
}

Entities createMutant()
{
	srand(time(NULL));
	Entities slug;
	slug.role = "Mutant Crawler";
	slug.trait = "One of \"Essece of Evolution\"'s proudest creature. Though tiny and squishy, they boast incredible destructive power and can rapidly refunction their body system as long as their creator still remains.";
	slug.trait += "\nRetain, restrict, retreat and repeat: Attack of this unit permanently decreases target's ATK. While \"Essence of Evolution\" and its evolution forms still persist, this unit is refreshed periodically.\nRefresh: Has their HP restored to full even if they're dead.";
	slug.health = 1222;										 slug.omniVamp = 0;
	slug.attackDmg = 700;									 slug.armor = 100;
	slug.magicRes = 600;									 slug.abilityPower = 0;
	slug.isEnemy = true;       slug.isNeutral = false;       slug.isPlayer = false;
	slug.maxHealth = slug.health;						     slug.baseAP = 0;
	slug.baseAR = slug.armor;							     slug.baseMR = slug.magicRes;
	slug.ARpen = 40;										 slug.range = 151;
	return slug;
}

Entities createEssence(bool info)
{
	srand(time(NULL));	
	Entities essence;
	essence.role = "Essence of Evolution";
	essence.trait = "A madman who should not have stepped upon this world. An oddity that should not have existed in the other world. The union of the two gave birth to this node of \"evolution\" that far surpasses the limits of biology. It's existence naturally contradicts all of the world. It should not live. It must not live.";
	essence.trait += "\n\nGlorious Evolution: Reduce true damage taken from abilities by 25%. This unit evolves and enters a different form after a certain amount of HP is loss. Each form has its own effect and changes this unit's behaviours.\n\n\"Newborn\": Starts the battle in \"Newborn\" form. During this state, gains immunity to magic damage, has attack damage and ability power increases by 60% and 30%, respectively. Gradually restores 800 HP each turn.";
	essence.trait += "\n\n\"Evolution\": Upon HP drops to 0 in \"Newborn Form\", evolves and enters \"Evolution Form\". During this state, gains immunity to physic damage, attack damage and ability power increases by 40% and 80%, respectively. Periodically, spawns a \"Mutant Crawler\". If one already existed, refreshes them instead.";
	essence.trait += "\n\n\"Perfect\": Upon HP drops to 0 in \"Evolution Form\", evolves and enters its final form. During this state, both armor and magic resist is greatly increased, but gradually loses HP over time. Attack instead releases a shockwave that deals 800 true damage to all allied units. Periodically, spawns two \"Mutant Crawler\" and refreshes those already existed.\n";
	essence.health = 8888;										   essence.omniVamp = 0;
	essence.attackDmg = 500;									   essence.armor = 650;
	essence.magicRes = 650;									       essence.abilityPower = 500;
	essence.isEnemy = true;     essence.isNeutral = false;         essence.isPlayer = false;
	essence.maxHealth = essence.health;						       essence.baseAP = 0;
	essence.baseAR = essence.armor;							       essence.baseMR = essence.magicRes;
	essence.range = 150;										   essence.baseAD = 500, essence.baseAP = 500;
	if (info) printEnemyInfo(&essence);
	essence.magicRes = 9999;
	essence.attackDmg = 500 * 16 / 10;
	essence.abilityPower = 500 * 13 / 10;
	return essence;
}

Entities createBlade(bool info)
{
	srand(time(NULL));
	Entities knight;
	knight.role = "Emperors' Blades";
	knight.trait = "A manifestation of a certain will. The most terrifying military force, they are widely-known throughout the world only as horrifying spectres of legend and yore. A single one is enough to slaughter entire squads. Defeat has never been a possibility.\n\"They are, in fact, a walking catastrophe\"\n";
	knight.trait += "\nDominion: Attack ignores a certain amount of defense and applies 'Fragile' to target with less than 50% HP, damage is increased dramatically when attack 'Fragile' target. Every attack permanently increases this unit's ATK, up to a total 5 times\nCollapsing Fear: All allied units are inflicted with 60% 'Grievous Wound' for a permanent duration. The first time HP drops to 0, immediately recovers all HP and enters \"Pursuer\" phase, gains greatly increased stats.\nDuring \"Pursuer\" phase, refreshes 'Grievous Wound' debuff and casts \"Collapsing Fear\" periodically, deals physic damage to all allied units, and attacks check its target's HP to apply 'Fragile' an additional time, after they have received the damage.";
	knight.health = 12500;									   knight.omniVamp = 0;
	knight.attackDmg = 900;									   knight.armor = 555;
	knight.magicRes = 799;									   knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAD = knight.attackDmg;						   knight.stack = 5;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.range = 101;										   knight.ARpen = 50;
	if (info) printEnemyInfo(&knight);
	char detail;
	setColor(6);
	printf("\nView further details (Y/N)? ");
	setColor(11);
	std::cin >> detail;
	setColor(7);
	if (detail == 'Y' || detail == 'y')
	{
		setColor(12);
		std::cout << "\nATK gains: +80 per stack (+400 at max)\nArmor penetration: 50%\n'Fragile' increased damage: 300% base damage\n\nDuring second phase:\n\"Pursuer\" phase's health: 21500";
		std::cout << "\nATK buff: +300\nArmor buff: +222\nResistance buff: +200\n\"Collapsing Fear\" casts: whenever current turn is divisible by 3\n\"Collapsing Fear\" scales = 80% ATK\n";
		system("pause");
	}
	return knight;
}

Entities shitcom = createBlankTarget(), machineA = createBlankTarget(), machineB = createBlankTarget(), machineC = createBlankTarget();

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

char avoidRetardCharInput(std::string notif, std::string exceptions)
{
	bool isContainedInException = false;
	char userInput;
	std::cout << notif;
	std::cin >> userInput;
	for (int i = 0; i < exceptions.size(); i++)
	{
		if (exceptions[i] == userInput)
		{
			isContainedInException = true;
			break;
		}
	}
	return userInput;
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
		target->SpiritMark = 0;
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
		if (target->SpiritMark)
		{
			setColor(5);
			target->adrenaile > 0 || target->poisoned || target->fragile > 0 ? printf("  Marked: ") : (percentHP == 100 ? printf("   Marked: ") : percentHP >= 10 ? printf("    Marked: ") : printf("     Marked: "));
			target->SpiritMark >= 2 ? std::cout << target->SpiritMark << " turns left until the mark activates" : std::cout << "activates in the next turn";
		}
	}
	printf("\n\n");
	setColor(7);
}

void bleedingDmg(Entities* target, Entities* caster)
{	
	int reducedMR = target->magicRes * (100 - caster->MRpen) / 100 - 100;
	if (reducedMR < 0) reducedMR = 0;
	int damageTaken2 = damageOutput(0, reducedMR, 0, target->maxHealth * 20 / 100);
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

void dealingDamage(Entities* attacker, Entities* gotAttacked, bool specialForce, bool fighterWill, int playerHealth, int enemyMaxHealth, bool painSupress, bool anhquocSupremacy) {
	if (attacker->role == "blank" || attacker->role == "Dummy") return;
	int damageTaken = !painSupress ? damageOutput(gotAttacked->armor * (100 - attacker->ARpen) / 100, gotAttacked->magicRes * (100 - attacker->ARpen) / 100, (*attacker).attackDmg, (*attacker).abilityPower) : damageOutput(0, 0, (*attacker).attackDmg, (*attacker).abilityPower);

	//Maskman talent
	if (attacker->range == 3)
	{
		int healthDifference = gotAttacked->maxHealth - attacker->maxHealth, dif_20PercentHP = attacker->maxHealth / 5;
		int bonusDmg = healthDifference / dif_20PercentHP;
		bonusDmg > 10 ? bonusDmg = 10 : bonusDmg < 0 ? bonusDmg = 0 : bonusDmg;
		damageTaken += damageTaken * (bonusDmg * 10) / 100;
	}

	//Enemy normal attack effect
	if (attacker->range == 101 && gotAttacked->fragile) damageTaken *= 3;
	
	if (attacker->stack > 0)
	{
		attacker->attackDmg += 80;
		attacker->baseAD += 80;
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
	else if ((*attacker).role == "Senior goblin shaman") damageTaken = damageOutput((*gotAttacked).armor, (*gotAttacked).magicRes * 8 / 10, (*attacker).attackDmg, (*attacker).abilityPower);
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
			!(attacker->challengeMode) ? damageTaken += damageOutput(0, gotAttacked->magicRes, 0, gotAttacked->health * 16 / 100) : damageTaken += gotAttacked->health * 16 / 100;
		}
	}
	else if (attacker->range == 60)
	{
		!(gotAttacked->isNeutral) ? std::cout << gotAttacked->role << " is poisoned in the next 3 turns!\n", gotAttacked->poisoned = 3 : damageTaken *= 4;
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
		if (criticalStrike <= 15 + attacker->critUp && attacker->range != 8 && attacker->range != 12 && attacker->range != -1)
		{
			setColor(12);
			printf("CRITICAL STRIKE! The damage dealt is doubled up!\n");
			setColor(7);
			attacker->predatorMode ? (gotAttacked->health >= gotAttacked->maxHealth / 2 ? damageTaken *= 25 / 10 : damageTaken *= 4) : damageTaken *= 2;
			if (attacker->exploit) damageTaken += 135 + damageTaken / 10;
		}

		if (attacker->range == 63) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, (attacker->attackDmg / 2) * (attacker->shockwave));
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

			if (attacker->omniVamp >= 40) damageTaken += damageOutput(0, gotAttacked->magicRes, 0, enemyMaxHealth / 10);
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

		if (gotAttacked->fragile > 0) damageTaken = gotAttacked->isPlayer ? damageTaken * 12 / 10 : damageTaken * 14 / 10;

		//AlterVinh talent
		if (attacker->range == 12 && damageTaken < (attacker->abilityPower + attacker->attackDmg) / 2) damageTaken = (attacker->abilityPower + attacker->attackDmg) / 2;

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
				setColor(12);
				std::cout << (10 - 8 + weirdFlex) * 10 << "%\n";
				setColor(7);
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
			setColor(2);
			std::cout << restore << " health!\n";
			setColor(7);
			gotAttacked->health + restore <= gotAttacked->maxHealth ? gotAttacked->health += restore : gotAttacked->health = gotAttacked->maxHealth;
			gotAttacked->shield--;
		}

		//Life steal
		int healing = lifeSteal(damageTaken, (*attacker).omniVamp);
		if (attacker->poisoned > 0) healing = healing * 4 / 10;

		//Minh phan's bleeding effect & talent
		if ((*gotAttacked).bleeding) bleedingDmg(gotAttacked, attacker);

		if (gotAttacked->range == 7 || gotAttacked->possessTalent == 7 || gotAttacked->possessTalent2 == 7) damageTaken = damageTaken * 8 / 10;

		//Fighter's skill 2
		if (fighterWill || gotAttacked->fighter)
		{
			(*attacker).isEnemy ? damageTaken /= 10 : damageTaken /= 2;
		}

		//Damage dealt
		(*gotAttacked).health -= damageTaken;

		if (attacker->role == "Emperors' Blade - The Pursuer" && gotAttacked->health < gotAttacked->maxHealth / 2) gotAttacked->fragile = 10;

		//Minh Phan's passive
		if ((*attacker).healingBanned) healing = 0;

		//If the healing went beyond unit's max health, it's set to their max health
		if ((*attacker).isPlayer) (*attacker).health = ((*attacker).health + healing > attacker->maxHealth ? attacker->maxHealth : (*attacker).health + healing);
		else (*attacker).health = (*attacker).health + healing > enemyMaxHealth ? enemyMaxHealth : (*attacker).health + healing;

		//Send damage output
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

		//Caster skill 2 activation
		if (painSupress || gotAttacked->antiDeath)
		{
			(*gotAttacked).health < 1 ? (*gotAttacked).health = 1 : (*gotAttacked).health;
			int manaBuff = 6 + damageTaken / 75;
			std::cout << "Due to the damage taken, you receive ";
			setColor(11);
			std::cout << manaBuff << " mana!\n";
			setColor(7);
			(*gotAttacked).mana += manaBuff;
			(*gotAttacked).genesisUsed = true;
		}

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
			int damageReflect = damageOutput(0, attacker->magicRes, 0, 30 + gotAttacked->armor / 4 + gotAttacked->magicRes / 4);
			damageReflect = runeDmg(attacker, gotAttacked, damageReflect);
			(*attacker).health -= damageReflect;
			std::cout << gotAttacked->role << " reflected to " << (*attacker).role << " ";
			setColor(5);
			std::cout << damageReflect << " damage!\n";
			setColor(7);
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

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
		//Next attack deals 180% damage and guarantee a crit, ignore 25% armor. Then briefly gains 15% lifesteal
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		int heal = damageTaken * 15 / 100 + 50 + lifeSteal(damageTaken, (*caster).omniVamp);
		if (caster->poisoned > 0) heal = heal * 4 / 10;

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
		/*
		Consume all Mana to use
		Converts 200% physic damage to ability power, attacks deals true damage. Each mana spent increases damage by 30 + 20%
																															*/
		caster->mana += 3;
		damageTaken = damageOutput(0, 0, 0, caster->abilityPower + 150) * 2;
		int Sto = damageTaken;
		while (caster->mana > 0)
		{
			damageTaken += 50 + Sto / 5;
			caster->mana--;
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

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
				std::cout << shieldHeal << " health!", setColor(7);
				target->health += shieldHeal;
				target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
			}

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
			std::cout << "\nThis ability also triggered ";
			setColor(12);
			std::cout << "'Bleeding'";
			setColor(7);
			std::cout << " effect, deals an additional ";
			setColor(5);
			std::cout << damageTaken2 << " damage!\n";
			setColor(7);
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

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
			setColor(11);
			std::cout << caster->role << " obtained 1 Sun Blade!\n";
			setColor(7);
			caster->sunBlade++;
			dealingDamage(&(*caster), &(*target), 0, 0, caster->health, 0, 0, 0);
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
			caster->omniVamp = 40;
			dealingDamage(&(*caster), &(*target), 0, 0, caster->health, maxHP, 0, 0);
			caster->omniVamp = 0;
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}
		
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

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
	switch ((*caster).range)
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
			std::cout << shieldHeal << " health!", setColor(7);
			target->health += shieldHeal;
			target->health > target->maxHealth ? target->health = target->maxHealth : target->health = target->health;
		}

		(*target).health -= damageTaken;
		std::cout << caster->role << " brandished your shield and dealt ";
		setColor(5);
		std::cout << damageTaken << " damage!\n";
		setColor(7);
		if (target->bleeding) bleedingDmg(target, caster);
		break;
	}
	case 3:
	{
		caster->baseAD += 50, caster->attackDmg += 50;          
		(*caster).omniVamp = (*caster).omniVamp + 10 > 50 ? 50 : (*caster).omniVamp + 10;
		std::cout << caster->role << "'s attack damage is now increased to ";
		setColor(12);
		std::cout << (*caster).attackDmg;
		setColor(7);
		std::cout << "\nLife-steal is increased to ";
		setColor(4);
		std::cout << (*caster).omniVamp << "%\n";
		setColor(7);
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
		printf("This unit doesn't need such of thing, they will perform a normal attack instead\n");
		dealingDamage(&(*caster), &(*target), false, false, playerHealth, 0, false, 0);
		break;
	}
	case 6:
	{
		setColor(12);
		std::cout << "Anh Quoc performs a bunch of auto attacks!\n", setColor(7);
		for (int i = 0; i < 6; i++) dealingDamage(&(*caster), &(*target), false, false, playerHealth, 0, false, false);
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
		dealingDamage(&(*caster), &(*target), 0, 0, caster->health, 0, 0, 0);
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
				setColor(14);
				std::cout << caster->role, setColor(7);
				std::cout << " dealt to ", setColor(14);
				std::cout << target1->role, setColor(5);
				std::cout << " " << damageTaken << " damage!\n", setColor(7);
				caster->damageDealt += damageTaken;
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
				setColor(14);
				std::cout << caster->role, setColor(7);
				std::cout << " dealt to ", setColor(14);
				std::cout << target2->role, setColor(5);
				std::cout << " " << damageTaken << " damage!\n", setColor(7);
				caster->damageDealt += damageTaken;
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
				setColor(14);
				std::cout << caster->role, setColor(7);
				std::cout << " dealt to ", setColor(14);
				std::cout << target3->role, setColor(5);
				std::cout << " " << damageTaken << " damage!\n", setColor(7);
				caster->damageDealt += damageTaken;
			}
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
					else if (target->range == 7) damageDeal = damageDeal * 8 / 10;
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

bool skipTurnBanned = false;

void playerChoice(Entities* player, Entities* ally1, Entities* ally2, Entities* enemy1, Entities* enemy2, Entities* enemy3)
{
	srand(time(NULL));

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
		case 3:
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
				Entities* machineHealed = nullptr;
				short currentMachineHP;
				setColor(14);
				std::cout << player->role;
				setColor(7);
				std::cout << " healed the machine with least HP for ";
				setColor(2);
				std::cout << player->abilityPower << " HP!\n";
				setColor(7);
				if (machineA.health < machineB.health && ((machineA.health < machineC.health && machineC.health > 0) || (machineA.health > machineC.health && machineC.health <= 0)) && machineA.health > 0)
				{
					currentMachineHP = machineA.health;
					machineA.health + player->abilityPower > 1500 ? machineA.health = 1500 : machineA.health += player->abilityPower;
					machineHealed = &machineA;
				}
				else if (machineB.health < machineA.health && ((machineB.health < machineC.health && machineC.health > 0) || (machineB.health > machineC.health && machineC.health <= 0)) && machineB.health > 0)
				{
					currentMachineHP = machineB.health;
					machineB.health + player->abilityPower > 1500 ? machineB.health = 1500 : machineB.health += player->abilityPower;
					machineHealed = &machineB;
				}

				else if (machineC.health > 0)
				{
					currentMachineHP = machineC.health;
					machineC.health + player->abilityPower > 1500 ? machineC.health = 1500 : machineC.health += player->abilityPower;
					machineHealed = &machineC;
				}

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
						machineHealed->health = currentMachineHP;
						machineHealed = nullptr;
						free(machineHealed);
						goto currentChoice;
						break;
					}
					else
					{
						machineHealed = nullptr;
						free(machineHealed);
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
}

int minHealth(Entities* player1, Entities* player2, Entities* player3)
{
	if (((player1->health <= player2->health && player2->health > 0) || (player1->health > player2->health && player2->health <= 0)) && ((player1->health <= player3->health && player3->health > 0) || (player1->health > player3->health && player3->health <= 0)) && player1->health > 0) return 1;
	else if (((player2->health <= player1->health && player1->health > 0) || (player2->health > player1->health && player1->health <= 0)) && ((player2->health <= player3->health && player3->health > 0) || (player2->health > player3->health && player3->health <= 0)) && player2->health > 0) return 2;
	else return 3;
}

short risk = 0, pack = 0;

void collectDiary(Entities* enemy, Entities* player)
{
	std::ofstream diaryData("saves\\diary.dat", std::ofstream::out | std::ios::app);
	std::string dataInput;
	
	if (enemy->role == "Goblin champion") dataInput = "RC_1_CLR";
	else if (enemy->role == "The Singer") dataInput = "RC_2_CLR";
	else if (enemy->range == 100) dataInput = "RC_4_CLR";
	else dataInput = "RC_3_CLR";

	diaryData << '\n' << dataInput;
	diaryData.close();
}

void collectData(Entities* enemy, Entities* player1, Entities* player2, Entities* player3)
{	
	std::ifstream convertFile("saves\\data.dat");
	std::ofstream backupFile("saves\\ditmeluubao.dat");
	std::string convertData;
	while (convertFile >> convertData)
	{
		backupFile << convertData << '\n';
	}
	convertFile.close();
	backupFile.close();
	
	std::ifstream dataIn("saves\\ditmeluubao.dat");
	std::ofstream storeData("saves\\data.dat");
	std::string currentLine, wordToReplace;
	byte lineNumber = 0;
	switch (pack)
	{
	case 1:
		wordToReplace = "P1";
		break;
	case 2:
		wordToReplace = "P2";
		break;
	case 3:
		wordToReplace = "P3";
		break;
	case 4:
		wordToReplace = "P4";
		break;
	case 5:
		wordToReplace = "P5";
		break;
	case 6:
		wordToReplace = "P6";
		break;
	case 7:
		wordToReplace = "P7";
		break;
	}
	while (dataIn >> currentLine)
	{
		std::string ifSuperior = currentLine;
		lineNumber++;
		if (lineNumber == pack)
		{
			std::string newReplacement = "NR";
			if (risk > 0) newReplacement = "RS";
			else if (enemy->challengeMode) newReplacement = "CM";

			if (ifSuperior == "RS") newReplacement = "RS";
			else if (ifSuperior == "CM" && newReplacement == "NR") newReplacement = "CM";

			storeData << newReplacement << '\n';
		}
		else
		{
			storeData << currentLine << '\n';
		}
	}
	dataIn.close();
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

	Entities* luubao, * pvinh, * anhQuoc , * duongLe, * minhphan, *supporter, *fighter, *caster, * defender, * alter;
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

	Entities* slug, * chimera, * phantom, * zombieOrc, * spirit, * henryFat, * singer, * shinigami, * Free, * en_soldier, * en_leader, *pos_def, *em_blade, * EoE, *cor_blade = nullptr, *cor_cas = nullptr;
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
			Sleep(3000);
			setColor(12);
			printf("\n\nSoloist: The Singer no longer possess \"Low-altitude hovering\", has significantly increased ATK and inflicts AoE attacks\n");
			singer->solo = true;
			singer->floating = false;
			singer->baseAP = 100 + singer->baseAP * 12 / 10, singer->abilityPower = singer->baseAP;
			singer->MRpen = 25;
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
					marked->SpiritMark = 3;
					setColor(13);
					std::cout << spirit->role << " marked " << marked->role << "! In the next 2 turns, this unit is more vulnerable to damage!\n", setColor(7);
				}
				if (marked && marked->SpiritMark == 1)
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
					marked->SpiritMark = 0;
					setColor(7);
				}
				else if (marked && marked->SpiritMark > 0)
				{
					marked->health > 0 ? marked->SpiritMark-- : marked->SpiritMark = 0;
				}
			}
			else
			{
				player1->SpiritMark = 0;
				player2->SpiritMark = 0;
				player3->SpiritMark = 0;
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
																												
		if (turn % 5 == 0 && turn != 0)
		{
			if (luubao && luubao->range == 10 && luubao->fructure < 3 && luubao->health > 0)
			{
				setColor(11);
				std::cout << "Luu Bao gained 1 Structure point!\n";
				setColor(7);
				luubao->fructure++;
				system("pause");
			}

			if (chimera && chimera->health > 0)
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
					!(singer&& singer->challengeMode) ? chimera->attackDmg = 573 : chimera->attackDmg = 573 * 15 / 10;
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
					!(singer&& singer->challengeMode) ? chimera->abilityPower = 535 : chimera->abilityPower = 535 * 15 / 10;
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
		}

		if (pos_def && pos_def->health > 0 && turn % 3 == 2)
		{
			setColor(14);
			std::cout << pos_def->role << " taunts all allies this turn!\n", setColor(7);
			player1->taunt = 1, player2->taunt = 1, player3->taunt = 1;
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

		//5k+ lines go go

		Entities* targeto = nullptr;

		//Enemies attack

		system("pause");

		if (Free && Free->health > 0)
		{
			(Free->health < Free->maxHealth && Free->standBy) || Free->taunt > 0 ? Free->standBy = false, Free->combat = true : 1;
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
				defender->armor = defender->baseAR + 200, defender->magicRes = defender->baseMR + 200;
				dealingDamage(enemy1, defender, 0, 0, defender->health, enemy1->maxHealth, 0, 0);
				defender->armor = defender->baseAR, defender->magicRes = defender->baseMR;
				enemy1->taunt--;
			}

			if (em_blade) em_blade->abilityPower = 0;
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
					!(singer) ? slug->attackDmg += 800 : slug->attackDmg += 1200;
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
				std::cout << "Shitcom slight burnt, deals to all enemies 75 damage!\n", setColor(7);
				enemy1->health -= 75, enemy2->health -= 75, enemy3->health -= 75;
			}
			else
			{
				setColor(14);
				std::cout << "OVERHEAT! Shitcom performed an explosion, deals to all enemies 1200 true damage!\n", setColor(7);
				enemy1->health -= 1200, enemy2->health -= 1200, enemy3->health -= 1200;
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
				if (em_blade->challengeMode)
				{
					*enemy2 = createCorKnight(0);
					*enemy3 = createCorKnight_L(0);
					cor_blade = enemy2;
					cor_cas = enemy3;
				}
			}

			if (em_blade->turn % 3 == 2 && !instaDelete)
			{
				setColor(8);
				std::cout << "Without a trace...\n";
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
			std::cout << "Stay determined! Fighter gained 30 attack damage and subtract all enemy's armor by 15!", setColor(7);
			fighter->baseAD += 30, fighter->attackDmg += 30;
			enemy1->baseAR -= 15, enemy1->armor -= 15;
			enemy2->baseAR -= 15, enemy2->armor -= 15;
			enemy3->baseAR -= 15, enemy3->armor -= 15;
		}

		if (phantom && (phantom->possessTalent == 1 || phantom->possessTalent2 == 1) && phantom->health > 0)
		{
			setColor(6);
			std::cout << "Stay chaotic! Phantom gained 30 attack damage and subtract all friendly unit's armor by 8!", setColor(7);
			phantom->baseAD += 30, phantom->attackDmg += 30;
			player1->baseAR -= 8, player1->armor -= 8;
			player2->baseAR -= 8, player2->armor -= 8;
			player3->baseAR -= 8, player3->armor -= 8;
		}
	    
		if (phantom && (phantom->possessTalent == 8 || phantom->possessTalent2 == 8) && phantom->sunBlade < 2 && phantom->health > 0)
		{
			setColor(9);
			std::cout << phantom->role << " obtained 1 Moon Blade!", setColor(7);
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

		turn++,
			enemy1->turn++,
				enemy2->turn++,
					enemy3->turn++;

		if (towerMode)
		{
			if (enemy1->health <= 0 && enemy2->health <= 0 && enemy3->health <= 0)
			{
				towerRound++;
				player1->shield++, player2->shield++, player3->shield++;
				/////////////////////////////////////////////////////////////////////////////////////////////////////																									
				* enemy1 = createBlankTarget(), * enemy2 = createBlankTarget(), * enemy3 = createBlankTarget();
				zombieOrc = nullptr;			pos_def = nullptr;
				singer = nullptr;				en_leader = nullptr;
				Free = nullptr;					en_soldier = nullptr;
				spirit = nullptr;				slug = nullptr;
				em_blade = nullptr;				EoE = nullptr;
				chimera = nullptr;				shinigami = nullptr;
				henryFat = nullptr;
																													
				std::vector<short> randomStuff;
				if (towerRound <= 5)
				{
					for (int j = 1; j <= 5; j++) randomStuff.push_back(j);
				}
				else
				{
					for (int j = 4; j <= 11; j++) randomStuff.push_back(j);
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
							break;
						case 8:
							*resurrectEnemy = createShinigami(0);
							shinigami = resurrectEnemy;
							break;
						case 6:
							*resurrectEnemy = createFree(0);
							Free = resurrectEnemy;
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
							break;
						case 10:
							*resurrectEnemy = createPosDef(0);
							pos_def = resurrectEnemy;
							break;
						default:
							*resurrectEnemy = createPosKnight_L(0);
							en_leader = resurrectEnemy;
							break;
					}
				}
				resurrectEnemy = nullptr;
				free(resurrectEnemy);
				setColor(12);
				std::cout << "\nNew challengers appeared: " << enemy1->role << " / "<< enemy2->role << " / " << enemy3->role << ".\n\n";
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
																																	
	machineA = createBlankTarget(); machineB = createBlankTarget(); machineC = createBlankTarget(); shitcom = createBlankTarget();
	* player1 = createBlankTarget(), * player2 = createBlankTarget(), * player3 = createBlankTarget();
	* enemy1 = createBlankTarget(), * enemy2 = createBlankTarget(), * enemy3 = createBlankTarget();
	system("pause");
}

int turn = 0;

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
	std::cout << "\nSelect combat mode:\n1. Solo\n2. 3v3-Custom: Feel free to choose your units and enemies\n3. 3v3-Packed mode: Enemies units are locked and can not be changed, but you can experience enemies that can not be challenged normally\n4. 3v3 - Tower mode: Starts off normally, but wait, why do these enemies keep spawning...\n???. Stay tune, something wicked this way comes...\nOthers. Return to main menu\nYour choice: ";
	setColor(11);
	std::cin >> modoChoice;
	
	while (std::cin.fail() || modoChoice > 4 || modoChoice < 1)
	{
		std::cin.clear();
		std::cin.ignore();
		setColor(12);
		std::cout << "\nInvalid input! Recommend trying again";
		std::cout << "\nSelect combat mode:\n1. Solo\n2. 3v3-Custom: Feel free to choose your units and enemies\n3. 3v3-Packed mode: Enemies units are locked and can not be changed, but you can experience enemies that can not be challenged normally\n4. 3v3 - Tower mode: Starts off normally, but wait, why do these enemies keep spawning...\nOthers. Return to main menu\nYour choice: ";
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

void mainMenu()
{
	PlaySound(TEXT("ost\\lobby.wav"), NULL, SND_ASYNC | SND_LOOP);
	setColor(6);
	std::cout << "Welcome to \"Benh Vien Cut Dai Nhiet Hach\"!\n1. Start now\n2. Diary\n3. How to play?\nOthers: Exit\nChoose action: ";
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
		printf("\nShort answer: your pp\nLong answer: your mom\n\n");
		break;
	default:
		setColor(6);
		printf("\nWhat a pity, cya!\n");	
		setColor(10);
		system("pause");
		runningProgram = false;
	}
}

int main() {
	SetConsoleTitle(TEXT("Nicho5, gem turn base không đồ họa dễ nhất mọi thời đại!"));
	std::cout << "Loading menu, please wait...";
	Sleep(2000);
	system("cls");
	while (runningProgram) {
		printf("\n");
		mainMenu();
	}
	//dit me quoc anh
	return 0;
}