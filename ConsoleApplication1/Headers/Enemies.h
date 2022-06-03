#pragma once

//blank target: a pseudo object, mostly used to trick function that requires "class" agruments
//have no meaningful purpose otherwise
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

Entities createGoblinChamp(bool info) {
	srand(time(NULL));
	Entities goblin;
	goblin.role = "Goblin champion";
	goblin.trait = "An extremely dangerous form of goblin. They have been trained through much of battles, their strength and health are outstanding. That being said, goblins normally ain't no such a serious threat to deal with, so maybe it's not as frightening as it seems to be.";
	goblin.health = rand() % (6000 - 4000 + 1) + 4000;
	goblin.attackDmg = 550;												goblin.abilityPower = 0;
	goblin.armor = rand() % (500 - 450 + 1) + 450;                      goblin.magicRes = goblin.armor - 250;
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
	goblin.armor = rand() % (300 - 250 + 1) + 250;      goblin.magicRes = 400 + goblin.armor;
	goblin.abilityPower = 100 + goblin.magicRes;        goblin.health = rand() % (4000 - 3000 + 1) + 3000;
	goblin.MRpen = 20;
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
	orc.trait = "Rotten kind of life-form. Has massive strength and resistance, capable of self-healing bases on damage dealt. However, they gradually lose HP and resistances over time.\n\nRemnant Ash: Attack ignores 40% armor and heals themself for 60% damage dealt, but loses 5% max HP and 20% current resistances every turn\n";
	orc.health = rand() % (11000 - 10500 + 1) + 10500;	  orc.omniVamp = 60;
	orc.attackDmg = rand() % (700 - 650 + 1) + 650;		  orc.magicRes = 400;
	orc.armor = 700;									  orc.abilityPower = 0;
	orc.ARpen = 40;
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
	slug.trait = "\"Slug\" in this world is nowhere to be small and harmless. Instead, one referrs to a chunky creature that you'd never wish to mess with.\nNow, what could be the worst scenario when encountering a slug? How serious of a threat that one can pose?\nEver thought about a mutant slug, carries tons of unstable-explosive chemical stuffs inside their body? Bet you do now!\n\nHeat-up: Gains increased attack damage bases on missing health\nCracked Shield: Starting from 50% HP and below, \"Heat-up\" also provides an increment in resistances\nUnstable Plasma: Upon death, causes an explosion that deals 1000 true damage to all allied units.\n";
	slug.attackDmg = rand() % (600 - 550 + 1) + 550;		slug.omniVamp = 0;
	slug.armor = rand() % (550 - 500 + 1) + 500;			slug.magicRes = slug.armor / 2;
	slug.abilityPower = 0;									slug.health = 9500;
	slug.isEnemy = true;          slug.isPlayer = false;    slug.isNeutral = false;
	slug.maxHealth = slug.health;							slug.baseAD = slug.attackDmg;
	slug.baseAR = slug.armor;								slug.baseMR = slug.magicRes;
	slug.range = 57;
	if (info) printEnemyInfo(&slug);
	return slug;
}

