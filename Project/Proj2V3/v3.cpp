/******************************************************************************
* Name: Ashton Cramer
* Date: 5/27/2025
* Purpose: Black Jack. Project 2, Version 3. Basic card picking program, now
*          with a dealer and extra players.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#include "card.h"

void prntTtl(); //prints the title
string plyrNme(); //ask for the player's name
int plyrNum(); //ask how many players there are.
void binWrte(int); //write a series of numbers to the cards.bin
void binRead(char *, int); //read contents from cards.bin into a dynamic array
void shuffle(char *, int); //shuffle the dynamic array
void slctCrd(int, int&, int, char *); //select a number from the dynamic array
void results(bool &, bool &, int&, int&, int); //decides the winner

string DlrCard::dlrName = "Dealer"; 
int DlrCard::nameNum = 0;

int main(){
    srand(time(0));
    
    string player; //player's name
    char *ptrArr = nullptr; //ptr to make a dynamic array
    bool won; //flag for win case
    int counter, dlrCntr, stayCtr; //counters
    int chosen, choose; //decides which card is chosen
    int size = 53, hndSize = 2; //size for dynamic arrays and object array
    char ask; //ask if the player wants to play again
    int plyrSze; //amount of extra players.
    ExtrPyr *exPlArr; //to make a dynamic array based on the amount the player gives

    counter = 0; //your points counter
    dlrCntr = 0; //points counter for the dealer
    stayCtr = 0; //count how many times player's stayed.
    ask = 'y'; //set ask to y to enter the while loop
    ptrArr = new char[size]; 

    prntTtl();

    player = plyrNme();

    plyrSze = plyrNum();

    DlrCard::pickNme(); //pick the name of the dealer

    binWrte(size);
    
    binRead(ptrArr, size); 

    DlrCard dlrArr[hndSize]; //dealer array
    Card cardArr[hndSize]; //player array
    exPlArr = new ExtrPyr[plyrSze]; //extra player array

    for(int i=0; i < hndSize; i++){
        shuffle(ptrArr, size);
        slctCrd(choose, chosen, size, ptrArr);
        cardArr[i].setCard(chosen);
        while(cardArr[i] == cardArr[i - 1]){ //reshuffle if the 2 cards are the same
            shuffle(ptrArr, size);
            slctCrd(choose, chosen, size, ptrArr);
        }
        cout << player << " pulled: " << cardArr[i] << endl;
    }

    cout << endl;
    for(int i=0; i < hndSize; i++){
        shuffle(ptrArr, size);
        slctCrd(choose, chosen, size, ptrArr);
        dlrArr[i].setCard(chosen);
        while(dlrArr[i] == dlrArr[i - 1]){ //reshuffle if the 2 cards are the same
            shuffle(ptrArr, size);
            slctCrd(choose, chosen, size, ptrArr);
        }

        if(i == 1){ //hide second card
            cout << dlrArr[i].getDlr() << " pulled: ?????" << endl;
        }
        else{
            cout << dlrArr[i].getDlr() << " pulled: " << dlrArr[i] << endl;
        }
    }

    
    for(int i=0; i < plyrSze; i++){
        cout << endl;
        exPlArr[i].pickNme();
        for(int j=0; j < hndSize; j++){
            shuffle(ptrArr, size);
            slctCrd(choose, chosen, size, ptrArr);
            exPlArr[i].setCard(chosen);
            exPlArr[i].setCrdAr(j);
            while(exPlArr[i].getCrdAr(j) == exPlArr[i].getCrdAr(j - 1)){ //reshuffle if the 2 cards are the same
                shuffle(ptrArr, size);
                slctCrd(choose, chosen, size, ptrArr);
            }

            if(j == 1){ //hide second card
                cout << exPlArr[i].getPlyr() << " pulled: ?????" << endl;
            }
            else{
                exPlArr[i].setFace(j);
                exPlArr[i].setSuit(j);
                cout << exPlArr[i].getPlyr() << " pulled: " << exPlArr[i].getName() << endl;
            }
        }
    }

    //clean up
    delete [] exPlArr;
    delete [] ptrArr;
    return 0;
}

void prntTtl(){
    cout << "**************************************************************" << endl;
    cout << "* Black Jack                                                 *" << endl;
    cout << "**************************************************************" << endl;
}

string plyrNme(){
    string str;

    cout << "What is your name?: ";
    cin >> str;

    return str;
}

int plyrNum(){
    int n;
    cout << "How many other players are there (0 - 2)?: ";
    cin >> n;
    while(n < 0 || n > 2){
        cout << "Invalid: ";
        cin >> n;
    }
    return n; 
}

/*
void results(bool &won, bool &lost, int &counter, int &dlrCntr, int stayCtr){
            cout << "Your points: " << counter << endl;
            cout << "Dealer's points: " << dlrCntr << endl;
            if(counter > 21){
                cout << "!!You go over 21 points, you lost!!" << endl;
                lost = true;
                counter = 0;
                dlrCntr = 0;
            }
            else if(dlrCntr > 21){
                cout << "!!Dealer goes over 21 points, you win!!" << endl;
                won = true;
                counter = 0;
                dlrCntr = 0;
            }
            else if(stayCtr >= 2){
                if(dlrCntr > counter){
                    cout << "!!Both stayed, dealer has more points, you lose!!" << endl;
                    lost = true;
                    counter = 0;
                    dlrCntr = 0;
                }
                else if(dlrCntr < counter){
                    cout << "!!Both stayed, you have more points, you win!!" << endl;
                    won = true;
                    counter = 0;
                    dlrCntr = 0;
                }
            }
}*/

