#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;


enum enChange_Clints_AccountBalance{enAdd=1 , enWithade};

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string FullName;
    string Phone;
    double AccountBalance;
    bool DelteThis = false;
};

struct sUser
{
    string Name;
    string PinCode;
    short Access;
    bool DelteThis = false;
};

void Login();
void Start_Users_Main_Program();
void Print_No_Access_to_this_Page();
void Transactions_Menue_Start();
void Back_To_Main_Menue();
void Start_Main_Program();


const string Clients_Main_File = "Clients File.txt";
const string Users_Main_File = "Users File.txt";
sUser CurrentUser;

string User_Struct_to_string(sUser User,string subtracter="#//#")
{
    return User.Name + subtracter + User.PinCode + subtracter + to_string(User.Access);
}

void Print_User_form_Struct(sUser User)
{
    cout<<"==============================\n"
    <<"User Name: "<<User.Name<<endl
    <<"User PIN: "<<User.PinCode<<endl
    <<"User PIN: "<<User.Access<<endl
    <<"==============================\n";
}

sUser String_To_User_struct(string line,string letter="#//#")
{
    sUser User;
    User.Name = line.substr(0,line.find(letter));
    line.erase(0,line.find(letter) + letter.length());

    User.PinCode = line.substr(0,line.find(letter));
    line.erase(0,line.find(letter) + letter.length());

    User.Access = stoi(line.substr(0,line.find(letter) + letter.length()));
    line.erase(0,line.find(letter));

    return User;
}

vector <sUser> Read_User_File()
{
    vector <sUser> vUsers;

    fstream UsersFile;

    string Line="";

    UsersFile.open(Users_Main_File,ios::in);

    if (UsersFile.is_open())
    {
        while (getline(UsersFile,Line))
        {
            vUsers.push_back(String_To_User_struct(Line)) ;
        }
        
    }
    UsersFile.close();
    return vUsers;
}

bool Is_User_in_file_by_User_Name(string UserName)
{
    vector <sUser> vUsers = Read_User_File();
    
    for(sUser &User:vUsers)
    {
        if(User.Name == UserName)
        {
            return 1;
        }
    }
return 0;
}

short Find_index_of_User_by_User_Name(string UserName)
{
    vector <sUser> vUsers = Read_User_File();
    for(int i=0;i<vUsers.size();i++)
    {
        if(vUsers[i].Name == UserName)
        {
            return i;
        }
    }
    return -1;
}

bool is_PIN_correct(string PIN,string UserName)
{
    vector <sUser> vUsers = Read_User_File();
    if(!Is_User_in_file_by_User_Name(UserName)){
        return 0;
    }
    return vUsers[Find_index_of_User_by_User_Name(UserName)].PinCode == PIN;
}

bool Read_User_Name_and_Pin()
{
    sUser User;

    cout<<"Enter User Name? ";
    getline(cin>>ws,User.Name);

    cout<<"Pleas,Enter User PIN ";
    getline(cin,User.PinCode);

    if(is_PIN_correct(User.PinCode , User.Name))
    {
        vector <sUser> vUsers = Read_User_File();
        CurrentUser.Access = vUsers[Find_index_of_User_by_User_Name(User.Name)].Access;
        CurrentUser.Name = User.Name;
        CurrentUser.PinCode = User.PinCode;
        return 1;
    }
    return 0;
}

void Print_Loging_Screen()
{
    cout<<"============================================\n"<<
    "                Login Screen\n"<<
    "============================================\n";
}

void Print_Main_Menue_Screen()
{
    cout<<"============================================"<<endl<<
    "              Main Menue Screen             "<<endl<<
    "============================================"<<endl<<
    "         [1] Show Client List."<<endl<<
    "         [2] Add New Client."<<endl<<
    "         [3] Delete Client."<<endl<<
    "         [4] Update Client Info."<<endl<<
    "         [5] Find Client."<<endl<<
    "         [6] Transactions."<<endl<<
    "         [7] Mange Users."<<endl<<
    "         [8] Logout."<<endl;
}

void Print_Mange_User_Menue()
{
    cout<<"============================================"<<endl<<
    "            Mange Users Menue Screen"<<endl<<
    "============================================"<<endl<<
    "         [1] Show Users List."<<endl<<
    "         [2] Add New Users."<<endl<<
    "         [3] Delete Users."<<endl<<
    "         [4] Update Users Info."<<endl<<
    "         [5] Find Users."<<endl<<
    "         [6] Main Menue."<<endl;
}

