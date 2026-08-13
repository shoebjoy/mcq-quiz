/*
 * Shoeb Mahmud Joy
 * ID: 192-1513045
 * Daffodil International University
 *
 * Advisor: Syeda Tasmia Alvi Onika
 * Lecturer, Department of CSE
 * Daffodil International University
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

/* ─────────────────────────── Data Structures ─────────────────────────── */

#define POOL_SIZE        20   /* total questions per category              */
#define QUIZ_LENGTH      10   /* questions presented per quiz              */
#define MAX_WRONG         3   /* wrong answers before elimination          */
#define POINTS_PER_Q      5   /* score awarded for each correct answer     */
#define MAX_NAME_LEN     20
#define SCORE_FILE       "Score.txt"

typedef struct {
    const char *question;
    const char *option_a;
    const char *option_b;
    const char *option_c;
    const char *option_d;
    char        answer;       /* 'A', 'B', 'C', or 'D'                    */
} Question;

/* ──────────────────────────── Question Banks ─────────────────────────── */

static const Question international_bank[POOL_SIZE] = {
    { "Which is the largest continent in the world?",
      "Europe",        "Africa",        "Australia",     "Asia",            'D' },
    { "How many UN member countries?",
      "193",           "191",           "195",           "197",             'A' },
    { "Which is the largest country in the world?",
      "Canada",        "China",         "Russia",        "India",           'C' },
    { "Which is the deepest lake in the world?",
      "Lake Baikal",   "Sarez Lake",    "Lake Tanganyika","Lake Tahoe",     'A' },
    { "How many provinces are there in India?",
      "25",            "27",            "31",            "29",              'D' },
    { "How many oceans are there in the world?",
      "5",             "7",             "4",             "6",               'A' },
    { "Which is the deepest ocean in the world?",
      "Atlantic Ocean", "Indian Ocean", "Pacific Ocean", "Arctic Ocean",    'C' },
    { "Which is the deepest place in the world?",
      "Marianas Trench","Puerto Rico Trench","Java Trench","Arctic Basin",  'A' },
    { "Which is the biggest desert in the world?",
      "Kalahari Desert","Sonoran Desert","Sahara Desert", "Arabian Desert", 'C' },
    { "Which is the longest river of the world?",
      "Amazon",        "Nile",          "Congo",         "Lena",            'B' },
    { "Which is the biggest iceland of the world?",
      "Greenland",     "New Guinea",    "Borneo",        "Madagascar",      'A' },
    { "Which is the biggest mountain of the world?",
      "Lhotse",        "Cho Oyu",       "Manaslu",       "Mount Everest",   'D' },
    { "Which is the top country in tea imports?",
      "Russia",        "China",         "India",         "Canada",          'A' },
    { "Which is the top country in tea exports?",
      "Russia",        "China",         "India",         "Canada",          'B' },
    { "In which ocean 'Titanic' sank?",
      "Pacific Ocean", "Atlantic Ocean","Indian Ocean",  "Arctic Ocean",    'B' },
    { "Which is the biggest forest in the world?",
      "Daintree Rainforest","Congo Rainforest","Sundarban","Amazon Rainforest",'D' },
    { "China is forging strategic ties whith which African nation?",
      "Djibouti",      "Liberia",       "Zambia",        "Ethiopia",        'A' },
    { "How many agreements India signed with Philippines in Nov 2017?",
      "3",             "4",             "5",             "6",               'B' },
    { "UNGCP was adopted by UN on Which date?",
      "Dec 22, 2015",  "April 16, 1985","April 18, 1985","Dec 24, 2015",   'B' },
    { "Exercise pitch Black 2018 was hosted by:",
      "South Africa",  "Israel",        "India",         "Australia",       'D' },
};

