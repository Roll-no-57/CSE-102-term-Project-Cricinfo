#include "iGraphics.h"
// for suffle random number
char file_ranking_Test[50] = "File Input//icc_rank_Test.txt";
char file_ranking_ODI[50] = "File Input//icc_rank_odi.txt";
char file_ranking_t20[50] = "File Input//icc_rank_t20.txt";
char file_bowling_ODI[50] = "File Input//bowling_odi.txt";
char file_bowling_Test[50] = "File Input//bowling_test.txt";
char file_bowling_t20[50] = "File Input//bowling_t20.txt";
char file_batting_ODI[50] = "File Input//batting_odi.txt";
char file_batting_Test[50] = "File Input//batting_test.txt";
char file_batting_t20[50] = "File Input//batting_t20.txt";
char file_allrounder_ODI[50] = "File Input//allrounder_odi.txt";
char file_allrounder_Test[50] = "File Input//allrounder_test.txt";
char file_allrounder_t20[50] = "File Input//allrounder_t20.txt";

// for players
char TamimAccount[300] = "File Input//TamimAccount.txt";

time_t t1;
int interval = 500;

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define MENU_CLR 0, 146, 112
#define CHAI 227, 230, 227
#define Halka_chai 235, 230, 235
// window width and height
#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 620

// Headers colors define
#define menu_color 1
#define matches_color 2

// globally initialized header variables
#define header_menu_text_no 7
#define header_matches_text_no 7

// Header Text
char Header_matches_text[header_matches_text_no][100] = {"MATCHES", "NZ vs SL", "ENG vs AUS", "UAE vs AFG", "BD VS SA"};
// for ranking

// For all Match boxes
// for match texts
#define Match_Text_r 8
#define Match_Text_c 150
// Match Box photos
#define mat_teams_bmp_r 2
#define mat_teams_bmp_c 100
// for match type
#define match_type_text_r 1
#define match_type_text_c 10

// for todays match
#define today_mat_text_r 5
#define today_mat_text_c 60
// for news match
#define news_mat_bmp_r 6
#define news_mat_bmp_c 60

// for teams text
#define teams_text_r 15
#define teams_text_c 50

#define teams_name_text_r 9
#define teams_name_text_c 50

#define teams_type_text_r 3
#define teams_type_text_c 50

char Name_input[1000] = {0};
char Email_input[1000] = {0};
char Photo_input[1000] = {0};

int name_idx = -1;
int email_idx = -1;
int photo_idx = -1;
bool teamsHomepage = false;
enum MouseState
{
    id_1_input,
    id_2_input,
    profile_in,
    nothing
};
MouseState current_mouseState = nothing;

// Different Page opening
enum mainPageState
{
    intro,
    HomePage,
    LiveScorePage,
    SchedulePage,
    NewsPage,
    RankingPage,
    TeamsPage,
    LogInPage

};
mainPageState currentMainPage = intro, previousMainPage = intro;

enum RankingPageState
{
    rank_team,
    rank_batsman,
    rank_bowler,
    rank_allrounder
};
RankingPageState currentRankState;

enum Pagestate
{

    LiveScoreLivePage,
    LiveScorePastPage,
    LiveScoreUpcomingPage,

    ScheduleInternationalPage,
    ScheduleDomesticPage,

    Test,
    ODI,
    t20,

    LogInputPage,
    AccountInformationPage,

    // Bangladesh_player

    // TeamBangladesh,
    // TeamIndia,
    // TeamPakistan,

    // TeamKolkata,
    // TeamChennai

};

Pagestate currentPage, previousPage;
// enum current_coun
// {

// };
// current_coun current_desh;
enum Countries
{
    country_Players,
    country_stats,
    country_tamim
};
Countries current_country_state;

enum TeamsTypePageState
{
    TeamsInternationalPage,
    TeamsDomesticPage,
    BD,
    IND,
    PAK,
    KNR,
    DD,
    none
};
TeamsTypePageState currentTeamType;

// enum TeamsHomepage{

// };

// TeamsHomepage currentsTeamsPage;

bool TeamsHomePage = false;
bool BangladeshHomepage = false;

enum PlayerName
{

    tamim_box,
    shanto_box
};

PlayerName currentPlayer;