void Print_No_Access_to_this_Page()
{
    system("cls");
    cout<<"============================================\n"
    <<"You Dont Have access to this page!\n"
    <<"============================================\n";
    Back_To_Main_Menue();
}

short Read_Number_is_Range(short From,short TO)
{
    short Answer=0;
    cout<<"Choose what do you want to do ["<< From <<" to "<< TO <<"]?";

    while (!(std::cin >> Answer) || Answer <= From || Answer > TO) {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer[" << From <<" to "<< TO << "]: ";
    }
    return Answer;
}

short Choose_Which_Table_To_Open_In_Main_Menue()
{
    short Answer=0;
    cout<<"Choose what do you want to do [1 to 8]?";

    while (!(std::cin >> Answer) || Answer <= 0 || Answer > 8) {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer [1 to 8]: ";
    }
    return Answer;
}


short Choose_Which_Table_To_Open_In_Transactions_Menue()
{
    short Answer=0;
    cout<<"Choose what do you want to do [1 to 4]?";

    while (!(std::cin >> Answer) || Answer <= 0 || Answer > 4) {
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter an integer [1 to 4]: ";
    }
    return Answer;
}


void Back_To_Users_Main_Menue()
{
    system("pause");
    Start_Users_Main_Program();
}

void Back_To_Main_Menue()
{
    system("pause");
    Start_Main_Program();
}

void Back_To_Transactions_Menue()
{
    system("pause");
    Transactions_Menue_Start();
}

vector<string> Split(string S1 , string delim)
{
    vector <string> vWords;
    string word="";
    short DelimPostion=0;
    while ((DelimPostion=S1.find(delim)) != std::string::npos)
    {
        word=S1.substr(0,DelimPostion);

        if(word!=""){
            vWords.push_back(word);
        }

        S1.erase(0 , DelimPostion + delim.length());
}

    if(S1!=""){
        vWords.push_back(S1);
    }

    return vWords;
}

stClientData Convert_String_To_ClientDate(string S1,string Seperator="#//#")
{
    stClientData Client;

    vector <string> vClient=Split(S1,Seperator);

    Client.AccountNumber=vClient[0];

    Client.PinCode=vClient[1];

    Client.FullName=vClient[2];

    Client.Phone=vClient[3];

    Client.AccountBalance = stod (vClient[4]);

    return Client;

}

vector <stClientData> Load_Clients_From_File()
{
    vector <stClientData> Clients;
    ifstream MyReadFile;
    string line;

    MyReadFile.open(Clients_Main_File, ios::in);

    while (getline(MyReadFile,line))
    {
        Clients.push_back(Convert_String_To_ClientDate(line));
    }
    MyReadFile.close();
    return Clients;
}

void Print_One_Client(stClientData Client)
{
    cout<< "|" << setw(16) << left << Client.AccountNumber
    << "|" << setw(16) << left << Client.PinCode
    << "|" << setw(16) << left << Client.FullName
    << "|" << setw(16) << left << Client.Phone
    << "|" << setw(16) << left << Client.AccountBalance<<endl;
}


void Print_One_User(sUser User)
{
    cout<< "|" << setw(16) << left << User.Name
    << "|" << setw(16) << left << User.PinCode
    << "|" << setw(16) << left << User.Access<<endl;
}

void Print_Header(vector <stClientData> &Clients)
{
    cout<<"\t\t\t\tClient List("<<Clients.size()<<")Clients(s)."<<endl;
    cout<<"______________________________________________________________________________________"<<endl;
}

void Print_All_Clients(vector <stClientData> &Clients)
{
    Print_Header(Clients);
    cout<< "|" << setw(16) << left << "AccountNumber"
    << "|" << setw(16) << left << "PinCode"
    << "|" << setw(16) << left << "FullName"
    << "|" << setw(16) << left << "Phone"
    << "|" << setw(16) << left << "AccountBalance"<<endl;
    cout<<"______________________________________________________________________________________"<<endl;
    for(stClientData &Client:Clients)
    {
        Print_One_Client(Client);
    }
    cout<<"______________________________________________________________________________________"<<endl;
}