Entities createSneaker(bool info)
{
	srand(time(NULL));
	Entities dwarft;
	dwarft.role = "Senior Drawft";
	dwarft.trait = "A tiny, sneaky form of being. A normal drawft is usually weak and easy to be taken down, but this one knows how to exploit their enemy's weaknesses and blindspots, making them much harder to deal with\n\nSneak: Attack deals extra damage bases on target's missing health. Upon taking damage, has a chance to dodge or graze it!\n";
	dwarft.health = rand() % (8000 - 7000 + 1) + 7000;		dwarft.omniVamp = 0;
	dwarft.attackDmg = rand() % (500 - 450 + 1) + 450;		dwarft.magicRes = 200;
	dwarft.armor = 420;										dwarft.abilityPower = 0;
	dwarft.isEnemy = true;      dwarft.isPlayer = false;    dwarft.isNeutral = false;
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
	phantom.trait = "Unknown creature, has unstable shape and capable of performing their former target's traits\n\nTrauma: Before the battle, this unit chooses one random playable character and possesses their talent (can not possess talent with 'Unique').\n";
	phantom.health = rand() % (7000 - 6500 + 1) + 6500;			phantom.omniVamp = 0;
	phantom.attackDmg = rand() % (550 - 520 + 1) + 520;			phantom.armor = 450;
	phantom.magicRes = phantom.armor * 6 / 10;					phantom.abilityPower = 0;
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
	spirit.trait = "Their body has decayed and returned to the wild. What's left now is a chained will, a bare essence that got jealous just by seeing any living creature who has a thing they can no longer have. Their whole purpose is to kill, and they're dead serious: Challenging them while your lifeforce is not strong enough guarantees nothing but a death sentence.\n\"A spirit, a soul, a phantasm,... Whatever it's called, this thing is definitely not pleasant at all.\"";
	spirit.trait += "\n\nEmotional Absorption: At the start of battle and after every 5 turns, this unit marks their opponent, attack against marked target deals 18% max health's magic damage. Aftec 3 turns, the mark activates, steals away 6 mana from its target and restores 888 HP. Target that has less than required quantity will take 9999 true damage.\n";
	spirit.health = rand() % (7900 - 7600 + 1) + 7600;        spirit.omniVamp = 0;
	spirit.attackDmg = 0;                                     spirit.armor = rand() % (700 - 650 + 1) + 650;
	spirit.magicRes = spirit.armor - 450;                     spirit.abilityPower = rand() % (300 - 250 + 1) + 250;
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
	chimera.trait = "A monstrous creature with parts from multiple animals, capable of switching form during battle\n\nTwilight: This unit has 2 unique form - 'Predator' and 'Divine Beast' (always starts the battle in 'Divine Beast' form) - and swaps between them every 5 turns.\nPredator: Has increased armor, gains 573 physic damage and extra critical chance, critical attack instead deals 250% damage (400% against target with less than 50% health). Before swapping form, 'Bind' their target then attacks with 1000 damage, ignores 60% armor and heals for 200% damage dealt\nDivine Beast: Attack damage drops to 0, gains 535 ability power and increased magic resist, attack against target with higher than 50% health deals an additional 16% current health damage. Before swapping form, removes all good effects from their opponent.\n";
	chimera.health = rand() % (20000 - 19500 + 1) + 19500;       chimera.omniVamp = 0;
	chimera.attackDmg = 0;                                       chimera.armor = rand() % (400 - 350 + 1) + 350;
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
	alpha.trait = "An enormous creature with a humanoid appearance. Thanks to that, they can easily approach their target and inflicts them with a mysterious neurotoxin and not even the most intense medical treatment was enough to fully nullify its toxicity. The progress happens slowly yet insanely painful, but most of their victim won't recognize it at first, until they're all collapsed. Their fleshes then melt and vamporize, and their death will be noted as 'Unexplained fever'. No one wants to witness that scenario, afterall.\n\nWarm Welcome: Immediately deals 30% max health true damage and ignores 'Shield' at the start of the battle to all friendly units\nNeurotoxin: Attack poisons non-summoned target, deals 200-500 magic damage bases on missing health and applies 60% 'Grievous Wound' every turn in 3 turns. This unit won't attack 'Poisoning' targets. Targets that can not be poisoned instead take 400% damage\nSpace Out: When there isn't any target to attack, Resistances +250% and restores 500 HP each turn.\n";
	alpha.health = rand() % (8500 - 8000 + 1) + 8000;          alpha.omniVamp = 0;
	alpha.attackDmg = 420;                                     alpha.armor = rand() % (400 - 350 + 1) + 350;
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
	singer.trait = "Unknown entity, unclear background, no recent report was found, but there's once a myth about a mysterious creature that shares the same properties with this one:\nThey appear in a black coat, humming an unknown yet pleasing melody. They travel from place to place, bringing their songs to anywhere they came\nEveryone in the country felt in love with these songs, they sang it in every party, celebration or even around the campfire.\nTime passed over, after that traveller left the town for a really long time, war occurred: a conflict betweem two nations, common story.\nYet, the strange thing is, all soldiers in that country - for some reasons - lost all the will to fight, to defense their own hometown. Their bodies no longer response, they could barely pick up their weapon.\nWhat happened next is just the whole stage of tragedy: vanguards couldn't swing their swords, archers couldn't string their bows. They dead standing there, looked at the battlefield, stared at eachothers, whispered some weird words, before getting crushed by enemies' fire power.\nEveryone knew that they're dead meat, yet they didn't run, resist, or even felt scared.\nInstead, they started singing...\n\n\"At the end of it all, consciousness began to escape from my mind\nI saw the town I once hated riddled with holes, but this brought me no joy\nThere, I see a wandering traveler\nI hear a strange song, yet somewhat familiar\nI see our mountains\"\n\nAblities:\n\nDuetto: Attack applies 20% 'Fragile' in 2 turns.\nEncore: When a 'Fragile' effect runs out, has 50% chance for it to reset the duration.\nHymn of Respite: Becomes \"Low-altitude Hovering\", effect lasts until this unit enters \"Soloist\" form\nSoloist: When this unit is the only enemy alive, ATK +20%, attack now deals AoE damage and ignores up to 25% magic resist\nDeaf to all but the Song: Upon death, resurrects all fallen enemies (excluding self), restores 100% of their HP and applies 'Fragile' to all friendly units in 10 turns.";
	singer.health = 12345;									   singer.omniVamp = 0;
	singer.attackDmg = 30;                                     singer.armor = 600;
	singer.magicRes = 600;									   singer.abilityPower = 350;
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
	reaper.trait = "The most ancient so-called creature that has been existed for centuries. Equipped with the scythe that has tasted many deaths, they'll take away the life of even the most fragile creature. Their appearance may appears modern, yet the method they use is primitive at their root: Always go for the weaks first\n";
	reaper.trait += "\nScythe: Attack prioritizes non-summoned target with least HP, regardless of their likelihood of being targetted\nReap: In the 4th turn and every 3 turns afterwards, performs an AoE attack that deals 133% ATK and deals extra physic damage equivalent to 100% target's missing health (won't surpass 399% ATK). If this attack takes down atleast 1 non-summon target, this unit will immediately recast it.\n";
	reaper.health = rand() % (10000 - 9500 + 1) + 9500;        reaper.omniVamp = 0;
	reaper.attackDmg = 555;                                    reaper.armor = rand() % (500 - 450 + 1) + 450;
	reaper.magicRes = reaper.armor - 200;					   reaper.abilityPower = 0;
	reaper.baseAD = 555;
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
	Free.trait += "\n\nWaiting Game: Starts the battle in 'Standby' mode and continously heals other enemies for 750 HP each turn, this healing is unaffected by 'Grievous Wound' and will increase its value up to 100% against target with less than 50% max HP, further increase to 200% if the target is below 25% HP.\nBreak the Chain: After being injured, enters 'Combat-ready' mode, magic resist increased by 500 and starts attacking, each attack follows with a shockwave that deals magic damage equals 50% ATK. Every 15% HP loss increases the amount of shockwave by 1.\n";
	Free.health = rand() % (8000 - 7500 + 1) + 7500;           Free.omniVamp = 0;
	Free.attackDmg = 460;									   Free.armor = rand() % (650 - 600 + 1) + 600;
	Free.magicRes = 0;									   Free.abilityPower = 0;
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
	knight.trait = "Used to be normal soldier, but has completely given in to primal madness as their lifeforce is consumed. The appearance of such an aberration on the battllefield is almost beyond imagination\n\"Something fell down from their pocket, it's a letter written by hand, yet impossible to read\"\n\nFinal Warcry: Has extremely high ATK and gradually loses HP overtime.\n";
	knight.health = rand() % (11000 - 10500 + 1) + 10500;      knight.omniVamp = 0;
	knight.attackDmg = rand() % (1800 - 1750 + 1) + 1750;      knight.armor = rand() % (400 - 350 + 1) + 350;
	knight.magicRes = 600;									   knight.abilityPower = 0;
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
	knight.trait = "Used to be normal archer, but has completely given in to primal madness as their lifeforce is consumed. They will even rip out anything inside their bodies to throw because of their deadened sense of pain\n\"That bow laying on the ground seems completely broken down, there's a name inscribed on it\"\n\nFinal Warcry: Has ridiculously high ATK, increased crit chance and armor penetration. Gradually loses even more HP overtime.\n";
	knight.health = rand() % (9500 - 9000 + 1) + 9000;         knight.omniVamp = 0;
	knight.attackDmg = rand() % (2200 - 2100 + 1) + 2100;      knight.armor = rand() % (250 - 200 + 1) + 200;
	knight.magicRes = 550;									   knight.abilityPower = 0;
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
	knight.trait = "A warrior that can not be seen or summoned using regular methods. Few reports show that they usually come in pair, and serve under a mysterious blade wielder.\nTheir loyalty is absolute and known as unshakable. Should their master ever needs their help, they'll even sacrifice their own life in order to support him\n\nCommand - Meltdown: First attack of this unit permanently decreases target's armor by 40% and removes all current buffs on them. Whenever \"Emperors' Blade - The Pursuer\" is injured, drains 15% of self HP to heal him for an equivalent amount.\n";
	knight.health = rand() % (8000 - 7500 + 1) + 7500;         knight.omniVamp = 0;
	knight.attackDmg = rand() % (800 - 650 + 1) + 650;         knight.armor = rand() % (750 - 720 + 1) + 720;
	knight.magicRes = knight.armor - 500;					   knight.abilityPower = 0;
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
	knight.trait = "A caster that can not be seen or summoned using regular methods. Few reports show that they usually come in pair, and serve under a mysterious blade wielder.\nTheir loyalty is absolute and known as unshakable. Should their master ever needs their help, they'll even sacrifice their own life in order to support him\n\nCommand - Meltdown: First attack of this unit deals true damage and removes all mana of its target. Whenever \"Emperors' Blade - The Pursuer\" attacks, drains 10% of self HP to deal an equivalent amount of magic damage to the target.\n";
	knight.health = rand() % (6000 - 5500 + 1) + 5500;         knight.omniVamp = 0;
	knight.attackDmg = 0;									   knight.armor = rand() % (450 - 420 + 1) + 420;
	knight.magicRes = knight.armor + 350;				       knight.abilityPower = rand() % (1100 - 1050 + 1) + 1050;
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
	Entities defender;
	defender.role = "Possessed Heavy Defender";
	defender.trait = "A heavy defender that has been controlled by an unknown entity, capable of regenerating rapidly. Well-protected by elite tactical gear, the appearance of such an aberration on the battlefield is almost beyond imagination.\n\nForm-up: Has extremely high armor. Regenerates 5% max HP every turn and ignores 'Grievous Wound'. Every 3 turns, taunts all non-summed friendly units, forces them to use a normal attack against this unit.\n";
	defender.health = rand() % (9000 - 8500 + 1) + 8500;				defender.omniVamp = 0;
	defender.attackDmg = rand() % (300 - 250 + 1) + 250;				defender.armor = rand() % (1100 - 1050 + 1) + 1050;
	defender.magicRes = rand() % (300 - 250 + 1) + 250;					defender.abilityPower = 0;
	defender.isEnemy = true;     defender.isNeutral = false;			defender.isPlayer = false;
	defender.maxHealth = defender.health;								defender.baseAP = 0;
	defender.baseAR = defender.armor;									defender.baseMR = defender.magicRes;
	defender.range = 66;
	if (info) printEnemyInfo(&defender);
	return defender;
}

