#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define PIECES 19
#define HEXES 19
#define PIECE_END -1
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
void swap_int(int *p,int *q){
	int temp=*p;
	*p=*q;
	*q=temp;
}
void swap_char(char *p,char *q){
	int temp=*p;
	*p=*q;
	*q=temp;
}
void random_pieces(int *p){
	int *q=p;
	while(*q!=PIECE_END){
		int pos=rand()%PIECES;
		swap_int(q,p+pos);
		++q;
	}
}
void random_board(char *p){
	char *q=p;
	while(*q!='\0'){
		int pos=rand()%HEXES;
		swap_char(q,p+pos);
		++q;
	}
}
void fix_desert(char *b,int *p){
	char *c;
	int *q;
	size_t loc;
	for(c=b;*c!='D' && *c!='\0';++c){}
	loc=c-b;
	for(q=p;*q!=0 && *q!=PIECE_END;++q){}
	swap_int(p+loc,q);
}
bool is_red(int i){return i==6 || i==8;}
void print(char *b,int *p){
	char *c=b;
	int *q=p;
	while(*c!='\0' && *q!=PIECE_END){
		switch(c-b){
			case 0:
				printf("    ");
				break;
			case 16:
				printf("\n    ");
				break;
			case 3:
			case 12:
				printf("\n  ");
				break;
			case 7:
				printf("\n");
				break;
			default:
				break;

		}
		printf(NORMAL "%c",*c);
		if(is_red(*q)){
			printf(RED);
		}else{
			printf(NORMAL);
		}
		printf((*q/10==0)?"0%d ":"%d ",*q);
		++c,++q;
	}
	printf(NORMAL "\nS = Sheep, L = Lumber, W = Wheat, B = Brick, O = Ore, D = Desert\n");
}
bool is_adj(int i,int j){
	switch(i){
		case 0:
		case 1:
		case 13:
		case 14:
			if(j==i+1 || j==i+3 || j==i+4){return true;}
			return false;
		case 2:
			if(j==5 || j==6){return true;}
			return false;
		case 3:
		case 4:
		case 5:
		case 8:
		case 9:
		case 10:
			if(j==i+1 || j==i+4 || j==i+5){return true;}
			return false;
		case 6:
			if(j==10 || j==11){return true;}
			return false;
		case 7:
			if(j==8 || j==12){return true;}
			return false;
		case 11:
			if(j==15){return true;}
			return false;
		case 12:
			if(j==13 || j==16){return true;}
			return false;
		case 15:
			if(j==18){return true;}
			return false;
		case 16:
		case 17:
			if(j==i+1){return true;}
			return false;
		case 18:
			return false;
		default:
			printf("Invalid number\n");
			return false;
	}
}
bool check(int *ps){
	int *p,*q;
	for(p=ps;*p!=PIECE_END;++p){
		for(q=ps;*q!=PIECE_END;++q){
			if(is_adj(p-ps,q-ps) && is_red(*p) && is_red(*q)){
				return false;
			}
		}
	}
	return true;
}
void run(char *board,int *pieces){
	srand(time(NULL));
	int c;
	do{
		random_board(board);
		do{
			random_pieces(pieces);
			fix_desert(board,pieces);
		}while(!check(pieces));
		print(board,pieces);
		printf("Type q to quit or enter for another board.\n");
		c=getchar();
	}while(c!='q' && c!='Q');
}
int main(){
	int pieces[]={2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12,0,PIECE_END};
	char board[]="SSSSLLLLWWWWBBBOOOD";
	run(board,pieces);
}
