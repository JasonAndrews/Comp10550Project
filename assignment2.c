/*
 * main.c

 *
 *  Created on: 1 Mar 2017
 *      Author: jeremiah
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

# define MAX_PLAYERS 6 // this is the maximun number of players allowed
# define MAX_PTS 100
# define MIN_PTS 0


enum type {
	Elf,
	Human,
	Ogre,
	Wizard
};
/*struct cap{
	int Smartness;
	int Strength;
	int Magic_skills;
	int Luck;
	int Dexterity;
};*/

struct player {
	char name[20];
	enum type playerType;
	int life_pts;
	/*struct cap level;*/
	int cap[5]; //Array of capabilities. Smartness, Strength, Magic_skills, Luck, Dexterity, respectively
};
void sortCap(int i);
bool found;
struct player num[MAX_PLAYERS];

int main()
{
	int i=0,n;
	
	int choice;
	
	
	printf("Please enter number of players (max. 6 players)\n");
	scanf("%d", &n);

	if(n<1||n>6)
	{
		printf("ERROR INVALID ENTRY: Please enter a number between 1 and 6");
	}
	else
	{
		do
		{
			
			
			printf("\nPlease enter player name (20 characers max.)\n");
			scanf("%s", num[i].name);
			
			printf("\nPlease select player type\n");
			printf("1)Elf\n");
			printf("2)Human\n");
			printf("3)Ogre\n");
			printf("4)Wizard\n");

			scanf("%d", &choice);

			switch(choice)
			{
			case 1:
			num[i].playerType=Elf;
			break;

			case 2:
			num[i].playerType=Human;
			break;

			case 3:
			num[i].playerType=Ogre;
			break;

			case 4:
			num[i].playerType=Wizard;
			break;

			default:
			printf("ERROR INVALID ENTRY:Please enter a number between 1 and 4");
			}
			num[i].life_pts = MAX_PTS;
			i++;
			
			sortCap(i);
			
		}while(i<n);
		
		printf("%s(%d,%d)", num[0].name, num[0].cap[0],num[0].life_pts);
		printf("%s(%d,%d)", num[1].name, num[1].cap[0],num[1].life_pts);
	}

	return 0;
}

void sortCap(int i)
{
	int sum,j;
	srand(time(NULL));
	
	if(num[i].playerType==1)
			{
				while(found)
				{
					for(j=0;j<5;j++)
					{
						num[i].cap[j]=1+rand()%99;
						sum+=num[i].cap[i];
					}
					
					if(sum<300)
					{
						found;
					}else{!found;}
				}
			}
			
			if(num[i].playerType==2)
			{
				while(found)
				{
					num[i].cap[2]=MIN_PTS;
					num[i].cap[0]=rand()%20;
					num[i].cap[1]=80+rand()%20;
					num[i].cap[4]=80+rand()%20;
					
					if((num[i].cap[0]+num[i].cap[3])<50)
					{
						found;
					}else{!found;}
				}
			}
			
			if(num[i].playerType==0)
			{
				num[i].cap[3]=60+rand()%40;
				num[i].cap[0]=70+rand()%30;
				num[i].cap[1]=1+rand()%49;
				num[i].cap[2]=51+rand()%29;
				num[i].cap[4]=1+rand()%99;
			}
			
			if(num[i].playerType==3)
			{
				num[i].cap[3]=50+rand()%50;
				printf("%d", num[i].cap[3]);
				num[i].cap[0]=90+rand()%10;
				num[i].cap[1]=1+rand()%19;
				num[i].cap[2]=80+rand()%20;
				num[i].cap[4]=1+rand()%99;
			}
}