static const Question bangladesh_bank[POOL_SIZE] = {
    { "When did Bangladesh become an independent country?",
      "1965",          "1952",          "1971",          "1981",            'C' },
    { "Bangladesh was known as:?",
      "Baluchistan",   "East Pakistan", "West Pakistan", "Sindh",           'B' },
    { "Which district of Bangladesh was part of Assam?",
      "Sylhet",        "Chittagong",    "Dinajpur",      "Khulna",          'A' },
    { "Which river of Bangladesh originates in Tibet?",
      "Tista",         "Padma",         "Brahmaputra",   "Surma",           'C' },
    { "What is the national flower of Bangladesh?",
      "Rose",          "Jasmine",       "Lotus",         "Water Lily",      'D' },
    { "In which continent is Bangladesh located?",
      "Africa",        "Asia",          "Europe",        "Australia",       'B' },
    { "The population of Bangladesh is around:",
      "160 million",   "158 million",   "156 million",   "159 million",     'A' },
    { "When was Bangabandhu Satellite-1 launched?",
      "11 March, 2018","11 April, 2018","11 May, 2018",  "11 June, 2018",  'C' },
    { "When is 'International Mother Language Day'?",
      "21 June",       "21 March",      "21 April",      "21 February",     'D' },
    { "Where is the 'Chimbuk' Hill?",
      "Bandarban",     "Sylhet",        "Rangamati",     "Chittagong",      'A' },
    { "Where is the 'Hum Hum' waterfall?",
      "Thanchi, Bandarban","Kamalganj, Moulvibazar","Ruma, Bandarban","Thaikong, Bnadarban",'B' },
    { "What is the national fruit of Bangladesh?",
      "Mango",         "Jack fruit",    "Litchi",        "Apple",           'B' },
    { "How many district in Bangladesh?",
      "63",            "66",            "64",            "65",              'C' },
    { "What is the national bird of Bangladesh?",
      "Magpie",        "Owl",           "Pigeons",       "Ostrich",         'A' },
    { "When did Bangladeshi taka first launched?",
      "Dec 16, 1972",  "June 4, 1972",  "March 4, 1972", "Sept 4, 1972",   'C' },
    { "What is the national animal of Bangladesh?",
      "Lion",          "Royal Bengal Tiger","Leopard",    "Kangaroo",        'B' },
    { "Which organization launched Bangabandhu Satellite-1?",
      "NASA",          "ISRO",          "Roscosmos",     "SpaceX",          'D' },
    { "When is Bangladesh Independence Day?",
      "March 26",      "April 26",      "March 25",      "March 7",         'A' },
    { "When is Bangladesh's Victory Day?",
      "March 7",       "Dec 14",        "Dec 16",        "March 26",        'C' },
    { "How many sea ports in Bangladesh?",
      "3",             "4",             "5",             "2",               'A' },
};

