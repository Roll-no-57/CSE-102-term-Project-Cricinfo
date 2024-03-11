#include "iGraphics.h"
// for suffle random number
char file_ranking_men[50] = "icc_rank_men.txt";
time_t t1;
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define MENU_CLR 0, 146, 112
#define CHAI 227, 230, 227
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
char Header_matches_text[header_matches_text_no][100] = {"Matches", "BD vs IND", "NZ vs WE", "PAK vs ENG", "DG vs CV", "AF VS SA"};
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

int name_idx = -1;
int email_idx = -1;

enum MouseState
{
    id_1_input,
    id_2_input,
    ProfilePage,

    none
};
MouseState current_mouseState = none;

// Different Page opening
bool InternationalPage = true;
enum Pagestate
{
    intro,
    HomePage,
    RankingPage,
    NewsPage,
    SchedulePage,
    LiveScorePage,

    TeamsPage,
    TeamsInternational,
    TeamsDomestic,

    DomesticPage,

    LogInPage,

    BangladeshPage,
    IndiaPage,
    PakistanPage,

    TeamsTestPage,
    BattingTestPage,
    BowlingTestPage,
    All_rounderTestPage,

    TeamsODIPage,
    BattingODIPage,
    BowlingODIPage,
    All_rounderODIPage,

    Teamst20Page,
    Battingt20Page,
    Bowlingt20Page,
    All_roundert20Page,

    LiveScoreLivePage,
    LiveScorePastPage,
    LiveScoreUpcomingPage,

};

Pagestate currentPage = intro, prevPage = intro, TeamsInternational = TeamsPage;

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

    iText(menu.x + 20, menu.y + 20, "Cricinfo");
    iText(live_score.x + 20, live_score.y + 20, "Live score");
    iText(schedule.x + 20, schedule.y + 20, "Schedule");
    iText(NEWS.x + 20, NEWS.y + 20, "News");
    iText(ranking.x + 20, ranking.y + 20, "Ranking");
    iText(teams.x + 20, teams.y + 20, "Teams");
    iText(Login.x + 20, Login.y + 20, "Login");

    iSetColor(255, 255, 255);
    for (int i = 0; i < header_matches_text_no; i++)
    {
        iText(matches.x + 10 + i * 90, matches.y + 11, Header_matches_text[i]);
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
    char mat_teams_bmp[mat_teams_bmp_r][mat_teams_bmp_c];
    char todays_match_text[today_mat_text_r][today_mat_text_c];
    char news_mat_bmp[news_mat_bmp_r][news_mat_bmp_c];

    int color;
} Match;

Match match_1, match_2, match_3, shadow_match_1, shadow_match_2, shadow_match_3, news, shadow_news, todays_matches, shadow_todays_matches, match_type_1, match_type_2, match_type_3;

