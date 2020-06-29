#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

using namespace std;

unsigned int rings = 0;
int lenOfBlock;
bool isGameOver = 0;
char escape[4] = "esc";
char noName[7] = "noName";
char help[5] = "help";

class ringDefault {
public:
    int numPos;
    int tower;
    int Ypos;
    int len;
};


void ringDraw (ringDefault RING){
    //cout << RING.len << " / " << RING.Ypos << endl;
    int left = (lenOfBlock - RING.len) / 2;
    int right = lenOfBlock - ((lenOfBlock - RING.len) / 2);
    if (RING.len == lenOfBlock){
        for (int p = 0; p < lenOfBlock; p++){
            cout << "#";
        }
    } else {
        for (int p = 0; p < lenOfBlock; p++){
            if ((p < left) || (p >= right)){
                cout << " ";
            } else { cout << "#";}
        }
    }
}

void easyDraw(){
    for (int p = 0; p < lenOfBlock; p++){
        if (p == lenOfBlock / 2){
            cout << "|";
        } else {
            cout << ".";
        }
    }
}

int check(ringDefault RING, int Hei, int Tow){
    if ((RING.tower == Tow) && (RING.Ypos == Hei)){
        return 1;
    } else {
        return 0;
    }

}

bool checkWinner(ringDefault arr[]){
    unsigned int flag = 0;
    for (unsigned int i = 0; i < rings; i++){
        if (arr[i].tower == 2){
            flag += 1;
        }
    }
    if (flag == rings){
        return 1;
    } else {
        return 0;
    }
}

void mainDraw(ringDefault ringArr[]){
    int flag = -1;
    for (int i = 1; i < 4; i++){
        for (int j = 0; j < lenOfBlock; j++){
            if (j == lenOfBlock / 2){
                cout << i;
            } else {
                cout << " ";
            }
        }
        cout << " ";
    }
    cout << endl;
    for (int i = rings; i >= 0; i--){ // HEIGHT
            for (int j = 0; j < 3; j++){ // TOWER
                for (unsigned int k = 0; k < rings; k++){
                    if (check(ringArr[k], i, j) == 1){ // i - HEIGHT / j - TOWER
                        ringDraw(ringArr[k]);
                        flag = 1;
                    }
                }
            if (flag == -1){
                easyDraw();
                }
            flag = -1;
            cout << " ";
            }
            cout << endl;
        }
}

void creation(ringDefault ringArr[]){
    for (unsigned int i = 1; i < rings + 1; i++){
        ringArr[i-1].numPos = i;
        ringArr[i-1].tower = 0; // STARTING POSITION
        ringArr[i-1].Ypos = rings-i;
        ringArr[i-1].len = (2*i - 1);
    }
}

bool mistake(char param[80], int numbOfError){
    if (((atoi(param) == 0) || (atoi(param) > 3) || (atoi(param) < 1)) && (numbOfError == 1)){
        cout << "It's mistake! Enter number from 1 to 3, please!" << endl;
        return 0;
    }
    if (numbOfError == 2){
        cout << "It's mistake! You can't put bigger ring on smaller!" << endl << "Move to:" << endl;
        return 0;
    }
    if (numbOfError == 3){
        cout << "You can't move empty place!" << endl << "Enter where move from:" << endl;;
        return 0;
    }
    if ((numbOfError == 4) && (strcmpi(param, help) != 0) && ((atoi(param) == 0) || (atoi(param) < 0))){
        cout << "Enter digit or 'help'!" << endl << "Enter amount of rings:" << endl;
        return 0;
    }
    return 1;
}

bool checkUnder(ringDefault ringArr[], int len, int choice2){
    int Y = -1;
    for (unsigned int i = 0; i < rings; i++){
        if ((ringArr[i].tower == (choice2-1)) && (ringArr[i].Ypos > Y)){
            Y = ringArr[i].Ypos;
            if (len <= ringArr[i].len){
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

void isItEmpty(int *p, ringDefault ringArr[]){
    int anchor = 0;
    for (unsigned int u = 0; u < rings; u++){
        if (ringArr[u].tower == ((*p) - 1)){
            anchor = 1;
        }
    }
    if (anchor == 0){
        mistake(noName, 3);
        (*p) = 0;
    }
}

void timeToMove(ringDefault ringArr[]){
    char choice[80];
    int choice1 = 0;
    int choice2 = 0;
    cout << "Enter where move from:";
    while(choice1 == 0){
        cin >> choice;
        if (strcmpi(choice, escape) == 0){ // TYPE "esc" TO LEAVE GAME
            isGameOver = 1;
            return;
        }
        if (mistake(choice, 1) == 0){
            choice1 = 0;
        } else {
            choice1 = atoi(choice);
        }
        isItEmpty(&choice1, ringArr);
    }
    int whatRing;
    int tow = -1;
    int yPos = -1;
    for (unsigned int u = 0; u < rings; u++){
            if (ringArr[u].tower == (choice1 - 1)){
                    tow = ringArr[u].tower;
                if (ringArr[u].Ypos > yPos){
                    yPos = ringArr[u].Ypos;
                    whatRing = u;
                }
            }
        }
    cout << "Move to:";
    while(choice2 == 0){
        cin >> choice;
        if (strcmpi(choice, escape) == 0){
            isGameOver = 1;
            return;
        }
        if (mistake(choice, 1) == 0){
            choice2 = 0;
        } else {
            choice2 = atoi(choice);
        }
        if (checkUnder(ringArr, ringArr[whatRing].len ,choice2) == 0){
            mistake(noName, 2);
            choice2 = 0;
        }
    }
    for (unsigned int u = 0; u < rings; u++){
        if ((ringArr[u].tower == tow) && (ringArr[u].Ypos == yPos)){
            //cout << u << endl;
                ringArr[u].tower = (choice2 - 1);
                ringArr[u].Ypos = 0;
                for (unsigned int k = 0; k < rings; k++){
                    if ((ringArr[k].tower == ringArr[u].tower) && (u != k)){
                        ringArr[u].Ypos += 1;
                    }
                }
        }
    }
}

void helpFunc(){
    cout << "1. You must enter number of circles" << endl;
    cout << "2. You must enter only digits, not words" << endl;
    cout << "3. You can move circles with entering digits from 1 to 3" << endl;
    cout << "4. You win, when you move your last circle to right side" << endl;
    cout << "print 'esc' to close game" << endl;
    cout << "Enter amount of rings:" << endl;
}

int main()
{
    char ans[80];
    int turns = 0;
    cout << "If you need information print 'help'" << endl;
    cout << "Enter amount of rings:" << endl;
    while(rings == 0){
        cin >> ans;
        if (strcmpi(ans, escape) == 0){
            isGameOver = 1;
        }
        if (mistake(ans, 4) == 0){
            rings = 0;
        } else {
            rings = atoi(ans);
        }
        if (strcmpi(ans, help) == 0){helpFunc(); rings = 0;}
    }
    ringDefault ringArr[rings];
    creation(ringArr);
    lenOfBlock = 2 * (sizeof(ringArr)/sizeof(*ringArr)) - 1;
    system("cls");
    while (!isGameOver){
        cout << "Number of turns: " << turns << endl;
        mainDraw(ringArr);

        timeToMove(ringArr);

        system("cls");
        turns += 1;
        if (checkWinner(ringArr) == 1){
            isGameOver = 1;
            cout << "You Won! Turns: " << turns << endl;
        }
    }
    return 0;
}
