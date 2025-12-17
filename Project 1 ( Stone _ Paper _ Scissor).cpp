
#include<iostream>
#include<cstdlib>
#include<string>
#include<iomanip>
 using namespace std;

    enum enGameChoices { Stone = 1, Paper = 2, Scissorss = 3 };

    enum enWinner { Player1 = 1, Computer = 2, draw = 3 };

    struct stRound
    {

        short RoundNumber;
        enGameChoices Player1Choice;
        enGameChoices ComputerChoice;
        enWinner RoundWinner;





    };


    struct stGameInfo
    {
        short GameRounds;
        short Player1WinTimes;
        short ComputerWinTimes;
        short DrawTimes;
        enWinner FinalWinner;

    };


    enGameChoices GetComputerChoice();
    int GetRandomNumber(int, int);
    enWinner RoundWinner(enGameChoices, enGameChoices);
    stRound FillRoundInfo(short);
    void SetWinnerScreen(enWinner);
    void PrintRoundInfo(stRound);
    stGameInfo FillGameInfo(short, short, short, short);
    short ReadHowManyRounds();
    string Tabs(short);
    void GameOverHeader();
    void ResetScreen();




    int GetRandomNumber(int From, int To)
    {


        return rand() % (To - From + 1) + From;


    }

    enGameChoices GetComputerChoice()
    {

        return(enGameChoices)GetRandomNumber(1, 3);



    }


    enWinner RoundWinner(enGameChoices PlayerChoice, enGameChoices ComputerChoice)
    {
        if (PlayerChoice == ComputerChoice)
        {
            return enWinner::draw;
        }


        switch (ComputerChoice)
        {
        case enGameChoices::Paper:
            if (PlayerChoice == enGameChoices::Stone)
                return enWinner::Computer;

        case enGameChoices::Scissorss:
            if (PlayerChoice == enGameChoices::Paper)
                return enWinner::Computer;

        case enGameChoices::Stone:
            if (PlayerChoice == enGameChoices::Scissorss)
                return enWinner::Computer;


        }


        return enWinner::Player1;


    }

    enGameChoices ReadPlayerChoice()
    {
        int C;
        do
        {

            cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissor ? ";
            cin >> C;


        } while (C < 1 || C>3);

        return (enGameChoices)C;

    }

    string GetChoiceText(enGameChoices Choice)
    {
        string arrChoice[3] = { "Stone","Paper","Scissor" };

        return arrChoice[Choice - 1];
    }

    string GetWinnerText(enWinner Winner)
    {
        string arrWinner[3] = { "Player1","Computer","[No Winner]" };

        return arrWinner[Winner - 1];


    }


    stRound FillRoundInfo(short RoundNumber)
    {
        stRound Round;
        Round.RoundNumber = RoundNumber;
        Round.Player1Choice = ReadPlayerChoice();
        Round.ComputerChoice = GetComputerChoice();
        Round.RoundWinner = RoundWinner(Round.Player1Choice, Round.ComputerChoice);


        return Round;

    }


    void PrintRoundInfo(stRound Round)
    {
        printf("\n--------------------Round[%d]---------------------\n", Round.RoundNumber);

        cout << "\nPlayer1 Choice   :" << GetChoiceText(Round.Player1Choice);
        cout << "\nComputer Choice  :" << GetChoiceText(Round.ComputerChoice);
        cout << "\nRound Winner     :" << GetWinnerText(Round.RoundWinner);

        printf("\n\n-----------------------------------------------------\n");

        SetWinnerScreen(Round.RoundWinner);

    }

    void SetWinnerScreen(enWinner Winner)
    {
        switch (Winner)
        {
        case enWinner::Player1:
            system("color 2F");
            break;

        case enWinner::Computer:
            system("color 4F");
            cout << "\a";
            break;

        case enWinner::draw:
            system("color 6F");


        }


    }

    enWinner GameWinner(short Player1WinTimes, short ComputerWinTimes)
    {
        if (Player1WinTimes == ComputerWinTimes)
        {
            return enWinner::draw;
        }

        if (Player1WinTimes > ComputerWinTimes)
            return enWinner::Player1;
        else
            return enWinner::Computer;



    }


    stGameInfo PlayRounds(short NumberOfRounds)
    {
        stRound Round;

        short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

        for (int i = 1; i <= NumberOfRounds; i++)
        {

            printf("\n\nRound [%d] begins: \n", i);

            Round = FillRoundInfo(i);

            PrintRoundInfo(Round);

            switch (Round.RoundWinner)
            {
            case enWinner::Player1:
                Player1WinTimes++;
                break;

            case enWinner::Computer:
                ComputerWinTimes++;
                break;

            case enWinner::draw:
                DrawTimes++;
                break;

            }

        }

        return FillGameInfo(Player1WinTimes, ComputerWinTimes, DrawTimes, NumberOfRounds);

    }



    stGameInfo FillGameInfo(short Player1WinTimes, short ComputerWinTimes, short DrawTimes, short NumberOfRounds)
    {
        stGameInfo GameInfo;
        GameInfo.ComputerWinTimes = ComputerWinTimes;
        GameInfo.Player1WinTimes = Player1WinTimes;
        GameInfo.DrawTimes = DrawTimes;
        GameInfo.GameRounds = NumberOfRounds;
        GameInfo.FinalWinner = GameWinner(Player1WinTimes, ComputerWinTimes);

        return GameInfo;


    }

    string Tabs(short Number)
    {
        string T = "";

        for (int i = 1; i <= Number; i++)
        {
            T = T + "\t";

        }

        return T;

    }


    void GameOverHeader()
    {
        cout << Tabs(4) << "----------------------------------------------------\n\n";
        cout << Tabs(6) << "+++G a m e  O v e r+++" << endl << endl;
        cout << Tabs(4) << "----------------------------------------------------\n\n";
    }


    void PrintGameInfo(stGameInfo GameInfo)
    {
        GameOverHeader();

        cout << Tabs(4) << "--------------------[ Game Results ]-----------------\n\n";
        cout << Tabs(4) << "Game Rounds         : " << GameInfo.GameRounds << endl;
        cout << Tabs(4) << "Player 1 Won Times  : " << GameInfo.Player1WinTimes << endl;
        cout << Tabs(4) << "Computer Won Times  : " << GameInfo.ComputerWinTimes << endl;
        cout << Tabs(4) << "Draw Times          :" << GameInfo.DrawTimes << endl;
        cout << Tabs(4) << "Final Winner        :" << GetWinnerText(GameInfo.FinalWinner);
        cout << "\n" << Tabs(4) << "----------------------------------------------------\n\n";

        SetWinnerScreen(GameInfo.FinalWinner);

    }

    short ReadHowManyRounds()
    {
        short NumberOfRounds;
        cout << "How Many rounds do you want to play? \n";
        cin >> NumberOfRounds;

        return NumberOfRounds;

    }


    void ResetScreen()
    {
        system("cls");

        system("Color 0F");

    }


    void startGame()
    {
        char PlayAgain = 'y';

        do
        {
            ResetScreen();

            PrintGameInfo(PlayRounds(ReadHowManyRounds()));

            cout << "Do yoy want to play again? Y/N?";
            cin >> PlayAgain;


        } while (PlayAgain == 'y' || PlayAgain == 'Y');




    }

    int main()
    {
        srand((unsigned)time(NULL));

        startGame();

        return 0;
    }





