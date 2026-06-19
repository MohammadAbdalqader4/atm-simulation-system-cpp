// ATM_System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

const string ClientsFile = "ClientsFile.txt";

struct sClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkToDelete = false;
};
enum enMainMenueOptions
{
    QuickWithdraw = 1,
    NormalWithdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    Logout = 5,

};
enum enQuickWithdrawOptions
{
    Twenty = 1,
    Fifty = 2,
    Hundred = 3,
    twoHundred = 4,
    FourHundred = 5,
    SixHundred = 6,
    EightHundred = 7,
    Thousand = 8,

};
sClient CurrentClient;
void ShowMainMenu();
void Login();
void ShowMainMenu();
void ShowQuickWithdrawScreen();
void GoBackToMainMenue() {
    cout << "\nPress any key to go back to Main Menue\n";
    system("pause>0");
    ShowMainMenu();
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "") vString.push_back(S1);
    return vString;
}
string ConvertRecordToLine(sClient ClientRecord, string delimiter = "#//#") {
    string s1 = "";
    s1 += ClientRecord.AccountNumber + delimiter;
    s1 += ClientRecord.PinCode + delimiter;
    s1 += ClientRecord.Name + delimiter;
    s1 += ClientRecord.Phone + delimiter;
    s1 += to_string(ClientRecord.AccountBalance);
    return s1;
}

sClient ConvertLineToRecord(string stLine) {
    sClient ClientRecord;
    vector<string> Records = SplitString(stLine, "#//#");
    ClientRecord.AccountNumber = Records[0];
    ClientRecord.PinCode = Records[1];
    ClientRecord.Name = Records[2];
    ClientRecord.Phone = Records[3];
    ClientRecord.AccountBalance = stod(Records[4]);
    return ClientRecord;
}
short DetectOperation() {
    short number = 0;
    cin >> number;
    return number;
}
bool DepositAmmountToClient(string AccountNumber, vector<sClient>& vClints, double DepositeAmount) {
    for (sClient& C : vClints) {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance += DepositeAmount;
            return true;
        }
    }
    return false;
}
bool WithdrawAmountToClient(string AccountNumber, vector<sClient>& vClints, double WithdrawAmount) {
    for (sClient& C : vClints) {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance -= WithdrawAmount;
            return true;
        }
    }
    return false;
}
vector<sClient> LoadDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open())
    {
        sClient stClient;
        string line = "";
        while (getline(MyFile, line)) {
            stClient = ConvertLineToRecord(line);
            vClients.push_back(stClient);
        }
        MyFile.close();
    }
    return vClients;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Clinet) {
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Clinet = C;
            return true;
        }
    }
    return false;
}
double GetAmountToWithdraw(enQuickWithdrawOptions QuickWithdrawOptions) {
    switch (QuickWithdrawOptions) {

    case enQuickWithdrawOptions::Twenty:
        return 20;
    case enQuickWithdrawOptions::Fifty:
        return 50;
    case enQuickWithdrawOptions::Hundred:
        return 100;
    case enQuickWithdrawOptions::twoHundred:
        return 200;
    case enQuickWithdrawOptions::FourHundred:
        return 400;
    case enQuickWithdrawOptions::SixHundred:
        return 600;
    case enQuickWithdrawOptions::EightHundred:
        return 800;
    case enQuickWithdrawOptions::Thousand:
        return 1000;
    case 9:
        ShowMainMenu();
    default:
        return 20;

    }
}
void SaveClientsDataToFile(vector<sClient>& vClient, string FileName) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open())
    {
        string line = "";
        for (sClient& Client : vClient) {
            if (!Client.MarkToDelete)
            {
                line = ConvertRecordToLine(Client);
                MyFile << line << endl;
            }
        }
        MyFile.close();
    }
}
bool MakeQuickWithdraw(enQuickWithdrawOptions QuickWithdrawOptions) {
    vector <sClient>vClients = LoadDataFromFile(ClientsFile);
    sClient Client;
    char Answer = 'n';

    FindClientByAccountNumber(CurrentClient.AccountNumber, vClients, Client);

    double WithdrawAmount = GetAmountToWithdraw(QuickWithdrawOptions);
    if (WithdrawAmount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Press AnyKey to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return false;
    }
    cout << "\nAre You sure you want perform this transaction? y/n  ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        WithdrawAmountToClient(CurrentClient.AccountNumber, vClients, WithdrawAmount);
        CurrentClient.AccountBalance -= WithdrawAmount;
        cout << "\nThe amount has been successfully Withdraw from the account.\n";
        SaveClientsDataToFile(vClients, ClientsFile);
        return true;
    }
    return false;
}

