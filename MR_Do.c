#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#define ESP 32
#define CIMA 72
#define BAIXO 80
#define ESQUERDA 75
#define DIREITA 77
#define FUNDO 176
#define FANTASMA 153
#define NINHO 206
#define VELOCIDADE 1
#define VELGHOST 4
#define FUT 229
#define FANTASMA 153
#define CIMAF 3
#define DIREITAF 2
#define BAIXOF  1
#define ESQUERDAF 0



typedef struct{
	int Pfx [10];
	int Pfy [10];
	int Exi [10];
	int ultP[10];
	int acerto;
}Inimigo;
typedef struct {
	int Pvx[32];
	int Pvy[32];
	int Exi[32];
}Frutas;
typedef struct{                                                                 // Personagem
 int Posx; //mrdo[0]
 int Posy; //mrdo[1]
 int ultP;
 int pontos;
}MrDo;
typedef struct{                                                                  // tiro
	int PxT;
	int PyT;
	int Tex;
	int dirT;
	int prox;
}Tiro;

void MENU (){                                                                     // função MENU
	int i=0,menu=0;
	system("cls");
	for(i=0;i<=60;i++){
		printf("%c",FUNDO);
	}
	printf("\n\t\t\tMr Do !\n\n");
	
	for(i=0;i<=60;i++){
		printf("%c",250);
	}
	printf("\n\t\t1 - NOVO JOGO\n");
	printf("\t\t2 - CONTINUAR\n");
	printf("\t\t3 - HIGH SCORES\n");
	printf("\t\t4 - SAIR\n");
	for(i=0;i<=60;i++){
		printf("%c",FUNDO);
	}
	printf("\n\t\tENTRE COM A OPCAO DESEJADA\n");
	scanf("%d",&menu);
	
	switch (menu){
	
		case 1:break;
		case 2:break;
		case 3:break;
		case 4: exit(0); break;
		default:MENU();break;
	
	}
	
}
void gotoxy (int x, int y)  {          // funçao gotoxy --> deixa o estado no mouse na coordenada 0,0
    COORD coord = {0, 0};
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void ShowConsoleCursor(int showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // esconder o cursos  no estado que estiver
    SetConsoleCursorInfo(out, &cursorInfo);
}
Inimigo INICIAR_FANTASMA(Inimigo fantasma){
	int i;
	for(i=0;i<10;i++){
		fantasma.Exi[i] = 0;
		fantasma.Pfx[i] = 11;
		fantasma.Pfy[i] = 30;
		fantasma.ultP[i]=4;
	}
	return fantasma;
}

Inimigo NASCER_FANTASMA(Inimigo fantasma, int k){
	fantasma.Exi[k] = 1;
	fantasma.ultP[k]=4;
	fantasma.Pfx[k] = 11;
	fantasma.Pfy[k] = 30;
		
	return fantasma;
}

Frutas IniciarCerejas(Frutas Cereja){
	int i=0;	
	for (i=0; i<32; i++){                               //colocar cerejas
		Cereja.Exi[i]=1;
		Cereja.Pvx[i]= (rand() % 21)+1;                 //+1 colocado pois as vezes as frutas apreciam em cima do * (borda)
		Cereja.Pvy[i]=(rand() % 57)+1;
	}                                                   //colocar cerejas
	 	return Cereja;												// rand -> criar numeros aleatorios
}

int CAMINHOGHOST (char matriz [23][60], int possibilidades[4], int i, Inimigo fantasma){
	int j=0, quantidade=0;
		for (j=0;j<4;j++){
					possibilidades[j]=0;
				}
				
				if(matriz[fantasma.Pfx[i]][fantasma.Pfy[i]-1] == ' '){
					possibilidades[ESQUERDAF] = 1; 
					quantidade++;
				}
				
				if(matriz[fantasma.Pfx[i]+1][fantasma.Pfy[i]] == ' '){
					possibilidades[BAIXOF] = 1;
					quantidade++;
				}
				
				if(matriz[fantasma.Pfx[i]][fantasma.Pfy[i]+1] == ' '){
					possibilidades[DIREITAF] = 1;
					quantidade++;
				}
				if(matriz[fantasma.Pfx[i]-1][fantasma.Pfy[i]] == ' '){
					possibilidades[CIMAF] = 1;
					quantidade++;
				}
				return quantidade;
}

Inimigo DECIDIRFANTASMA(Inimigo fantasma, char matriz[23][60]){
		int i=0, j=0, possibilidades[4], quantidade=0, decisao=0;	
	
			for(i=0;i<10;i++){                                          //Verificar quais os
				if(fantasma.Exi[i] == 1){
					quantidade=CAMINHOGHOST(matriz, possibilidades, i, fantasma);
					if (fantasma.ultP[i]==4 ){ 
						do {
							fantasma.ultP[i]= rand() % 4;
						}while	(possibilidades[fantasma.ultP[i]]==4);	
					}
					if (quantidade>=3 ){

						do {
							decisao=rand() % 4;
							if (decisao!=fantasma.ultP[i]){
								fantasma.ultP[i]=decisao;
								decisao=4;
							}
						}while	(decisao==4);	
					}
					
					if(fantasma.Exi[i]==1){
						matriz[fantasma.Pfx[i]][fantasma.Pfy[i]]= FANTASMA;
					}
				}
			}
		return fantasma;
}

void PRINTMATRIZ(char matriz[23][60]){
	int i=0, j=0;
	
			matriz[11][30]= NINHO;
		for (i=0;i<23;i++){	 
			for(j=0;j<60;j++){  //impressão da matriz
					printf("%c" ,matriz[i][j]) ;
			}
			printf("\n");	
		}
}

Inimigo MOVEFANTASMA(Inimigo fantasma, char matriz[23][60], int TEMPOGLOB){		
	int i=0;
		
		for(i=0;i<10;i++){
			if(fantasma.Exi[i]==1){// movimentação do fantasma
				matriz[fantasma.Pfx[i]][fantasma.Pfy[i]]= ' ';
				if (TEMPOGLOB%VELGHOST==0){
				if (fantasma.ultP[i] == 0){
					if(matriz[fantasma.Pfx[i]][fantasma.Pfy[i]-1] == (char)FUNDO || matriz[fantasma.Pfx[i]][fantasma.Pfy[i]-1] == '*'  ){
						fantasma.ultP[i]=4;
					}
					else{
						fantasma.Pfy[i]-=1;
					}
				}
				if (fantasma.ultP[i] == 1){
					if(matriz[fantasma.Pfx[i]+1][fantasma.Pfy[i]] == (char)FUNDO || matriz[fantasma.Pfx[i]+1][fantasma.Pfy[i]] == '*' ){
						fantasma.ultP[i]=4;
					}
					else{
					fantasma.Pfx[i]+=1;
					}
				}
				if (fantasma.ultP[i] == 2){
					if(matriz[fantasma.Pfx[i]][fantasma.Pfy[i]+1] == (char)FUNDO || matriz[fantasma.Pfx[i]][fantasma.Pfy[i]+1] == '*' ){
						fantasma.ultP[i]=4;
					}
					else{
					fantasma.Pfy[i]+=1;
					}
				}
				if (fantasma.ultP[i] == 3){
					if(matriz[fantasma.Pfx[i]-1][fantasma.Pfy[i]] == (char)FUNDO || matriz[fantasma.Pfx[i]-1][fantasma.Pfy[i]] == '*' ){
						fantasma.ultP[i]=4;
					}
					else{
					fantasma.Pfx[i]-=1;
					}
				}
				}
			}
		}
	
		
		return fantasma;
}

void TELA(char matriz[23][60], Frutas Cereja, MrDo Do ){
	int i=0, j=0;
		
	for (i=0;i<23;i++){ // limpar linhas
		for(j=0;j<60;j++){  // limpar colunas
			matriz[i][j]= FUNDO;
		}
	}
	
	for (j=0;j<60;j++){ // borda
		matriz[0][j]='*';
		matriz[22][j]='*';
	}
	
	
	for (i=0;i<23;i++){ // borda
		matriz[i][0]='*';
		matriz[i][59]='*';
	
	}
	for(i=1; i<22; i++){ // baixo
		matriz[i][30]=' ';
	}
	for (i=1; i<45; i++){ //meio
		matriz[21][i]=' ';
	}

	for (i=1; i<30; i++){ //lateral esquerda até o meio
		matriz [16][i]=' ';	
	}
	for (i=16; i<21; i++){
		matriz[i][12]=' ';
	}
	
	for (i=0; i<32; i++){
		matriz[Cereja.Pvx[i]][Cereja.Pvy[i]]=229;
	}
	matriz[Do.Posx][Do.Posy]=244;
	matriz[11][30]= NINHO;
	system ("cls");
}

Tiro MOVETIRO(Tiro Shot, char matriz[23][60]){

		if (Shot.dirT==BAIXO  && matriz[Shot.PxT+1][Shot.PyT] != '*' && matriz[Shot.PxT+1][Shot.PyT] != (char)FUNDO && matriz[Shot.PxT+1][Shot.PyT] != (char)FANTASMA){
						matriz[Shot.PxT][Shot.PyT]=Shot.prox;
						Shot.PxT+=1;
						Shot.prox=matriz[Shot.PxT][Shot.PyT];
						matriz[Shot.PxT][Shot.PyT]=250;	
				}
				else if(Shot.dirT==BAIXO  && (matriz[Shot.PxT+1][Shot.PyT] == '*' || matriz[Shot.PxT+1][Shot.PyT]==(char)FUNDO || matriz[Shot.PxT+1][Shot.PyT]==(char)FANTASMA)){ 
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.Tex=0;
				}
				
				if (Shot.dirT==CIMA && matriz[Shot.PxT-1][Shot.PyT] != '*' && matriz[Shot.PxT-1][Shot.PyT]!=(char)FUNDO && matriz[Shot.PxT-1][Shot.PyT] != (char)FANTASMA) {
					
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.PxT-=1;
					Shot.prox=matriz[Shot.PxT][Shot.PyT];
					matriz[Shot.PxT][Shot.PyT]=250;
				}
				else if(Shot.dirT==CIMA  && (matriz[Shot.PxT-1][Shot.PyT] == '*' || matriz[Shot.PxT-1][Shot.PyT]==(char)FUNDO || matriz[Shot.PxT-1][Shot.PyT]==(char)FANTASMA)){
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.Tex=0;
				}
				
				if(Shot.dirT==ESQUERDA && matriz[Shot.PxT][Shot.PyT-1] != '*' && matriz[Shot.PxT][Shot.PyT-1]!=(char)FUNDO && matriz[Shot.PxT][Shot.PyT-1] != (char)FANTASMA){
					
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.PyT-=1;
					Shot.prox=matriz[Shot.PxT][Shot.PyT];
					matriz[Shot.PxT][Shot.PyT]=250;
				}
				else if(Shot.dirT==ESQUERDA  && (matriz[Shot.PxT][Shot.PyT-1] == '*' || matriz[Shot.PxT][Shot.PyT-1]==(char)FUNDO || matriz[Shot.PxT][Shot.PyT-1]==(char)FANTASMA)){
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.Tex=0;
				}
				
				if (Shot.dirT==DIREITA && matriz[Shot.PxT][Shot.PyT+1] != '*' && matriz[Shot.PxT][Shot.PyT+1]!=(char)FUNDO && matriz[Shot.PxT][Shot.PyT+1] != (char)FANTASMA){
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.PyT+=1;
					Shot.prox=matriz[Shot.PxT][Shot.PyT];
					matriz[Shot.PxT][Shot.PyT]=250;
				}
				else if (Shot.dirT==DIREITA  && (matriz[Shot.PxT][Shot.PyT+1] == '*' || matriz[Shot.PxT][Shot.PyT+1]==(char)FUNDO  || matriz[Shot.PxT][Shot.PyT+1]==(char)FANTASMA)){
					matriz[Shot.PxT][Shot.PyT]=Shot.prox;
					Shot.Tex=0;
				}
				return Shot;
}

Inimigo MATAR_FANTASMA(Tiro *Shot, Inimigo fantasma, char matriz[23][60], MrDo *Do){ //
	int i, j=0;
	for(i=0;i<10;i++){
		
		if (fantasma.Exi[i] == 1){
		
		
			if((*Shot).PxT == fantasma.Pfx[i] && (*Shot).PyT == fantasma.Pfy[i]  ){
				j=1;
			}
			if(fantasma.Pfx[i] == (*Shot).PxT-1 && fantasma.Pfy[i] == (*Shot).PyT){
				j=1;
			}
			if(fantasma.Pfx[i] == (*Shot).PxT+1 && fantasma.Pfy[i] == (*Shot).PyT){
				j=1;
			}
			if(fantasma.Pfx[i] == (*Shot).PxT && fantasma.Pfy[i] == (*Shot).PyT+1){
				j=1;
			}
			if(fantasma.Pfx[i] == (*Shot).PxT && fantasma.Pfy[i] == (*Shot).PyT-1){
				j=1;
			}
			if(j==1){
				fantasma.Exi[i] = 0;
				(*Shot).Tex = 0;
				(*Do).pontos+=10;
				fantasma.acerto+=1;
				matriz[(*Shot).PxT][(*Shot).PyT] = ' ';
				j=0;
			}
		}
	}
	return fantasma;
}

Frutas MATAR_CEREJA(Frutas Cereja, Tiro *Shot, char matriz[23][60]){
	int i;
	for(i=0;i<32;i++){
		if(Cereja.Exi[i]==1){
			if((*Shot).PxT == Cereja.Pvx[i] && (*Shot).PyT == Cereja.Pvy[i]){
				Cereja.Exi[i] = 0;
				(*Shot).Tex = 0;
				matriz[(*Shot).PxT][(*Shot).PyT] = ' ';
			}
		}
	}
	return Cereja;
}
MrDo MOVEDO(MrDo Do, char matriz[23][60], int TEMPOGLOB){
	int i;
	
	if (Do.ultP==BAIXO && matriz[Do.Posx+1][Do.Posy] != '*' && TEMPOGLOB % VELOCIDADE==0 && matriz[Do.Posx+1][Do.Posy] != (char)NINHO ){	
		if(matriz[Do.Posx+1][Do.Posy]==(char)FUT)	{
			Do.pontos+=50;
		}
			matriz[Do.Posx][Do.Posy]=' ';
			Do.Posx++;
			matriz[Do.Posx][Do.Posy]=244; // bichinho da tabela 
			Do.ultP=BAIXO;
		}
		if (Do.ultP==CIMA && matriz[Do.Posx-1][Do.Posy] != '*' && TEMPOGLOB % VELOCIDADE==0 && matriz[Do.Posx-1][Do.Posy] !=(char) NINHO){
			if(matriz[Do.Posx-1][Do.Posy]==(char)FUT)	{
				Do.pontos+=50;
			}
			matriz[Do.Posx][Do.Posy]=' ';
			Do.Posx--;
			matriz[Do.Posx][Do.Posy]=244; // bichinho da tabela 
			Do.ultP=CIMA;
		}
		if (Do.ultP==DIREITA && matriz[Do.Posx][Do.Posy+1] != '*' && TEMPOGLOB % VELOCIDADE==0 && matriz[Do.Posx][Do.Posy+1] !=(char) NINHO){
				if(matriz[Do.Posx][Do.Posy+1]==(char)FUT)	{
					Do.pontos+=50;
				}
				matriz[Do.Posx][Do.Posy]=' ';
				Do.Posy++;
				matriz[Do.Posx][Do.Posy]=244; // bichinho da tabela
				Do.ultP=DIREITA; 
			}
		if (Do.ultP==ESQUERDA && matriz[Do.Posx][Do.Posy-1] != '*' && TEMPOGLOB % VELOCIDADE==0 && matriz[Do.Posx][Do.Posy-1] !=(char) NINHO ){
				if(matriz[Do.Posx][Do.Posy-1]==(char)FUT)	{
					Do.pontos+=50;
				}
				matriz[Do.Posx][Do.Posy]=' ';
				Do.Posy--;
				matriz[Do.Posx][Do.Posy]=244; // bichinho da tabela
				Do.ultP=ESQUERDA; 
			}                                              //movimento continuo
			
			return Do;
}
Frutas COMER_CEREJA(MrDo Do, Frutas Cereja, char matriz[23][60], Inimigo fantasma){
	int i, j;

					for(i=0;i<32;i++){
						if(Cereja.Pvx[i] == Do.Posx && Cereja.Pvy[i] == Do.Posy){
							Cereja.Exi[i] = 0;  
						}
						
						for(j=0;j<10;j++){
						 	if(fantasma.Exi[j] == 1 && Cereja.Pvx[i] == fantasma.Pfx[j] && Cereja.Pvy[i] == fantasma.Pfy[j]){
								Cereja.Exi[i] = 0;  
							}	
						}
				}
			return Cereja;
}
void GAME_OVER(MrDo Do, Inimigo fantasma, Frutas Cereja){
	int i, x = 0;
	for(i=0;i<10;i++){
		if(Do.Posx == fantasma.Pfx[i] && Do.Posy == fantasma.Pfy[i]){
			   system ("cls");
			   printf ("VOCE PERDEU SEU ARROMBADO, voce tocou no fantasma!");
			   system ("PAUSE");
			   exit(0);
		}
	}
	for(i=0;i<32;i++){
		if(Cereja.Exi[i] == 1){
			x++;
		}
	}
	if(x==0){
		system ("cls");
			   printf ("PARABAINS, VOCE PEGOU TODAS AS FRUTAS!");
			   system ("PAUSE");
			   exit(0);	
	}
	
		if(fantasma.acerto==10){
			system("PAUSE");
		}
	
	
}
void JOGO(MrDo Do, Tiro Shot, Inimigo fantasma,char matriz[23][60], Frutas Cereja){
		
		int k=0, i=0,j=0,tempo=0;
		int keypress;
		int TEMPOGLOB=1;
		
		//fantasma.Exi[0]=1;
		//fantasma.ultP[0]=4;
		
		
		while(1){ // enquanto sempre verdade, com while  1
		gotoxy(0,0);
		if (TEMPOGLOB%43==0 && k<10) {
			fantasma=NASCER_FANTASMA(fantasma, k);
			k++;
		}
		if(kbhit()) {
			Do.ultP = CONTROLARMRDO(keypress, matriz, Do, &Shot); // mover MrDo Do
	 	}
		                                                         
		if (Shot.Tex==1){
			Shot = MOVETIRO(Shot, matriz);
			Cereja=MATAR_CEREJA(Cereja, &Shot, matriz);
			fantasma=MATAR_FANTASMA(&Shot, fantasma, matriz, &Do);
		}
		printf("pos x tiro:%d  pos y tiro:%d \n  Tempo: %d\n", Shot.PxT, Shot.PyT,clock()/1000);        
		fantasma=DECIDIRFANTASMA(fantasma, matriz);
		PRINTMATRIZ(matriz);
		fantasma=MOVEFANTASMA(fantasma, matriz,TEMPOGLOB);
		printf("Pontos: %d\n",Do.pontos);
		Cereja=COMER_CEREJA(Do, Cereja, matriz, fantasma);
		Do=MOVEDO(Do, matriz, TEMPOGLOB);	
		TEMPOGLOB++;
		GAME_OVER(Do, fantasma, Cereja);
			
	}
	
}
int CONTROLARMRDO(int keypress, char matriz[23][60], MrDo Do, Tiro *Shot){
			
	                                                      //   movimento
			keypress = getch();
			if (keypress==BAIXO && matriz[Do.Posx+1][Do.Posy] != '*' ){
				Do.ultP=BAIXO;
			}
			if (keypress==CIMA && matriz[Do.Posx-1][Do.Posy] != '*' ){
				Do.ultP=CIMA;
			}
			if (keypress==DIREITA && matriz[Do.Posx][Do.Posy+1] != '*'){
				Do.ultP=DIREITA; 
			}
			if (keypress==ESQUERDA && matriz[Do.Posx][Do.Posy-1] != '*'){
				Do.ultP=ESQUERDA; 
		
			}  
			if (keypress==ESP && (*Shot).Tex==0 ){                          // tiro
				(*Shot).Tex=1;
				if(Do.ultP==BAIXO){
					(*Shot).PxT=Do.Posx+1;
					(*Shot).PyT=Do.Posy;
					(*Shot).dirT=BAIXO;
				}
				else if(Do.ultP==CIMA){
					(*Shot).PxT=Do.Posx-1;
					(*Shot).PyT=Do.Posy;
					(*Shot).dirT=CIMA;
				}
				else if(Do.ultP==ESQUERDA){
					(*Shot).PxT=Do.Posx;
					(*Shot).PyT=Do.Posy-1;
					(*Shot).dirT=ESQUERDA;
				}
				else if(Do.ultP==DIREITA){
					(*Shot).PxT=Do.Posx;
					(*Shot).PyT=Do.Posy+1;
					(*Shot).dirT=DIREITA;
				}
				(*Shot).prox=matriz[(*Shot).PxT][(*Shot).PyT];
				
			}
			
			return (Do.ultP);
}                                                           // movimento

int main(int argc, char *argv[]) {



ShowConsoleCursor(0);
	HWND wh = GetConsoleWindow(); // captura janela // HWND : identificador do tipo da janela // GetConsoleWindow recupera o identificador da janela
	MoveWindow(wh, 10, 10, 1000, 1000, TRUE); // controla o tamanho da janela
	char matriz[23][60]; // crair matriz com tamanho definido
	MrDo Do;
	Do.Posx=21;
	Do.Posy=30;
	Do.pontos;
	Tiro Shot;
	//Tiro *Bala=Shot;
	Shot.Tex=0;
	Shot.dirT=0;
	Frutas Cereja; 
	MENU();
	Inimigo fantasma;
	fantasma.acerto=0;
	srand(time(NULL)); //por padrão retira informações da hora do sistema para a criação de numeros randomicos
	Cereja=IniciarCerejas(Cereja);
	TELA(matriz, Cereja, Do);
	JOGO(Do, Shot, fantasma, matriz, Cereja);

	return 0;
	
}
//%c imprime char
