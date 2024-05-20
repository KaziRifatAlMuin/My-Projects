#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <random>
using namespace std;
#define PI acos(-1.0)
std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
#define random(l, r) (std::uniform_int_distribution<long long int>(l, r)(mt))

/*

Lab Project by
Kazi Rifat Al Muin
2107042

The Project Functions :
- There are some polygons
- All Polygons have different classes, functions
- It is in game mode, a player have to tell the area according to given information
- After Every level, The game becomes harder
- In every 5th level, Player has to tell sum of two different polygons

Concepts of OOP used in the project:

1. There are total of 1 + 2 + 4 + 3 + 1 + 3 = 14 classes, initialized with constructors, have destructors
2. Three level inheritance is used here. Polygon -> (Quad, Tri, Any) -> (Rec, Sq, Prl, trp) (Equ, Iso, Sce)
3. Polymorphism is used : To Calculate Area - overriding the functions in derived classes
4. Abstract class and Pure Virtual Function is used : To Ask Question (In Game)
5. Friend class is used : To connect Polygon with Game, Gamer with Database
6. Friend function is used : To search player, To Run the game, For Home Page
7. STL is used : To sort co-ordinates anti-clockwise, sort Leaderboards, containers to store data
8. Operator Overloading : For input >> and output << for the gamer class
9. File Management : Database and Leaderboard - two files are used to read, write and store data
10. Template : This is used to add two polymorphic class using pointers and template function

*/

class Game;
class Database;

class Polygon{
protected:
    int n;
    vector<double> x, y;
    vector<pair<double, pair<double, double>>> xy;
public:
    friend class Game; // Friend Class to control Game
    Polygon(){}
    Polygon(int n)
    {
        this->n = n;
    }
    ~ Polygon()
    {
        // Destructor
    }
    int SideNo()
    {
        return n;
    }
    // Abstract Class
    virtual double ask() = 0; // Pure Virtual Function

    void set_xy(double a, double b)
    {
        x.push_back(a);
        y.push_back(b);
        pair<double, pair<double, double>> pr;
        pr.first = 0;
        pr.second.first = a;
        pr.second.second = b;
        xy.push_back(pr);
    }
    virtual double Area() // Area Calculation for any Polygon
    {
        sort_coordinate();
        double A = 0;
        for(int i = 1; i < n; i++){
            A += (x[i-1] * y[i]);
        }
        A += (x[n-1] * y[0]);
        for(int i = 1; i < n; i++){
            A -= (y[i-1] * x[i]);
        }
        A -= (y[n-1] * x[0]);
        return abs(0.5 * A);
    }
    void sort_coordinate()
    {
        for(int i = 0; i < n; i++){
            xy[i].second.first = x[i];
            xy[i].second.second = y[i];
        }
        for(auto i : xy){
            double xx = i.second.first;
            double yy = i.second.second;
            double theta = atan(abs(yy)/abs(xx)) * 180 / PI;
            if(xx >= 0 && yy >= 0) i.first = theta;
            else if(xx < 0 && yy >= 0) i.first = theta + 90;
            else if(xx < 0 && yy < 0) i.first = theta + 180;
            else i.first = theta + 270;
        }
        sort(xy.begin(), xy.end());
        for(int i = 0; i < n; i++){
            x[i] = xy[i].second.first;
            y[i] = xy[i].second.second;
        }
    }
};