void ShowQuickWithdrawScreen() {
    cout << "=======================================\n";
    cout << "             Quick WithDraw Screen        \n";
    cout << "=======================================\n";
    cout << "          [1] 20 " << "            [2] 50  " << "\n";
    cout << "          [3] 100" << "            [4] 200 " << "\n";
    cout << "          [5] 400" << "            [6] 600 " << "\n";
    cout << "          [7] 800 " << "           [8] 1000" << "\n";
    cout << "          [9] Exit\n";
    cout << "=======================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance;
    cout << "\nChoose what to withdraw from [1] to [9] ?";
    MakeQuickWithdraw((enQuickWithdrawOptions)DetectOperation());

}
double ReadAmount(string message) {
    double Amount = 0;
    do
    {
        cout << message;
        cin >> Amount;
    } while (Amount < 0);
    return Amount;
}
bool ShowNormalWithDraw() {
    cout << "=======================================\n";
    cout << "             Normal WithDraw Screen        \n";
    cout << "=======================================\n";
    vector <sClient>vClients = LoadDataFromFile(ClientsFile);
    sClient Client;
    char Answer = 'n';

    FindClientByAccountNumber(CurrentClient.AccountNumber, vClients, Client);

    int WithdrawAmount = ReadAmount("Enter an amount multiple of 5's ? ");
    while (WithdrawAmount % 5 != 0) {
        WithdrawAmount = ReadAmount("Enter an amount multiple of 5's ? ");
    }
    if (WithdrawAmount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, make another choice.\n";
        GoBackToMainMenue();

    }
    cout << "\nAre You sure you want perform this transaction? y/n  ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        WithdrawAmountToClient(CurrentClient.AccountNumber, vClients, WithdrawAmount);
        CurrentClient.AccountBalance -= WithdrawAmount;
        cout << "\nThe amount has been successfully Withdraw from the account.\n";
        SaveClientsDataToFile(vClients, ClientsFile);
        return true;
    }
    return false;
}
void ShowCheckBalance() {

    cout << "=======================================\n";
    cout << "             Check Balance Screen        \n";
    cout << "=======================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance << "\n";
}
bool ShowDepositScreen() {
    cout << "=======================================\n";
    cout << "             Deposit Screen        \n";
    cout << "=======================================\n";
    vector <sClient>vClients = LoadDataFromFile(ClientsFile);
    sClient Client;
    char Answer = 'Y';
    FindClientByAccountNumber(CurrentClient.AccountNumber, vClients, Client);

    int DepositeAmount = ReadAmount("\nPlease a positive Deposite Amount? ");
    cout << "\nAre You sure you want perform this transaction? y/n  ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        DepositAmmountToClient(CurrentClient.AccountNumber, vClients, DepositeAmount);
        CurrentClient.AccountBalance += DepositeAmount;
        cout << "\nThe amount has been successfully deposited into the account.\n";
        SaveClientsDataToFile(vClients, ClientsFile);
        return true;
    }
    return false;
}
void PerformMainMenueOption(enMainMenueOptions Operation) {
    switch (Operation) {
    case enMainMenueOptions::QuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::NormalWithdraw:
        system("cls");
        ShowNormalWithDraw();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Deposit:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::CheckBalance:
        system("cls");
        ShowCheckBalance();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Logout:
        system("cls");
        Login();
        GoBackToMainMenue();
        break;
    default:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    }
}
void ShowMainMenu() {
    system("cls");
    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen\t\t";
    cout << "\n=================================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";

    cout << "=================================================\n";
    cout << "Choose what do you want to do ? [1 to 5]:   ";
    PerformMainMenueOption((enMainMenueOptions)DetectOperation());
}




bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& CurrentClient) {
    //fstream MyFile(ClientsFile, ios::in);
    //if (MyFile.is_open())
    //{
    //    sClient Client;
    //    string line = "";
    //    while (getline(MyFile, line)) {
    //        Client = ConvertLineToRecord(line);
    //        VClients.push_back(Client);
    //    }
    //    MyFile.close();
    //}
    vector<sClient> VClients = LoadDataFromFile(ClientsFile);
    for (sClient& C : VClients)
    {
        if (AccountNumber == C.AccountNumber && PinCode == C.PinCode)
        {
            CurrentClient = C;
            return true;
        }
    }
    return false;
}

void Login() {
    bool LoginFaild = false;
    string AccountNumber, PinCode;
    do
    {
        system("cls");
        cout << "\n-------------------------------------------------\n";
        cout << "\t\tLogin Screen\t\t";
        cout << "\n-------------------------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invalid AccountNumber or PinCode";
        }
        cout << "\nEnter AccountNumber? "; cin >> AccountNumber;
        cout << "\nEnter Pin? "; cin >> PinCode;

        LoginFaild = !FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient);
    } while (LoginFaild);


    ShowMainMenu();
}
int main()
{
    Login();
}