Entities createPhaCleaver(bool info)
{
	srand(time(NULL));
	Entities cleaver;
	cleaver.role = "Phalanx Soulcleaver";
	cleaver.trait = "A \"phalanx\" type humanoid object that's specialized in melee combat. Even though their strength is somewhat run of the mill, the injuries they inflict are paranormal, makes it nigh impossible for the victims to recover, thus leaves them wide open and become extremely vunerable to attack.\nThe name \"Phalanx\" of theirs seems heavily inspired from a well-known ancient combat formation. Marching alongside, they strengthen the will of eachother, making them significantly harder to deal with.\n";
	cleaver.trait += "\nSoulcleaver: Attack permanently deducts target's max health, proportional to damage dealt.\nEnomotia: When in effect, gains greatly increased attack damage.\n";
	cleaver.health = rand() % (10500 - 10000 + 1) + 10000;			cleaver.omniVamp = 0;
	cleaver.attackDmg = rand() % (800 - 750 + 1) + 750;				cleaver.armor = rand() % (500 - 450 + 1) + 450;
	cleaver.magicRes = 700;											cleaver.abilityPower = 0;
	cleaver.isEnemy = true;     cleaver.isNeutral = false;			cleaver.isPlayer = false;
	cleaver.maxHealth = cleaver.health;								cleaver.baseAP = 0;
	cleaver.baseAR = cleaver.armor;									cleaver.baseMR = cleaver.magicRes;
	cleaver.ARpen = 0;												cleaver.critUp = 0;
	cleaver.range = 67;												cleaver.baseAD = cleaver.attackDmg;
	if (info) printEnemyInfo(&cleaver);	
	return cleaver;
}