void binWrte(int size){
    char *arr = new char[size]; //dynamic char array
    fstream toFile;
    
    for(int i=0; i < size; i++){
        arr[i] = i + 1;
    }

    cout << "Deck size: " << strlen(arr) - 1 << endl << endl; //string object
    
    toFile.open("cards.bin", ios::out | ios::binary);
    
    toFile.write(reinterpret_cast<char*>(arr), size * sizeof(char));

    //clean up
    delete [] arr;
    toFile.close();
}

void binRead(char *ptrArr, int size){
    fstream fromFile;

    //Read process
    fromFile.open("cards.bin", ios::in | ios::binary);
    
    fromFile.seekg(0, ios::beg); 
    
    for(int i=0; i < size; i++){
        fromFile.seekg(i, ios::beg);
        ptrArr[i] = fromFile.tellg(); 
    }

    //close file
    fromFile.close();
}

void shuffle(char *ptrArr, int size){
    for(int i = 0; i < size; i++){
        swap(ptrArr[i], ptrArr[rand() % 52]); 
    }
}

void slctCrd(int choose, int &chosen, int size, char *ptrArr){
    choose = rand() % (size - 1) + 1;
    for(int i=0; i < size; i++){
        if(static_cast<int>(ptrArr[i]) == choose){
            chosen = static_cast<int>(ptrArr[i]);
        }
    }
}

