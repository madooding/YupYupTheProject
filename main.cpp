#include <stdio.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define ScreenW 800
#define ScreenH 600
#define bigfontsize 52
#define fontsize 48
#define start_time 60
#define maxlife 3


int randint(int);
void perchar(char text[]);

int randint(int size){
    int num;    
    time_t t;
    srand((unsigned) time(&t));
    return rand() % size;
}


void textballoon(int a, char *text){
    char* correct[] = {"Good!", "Great!", "Excellent!", "Perfect!", "Like a boss!!"};
    char* incorrect[] = {"Try again.", "Wrong!", "T T", "O[]O", "Kak jung!"};
    if(a == 1)
         sprintf(text, "%s", correct[randint(5)]);
    else
        sprintf(text, "%s", incorrect[randint(5)]);
}


void perchar(char text[]){
    int i, ranNumber;
    char temp, tword[24];
    for(i = 0; i < strlen(text); i++){
        ranNumber = randint(strlen(text));
        temp = text[i];
        text[i] = text[ranNumber];
        text[ranNumber] = temp;
        }
    sprintf(tword, "");
    for(i = 0; i < strlen(text); i++)
        sprintf(tword, "%s%c ", tword, text[i]);
    strcpy(text, tword);
}

void print_credit(const ALLEGRO_FONT *font, const ALLEGRO_FONT *bigfont){
    int currentY = 115;
    al_draw_text(bigfont, al_map_rgb(255, 255, 255), ScreenW / 2, ScreenH / 2 - (bigfontsize/2), ALLEGRO_ALIGN_CENTRE, "Ans of Heart");
    al_flip_display();
    al_rest(2.0);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_rest(.5);
    al_draw_text(bigfont, al_map_rgb(255, 255, 255), ScreenW /2, currentY, ALLEGRO_ALIGN_CENTRE, "Members");
    currentY += (bigfontsize + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 180, currentY, ALLEGRO_ALIGN_LEFT, "Prachyawich Raomana       57070066");
    currentY += (fontsize + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 180, currentY, ALLEGRO_ALIGN_LEFT, "Pipat Saweay                    57070080");
    currentY += (fontsize + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 180, currentY, ALLEGRO_ALIGN_LEFT, "Phakphum Charatphan        57070088");
    currentY += (fontsize + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 180, currentY, ALLEGRO_ALIGN_LEFT, "Sirirach Junta                     57070112   ");
    currentY += (fontsize + 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 180, currentY, ALLEGRO_ALIGN_LEFT, "Harit Leelabunyong            57070138");
    al_flip_display();
    al_rest(2.0);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_rest(1);
}



void updatescore(char rname[][30], int *rscore){
    int i = 1, temp = 0;
    char ctemp[30];
    FILE *fscore;
    fscore = fopen("score.txt", "r+");
    while(!feof(fscore) && i <= 5){
        fscanf(fscore,"%s%d", rname[i - 1], &rscore[i - 1]);
        i++;
    }
    for(i = 0; i < 6; i++)
        for(int j = 0; j < 6; j++){
            if(rscore[i] > rscore[j]){
                temp = rscore[i];
                rscore[i] = rscore[j];
                rscore[j] = temp;
                sprintf(ctemp, "%s", rname[i]);
                strcpy(rname[i], rname[j]);
                strcpy(rname[j], ctemp);
            }
        }
    fclose(fscore);
    FILE *write;
    write = fopen("score.txt", "w+");
    for(i = 0; i < 5; i++){
          sprintf(ctemp, "%s %d\n", rname[i], rscore[i]);
          fputs(ctemp,write);
        }
    fclose(write);
}

int frameInc(int frame){
    if (frame == 60)
       frame = 1;
    else
       frame++;
    return frame;
}
float moveCheck(float y){
    if (y < -100)
       y = 700;
    return y;
}
int selectionState(int s){
    if (s == 0)
        s = 3;
    else if (s > 3)
        s = 1;
    return s;
}

