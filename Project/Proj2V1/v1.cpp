/******************************************************************************
Name: Ashton Cramer
Date: 5/24/2025
Purpose: Black Jack. Project 2, Version 1. Basic card picking program.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Card{
    private:
        int card;
        string name;
        enum Deck {
            //Clubs
            CA = 1, C2, C3, C4, C5, 
            C6, C7, C8, C9, C10, 
            CJ, CQ, CK,
            //Diamonds
            DA, D2, D3, D4, D5, 
            D6, D7, D8, D9, D10, 
            DJ, DQ, DK,
            //Hearts
            HA, H2, H3, H4, H5, 
            H6, H7, H8, H9, H10, 
            HJ, HQ, HK,
            //Spades
            SA, S2, S3, S4, S5, 
            S6, S7, S8, S9, S10,
            SJ, SQ, SK
        };

    public:
        Card(int n)
            { card = n; }
        void setCard(int newInt)
            { card = newInt; }
        int getCrdN()
            { return card; }
        string getName()
            { return name; }
        
        void setFace()
        {
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

        void setSuit()
        {
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

        friend std::ostream &operator<<(ostream &strm, Card obj){ //overloading the "<<" operator
            obj.setFace();
            obj.setSuit();
            strm << obj.name;
            return strm;
        }
};

string plyrNme(); //ask for the player's name
void binWrte(int); //write a series of numbers to the cards.dat
void binRead(char *, int, int, int&); //read from cards.dat into a dynamic array
void results(bool &, bool &, int&, int&, int); //decides the winner

int main(){
    srand(time(0));
    
    string player; //player's name
    char *ptrArr = nullptr; //ptr to make a dynamic array
    bool won; //flag for win case
    int opt, counter, dlrCntr, stayCtr; //counters
    int chosen, choose; //decides which card is chosen.
    int size = 53; //size for dynamic arrays
    char ask; //ask if the player wants to play again

    counter = 0; //your points counter
    dlrCntr = 0; //points counter for the dealer
    stayCtr = 0; //count how many times player's stayed.
    ask = 'y'; 

    binWrte(size);

    player = plyrNme();
    
    binRead(ptrArr, size, choose, chosen);

    Card card(chosen);
    cout << player << " pulled: " << card;

    delete [] ptrArr;
    return 0;
}

string plyrNme(){
    string str;

    cout << "What is your name?: ";
    cin >> str;

    return str;
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

    cout << "Deck size: " << strlen(arr) - 1 << endl; //string object
    
    toFile.open("cards.bin", ios::out | ios::binary);
    
    toFile.write(reinterpret_cast<char*>(arr), size * sizeof(char));

    //clean up
    delete [] arr;
    toFile.close();
}

void binRead(char *ptrArr, int size, int choose, int &chosen){
    fstream fromFile;

    //Read process
    fromFile.open("cards.bin", ios::in | ios::binary);
    ptrArr = new char[size]; //53
    
    fromFile.seekg(0, ios::beg); 
    
    for(int i=0; i < size; i++){
        fromFile.seekg(i, ios::beg);
        ptrArr[i] = fromFile.tellg(); 
    }

    choose = rand() % (size - 1) + 1;
    for(int i=0; i < size; i++){
        if(static_cast<int>(ptrArr[i]) == choose){
            chosen = static_cast<int>(ptrArr[i]);
        }
    }

    //close file
    fromFile.close();
}