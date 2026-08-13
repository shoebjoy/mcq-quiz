/*
 * Shoeb Mahmud Joy
 * ID: 192-1513045
 * Daffodil International University
 *
 * Advisor: Syeda Tasmia Alvi Onika
 * Lecturer, Department of CSE
 * Daffodil International University
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

/* ─────────────────────────── Constants ────────────────────────────────── */

constexpr int POOL_SIZE      = 20;
constexpr int QUIZ_LENGTH    = 10;
constexpr int MAX_WRONG      = 3;
constexpr int POINTS_PER_Q   = 5;
constexpr int MAX_NAME_LEN   = 20;
constexpr const char* SCORE_FILE = "Score.txt";

/* ─────────────────────────── Data Structures ─────────────────────────── */

struct Question {
    std::string question;
    std::array<std::string, 4> options;   // A, B, C, D
    char answer;                          // 'A', 'B', 'C', or 'D'

    [[nodiscard]] const std::string& correct_text() const {
        return options[answer - 'A'];
    }
};

/* ──────────────────────────── Question Banks ─────────────────────────── */

static std::vector<Question> build_international_bank()
{
    return {{
        {"Which is the largest continent in the world?",
         {"Europe","Africa","Australia","Asia"}, 'D'},
        {"How many UN member countries?",
         {"193","191","195","197"}, 'A'},
        {"Which is the largest country in the world?",
         {"Canada","China","Russia","India"}, 'C'},
        {"Which is the deepest lake in the world?",
         {"Lake Baikal","Sarez Lake","Lake Tanganyika","Lake Tahoe"}, 'A'},
        {"How many provinces are there in India?",
         {"25","27","31","29"}, 'D'},
        {"How many oceans are there in the world?",
         {"5","7","4","6"}, 'A'},
        {"Which is the deepest ocean in the world?",
         {"Atlantic Ocean","Indian Ocean","Pacific Ocean","Arctic Ocean"}, 'C'},
        {"Which is the deepest place in the world?",
         {"Marianas Trench","Puerto Rico Trench","Java Trench","Arctic Basin"}, 'A'},
        {"Which is the biggest desert in the world?",
         {"Kalahari Desert","Sonoran Desert","Sahara Desert","Arabian Desert"}, 'C'},
        {"Which is the longest river of the world?",
         {"Amazon","Nile","Congo","Lena"}, 'B'},
        {"Which is the biggest iceland of the world?",
         {"Greenland","New Guinea","Borneo","Madagascar"}, 'A'},
        {"Which is the biggest mountain of the world?",
         {"Lhotse","Cho Oyu","Manaslu","Mount Everest"}, 'D'},
        {"Which is the top country in tea imports?",
         {"Russia","China","India","Canada"}, 'A'},
        {"Which is the top country in tea exports?",
         {"Russia","China","India","Canada"}, 'B'},
        {"In which ocean 'Titanic' sank?",
         {"Pacific Ocean","Atlantic Ocean","Indian Ocean","Arctic Ocean"}, 'B'},
        {"Which is the biggest forest in the world?",
         {"Daintree Rainforest","Congo Rainforest","Sundarban","Amazon Rainforest"}, 'D'},
        {"China is forging strategic ties whith which African nation?",
         {"Djibouti","Liberia","Zambia","Ethiopia"}, 'A'},
        {"How many agreements India signed with Philippines in Nov 2017?",
         {"3","4","5","6"}, 'B'},
        {"UNGCP was adopted by UN on Which date?",
         {"Dec 22, 2015","April 16, 1985","April 18, 1985","Dec 24, 2015"}, 'B'},
        {"Exercise pitch Black 2018 was hosted by:",
         {"South Africa","Israel","India","Australia"}, 'D'},
    }};
}