void Print_Users_Header(vector <sUser> &Users)
{
    cout<<"\t\t\t\tUsers List("<<Users.size()<<")Users(s)."<<endl;
    cout<<"______________________________________________________________________________________"<<endl;
}

void Print_All_Users()
{
    vector <sUser> Users = Read_User_File();
    Print_Users_Header(Users);

    cout<< "|" << setw(16) << left << "User Name"
    << "|" << setw(16) << left << "PinCode"
    << "|" << setw(16) << left << "Access"<<endl;
    cout<<"______________________________________________________________________________________"<<endl;
    for(sUser &User : Users)
    {
        Print_One_User(User);
    }
    cout<<"______________________________________________________________________________________"<<endl;

}


void Show_Users_List()
{
    system("cls");
    Print_All_Users();
    Back_To_Users_Main_Menue();
}

void Show_Clients_List()
{
    system("cls");
    vector <stClientData> Clients = Load_Clients_From_File();
    Print_All_Clients(Clients);
    Back_To_Main_Menue();
}

void Write_Users_file_agin(vector <sUser> Users)
{
    fstream MyFile;
    MyFile.open(Users_Main_File , ios::out);
    if(MyFile.is_open())
    {
        for(sUser &user:Users){
            MyFile<<User_Struct_to_string(user)<<endl;
        }
        MyFile.close();
    }
}

void Add_Data_Line_To_User_File(string Line)
{

    fstream MyFile;
    MyFile.open(Users_Main_File , ios::out| ios::app);
    if(MyFile.is_open())
    {
        MyFile<<Line<<endl;
        MyFile.close();
    }

}

void Add_Data_Line_To_File(string Client_File_Name, string Line)
{

    fstream MyFile;
    MyFile.open(Client_File_Name , ios::out| ios::app);
    if(MyFile.is_open())
    {
        MyFile<<Line<<endl;
        MyFile.close();
    }

}

string Convert_Record_To_Line(stClientData ClientData,string Seperator="#//#")
{
    string ClientString="";

    ClientString = ClientData.AccountNumber + Seperator ;

    ClientString += ClientData.PinCode + Seperator ;

    ClientString += ClientData.FullName + Seperator ;

    ClientString += ClientData.Phone + Seperator ;

    ClientString += to_string(ClientData.AccountBalance);


    return ClientString;
}

bool is_Account_Number_Valed(string AccountNumber)
{
    vector <stClientData> Clients = Load_Clients_From_File();
    for(int i=0;i<Clients.size();i++)
    {
        if(Clients[i].AccountNumber==AccountNumber)
        {
            return 0;
        }
    }
    return 1;

}


stClientData Read_New_Client_Data()
{
    stClientData ClientData;
    cout<<"Please Enter Clinet Data:\n"<<endl;


        cout<<"Enter Account Number?";
        getline(cin >> ws,ClientData.AccountNumber);


    while (!is_Account_Number_Valed(ClientData.AccountNumber))
    {
        cout<< "Client With["<< ClientData.AccountNumber <<"] already exists, Enter another Account Number?";
        getline(cin >> ws,ClientData.AccountNumber);
    }
    
        cout<<"Enter Account PinCode?";
        getline(cin,ClientData.PinCode);

        cout<<"Enter Account FullName?";
        getline(cin,ClientData.FullName);

        cout<<"Enter Account Phone?";
        getline(cin,ClientData.Phone);

        cout<<"Enter Account AccountBalance?";
        cin>>ClientData.AccountBalance;
    
    return ClientData;
}

short Read_User_Access()
{
    char Answer = 'n';

    cout<<"Do you want to give full access y/n? ";
    cin>>Answer;
    if(toupper(Answer) == 'Y'){
        return -1;
    }

    short Access=0;

    cout<<"Show User List y/n? ";
    cin>>Answer;

    if(toupper(Answer) == 'Y'){
        Access += 1;
        Answer='n';
    }

    cout<<"Add New User y/n? ";
    cin>>Answer;
    
    if(toupper(Answer) == 'Y'){
        Access += 2;
        Answer='n';
    }

    cout<<"Delte User y/n? ";
    cin>>Answer;
    
    if(toupper(Answer) == 'Y'){
        Access += 4;
        Answer='n';
    }

    cout<<"Update User y/n? ";
    cin>>Answer;
    
    if(toupper(Answer) == 'Y'){
        Access += 8;
        Answer='n';
    }

    cout<<"Find User y/n? ";
    cin>>Answer;
    
    if(toupper(Answer) == 'Y'){
        Access += 16;
        Answer='n';
    }

    cout<<"Transactions y/n? ";
    cin>>Answer;
    
    if(toupper(Answer) == 'Y'){
        Access += 32;
        Answer='n';
    }
    return Access==63 ? -1 : Access;
}

