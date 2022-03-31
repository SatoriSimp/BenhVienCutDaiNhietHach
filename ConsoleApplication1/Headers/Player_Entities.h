#pragma once

Entities createSoldier() {
	srand(time(NULL));
	std::string randomChar = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c' };

	setColor(BO_RED);
	std::cout << "\nChoose unit's role:\n";

	std::vector<char> solSymbol = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'R' };
	std::vector<std::string> solName = { "Fighter", "Defender", "Maskman", "Caster", "Specialist", "Anh Quoc", "Minh Phan", "Duong Le", "Phong Vinh", "Luu Bao", "Supporter", "Alter Vinh", "Random character" };
	std::vector<std::string> solDes = { "Starts off mediocre, but will slowly dominate the entire battlefield as the fight goes on", "Have increased HP and Resistances by sacrificing their own damage", "High attack damage, easier to obtain a critical strike and has healing potential, but somewhat squishy", "Insane strong damage burst on single target, or decent AoE damage", "Decent stats and less likely to be attacked", "Recommend for whoever wishes to test their luck", "Destroy the battlefield with his own weight", "For people who has no brain and prefers using normal attacks", "Be still, as a mountain, yet no maidens", "Uses quantity to destroy quality", "Provides decent healing and utility", "Applies buff and debuff, repeatively", "Pick any playable character" };

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
		soldier.spell_2 = "Haemorrhage (1 mana): Affects the enemy with 'Bleeding'. This effect has no duration and will last until being activated";
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
		soldier.talent = "Rock Dealer: Starts the battle with 2 'Shield' and gradually gains 1 'Shield' for every 4 turns from where the battle starts.\n               Range is an Advantage (Unique): Gains bonus attack damage bases on current health's difference betweens this unit and their opponent (Only the highest effect of this type is applied)";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies 1 'Shield'";
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
		soldier.talent = "Martial Poise: When this unit is on the battlefield, all allies gains +20% ATK and +10% Crit chance\n               Stable Esthesia: Normal attack and ability deal atleast 50% ATK, but can not crit\n               Leg-day: Skipping turn only regains 2 mana";
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
		soldier.spell_2 = "Haemorrhage (1 mana): Affects the enemy with 'Bleeding'. This effect has no duration and will last until being activated";
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
		soldier.talent = "Rock Dealer: Starts the battle with 2 'Shield' and gradually gains 1 'Shield' every 4 turns from where the battle starts.\n               Range is an Advantage (Unique): Gains bonus attack damage bases on current health's difference betweens this unit and their opponent (Only the highest effect of this type is applied)";
		soldier.talent += "\n               Brother in Arms (Team): When all friendly units are part of \"101 Logistic Gang\", grants to self and other allies 1 'Shield'";
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