static const Question technology_bank[POOL_SIZE] = {
    { "Bluetooth was invented by which company?",
      "Sony",          "Ericsson",      "Samsung",       "Nokia",           'B' },
    { "Who invented the printing press?",
      "Mary Anderson", "George Antheil","Johannes Gutenberg","Victor Adler", 'C' },
    { "What does 'ATM' stands for?",
      "Automated Teller Machine","Automated Teller Money","Automated Transaction Machine","Automated Transaction Money",'A' },
    { "Who invented World Wide Web?",
      "Tim Barners",   "Dennis Ritchie","Bjarne Stroustrup","John Backus",  'A' },
    { "Atomic bomb was first successfully developed by:",
      "Russia",        "China",         "Germany",       "United States",   'D' },
    { "Frequency Modulation radio was invented by:",
      "Gerald Pearson","Edwin Howard Armstrong","Daryl Chapin","Calvin Southern Fuller",'B' },
    { "Printing press was invented in:",
      "1440",          "1436",          "1486",          "1446",            'A' },
    { "'DVD' was developed by:",
      "Sony",          "Intel",         "Panasonic",     "Both A and B",    'D' },
    { "Facebook invented year:",
      "2003",          "2000",          "2004",          "2002",            'C' },
    { "Compass was invented by:",
      "Europeans",     "Chinese",       "Romans",        "Greeks",          'B' },
    { "First personal computer controlled with a keyboard was invented by:",
      "Apple",         "Microsoft",     "Hewlett Packard","IBM",            'D' },
    { "Telephone was invented by:",
      "Alexander Graham Bell","Alexander Fleming","Howard Armstrong","Ferdinand Magellan",'A' },
    { "First Graphical user Interface (GUI) was popularized as:",
      "Xerox Star",    "Apple Lisa",    "IBM 610",       "Both A and B",    'D' },
    { "'DVD' was invented in:",
      "1990",          "1995",          "1997",          "1992",            'B' },
    { "First Freely programmable computer in world was built in:",
      "1936",          "1934",          "1938",          "1932",            'C' },
    { "First personal computer controlled with a keyboard is:",
      "IBM 610",       "hp 610",        "Intel 210",     "IBM 800",         'A' },
    { "First freely programmable computer in world was built by:",
      "Karl Benz",     "Percy Spencer", "Konrad Zuse",   "Georage Stepheman",'C' },
    { "Name of first popular web browser is:",
      "IBM browser",   "NCSA Mosaic",   "Google Chrome",  "Mozilla Firefox", 'B' },
    { "'FM' radio was invented in:",
      "1934",          "1936",          "1939",          "1933",            'D' },
    { "Airplane was invented by:",
      "Wright Brothers","Robert Adler",  "Ernst Abbe",    "Edwin Armstrong", 'A' },
};

static const Question sports_bank[POOL_SIZE] = {
    { "When was BCB founded?",
      "1973",          "1975",          "1972",          "1974",            'C' },
    { "Where is the BCB headquarters?",
      "Dhaka",         "Khulna",        "Sylhet",        "Bogra",           'A' },
    { "When was the first common wealth games held?",
      "1934",          "1930",          "1938",          "1948",            'B' },
    { "In which sports is the participant called pugilist?",
      "Sprinter",      "Wrestling",     "Javelin throw", "Boxing",          'D' },
    { "The term 'Butterfly Stroke' is referred to in which sport?",
      "Wrestling",     "Volley Ball",   "Swimming",      "Tennis",          'C' },
    { "In which game the term 'Putting' is used?",
      "Golf",          "Chess",         "Hockey",        "Billiards",       'A' },
    { "Thomas Cup is related to:",
      "Tennis",        "Badminton",     "Cricket",       "Basketball",      'B' },
    { "The number of players in each side in water polo is:",
      "6",             "8",             "9",             "7",               'D' },
    { "Which was the first country to host the Asian Games?",
      "China",         "Japan",         "India",         "Korea",           'C' },
    { "Where is the headquarters of the International Olympic Committee located?",
      "Switzerland",   "France",        "Belgium",       "Italy",           'A' },
    { "'Free throw' is associate with:",
      "Hockey",        "Basketball",    "Volley Ball",   "Football",        'B' },
    { "2018 'FIFA' world cup held in:",
      "Qatar",         "Netherlands",   "France",        "Russia",          'D' },
    { "The first world cup cricket was held in:",
      "1971",          "1973",          "1975",          "1977",            'C' },
    { "Where did the game of chess originate?",
      "India",         "Persia",        "Arabia",        "Europe",          'A' },
    { "How many players are there on each side in the game of cricket?",
      "11",            "10",            "12",            "13",              'A' },
    { "The distance of marathon race is:",
      "24 miles",      "26 miles",      "25 miles",      "28 miles",        'B' },
    { "What is the maximum permitted length of cricket bat?",
      "36 inches",     "37 inches",     "38 inches",     "39 inches",       'C' },
    { "Green Park Stadium is in:",
      "Kanpur, India", "Dehradun, India","Bengaluru, India","Chandigarh, India",'A' },
    { "Which of the following is not correct?",
      "Sania Mirza(Tennis)","Jeev Milkha Singh(Football)","Saina Nehwal(Badminton)","Vishwanathan Anand(Chess)",'B' },
    { "India won it's first Olympic hockey gold in:",
      "1924",          "1932",          "1948",          "1928",            'D' },
};