Entities createPhaShooter(bool info)
{
	srand(time(NULL));
	Entities shooter;
	shooter.role = "Phalanx Heavyshooter";
	shooter.trait = "A \"phalanx\" type humanoid object that's specialized in ranged combat. Using crossbow-like weapon, they slit through the enemy's defense with high accuracy point-blank shots, makes blocking means nothing to them.\nThe name \"Phalanx\" of theirs seems heavily inspired from a well-known ancient combat formation. Marching alongside, their morale will peak, causing them to inflict even more destruction.\n";
	shooter.trait += "\nHeavyshooter: Attack can not critical and delivers 3 instances of damage in a rapid successsion, each is counted as a separated hit.\nEnomotia: When in effect, attack strikes an additional hit and ignores up to 50% armor.\n";
	shooter.health = rand() % (8500 - 8000 + 1) + 8000;				shooter.omniVamp = 0;
	shooter.attackDmg = rand() % (480 - 470 + 1) + 470;				shooter.armor = rand() % (400 - 350 + 1) + 350;
	shooter.magicRes = 600;										shooter.abilityPower = 0;
	shooter.isEnemy = true;     shooter.isNeutral = false;			shooter.isPlayer = false;
	shooter.maxHealth = shooter.health;								shooter.baseAP = 0;
	shooter.baseAR = shooter.armor;									shooter.baseMR = shooter.magicRes;
	shooter.ARpen = 0;												shooter.critUp = -15;
	shooter.range = 68;
	if (info) printEnemyInfo(&shooter);
	return shooter;
}