// draw Background
void drawBG()
{
    iSetColor(WHITE);
    iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
//---------------------------------------------------------------------------------
// header struct
typedef struct
{
    int x;
    int y;
    int w;
    int h;
    int color;
} Header;

Header menu, matches, live_score, schedule, NEWS, ranking, teams, Login;

// initialize header variables
void initHeader()
{

    menu.x = 50;
    menu.y = 550;
    menu.w = 950;
    menu.h = 50;
    menu.color = menu_color;

    matches.x = menu.x;
    matches.y = menu.y - 30;
    matches.w = menu.w;
    matches.h = menu.h - 20;
    matches.color = matches_color;

    live_score.x = menu.x + 130;
    live_score.y = menu.y;
    live_score.w = 130;
    live_score.h = menu.h;

    schedule.x = live_score.x + 130;
    schedule.y = menu.y;
    schedule.w = 130;
    schedule.h = menu.h;

    NEWS.x = schedule.x + 130;
    NEWS.y = menu.y;
    NEWS.w = 130;
    NEWS.h = menu.h;

    ranking.x = NEWS.x + 130;
    ranking.y = menu.y;
    ranking.w = 130;
    ranking.h = menu.h;

    teams.x = ranking.x + 130;
    teams.y = menu.y;
    teams.w = 130;
    teams.h = menu.h;

    Login.x = teams.x + 130;
    Login.y = menu.y;
    Login.w = 130;
    Login.h = menu.h;
}

// draw header
void drawHeaderBox(Header box)
{
    if (box.color == menu_color)
    {
        iSetColor(0, 146, 112);
    }
    if (box.color == matches_color)
    {
        iSetColor(0, 0, 0);
    }
    iFilledRectangle(box.x, box.y, box.w, box.h);
}

// write headers on header
void drawHeaderTextBox()
{
    iSetColor(0, 0, 0);

    iText(menu.x + 20, menu.y + 20, "CRICINFO", GLUT_BITMAP_9_BY_15);
    iText(live_score.x + 20, live_score.y + 20, "LIVE SCORE", GLUT_BITMAP_9_BY_15);
    iText(schedule.x + 20, schedule.y + 20, "SCHEDULE", GLUT_BITMAP_9_BY_15);
    iText(NEWS.x + 20, NEWS.y + 20, "NEWS", GLUT_BITMAP_9_BY_15);
    iText(ranking.x + 20, ranking.y + 20, "RANKING", GLUT_BITMAP_9_BY_15);
    iText(teams.x + 20, teams.y + 20, "TEAMS", GLUT_BITMAP_9_BY_15);
    iText(Login.x + 20, Login.y + 20, "LOGIN", GLUT_BITMAP_9_BY_15);

    iSetColor(255, 255, 255);
    for (int i = 0; i < header_matches_text_no; i++)
    {
        iText(matches.x + 20 + i * 130, matches.y + 11, Header_matches_text[i], GLUT_BITMAP_8_BY_13);
    }
}

// for all header function
void drawAllHeader()
{
    drawHeaderBox(menu);
    drawHeaderBox(matches);
    drawHeaderTextBox();
}
//----------------------------------------------------------------------------------------------------------------------
// structure for Match score boxes
typedef struct
{

    int x;
    int y;
    int w;
    int h;
    char mat_text[Match_Text_r][Match_Text_c];
    char match_type_text[match_type_text_r][match_type_text_c];
    int team_1_run, team_2_run, team_1_wicket, team_2_wicket;
    int team_1_over, team_2_over;
    int ball;
    int array[10];
    int count = 0;
    int diff_wicket;
    int diff_run;
    int which_team;
    char mat_teams_bmp[mat_teams_bmp_r][mat_teams_bmp_c];
    char todays_match_text[today_mat_text_r][today_mat_text_c];
    char news_mat_bmp[news_mat_bmp_r][news_mat_bmp_c];
    int color;
} Match;

Match match_1, match_2, match_3, shadow_match_1, shadow_match_2, shadow_match_3, news, shadow_news, todays_matches, shadow_todays_matches, match_type_1, match_type_2, match_type_3, match_1_live, match_2_live, shadow_match_1_live, shadow_match_2_live;

// initialize Match boxes
void initMatchBoxes()
{
    // match_1 initialize
    match_1.x = matches.x;
    match_1.y = matches.y - 160;
    match_1.w = 310;
    match_1.h = 150;
    strcpy(match_1.mat_text[0], "11th Match,Group A,ICC Womens T20");
    match_1.team_1_run = 0;
    match_1.team_2_run = 160;
    match_1.team_1_wicket = 0;
    match_1.team_2_wicket = 10;
    match_1.team_1_over = 0;
    match_1.team_2_over = 16.2;
    strcpy(match_1.mat_text[3], "Match is running now");
    strcpy(match_1.mat_text[4], "");
    strcpy(match_1.mat_text[5], "");

    strcpy(match_1.mat_teams_bmp[0], "Assets//Australia.bmp");
    strcpy(match_1.mat_teams_bmp[1], "Assets//srilanka.bmp");

    shadow_match_1.x = match_1.x;
    shadow_match_1.y = match_1.y + match_1.h - 20;
    shadow_match_1.w = match_1.w;
    shadow_match_1.h = 20;

    match_type_1.x = match_1.x + match_1.w - 40;
    match_type_1.y = match_1.y + match_1.h - 40;
    match_type_1.w = 20;
    match_type_1.h = 20;
    strcpy(match_type_1.match_type_text[0], "TEST");

    // match_2 initialize
    match_2.x = match_1.x + match_1.w + 9;
    match_2.y = match_1.y;
    match_2.w = match_1.w;
    match_2.h = match_1.h;
    strcpy(match_2.mat_text[0], "1st test,England tour of Newzealand");
    match_2.team_1_run = 0;
    match_2.team_2_run = 170;
    match_2.team_1_wicket = 0;
    match_2.team_2_wicket = 7;
    match_2.team_1_over = 0;
    match_2.team_2_over = 20.0;
    strcpy(match_2.mat_text[3], "Match is running");
    strcpy(match_2.mat_text[4], "");
    strcpy(match_2.mat_text[5], "");

    strcpy(match_2.mat_teams_bmp[0], "Assets//england.bmp");
    strcpy(match_2.mat_teams_bmp[1], "Assets//new-zealand.bmp");

    shadow_match_2.x = match_2.x;
    shadow_match_2.y = match_2.y + match_2.h - 20;
    shadow_match_2.w = 310;
    shadow_match_2.h = 20;

    match_type_2.x = match_2.x + match_2.w - 40;
    match_type_2.y = match_2.y + match_2.h - 40;
    match_type_2.w = 20;
    match_type_2.h = 20;
    strcpy(match_type_2.match_type_text[0], "TEST");

    // use random time for wicket

    // match_3 initialize
    match_3.x = match_2.x + match_2.w + 9;
    match_3.y = match_1.y;
    match_3.w = 310;
    match_3.h = 150;
    strcpy(match_3.mat_text[0], "1st test,Afganistan tour of UAE");
    match_3.team_1_run = 0;
    match_3.team_2_run = 143;
    match_3.team_1_wicket = 0;
    match_3.team_2_wicket = 10;
    match_3.team_1_over = 0;
    match_3.team_2_over = 17.5;
    strcpy(match_3.mat_text[3], "Match is running");
    strcpy(match_3.mat_text[4], "");
    strcpy(match_3.mat_text[5], "");
    strcpy(match_3.mat_teams_bmp[0], "Assets//UAE.bmp");
    strcpy(match_3.mat_teams_bmp[1], "Assets//Afganistan.bmp");

    shadow_match_3.x = match_3.x;
    shadow_match_3.y = match_3.y + match_3.h - 20;
    shadow_match_3.w = 310;
    shadow_match_3.h = 20;

    match_type_3.x = match_3.x + match_3.w - 40;
    match_type_3.y = match_3.y + match_3.h - 40;
    match_type_3.w = 20;
    match_type_3.h = 20;
    strcpy(match_type_3.match_type_text[0], "ODI");

    // for todays matches section
    todays_matches.x = 50;
    todays_matches.y = 30;
    todays_matches.w = 290;
    todays_matches.h = 300;
    strcpy(todays_matches.todays_match_text[0], "TODAYS MATCHES");
    strcpy(todays_matches.todays_match_text[1], ">> England tour of New-zealand");
    strcpy(todays_matches.todays_match_text[2], ">> Afganistan tour of UAE");
    strcpy(todays_matches.todays_match_text[3], ">> SLW vs AUSW");
    strcpy(todays_matches.todays_match_text[4], ">> Bangladesh tour of Zimbabwe");

    shadow_todays_matches.x = 50;
    shadow_todays_matches.y = 310;
    shadow_todays_matches.w = 290;
    shadow_todays_matches.h = 20;

    // for news section
    news.x = 350;
    news.y = 30;
    news.w = 650;
    news.h = 300;
    strcpy(news.news_mat_bmp[0], "NEWS");
    strcpy(news.news_mat_bmp[1], "Assets//news2.bmp");
    strcpy(news.news_mat_bmp[2], "Assets//news6.bmp");

    shadow_news.x = 350;
    shadow_news.y = 310;
    shadow_news.w = 650;
    shadow_news.h = 20;
}

// void updateLiveMatch(Match box,Match box_live)
// {
//     printf("live match is updating \n");
//     if (box.team_1_run <= box.team_2_run)
//     {
//         box.team_1_run += rand() % 7;
//         box.ball++;
//         if (box.ball == 6)
//         {
//             box.ball = 0;
//             box.team_1_over++;
//         }
//     }

//     else
//     {

//         strcpy(box.mat_text[3], "Australia won by 10 wickets");
//     }
//     printf("match_1 team run  is     %d \n",box.team_1_run);
//     box_live.team_1_run = box.team_1_run;
//     box_live.team_1_over = box.team_1_over;
//     box_live.ball = box.ball;
// }

void updateMatchStatus()
{
    // updateLiveMatch(match_1,match_1_live);
    if (match_1.team_1_wicket < 10)
    {

        if (match_1.team_1_run <= match_1.team_2_run)
        {
            match_1.team_1_run += rand() % 7;
            match_1.ball++;
            if (match_1.ball == 6)
            {
                match_1.ball = 0;
                match_1.team_1_over++;
            }
        }
    }

    else
    {
        match_1.diff_run = match_1.team_2_run - match_1.team_1_run;
        strcpy(match_1.mat_text[3], "Srilanka won by");
        char match_diff_run[20];
        sprintf(match_diff_run, "%d", match_1.diff_run);
        strcpy(match_1.mat_text[4], match_diff_run);
        strcpy(match_1.mat_text[5], "run");
    }

    if (match_2.team_1_wicket < 10)
    {

        if (match_2.team_1_run <= match_2.team_2_run)
        {
            match_2.team_1_run += rand() % 7;
            match_2.ball++;

            if (match_2.ball == 6)
            {
                match_2.ball = 0;
                match_2.team_1_over++;
            }
        }
    }
    else
    {
        match_2.diff_run = match_2.team_2_run - match_2.team_1_run;
        strcpy(match_2.mat_text[3], "Australia won by");
        char match_diff_run[20];
        sprintf(match_diff_run, "%d", match_2.diff_run);
        strcpy(match_2.mat_text[4], match_diff_run);
        strcpy(match_2.mat_text[5], "run");
        // strcpy(match_2.mat_text[3], "England won by 8 wickets");
    }
    if (match_3.team_1_wicket < 10)
    {
        if (match_3.team_1_run < match_3.team_2_run)
        {
            match_3.team_1_run += rand() % 7;
            match_3.ball++;
            if (match_3.ball == 6)
            {
                match_3.ball = 0;
                match_3.team_1_over++;
            }
        }
    }
    else
    {
        match_3.diff_run = match_3.team_2_run - match_3.team_1_run;
        strcpy(match_3.mat_text[3], "Afghanistan won by");
        char match_diff_run[20];
        sprintf(match_diff_run, "%d", match_3.diff_run);
        strcpy(match_3.mat_text[4], match_diff_run);
        strcpy(match_3.mat_text[5], "run");
        // strcpy(match_3.mat_text[3], "Afganistan won by 5 runs");
    }
    match_1_live.team_1_run = match_1.team_1_run;
    match_1_live.team_1_over = match_1.team_1_over;
    match_1_live.ball = match_1.ball;
    match_2_live.team_1_run = match_2.team_1_run;
    match_2_live.team_1_over = match_2.team_1_over;
    match_2_live.ball = match_2.ball;
}
// void swap(int *xp, int *yp)
// {
//     int temp = *xp;
//     *xp = *yp;
//     *yp = temp;
// }
// void bubbleSort(int arr[], int n)
// {
//     int i, j;
//     for (i = 0; i < n - 1; i++)

//         // Last i elements are already in place
//         for (j = 0; j < n - i - 1; j++)
//             if (arr[j] > arr[j + 1])
//                 swap(&arr[j], &arr[j + 1]);
// }
void wicketfall()
{

    // printf("hi\n");
    for (int i = 0; i < 10; i++)
    {
        match_1.array[i] = rand() % 200;
        // printf("array %d", array[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        match_2.array[i] = rand() % 60;
        // printf("array %d", array[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        match_3.array[i] = rand() % 200;
        // printf("array %d", array[i]);
    }
}

// int count = 0;
void updateWicket()
{
    match_1.count++;
    if (match_1.team_1_run <= match_1.team_2_run)
    {
        for (int i = 0; i < 10; i++)
        {
            if (match_1.count == match_1.array[i])
            {
                if (match_1.team_1_wicket != 10)
                {
                    match_1.team_1_wicket++;
                }
                printf("wicket falls on %d seconds\n", match_1.count);
            }
        }
    }
    else
    {
        // strcpy(match_1.mat_text[3], "Australia won the match");
        match_1.diff_wicket = match_1.team_2_wicket - match_1.team_1_wicket;
        // match_1.diff_run = match_1.team_2_run - match_1.team_1_run;
        strcpy(match_1.mat_text[3], "Newzealand won by");
        char match_diff_wicket[20];
        sprintf(match_diff_wicket, "%d", match_1.diff_wicket);
        strcpy(match_1.mat_text[4], match_diff_wicket);
        strcpy(match_1.mat_text[5], "wicket");
    }
    match_2.count++;
    if (match_2.team_1_run <= match_2.team_2_run)
    {
        for (int i = 0; i < 10; i++)
        {
            if (match_2.count == match_2.array[i])
            {
                if (match_2.team_1_wicket != 10)
                {
                    match_2.team_1_wicket++;
                }
                // printf("wicket falls on %d seconds\n", match_2.count);
            }
        }
    }
    else
    {
        match_2.diff_wicket = match_2.team_2_wicket - match_2.team_1_wicket;
        // match_2.diff_run = match_2.team_2_run - match_2.team_1_run;
        strcpy(match_2.mat_text[3], "England won by");
        char match_diff_wicket[20];
        sprintf(match_diff_wicket, "%d", match_2.diff_wicket);
        strcpy(match_2.mat_text[4], match_diff_wicket);
        strcpy(match_2.mat_text[5], "wicket");
    }
    match_3.count++;
    if (match_3.team_1_run <= match_3.team_2_run)
    {
        for (int i = 0; i < 10; i++)
        {
            if (match_3.count == match_3.array[i])
            {
                if (match_3.team_1_wicket != 10)
                {
                    match_3.team_1_wicket++;
                }
                // printf("wicket falls on %d seconds\n", match_3.count);
            }
        }
    }
    else
    {
        match_3.diff_wicket = match_3.team_2_wicket - match_3.team_1_wicket;
        // match_3.diff_run = match_3.team_2_run - match_3.team_1_run;
        strcpy(match_3.mat_text[3], "U.A.E   won  by");
        char match_diff_wicket[20];
        sprintf(match_diff_wicket, "%d", match_3.diff_wicket);
        strcpy(match_3.mat_text[4], match_diff_wicket);
        strcpy(match_3.mat_text[5], "wicket");
    }
}

// void update_wicket(){
//     match_1.team_1_wicket++;
//     time_interval=rand()%20000;
//     printf("Time is generating randomly ==%d and also wicket==%d\n",time_interval,match_1.team_1_wicket);
// }
// draw match box;
void drawMatchBox(Match box)
{

    // for box and headline
    iSetColor(0, 0, 0);
    iRectangle(box.x, box.y, box.w, box.h);
    iSetColor(0, 146, 112);
    iText(box.x + 10, box.y + box.h - 15, box.mat_text[0]);
    iSetColor(0, 0, 0);
    // updating score for team _1
    //  for update run score
    char match_run_1[10];
    sprintf(match_run_1, "%d", box.team_1_run);
    iText(box.x + 120, box.y + box.h - 55, match_run_1);
    iText(box.x + 140, box.y + box.h - 55, " - ");
    // for wicket
    char match_wicket_1[10];
    sprintf(match_wicket_1, "%d", box.team_1_wicket);
    iText(box.x + 165, box.y + box.h - 55, match_wicket_1);
    // // for over update
    // int last_digit;
    // last_digit = ((int)((box.team_1_over) * 10)) % 10;
    // printf(" over :%.1f \n",box.team_1_over);
    // if (box.ball == 6)
    // {
    //     box.ball = 0;
    //     box.team_1_over++;
    // }
    // printf(" over :%.1f \n",last_digit);
    iText(box.x + 183, box.y + box.h - 55, "(");
    char match_over_1[10];
    sprintf(match_over_1, "%d", box.team_1_over);
    iText(box.x + 193, box.y + box.h - 55, match_over_1);
    iText(box.x + 210, box.y + box.h - 55, ".");
    char mat_ball[10];
    sprintf(mat_ball, "%d", box.ball);
    iText(box.x + 220, box.y + box.h - 55, mat_ball);
    iText(box.x + 240, box.y + box.h - 55, ")");
    // for team_2 score

    char match_run_2[10];
    sprintf(match_run_2, "%d", box.team_2_run);
    iText(box.x + 120, box.y + box.h - 95, match_run_2);
    iText(box.x + 140, box.y + box.h - 95, " - ");
    // for wicket
    char match_wicket_2[10];
    sprintf(match_wicket_2, "%d", box.team_2_wicket);
    iText(box.x + 165, box.y + box.h - 95, match_wicket_2);

    iText(box.x + 183, box.y + box.h - 95, "(");
    char match_over_2[10];
    sprintf(match_over_2, "%d", box.team_2_over);
    iText(box.x + 200, box.y + box.h - 95, match_over_2);
    iText(box.x + 230, box.y + box.h - 95, ")");

    // for match status
    iSetColor(255, 0, 0);
    iText(box.x + 5, box.y + 5, box.mat_text[3]);
    iText(box.x + 155, box.y + 5, box.mat_text[4]);
    iText(box.x + 200, box.y + 5, box.mat_text[5]);

    // for result announcement
    iShowBMP(box.x + 25, box.y + box.h - 60, box.mat_teams_bmp[0]);
    iShowBMP(box.x + 25, box.y + box.h - 100, box.mat_teams_bmp[1]);
}
void matchType(Match box)
{
    iSetColor(255, 0, 0);
    iFilledRectangle(box.x, box.y, box.w, box.h);
    iSetColor(255, 255, 255);
    iText(box.x, box.y, box.match_type_text[0]);
}
// draw Todays Match box
void TodaysMatchBox(Match box)
{
    iSetColor(0, 0, 0);
    iRectangle(box.x, box.y, box.w, box.h);
    iSetColor(0, 146, 112);
    iText(box.x + 10, box.y + box.h - 15, box.todays_match_text[0]);
    iSetColor(0, 0, 0);
    iText(box.x + 10, box.y + box.h - 40, box.todays_match_text[1]);
    iText(box.x + 10, box.y + box.h - 65, box.todays_match_text[2]);
    iText(box.x + 10, box.y + box.h - 90, box.todays_match_text[3]);
    iText(box.x + 10, box.y + box.h - 115, box.todays_match_text[4]);
}

// for news
void drawNews(Match box)
{
    iSetColor(0, 0, 0);
    iRectangle(box.x, box.y, box.w, box.h);
    iSetColor(0, 146, 112);

    iText(box.x + 10, box.y + box.h - 15, box.news_mat_bmp[0]);
    iShowBMP(box.x + 10, box.y + 15, box.news_mat_bmp[1]);
    iShowBMP(box.x + 343, box.y + 10, box.news_mat_bmp[2]);
    //  iShowBMP(box.x+10,box.y+10,box.news_mat_bmp[3]);
    //  iShowBMP(box.x+10,box.y+10,box.news_mat_bmp[0]);
}

// draw shadow on match box
void shadowBox(Match box)
{
    iSetColor(227, 230, 227);
    iFilledRectangle(box.x, box.y, box.w, box.h);
}
// draw All boxes for 1st page
void drawHomePage()
{
    // matchType(match_type_1);
    // matchType(match_type_2);
    // matchType(match_type_3);

    shadowBox(shadow_news);
    shadowBox(shadow_todays_matches);
    shadowBox(shadow_match_1);
    shadowBox(shadow_match_2);
    shadowBox(shadow_match_3);
    drawMatchBox(match_1);
    drawMatchBox(match_2);
    drawMatchBox(match_3);
    TodaysMatchBox(todays_matches);
    drawNews(news);
}

//--------------------------------------------------------------------------------------------------------------------------
// for teams page

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    char teams_bar_text[teams_text_r][teams_text_c];
    char teams_name_text[teams_name_text_r][teams_name_text_c];
    char teams_type_text[teams_type_text_r][teams_type_text_c];
    // char filename[100];
} Teams;