static std::vector<Question> build_bangladesh_bank()
{
    return {{
        {"When did Bangladesh become an independent country?",
         {"1965","1952","1971","1981"}, 'C'},
        {"Bangladesh was known as:?",
         {"Baluchistan","East Pakistan","West Pakistan","Sindh"}, 'B'},
        {"Which district of Bangladesh was part of Assam?",
         {"Sylhet","Chittagong","Dinajpur","Khulna"}, 'A'},
        {"Which river of Bangladesh originates in Tibet?",
         {"Tista","Padma","Brahmaputra","Surma"}, 'C'},
        {"What is the national flower of Bangladesh?",
         {"Rose","Jasmine","Lotus","Water Lily"}, 'D'},
        {"In which continent is Bangladesh located?",
         {"Africa","Asia","Europe","Australia"}, 'B'},
        {"The population of Bangladesh is around:",
         {"160 million","158 million","156 million","159 million"}, 'A'},
        {"When was Bangabandhu Satellite-1 launched?",
         {"11 March, 2018","11 April, 2018","11 May, 2018","11 June, 2018"}, 'C'},
        {"When is 'International Mother Language Day'?",
         {"21 June","21 March","21 April","21 February"}, 'D'},
        {"Where is the 'Chimbuk' Hill?",
         {"Bandarban","Sylhet","Rangamati","Chittagong"}, 'A'},
        {"Where is the 'Hum Hum' waterfall?",
         {"Thanchi, Bandarban","Kamalganj, Moulvibazar","Ruma, Bandarban","Thaikong, Bnadarban"}, 'B'},
        {"What is the national fruit of Bangladesh?",
         {"Mango","Jack fruit","Litchi","Apple"}, 'B'},
        {"How many district in Bangladesh?",
         {"63","66","64","65"}, 'C'},
        {"What is the national bird of Bangladesh?",
         {"Magpie","Owl","Pigeons","Ostrich"}, 'A'},
        {"When did Bangladeshi taka first launched?",
         {"Dec 16, 1972","June 4, 1972","March 4, 1972","Sept 4, 1972"}, 'C'},
        {"What is the national animal of Bangladesh?",
         {"Lion","Royal Bengal Tiger","Leopard","Kangaroo"}, 'B'},
        {"Which organization launched Bangabandhu Satellite-1?",
         {"NASA","ISRO","Roscosmos","SpaceX"}, 'D'},
        {"When is Bangladesh Independence Day?",
         {"March 26","April 26","March 25","March 7"}, 'A'},
        {"When is Bangladesh's Victory Day?",
         {"March 7","Dec 14","Dec 16","March 26"}, 'C'},
        {"How many sea ports in Bangladesh?",
         {"3","4","5","2"}, 'A'},
    }};
}