class Triangle : virtual public Polygon{
    double base, height;
public:
    Triangle()
    {
        n = 3;
    }
    Triangle(double b, double h)
    {
        base = b;
        height = h;
    }
    double ask()
    {
        cout << "The height of the Triangle is : " << height << "\n";
        cout << "The Base of the Triangle is   : " << base << "\n";
        cout << "What is the Area of the Triangle? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
    double Area() // Overiding function, Polymorphism
    {
        return 0.5 * base * height;
    }
};

class Quadrilateral : virtual public Polygon{
public:
    Quadrilateral()
    {
        n = 4;
    }
    double ask()
    {
        for(int i = 0; i < n; i++){
            int xx = random(-10,10);
            int yy = random(-20,20);
            x.push_back(xx);
            y.push_back(yy);
        }
        cout << "You are Given a Quadrilateral. Its Co-ordinates are : \n";
        for(int i = 0; i < n; i++){
            cout << "(" << x[i] << "," << y[i] << ")\n";
        }
        cout << "What is the Area? \nAns : ";
        double in;
        cin >> in;
        return in;
    }
};

class Rectangle : virtual public Quadrilateral{
    double width, height;
public:
    Rectangle(){}
    Rectangle(double a, double b)
    {
        width = a;
        height = b;
    }
    double Area()
    {
        return width * height;
    }
    double ask()
    {
        cout << "The height of the Rectangle is : " << height << "\n";
        cout << "The width of the Rectangle is  : " << width << "\n";
        cout << "What is the Area of the Rectangle? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Square : virtual public Quadrilateral{
    double SideLength;
public:
    Square(){}
    Square(double a)
    {
        SideLength = a;
    }
    double Area()
    {
        return SideLength * SideLength;
    }
    double ask()
    {
        cout << "The Side Length of the Square is : " << SideLength << "\n";
        cout << "What is the Area of the Square? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Parallelogram : virtual public Quadrilateral{
    double base, height;
public:
    Parallelogram(){}
    Parallelogram(double a, double b)
    {
        base = a;
        height = b;
    }
    double Area()
    {
        return base * height;
    }
    double ask()
    {
        cout << "The height of the Parallelogram is : " << height << "\n";
        cout << "The base of the Parallelogram is   : " << base << "\n";
        cout << "What is the Area of the Parallelogram? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Trapezoid : virtual public Quadrilateral{
    double side1, side2, height;
public:
    Trapezoid(){}
    Trapezoid(double a, double b, double h)
    {
        side1 = a;
        side2 = b;
        height = h;
    }
    double Area()
    {
        return 0.5 * (side1 + side2) * height;
    }
    double ask()
    {
        cout << "The side1 of the Trapezoid is  : " << side1 << "\n";
        cout << "The side2 of the Trapezoid is  : " << side2 << "\n";
        cout << "The distance between two parallel side is : " << height << "\n";
        cout << "What is the Area of the Trapezoid? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Equilateral_Triangle: virtual public Triangle{
    double a;
public:
    Equilateral_Triangle(){}
    Equilateral_Triangle(double a)
    {
        this->a = a;
    }
    double Area()
    {
        return sqrt(3.0) * a * a / 4;
    }
    double ask()
    {
        cout << "The Side Length of Equilateral Triangle is : " << a << "\n";
        cout << "What is the Area of the Equilateral Triangle? \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Isosceles_Triangle: virtual public Triangle{
    double a, b; // a is same side
public:
    Isosceles_Triangle(){}
    Isosceles_Triangle(double a, double b)
    {
        this->a = a;
        this->b = b;
    }
    double Area()
    {
        return sqrt((a * a) - (b * b / 4)) * b / 2;
    }
    double ask()
    {
        cout << "The Length of two equal side of Isosceles Triangle  is : " << a << "\n";
        cout << "The Length of another side of Isosceles Triangle  is   : " << b << "\n";
        cout << "What is the Area of the Isosceles Triangle \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class Scalene_Triangle: virtual public Triangle{
    double a, b, c;
public:
    Scalene_Triangle(){}
    Scalene_Triangle(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    double Area()
    {
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double ask()
    {
        cout << "The Length of side1 of Scalene Triangle  is : " << a << "\n";
        cout << "The Length of side2 of Scalene Triangle  is : " << b << "\n";
        cout << "The Length of side3 of Scalene Triangle  is : " << c << "\n";
        cout << "What is the Area of the Scalene Triangle \nAns : ";
        double ans;
        cin >> ans;
        return ans;
    }
};

class AnyPolygon : virtual public Polygon{
// This is for any type of Polygon with n sides
public:
    AnyPolygon(){}
    AnyPolygon(int n) : Polygon(n)
    {
        this->n = n;
    }
    double ask()
    {
        for(int i = 0; i < n; i++){
            int xx = random(-10,10);
            int yy = random(-20,20);
            x.push_back(xx);
            y.push_back(yy);
        }
        cout << "You are Given a Polygon with " << n << " sides. Its Co-ordinates are : \n";
        for(int i = 0; i < n; i++){
            cout << "(" << x[i] << "," << y[i] << ")\n";
        }
        cout << "What is the Area? \nAns : ";
        double in;
        cin >> in;
        return in;
    }
};

template <typename T1, typename T2> // Use of Template for adding two different class objects
bool AddTwo(T1 &ob1, T2 &ob2)
{
    Polygon *p = ob1;
    Polygon *q = ob2;
    double r1, r2, input;
    r1 = p->ask();
    r2 = q->ask();
    cout << "Write the Total Area : ";
    cin >> input;
    double ANS = p->Area() + q->Area();
    if(abs(ANS - input) < 0.01){
        cout << "Correct Answer!\n";
        return true;
    }
    else{
        cout << "---------------------------------------------------------\n";
        cout << "--------------------| Wrong Answer |---------------------\n";
        cout << "---------------------------------------------------------\n";
        cout << "The Area is : " << ANS << "\n";
        return false;
    }
}

class Game{
    int a, b, c;
public:
    friend class Polygon;
    bool MakeQues(int level)
    {
        cout << "---------------------------------------------------------\n";
        cout << "----------------------| Level " << level << " |------------------------\n";
        cout << "---------------------------------------------------------\n";
        a = random(1, level + 7) * 2; // Difficulty increases by level
        b = random(abs(a-3), a + 3);
        c = abs(random(1, b) * 2);
        Polygon *p[10]; // Asks Area of 10 types of Different Shape
        int x, y, z;
        z = level / 7;
        p[0] = new Triangle(a, b);
        p[1] = new Rectangle(a, b);
        p[2] = new Square(a);
        p[3] = new Parallelogram(a, b);
        p[4] = new Trapezoid(a, b, c);
        p[5] = new Equilateral_Triangle(a);
        p[6] = new Isosceles_Triangle(a, b);
        p[7] = new Scalene_Triangle(a, b, c);
        p[8] = new Quadrilateral;
        p[9] = new AnyPolygon(z);
        if(level < 10){
            x = random(0, 4);
            y = (x + random(0, 4)) % 5;
        }
        else if(level < 25) {
            x = random(0, 7);
            y = (x + random(0, 7)) % 8;
        }
        else{
            // Higher Level, More Various and Harder Ques
            x = random(0, 9);
            y = (x + random(0, 9)) % 10;
        }
        if(level % 5 == 0){
            bool res = AddTwo(p[x], p[y]); // For Every 5th level, Sum of Two Shape is asked
            return res;
        }
        double input;
        input = p[x]->ask();
        double ANS = p[x]->Area();
        if(abs(ANS - input) < 0.01){
            cout << "Correct Answer!\n";
            return true;
        }
        else{
            cout << "---------------------------------------------------------\n";
            cout << "--------------------| Wrong Answer |---------------------\n";
            cout << "---------------------------------------------------------\n";
            cout << "The Area is : " << ANS << "\n";
            return false;
        }
    }
};

class Gamer{
    string Name;
    string username;
    string Department;
    int Roll;
    int HighestScore;
public:
    friend class Database;
    friend void SearchAPlayer(Database, string);
    friend void Home();
    friend void PlayGame();
    Gamer(){}
    Gamer(string Name, string username, string Department, int Roll, int HighestScore)
    {
        this->Name = Name;
        this->username = username;
        this->Department = Department;
        this->Roll = Roll;
        this->HighestScore = HighestScore;
    }
    friend istream & operator >> (istream &in, Gamer &G) // Input operator Overloading
    {
        G.HighestScore = 0;
        cout << "Enter Your Name : ";
        fflush(stdin);
        getline(in, G.Name);
        fflush(stdin);
        cout << "Enter a username (without space): ";
        in >> G.username;
        fflush(stdin);
        cout << "Enter Your Department Name : ";
        in >> G.Department;
        fflush(stdin);
        cout << "Enter your Roll No : ";
        in >> G.Roll;
        return in;
    }
    friend ostream & operator << (ostream &out, Gamer &G) // Outpur Operator Overloading
    {
        out << "Name          : " << G.Name << endl;
        out << "Username      : " << G.username << endl;
        out << "Department    : " << G.Department << endl;
        out << "Roll          : " << G.Roll << endl;
        out << "Highest Score : " << G.HighestScore << endl;
        return out;
    }
};

class Database{
    Gamer GamerList[1000];
    int PlayerNo;
public:
    map <string, int> ScoreBoard;
    vector<pair<int, string>> RANK;
    friend void SearchAPlayer(Database, string);
    friend void Home();
    friend void PlayGame();
    Database()
    {
        PlayerNo = 0;
    }
    void Update(string user, int score)
    {
        int i = 0;
        for(i = 0; i < PlayerNo; i++){
            if(GamerList[i].username == user) break;
        }
        GamerList[i].HighestScore = max(GamerList[i].HighestScore, score);

        for(int j = 0; j < RANK.size(); j++){
            if(RANK[j].second == user){
                RANK[j].first = GamerList[i].HighestScore;
                break;
            }
        }
        sort(RANK.rbegin(), RANK.rend());
    }
    void UpdateData()
    {
        ofstream OutFile; // Using file to store and manage huge data
        OutFile.open("Database.txt");
        for(int i = 0; i < PlayerNo; i++){
            OutFile << GamerList[i].Name << "\n";
            OutFile << GamerList[i].username << "\n";
            OutFile << GamerList[i].Department << "\n";
            OutFile << GamerList[i].Roll << "\n";
            OutFile << GamerList[i].HighestScore << "\n";
        }
        OutFile.close();
        sort(RANK.rbegin(), RANK.rend());
        OutFile.open("Leaderboard.txt");
        int i = 1;
        for(auto x : RANK){
            OutFile << i++ << ". " << x.second << " : " << x.first << endl;
        }
        OutFile.close();
    }

    void AddNewGamer(Gamer &G)
    {
        ScoreBoard[G.username] = G.HighestScore;
        GamerList[PlayerNo] = G;

        pair <int, string> p;
        p.first = GamerList[PlayerNo].HighestScore;
        p.second = GamerList[PlayerNo].username;
        RANK.push_back(p);
        sort(RANK.rbegin(), RANK.rend());
        PlayerNo++;

        ofstream OutFile;
        OutFile.open("Database.txt", ios::app);  // Open the file in append mode
        OutFile << G.Name << "\n";
        OutFile << G.username << "\n";
        OutFile << G.Department << "\n";
        OutFile << G.Roll << "\n";
        OutFile << G.HighestScore << "\n";
        OutFile.close();
    }

    void ShowLeaderBoard()
    {
        sort(RANK.rbegin(), RANK.rend());
        ofstream OutFile;
        OutFile.open("Leaderboard.txt"); //Leaderboard File for the Game
        cout << "---------------------------------------------------------\n";
        cout << "--------------------| Leaderboard |----------------------\n";
        cout << "---------------------------------------------------------\n";
        int i = 1;
        for(auto x : RANK){
            OutFile << i << ". " << x.second << " : " << x.first << endl;
            cout << i++ << ". " << x.second << " : " << x.first << endl;
        }
        OutFile.close();
    }

    void ReadDatabase()
    {
        ifstream inFile("Database.txt");
        if (!inFile.is_open()) {
            cerr << "Error: Could not open the file.\n";
            return;
        }
        while (inFile) {
            Gamer G;
            // Read data from the file into the Gamer object
            getline(inFile, G.Name);
            getline(inFile, G.username);
            getline(inFile, G.Department);
            inFile >> G.Roll;
            inFile >> G.HighestScore;
            inFile.ignore();  // Ignore the newline character
            // Check if the input was successful (avoiding reading past end of file)
            if (inFile) {
                GamerList[PlayerNo++] = G;
            }
        }
        inFile.close();
    }
    void UpdateScoreboard()
    {
        for(int i = 0; i < PlayerNo; i++){
            pair <int, string> p;
            p.first = GamerList[i].HighestScore;
            p.second = GamerList[i].username;
            RANK.push_back(p);
        }
        sort(RANK.rbegin(), RANK.rend());
        ofstream OutFile;
        OutFile.open("Leaderboard.txt");
        int i = 1;
        for(auto x : RANK){
            OutFile << i++ << ". " << x.second << " : " << x.first << endl;
            ScoreBoard[x.second] = x.first;
        }
        OutFile.close();
    }
};


void SearchAPlayer(Database admin, string username)
{
    for(int i = 0; i < admin.PlayerNo; i++){
        if(username == admin.GamerList[i].username){
            cout << "---------------------------------------------------------\n";
            cout << "--------------------- Search Result ---------------------\n";
            cout << "---------------------------------------------------------\n";
            cout << admin.GamerList[i] << endl;
            cout << "---------------------------------------------------------\n";
            return;
        }
    }
    cout << "Player not found\n" << endl;
}

Game Geo;
Gamer Player;
Database Admin;
void Home();

void PlayGame(string user)
{
    cout << "---------------------------------------------------------\n";
    cout << "----------------| Starting Geometry Game |---------------\n";
    cout << "---------------------------------------------------------\n";
    int level = 1, score = 0;
    while(Admin.ScoreBoard.find(user) == Admin.ScoreBoard.end()){
        cout << "No User Found!\n";
        cout << "Enter Again (Enter 0 to Exit): ";
        cin >> user;
        if(user == "0") return;
    }
    while(Geo.MakeQues(level)){
        ++level;
    }
    score = (level - 1) * 10;
    cout << "---------------------------------------------------------\n";
    cout << "---------------------| Score : " << score << " |--------------------\n";
    cout << "---------------------------------------------------------\n";

    Admin.Update(user, score); // Updating the Scoreboard and Database
    Admin.UpdateData();

    cout << "1. Play again\n";
    cout << "2. See Leaderboard\n";
    cout << "3. Exit\n";
    cout << "\nSelect an Option : ";
    int k;
    cin >> k;
    while(k > 3 || k < 1){
        cout << "You Have Entered a wrong Key! Enter again : ";
        cin >> k;
    }
    if(k == 1) PlayGame(user);
    else if(k == 2){
        Admin.ShowLeaderBoard();
        Home();
    }
    else{
        return;
    }
}

void Home()
{
    int level = 1;
    cout << "---------------------------------------------------------\n";
    cout << "| | | | | | | | | | | Geometry Game | | | | | | | | | | |\n";
    cout << "---------------------------------------------------------\n";
    cout << "1. Register as a New Player\n";
    cout << "2. Play Game\n";
    cout << "3. Leaderboard\n";
    cout << "4. Search a Player\n";
    cout << "5. Exit\n";
    cout << "\nSelect an Option : ";
    int k;
    cin >> k;
    if(k == 1){
        cin >> Player;
        Admin.AddNewGamer(Player);
        Home();
    }
    else if(k == 2){
        cout << "---------------------------------------------------------\n";
        cout << "Enter Your Username : ";
        string user;
        cin >> user;
        PlayGame(user);
    }
    else if(k == 3){
        Admin.ShowLeaderBoard();
        Home();
    }
    else if(k == 4){
        cout << "Enter Player Username : ";
        string user;
        cin >> user;
        SearchAPlayer(Admin, user);
        Home();
    }
    else if(k == 5){
        return;
    }
    else{
        return;
    }
}

int main()
{
    Admin.ReadDatabase();
    Admin.UpdateScoreboard();
    Home();
    cout << "---------------------------------------------------------\n";
    cout << "---------------------| GAME CLOSED |---------------------\n";
    cout << "---------------------------------------------------------\n";

    return 0;
}