Teams teams_bar, teams_type_1, teams_type_2, All_Teams;

void initTeams()
{
    teams_bar.x = 50;
    teams_bar.y = 420;
    teams_bar.w = 950;
    teams_bar.h = 80;

    teams_type_1.x = teams_bar.x + 30;
    teams_type_1.y = teams_bar.y + 10;
    teams_type_1.w = 120;
    teams_type_1.h = 18;

    teams_type_2.x = teams_type_1.x + teams_type_1.w + 45;
    teams_type_2.y = teams_type_1.y;
    teams_type_2.w = teams_type_1.w;
    teams_type_2.h = teams_type_1.h;
}

void drawTeamsBar(Teams box)
{
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 30, box.y + box.h - 28, box.teams_bar_text[0], GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawTeamsType(Teams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iText(box.x + 5, box.y + box.h - 13, box.teams_type_text[0], GLUT_BITMAP_8_BY_13);
}

// Teams
typedef struct
{
    int x;
    int y;
    int w;
    int h;
    char InTeams_bmp[5][60];

} InTeams;

InTeams Bangladesh, India, Pakistan, Australia, New_zealand, England, Srilanka, Afghanistan, Wes_indies;

void initInTeams()
{
    Bangladesh.x = teams_bar.x;
    Bangladesh.y = teams_bar.y - 120;
    Bangladesh.w = (teams_bar.w / 3);
    Bangladesh.h = 85;
    strcpy(Bangladesh.InTeams_bmp[0], "Assets//Teams//bangladesh.bmp");
    strcpy(Bangladesh.InTeams_bmp[1], "BANGLADESH");
    strcpy(Bangladesh.InTeams_bmp[2], "Assets//league//barisal-bulls.bmp");
    strcpy(Bangladesh.InTeams_bmp[3], "BARISAL BULLS");

    India.x = teams_bar.x;
    India.y = Bangladesh.y - 110;
    India.w = (teams_bar.w / 3);
    India.h = 85;
    strcpy(India.InTeams_bmp[0], "Assets//Teams//india.bmp");
    strcpy(India.InTeams_bmp[1], "INDIA");
    strcpy(India.InTeams_bmp[2], "Assets//league//chennai-super-kings.bmp");
    strcpy(India.InTeams_bmp[3], "CHENNAI SUPER KINGS");

    Pakistan.x = teams_bar.x;
    Pakistan.y = India.y - 110;
    Pakistan.w = (teams_bar.w / 3);
    Pakistan.h = 85;
    strcpy(Pakistan.InTeams_bmp[0], "Assets//Teams//pakistan.bmp");
    strcpy(Pakistan.InTeams_bmp[1], "PAKISTAN");
    strcpy(Pakistan.InTeams_bmp[2], "Assets//league//delhi-capitals.bmp");
    strcpy(Pakistan.InTeams_bmp[3], "DELHI CAPITALS");

    // for second column
    Australia.x = Bangladesh.x + Bangladesh.w + 5;
    Australia.y = teams_bar.y - 120;
    Australia.w = (teams_bar.w / 3);
    Australia.h = 85;
    strcpy(Australia.InTeams_bmp[0], "Assets//Teams//australia.bmp");
    strcpy(Australia.InTeams_bmp[1], "AUSTRALIA");
    strcpy(Australia.InTeams_bmp[2], "Assets//league//dhaka-dynamites.bmp");
    strcpy(Australia.InTeams_bmp[3], "DHAKA DYNAMITES");

    New_zealand.x = Bangladesh.x + Bangladesh.w + 5;
    New_zealand.y = India.y;
    New_zealand.w = (teams_bar.w / 3);
    New_zealand.h = 85;
    strcpy(New_zealand.InTeams_bmp[0], "Assets//Teams//new-zealand.bmp");
    strcpy(New_zealand.InTeams_bmp[1], "NEWZEALAND");
    strcpy(New_zealand.InTeams_bmp[2], "Assets//league//kolkata-knight-riders.bmp");
    strcpy(New_zealand.InTeams_bmp[3], "KOLKATA KNIGHT RIDERS");

    England.x = Bangladesh.x + Bangladesh.w + 5;
    England.y = Pakistan.y;
    England.w = (teams_bar.w / 3);
    England.h = 85;
    strcpy(England.InTeams_bmp[0], "Assets//Teams//england.bmp");
    strcpy(England.InTeams_bmp[1], "ENGLAND");
    strcpy(England.InTeams_bmp[2], "Assets//league//rangpur-riders.bmp");
    strcpy(England.InTeams_bmp[3], "RANGPUR RIDERS");

    Srilanka.x = Bangladesh.x + Bangladesh.w + Australia.w + 10;
    Srilanka.y = teams_bar.y - 120;
    Srilanka.w = (teams_bar.w / 3);
    Srilanka.h = 85;
    strcpy(Srilanka.InTeams_bmp[0], "Assets//Teams//sri-lanka.bmp");
    strcpy(Srilanka.InTeams_bmp[1], "SRI-LANKA");
    strcpy(Srilanka.InTeams_bmp[2], "Assets//league//royal-challengers-bangalore.bmp");
    strcpy(Srilanka.InTeams_bmp[3], "ROYAL CHALLENGERS");

    Afghanistan.x = Bangladesh.x + Bangladesh.w + Australia.w + 10;
    Afghanistan.y = India.y;
    Afghanistan.w = (teams_bar.w / 3);
    Afghanistan.h = 85;
    strcpy(Afghanistan.InTeams_bmp[0], "Assets//Teams//afghanistan.bmp");
    strcpy(Afghanistan.InTeams_bmp[1], "AFGHANISTAN");
    strcpy(Afghanistan.InTeams_bmp[2], "Assets//league//sunrisers-hyderabad.bmp");
    strcpy(Afghanistan.InTeams_bmp[3], "SUNRISERS HYDERABAD");

    Wes_indies.x = Bangladesh.x + Bangladesh.w + Australia.w + 10;
    Wes_indies.y = England.y;
    Wes_indies.w = (teams_bar.w / 3);
    Wes_indies.h = 85;
    strcpy(Wes_indies.InTeams_bmp[0], "Assets//Teams//west-indies.bmp");
    strcpy(Wes_indies.InTeams_bmp[1], "WEST-INDIES");
    strcpy(Wes_indies.InTeams_bmp[2], "Assets//league//sylhet-thunder.bmp");
    strcpy(Wes_indies.InTeams_bmp[3], "SYLHET THUNDER");
}

//============================================for each team=================
Teams BD_bar, player, stats;

void initBangladesh()
{
    BD_bar.x = 50;
    BD_bar.y = 435;
    BD_bar.w = 950;
    BD_bar.h = 80;

    player.x = BD_bar.x + 30;
    player.y = BD_bar.y + 10;
    player.w = 120;
    player.h = 18;

    stats.x = player.x + player.w + 45;
    stats.y = player.y;
    stats.w = player.w;
    stats.h = player.h;
}

Teams batsman_box, bowler_box, allrounder_box, wicket_keeper;
InTeams tamim, liton, shanto, sabbir, mushfiq, mithun, mahmudullah, sakib, miraz, mustafiz, mash, rubel, jayed;

void drawPlayers(InTeams box)
{
    iSetColor(BLACK);
    // iRectangle(box.x, box.y, box.w, box.h);
    iShowBMP(box.x, box.y, box.InTeams_bmp[0]);
    iText(box.x + 95, box.y + 40, box.InTeams_bmp[1], GLUT_BITMAP_9_BY_15);
}

Match shadow_batsman, shadow_bowler, shadow_allrounder_box, shadow_wicket_keeper;

void initplayer()
{
    // batsman
    batsman_box.x = BD_bar.x;
    batsman_box.y = BD_bar.y - 105;
    batsman_box.w = BD_bar.w;
    batsman_box.h = 95;
    strcpy(batsman_box.teams_type_text[0], "BATSMAN");
    shadow_batsman.x = batsman_box.x;
    shadow_batsman.y = batsman_box.y + batsman_box.h - 15;
    shadow_batsman.w = batsman_box.w;
    shadow_batsman.h = 15;

    tamim.x = batsman_box.x;
    tamim.y = batsman_box.y;
    tamim.w = 230;
    tamim.h = 40;
    strcpy(tamim.InTeams_bmp[0], "Assets//player//tamim.bmp");
    strcpy(tamim.InTeams_bmp[1], "Tamim Iqbal");

    shanto.x = tamim.x + tamim.w + 10;
    shanto.y = batsman_box.y;
    shanto.w = 230;
    shanto.h = 40;
    strcpy(shanto.InTeams_bmp[0], "Assets//player//shanto.bmp");
    strcpy(shanto.InTeams_bmp[1], "LORD SHANTO");

    liton.x = shanto.x + shanto.w + 10;
    liton.y = batsman_box.y;
    liton.w = 230;
    liton.h = 40;
    strcpy(liton.InTeams_bmp[0], "Assets//player//liton.bmp");
    strcpy(liton.InTeams_bmp[1], "LITON DAS");

    sabbir.x = liton.x + liton.w + 10;
    sabbir.y = batsman_box.y;
    sabbir.w = 230;
    sabbir.h = 40;
    strcpy(sabbir.InTeams_bmp[0], "Assets//player//sabbir.bmp");
    strcpy(sabbir.InTeams_bmp[1], "SABBIR HOSSAIN");

    bowler_box.x = batsman_box.x;
    bowler_box.y = batsman_box.y - 105;
    bowler_box.w = batsman_box.w;
    bowler_box.h = batsman_box.h;
    strcpy(bowler_box.teams_type_text[0], "BOWLER");
    shadow_bowler.x = bowler_box.x;
    shadow_bowler.y = bowler_box.y + bowler_box.h - 15;
    shadow_bowler.w = bowler_box.w;
    shadow_bowler.h = 15;
    mash.x = tamim.x;
    mash.y = bowler_box.y;
    mash.w = 230;
    mash.h = 40;
    strcpy(mash.InTeams_bmp[0], "Assets//player//mash.bmp");
    strcpy(mash.InTeams_bmp[1], "MASHRAFEE MORATAZA");
    mustafiz.x = mash.x + mash.w + 10;
    mustafiz.y = bowler_box.y;
    mustafiz.w = 230;
    mustafiz.h = 40;
    strcpy(mustafiz.InTeams_bmp[0], "Assets//player//mustafiz.bmp");
    strcpy(mustafiz.InTeams_bmp[1], "MUSTAFIZUR RAHMAN");
    rubel.x = mustafiz.x + mustafiz.w + 10;
    rubel.y = bowler_box.y;
    rubel.w = 230;
    rubel.h = 40;
    strcpy(rubel.InTeams_bmp[0], "Assets//player//rubel.bmp");
    strcpy(rubel.InTeams_bmp[1], "RUBEL HOSSAIN");
    jayed.x = rubel.x + rubel.w + 10;
    jayed.y = bowler_box.y;
    jayed.w = 230;
    jayed.h = 40;
    strcpy(jayed.InTeams_bmp[0], "Assets//player//jayed.bmp");
    strcpy(jayed.InTeams_bmp[1], "ABU JAYED");

    allrounder_box.x = bowler_box.x;
    allrounder_box.y = bowler_box.y - 105;
    allrounder_box.w = bowler_box.w;
    allrounder_box.h = bowler_box.h;
    strcpy(allrounder_box.teams_type_text[0], "ALL-ROUNDER");
    shadow_allrounder_box.x = allrounder_box.x;
    shadow_allrounder_box.y = allrounder_box.y + allrounder_box.h - 15;
    shadow_allrounder_box.w = allrounder_box.w;
    shadow_allrounder_box.h = 15;
    mahmudullah.x = tamim.x;
    mahmudullah.y = allrounder_box.y;
    mahmudullah.w = 230;
    mahmudullah.h = 40;
    strcpy(mahmudullah.InTeams_bmp[0], "Assets//player//mahmudullah.bmp");
    strcpy(mahmudullah.InTeams_bmp[1], "MAHMUDULLAH RYADH");
    sakib.x = mahmudullah.x + mahmudullah.w + 10;
    sakib.y = allrounder_box.y;
    sakib.w = 230;
    sakib.h = 40;
    strcpy(sakib.InTeams_bmp[0], "Assets//player//sakib.bmp");
    strcpy(sakib.InTeams_bmp[1], "SAKIB AL HASAN");
    miraz.x = sakib.x + sakib.w + 10;
    miraz.y = allrounder_box.y;
    miraz.w = 230;
    miraz.h = 40;
    strcpy(miraz.InTeams_bmp[0], "Assets//player//miraz.bmp");
    strcpy(miraz.InTeams_bmp[1], "MEHEDY HASAN");

    wicket_keeper.x = allrounder_box.x;
    wicket_keeper.y = allrounder_box.y - 105;
    wicket_keeper.w = allrounder_box.w;
    wicket_keeper.h = allrounder_box.h;
    strcpy(wicket_keeper.teams_type_text[0], "WICKET-KEEPER");
    shadow_wicket_keeper.x = wicket_keeper.x;
    shadow_wicket_keeper.y = wicket_keeper.y + wicket_keeper.h - 15;
    shadow_wicket_keeper.w = wicket_keeper.w;
    shadow_wicket_keeper.h = 15;
    mushfiq.x = tamim.x;
    mushfiq.y = wicket_keeper.y;
    mushfiq.w = 230;
    mushfiq.h = 40;
    strcpy(mushfiq.InTeams_bmp[0], "Assets//player//mushfiq.bmp");
    strcpy(mushfiq.InTeams_bmp[1], "MUSHFIQUR RAHIM");
    mithun.x = mushfiq.x + mushfiq.w + 10;
    mithun.y = wicket_keeper.y;
    mithun.w = 230;
    mithun.h = 40;
    strcpy(mithun.InTeams_bmp[0], "Assets//player//mithun.bmp");
    strcpy(mithun.InTeams_bmp[1], "MOHAMMAD MITHUN");
}

// typedef struct {
//     char born[20];
//     char birth_place[20];
//     char height[10];
//     char role[20];
//     char batting[20];
//     char test_mat[10];
//     char odi_mat[10];
//     char t20_mat[10];
// } PlayerInfo;

// void PlayerProfileBox(char filename[])
// {

//     PlayerProIN.x = TamimProfile.x;
//     PlayerProIN.y = TamimProfile.y - 380;
//     PlayerProIN.w = 330;
//     PlayerProIN.h = 370;

//     iSetColor(Halka_chai);
//     iFilledRectangle(PlayerProIN.x, PlayerProIN.y, PlayerProIN.w, PlayerProIN.h);
//     iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 20, "PERSONAL INFORMATION", GLUT_BITMAP_9_BY_15);
//     iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 50, "Born", GLUT_BITMAP_9_BY_15);

//     FILE *fptr = fopen(filename, "r");
//     if (fptr == NULL)
//     {
//         printf("Error opening file!");
//         return;
//     }

//     PlayerInfo player;
//     char line[100];
//     if (fgets(line, sizeof(line), fptr) != NULL)
//     {
//         char *field = strtok(line, "|");
//         strcpy(player.born, field);
//         field = strtok(NULL, "|");
//         strcpy(player.birth_place, field);
//         field = strtok(NULL, "|");
//         strcpy(player.height, field);
//         field = strtok(NULL, "|");
//         strcpy(player.role, field);
//         field = strtok(NULL, "|");
//         strcpy(player.batting, field);
//         field = strtok(NULL, "|");
//         strcpy(player.test_mat, field);
//         field = strtok(NULL, "|");
//         strcpy(player.odi_mat, field);
//         field = strtok(NULL, "|");
//         strcpy(player.t20_mat, field);
//         iText(PlayerProIN.x + 100, PlayerProIN.y + PlayerProIN.h - 50, player.born);
//         iSetColor(BLACK);
//         iRectangle(PlayerProIN.x, PlayerProIN.y, PlayerProIN.w, PlayerProIN.h);
//     }
//     fclose(fptr);
// }

InTeams TamimProfile, shantoProfile;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    char profile_information[10][100];

} playerProfile;