static std::vector<Question> build_technology_bank()
{
    return {{
        {"Bluetooth was invented by which company?",
         {"Sony","Ericsson","Samsung","Nokia"}, 'B'},
        {"Who invented the printing press?",
         {"Mary Anderson","George Antheil","Johannes Gutenberg","Victor Adler"}, 'C'},
        {"What does 'ATM' stands for?",
         {"Automated Teller Machine","Automated Teller Money","Automated Transaction Machine","Automated Transaction Money"}, 'A'},
        {"Who invented World Wide Web?",
         {"Tim Barners","Dennis Ritchie","Bjarne Stroustrup","John Backus"}, 'A'},
        {"Atomic bomb was first successfully developed by:",
         {"Russia","China","Germany","United States"}, 'D'},
        {"Frequency Modulation radio was invented by:",
         {"Gerald Pearson","Edwin Howard Armstrong","Daryl Chapin","Calvin Southern Fuller"}, 'B'},
        {"Printing press was invented in:",
         {"1440","1436","1486","1446"}, 'A'},
        {"'DVD' was developed by:",
         {"Sony","Intel","Panasonic","Both A and B"}, 'D'},
        {"Facebook invented year:",
         {"2003","2000","2004","2002"}, 'C'},
        {"Compass was invented by:",
         {"Europeans","Chinese","Romans","Greeks"}, 'B'},
        {"First personal computer controlled with a keyboard was invented by:",
         {"Apple","Microsoft","Hewlett Packard","IBM"}, 'D'},
        {"Telephone was invented by:",
         {"Alexander Graham Bell","Alexander Fleming","Howard Armstrong","Ferdinand Magellan"}, 'A'},
        {"First Graphical user Interface (GUI) was popularized as:",
         {"Xerox Star","Apple Lisa","IBM 610","Both A and B"}, 'D'},
        {"'DVD' was invented in:",
         {"1990","1995","1997","1992"}, 'B'},
        {"First Freely programmable computer in world was built in:",
         {"1936","1934","1938","1932"}, 'C'},
        {"First personal computer controlled with a keyboard is:",
         {"IBM 610","hp 610","Intel 210","IBM 800"}, 'A'},
        {"First freely programmable computer in world was built by:",
         {"Karl Benz","Percy Spencer","Konrad Zuse","Georage Stepheman"}, 'C'},
        {"Name of first popular web browser is:",
         {"IBM browser","NCSA Mosaic","Google Chrome","Mozilla Firefox"}, 'B'},
        {"'FM' radio was invented in:",
         {"1934","1936","1939","1933"}, 'D'},
        {"Airplane was invented by:",
         {"Wright Brothers","Robert Adler","Ernst Abbe","Edwin Armstrong"}, 'A'},
    }};
}

static std::vector<Question> build_sports_bank()
{
    return {{
        {"When was BCB founded?",
         {"1973","1975","1972","1974"}, 'C'},
        {"Where is the BCB headquarters?",
         {"Dhaka","Khulna","Sylhet","Bogra"}, 'A'},
        {"When was the first common wealth games held?",
         {"1934","1930","1938","1948"}, 'B'},
        {"In which sports is the participant called pugilist?",
         {"Sprinter","Wrestling","Javelin throw","Boxing"}, 'D'},
        {"The term 'Butterfly Stroke' is referred to in which sport?",
         {"Wrestling","Volley Ball","Swimming","Tennis"}, 'C'},
        {"In which game the term 'Putting' is used?",
         {"Golf","Chess","Hockey","Billiards"}, 'A'},
        {"Thomas Cup is related to:",
         {"Tennis","Badminton","Cricket","Basketball"}, 'B'},
        {"The number of players in each side in water polo is:",
         {"6","8","9","7"}, 'D'},
        {"Which was the first country to host the Asian Games?",
         {"China","Japan","India","Korea"}, 'C'},
        {"Where is the headquarters of the International Olympic Committee located?",
         {"Switzerland","France","Belgium","Italy"}, 'A'},
        {"'Free throw' is associate with:",
         {"Hockey","Basketball","Volley Ball","Football"}, 'B'},
        {"2018 'FIFA' world cup held in:",
         {"Qatar","Netherlands","France","Russia"}, 'D'},
        {"The first world cup cricket was held in:",
         {"1971","1973","1975","1977"}, 'C'},
        {"Where did the game of chess originate?",
         {"India","Persia","Arabia","Europe"}, 'A'},
        {"How many players are there on each side in the game of cricket?",
         {"11","10","12","13"}, 'A'},
        {"The distance of marathon race is:",
         {"24 miles","26 miles","25 miles","28 miles"}, 'B'},
        {"What is the maximum permitted length of cricket bat?",
         {"36 inches","37 inches","38 inches","39 inches"}, 'C'},
        {"Green Park Stadium is in:",
         {"Kanpur, India","Dehradun, India","Bengaluru, India","Chandigarh, India"}, 'A'},
        {"Which of the following is not correct?",
         {"Sania Mirza(Tennis)","Jeev Milkha Singh(Football)","Saina Nehwal(Badminton)","Vishwanathan Anand(Chess)"}, 'B'},
        {"India won it's first Olympic hockey gold in:",
         {"1924","1932","1948","1928"}, 'D'},
    }};
}