/* ─────────────────────── Category Lookup Table ───────────────────────── */

typedef struct {
    const char     *name;
    const Question *bank;
} Category;

static const Category categories[] = {
    { "International", international_bank },
    { "Bangladesh",    bangladesh_bank    },
    { "Technology",    technology_bank    },
    { "Sports",        sports_bank        },
};

#define NUM_CATEGORIES  (sizeof(categories) / sizeof(categories[0]))

/* ───────────────────── Fisher-Yates Shuffle Helper ───────────────────── */

static void shuffle_indices(int *arr, int n)
{
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

/* ─────────────────────── Performance Feedback ────────────────────────── */

static void print_feedback(int score)
{
    if (score == 50)
        printf("\n\n\t\tExcellent!!! Keep it up :)");
    else if (score >= 40)
        printf("\n\n\t\tVery Good!!");
    else if (score >= 20)
        printf("\n\n\t\tGood! But You Need to Know More :)");
    else if (score >= 10)
        printf("\n\n\t\tSatisfactory Result, Study More :)");
    else
        printf("\n\n\t\tYour General Knowledge is Very Poor :(");
    printf("\n");
}

/* ──────────────────── Generic Quiz Engine (core) ─────────────────────── */

static int run_quiz(const Question *bank)
{
    int indices[POOL_SIZE];
    int correct = 0;
    int wrong   = 0;
    int asked   = 0;

    /* Build and shuffle index array for random, non-repeating selection. */
    for (int i = 0; i < POOL_SIZE; ++i)
        indices[i] = i;
    shuffle_indices(indices, POOL_SIZE);

    while (asked < QUIZ_LENGTH && wrong < MAX_WRONG) {
        system("cls");

        const Question *q = &bank[indices[asked]];
        const char *options[] = { q->option_a, q->option_b, q->option_c, q->option_d };

        printf("\n\n%s", q->question);
        printf("\n\nA.%s\tB.%s\n\nC.%s\tD.%s\n\n",
               options[0], options[1], options[2], options[3]);

        char input = (char)toupper(getch());

        if (input == q->answer) {
            printf("\n\nCorrect!!!");
            ++correct;
        } else {
            Beep(1000, 500);
            printf("\n\nWrong!!! The correct answer is %c.%s;\n",
                   q->answer, options[q->answer - 'A']);
            ++wrong;
        }
        ++asked;
        getch();  /* pause so the user can read the result */
    }

    /* Elimination message */
    if (wrong >= MAX_WRONG) {
        system("cls");
        Beep(5000, 500);
        printf("\n\n\t\tYou have given 3 wrong answer;\n\n\t\tYou cannot play anymore;");
    }

    int score = correct * POINTS_PER_Q;
    if (score < 0) score = 0;

    print_feedback(score);
    return score;
}

/* ────────────────────── Score Persistence (File I/O) ─────────────────── */

static void show_scoreboard(void)
{
    char name[MAX_NAME_LEN];
    float scr;
    FILE *fp;

    system("cls");
    fp = fopen(SCORE_FILE, "r");
    if (fp && fscanf(fp, "%19s %f", name, &scr) == 2) {
        printf("\t%s is the current high scorer with the score of %.2f", name, scr);
        printf("\n\n\t\t ");
        fclose(fp);
    } else {
        if (fp) fclose(fp);
        printf("\tNo high score recorded yet.\n");
    }
    getch();
}

static void set_score(const char *player_name, float score)
{
    char hn[MAX_NAME_LEN];
    float hs = -1.0f;
    FILE *fp;

    system("cls");
    fp = fopen(SCORE_FILE, "r");
    if (fp) {
        fscanf(fp, "%19s %f", hn, &hs);
        fclose(fp);
    }

    if (score >= hs) {
        fp = fopen(SCORE_FILE, "w");
        if (fp) {
            fprintf(fp, "%s %.2f", player_name, score);
            fclose(fp);
        }
    }
}

static void reset_high_score(void)
{
    FILE *fp = fopen(SCORE_FILE, "w");
    system("cls");
    if (fp) fclose(fp);
    printf("\n\t\tHigh score has been reset.\n");
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
static void show_credits(void)
{
    system("cls");
    printf("\n\t\t\t***************************** Credits *****************************");
    printf("\n\n\n\tAdvisor of this project:\n\tSyeda Tasmia Alvi Onika\n\tLecturer, Department of CSE\n\tDaffodil International University\n\n\n");
    printf("\n\n\n\tPresented by:\n\tShoeb Mahmud Joy\n\tID: 192-15-13045\n\tDaffodil International University");
}

static void show_rules(void)
{
    system("cls");
    printf("\n\t\t\t***************************** GAME RULES *****************************");
    printf("\n\n\n\t1.You have 10 question to answer.");
    printf("\n\n\t2.You will be given 4 options and you have to press A, B, C, D for the right option.");
    printf("\n\n\t3.Without A, B, C, D, if you press any other button for answering your question it will count as wrong answer.");
    printf("\n\n\t4.Each question will carry 5 points.");
    printf("\n\n\t5.The game will automatically end after answering 3 questions incorrectly.");
    printf("\n\n\t6.There is no negative marking for wrong answer.");
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tGOOD LUCK:)");
}

/* ───────────────────────────── Main Menu ─────────────────────────────── */

int main(void)
{
    char name[MAX_NAME_LEN];
    char ch;
    bool running = true;

    srand((unsigned)time(NULL));   /* seed PRNG exactly once */

    while (running) {
        system("cls");
        puts("\n\t\t***************************** WELCOME TO Quiz Test Program 2021 *****************************\n\n");
        puts("\n\t\t Enter the mentioned keywords for its assigned action:");
        puts("\n\t\t A.Start Game");
        puts("\n\t\t B.High Score");
        puts("\n\t\t C.Reset High Score");
        puts("\n\t\t D.Rules");
        puts("\n\t\t E.Credits");
        puts("\n\t\t F.Exit");

        ch = (char)toupper(getch());

        switch (ch) {
        case 'A': {
            printf("\n\n\n\t\tPlease Enter your Name:\t");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';  /* strip trailing newline */

            system("cls");
            printf("\n\n\t\tPress S to start the quiz\n");
            if (toupper(getch()) != 'S')
                break;

            /* Category selection loop */
            for (;;) {
                system("cls");
                printf("\n\n\t\tPlease select the subject you prefer for your quiz:\n");
                printf("\n\t\t1.International\t2.Bangladesh\n\n\t\t3.Technology\t4.Sports");

                char cat = (char)getch();
                int idx = cat - '1';   /* 0..3 */

                if (idx >= 0 && idx < (int)NUM_CATEGORIES) {
                    float score = (float)run_quiz(categories[idx].bank);
                    printf("\n\t\tYour Score: %.2f;\n", score);
                    getch();
                    set_score(name, score);
                    break;
                }

                printf("\n\n\n\t\tInvalid Input:(\n");
                getch();
            }
            break;
        }
        case 'B':
            show_scoreboard();
            break;
        case 'C':
            reset_high_score();
            getch();
            break;
        case 'D':
            show_rules();
            getch();
            break;
        case 'E':
            show_credits();
            getch();
            break;
        case 'F':
            printf("Exiting");
            system("cls");
            running = false;
            break;
        default:
            printf("\n\n\n\n\t\t!!!!!Invalid Keyword!!!!!!\n");
            getch();
            break;
        }
    }

    return 0;
}