// initialize Match boxes
void initMatchBoxes()
{
    // match_1 initialize
    match_1.x = 50;
    match_1.y = 350;
    match_1.w = 310;
    match_1.h = 150;
    strcpy(match_1.mat_text[0], "11th Match,Group A,ICC Womens T20");
    match_1.team_1_run = 0;
    match_1.team_2_run = 160;
    match_1.team_1_wicket = 0;
    match_1.team_2_wicket = 10;
    match_1.team_1_over = 0.0;
    match_1.team_2_over = 16.0;
    strcpy(match_1.mat_text[3], "Australia won by 10 wickets");
    strcpy(match_1.mat_teams_bmp[0], "Assets//Australia.bmp");
    strcpy(match_1.mat_teams_bmp[1], "Assets//srilanka.bmp");

    shadow_match_1.x = 50;
    shadow_match_1.y = 480;
    shadow_match_1.w = 310;
    shadow_match_1.h = 20;

    match_type_1.x = match_1.x + match_1.w - 40;
    match_type_1.y = match_1.y + match_1.h - 40;
    match_type_1.w = 20;
    match_type_1.h = 20;
    strcpy(match_type_1.match_type_text[0], "TEST");

    // match_2 initialize
    match_2.x = 370;
    match_2.y = 350;
    match_2.w = 310;
    match_2.h = 150;
    strcpy(match_2.mat_text[0], "1st test,England tour of Newzealand");
    match_2.team_1_run = 0;
    match_2.team_2_run = 170;
    match_2.team_1_wicket = 0;
    match_2.team_2_wicket = 7;
    match_2.team_1_over = 0.0;
    match_2.team_2_over = 20.0;
    strcpy(match_2.mat_text[3], "England won by 8 wickets");

    strcpy(match_2.mat_teams_bmp[0], "Assets//england.bmp");
    strcpy(match_2.mat_teams_bmp[1], "Assets//new-zealand.bmp");

    shadow_match_2.x = 370;
    shadow_match_2.y = 480;
    shadow_match_2.w = 310;
    shadow_match_2.h = 20;

    match_type_2.x = match_2.x + match_2.w - 40;
    match_type_2.y = match_2.y + match_2.h - 40;
    match_type_2.w = 20;
    match_type_2.h = 20;
    strcpy(match_type_2.match_type_text[0], "TEST");

    // use random time for wicket

    // match_3 initialize
    match_3.x = 690;
    match_3.y = 350;
    match_3.w = 310;
    match_3.h = 150;
    strcpy(match_3.mat_text[0], "1st test,Afganistan tour of UAE");
    match_3.team_1_run = 0;
    match_3.team_2_run = 143;
    match_3.team_1_wicket = 0;
    match_3.team_2_wicket = 10;
    match_3.team_1_over = 0.0;
    match_3.team_2_over = 17.8;
    strcpy(match_3.mat_text[3], "Afganistan won by 5 runs");

    strcpy(match_3.mat_teams_bmp[0], "Assets//UAE.bmp");
    strcpy(match_3.mat_teams_bmp[1], "Assets//Afganistan.bmp");

    shadow_match_3.x = 690;
    shadow_match_3.y = 480;
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
// Update match status
//  int ball=0;
void updateMatchStatus()
{
    match_1.team_1_run += rand() % 7;
    match_2.team_1_run += rand() % 7;
    match_3.team_1_run += rand() % 7;
    match_1.team_1_over += 0.1;
    match_2.team_1_over += 0.1;
    match_3.team_1_over += 0.1;

    printf("over increasing --%.1lf\n", match_1.team_1_over);
}

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
    // for over update
    int last_digit;
    last_digit = ((int)((box.team_1_over) * 10)) % 10;

    if (last_digit == 6)
    {
        box.team_1_over = box.team_1_over + 1.0;
        box.team_1_over = box.team_1_over - .6;
    }
    iText(box.x + 180, box.y + box.h - 55, "(");
    char match_over_1[10];
    sprintf(match_over_1, "%.1lf", box.team_1_over);
    iText(box.x + 185, box.y + box.h - 55, match_over_1);
    iText(box.x + 230, box.y + box.h - 55, ")");
    // for team_2 score

    char match_run_2[10];
    sprintf(match_run_2, "%d", box.team_2_run);
    iText(box.x + 120, box.y + box.h - 95, match_run_2);
    iText(box.x + 140, box.y + box.h - 95, " - ");
    // for wicket
    char match_wicket_2[10];
    sprintf(match_wicket_2, "%d", box.team_2_wicket);
    iText(box.x + 165, box.y + box.h - 95, match_wicket_2);

    iText(box.x + 180, box.y + box.h - 95, "(");
    char match_over_2[10];
    sprintf(match_over_2, "%.1lf", box.team_2_over);
    iText(box.x + 185, box.y + box.h - 95, match_over_2);
    iText(box.x + 230, box.y + box.h - 95, ")");

    // for match status
    iSetColor(255, 0, 0);
    iText(box.x + 10, box.y + 5, box.mat_text[3]);
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
    strcpy(teams_bar.teams_bar_text[0], "CRICKET TEAMS");

    teams_type_1.x = teams_bar.x + 30;
    teams_type_1.y = teams_bar.y + 10;
    teams_type_1.w = 120;
    teams_type_1.h = 18;
    strcpy(teams_type_1.teams_type_text[0], "International");

    teams_type_2.x = teams_type_1.x + teams_type_1.w + 45;
    teams_type_2.y = teams_type_1.y;
    teams_type_2.w = teams_type_1.w;
    teams_type_2.h = teams_type_1.h;
    strcpy(teams_type_2.teams_type_text[0], "Domestic");
}