void draw_hearts(ALLEGRO_BITMAP *hearts, float *heartsPos, float *heartsMoveSpeed){
    al_draw_bitmap_region(hearts, 0, 0, 200, 100, 30, heartsPos[0], NULL);
    al_draw_bitmap_region(hearts, 200, 0, 200, 100, 250, heartsPos[1], NULL);
    al_draw_bitmap_region(hearts, 400, 0, 200, 100, 435, heartsPos[2], NULL);
    al_draw_bitmap_region(hearts, 400, 0, 200, 100, 22, heartsPos[3], NULL);
    al_draw_bitmap_region(hearts, 0, 0, 200, 100, 625, heartsPos[4], NULL);
    al_draw_bitmap_region(hearts, 600, 0, 200, 100, 525, heartsPos[5], NULL);
    for(int i = 0; i < 6; i++){
        heartsPos[i] -= heartsMoveSpeed[i];
        heartsPos[i] = moveCheck(heartsPos[i]);
    }
}
void print_text(char *text,const ALLEGRO_FONT *font, float *arr){

    int space = 1;
    while(*text){
        if(*text == ' '){
            space++;
            if(space % 4 == 0)
                printf("\n");
            else
                printf(" ");
        }
        else
            printf("%c", *text);
        *text++;
    }
}

void getWord(char *word, int n){
    FILE *fword;
    char tword[24];
    sprintf(tword, "");  
    fword = fopen("word.txt", "r");
    for(int i = 1; i <= n; i++){
        fgets(word, 13, fword);
    }
    for(int i = 0; i < strlen(word)-1; i++)
        sprintf(tword, "%s%c", tword, word[i]);
    strcpy(word, tword);
    fclose(fword);
}
void getMeaning(char *meaning, int n){
    FILE *fmeaning;
    fmeaning = fopen("meaning.txt", "r");
    for(int i = 1; i <= n; i++)
        fgets(meaning, 120, fmeaning);
    fclose(fmeaning);     
}

int increaseHeart(int life){
    if(life < maxlife)
        life++;
    return life;
}

void inputStatusText(int key, char text[]){
    char tword[13];
    sprintf(tword, "");
    if(key == 5 && strlen(text) > 0){
        for(int i = 0; i < strlen(text)-1; i++)
            sprintf(tword, "%s%c", tword, text[i]);
        strcpy(text, tword);
    }else if(key > 5)
        sprintf(text, "%s%c", text, key+91);
}