playerProfile PlayerProIN, batting_career;

void PlayerProfileBox(char filename[])
{

    PlayerProIN.x = TamimProfile.x;
    PlayerProIN.y = TamimProfile.y - 360;
    PlayerProIN.w = 330;
    PlayerProIN.h = 350;

    batting_career.x = PlayerProIN.x + PlayerProIN.w + 10;
    batting_career.y = PlayerProIN.y;
    batting_career.w = 610;
    batting_career.h = 350;
    iSetColor(Halka_chai);
    iFilledRectangle(PlayerProIN.x, PlayerProIN.y, PlayerProIN.w, PlayerProIN.h);
    iFilledRectangle(batting_career.x, batting_career.y, batting_career.w, batting_career.h);
    iSetColor(BLACK);
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 20, "PERSONAL INFORMATION", GLUT_BITMAP_9_BY_15);
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 50, "Born       :MARCH 20,1989(33 YEARS)", GLUT_BITMAP_9_BY_15);
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 80, "Birth place :CHITTAGONG");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 110, "Height     :CHITTAGONG");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 140, "Role       :Batsman");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 170, "Batting style  :Left handed bat");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 200, "ICC Rankings  ");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 230, "           Test  ODI  t20  ");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 260, "Batting    40    15    22");
    iText(PlayerProIN.x + 10, PlayerProIN.y + PlayerProIN.h - 290, "Bowling    --    --    --");

    iText(batting_career.x + 10, batting_career.y + batting_career.h - 20, "BATTING CAREER SUMMARY", GLUT_BITMAP_9_BY_15);
    iText(batting_career.x + 10, batting_career.y + batting_career.h - 60, "        M    Inn   NO   Runs   HS   avg    SR     100   200", GLUT_BITMAP_9_BY_15);
    iText(batting_career.x + 10, batting_career.y + batting_career.h - 100, "Test:   69   132    2   5082   206  39.09  58.07  10    1", GLUT_BITMAP_9_BY_15);
    iText(batting_career.x + 10, batting_career.y + batting_career.h - 140, "ODI:    231  229   11   8074   158  37.04  78.66  14    0", GLUT_BITMAP_9_BY_15);
    iText(batting_career.x + 10, batting_career.y + batting_career.h - 180, "T20I:   78   78    5    1758   103  24.08  117.2  1     0", GLUT_BITMAP_9_BY_15);

    // FILE *fptr = fopen("filename.txt", "r");
    // if (fptr == NULL)
    // {
    //     printf("Error opening file!");
    //     return;
    // }
    // char *born;
    // char *birth_place;
    // char *height;
    // char *role;
    // char *batting;
    // char *test_mat;
    // char *odi_mat;
    // char *t20_mat;
    // char line[100];
    // int i = 0;
    // while (fgets(line, sizeof(line), fptr))
    // {
    //     born = strtok(line, ",");
    //     birth_place = strtok(NULL, ",");
    //     height = strtok(NULL," ,");
    //     role = strtok(NULL, ",");
    //     batting = strtok(NULL," ,");
    //     test_mat = strtok(NULL, ",");
    //     odi_mat = strtok(NULL," ,");
    //     t20_mat = strtok(NULL, ",");
    // }

    // iText(PlayerProIN.x + 100, PlayerProIN.y + PlayerProIN.h - 50,"");
    iSetColor(BLACK);
    iRectangle(batting_career.x, batting_career.y, batting_career.w, batting_career.h);
    iRectangle(PlayerProIN.x, PlayerProIN.y, PlayerProIN.w, PlayerProIN.h);
    // fclose(fptr);
}

