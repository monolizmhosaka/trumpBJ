#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct tr {
    int suit;
    int value;
    int disp;
    char mark;
}card[52], deal[21], play[21], tmp;

const char* ps = "プレイヤー";
const char* ds = "ディーラー";

void disp(int a, struct tr b[21]) {

    for (int i = 0; i < a; i++) printf("%c%d　", b[i].mark, b[i].disp);
    printf("\n");
}

void num(int* n) {

    if (*n > 10) *n = 10;
    if (*n == 1) *n = 11;

    return;

}

int hantei(int p, int d) {

    int win = 0;

    if ((p > d && p < 22) || (d > 21 && p < 22)) {
        printf("%sの勝ちです\n", ps);
        win = 2;
    }
    if ((d > p && d < 22) || (p > 21)) {
        printf("%sの勝ちです\n", ds);
        win = 1;
    }
    if (d == p || (d > 21 && p > 21)) {
        printf("引き分けです\n");
        win = 3;
    }
    return win;
}


int main(void) {

    srand(time(NULL));

    int s1 = 0, s2 = 0;
    int cont = 1;

    do {

        int deal_s = 0;
        int play_s = 0;
        int c_d = 0;
        int c_p = 0;
        int c_t = 0;
        int playflag = 1;
        int dealflag = 1;
        int win = 0;
        int p_key = 0;

        for (int i = 0; i <= 12; i++) {
            card[i].suit = 1;
            card[i].value = i + 1;
            card[i].disp = i + 1;
            card[i].mark = 'S';
        }

        for (int i = 13; i <= 25; i++) {
            card[i].suit = 2;
            card[i].value = i - 12;
            card[i].disp = i - 12;
            card[i].mark = 'H';
        }

        for (int i = 26; i <= 38; i++) {
            card[i].suit = 3;
            card[i].value = i - 25;
            card[i].disp = i - 25;
            card[i].mark = 'D';
        }

        for (int i = 39; i <= 51; i++) {
            card[i].suit = 4;
            card[i].value = i - 38;
            card[i].disp = i - 38;
            card[i].mark = 'C';
        }

        for (int i = 1; i <= 100; i++) {

            s1 = rand() % 52;
            s2 = rand() % 52;

            tmp = card[s1];
            card[s1] = card[s2];
            card[s2] = tmp;

        }

        printf("カードを配ります\n");

        for (int i = 0; i < 2; i++) {

            play[c_p] = card[c_t++];
            num(&play[c_p].value);
            play_s = play_s + play[c_p++].value;
            deal[c_d] = card[c_t++];
            num(&deal[c_d].value);
            deal_s = deal_s + deal[c_d++].value;
        }

        printf("%sの手札\n", ps);
        disp(c_p, play);

        printf("%sの手札\n", ds);
        disp(c_d, deal);

        while (1) {

            if (playflag) {
                printf("%sのターン\n", ps);
                printf("　もう1枚カードを引きますか？　Yes=1, No=0\n");
                //scanf("%d", &p_key);
                cin >> p_key;

                if (!p_key) {
                    playflag = 0;
                }
                else
                {
                    play[c_p] = card[c_t++];
                    num(&play[c_p].value);
                    play_s = play_s + play[c_p++].value;

                    if (play_s > 21) {
                        for (int i = 0; i < c_p; i++) {
                            if (play[i].value == 11) {
                                play[i].value = 1;
                                play_s = play_s - 10;
                            }
                        }
                    }

                    printf("%sはカードを引きました\n", ps);
                    printf("%sの手札\n", ps);
                    disp(c_p, play);
                }

                if (play_s > 21) {
                    playflag = 0;
                    dealflag = 0;
                }
            }

            if (playflag == 0 && dealflag == 0) win = hantei(play_s, deal_s);
            if (win) break;

            if (dealflag) {
                printf("%sのターン\n", ds);
                if (deal_s >= 17) dealflag = 0;
                if (deal_s < 17) {
                    deal[c_d] = card[c_t++];
                    num(&deal[c_d].value);
                    deal_s = deal_s + deal[c_d++].value;

                    if (deal_s > 21) {
                        for (int i = 0; i < c_d; i++) {
                            if (deal[i].value == 11) {
                                deal[i].value = 1;
                                deal_s = deal_s - 10;
                            }
                        }
                    }

                    printf("%sはカードを引きました\n", ds);
                    printf("%sの手札\n", ds);
                    disp(c_d, deal);
                }

                if (playflag == 0 && dealflag == 0) win = hantei(play_s, deal_s);
                if (win) break;
            }
        }

        printf("　もう1回やりますか？　Yes=1, No=0\n");
        //scanf("%d", &p_key);
        cin >> p_key;
        if (!p_key)cont = 0;

    } while (cont);

}