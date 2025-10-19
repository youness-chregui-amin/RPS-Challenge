#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {

	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults {

	short GameRounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

struct stRoundWinnerTimes {

	short PlayerCounter = 0;
	short ComputerCounter = 0;
	short DrawCounter = 0;
};

short ReadHowManyRound() {

	short Rounds = 0;
	do {
		cout << "How Many Rounds Do You Want to Play ?";
		cin >> Rounds;
	} while (Rounds < 0);

	return Rounds;
}

short RandomNumber(short From, short To) {

	return rand() % (To - From + 1) + From;

}

enGameChoice ComputerChoice() {

	return (enGameChoice)RandomNumber(1, 3);
}

enGameChoice PlayerChoice() {

	short Choice = 0;

	do {
		cout << "Choose --> [1]:Rock , [2]:Paper , [3]:Scissor ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enWinner WhoWonTheRound(stRoundInfo Info) {

	if (Info.PlayerChoice == Info.ComputerChoice)
		return enWinner::Draw;

	switch (Info.PlayerChoice) {

	case enGameChoice::Rock:
		if (Info.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;

		}
		break;
	case enGameChoice::Paper:
		if (Info.ComputerChoice == enGameChoice::Scissor) {
			return enWinner::Computer;

		}
		break;
	case enGameChoice::Scissor:
		if (Info.ComputerChoice == enGameChoice::Rock) {
			return enWinner::Computer;

		}
		break;
	}
	return enWinner::Player1;
}

string WinnerName(enWinner Winner) {

	string ArrWinnerName[3] = { "Player1", "Computer", "No Winner" };
	return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice) {

	string ArrChoiceName[3] = { "Rock" , "Paper" , "Scissor" };
	return ArrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner) {

	switch (Winner) {

	case enWinner::Computer:
		system("Color 4F");
		system("\a");
		break;

	case enWinner::Player1:
		system("Color 2F");
		break;
	case enWinner::Draw:
		system("Color 6F");
		break;
	}
}

void PrintRoundResult(stRoundInfo Info) {

	cout << "\n____________Round[" << Info.RoundNumber << "]_____________\n\n";
	cout << "Player Choice : " << ChoiceName(Info.PlayerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(Info.ComputerChoice) << endl;
	cout << "RoundWinner : " << Info.WinnerName << endl;
	cout << "______________________________________\n" << endl;

	SetWinnerScreenColor(Info.Winner);
}

enWinner WhoWonTheGame(stRoundWinnerTimes WinnerTime) {

	if (WinnerTime.PlayerCounter > WinnerTime.ComputerCounter)
		return enWinner::Player1;
	else if (WinnerTime.ComputerCounter > WinnerTime.PlayerCounter)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short Rounds, stRoundWinnerTimes WinnerTimes) {

	stGameResults GameResults;

	GameResults.GameRounds = Rounds;
	GameResults.PlayerWonTimes = WinnerTimes.PlayerCounter;
	GameResults.ComputerWonTimes = WinnerTimes.ComputerCounter;
	GameResults.DrawTimes = WinnerTimes.DrawCounter;
	GameResults.GameWinner = WhoWonTheGame(WinnerTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRound) {

	stRoundInfo Info;
	stRoundWinnerTimes WinnerTimes;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++) {

		cout << "\nRound[" << GameRound << "] Begins \n";
		Info.RoundNumber = GameRound;
		Info.PlayerChoice = PlayerChoice();
		Info.ComputerChoice = ComputerChoice();
		Info.Winner = WhoWonTheRound(Info);
		Info.WinnerName = WinnerName(Info.Winner);

		if (Info.WinnerName == "Player1")
			WinnerTimes.PlayerCounter++;
		else if (Info.WinnerName == "Computer")
			WinnerTimes.ComputerCounter++;
		else
			WinnerTimes.DrawCounter++;

		PrintRoundResult(Info);
	}

	return FillGameResults(HowManyRound, WinnerTimes);
}

void ResetScreen() {

	system("cls");
	system("Color 0F");
}

string Tabs(short NumberOfTabs) {

	string T = "";

	for (int i = 1; i <= NumberOfTabs; i++) {

		T = T + "\t";
		cout << T;
	}

	return T;
}

void ShowGameOverScreen() {

	cout << Tabs(2) << "_______________________________________________________\n\n";
	cout << Tabs(2) << "                       ++++ G a m e O v e r ++++\n\n";
	cout << Tabs(2) << "_______________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults) {

	cout << Tabs(2) << "________________________[Game Results]________________________\n\n";
	cout << Tabs(2) << "Game Results            :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times        :" << GameResults.PlayerWonTimes << endl;
	cout << Tabs(2) << "Computer Won Times      :" << GameResults.ComputerWonTimes << endl;
	cout << Tabs(2) << "Draw Times              :" << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "FinalWinner             :" << GameResults.WinnerName << endl;
	cout << Tabs(2) << "______________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame() {

	char PlayAgain = 'Y';

	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRound());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << "Do You Want To Play Again ? Y / N ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main() {

	
	srand((unsigned)time(NULL));

	StartGame();
}