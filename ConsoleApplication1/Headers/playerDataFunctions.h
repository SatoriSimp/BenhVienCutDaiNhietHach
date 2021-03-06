#pragma once

void collectDiary(Entities* enemy, Entities* player)
{
	std::ofstream diaryData("saves\\diary.dat", std::ofstream::out | std::ios::app);
	std::string dataInput;

	if (enemy->role == "Goblin champion") dataInput = "RC_1_CLR";
	else if (enemy->role == "The Singer") dataInput = "RC_2_CLR";
	else if (enemy->range == 101) dataInput = "RC_4_CLR";
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
	std::string currentLine;
	unsigned short lineNumber = 0;
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