sUser Read_New_User_Data()
{
    sUser User;
    cout<<"Please Enter User Data:\n"<<endl;


        cout<<"Enter User Name? ";
        getline(cin >> ws,User.Name);


    while (Is_User_in_file_by_User_Name(User.Name))
    {
        cout<< "User With["<< User.Name <<"] already exists, Enter another User Name?";
        getline(cin >> ws,User.Name);
    }
    
        cout<<"Enter Account PinCode?";
        getline(cin,User.PinCode);

        User.Access = Read_User_Access();
    
    return User;
}

void Add_New_Client()
{
    stClientData Client;
    Client=Read_New_Client_Data();
    Add_Data_Line_To_File(Clients_Main_File,Convert_Record_To_Line(Client));
}

void Add_New_User()
{
    sUser User;
    User = Read_New_User_Data();
    Add_Data_Line_To_User_File(User_Struct_to_string(User));
}

void Print_Add_Clients_Screen()
{
    cout<<"============================================"<<endl<<
    "              Add New Clients Screen        "<<endl<<
    "============================================"<<endl;
}

void Add_Clients()
{
    char MoreClients='y';

    do
    {
        system("cls");
        Print_Add_Clients_Screen();
        cout<<"Adding New Client:\n\n";

        Add_New_Client();

        cout<<"Do you want to add more Clients Y/N ?";
        cin>>MoreClients;
    } while (MoreClients=='y'|| MoreClients=='Y');
    Back_To_Main_Menue();
}

void Print_Add_Users_Screen()
{
    cout<<"============================================"<<endl<<
    "               Add New Users Screen        "<<endl<<
    "============================================"<<endl;
}

void Add_Users()
{
    char MoreUsers='y';

    do
    {
        system("cls");
        Print_Add_Users_Screen();
        cout<<"Adding New User:\n\n";

        Add_New_User();

        cout<<"Do you want to add more Users Y/N ?";
        cin>>MoreUsers;
    } while (MoreUsers=='y'|| MoreUsers=='Y');
    Back_To_Users_Main_Menue();
}

string Read_Account_Number_From_User()
{
    string S1="";
    cout<<"Please enter the Account Number ";
    cin>>S1;
    return S1;
}

string Read_User_Name_From_User()
{
    string S1="";
    cout<<"Please enter the User Name ";
    cin>>S1;
    return S1;
}

void Print_Client_Data_from_struct(stClientData Client)
{
    cout<<"Clinet Data Are: \n"<<endl;

    cout<<"Client AccountNumber: "<<Client.AccountNumber<<endl;

    cout<<"Client PinCode: "<<Client.PinCode<<endl;

    cout<<"Client FullName: "<<Client.FullName<<endl;

    cout<<"Client Phone:"<<Client.Phone<<endl;

    cout<<"Client AccountBalance:"<<Client.AccountBalance<<endl;
}

stClientData Find_Client_Struct_By_Account_Number(vector <stClientData> &Clients,string AccountNumber)
{

    for(stClientData &C :Clients){
        if(C.AccountNumber==AccountNumber)
        {
            return C;
        }
    }
    stClientData C;
    return C;
}


short Search_By_Account_Number(vector <stClientData> &Clients,string AccountNumber)
{
    for(int i=0;i<Clients.size();i++)
    {
        if(Clients[i].AccountNumber==AccountNumber){
            return i;
        }
    }
    return -1;
}


vector <stClientData> Write_Vector_Agin(vector <stClientData> Clients)
{
    vector <stClientData> NewClients;

    for(stClientData &C:Clients)
    {
        if (!C.DelteThis)
        {
            NewClients.push_back(C);
        }
    }
    return NewClients;
}

void Write_File_From_Vector(vector <stClientData> Clients)
{
    fstream MyFile;
    MyFile.open(Clients_Main_File,ios::out);
    if(MyFile.is_open())
    {
        for(stClientData &C:Clients)
        {
            MyFile<<Convert_Record_To_Line(C)<<endl;
        }
        MyFile.close();
    }
    
}



