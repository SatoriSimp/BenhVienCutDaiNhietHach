#pragma once

void retardInput()
{
	std::cout << "\nBruh wtf are you doing?\n\n";
}

int damageOutput(int armor, int magicResistance, int physicDmg, int magicDmg) {
	int physicTaken = (armor >= 0) ? physicDmg * 100 / (100 + armor) : physicDmg * 2 - 100 / (100 - armor);
	int magicTaken = (magicResistance >= 0) ? magicDmg * 100 / (100 + magicResistance) : magicDmg * 2 - 100 / (100 - magicResistance);
	return physicTaken + magicTaken;
}

int lifeSteal(int damage, int vamp) { return damage * vamp / 100; }