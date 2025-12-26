#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice CompChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults {
	short GameRounds = 0;
	short PlayerWonTimes = 0;
	short CompWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		break;
	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

enGameChoice GetCompChoice() {
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.CompChoice)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		return (RoundInfo.CompChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Paper:
		return (RoundInfo.CompChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Scissors:
		return (RoundInfo.CompChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
	}

	return enWinner::Draw;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short CompWinTimes) {
	if (PlayerWinTimes > CompWinTimes) return enWinner::Player1;
	else if (CompWinTimes > PlayerWinTimes) return enWinner::Computer;
	else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice) {
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player", "Comp","No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayerChoice() {
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo) {
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.CompChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}

stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, CompWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.CompChoice = GetCompChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			CompWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);

		SetWinnerScreenColor(RoundInfo.Winner);
	}

	return { HowManyRounds,Player1WinTimes,CompWinTimes,DrawTimes,
		WhoWonTheGame(Player1WinTimes,CompWinTimes),
		WinnerName(WhoWonTheGame(Player1WinTimes, CompWinTimes))
	};

}

short ReadHowManyRounds() {
	short HowManyRounds = 1;
	do {
		cout << "How Many Rounds? 1 to 10\n";
		cin >> HowManyRounds;
	} while (HowManyRounds < 1 || HowManyRounds>10);

	return HowManyRounds;
}

string Tabs(short TabsCount) {
	string t = "";
	for (int i = 1; i < TabsCount; i++) {
		t += "\t";
		cout << t;
	}

	return t;
}

void ShowFinalGameResults(stGameResults GameResults) {
	cout << Tabs(2) << "_____________________[ Game Results ]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player won times   : " << GameResults.PlayerWonTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.CompWonTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "__________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

void ShowGameOverScreen() {
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                +++  G a m e  O v e r  +++\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << Tabs(2) << "Do you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;

}