void Delte_Client_By_Account_Number(string AccountNumber)
{
    vector <stClientData> Clients = Load_Clients_From_File();
    char AreYouSure='n';

    while (is_Account_Number_Valed(AccountNumber))
    {
        cout<<"The Account Number ["<<AccountNumber<<"] is not Valed";
        AccountNumber = Read_Account_Number_From_User();
    }
        Print_Client_Data_from_struct(Find_Client_Struct_By_Account_Number(Clients,AccountNumber));
        cout<<"Are You Sure That you want to delte the CLient  Number("<<Clients[Search_By_Account_Number(Clients,AccountNumber)].AccountNumber<<") Y/N?";
        cin>>AreYouSure;
        
        if(toupper(AreYouSure)=='Y')
        {
            Clients[Search_By_Account_Number(Clients,AccountNumber)].DelteThis = true;
            Clients = Write_Vector_Agin(Clients);
            Write_File_From_Vector(Clients);
        }
}

vector <sUser> Write_User_File_After_Deleting(vector <sUser> &Users)
{
    vector <sUser> NewUsers;
    for(sUser & user:Users)
    {
        if(!user.DelteThis){
            NewUsers.push_back(user);
        }
    }
    return NewUsers;
}

void Delte_User_By_Account_Number(string UserName)
{
    vector <sUser> Users = Read_User_File();
    char AreYouSure='n';

    while (!Is_User_in_file_by_User_Name(UserName))
    {
        cout<<"The User Name is Valed["<<UserName<<"] is not Valed";
        UserName = Read_User_Name_From_User();
    }

    Print_User_form_Struct(Users[Find_index_of_User_by_User_Name(UserName)]);

    cout<<"\nAre You Sure That you want to delte the CLient  Number("<<UserName<<") Y/N?";
    cin>>AreYouSure;
    if(toupper(AreYouSure)=='Y')
    {
        Users[Find_index_of_User_by_User_Name(UserName)].DelteThis = 1;
        Users = Write_User_File_After_Deleting(Users);
        Write_Users_file_agin(Users);
    }
    cout<<"User Delted Successfully\n";
}

void Delete_Client()
{
    system("cls");

    Delte_Client_By_Account_Number(Read_Account_Number_From_User());

    Back_To_Main_Menue();
}

void Delete_Users()
{
    system("cls");

    Delte_User_By_Account_Number(Read_User_Name_From_User());

    Back_To_Users_Main_Menue();
}

void Apdate_Client_Data(stClientData &OldData)
{
    cout<<"Please Enter Clinet Data:\n"<<endl;


    cout<<"Enter Account PinCode?";
    getline(cin >> ws ,OldData.PinCode);

    cout<<"Enter Account FullName?";
    getline(cin,OldData.FullName);

    cout<<"Enter Account Phone?";
    getline(cin,OldData.Phone);

    cout<<"Enter Account AccountBalance?";
    cin>>OldData.AccountBalance;
}

void Read_New_User_Date_to_Change(sUser &User)
{
    cout<<"Please Enter New User Data:\n"<<endl;
    
    cout<<"Enter Account PinCode?";
    getline(cin>>ws,User.PinCode);

    User.Access = Read_User_Access();
}

void Update_User_Info_By_User_Name(string UserName)
{
    char AreYouSure='n';
    vector <sUser> Users = Read_User_File();
    while (!Is_User_in_file_by_User_Name(UserName))
    {
        cout<<"User with ["<<UserName<<"] is not found"<<endl;
        UserName = Read_Account_Number_From_User();
    }
    Print_User_form_Struct(Users[Find_index_of_User_by_User_Name(UserName)]);
    cout<<"Are You Sure you want to Change the date Y/N";
    cin>>AreYouSure;

    sUser NewUserData;
    if(toupper(AreYouSure)=='Y')
    {
        Read_New_User_Date_to_Change(NewUserData);
        NewUserData.Name = UserName;
    }
    Users[Find_index_of_User_by_User_Name(UserName)]=NewUserData;
    Write_Users_file_agin(Users);
}

