class Card{
    protected:
        int card;
        string name;
        int points;
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
        Card()
            { card = 0; 
              points = 0; }
        Card(int n)
            { card = n; }
        ~Card(){}
        void setCard(int newInt)
            { card = newInt; }
        void setPnts(int n)
            { points = n; }
        int getCrdN()
            { return card; }
        string getName()
            { return name; }
        int getPnts()
            { return points; }

        int detPnts(); //determine the amount of points a card is worth.
        
        void setFace();

        void setSuit();

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
        ~DlrCard(){};
        
        static string getDlr()
            { return dlrName; }

        static void pickNme();
};

class ExtrPyr : public Card{
    private:
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
        ~ExtrPyr()
            { delete [] crdAr; }

        void setFace(int); //pulls in an index
        void setSuit(int); // pulls in an index

        int detPnts(int); //determine the amount of points a card is worth.
        
        int getCrdAr(int index){
            return crdAr[index];
        }
        void setCrdAr(int index){
            crdAr[index] = card;
        }

        void pickNme(); //pick the name
        string getPlyr()
            { return  extPNme; }
};