/* ─────────────────────── Category Abstraction ────────────────────────── */

struct Category {
    std::string              name;
    std::vector<Question>    bank;
};

static std::vector<Category> build_categories()
{
    std::vector<Category> cats;
    cats.push_back({"International", build_international_bank()});
    cats.push_back({"Bangladesh",    build_bangladesh_bank()});
    cats.push_back({"Technology",    build_technology_bank()});
    cats.push_back({"Sports",        build_sports_bank()});
    return cats;
}

/* ─────────────────────── Performance Feedback ────────────────────────── */

static void print_feedback(int score)
{
    if (score == 50)
        std::cout << "\n\n\t\tExcellent!!! Keep it up :)";
    else if (score >= 40)
        std::cout << "\n\n\t\tVery Good!!";
    else if (score >= 20)
        std::cout << "\n\n\t\tGood! But You Need to Know More :)";
    else if (score >= 10)
        std::cout << "\n\n\t\tSatisfactory Result, Study More :)";
    else
        std::cout << "\n\n\t\tYour General Knowledge is Very Poor :(";
    std::cout << '\n';
}

/* ──────────────────── Generic Quiz Engine (core) ─────────────────────── */

static int run_quiz(const std::vector<Question>& bank)
{
    /* Build shuffled index array for random, non-repeating selection. */
    std::vector<int> indices(POOL_SIZE);
    for (int i = 0; i < POOL_SIZE; ++i)
        indices[i] = i;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(indices.begin(), indices.end(), rng);

    int correct = 0;
    int wrong   = 0;
    int asked   = 0;

    while (asked < QUIZ_LENGTH && wrong < MAX_WRONG) {
        system("cls");

        const Question& q = bank[indices[asked]];

        std::cout << "\n\n" << q.question;
        std::cout << "\n\nA." << q.options[0] << "\tB." << q.options[1]
                  << "\n\nC." << q.options[2] << "\tD." << q.options[3]
                  << "\n\n";

        char input = static_cast<char>(std::toupper(_getch()));

        if (input == q.answer) {
            std::cout << "\n\nCorrect!!!";
            ++correct;
        } else {
            Beep(1000, 500);
            std::cout << "\n\nWrong!!! The correct answer is "
                      << q.answer << '.' << q.correct_text() << ";\n";
            ++wrong;
        }
        ++asked;
        _getch();   /* pause so the user can read the result */
    }

    /* Elimination message */
    if (wrong >= MAX_WRONG) {
        system("cls");
        Beep(5000, 500);
        std::cout << "\n\n\t\tYou have given 3 wrong answer;\n\n\t\tYou cannot play anymore;";
    }

    int score = correct * POINTS_PER_Q;
    if (score < 0) score = 0;

    print_feedback(score);
    return score;
}

/* ────────────────────── Score Persistence (File I/O) ─────────────────── */

static void show_scoreboard()
{
    system("cls");
    std::ifstream ifs(SCORE_FILE);
    std::string name;
    float scr = 0.0f;

    if (ifs >> name >> scr) {
        std::cout << '\t' << name
                  << " is the current high scorer with the score of "
                  << scr << "\n\n\t\t ";
    } else {
        std::cout << "\tNo high score recorded yet.\n";
    }
    _getch();
}

static void set_score(const std::string& player_name, float score)
{
    system("cls");
    std::string hn;
    float hs = -1.0f;

    {
        std::ifstream ifs(SCORE_FILE);
        if (ifs.is_open())
            ifs >> hn >> hs;
    }

    if (score >= hs) {
        std::ofstream ofs(SCORE_FILE, std::ios::trunc);
        if (ofs.is_open())
            ofs << player_name << ' ' << score;
    }
}

static void reset_high_score()
{
    system("cls");
    std::ofstream ofs(SCORE_FILE, std::ios::trunc);
    std::cout << "\n\t\tHigh score has been reset.\n";
}

