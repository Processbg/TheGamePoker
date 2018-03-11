#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int card_rank; // 2-14
	int card_suit; // 1-2-3-4
} Carta;

// Pika, Kupa, Karo, Spatia
// A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2

// A-Pika, K-Karo, 

int playerACards[2];
int playerBCards[2];

int faceUpCards[5];

Carta all_cards[52];

int used_cards[52]; // vsichko  e nula v nachaloto

int playerTurn = 0;

int playerAMoney = 5000;
int playerBMoney = 5000;

int playerABet = 0;
int playerBBet = 0;


void initialize_cards(){
	int counter = 0;
	int i = 0;
	int k = 0;


	playerAMoney = 5000;
	playerBMoney = 5000;

	playerABet = 0;
	playerBBet = 0;
	
	for (i=0;i<4;i++)
	  for (k=0;k<13;k++)
	  {
		  Carta c;
		  c.card_rank = k+2;
		  c.card_suit = i;
		  all_cards[counter] = c;
		  used_cards[counter] = 0;
		  counter++;
	  }
	 
	 for (i=0;i<2;i++)
	 {
		playerACards[i] = -1;
		playerBCards[i] = -1;
	}	
	
	for (i=0;i<5;i++)
	{
		faceUpCards[i] = -1;
	}	
}

int iztegli_karta() 
{
	int index = -1;
	
	while (index == -1) 
	{ 
	  index = alea_int(52);
	  
	  if (used_cards[index] == 1)
	    index = -1;
	}
   used_cards[index] = 1;
   
   return index;
}

void carta_to_char(Carta carta, char buffer[]) 
{
	char rank = '?';
	switch (carta.card_rank) 
	{
	  case 2:    rank = '2';  break;
	  case 3:    rank = '3';  break;	 
	  case 4:    rank = '4';  break;
	  case 5:    rank = '5';  break;
	  case 6:    rank = '6';  break;
	  case 7:    rank = '7';  break;
	  case 8:    rank = '8';  break;
	  case 9:    rank = '9';  break;
	  case 10:   rank = 'T';  break;
	  case 11:   rank = 'J';  break;
	  case 12:   rank = 'Q';  break;
	  case 13:   rank = 'K';  break;
	  case 14:   rank = 'A';  break;
   }
    
    buffer[0] = rank;
    buffer[1] = '-';
    
    switch (carta.card_suit) 
    {
		case 0:  buffer[2] = 'S';buffer[3] = 'P';buffer[4] = 'A'; buffer[5] = 'T'; buffer[6] = 0; break;
		case 1:  buffer[2] = 'K';buffer[3] = 'A';buffer[4] = 'R'; buffer[5] = 'O'; buffer[6] = 0; break;
		case 2:  buffer[2] = 'K';buffer[3] = 'U';buffer[4] = 'P'; buffer[5] = 'A'; buffer[6] = 0; break;
		case 3:  buffer[2] = 'P';buffer[3] = 'I';buffer[4] = 'K'; buffer[5] = 'A'; buffer[6] = 0; break;
	}
}

int comp (const void * elem1, const void * elem2) 
{
	int f = *((int*)elem1);
	int s = *((int*)elem2);
	
	if (f > s) return  1;
	if (f < s) return -1;
	
	return 0;
}


void popylni_karti(char faceUpBufAll[], char faceupBuf[], int n, int karti[]){
	
	strcat(faceUpBufAll, faceupBuf);
	
	char temp_buf[] = "1234567";
	
	int m = 0;
	for (m=0;m<n;m++) 
	{
		if (karti[m]==-1)
		  break;

		carta_to_char(all_cards[karti[m]], temp_buf);
		strcat(faceUpBufAll, temp_buf);
		strcat(faceUpBufAll, ",");
	}
}

void afficher_status(int do_check) 
{	
	POINT tx;
	tx.x = 0;
	tx.y = 600;

	char faceUpBuf[] = "Face up cards:";
	
	char playerACardsStr[] = "Player A cards:";
	char playerBCardsStr[] = "Player B cards:";
	char playerAMoneyStr[] = "Player A money:";
	char playerBMoneyStr[] = "Player B money:";
	char playerABetMoney[] = "Player A bet:";
	char playerBBetMoney[] = "Player B bet:";
	
	char playerTurnA[] = "Player turn:A";
	char playerTurnB[] = "Player turn:B";
	
	char question1[] = "Call/Raise/Fold ?";
	char question2[] = "cHeck/Raise/Fold ?";
	
	char faceUpBufAll[100];
	char playerACardsAll[100];
	char playerBCardsAll[100];

	char playerABetMoneyAll[100];
	char playerBBetMoneyAll[100];
	
	char playerAMoneyAll[100];
	char playerBMoneyAll[100];
	
	faceUpBufAll[0] = 0;
    playerACardsAll[0] = 0;
    playerBCardsAll[0] = 0;
    
    playerABetMoneyAll[0] = 0;
    playerBBetMoneyAll[0] = 0;

    playerAMoneyAll[0] = 0;
    playerBMoneyAll[0] = 0;

    
    char tmp[] = "9999999"; // 4980
    
    strcat(playerABetMoneyAll, playerABetMoney);
    sprintf(tmp,"%d", playerABet);
    strcat(playerABetMoneyAll, tmp);
    
    strcat(playerBBetMoneyAll, playerBBetMoney);
    sprintf(tmp,"%d", playerBBet);
    strcat(playerBBetMoneyAll, tmp);
    
    strcat(playerAMoneyAll, playerAMoneyStr); // playerAMoneyAll="Player A Money:"
    sprintf(tmp,"%d", playerAMoney); // tmp = "4980"
    strcat(playerAMoneyAll, tmp); // "Player A Money:4980"
    

    strcat(playerBMoneyAll, playerBMoneyStr); 
    sprintf(tmp,"%d", playerBMoney);
    strcat(playerBMoneyAll, tmp);

	
	popylni_karti(faceUpBufAll, faceUpBuf, 5, faceUpCards);
	popylni_karti(playerACardsAll, playerACardsStr, 2, playerACards);
	popylni_karti(playerBCardsAll, playerBCardsStr, 2, playerBCards);
	
	POINT bg;
	bg.x = 0;
	bg.y = 0;
	
	POINT hd;
	hd.x = 1000;
	hd.y = 600;
	
	draw_fill_rectangle(bg, hd, noir);
	
	aff_pol(faceUpBufAll, 12, tx, rouge);
	tx.y -= 14;
	aff_pol(playerACardsAll, 12, tx, rouge);
    tx.y -= 14;
	aff_pol(playerBCardsAll, 12, tx, rouge);
    tx.y -= 14;
	aff_pol(playerAMoneyAll, 12, tx, rouge);
    tx.y -= 14;
	aff_pol(playerBMoneyAll, 12, tx, rouge);
    tx.y -= 14;
	aff_pol(playerABetMoneyAll, 12, tx, rouge);
    tx.y -= 14;
	aff_pol(playerBBetMoneyAll, 12, tx, rouge);
    tx.y -= 14;
    
    if (playerTurn == 0)
		aff_pol(playerTurnA, 12, tx, rouge);
	else
		aff_pol(playerTurnB, 12, tx, rouge);	
	
	tx.y -= 14;
	
	if (do_check==1) 
	  aff_pol(question2, 12, tx, rouge);
	else
      aff_pol(question1, 12, tx, rouge);
}