void Card::setFace(){
    switch(card){
                //Clubs
                case CA: 
                    name = "Ace ";
                    break;
                case C2: 
                    name = "Two ";
                    break;
                case C3: 
                    name = "Three ";
                    break;  
                case C4: 
                    name = "Four ";
                    break;  
                case C5: 
                    name = "Five ";
                    break;  
                case C6: 
                    name = "Six ";
                    break;  
                case C7: 
                    name = "Seven ";
                    break;
                case C8: 
                    name = "Eight ";
                    break;
                case C9: 
                    name = "Nine ";
                    break;
                case C10: 
                    name = "Ten ";
                    break;
                case CJ: 
                    name = "Jack ";
                    break;   
                case CQ:
                    name = "Queen ";
                    break;
                case CK:
                    name = "King ";
                    break;
                
                //Diamonds
                case DA: 
                    name = "Ace ";
                    break;
                case D2: 
                    name = "Two ";
                    break;
                case D3: 
                    name = "Three ";
                    break;  
                case D4: 
                    name = "Four ";
                    break;  
                case D5: 
                    name = "Five ";
                    break;  
                case D6: 
                    name = "Six ";
                    break;  
                case D7: 
                    name = "Seven ";
                    break;
                case D8: 
                    name = "Eight ";
                    break;
                case D9: 
                    name = "Nine ";
                    break;
                case D10: 
                    name = "Ten ";
                    break;
                case DJ: 
                    name = "Jack ";
                    break;   
                case DQ:
                    name = "Queen ";
                    break;
                case DK:
                    name = "King ";
                    break;
                
                //Hearts
                case HA: 
                    name = "Ace ";
                    break;
                case H2: 
                    name = "Two ";
                    break;
                case H3: 
                    name = "Three ";
                    break;  
                case H4: 
                    name = "Four ";
                    break;  
                case H5: 
                    name = "Five ";
                    break;  
                case H6: 
                    name = "Six ";
                    break;  
                case H7: 
                    name = "Seven ";
                    break;
                case H8: 
                    name = "Eight ";
                    break;
                case H9: 
                    name = "Nine ";
                    break;
                case H10: 
                    name = "Ten ";
                    break;
                case HJ: 
                    name = "Jack ";
                    break;   
                case HQ:
                    name = "Queen ";
                    break;
                case HK:
                    name = "King ";
                    break;

                //Spades
                case SA: 
                    name = "Ace ";
                    break;
                case S2: 
                    name = "Two ";
                    break;
                case S3: 
                    name = "Three ";
                    break;  
                case S4: 
                    name = "Four ";
                    break;  
                case S5: 
                    name = "Five ";
                    break;  
                case S6: 
                    name = "Six ";
                    break;  
                case S7: 
                    name = "Seven ";
                    break;
                case S8: 
                    name = "Eight ";
                    break;
                case S9: 
                    name = "Nine ";
                    break;
                case S10: 
                    name = "Ten ";
                    break;
                case SJ: 
                    name = "Jack ";
                    break;   
                case SQ:
                    name = "Queen ";
                    break;
                case SK:
                    name = "King ";
                    break;
            }
}

void Card::setSuit(){
            if(card <= CK){
                name += "of Clubs";
            }
            else if(card > CK && card <= DK){
                name += "of Diamonds";
            }
            else if(card > DK && card <= HK){
                name += "of Hearts";
            }
            else if(card > HK && card <= SK){
                name += "of Spades";
            }
}

void DlrCard::pickNme(){
    nameNum = rand() % 15;
    switch(nameNum){
        case 0:
            dlrName = "Jeffrey";
            break;
        case 1:
            dlrName = "Carlos";
            break;
        case 2:
            dlrName = "George";
            break;
        case 3:
            dlrName = "Elon";
            break;
        case 4:
            dlrName = "Jones";
            break;
        case 5:
            dlrName = "Micheal";
            break;
        case 6:
            dlrName = "Pablo";
            break;
        case 7:
            dlrName = "Steve";
            break;
        case 8:
            dlrName = "James";
            break;
        case 9:
            dlrName = "Abraham";
            break;
        case 10:
            dlrName = "No-Name";
            break;
        case 11:
            dlrName = "William";
            break;
        case 12:
            dlrName = "Dan";
            break;
        case 13:
            dlrName = "Anton";
            break;
        case 14:
            dlrName = "Case";
            break;
        case 15:
            dlrName = "Jack";
            break;
    }
    cout << "Dealer: " << getDlr() << endl;
}

void ExtrPyr::pickNme(){
    nameNum = rand() % 15;
    switch(nameNum){
        case 0:
            extPNme = "Jeffrey";
            break;
        case 1:
            extPNme = "Carlos";
            break;
        case 2:
            extPNme = "George";
            break;
        case 3:
            extPNme = "Elon";
            break;
        case 4:
            extPNme = "Jones";
            break;
        case 5:
            extPNme = "Micheal";
            break;
        case 6:
            extPNme = "Pablo";
            break;
        case 7:
            extPNme = "Steve";
            break;
        case 8:
            extPNme = "James";
            break;
        case 9:
            extPNme = "Abraham";
            break;
        case 10:
            extPNme = "No-Name";
            break;
        case 11:
            extPNme = "William";
            break;
        case 12:
            extPNme = "Dan";
            break;
        case 13:
            extPNme = "Anton";
            break;
        case 14:
            extPNme = "Case";
            break;
        case 15:
            extPNme = "Jack";
            break;
    }
    cout << "Playing against: " << getPlyr() << endl;
}