void Update_Client_Info_By_Account_Number(string AccountNumber)
{
    char AreYouSure='n';

    vector <stClientData> Clients = Load_Clients_From_File();

    while (is_Account_Number_Valed(AccountNumber))
    {
        AccountNumber = Read_Account_Number_From_User();
    }
    

        Print_Client_Data_from_struct(Find_Client_Struct_By_Account_Number(Clients,AccountNumber));

        cout<<"Are You Sure That you want to Apdate The Clients Data Number("<<Clients[Search_By_Account_Number(Clients,AccountNumber)].AccountNumber<<") Y/N?";
        cin>>AreYouSure;

        if(toupper(AreYouSure)=='Y')
        {
            Apdate_Client_Data(Clients[Search_By_Account_Number(Clients,AccountNumber)]);
            Write_File_From_Vector(Clients);
        }
    
}

void Update_Client_Info()
{
    system("cls");

    Update_Client_Info_By_Account_Number(Read_Account_Number_From_User());

    Back_To_Main_Menue();
}

void Update_User_Info()
{
    system("cls");

    Update_User_Info_By_User_Name(Read_Account_Number_From_User());

    Back_To_Users_Main_Menue();
}

void Find_Client()
{
    system("cls");

    vector <stClientData> Clients = Load_Clients_From_File();

    string AccountNumber=Read_Account_Number_From_User();

    while (is_Account_Number_Valed(AccountNumber))
    {
        AccountNumber = Read_Account_Number_From_User();
    }
    

    Print_Client_Data_from_struct(Find_Client_Struct_By_Account_Number(Clients,AccountNumber));

    Back_To_Main_Menue();
}

void Find_User()
{
    system("cls");

    vector <sUser> Users = Read_User_File();

    string UserName = Read_User_Name_From_User();

    while (!Is_User_in_file_by_User_Name(UserName))
    {
        cout<<UserName<<" Is Not Valed ";
        UserName = Read_User_Name_From_User();
    }
    

    Print_User_form_Struct(Users[Find_index_of_User_by_User_Name(UserName)]);

    Back_To_Users_Main_Menue();
}

void Print_Transactions_Menue()
{
cout<<"============================================"<<endl<<
    "            Transactions Menue Screen         "<<endl<<
    "============================================"<<endl<<
    "         [1] Deposit."<<endl<<
    "         [2] Withdraw."<<endl<<
    "         [3] Total Balances."<<endl<<
    "         [4] Main Menue."<<endl;
}


void Change_Client_Balance(int Amount,string AccountNumber,vector <stClientData> &Clients)
{

    
    char Answer='n';
    
    cout<<"Are you sure you want perfrom this transaction Y/N ? ";
    cin>>Answer;

    if(toupper(Answer) == 'Y')
    {
        Clients[Search_By_Account_Number(Clients,AccountNumber)].AccountBalance += Amount;
        Write_File_From_Vector(Clients);
    }
}


void Print_Deposit_Header()
{
    cout<<"============================================\n"<<
            "             Deposit Screen                \n"<<
    "============================================\n";
}

void Read_Change_Client_Balanc_for_adding(string AccountNumber)
{
    int Amount=0;
    cout<<"Pleas enter deposit amount? ";
    cin>>Amount;
    vector <stClientData> Clients = Load_Clients_From_File();

    Change_Client_Balance(Amount ,AccountNumber,Clients);

}


void Read_Change_Client_Balanc_for_withade(string AccountNumber)
{
    int Amount=0;
    cout<<"Pleas enter deposit amount? ";
    cin>>Amount;
    vector <stClientData> Clients = Load_Clients_From_File();

    while (Clients[Search_By_Account_Number(Clients,AccountNumber)].AccountBalance < Amount)
    {
        cout<<"This Client Doesnt have the Amount ,Please enter a valed Amount ";
        cin>>Amount;
    }
    Change_Client_Balance(Amount *- 1,AccountNumber,Clients);
}

void Print_Client_for_Transaction(string AccountNumber,enChange_Clints_AccountBalance Change_Clints_AccountBalance)
{
    vector <stClientData> Clients = Load_Clients_From_File();
    while (is_Account_Number_Valed(AccountNumber))
    {
        AccountNumber = Read_Account_Number_From_User();
    }
        Print_Client_Data_from_struct(Find_Client_Struct_By_Account_Number(Clients,AccountNumber));
        if(Change_Clints_AccountBalance == enChange_Clints_AccountBalance::enAdd){
        Read_Change_Client_Balanc_for_adding(AccountNumber);
        }else{
        Read_Change_Client_Balanc_for_withade(AccountNumber);
        }
}