/* ────────────────────────── Info Screens ──────────────────────────────── */

/*
 * Advisor of this project:
 * Syeda Tasmia Alvi Onika
 * Lecturer, Department of CSE
 * Daffodil International University
 *
 * Presented by:
 * Shoeb Mahmud Joy
 * ID: 192-15-13045
 * Daffodil International University
 */
static void show_credits()
{
    system("cls");
    std::cout << "\n\t\t\t***************************** Credits *****************************";
    std::cout << "\n\n\n\tAdvisor of this project:\n\tSyeda Tasmia Alvi Onika\n\tLecturer, Department of CSE\n\tDaffodil International University\n\n\n";
    std::cout << "\n\n\n\tPresented by:\n\tShoeb Mahmud Joy\n\tID: 192-15-13045\n\tDaffodil International University";
}

static void show_rules()
{
    system("cls");
    std::cout << "\n\t\t\t***************************** GAME RULES *****************************";
    std::cout << "\n\n\n\t1.You have 10 question to answer.";
    std::cout << "\n\n\t2.You will be given 4 options and you have to press A, B, C, D for the right option.";
    std::cout << "\n\n\t3.Without A, B, C, D, if you press any other button for answering your question it will count as wrong answer.";
    std::cout << "\n\n\t4.Each question will carry 5 points.";
    std::cout << "\n\n\t5.The game will automatically end after answering 3 questions incorrectly.";
    std::cout << "\n\n\t6.There is no negative marking for wrong answer.";
    std::cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tGOOD LUCK:)";
}

/* ───────────────────────────── Main Menu ─────────────────────────────── */

int main()
{
    auto categories = build_categories();
    bool running = true;

    while (running) {
        system("cls");
        std::cout << "\n\t\t***************************** WELCOME TO Quiz Test Program 2021 *****************************\n\n";
        std::cout << "\n\t\t Enter the mentioned keywords for its assigned action:";
        std::cout << "\n\t\t A.Start Game";
        std::cout << "\n\t\t B.High Score";
        std::cout << "\n\t\t C.Reset High Score";
        std::cout << "\n\t\t D.Rules";
        std::cout << "\n\t\t E.Credits";
        std::cout << "\n\t\t F.Exit" << std::endl;

        char ch = static_cast<char>(std::toupper(_getch()));

        switch (ch) {
        case 'A': {
            std::cout << "\n\n\n\t\tPlease Enter your Name:\t";
            std::string name;
            std::getline(std::cin, name);
            if (name.length() > MAX_NAME_LEN)
                name.resize(MAX_NAME_LEN);

            system("cls");
            std::cout << "\n\n\t\tPress S to start the quiz\n";
            if (std::toupper(_getch()) != 'S')
                break;

            /* Category selection loop */
            for (;;) {
                system("cls");
                std::cout << "\n\n\t\tPlease select the subject you prefer for your quiz:\n";
                std::cout << "\n\t\t1.International\t2.Bangladesh\n\n\t\t3.Technology\t4.Sports";

                int idx = _getch() - '1';   // 0..3

                if (idx >= 0 && idx < static_cast<int>(categories.size())) {
                    float score = static_cast<float>(run_quiz(categories[idx].bank));
                    std::cout << "\n\t\tYour Score: " << score << ";\n";
                    _getch();
                    set_score(name, score);
                    break;
                }

                std::cout << "\n\n\n\t\tInvalid Input:(\n";
                _getch();
            }
            break;
        }
        case 'B':
            show_scoreboard();
            break;
        case 'C':
            reset_high_score();
            _getch();
            break;
        case 'D':
            show_rules();
            _getch();
            break;
        case 'E':
            show_credits();
            _getch();
            break;
        case 'F':
            std::cout << "Exiting";
            system("cls");
            running = false;
            break;
        default:
            std::cout << "\n\n\n\n\t\t!!!!!Invalid Keyword!!!!!!\n";
            _getch();
            break;
        }
    }

    return 0;
}