int main(int argc, char **argv)
{   
    //game variables
    bool done = false, press = false;
    int game_state = -1, menuSelector = 1;
    float FPS = 60.0;
    int frame = 1, life = 3, wordcount = 1, etc = 0;
    char text[350];
    char tempText[350], word[26], meaning[120], permutedWord[26], tempText2[30];
    float heartsPos[] = {70,300,20,410,0,500};
    float heartsMoveSpeed[] = {0.8, 1.2, 1.5, 0.85, 1, 1.35};
    long int second = 3, start_delay = 0;
    enum key {NONE, ESC, UP, DOWN, ENTER, BACKSPACE, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    int jkey = NONE, temp = 999 , textCounter = 0, countdown = 30, score = 0;
    char rname[6][30];
    int rscore[6];
    int space = 1;
    int lineshift = 0;
    
    
    //Screen initialize
    ALLEGRO_DISPLAY *display = NULL; 
    if(!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
    } 
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE); 
    display = al_create_display(ScreenW, ScreenH);
    //al_set_window_position(display, 100, 200);
    al_set_window_title(display, "Ans of Heart : C project."); 

    //Keyboard initialize
    al_install_keyboard();
    
    // Image initialize
    al_init_image_addon();
    ALLEGRO_BITMAP *main_bg = al_load_bitmap("images/main_bg.png");
    ALLEGRO_BITMAP *logo = al_load_bitmap("images/logo.png");
    ALLEGRO_BITMAP *hearts = al_load_bitmap("images/hearts.png");
    ALLEGRO_BITMAP *guide1 = al_load_bitmap("images/guide1.png");
    ALLEGRO_BITMAP *howtoplay = al_load_bitmap("images/howtoplay.png");
    ALLEGRO_BITMAP *gleft = al_load_bitmap("images/gleft.png");
    ALLEGRO_BITMAP *gright = al_load_bitmap("images/gright.png");
    ALLEGRO_BITMAP *game_box = al_load_bitmap("images/game_box.png");
    ALLEGRO_BITMAP *c1 = al_load_bitmap("images/1.png");
    ALLEGRO_BITMAP *c2 = al_load_bitmap("images/2.png");
    ALLEGRO_BITMAP *c3 = al_load_bitmap("images/3.png");
    ALLEGRO_BITMAP *balloon = al_load_bitmap("images/balloon.png");
    ALLEGRO_BITMAP *enteryourname = al_load_bitmap("images/enteryourname.png");
    ALLEGRO_BITMAP *highscores = al_load_bitmap("images/highscores.png");

    
    // Timer initialize
    ALLEGRO_TIMER *timer = al_create_timer(1/FPS);
    
    //Event

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // Fonts initialize
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font = al_load_font("game_font.ttf", fontsize, NULL);
    ALLEGRO_FONT *bigfont = al_load_font("game_font.ttf", bigfontsize, NULL);


    
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    
    al_start_timer(timer);
    print_credit(font, bigfont);
    //Game loop
    
    while(!done){

        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {   
            //printf("%d", press);
            if(press != true){
            
            switch(events.keyboard.keycode)
            {                             
                case ALLEGRO_KEY_ESCAPE:
                     jkey = ESC;
                     break;
                case ALLEGRO_KEY_UP:
                     jkey = UP;
                     break;
                case ALLEGRO_KEY_DOWN:
                     jkey = DOWN;
                     break;
                case ALLEGRO_KEY_ENTER:
                     jkey = ENTER;
                     break;
                case ALLEGRO_KEY_A:
                    jkey = A;
                    break;
                case ALLEGRO_KEY_B:
                    jkey = B;
                    break;
                case ALLEGRO_KEY_C:
                    jkey = C;
                    break;
                case ALLEGRO_KEY_D:
                    jkey = D;
                    break;
                case ALLEGRO_KEY_E:
                    jkey = E;
                    break;
                case ALLEGRO_KEY_F:
                    jkey = F;
                    break;
                case ALLEGRO_KEY_G:
                    jkey = G;
                    break;
                case ALLEGRO_KEY_H:
                    jkey = H;
                    break;
                case ALLEGRO_KEY_I:
                    jkey = I;
                    break;
                case ALLEGRO_KEY_J:
                    jkey = J;
                    break;
                case ALLEGRO_KEY_K:
                    jkey = K;
                    break;
                case ALLEGRO_KEY_L:
                    jkey = L;
                    break;
                case ALLEGRO_KEY_M:
                    jkey = M;
                    break;
                case ALLEGRO_KEY_N:
                    jkey = N;
                    break;
                case ALLEGRO_KEY_O:
                    jkey = O;
                    break;
                case ALLEGRO_KEY_P:
                    jkey = P;
                    break;
                case ALLEGRO_KEY_Q:
                    jkey = Q;
                    break;
                case ALLEGRO_KEY_R:
                    jkey = R;
                    break;
                case ALLEGRO_KEY_S:
                    jkey = S;
                    break;
                case ALLEGRO_KEY_T:
                    jkey = T;
                    break;
                case ALLEGRO_KEY_U:
                    jkey = U;
                    break;
                case ALLEGRO_KEY_V:
                    jkey = V;
                    break;
                case ALLEGRO_KEY_W:
                    jkey = W;
                    break;
                case ALLEGRO_KEY_X:
                    jkey = X;
                    break;
                case ALLEGRO_KEY_Y:
                    jkey = Y;
                    break;
                case ALLEGRO_KEY_Z:
                    jkey = Z;
                    break;
                case ALLEGRO_KEY_BACKSPACE:
                    jkey = BACKSPACE;
                    break;
            }
            }
            press = true;
        }   
        if(events.type == ALLEGRO_EVENT_KEY_UP)
        {
                       
                       press = false;
                       //printf("%d", press);
                       //jkey = NONE;
                       
        }
       if(events.type == ALLEGRO_EVENT_TIMER){
           
           switch(game_state){
               case -1: if(start_delay < 360){
                        al_draw_text(font, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 - 24,ALLEGRO_ALIGN_CENTRE, "Loading...");
                        al_flip_display();
                        start_delay++;
                        }else {game_state = 0; start_delay = 0;}
                        break;
               case 0:  if(jkey == ENTER){ 
                        game_state = 1;
                        break;
                        }
               case 1:
                    //printf("game state : %d\n", game_state);
                    if(game_state == 1)
                    if(jkey == DOWN)
                        menuSelector = selectionState(menuSelector + 1);
                    else if(jkey == UP)
                        menuSelector = selectionState(menuSelector - 1);   
                    else if(jkey == ENTER)
                        switch(menuSelector){
                            case 1: game_state = 3;
                                    life = 3;
                                    score = 0;
                                    countdown = 3;
                                    frame = 0;
                                    wordcount = 1;
                                    sprintf(text, "");
                                    getWord(word, wordcount);
                                    getMeaning(meaning, wordcount);
                                    strcpy(permutedWord, word);
                                    perchar(permutedWord);
                                    break;
                            case 2: game_state = 2;
                                    start_delay = 0;
                                    break;
                            case 3: done = true;
                                    break;                  
                       }
                    
                    al_draw_bitmap(main_bg, 0, 0, NULL);
                    al_draw_bitmap(logo, 0, 0, NULL);
                    draw_hearts(hearts, heartsPos, heartsMoveSpeed);
                    al_draw_bitmap(guide1, 0, 170 - start_delay, NULL);
                    if(start_delay < 170) start_delay+=1;
                    if (game_state == 0){
                    if(frame > 30)
                        al_draw_text(font, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 + 200,ALLEGRO_ALIGN_CENTRE, "Press enter to continue");
                    }else{
                          al_draw_text(menuSelector == 1? bigfont:font, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 + 80,ALLEGRO_ALIGN_CENTRE, "Start game");
                          al_draw_text(menuSelector == 2? bigfont:font, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 + 115,ALLEGRO_ALIGN_CENTRE, "How to play");
                          al_draw_text(menuSelector == 3? bigfont:font, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 + 150,ALLEGRO_ALIGN_CENTRE, "Exit game");
                          
                          }
                    al_flip_display();
                    break;

                case 2: //How to play.
                        // COMMENT text in the white box can include a charactor just only "text star here, from here to here."
                        al_draw_bitmap(main_bg, 0, 0, NULL);
                        draw_hearts(hearts, heartsPos, heartsMoveSpeed);
                        al_draw_bitmap_region(howtoplay, 0, 0, 800, 100, 0, -100 + start_delay, NULL);
                        al_draw_bitmap_region(howtoplay, 0, 100, 800, 600, 0, 600 - ((start_delay / 2) * 10), NULL);
                        if(start_delay < 100){
                            start_delay += 5;
                        }else{
                            if(frame > 30)
                                al_draw_text(bigfont, al_map_rgb(0, 0, 0), ScreenW / 2, 510, ALLEGRO_ALIGN_CENTRE, "Press enter to continue");
                        space = 1;
                        lineshift = 0;
                        textCounter = 0;
                        sprintf(tempText, "");
                        sprintf(text, "At the beginning, you will be given 3 hearts and 60 seconds. The game will provide you a hint with an unordered word.  If your answer is wrong, a heart will be deducted.");
                        sprintf(text, "%s if your answer is correct, not only a heart, but also 2 seconds will be given. Either none of your heart is left or there is no more time, the game is over.", text);
                        while(textCounter <= strlen(text)){
                            if(text[textCounter] == ' ' || textCounter == strlen(text)){
                                if(space == 6 || textCounter == strlen(text)){
                                    al_draw_text(font, al_map_rgb(0, 0, 0), 225, 120 + lineshift, ALLEGRO_ALIGN_LEFT, tempText);
                                    lineshift += 30;
                                    space = 1;
                                    sprintf(tempText, "");
                                }else{
                                    sprintf(tempText, "%s ", tempText);
                                    space++;
                                }
                            }else{
                                sprintf(tempText, "%s%c", tempText, text[textCounter]);
                            }



                            /*
                            sprintf(tempText, "%s%c", tempText, text[textCounter]);
                            if(textCounter == strlen(text)-1)
                                al_draw_text(font, al_map_rgb(0, 0, 0), 215, 110 + lineshift, ALLEGRO_ALIGN_LEFT, tempText);
                            */
                            textCounter++;
                        }
                        
                        }
                        al_flip_display();
                        //Key code check
                        if(jkey == ENTER){
                            game_state = 1;
                            start_delay = 0;
                            break;
                            }
                        break;
                case 3: // countdown
                        if(frame % 60 == 0){
                            countdown -= 1;
                        }
                        al_draw_bitmap(main_bg, 0, 0, NULL);
                        switch(countdown){
                            case 3: al_draw_bitmap(c3, 0, 0, NULL);
                                    break;
                            case 2: al_draw_bitmap(c2, 0, 0, NULL);
                                    break;
                            case 1: al_draw_bitmap(c1, 0, 0, NULL);
                                    break;
                            case 0:
                                    game_state = 4;
                                    countdown = start_time;
                                    start_delay = 0;
                                    break;
                        }
                        al_flip_display();
                        break;
                case 4: // game_play
                        al_draw_bitmap(main_bg, 0, 0, NULL);
                        al_draw_bitmap(game_box, 0, 0, NULL);                        
                        sprintf(tempText, "Word : %d/100", wordcount);
                        al_draw_text(bigfont, al_map_rgb(255, 255, 255), 55, 20, ALLEGRO_ALIGN_LEFT, tempText);
                        sprintf(tempText, "Time left : %d", countdown);
                        if(countdown < 11){
                            if(frame % 10 == 0)
                                al_draw_text(bigfont, al_map_rgb(255, 0, 0), 265, 20, ALLEGRO_ALIGN_LEFT, tempText);
                        }else al_draw_text(bigfont, al_map_rgb(255, 255, 255), 265, 20, ALLEGRO_ALIGN_LEFT, tempText);
                        al_draw_bitmap_region(hearts, 600, 0, 200, 100, -30 + 420, -8, NULL);
                        sprintf(tempText, "x%d", life);
                        al_draw_text(bigfont, al_map_rgb(255, 255, 255), 93 + 420, 20, ALLEGRO_ALIGN_LEFT, tempText);
                        sprintf(tempText, "Score : %d", score);
                        al_draw_text(bigfont, al_map_rgb(255, 255, 255), 93 + 520, 20, ALLEGRO_ALIGN_LEFT, tempText);

                        space = 1;
                        lineshift = 0;
                        textCounter = 0;
                        sprintf(tempText, "");
                        //sprintf(meaning, "%s",meaning);
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), 480 , 105, ALLEGRO_ALIGN_LEFT, "Hint 1 :");
                        while(textCounter <= strlen(meaning)-1){
                            if(meaning[textCounter] == ' ' || textCounter == strlen(meaning)-1){
                                if(space == 3 || textCounter == strlen(meaning)-1){
                                    al_draw_text(font, al_map_rgb(0, 0, 0), 480, 140 + lineshift, ALLEGRO_ALIGN_LEFT, tempText);
                                    lineshift += 30;
                                    space = 1;
                                    sprintf(tempText, "");
                                }else{
                                    sprintf(tempText, "%s ", tempText);
                                    space++;
                                }
                            }else{
                                sprintf(tempText, "%s%c", tempText, meaning[textCounter]);
                            }
                            textCounter++;
                        }
                        
                        lineshift += 30;
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), 480 , 140 + lineshift, ALLEGRO_ALIGN_LEFT, "Hint 2 :");
                        lineshift += 35;
                        al_draw_text(font, al_map_rgb(0, 0, 0), 480, 140 + lineshift, ALLEGRO_ALIGN_LEFT, permutedWord);
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), 215, 500, ALLEGRO_ALIGN_CENTRE, text);
                        
                        if(countdown <= 0 || life == 0 || wordcount > 100){
                            wordcount = 1;
                            start_delay = 0;
                            game_state = 5;
                            sprintf(text, "");
                        }
                        if(jkey > 5 && jkey < 32 && strlen(text) < 15){
                            inputStatusText(jkey, text);
                            //printf("%d %s\n", strlen(text), text);
                        }else if(jkey == ENTER && strlen(text) != 0){
                            if(strcmp(text, word) == 0){
                                countdown += 2;
                                life = increaseHeart(life);
                                wordcount += 1;
                                sprintf(text, "");
                                getWord(word, wordcount);
                                getMeaning(meaning, wordcount);
                                strcpy(permutedWord, word);
                                perchar(permutedWord);
                                start_delay = 2;
                                score += 10;
                                etc = 1;
                                textballoon(1, tempText2);
                            }else{
                                life -= 1;
                                start_delay = 2;
                                etc = -1;
                                textballoon(0, tempText2);
                                sprintf(text, "");
                            }
                        }else if(jkey == BACKSPACE)
                            inputStatusText(jkey, text);
                        if(frame % 60 == 0){
                            countdown -= 1;
                        }
                        
                        if(start_delay > 0){
                            
                            if(frame % 60 == 0) start_delay--;
                            if((frame / 10) % 2 == 0 && frame != 60)
                                al_draw_bitmap(gright, 75, 142, NULL);
                            else
                                al_draw_bitmap(gleft, 75, 142, NULL);
                            al_draw_bitmap(balloon, 0, 0, NULL);
                            al_draw_text(bigfont, al_map_rgb(0, 0, 0), 325, 200, ALLEGRO_ALIGN_CENTRE, tempText2);
                        }else {
                            al_draw_bitmap(gleft, 75, 142, NULL);
                        }

                        al_flip_display();
                        break;
                case 5: // Game overstate
                        if(start_delay < 360 && jkey != ENTER){
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_text(bigfont, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2 - 35,ALLEGRO_ALIGN_CENTRE, "Game over");
                        sprintf(tempText, "Your score : %d", score);
                        al_draw_text(bigfont, al_map_rgb(255,255,255), ScreenW / 2, ScreenH / 2,ALLEGRO_ALIGN_CENTRE, tempText);
                        al_flip_display();
                        start_delay++;
                        }else {game_state = 6; 
                            start_delay = 0;}
                        break;
                case 6: // Enter your name
                        al_draw_bitmap(main_bg, 0, 0, NULL);
                        al_draw_bitmap(enteryourname, 0, 180, NULL);
                        al_draw_bitmap_region(game_box, 0,450, 410, 600, 185, 250, NULL);
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), ScreenW / 2, 300, ALLEGRO_ALIGN_CENTRE, text);
                        al_flip_display();
                        if(jkey == ENTER && strlen(text) > 0){
                            sprintf(rname[5], "%s", text);
                            rscore[5] = score;
                            updatescore(rname, rscore);                             
                            game_state = 7;
                        }
                        else if(jkey > 5 && jkey < 32 && strlen(text) < 10)
                            inputStatusText(jkey, text);
                        else if(jkey == 5)
                            inputStatusText(jkey, text);
                        break;
                case 7: //High scores showed
                        al_draw_bitmap(main_bg, 0, 0, NULL);
                        al_draw_bitmap(highscores, 0, 0, NULL);
                        al_draw_bitmap_region(howtoplay, 0, 100, 800, 600, 0, 100, NULL);
                        lineshift = 40;
                        sprintf(tempText, "NAME", rname[wordcount]);
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), 225, 120, ALLEGRO_ALIGN_LEFT, tempText);
                        sprintf(tempText, "SCORE", rname[wordcount]);
                        al_draw_text(bigfont, al_map_rgb(0, 0, 0), 575, 120, ALLEGRO_ALIGN_RIGHT, tempText);
                        for(wordcount = 0; wordcount < 5; wordcount++){
                            sprintf(tempText, "%s", rname[wordcount]);
                            al_draw_text(font, al_map_rgb(0,0,0), 225, 120 + lineshift, ALLEGRO_ALIGN_LEFT, tempText);
                            sprintf(tempText, "%d", rscore[wordcount]);
                            al_draw_text(font, al_map_rgb(0, 0, 0), 575, 120 + lineshift, ALLEGRO_ALIGN_RIGHT, tempText);
                            lineshift += 33;
                        }
                        if(frame > 30)
                                al_draw_text(bigfont, al_map_rgb(0, 0, 0), ScreenW / 2, 510, ALLEGRO_ALIGN_CENTRE, "Press enter to continue");
                        al_flip_display();
                        if(jkey == ENTER)
                            game_state = 0;
                }   
                //temp = jkey;
                frame = frameInc(frame);
                jkey = NONE;
        }else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    done = true;

        
        
    }
    al_destroy_bitmap(main_bg);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(hearts);
    al_destroy_bitmap(guide1);
    al_destroy_bitmap(gleft);
    al_destroy_bitmap(gright);
    al_destroy_bitmap(game_box);
    al_destroy_bitmap(howtoplay);
    al_destroy_bitmap(c1);
    al_destroy_bitmap(c2);
    al_destroy_bitmap(c3);
    al_destroy_bitmap(balloon);
    al_destroy_bitmap(enteryourname);
    al_destroy_bitmap(highscores);
    al_destroy_font(font);
    al_destroy_font(bigfont);
    al_destroy_display(display);
    return 0;
}