void drawPlayerBar(InTeams box)
{

    iSetColor(BLACK);
    iShowBMP(box.x, box.y, box.InTeams_bmp[0]);
    iText(box.x + 160, box.y + (box.h / 2), box.InTeams_bmp[1], GLUT_BITMAP_TIMES_ROMAN_24);
    iText(box.x + 160, box.y + (box.h / 2) - 40, box.InTeams_bmp[2], GLUT_BITMAP_9_BY_15);
    iRectangle(box.x, box.y, box.w, box.h);
}

void initIndividualPlayer()
{

    TamimProfile.x = matches.x;
    TamimProfile.y = matches.y - 155;
    TamimProfile.w = matches.w;
    TamimProfile.h = 140;
    strcpy(TamimProfile.InTeams_bmp[0], "Assets//player//tamimBIG.bmp");
    strcpy(TamimProfile.InTeams_bmp[1], "TAMIM IQBAL");
    strcpy(TamimProfile.InTeams_bmp[2], "Bangladesh");
}

void drawInTeams(InTeams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iShowBMP(box.x + 15, box.y + 20, box.InTeams_bmp[0]);
    iText(box.x + 95, box.y + 40, box.InTeams_bmp[1], GLUT_BITMAP_9_BY_15);
}

void drawDomTeams(InTeams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iShowBMP(box.x + 15, box.y + 20, box.InTeams_bmp[2]);
    iText(box.x + 95, box.y + 40, box.InTeams_bmp[3], GLUT_BITMAP_9_BY_15);
}

//============================================Ranking=========================================================================

Teams ranking_men, batting, bowling, all_rounder, test, odi, t_20, table_teams_rank, teams_rank;

