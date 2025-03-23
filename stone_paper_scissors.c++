#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;


enum EnGameChoice {Rock = 1, Paper= 2, Scissor =3};
enum EnWinner { Player1 = 1, Computer = 2, Draw =3};


int RandomNumber(int from, int to)
{
    int random_number;
    random_number = rand() % (to-from+1) + from;
    return random_number;
}

struct stRoundInfo
{
    short RoundNumber = 0;
    EnGameChoice Player1Choice;
    EnGameChoice ComputerChoice;
    EnWinner Winner;
    string WinnerName; 
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    EnWinner GameWinner;
    string WinnerName;
};

EnGameChoice GetComputerChoice()
{
    return (EnGameChoice) RandomNumber(1,3);
}

EnWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return EnWinner::Draw ;
    }
    
    switch (RoundInfo.Player1Choice)
    {
    case EnGameChoice::Rock :
        if (RoundInfo.ComputerChoice == EnGameChoice::Paper )
        {
            return EnWinner:: Computer;
        }
        break;
    
    case EnGameChoice::Paper :
        if (RoundInfo.ComputerChoice == EnGameChoice::Scissor)
        {
            return EnWinner::Computer;
        }
        break;

    case EnGameChoice::Scissor:
        if (RoundInfo.ComputerChoice== EnGameChoice::Rock )
        {
            return EnWinner ::Computer;
        }
        break;
    }
    // if you reach here then player1 is the winner.
    return EnWinner ::Player1;
    
}

EnWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return EnWinner ::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return EnWinner ::Computer;
    else
        return EnWinner::Draw;
}

string ChoiceName(EnGameChoice Choice)
{
    string arrGameChoices[3] = {"Stone", "Paper", "Scissors"};
    return arrGameChoices[Choice - 1];
}

string WinnerName(EnWinner Winner)
{
    string arrWinnerName[3] = {"Player1", "Computer", "No Winner"};
    return arrWinnerName[Winner-1];
}

EnGameChoice ReadPlayer1Choice()
{
    short Choice = 1;
    do
    {
        cout << endl << "Please choice an option: [1] Rock, [2] Paper, [3] Scissors" << endl;
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (EnGameChoice)Choice;
    
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes )
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (int i = 1; i< NumberOfTabs; i++)
    {
        t += "\t";
        cout << t;
    }
    return t;
}

void SetWinnerScreenColor(EnWinner Winner)
{
    switch (Winner)
    {
    case EnWinner ::Player1 :
        system("color 2F"); // Switch Screen to Green
        break;
    
    case EnWinner ::Computer :
        system("color 4F"); // Switch Screen to Red
        cout << "\a";
        break;
    
    default:
        system("color 6F"); // Switch Screen to Yellow
        break;
    }
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "_______________________________________________________________________________" << endl << endl;
    cout << Tabs(2) << "                     +++ G A M E  O V E R +++" << endl;
    cout << Tabs(2) << "_______________________________________________________________________________" << endl << endl;
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How many rounds do you want to play? (from 1 to 10)" << endl;
        cin >> GameRounds;

    } while (GameRounds <1 || GameRounds > 10);

    return GameRounds;
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_________________________________ [Game Results] ____________________________" << endl << endl;
    cout << Tabs(2) << "Game Rounds         :" << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player 1 win times  :" << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer win times  :" << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw times  :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner  :" << GameResults.WinnerName<< endl;
    cout << Tabs(2) << "_____________________________________________________________________________" << endl << endl;

    SetWinnerScreenColor(GameResults.GameWinner);
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << endl << "__________________ Rouund [" << RoundInfo.RoundNumber << "] ___________________" << endl << endl;
    cout << "Player 1 choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : [" << RoundInfo.WinnerName << "] " << endl;
    cout << "_________________________________________________________________________________________" << endl; 

    SetWinnerScreenColor(RoundInfo.Winner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1winTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

     
    for (short GameRound = 1; GameRound <=HowManyRounds; GameRound++)
    {
        cout << endl << "Round [" << GameRound << "] begins: " << endl;
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // Increase win/draw counters
        
        if (RoundInfo.Winner == EnWinner::Player1)
            Player1winTimes++;

        else if (RoundInfo.Winner == EnWinner::Computer )
            ComputerWinTimes++;

        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    
    return FillGameResults(HowManyRounds, Player1winTimes, ComputerWinTimes, DrawTimes);
}

void Start_game()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' | PlayAgain == 'y');
    
}

int main()
{
    srand((unsigned)time(NULL));

    Start_game();


    return 0;
}