Entities createPhaPioneer(bool info)
{
	srand(time(NULL));
	Entities pioneer;
	pioneer.role = "Phalanx Pioneer";
	pioneer.trait = "A \"phalanx\" type humanoid object that's specialized in covering the advance of their enemies. Protecting their allies with arts, they will make sure they're the only one handling enemies' firepower.\nThe name \"Phalanx\" of theirs seems heavily inspired from a well-known ancient combat formation. Marching alongside, their solidarity is insurmountable.\n";
	pioneer.trait += "\nEnomotia: When in effect, cover other \"Phalanx\" enemies with \"Camouflage\", making them impossible to be directly targeted.\n";
	pioneer.health = rand() % (13000 - 12500 + 1) + 12500;         pioneer.omniVamp = 0;
	pioneer.attackDmg = 300;									   pioneer.armor = rand() % (900 - 850 + 1) + 850;
	pioneer.magicRes = 500;										   pioneer.abilityPower = 0;
	pioneer.isEnemy = true;     pioneer.isNeutral = false;         pioneer.isPlayer = false;
	pioneer.maxHealth = pioneer.health;							   pioneer.baseAP = 0;
	pioneer.baseAR = pioneer.armor;								   pioneer.baseMR = pioneer.magicRes;
	pioneer.ARpen = 0;											   pioneer.critUp = 0;
	pioneer.range = 69;
	if (info) printEnemyInfo(&pioneer);
	return pioneer;
}