void ExtrPyr::setFace(int index){
    switch(crdAr[index]){
                //Clubs
                case CA: 
                    name = "Ace ";
                    break;
                case C2: 
                    name = "Two ";
                    break;
                case C3: 
                    name = "Three ";
                    break;  
                case C4: 
                    name = "Four ";
                    break;  
                case C5: 
                    name = "Five ";
                    break;  
                case C6: 
                    name = "Six ";
                    break;  
                case C7: 
                    name = "Seven ";
                    break;
                case C8: 
                    name = "Eight ";
                    break;
                case C9: 
                    name = "Nine ";
                    break;
                case C10: 
                    name = "Ten ";
                    break;
                case CJ: 
                    name = "Jack ";
                    break;   
                case CQ:
                    name = "Queen ";
                    break;
                case CK:
                    name = "King ";
                    break;
                
                //Diamonds
                case DA: 
                    name = "Ace ";
                    break;
                case D2: 
                    name = "Two ";
                    break;
                case D3: 
                    name = "Three ";
                    break;  
                case D4: 
                    name = "Four ";
                    break;  
                case D5: 
                    name = "Five ";
                    break;  
                case D6: 
                    name = "Six ";
                    break;  
                case D7: 
                    name = "Seven ";
                    break;
                case D8: 
                    name = "Eight ";
                    break;
                case D9: 
                    name = "Nine ";
                    break;
                case D10: 
                    name = "Ten ";
                    break;
                case DJ: 
                    name = "Jack ";
                    break;   
                case DQ:
                    name = "Queen ";
                    break;
                case DK:
                    name = "King ";
                    break;
                
                //Hearts
                case HA: 
                    name = "Ace ";
                    break;
                case H2: 
                    name = "Two ";
                    break;
                case H3: 
                    name = "Three ";
                    break;  
                case H4: 
                    name = "Four ";
                    break;  
                case H5: 
                    name = "Five ";
                    break;  
                case H6: 
                    name = "Six ";
                    break;  
                case H7: 
                    name = "Seven ";
                    break;
                case H8: 
                    name = "Eight ";
                    break;
                case H9: 
                    name = "Nine ";
                    break;
                case H10: 
                    name = "Ten ";
                    break;
                case HJ: 
                    name = "Jack ";
                    break;   
                case HQ:
                    name = "Queen ";
                    break;
                case HK:
                    name = "King ";
                    break;

                //Spades
                case SA: 
                    name = "Ace ";
                    break;
                case S2: 
                    name = "Two ";
                    break;
                case S3: 
                    name = "Three ";
                    break;  
                case S4: 
                    name = "Four ";
                    break;  
                case S5: 
                    name = "Five ";
                    break;  
                case S6: 
                    name = "Six ";
                    break;  
                case S7: 
                    name = "Seven ";
                    break;
                case S8: 
                    name = "Eight ";
                    break;
                case S9: 
                    name = "Nine ";
                    break;
                case S10: 
                    name = "Ten ";
                    break;
                case SJ: 
                    name = "Jack ";
                    break;   
                case SQ:
                    name = "Queen ";
                    break;
                case SK:
                    name = "King ";
                    break;
            }
}

void ExtrPyr::setSuit(int index){
            if(crdAr[index] <= CK){
                name += "of Clubs";
            }
            else if(crdAr[index] > CK && crdAr[index] <= DK){
                name += "of Diamonds";
            }
            else if(crdAr[index] > DK && crdAr[index] <= HK){
                name += "of Hearts";
            }
            else if(crdAr[index] > HK && crdAr[index] <= SK){
                name += "of Spades";
            }
}