void drawTeamsBar(Teams box)
{
    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iText(box.x + 30, box.y + box.h - 25, box.teams_bar_text[0], GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawTeamsType(Teams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iSetColor(BLACK);
    iText(box.x + 5, box.y + 5, box.teams_type_text[0]);
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
    strcpy(Srilanka.InTeams_bmp[2], "Assets//league//royal-challangers-bangalore.bmp");
    strcpy(Srilanka.InTeams_bmp[3], "ROYAL CHALLENGERS BANGALORE");

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

void drawInTeams(InTeams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iShowBMP(box.x + 15, box.y + 20, box.InTeams_bmp[0]);
    iText(box.x + 95, box.y + 40, box.InTeams_bmp[1], GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawAllTeamsHead()
{
    drawTeamsBar(teams_bar);
    drawTeamsType(teams_type_1);
    drawTeamsType(teams_type_2);
}

void drawAllInterTeamsPage()
{

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

void drawDomTeams(InTeams box)
{

    iSetColor(BLACK);
    iRectangle(box.x, box.y, box.w, box.h);
    iShowBMP(box.x + 15, box.y + 20, box.InTeams_bmp[2]);
    iText(box.x + 95, box.y + 40, box.InTeams_bmp[3], GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawAllDomesTeamPage()
{
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

//==============================================Teams Individual Information==================================================

void initIndiuvidualTeamName()
{
}

void drawIndividualTeam()
{
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

void drawAllRankBoxes()
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
    int position;
    char team_name[100];
    int points;
    char points_s[50];
    char position_s[50];

    for (int i = 0; fscanf(fp, "%d %s %d", &position, team_name, &points) != EOF; i++)
    {
        snprintf(position_s, sizeof(position_s), "%d", position);
        snprintf(points_s, sizeof(points_s), "%d", points);

        iText(table_teams_rank.x + 30, table_teams_rank.y - (i * 30) - 20, position_s);
        iText(table_teams_rank.x + 310, table_teams_rank.y - (i * 30) - 20, team_name);
        iText(table_teams_rank.x + 630, table_teams_rank.y - (i * 30) - 20, points_s);
    }
    fclose(fp);
}
//===============================================schedule=====================================================================

// login Page

typedef struct
{
    char Name_box[2][50];
    int x;
    int y;
    int w;
    int h;
} LOGIN;
LOGIN ID_1, ID_2, Enter, login;

void initLogIn()
{

    strcpy(ID_1.Name_box[0], "Name  :");
    strcpy(ID_2.Name_box[0], "Email :");
    strcpy(Enter.Name_box[1], "Enter");
    strcpy(login.Name_box[1], "LOG IN");

    login.x = menu.x;
    login.y = matches.y - matches.h - 10;
    login.w = matches.w;
    login.h = matches.h;

    ID_1.x = login.x + (login.w / 2) - 50;
    ID_1.y = login.y - 100;
    ID_1.w = 250;
    ID_1.h = 30;

    ID_2.x = ID_1.x;
    ID_2.y = ID_1.x - 140;
    ID_2.w = 250;
    ID_2.h = 30;

    Enter.x = ID_2.x + 20;
    Enter.y = ID_2.y - 100;
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

void drawLoginBox()
{
    iSetColor(MENU_CLR);
    iFilledRectangle(login.x, login.y, login.w, login.h);
    drawloginBoxes(ID_1);
    drawloginBoxes(ID_2);
    drawloginBoxes(Enter);
    iText(login.x + (login.w / 2) - 40, login.y + 7, login.Name_box[1], GLUT_BITMAP_TIMES_ROMAN_24);
    iText(ID_1.x + 10, ID_1.y + 5, Name_input, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(ID_2.x + 10, ID_2.y + 5, Email_input, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(Enter.x + 10, Enter.y + 7, Enter.Name_box[1], GLUT_BITMAP_TIMES_ROMAN_24);
}
// for save login info

void save_account_info()
{

    FILE *accountfile;
    accountfile = fopen("accountfile.txt", "w");
    fprintf(accountfile, "%s\n%s", Name_input, Email_input);
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
    schedule_table_1.y = schedule_box.y - 50;
    schedule_table_1.w = schedule_box.w;
    schedule_table_1.h = 40;
    strcpy(schedule_table_1.teams_type_text[0], "THURDAY,FEBRUARY 23,2023");

    schedule_table_2.x = schedule_table_1.x;
    schedule_table_2.y = schedule_table_1.y - 190;
    schedule_table_2.w = schedule_table_1.w;
    schedule_table_2.h = 40;
    strcpy(schedule_table_2.teams_type_text[0], "FRIDAY,FEBRUARY 24,2023");
}

void drawAllSchedulePage()
{

    drawRankBoxes(schedule_box);
    drawRankType(inter_schedule);
    drawRankType(domestic_shcedule);
    drawTableBoxes(schedule_table_1);
    drawTableBoxes(schedule_table_2);
}
//==============================Live Score =====================================================================
Teams live_score_head, live_mat, past_mat, upcoming_mat, live_table_1, live_table_2;

void initLiveBoxes()
{

    live_score_head.x = schedule_box.x;
    live_score_head.y = schedule_box.y;
    live_score_head.w = schedule_box.w;
    live_score_head.h = 100;
    strcpy(live_score_head.teams_bar_text[0], "LIVE CRICKET SCORE");

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

    live_table_1.x = schedule_table_1.x;
    live_table_1.y = schedule_table_1.y;
    live_table_1.w = schedule_table_1.w;
    live_table_1.h = 40;
    strcpy(live_table_1.teams_type_text[0], "WEST INDIES TOUR OF SOUTH AFRICA, 2023");

    live_table_2.x = schedule_table_2.x;
    live_table_2.y = schedule_table_2.y;
    live_table_2.w = schedule_table_2.w;
    live_table_2.h = 40;
    strcpy(live_table_2.teams_type_text[0], "ICC CRICKET WORLD CUP LEAGUE TWO 2019-23");
}

// void initLiveScoreBarText(){

//     if(currentPage==LiveScorePage){
//         strcpy(live_score_head.teams_bar_text[0],"Live Cricket Score");
//     }
//     if(currentPage==LiveScorePastPage){
//         strcpy(live_score_head.teams_bar_text[0],"Live Cricket Score International");

//     }
//     if(currentPage==LiveScoreUpcomingPage){
//         strcpy(live_score_head.teams_bar_text[0],"Live Cricket Score Domestic");
//     }

// }

void drawAllLiveScorePage()
{
    drawRankBoxes(live_score_head);
    drawRankType(live_mat);
    drawRankType(past_mat);
    drawRankType(upcoming_mat);
    drawTableBoxes(live_table_1);
    drawTableBoxes(live_table_2);
}

// main idraw function
void iDraw()
{
    iClear();
    if (currentPage == intro)
    {
        iShowBMP(0, 0, "Assets//intro_final.bmp");
        iText(830, 40, "Press Insert.....", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        drawBG();
        drawAllHeader();
    }

    if (currentPage == HomePage)
    {
        drawHomePage();
    }
    if (currentPage == TeamsPage)
    {
        drawAllTeamsHead();
        // if (currentPage == TeamsInternational)
        // {
        //     drawAllInterTeamsPage();
        // }
        else if (currentPage == TeamsDomestic)
        {
            drawAllDomesTeamPage();
        }
    }
    if (currentPage == LogInPage)
    {
        drawLoginBox();
    }
    if (currentPage == RankingPage)
    {
        drawAllRankBoxes();
        InputFileRead(file_ranking_men);
    }
    if (currentPage == SchedulePage)
    {
        drawAllSchedulePage();
    }
    if (currentPage == LiveScorePage)
    {
        drawAllLiveScorePage();
    }
    if ()
    {
    }
}

// all Mouse event
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
    if (isButtonClicked(mx, my, menu.x, menu.y, menu.w, menu.h))
    {
        printf("menu bar was clicked\n");
        currentPage = HomePage;
    }
    if (isButtonClicked(mx, my, teams.x, teams.y, teams.w, teams.h))
    {
        printf("teams bar was clicked\n");
        currentPage = TeamsPage;
        InternationalPage = true;
    }
    if (isButtonClicked(mx, my, teams_type_2.x, teams_type_2.y, teams_type_2.w, teams_type_2.h))
    {
        currentPage = TeamsDomestic;
    }
    // if (isButtonClicked(mx, my, teams_type_1.x, teams_type_1.y, teams_type_1.w, teams_type_1.h))
    // {
    //     printf("international bar was clicked\n");
    //     currentPage = TeamsPage;
    //     InternationalPage = true;
    // }
    // if (isButtonClicked(mx, my, teams_type_2.x, teams_type_2.y, teams_type_2.w, teams_type_2.h))
    // {
    //     printf("domestic bar was clicked\n");
    //     currentPage = TeamsPage;
    //     InternationalPage = true;
    // }
    if (isButtonClicked(mx, my, login.x, login.y, login.w, login.h))
    {
        currentPage = LogInPage;
        printf("login bar was clicked\n");
    }
    if (isButtonClicked(mx, my, NEWS.x, NEWS.y, NEWS.w, NEWS.h))
    {
        currentPage = NewsPage;
        printf("news bar was clicked\n");
    }
    if (isButtonClicked(mx, my, Login.x, Login.y, Login.w, Login.h))
    {
        currentPage = RankingPage;
        printf("ranking bar was clicked\n");
    }
    if (isButtonClicked(mx, my, schedule.x, schedule.y, schedule.w, schedule.h))
    {
        currentPage = SchedulePage;
        printf("schedule bar was clicked\n");
    }
    if (isButtonClicked(mx, my, live_score.x, live_score.y, live_score.w, live_score.h))
    {
        currentPage = LiveScorePage;
        printf("live score bar was clicked\n");
    }
    if (isButtonClicked(mx, my, ID_1.x, ID_1.y, ID_1.w, ID_1.h))
    {
        printf("name bar was clicked\n");
        current_mouseState = id_1_input;
    }
    if (isButtonClicked(mx, my, ID_2.x, ID_2.y, ID_2.w, ID_2.h))
    {
        printf("email bar was clicked\n");
        current_mouseState = id_2_input;
    }
    if (!isButtonClicked(mx, my, ID_1.x, ID_1.y, ID_1.w, ID_1.h) && !isButtonClicked(mx, my, ID_2.x, ID_2.y, ID_2.w, ID_2.h))
    {
        // printf("outside box bar was clicked\n");
        current_mouseState = none;
    }
    if (isButtonClicked(mx, my, Enter.x, Enter.y, Enter.w, Enter.h))
    {
        printf("enter bar was clicked\n");
        current_mouseState = ProfilePage;
        save_account_info();
    }
    if (isButtonClicked(mx, my, Bangladesh.x, Bangladesh.y, Bangladesh.w, Bangladesh.h))
    {
        printf("Bangladesh bar was clicked\n");
        currentPage = BangladeshPage;
    }
    if (isButtonClicked(mx, my, ranking.x, ranking.y, ranking.w, ranking.h))
    {
        printf("ranking bar was clicked\n");
        currentPage = RankingPage;
    }
    // if(mx, my, past_mat.x, past_mat.y, past_mat.w, past_mat.h){
    //     currentPage=LiveScorePage;
    // }
}

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

        printf("Taking Name input \n");
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
}

void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_INSERT)
    {
        currentPage = HomePage;
    }
}
int main()
{
    srand((unsigned)time(&t1));
    iSetTimer(5000, updateMatchStatus);
    initHeader();
    initMatchBoxes();
    initTeams();
    initLogIn();
    initInTeams();
    initTeamsRank();
    // initRankBoxes();
    initScheduleBox();
    initLiveBoxes();
    // initLiveScoreBarText();
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "CRICINFO");
    return 0;
}