Entities createSwarm()
{
	Entities swarm;
	swarm.role = "Assimilator, Will of the Swarm";
	swarm.trait = "Its existence is the pure contradiction between \"Enternity\" and \"Transient\", which has far surpassed the humanity's knowledge. By consuming the lifeforce of any living creature, reborn and adopt the victim's mannerisms, then turns back to the primary form without any scratch, they simply can not be defeated.\n\"I know I had to kill it! I know that was my duty! However,... however, how could I have the urge to do so, while that thing is forming into the shape of my son?\"\n\nHesitation: After the first attack, attack inflicts true damage equivalent to 20% target's max health\nAthanasios: Reduces damage taken by 99%. Upon being defeated, this unit will survive and transform into a random enemy or back to themselves, the process can be repeated indefinitely!\n";

	swarm.health = 100;												swarm.maxHealth = swarm.health;
	swarm.attackDmg = 150;											swarm.abilityPower = 150;
	swarm.armor = 0;												swarm.magicRes = 0;
	swarm.isEnemy = true, swarm.isNeutral = false, swarm.isPlayer = false;
	swarm.baseAR = swarm.armor;										swarm.baseMR = swarm.magicRes;
	swarm.ARpen = 0;												swarm.MRpen = 0;
	swarm.critUp = -15;												swarm.range = -100;
	swarm.stack = 1;												swarm.healingBanned = true;
	return swarm;
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
	knight.trait += "\nSet the Stage: First attack instead casts \"Collapsing Fear\" with increased damage, can only happen once.\nDominion: All allied units are permanently inflicted with 60% 'Grievous Wound'. Attack ignores a certain amount of defense, each attack permanently increases this unit's ATK, up to a total of 5 times.\nUnrelenting Conqueror: Attacks against target with less than 50% HP applies \"Fragile\" on them. Damage is increased dramatically when attack 'Fragile' target.\n\nThe first time HP drops to 0, immediately recovers all HP and enters \"Pursuer\" phase, gains greatly increased stats and resets \"Sett the Stage\".\nDuring \"Pursuer\" phase, \"Collapsing Fear\" can be casted periodically and attacks check its target's HP to apply 'Fragile' an additional time, after they have received the damage.\n\"Collapsing Fear\": Dealing magic damage to all allied units once, ignores damage reduction effect and refreshes \"Grievous Wound\" debuff on them beforehand.\n";
	knight.health = 12500;									   knight.omniVamp = 0;
	knight.attackDmg = 500;									   knight.armor = 666;
	knight.magicRes = 577;									   knight.abilityPower = 0;
	knight.isEnemy = true;     knight.isNeutral = false;       knight.isPlayer = false;
	knight.maxHealth = knight.health;						   knight.baseAP = 0;
	knight.baseAD = knight.attackDmg;						   knight.stack = 5;
	knight.baseAR = knight.armor;							   knight.baseMR = knight.magicRes;
	knight.range = 101;										   knight.ARpen = 50;
	if (info)
	{
		printEnemyInfo(&knight);
		char detail;
		setColor(6);
		printf("\nView further details (Y/N)? ");
		setColor(11);
		std::cin >> detail;
		setColor(7);
		if (detail == 'Y' || detail == 'y')
		{
			setColor(12);
			std::cout << "\nATK gains: +160 per stack (+800 at max)\nArmor penetration: 50%\n'Fragile' increased damage: 300% base damage\n\nDuring second phase:\n\"Pursuer\" phase's health: 21500";
			std::cout << "\nATK buff: +300\nArmor buff: +222 (treated as \"Refresh\")\nResistance buff: +200 (Treated as \"Refresh\")\n\"Collapsing Fear\" casts: whenever current turn is divisible by 3\n\"Collapsing Fear\" scales = 80% ATK (120% ATK at level 1)\n";
			system("pause");
		}
	}
	return knight;
}

Entities shitcom = createBlankTarget(), machineA = createBlankTarget(), machineB = createBlankTarget(), machineC = createBlankTarget();