void initTeamsRank()
{

    ranking_men.x = matches.x;
    ranking_men.y = matches.y - 120;
    ranking_men.w = matches.w;
    ranking_men.h = 110;
    strcpy(ranking_men.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S TEAMS");

    batting.x = ranking_men.x + 10;
    batting.y = ranking_men.y + 30;
    batting.w = 150;
    batting.h = 20;
    strcpy(batting.teams_name_text[0], "Batting");

    bowling.x = batting.x + batting.w + 20;
    bowling.y = batting.y;
    bowling.w = 150;
    bowling.h = 20;
    strcpy(bowling.teams_name_text[0], "Bowling");

    all_rounder.x = bowling.x + bowling.w + 20;
    all_rounder.y = bowling.y;
    all_rounder.w = 150;
    all_rounder.h = 20;
    strcpy(all_rounder.teams_name_text[0], "All-rounder");

    teams_rank.x = all_rounder.x + all_rounder.w + 20;
    teams_rank.y = all_rounder.y;
    teams_rank.w = 150;
    teams_rank.h = 20;
    strcpy(teams_rank.teams_name_text[0], "Teams");

    test.x = batting.x;
    test.y = batting.y - 25;
    test.w = 150;
    test.h = 20;
    strcpy(test.teams_name_text[0], "Test");

    odi.x = bowling.x;
    odi.y = bowling.y - 25;
    odi.w = 150;
    odi.h = 20;
    strcpy(odi.teams_name_text[0], "ODI");

    t_20.x = all_rounder.x;
    t_20.y = all_rounder.y - 25;
    t_20.w = 150;
    t_20.h = 20;
    strcpy(t_20.teams_name_text[0], "T20");

    table_teams_rank.x = ranking_men.x;
    table_teams_rank.y = ranking_men.y - 60;
    table_teams_rank.w = ranking_men.w;
    table_teams_rank.h = 40;
    strcpy(table_teams_rank.teams_type_text[0], "Position");
    strcpy(table_teams_rank.teams_type_text[1], "Team");
    strcpy(table_teams_rank.teams_type_text[2], "Points");
}

// void initRankBoxes()
// {

//     if (currentPage == RankingPage)
//     {
//         if (currentPage == TeamsTestPage)
//             strcpy(ranking_men.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S TEAMS");
//         if (currentPage == TeamsODIPage)
//             strcpy(ranking_men.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S TEAMS");
//     }
//     if (currentPage == BattingTestPage)
//     {
//     }
//     strcpy(batting.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S BATTING");
//     strcpy(bowling.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S BOWLING");
//     strcpy(all_rounder.teams_bar_text[0], "ICC CRICKET RANKING-MEN'S ALL-ROUNDER");
// }

void drawRankBoxes(Teams box)
{
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 10, box.y + box.h - 25, box.teams_bar_text[0], GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawRankType(Teams box)
{
    iSetColor(CHAI);
    iFilledRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 5, box.y + box.h - 15, box.teams_name_text[0]);
}

void drawTableBoxes(Teams box)
{
    iSetColor(CHAI);
    iFilledRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    for (int i = 0; i < teams_type_text_r; i++)
    {
        iText(box.x + i * 310 + 5, box.y + 10, box.teams_type_text[i], GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void InputFileRead(char filename[])
{

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!");
        return;
    }
    char *position;
    char *team_name;
    char *points;
    char line[100];
    // char points_s[50];
    // char position_s[50];

    // for (int i = 0; fscanf(fp, "%d %s %d", &position, team_name, &points) != EOF; i++)
    // {
    //     // snprintf(position_s, sizeof(position_s), "%d", position);
    //     // snprintf(points_s, sizeof(points_s), "%d", points);
    // }
    int i = 0;
    while (fgets(line, sizeof(line), fp))
    {
        position = strtok(line, ",");
        team_name = strtok(NULL, ",");
        points = strtok(NULL, ",");
        iText(table_teams_rank.x + 30, table_teams_rank.y - (i * 30) - 20, position, GLUT_BITMAP_9_BY_15);
        iText(table_teams_rank.x + 310, table_teams_rank.y - (i * 30) - 20, team_name, GLUT_BITMAP_9_BY_15);
        iText(table_teams_rank.x + 630, table_teams_rank.y - (i * 30) - 20, points, GLUT_BITMAP_9_BY_15);
        i++;
    }
    fclose(fp);
}
//===============================================login====================================================================

// login Page

typedef struct
{
    char Name_box[3][50];
    int x;
    int y;
    int w;
    int h;
} LOGIN;
LOGIN ID_1, ID_2, Enter, Login_bar, photoUpload;

void initLogIn()
{

    strcpy(ID_1.Name_box[0], "Name  :");
    strcpy(photoUpload.Name_box[0], "Image :");
    strcpy(ID_2.Name_box[0], "Email :");
    strcpy(Enter.Name_box[1], "Enter");
    strcpy(Login_bar.Name_box[1], "LOG IN");

    Login_bar.x = menu.x;
    Login_bar.y = matches.y - matches.h - 30;
    Login_bar.w = matches.w;
    Login_bar.h = matches.h;

    ID_1.x = Login_bar.x + (Login_bar.w / 2) - 50;
    ID_1.y = Login_bar.y - 100;
    ID_1.w = 250;
    ID_1.h = 30;

    ID_2.x = ID_1.x;
    ID_2.y = ID_1.y - 60;
    ID_2.w = 250;
    ID_2.h = 30;

    photoUpload.x = ID_2.x;
    photoUpload.y = ID_2.y - 60;
    photoUpload.w = 250;
    photoUpload.h = 30;

    Enter.x = photoUpload.x + 20;
    Enter.y = photoUpload.y - 80;
    Enter.w = 100;
    Enter.h = 40;
}

void drawloginBoxes(LOGIN box)
{
    iSetColor(CHAI);
    iFilledRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iText(box.x - 80, box.y + 5, box.Name_box[0], GLUT_BITMAP_TIMES_ROMAN_24);
}

// for save Login_ info

void save_account_info()
{

    FILE *accountfile;
    accountfile = fopen("File Input//accountfile.txt", "w");
    fprintf(accountfile, "%s\n%s\n%s", Name_input, Email_input, Photo_input);
    fclose(accountfile);
}

//=======================================================================================================================
//===============================================Schedule==========================================================================---
//=========================================================================================================================

Teams schedule_box, inter_schedule, domestic_shcedule, schedule_table_1, schedule_table_2;
void initScheduleBox()
{

    schedule_box.x = matches.x;
    schedule_box.y = matches.y - 105;
    schedule_box.w = matches.w;
    schedule_box.h = 100;
    strcpy(schedule_box.teams_bar_text[0], "CRICKET SCHEDULE");

    inter_schedule.x = schedule_box.x + 10;
    inter_schedule.y = schedule_box.y + 10;
    inter_schedule.w = 150;
    inter_schedule.h = 20;
    strcpy(inter_schedule.teams_name_text[0], "International");

    domestic_shcedule.x = inter_schedule.x + inter_schedule.w + 20;
    domestic_shcedule.y = inter_schedule.y;
    domestic_shcedule.w = 150;
    domestic_shcedule.h = 20;
    strcpy(domestic_shcedule.teams_name_text[0], "Domestic");

    schedule_table_1.x = schedule_box.x;
    schedule_table_1.y = schedule_box.y - 30;
    schedule_table_1.w = schedule_box.w;
    schedule_table_1.h = 25;

    schedule_table_2.x = schedule_table_1.x;
    schedule_table_2.y = schedule_table_1.y - 190;
    schedule_table_2.w = schedule_table_1.w;
    schedule_table_2.h = 25;
    strcpy(schedule_table_2.teams_type_text[0], "FRIDAY,FEBRUARY 24,2023");
}
Teams schedule_match_1, schedule_match_2, schedule_match_3, schedule_match_4;

void drawScheduleBoxMathces(Teams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 5, box.y + 35, box.teams_bar_text[0], GLUT_BITMAP_9_BY_15);
    iText(box.x + 370, box.y + 35, box.teams_bar_text[1], GLUT_BITMAP_9_BY_15);
    iText(box.x + 370, box.y + 15, box.teams_bar_text[2], GLUT_BITMAP_9_BY_15);
    iText(box.x + 800, box.y + 35, box.teams_bar_text[3], GLUT_BITMAP_9_BY_15);
}

void initScheduleMatches()
{
    schedule_match_1.x = schedule_table_1.x;
    schedule_match_1.y = schedule_table_1.y - 75;
    schedule_match_1.w = schedule_table_1.w;
    schedule_match_1.h = 65;
    strcpy(schedule_match_1.teams_bar_text[2], "SuperSport Park,Centurion");
    strcpy(schedule_match_1.teams_bar_text[3], "2:00 PM");

    schedule_match_2.x = schedule_table_1.x;
    schedule_match_2.y = schedule_table_1.y - 150;
    schedule_match_2.w = schedule_table_1.w;
    schedule_match_2.h = 65;

    schedule_match_3.x = schedule_table_2.x;
    schedule_match_3.y = schedule_table_2.y - 75;
    schedule_match_3.w = schedule_table_2.w;
    schedule_match_3.h = 65;
    strcpy(schedule_match_3.teams_bar_text[0], "England Tour of Bangladesh, 2023");
    strcpy(schedule_match_3.teams_bar_text[1], "BANGLADESH vs ENGLAND,1st ODI");
    strcpy(schedule_match_3.teams_bar_text[2], "Shere Bangla National Stadium");
    strcpy(schedule_match_3.teams_bar_text[3], "2:30 PM");

    schedule_match_4.x = schedule_table_2.x;
    schedule_match_4.y = schedule_table_2.y - 150;
    schedule_match_4.w = schedule_table_2.w;
    schedule_match_4.h = 65;
    strcpy(schedule_match_4.teams_bar_text[0], "Australia Tour of India,2023");
    strcpy(schedule_match_4.teams_bar_text[1], "SOUTH AFRICA vs WEST INDIES,1st Test,Day 1");
    strcpy(schedule_match_4.teams_bar_text[2], "Holkar stadium,INDIA");
    strcpy(schedule_match_4.teams_bar_text[3], "2:30 PM");
}

//==============================Live Score =====================================================================
void drawTableBoxes_score(Teams box)
{
    iSetColor(CHAI);
    iFilledRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 5, box.y + 6, box.teams_type_text[0], GLUT_BITMAP_9_BY_15);
}

Teams live_score_head, live_mat, past_mat, upcoming_mat, live_table_1, live_table_2;
Match past_match_1, shadow_past_match_1, past_match_2, shadow_past_match_2;

void initLiveBoxes()
{

    live_score_head.x = schedule_box.x;
    live_score_head.y = schedule_box.y;
    live_score_head.w = schedule_box.w;
    live_score_head.h = 100;

    live_mat.x = inter_schedule.x;
    live_mat.y = inter_schedule.y;
    live_mat.w = 150;
    live_mat.h = 20;
    strcpy(live_mat.teams_name_text[0], "Live");

    past_mat.x = domestic_shcedule.x;
    past_mat.y = domestic_shcedule.y;
    past_mat.w = 150;
    past_mat.h = 20;
    strcpy(past_mat.teams_name_text[0], "Past");

    upcoming_mat.x = domestic_shcedule.x + domestic_shcedule.w + 20;
    upcoming_mat.y = inter_schedule.y;
    upcoming_mat.w = 150;
    upcoming_mat.h = 20;
    strcpy(upcoming_mat.teams_name_text[0], "Upcoming");

    live_table_1.x = live_score_head.x;
    live_table_1.y = live_score_head.y - 30;
    live_table_1.w = live_score_head.w;
    live_table_1.h = 25;
    strcpy(live_table_1.teams_type_text[0], "WEST INDIES TOUR OF SOUTH AFRICA, 2023");

    live_table_2.x = live_table_1.x;
    live_table_2.y = live_table_1.y - 190;
    live_table_2.w = live_table_1.w;
    live_table_2.h = 25;
    strcpy(live_table_2.teams_type_text[0], "ICC CRICKET WORLD CUP LEAGUE TWO 2019-23");

    // match_1 initialize
    match_1_live.x = match_1.x;
    match_1_live.y = match_1.y - 130;
    match_1_live.w = match_1.w;
    match_1_live.h = match_1.h;
    strcpy(match_1_live.mat_text[0], "11th Match,Group A,ICC Womens T20");
    match_1_live.team_1_run = match_1.team_1_run;
    match_1_live.team_2_run = match_1.team_2_run;
    match_1_live.team_1_wicket = match_1.team_1_wicket;
    match_1_live.team_2_wicket = match_1.team_2_wicket;
    match_1_live.team_1_over = match_1.team_1_over;
    match_1_live.team_2_over = match_1.team_2_over;
    strcpy(match_1_live.mat_text[3], "Match is running");
    strcpy(match_1_live.mat_teams_bmp[0], "Assets//Australia.bmp");
    strcpy(match_1_live.mat_teams_bmp[1], "Assets//srilanka.bmp");

    shadow_match_1_live.x = match_1_live.x;
    shadow_match_1_live.y = match_1_live.y + match_1_live.h - 20;
    shadow_match_1_live.w = match_1_live.w;
    shadow_match_1_live.h = 20;

    // match_2 initialize
    match_2_live.x = match_1.x;
    match_2_live.y = match_2.y - 325;
    match_2_live.w = match_2.w;
    match_2_live.h = match_2.h;
    strcpy(match_2_live.mat_text[0], "1st test,England tour of Newzealand");
    match_2_live.team_1_run = match_2.team_1_run;
    match_2_live.team_2_run = match_2.team_2_run;
    match_2_live.team_1_wicket = match_2.team_1_wicket;
    match_2_live.team_2_wicket = match_2.team_2_wicket;
    match_2_live.team_1_over = match_2.team_1_over;
    match_2_live.team_2_over = match_2.team_2_over;
    strcpy(match_2_live.mat_text[3], "Match is running");
    strcpy(match_2_live.mat_teams_bmp[0], "Assets//england.bmp");
    strcpy(match_2_live.mat_teams_bmp[1], "Assets//new-zealand.bmp");

    shadow_match_1_live.x = match_2_live.x;
    shadow_match_1_live.y = match_2_live.y + match_2_live.h - 20;
    shadow_match_1_live.w = match_2_live.w;
    shadow_match_1_live.h = 20;

    // mpast match initialize
    past_match_1.x = match_1_live.x;
    past_match_1.y = match_1_live.y;
    past_match_1.w = match_1_live.w;
    past_match_1.h = match_1_live.h;
    strcpy(past_match_1.mat_text[0], "1st t20 match");
    past_match_1.team_1_run = 165;
    past_match_1.team_2_run = 160;
    past_match_1.team_1_wicket = 7;
    past_match_1.team_2_wicket = 10;
    past_match_1.team_1_over = 17;
    past_match_1.ball = 3;
    past_match_1.team_2_over = 16.2;
    strcpy(past_match_1.mat_text[3], "Bangladesh wins the match by wickets");
    strcpy(past_match_1.mat_teams_bmp[0], "Assets//bangladesh.bmp");
    strcpy(past_match_1.mat_teams_bmp[1], "Assets//west-indies_small.bmp");

    shadow_past_match_1.x = past_match_1.x;
    shadow_past_match_1.y = past_match_1.y + past_match_1.h - 20;
    shadow_past_match_1.w = past_match_1.w;
    shadow_past_match_1.h = 20;

    // past match_2 initialize
    past_match_2.x = match_2_live.x;
    past_match_2.y = match_2_live.y;
    past_match_2.w = match_2_live.w;
    past_match_2.h = match_2_live.h;
    strcpy(past_match_2.mat_text[0], "2nd t20 match");
    past_match_2.team_1_run = 172;
    past_match_2.team_2_run = 170;
    past_match_2.team_1_wicket = 7;
    past_match_2.team_2_wicket = 9;
    past_match_2.team_1_over = 18;
    past_match_2.ball = 5;
    past_match_2.team_2_over = 20.0;
    strcpy(past_match_2.mat_text[3], "UAE won the match by 5 wickets");

    strcpy(past_match_2.mat_teams_bmp[0], "Assets//united-arab-emirates.bmp");
    strcpy(past_match_2.mat_teams_bmp[1], "Assets//papua-new-guinea.bmp");

    shadow_past_match_2.x = past_match_2.x;
    shadow_past_match_2.y = past_match_2.y + past_match_2.h - 20;
    shadow_past_match_2.w = 310;
    shadow_past_match_2.h = 20;
}

//=======================================All Pages========================================================
void AllLiveScorePages()
{
    drawRankBoxes(live_score_head);
    drawRankType(live_mat);
    drawRankType(past_mat);
    drawRankType(upcoming_mat);
    if (currentPage == LiveScoreLivePage)
    {
        strcpy(live_score_head.teams_bar_text[0], "LIVE CRICKET SCORE");
        drawTableBoxes_score(live_table_1);
        drawTableBoxes_score(live_table_2);
        shadowBox(shadow_match_1_live);
        drawMatchBox(match_1_live);
        shadowBox(shadow_match_2_live);
        drawMatchBox(match_2_live);
    }
    if (currentPage == LiveScorePastPage)
    {
        strcpy(live_score_head.teams_bar_text[0], "RECENT CRICKET MATCHES");
        strcpy(live_table_1.teams_type_text[0], "Bangladesh tour of Newzealand");
        drawTableBoxes_score(live_table_1);
        strcpy(live_table_2.teams_type_text[0], "Pakistan Tour of India");
        drawTableBoxes_score(live_table_2);
        shadowBox(shadow_past_match_1);
        drawMatchBox(past_match_1);
        shadowBox(shadow_past_match_2);
        drawMatchBox(past_match_2);
    }
    if (currentPage == LiveScoreUpcomingPage)
    {
        strcpy(live_score_head.teams_bar_text[0], "UPCOMING CRICKET MATCHES");
    }
}
//======================================All schedule pages==========================================

void AllSchedulePages()
{
    drawRankBoxes(schedule_box);
    drawRankType(inter_schedule);
    drawRankType(domestic_shcedule);

    if (currentPage == ScheduleInternationalPage)
    {
        strcpy(schedule_table_1.teams_type_text[0], "THURDAY,FEBRUARY 23,2023");
        strcpy(schedule_table_2.teams_type_text[0], "FRIDAY,FEBRUARY 24,2023");
        strcpy(schedule_match_1.teams_bar_text[0], "WEST INDIES Tour of SOUTH AFRICA,2023");
        strcpy(schedule_match_1.teams_bar_text[1], "SOUTH AFRICA vs WEST INDIES,1st Test,Day 1");
        strcpy(schedule_match_2.teams_bar_text[0], "ICC MENS T20 WORLD CUP AMERICAS,2023");
        strcpy(schedule_match_2.teams_bar_text[1], "Bermuda vs Panama,6th Match");
        strcpy(schedule_match_2.teams_bar_text[2], "Belgrano Athletic Club Ground,belgrano");
        strcpy(schedule_match_2.teams_bar_text[3], "12:00 AM");
        drawTableBoxes_score(schedule_table_1);
        drawTableBoxes_score(schedule_table_2);
        drawScheduleBoxMathces(schedule_match_1);
        drawScheduleBoxMathces(schedule_match_2);
        drawScheduleBoxMathces(schedule_match_3);
        drawScheduleBoxMathces(schedule_match_4);
    }
    if (currentPage == ScheduleDomesticPage)
    {
        strcpy(schedule_table_1.teams_type_text[0], "SATURDAY,JANUARY 24,2023");
        strcpy(schedule_table_2.teams_type_text[0], "SUNDAY,FEBRUARY 25,2023");
        strcpy(schedule_match_1.teams_bar_text[0], "IRELAND TOUR OF AFGHANISTAN,2023");
        strcpy(schedule_match_3.teams_bar_text[0], "ZIMBABUAE TOUR OF SRILANKA, 2023");
        strcpy(schedule_match_2.teams_bar_text[0], "BERMUDA TOUR OF PANAMA,2023");
        strcpy(schedule_match_2.teams_bar_text[1], "Bermuda vs Panama,1st");
        strcpy(schedule_match_2.teams_bar_text[2], "Belgrano Athletic Club Ground,belgrano");
        strcpy(schedule_match_2.teams_bar_text[3], "12:00 AM");
        drawTableBoxes_score(schedule_table_1);
        drawTableBoxes_score(schedule_table_2);
        drawScheduleBoxMathces(schedule_match_1);
        drawScheduleBoxMathces(schedule_match_2);
        drawScheduleBoxMathces(schedule_match_3);
        drawScheduleBoxMathces(schedule_match_4);
    }
}
void AllNewsPages()
{
}

void AllRankingPages()
{

    drawRankBoxes(ranking_men);
    drawRankType(batting);
    drawRankType(bowling);
    drawRankType(all_rounder);
    drawRankType(teams_rank);
    drawRankType(test);
    drawRankType(odi);
    drawRankType(t_20);
    drawTableBoxes(table_teams_rank);
    if (currentRankState == rank_team)
    {
        if (currentPage == Test)
        {
            InputFileRead(file_ranking_Test);
        }
        if (currentPage == ODI)
        {
            InputFileRead(file_ranking_ODI);
        }
        if (currentPage == t20)
        {
            InputFileRead(file_ranking_t20);
        }
    }
    if (currentRankState == rank_batsman)
    {
        if (currentPage == Test)
        {
            InputFileRead(file_batting_Test);
        }
        if (currentPage == ODI)
        {
            InputFileRead(file_batting_ODI);
        }
        if (currentPage == t20)
        {
            InputFileRead(file_batting_t20);
        }
    }
    if (currentRankState == rank_bowler)
    {
        if (currentPage == Test)
        {
            InputFileRead(file_bowling_Test);
        }
        if (currentPage == ODI)
        {
            InputFileRead(file_bowling_ODI);
        }
        if (currentPage == t20)
        {
            InputFileRead(file_bowling_t20);
        }
    }
    if (currentRankState == rank_allrounder)
    {
        if (currentPage == Test)
        {
            InputFileRead(file_allrounder_Test);
        }
        if (currentPage == ODI)
        {
            InputFileRead(file_allrounder_ODI);
        }
        if (currentPage == t20)
        {
            InputFileRead(file_allrounder_t20);
        }
    }
}

void AllTeamsPages()
{
    if (currentTeamType == TeamsInternationalPage)
    {
        strcpy(teams_bar.teams_bar_text[0], "CRICKET TEAMS");
        drawTeamsBar(teams_bar);
        strcpy(teams_type_1.teams_type_text[0], "International");
        drawTeamsType(teams_type_1);
        strcpy(teams_type_2.teams_type_text[0], "Domestic");
        drawTeamsType(teams_type_2);
        drawInTeams(Bangladesh);
        drawInTeams(India);
        drawInTeams(Pakistan);
        drawInTeams(Australia);
        drawInTeams(New_zealand);
        drawInTeams(England);
        drawInTeams(Srilanka);
        drawInTeams(Wes_indies);
        drawInTeams(Afghanistan);
    }
    if (currentTeamType == TeamsDomesticPage)
    {
        strcpy(teams_bar.teams_bar_text[0], "CRICKET TEAMS");

        drawTeamsBar(teams_bar);
        strcpy(teams_type_1.teams_type_text[0], "International");

        drawTeamsType(teams_type_1);
        strcpy(teams_type_2.teams_type_text[0], "Domestic");

        drawTeamsType(teams_type_2);
        drawDomTeams(Bangladesh);
        drawDomTeams(India);
        drawDomTeams(Pakistan);
        drawDomTeams(Australia);
        drawDomTeams(New_zealand);
        drawDomTeams(England);
        drawDomTeams(Srilanka);
        drawDomTeams(Wes_indies);
        drawDomTeams(Afghanistan);
    }
    if (currentTeamType == BD)
    {
        if (current_country_state == country_Players)
        {
            strcpy(BD_bar.teams_bar_text[0], "Bangladesh National Cricket Team");
            drawTeamsBar(BD_bar);
            strcpy(player.teams_type_text[0], "Players");
            drawTeamsType(player);
            strcpy(stats.teams_type_text[0], "Stats");
            drawTeamsType(stats);
            drawPlayers(tamim);
            drawPlayers(liton);
            drawPlayers(sabbir);
            drawPlayers(shanto);
            drawPlayers(mustafiz);
            drawPlayers(mash);
            drawPlayers(rubel);
            drawPlayers(jayed);
            drawPlayers(sakib);
            drawPlayers(mahmudullah);
            drawPlayers(miraz);
            drawPlayers(mushfiq);
            drawPlayers(mithun);
            shadowBox(shadow_batsman);
            shadowBox(shadow_bowler);
            shadowBox(shadow_allrounder_box);
            shadowBox(shadow_wicket_keeper);
            drawTeamsType(batsman_box);
            drawTeamsType(bowler_box);
            drawTeamsType(allrounder_box);
            drawTeamsType(wicket_keeper);
            // iText(20, 20, "amar nam paurboajsdfj");
        }

        if (current_country_state == country_stats)
        {
            // iText(100, 100, "hi");
        }
        if (current_country_state == country_tamim)
        {
            drawPlayerBar(TamimProfile);
            PlayerProfileBox(TamimAccount);
            // iText(100, 100, "hi tamim");
        }
        // if (currentPlayer == tamim_box)
        // {
        // }
    }
    // if (current_desh == BD && current_country_state == country_stats)
    // {
    //     strcpy(BD_bar.teams_bar_text[0], "Bangladesh National Cricket Team statistics");
    //     drawTeamsBar(BD_bar);
    //     strcpy(player.teams_type_text[0], "Players");
    //     drawTeamsType(player);
    //     strcpy(stats.teams_type_text[0], "Stats");
    //     drawTeamsType(stats);
    // }

    // if (current_country_state==country_Players&& current_desh==IND)
    // {
    // }
    // if (current_country_state==country_Players&&current_desh==PAK)
    // {
    // }
    // if (current_country_state==country_Players&&current_desh==KNR)
    // {
    // }
    // if (current_country_state==country_Players&&current_desh==DD)
    // {
    // }
}

void AllLoginPages()
{
    iSetColor(CHAI);
    iFilledRectangle(Login_bar.x, Login_bar.y, Login_bar.w, Login_bar.h);
    iRectangle(Login_bar.x, Login_bar.y, Login_bar.w, Login_bar.h);
    drawloginBoxes(ID_1);
    drawloginBoxes(ID_2);
    iText(ID_1.x + 10, ID_1.y + 10, Name_input, GLUT_BITMAP_9_BY_15);
    iText(ID_2.x + 10, ID_2.y + 10, Email_input, GLUT_BITMAP_9_BY_15);
    if (currentPage == LogInputPage)
    {
        iText(Login_bar.x + (Login_bar.w / 2) - 40, Login_bar.y + 7, Login_bar.Name_box[1], GLUT_BITMAP_TIMES_ROMAN_24);
        drawloginBoxes(photoUpload);
        drawloginBoxes(Enter);
        iText(photoUpload.x + 10, photoUpload.y + 10, Photo_input, GLUT_BITMAP_9_BY_15);
        iText(Enter.x + 10, Enter.y + 7, Enter.Name_box[1], GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (currentPage == AccountInformationPage)
    {
        iText(Login_bar.x + (Login_bar.w / 2) - 90, Login_bar.y + 7, "ACCOUNT   INFORMATION", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(matches.x, ID_2.y - 180, Photo_input);
    }
}

// main idraw function
void iDraw()
{
    iClear();
    if (currentMainPage == intro)
    {
        iShowBMP(0, 0, "Assets//intro_final.bmp");
        iText(830, 40, "Press Insert.....", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        drawBG();
        drawAllHeader();
        if (currentMainPage == HomePage)
        {
            drawHomePage();
        }
        if (previousMainPage != intro && currentMainPage == LiveScorePage)
        {
            AllLiveScorePages();
        }
        if (previousMainPage != intro && currentMainPage == SchedulePage)
        {
            AllSchedulePages();
        }
        if (previousMainPage != intro && currentMainPage == NewsPage)
        {
            AllNewsPages();
        }
        if (previousMainPage != intro && currentMainPage == RankingPage)
        {
            AllRankingPages();
        }
        if (previousMainPage != intro && currentMainPage == TeamsPage)
        {
            AllTeamsPages();
        }

        if (previousMainPage != intro && currentMainPage == LogInPage)
        {
            AllLoginPages();
        }
    }
}
//=================================AllMouseEvent===================================================
void iMouseMove(int mx, int my)
{
}

int isPointInBox(int mx, int my, int x, int y, int w, int h)
{
    if (mx >= x && mx <= (x + w) && my >= y && my <= (y + h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isButtonClicked(int mx, int my, int x, int y, int w, int h)
{

    if (isPointInBox(mx, my, x, y, w, h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void checkButtonClicks(int mx, int my)
{
    if (isButtonClicked(mx, my, menu.x, menu.y, 120, menu.h))
    {

        if (currentMainPage != intro)
        {
            printf("Cricinfo bar was clicked\n");
            previousMainPage = currentMainPage;
            currentMainPage = HomePage;
        }
    }
    if (isButtonClicked(mx, my, live_score.x, live_score.y, live_score.w, live_score.h))
    {
        if (currentMainPage != intro)
        {
            previousMainPage = currentMainPage;
            currentMainPage = LiveScorePage;
            currentPage = LiveScoreLivePage;
            printf("live score bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, matches.x, matches.y, matches.w, matches.h))
    {
        if (currentMainPage != intro)
        {
            previousMainPage = currentMainPage;
            currentMainPage = LiveScorePage;
            currentPage = LiveScoreLivePage;
            printf("live score bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, live_mat.x, live_mat.y, live_mat.w, live_mat.h))
    {
        if (currentMainPage == LiveScorePage)
        {
            currentPage = LiveScoreLivePage;
            printf("currentMainPage %d\n", currentMainPage);
            printf("currentPage %d\n", currentPage);
            printf("live score live bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, past_mat.x, past_mat.y, past_mat.w, past_mat.h))
    {
        if (currentMainPage == LiveScorePage)
        {
            currentPage = LiveScorePastPage;
            printf("live score past bar was clicked\n");
            printf("currentMainPage %d\n", currentMainPage);
        }
    }
    if (isButtonClicked(mx, my, upcoming_mat.x, upcoming_mat.y, upcoming_mat.w, upcoming_mat.h))
    {
        if (currentMainPage == LiveScorePage)
        {
            currentPage = LiveScoreUpcomingPage;
            printf("live score upcoming bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, schedule.x, schedule.y, schedule.w, schedule.h))
    {
        if (currentMainPage != intro)
        {
            previousMainPage = currentMainPage;
            currentMainPage = SchedulePage;
            currentPage = ScheduleInternationalPage;
            printf("schedule bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, todays_matches.x, todays_matches.y, todays_matches.w, todays_matches.h))
    {
        if (currentMainPage ==HomePage)
        {
            previousMainPage = currentMainPage;
            currentMainPage = SchedulePage;
            currentPage = ScheduleInternationalPage;
            printf("schedule bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, inter_schedule.x, inter_schedule.y, inter_schedule.w, inter_schedule.h))
    {
        if (currentMainPage == SchedulePage)
        {
            currentPage = ScheduleInternationalPage;
            printf("schedule international bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, domestic_shcedule.x, domestic_shcedule.y, domestic_shcedule.w, domestic_shcedule.h))
    {
        if (currentMainPage == SchedulePage)
        {
            currentPage = ScheduleDomesticPage;
            printf("domestic schedule bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, NEWS.x, NEWS.y, NEWS.w, NEWS.h))
    {
        if (currentMainPage != intro)
        {
            previousMainPage = currentMainPage;
            currentMainPage = NewsPage;
            printf("news bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, ranking.x, ranking.y, ranking.w, ranking.h))
    {
        if (currentMainPage != intro)
        {
            printf("ranking bar was clicked\n");
            previousMainPage = currentMainPage;
            currentMainPage = RankingPage;
            currentRankState = rank_team;
            currentPage = Test;
        }
    }
    if (isButtonClicked(mx, my, teams_rank.x, teams_rank.y, teams_rank.w, teams_rank.h))
    {
        if (currentMainPage == RankingPage)
        {
            currentRankState = rank_team;
            currentPage = Test;
            printf("teams bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, batting.x, batting.y, batting.w, batting.h))
    {
        if (currentMainPage == RankingPage)
        {
            currentRankState = rank_batsman;
            currentPage = Test;
            printf("batting bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, bowling.x, bowling.y, bowling.w, bowling.h))
    {
        if (currentMainPage == RankingPage)
        {
            currentRankState = rank_bowler;
            currentPage = Test;
            printf("bowling bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, all_rounder.x, all_rounder.y, all_rounder.w, all_rounder.h))
    {
        if (currentMainPage == RankingPage)
        {
            currentRankState = rank_allrounder;
            currentPage = Test;
            printf("allrounder score bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, test.x, test.y, test.w, test.h))
    {
        if (currentMainPage == RankingPage)
        {

            printf("test score bar was clicked\n");
            currentPage = Test;
        }
    }
    if (isButtonClicked(mx, my, odi.x, odi.y, odi.w, odi.h))
    {
        if (currentMainPage == RankingPage)
        {
            currentPage = ODI;
            printf("odi score bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, t_20.x, t_20.y, t_20.w, t_20.h))
    {
        if (currentMainPage == RankingPage)
        {

            printf("t20 score bar was clicked\n");
            currentPage = t20;
        }
    }

    if (isButtonClicked(mx, my, teams.x, teams.y, teams.w, teams.h))
    {
        if (currentMainPage != intro)
        {
            printf("teams bar was clicked\n");
            previousMainPage = currentMainPage;
            currentMainPage = TeamsPage;
            currentTeamType = TeamsInternationalPage;
            teamsHomepage = true;
        }
    }
    if (isButtonClicked(mx, my, teams_type_1.x, teams_type_1.y, teams_type_1.w, teams_type_1.h))
    {
        if (teamsHomepage)
        {
            printf("international teams bar was clicked\n");
            currentTeamType = TeamsInternationalPage;
        }
    }
    if (isButtonClicked(mx, my, teams_type_2.x, teams_type_2.y, teams_type_2.w, teams_type_2.h))
    {
        if (teamsHomepage)
        {
            printf("fomestic teams bar was clicked\n");
            currentTeamType = TeamsDomesticPage;
        }
    }
    if (isButtonClicked(mx, my, Bangladesh.x, Bangladesh.y, Bangladesh.w, Bangladesh.h))
    {
        if (teamsHomepage)
        {
            printf("Bangladesh teams bar was clicked\n");
            currentTeamType = BD;
            current_country_state = country_Players;
            teamsHomepage = false;
            BangladeshHomepage = true;
            // current_country_state = country_Players;
        }
    }

    if (isButtonClicked(mx, my, player.x, player.y, player.w, player.h))
    {
        if (currentTeamType == BD)
        {
            printf("player teams bar was clicked\n");
            current_country_state = country_Players;
            // BangladeshHomepage = true;
        }
    }
    if (isButtonClicked(mx, my, stats.x, stats.y, stats.w, stats.h))
    {
        if (currentTeamType == BD)
        {
            printf("stats teams bar was clicked\n");
            current_country_state = country_stats;
            BangladeshHomepage = false;
        }
    }
    if (isButtonClicked(mx, my, tamim.x, tamim.y, tamim.w, tamim.h))
    {
        if (BangladeshHomepage)
        {
            printf("tamim teams bar was clicked\n");
            current_country_state = country_tamim;
        }
    }
    if (isButtonClicked(mx, my, match_1.x, match_1.y, match_1.w, match_1.h))
    {
        if (currentMainPage == HomePage)
        {
            printf("match _1  teams bar was clicked\n");
            // updateWicket(match_1);
        }
    }
    if (isButtonClicked(mx, my, match_2.x, match_2.y, match_2.w, match_2.h))
    {
        if (currentMainPage == HomePage)
        {
            printf("match _2 teams bar was clicked\n");
            // updateWicket(match_2);
        }
    }
    if (isButtonClicked(mx, my, match_3.x, match_3.y, match_3.w, match_3.h))
    {
        if (currentMainPage == HomePage)
        {
            printf("match _2 teams bar was clicked\n");
            // updateWicket(match_3);
        }
    }

    // if (isButtonClicked(mx, my, Bangladesh.x, Bangladesh.y, Bangladesh.w, Bangladesh.h))
    // {
    //     if (teamsHomepage)
    //     {
    //         printf("Bangladesh teams bar was clicked\n");
    //         // currentTeamType = BD;
    //         BangladeshHomepage = true;
    //         current_country_state = country_Players;
    //         teamsHomepage = false;
    //         // current_country_state = country_Players;
    //     }
    // }

    // if (isButtonClicked(mx, my, player.x, player.y, player.w, player.h))
    // {
    //     if (currentTeamType==BD)
    //     {
    //         printf("player teams bar was clicked\n");
    //         current_country_state = country_Players;
    //         // currentPage=Bangladesh_player;
    //     }
    // }

    // if (isButtonClicked(mx, my, stats.x, stats.y, stats.w, stats.h))
    // {
    //     if (currentTeamType==BD)
    //     {
    //         printf("stats teams bar was clicked\n");
    //         current_country_state = country_stats;
    //     }
    // }
    // if (isButtonClicked(mx, my, tamim.x, tamim.y, tamim.w, tamim.h))
    // {
    //     if (current_country_state==country_Players)
    //     {
    //         printf("tamim  bar was clicked\n");
    //         currentPlayer = tamim_box;
    //         // BangladeshHomepage = false;
    //         // current_country_state = country_stats;
    //     }
    // }

    if (isButtonClicked(mx, my, Login.x, Login.y, Login.w, Login.h))
    {
        if (currentMainPage != intro)
        {
            previousMainPage = currentMainPage;
            currentMainPage = LogInPage;
            currentPage = LogInputPage;
            printf("Login bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, Enter.x, Enter.y, Enter.w, Enter.h))
    {
        if (currentMainPage == LogInPage)
        {
            currentPage = AccountInformationPage;
            printf("Enter bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, ID_1.x, ID_1.y, ID_1.w, ID_1.h))
    {
        if (currentMainPage == LogInPage)
        {
            printf("name box bar was clicked\n");
            current_mouseState = id_1_input;
        }
    }
    if (isButtonClicked(mx, my, ID_2.x, ID_2.y, ID_2.w, ID_2.h))
    {
        if (currentMainPage == LogInPage)
        {
            current_mouseState = id_2_input;
            printf("email box bar was clicked\n");
        }
    }
    if (isButtonClicked(mx, my, photoUpload.x, photoUpload.y, photoUpload.w, photoUpload.h))
    {
        if (currentMainPage == LogInPage)
        {
            current_mouseState = profile_in;
            printf("image box bar was clicked\n");
        }
    }
}

// all Mouse event

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        checkButtonClicks(mx, my);
        // printf("x = %d, y= %d\n", mx, my);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}
// All keyboard event
void iKeyboard(unsigned char key)
{
    if (key == 'q')
    {
        exit(0);
    }
    if (current_mouseState == id_1_input)
    {
        if (key == 8) // if the user has pressed on backspace
        {
            if (name_idx >= 0) // if there is still some character in the string
            {
                Name_input[name_idx] = '\0';
                name_idx--;
            }
        }
        else
        {
            name_idx++;
            Name_input[name_idx] = key;
        }
    }
    if (current_mouseState == id_2_input)
    {
        printf("Taking email input \n");
        if (key == 8) // if the user has pressed on backspace
        {
            if (email_idx >= 0) // if there is still some character in the string
            {
                Email_input[email_idx] = '\0';
                email_idx--;
            }
        }
        else
        {
            email_idx++;
            Email_input[email_idx] = key;
        }
    }
    if (current_mouseState == profile_in)
    {
        printf("Takingptinput \n");
        if (key == 8) // if the user has pressed on backspace
        {
            if (photo_idx >= 0)
            {
                Photo_input[photo_idx] = '\0';
                photo_idx--;
            }
        }
        else
        {
            photo_idx++;
            Photo_input[photo_idx] = key;
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_INSERT)
    {
        previousMainPage = HomePage;
        currentMainPage = HomePage;
    }
}

int main()
{
    srand((unsigned)time(&t1));
    printf("hi interval %d\n", interval);
    //if (currentMainPage = HomePage)
    //{
        iSetTimer(1000, updateMatchStatus);
        iSetTimer(interval, updateWicket);
  //  }
    initHeader();
    initMatchBoxes();
    initTeams();
    initLogIn();
    initInTeams();
    initTeamsRank();
    initScheduleBox();
    initLiveBoxes();
    initBangladesh();
    initplayer();
    initIndividualPlayer();
    initScheduleMatches();
    wicketfall();
    // updateLiveMatch(match_1,match_1_live);
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "CRICINFO");
    return 0;
}