void bet(int player, int howmuch)
{
	if (player == 0) 
	{
		playerAMoney -= howmuch; // playerAMoney = playerAMoney - howmuch;
		playerABet += howmuch;
	}
	else 
	{
		playerBMoney -= howmuch;
		playerBBet += howmuch;
	}	
}

int zalagane()
{	
	int result = -1;
	
	int counter = 0;
	 
	while (result==-1) 
	{
		int do_check = playerABet == playerBBet;
	
		char c = ' ';
		int s = -1;
		
		if (do_check)
			while (c!='r' && c!='f' && c!='h') 
			{
				afficher_status(do_check);
				s = scanf(" %c",&c);
				if (s<0)
					continue;
			}
		else
			while (c!='c' && c!='r' && c!='f') 
			{
				afficher_status(do_check);
				s = scanf(" %c",&c);
				if (s<0)
					continue;				
			}
			
		if (c == 'h') 
		{
			playerTurn = 1 - playerTurn;
			
			if (counter > 0)
				break;
		    
			counter++;
			continue;			   
		}
			
		if (c == 'c') 
		{
			if(playerTurn == 0)
			    bet(0, playerBBet - playerABet);
			else
			    bet(1, playerABet - playerBBet);
			   
			playerTurn = 1 - playerTurn;
			
			if (counter > 0)
			  break;
			
			counter++;
			continue;
		}
		
		if (c == 'r') 
		{
			bet(playerTurn, 10);
		   
			playerTurn = 1 - playerTurn;
		   
			counter++;  
			continue;
		}
		
		if (c == 'f') 
		{
			return -1;
		}
	}
   
	return 0;		
}

void razkrii_oshte_karti(int etap) 
{
	switch (etap) 
	{
	case 1:
	 
	faceUpCards[0] = iztegli_karta();
	faceUpCards[1] = iztegli_karta();
	faceUpCards[2] = iztegli_karta();
	break;
	
	case 2:
	
	faceUpCards[3] = iztegli_karta();
	break;
	
	case 3:
	
	faceUpCards[4] = iztegli_karta();
	break;
	
	default:
	break;
	}
}

void end() 
{
	wait_escape();
	exit(0);
}

int main(int argc, char* argv[]) 
{
    //int x[] = {4,5,2,3,1,0,9,8,6,7};
	int L = 1000, H = 600;

    init_graphics(L,H);
	//qsort (x, sizeof(x)/sizeof(*x), sizeof(*x), comp);
    
    //for (i = 0 ; i < 10 ; i++)
       // printf ("%d ", x[i]);
       
    while (1)   {
	
	// trqbva da se slojat proizvolni karti na vseki igrach - vseki po 2 karti v masivite playerACards i playerBCards
	initialize_cards();

	// avtomatichno se zalagat big blind i small blind i igrach A e big blind po podrazbirane	
	playerACards[0] = iztegli_karta();
	playerACards[1] = iztegli_karta();

	playerBCards[0] = iztegli_karta();
	playerBCards[1] = iztegli_karta();
	
	bet(playerTurn, 20);
	bet(1 - playerTurn, 10);
	
	playerTurn = 1 - playerTurn; // tozi deto e slojil small blind
	
	if (zalagane()==-1) 
		//end();
		continue;
	
	razkrii_oshte_karti(1); // 1 znachi izvadi 3 karti navednyj ot testeto
	
	if (zalagane()==-1) 
		//end();
		continue;
	
	razkrii_oshte_karti(2); // 2 znachi izvadi 1 karta ot testeto
	
	if (zalagane()==-1) 
		//end();
		continue;
	
	razkrii_oshte_karti(3); // 3 znachi izvadi 1 karta ot testeto
	
	if (zalagane()==-1) 
		//end();
		continue;

	// proverka koi pecheli obshtiq zalog playerABet + playerBBet
	wait_clic();
	//wait_escape();
	}
	exit(0);

}