void Print_One_Client_Transaction(stClientData &Client)
{
    cout<< "|" << setw(16) << left << Client.AccountNumber
    << "|" << setw(16) << left << Client.FullName
    << "|" << setw(16) << left << Client.AccountBalance<<endl;
}



void Print_All_Clients_Transactions(vector <stClientData> &Clients)
{
    Print_Header(Clients);
    cout<< "|" << setw(16) << left << "AccountNumber"
    << "|" << setw(16) << left << "FullName"
    << "|" << setw(16) << left << "AccountBalance"<<endl;
    cout<<"______________________________________________________________________________________"<<endl;
    for(stClientData &Client:Clients)
    {
        Print_One_Client_Transaction(Client);
    }
    cout<<"______________________________________________________________________________________"<<endl;
}


void Show_Transactions_List()
{
    system("cls");
    vector <stClientData> Clients = Load_Clients_From_File();
    Print_All_Clients_Transactions(Clients);
    Back_To_Transactions_Menue();
}



void Deposit()
{
    system("cls");
    Print_Deposit_Header();
    Print_Client_for_Transaction(Read_Account_Number_From_User(),enChange_Clints_AccountBalance::enAdd);
    Back_To_Transactions_Menue();
}

void Print_Withdraw_Header()
{
    cout<<"============================================\n"<<
        "             Deposit Screen                \n"<<
    "============================================\n";
}

void Withdraw()
{
    system("cls");
    Print_Withdraw_Header();
    Print_Client_for_Transaction(Read_Account_Number_From_User(),enChange_Clints_AccountBalance::enWithade);
    Back_To_Transactions_Menue();
}

void Transactions_Menue_Start()
{
    system("cls");
    
    Print_Transactions_Menue();
    
    short Program_Mood = Choose_Which_Table_To_Open_In_Transactions_Menue();

    switch (Program_Mood)
    {
    case 1:
        Deposit();
        break;
    case 2:
        Withdraw();
        break;
    case 3:
        Show_Transactions_List();
        break;
    case 4:
        Start_Main_Program();
        break;
    default:
        cout<<"Sorry Somthing went wrong plz start the app agin :(";
    }
}


void Start_Users_Main_Program()
{
    system("cls");
    Print_Mange_User_Menue();
    short Program_Mood = Read_Number_is_Range(0,6);

    switch (Program_Mood)
    {
        case 1:
            Show_Users_List();
            break;
        case 2:
            Add_Users();
            break;
        case 3:
            Delete_Users();
            break;
        case 4:
            Update_User_Info();
            break;
        case 5:
            Find_User();
            break;
        case 6:
            Start_Main_Program();
            break;
        default:
            cout<<"Sorry Somthing went wrong plz start the app agin :(";
    }
}

void Start_Main_Program()
{

    system("cls");
    Print_Main_Menue_Screen();

    short Program_Mood = Choose_Which_Table_To_Open_In_Main_Menue();

    switch (Program_Mood)
    {
    case 1:
        if(CurrentUser.Access & 1){
            Show_Clients_List();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 2:
        if(CurrentUser.Access & 2){
                Add_Clients();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 3:
        if(CurrentUser.Access & 4){
                Delete_Client();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 4:
        if(CurrentUser.Access & 8){
                Update_Client_Info();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 5:
        if(CurrentUser.Access & 16){
            Find_Client();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 6:
        if(CurrentUser.Access & 32){
            Transactions_Menue_Start();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;   
    case 7:
        if(CurrentUser.Access==-1){
            Start_Users_Main_Program();
        }else{
            Print_No_Access_to_this_Page();
        }
        break;
    case 8:
        Login();
        break;
    default:
        cout<<"Sorry Somthing went wrong plz start the app agin :(";
    }
}

void Login()
{
    system("cls");
    vector <sUser> vUsers = Read_User_File();
    Print_Loging_Screen();

    if(Read_User_Name_and_Pin())
    {
        Start_Main_Program();
    }else{
        cout<<"Wrong Values"<<endl;
        system("pause");
    }
}

int main()
{
    Login();

    return 0;
}