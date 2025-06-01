#ifndef CARD_H
#define CARD_H

template <class T>
void rndmze(T &n){
    n = rand() % 15;
}

///abstract class
class Abstrct{ 
    protected:
        int card;
        string name;
        int points;
    public:
        Abstrct(){
            card = 0;
            name = "";
            points = 0;
        }
        ~Abstrct(){};
};

class PlyInfo{ //player info
    private:
        string plyrNme;
        int score;
    public:
        PlyInfo(){
            plyrNme = "";
            score = 0;
        }
        PlyInfo(string str)
            {plyrNme = str;
             score = 0; }
        ~PlyInfo(){};
        
        string getInfN()
            { return plyrNme; }
        int getScre()
            { return score; }
        void addScre()
            { score++; }
        void setInfN(string str)
            {   
                string exc;
                if(str.length() <= 2){ //exception
                    exc = "!error! Invalid input! ";
                    throw exc;
                }
                else{
                    plyrNme = str; 
                }
            }
};

class Card : public Abstrct{
    protected:
        PlyInfo plyinfo; //aggregation
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
        Card() : Abstrct()
            { 
              card = 0; 
              points = 0; 
            }
        Card(int n)
            { 
              card = n;
              points = 0; 
            }
        Card(Card &obj) //copy constructor
            {
                card = obj.getCrdN();
                name = obj.getName();
                points = obj.getPnts();
            }
        virtual ~Card(){}
        void setCard(int newInt)
            { card = newInt; }
        void setPnts(int n)
            { points = n; }
        int getCrdN()
            { return card; }
        string getName()
            { return name; }
        void setInfN(string str)
            { plyinfo.setInfN(str); }
        string getInfN()
            { return plyinfo.getInfN(); }
        int getInfS()
            { return plyinfo.getScre(); }
        int getPnts()
            { return points; }
        void addScre()
            { plyinfo.addScre(); }
        int getScre()
            { return plyinfo.getScre(); }

        int detPnts(); //determine the amount of points a card is worth.
        
        void setFace(); //set the face

        void setSuit(); //set the suit

        friend std::ostream &operator<<(ostream &strm, Card obj){ //overloading the "<<" operator
            obj.setFace();
            obj.setSuit();
            strm << obj.name;
            return strm;
        }

        bool operator==(const Card &obj){ //overloading the "==" operator
            bool status;

            if(card == obj.card){
                status = true;
            }
            else{
                status = false;
            }
            return status;
        }

        int operator+=(int p){ //overloading the "+=" operator
            points += p;
            return points;
        }
};

class DlrCard : public Card{
    private:
        static string dlrName;
        static int nameNum;
    public:
        DlrCard()
            { nameNum = 0; }
        virtual ~DlrCard(){};
        
        static int getNmeN()
            { return nameNum; }

        static string getDlr()
            { return  dlrName; }

        static void pickNme();
};

class ExtrPyr : public Card{
    private:
        string exc;
        string extPNme; //extra player name
        int nameNum;
        int size;
        int *crdAr; //individual double hand of each extra player.
    public:
        ExtrPyr()
            {  
              size = 2;
              crdAr = new int[size];
              nameNum = 0;
            }
        virtual ~ExtrPyr()
            { delete [] crdAr; }

        void setFace(int); //pulls in an index
        void setSuit(int); // pulls in an index

        int detPnts(int); //determine the amount of points a card is worth, pulls in an index.
        
        int getCrdAr(int index){
            return crdAr[index];
        }
        int getNmeN(){
            return nameNum;
        }
        void setCrdAr(int index){
            crdAr[index] = card;
        }

        //virtual functions, polymorphic association
        virtual void pickNme(); //pick the name
        virtual string getPlyr() 
            { 
                return  extPNme;  
            }
};

#endif