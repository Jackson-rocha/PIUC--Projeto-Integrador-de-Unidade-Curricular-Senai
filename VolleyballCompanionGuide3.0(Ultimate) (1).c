#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include<string.h>
#include<windows.h>

//Quadra
#define LINHAS 9
#define COLUNAS 9
//Times
#define MAX_TEAM 2
#define MAX_PLAYERS 6

typedef struct //Struct que armazena os dados dos times.
	{
		char players[MAX_PLAYERS][60];  
		char alfaplayers[MAX_PLAYERS][60];
		char teamName[20];
		int tshirt[MAX_PLAYERS];
		int alfatshirt[MAX_PLAYERS];
		int score,sets;
	}Team;

Team Times[MAX_TEAM];//Definição da Struct em Vetor.

//Protótipos das funções:
void startmatch(void);
void matchsimulator(void);
int scorewin(int score1,int score2);
int matchwin(int set1,int set2);
int tiebreak (int set1, int set2,int score1,int score2);
void Organizer();
void organizeTshirt();
void matchreport ( int second, int minute, int hour, int setatt, char teampointer[20]);
void MatchResults(char matchmarkedwinner[20]);
void VolleyCamp ();
void reportmanegement();
void reportclear ();
void logo ();

//Variaveis Globais:
int c;
char matchmarked[20];


	
//MAIN
int main(void) 
{
	setlocale (LC_ALL,"Portuguese");
    int opcao,org;
    int i,j,K;
    logo();    
    //Menu de seleção das funcionalidades do programa.
    do {
    	
    	printf("===================================================================\n");
		printf("<=============(VolleyBall Companion Guide - 3.0)==================>\n");
    	printf("===================================================================\n");
        printf("1. Cadastrar Times\n");
        printf("2. Visualizar Times\n");
        printf("3. Iniciar partida\n");
        printf("4. Simular partida\n");
        printf("5. Exibir Campo\n");
        printf("6. Relatório de partida\n");
        printf("7. Sair\n");
        printf("\nDigite sua opção: ");
        fflush(stdin);
        scanf("%d", &opcao);
		 
        switch (opcao) //Função Switch Case para a seleção das funcionalidades.
		{
            case 1://Cadastro das equipes.
                {
                printf("\nCadastro de equipes:\n");
				for ( i = 0; i < MAX_TEAM;i++)
				{
					printf("=====================================\n");
					printf("Digite o nome do %d° time competidor:\n",i+1);
					fflush(stdin);
					scanf(" %[^\n]",&Times[i].teamName);
					
						for ( j = 0; j < MAX_PLAYERS;j++)
						{
							printf("Digite o Nome do %d° jogador:\n",j+1);
							fflush(stdin);
							scanf(" %[^\n]",&Times[i].players[j]);
							printf("Digite o Número da camisa de %s:\n",Times[i].players[j]);
							fflush(stdin);
							scanf(" %d",&Times[i].tshirt[j]);
							printf("O nome do jogador é %s\n",Times[i].players[j]);
							printf("O número da camisa do  jogador é %d\n",Times[i].tshirt[j]);
							
						}
			    					
						printf("=====================================\n");	
						printf("%d° cadastro efetuado com sucesso!\n",i+1);
						
				}
				
				if ( i == MAX_TEAM )
					K++;
				               
                system("pause"); 
      			system("cls"); 
      			break;
      			}
      			
            case 2://Visualizar o cadastro das equipes
            	if ( K >= 1 )
            	{
            		system("cls");
					for ( i = 0; i < MAX_TEAM;i++)
					{
						printf("----------------------------------------------------\n");		
						printf("---------------------%s-----------------------------\n",Times[i].teamName);
						printf("----------------------------------------------------\n");
							for ( j = 0; j < MAX_PLAYERS;j++)
							{
								printf("O nome do jogador é %s\n",Times[i].players[j]);
								printf("O número da camisa do  jogador é %d\n",Times[i].tshirt[j]);
							}
									
				}
				
				printf("\n\nOrganizar:(1) Por nome do Jogador, (2) Por número da camisa ou (3) Para retornar ao Menú:\n");
				scanf("\n%d",&org);
					
				if ( org == 1)
				{
					system("cls");
					Organizer();
					
	      		}	
				if ( org == 2 )
				{
					system("cls");
				   	organizeTshirt();
				   	
	      		}	
				if ( org == 3)
				{
				   	system("cls"); 
					break;
				}							
				}else
	            	printf("\nRealize o cadastro das equipes primeiramente!\n\n\n");
	            	system("pause"); 
           		    system("cls");
	            	break;
                
            case 3: //Partida em tempo real
            	if ( K >= 1 )
            	{
            	c=0;
            	system("cls");
				printf("---------Partida Iniciada-------------\n");
            	printf("--Pressione 'P' para marcar pontuação!\n");
            	printf("--Pressione 'S' para sair da partida!\n");
            	printf("--------------------------------------\n");
            	
            	startmatch();
            	break;
            	}else
				{
				printf("\nRealize o cadastro das equipes primeiramente!\n\n\n");
				system("pause"); // comando que pausa a execução do programa e aguarda o pressionamento de uma tecla para prosseguir com a execução
           		system("cls");
			   	break;
            	}
            case 4: //Simulado de partida
            	if ( K >= 1 )
            	{
            	c=0;
            	system("cls");
            	printf("------Partida Simulada Iniciada------\n");
            	printf("--Pressione 'S' para sair da partida!\n");
            	printf("-------------------------------------\n");
            	
                matchsimulator();
                break;
                }else
            	{
				printf("\nRealize o cadastro das equipes primeiramente!\n\n\n");
				system("pause"); 
           		system("cls");
            	break;
            	}
            case 5: //Campo de Volley
                VolleyCamp ();
                break;
            case 6: //Visualização de realatório
                printf("\nVisualizar arquivo!\n\n\n");
                reportmanegement();
                reportclear ();
				break;
            case 7:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause"); 
      			system("cls");
                break;    
        }
    } while (opcao != 7);

    return 0;
}	
void startmatch (void) //Função da partida real.
{

	int segundo = 0;
    int minuto = 0;
    int hora = 0;
    int i,R,opt;
    int ch,setatt,win,winner,setregistro;
    char marked[20];
    setatt=0;
    setregistro=0;
    R=0;
    Times[0].score = 0;
	Times[1].score = 0;
	Times[0].sets = 0;
	Times[1].sets = 0;
    
    while (1)
	{
	 	
        printf("\t\t\t%dh : %dmin : %dseg\r", hora, minuto, segundo);
        printf("%d°SET:\r",setatt+1);
        setregistro= setatt+1;
        Sleep(1000); 
        
        segundo++;
			
        	if (segundo == 60)
			{
            	segundo = 0;  
            	minuto++;
       
       		}   
        	if (minuto == 60) 
			{
            	minuto = 0;  
            	hora++;
        	}
		
		if ( kbhit())
		{	
			ch = getch();
			
			if(ch==112)
			{
				printf("\n-----------------------------------\n");
			    printf("\nPonto efetuado!\n");
			    printf("\nDigite (1) para o time %s ou (2) para o time %s :\n", Times[0].teamName, Times[1].teamName);
			    fflush(stdin);
			    scanf("%d",&opt);
			    
				if ( opt == 1 )
				{
					Times[0].score++;
					printf("\n-%s\n",Times[0].teamName);
					printf("=============================(Placar)==================================\n");
					printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
					printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
					printf("=======================================================================\n");
					strcpy ( marked, Times[0].teamName );
				
				}
				
				if ( opt == 2 )
				{
					Times[1].score++;
					printf("\n-%s\n",Times[1].teamName);
					printf("=============================(Placar)==================================\n");
					printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
					printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
					printf("=======================================================================\n");
					strcpy ( marked, Times[1].teamName );
				}
			}
			
		matchreport( segundo, minuto, hora, setregistro, marked);
		setatt=setatt+scorewin(Times[0].score,Times[1].score);
	 	winner=scorewin(Times[0].score,Times[1].score);
		win=matchwin(Times[0].sets,Times[1].sets) ;
		win=tiebreak (Times[0].sets,Times[1].sets,Times[0].score,Times[1].score);
				
		c++;
		
		if ( win == 1 )
		{
			win=0;
			system("pause"); // comando que pausa a execução do programa e aguarda o pressionamento de uma tecla para prosseguir com a execução
      		system("cls"); 
			break;
		
        }
       		}
			fflush(stdin);
			if(ch==115)
			{
				printf("\n\n======================(Partida Interrompida)===========================\n\n");
				system("pause"); 
		      	system("cls");
		      	break;
				
			}	
}
}
void matchsimulator(void) //Função partida simulada.
{

	int segundo = 0;
    int minuto = 0;
    int hora = 0;
    int i,R,S,opt;
    int ch,setatt,win,winner,setregistro;
    char marked[20];
    setatt=0;
    R=0;
    setregistro=0;
    
    Times[0].score = 0;
	Times[1].score = 0;
	Times[0].sets = 0;
	Times[1].sets = 0;
	
    while (1)
	 {
        printf("\t\t\t%dh : %dmin : %dseg\r", hora, minuto, segundo);
        printf("%d°SET:\r",setatt+1);
        setregistro= setatt+1;
        Sleep(50); // O parâmetro 1000 milisegundos equivale a 1 segundo.(No caso 50 milisegundos)
        
        segundo++;//Relógio
        if (segundo == 60) 
		{
            segundo = 0;  
            minuto++;
        }   
        if (minuto == 60) 
		{
          	minuto = 0;  
            hora++;
        }
        
		if ( kbhit())
		{
			ch = getch();
			if(ch==115)
			{
				printf("\n\n======================(Partida Interrompida)===========================\n\n");
				system("pause"); 
		      	system("cls");
		      	break;
				
			}	
	    }
	    
	    
	    srand((unsigned)clock());
	   
		R=1+(rand()%20);
	    	    
	    
	    	
		if ( R==1 )
        {
			 printf("");
	         printf("\n-----------------------------------\n");
			 printf("Ponto efetuado!\n");
			 
			 S=1+(rand()%10);
			 
	         if ( S >= 1&& S <= 5 )
	        {
					Times[0].score++;
					printf("\n-%s\n",Times[0].teamName);
					printf("=============================(Placar)==================================\n");
					printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
					printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
					printf("=======================================================================\n");	
					strcpy ( marked, Times[0].teamName );
							
			}
			if ( S >= 6&& S <= 10 )
	        {
					Times[1].score++;
					printf("\n-%s\n",Times[1].teamName);
					printf("=============================(Placar)==================================\n");
					printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
					printf("SETS:                   %d  ...........  %d                 \n",Times[0].sets,Times[1].sets);
					printf("=======================================================================\n");
					strcpy ( marked, Times[1].teamName );
			}
        
		matchreport( segundo, minuto, hora, setregistro, marked);
		setatt=setatt+scorewin(Times[0].score,Times[1].score);
	 	winner=scorewin(Times[0].score,Times[1].score);
		win=matchwin(Times[0].sets,Times[1].sets) ;
		win=tiebreak (Times[0].sets,Times[1].sets,Times[0].score,Times[1].score);
				
		c++;
		
		if ( win == 1 )
		{
			win=0;
			system("pause"); // Comando que pausa a execução do programa.
      		system("cls");  // Limpa Terminal
			break;
        }
        
        } 
        
    }
}


int scorewin(int score1,int score2) //Função de vitória do set.
{	

	int result;
	result=0;

	
	if ((score2-score1)>=2||(score1-score2)>=2)
	{
		if (score1>=25||score2>=25)
		{
		
		if	(score1>score2)
		{
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
			printf("\n%s  ganhou o set\n",Times[0].teamName);
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
			Times[0].sets++;
			printf("=============================(Placar)==================================\n");
			printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
			printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
			printf("=======================================================================\n");			
			result=1;
			
			strcpy ( matchmarked, Times[0].teamName );
			MatchResults(matchmarked);
			Times[0].score = 0;
			Times[1].score = 0;
			
		}
		else 
		{
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		    printf("\n%s  ganhou o set\n",Times[1].teamName);
		    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		    
			Times[1].sets++;
			printf("=============================(Placar)==================================\n");
			printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
			printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
			printf("=======================================================================\n");		
			result=1;
			
			strcpy (matchmarked, Times[1].teamName );
			MatchResults(matchmarked);
			Times[0].score = 0;
			Times[1].score = 0;	
		}
		}	
    }
	
	
	return(result);

}
int matchwin(int set1,int set2) //Função da vitória da partida.
{	

	int setresult;
	
	
	
	if (set1>=3||set2>=3)
	{
	
		
		if	(set1>set2)
		{
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
			printf("\n\n%s  ganhou a partida\n\n\n",Times[0].teamName);
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
			setresult=1;
			Times[0].sets = 0;
			Times[1].sets = 0;
			
			
			
		}
		else 
		{
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		    printf("\n\n%s ganhou a partida\n\n\n",Times[1].teamName);
		    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		    setresult=1;
			Times[0].sets = 0;
			Times[1].sets = 0;
			
			
			
		}
			
    }
    		
	return(setresult);

}

int tiebreak (int set1, int set2, int score1, int score2) //Função do Tie-Break.
{

	int fivematch;
	
	if ( Times[0].sets==2&&Times[1].sets==2)
	{
		fivematch=0;
		if ((score2-score1)>=2||(score1-score2)>=2)	
			if (score1>=15||score2>=15)
			if	(score1>score2)
			{
				printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
				printf("\n%s  ganhou a partida!!\n",Times[0].teamName);
				printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
				Times[0].sets++;
				printf("=============================(Placar)==================================\n");
				printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
				printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
				printf("=======================================================================\n");			
				fivematch=1;
				strcpy(matchmarked,Times[0].teamName);
				MatchResults(matchmarked);
				Times[0].score = 0;
				Times[1].score = 0;
					
				
			}
		else 
		{
		    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
			printf("\n%s  ganhou a partida!!\n",Times[1].teamName);
			printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		    
			Times[1].sets++;
			printf("=============================(Placar)==================================\n");
			printf("Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
			printf("SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
			printf("=======================================================================\n");	
			fivematch=1;
			strcpy(matchmarked,Times[1].teamName);
			MatchResults(matchmarked);
			Times[0].score = 0;
			Times[1].score = 0;
			
			
		}
	}	
		
 	return(fivematch);
	
}

void Organizer () //Organizador por Ordem Alfabética
{
	int i, j, a,m,n,o,p,q;

	char players[MAX_PLAYERS][100], copy[100];

	for ( m = 0; m < 2;m++)  //Comando que realiza uma cópia do vetor de cadastro de jogadores.
		for( n =0; n < MAX_PLAYERS;n++ )
			strcpy(Times[m].alfaplayers[n],Times[m].players[n]);

	for ( a = 0; a < 2;a++) //Comando que compara e realoca os nomes em ordem alfabética.
		for ( i = 0; i < (MAX_PLAYERS-1) ; i ++ ) 
   			for( j = i + 1; j < MAX_PLAYERS; j ++ )

      /* strcmp 
     retorna = 0, caso a = b
     retorna > 0, caso a > b
     retorna < 0, caso a < b
      */

    if ( strcmp( Times[a].alfaplayers[i], Times[a].alfaplayers[j] ) > 0 )
	{
       /* strcpy
       copia de string 
       strcpy ( VarRecebe, VarEntrega )
        */
        strcpy ( copy, Times[a].alfaplayers[i] );
        strcpy( Times[a].alfaplayers[i], Times[a].alfaplayers[j] );
        strcpy( Times[a].alfaplayers[j], copy) ;
        
        
	for( q = 0; q < MAX_TEAM;q++)       //Comando que compara o vetor Organizado com o vetor original para manter a ordenação de camisas em relação aos jogadores.
		for ( o = 0; o < MAX_PLAYERS;o++)
			for( p =0; p < MAX_PLAYERS;p++ )
			
        	if ( strcmp (Times[q].players[o],Times[q].alfaplayers[p] ) == 0 )
			{
				Times[q].alfatshirt[p]=Times[q].tshirt[o];
			}
    }
	for ( i = 0; i < MAX_TEAM;i++)
		{
				printf("----------------------------------------------------\n");		
				printf("---------------------%s-----------------------------\n",Times[i].teamName);
				printf("----------------------------------------------------\n");
						for ( j = 0; j < MAX_PLAYERS;j++)
				    		{
							    	printf("O nome do jogador é %s\n",Times[i].alfaplayers[j]);
									printf("O número da camisa do  jogador é %d\n",Times[i].alfatshirt[j]);
							}		
		}
	printf("----------------------------------------------------\n");						
}
void organizeTshirt()
{
	int i,j,k,m,n,o,p,q;
	int temp;	
	
	for ( m = 0; m < 2;m++)
		for( n =0; n < MAX_PLAYERS;n++ )
			Times[m].alfatshirt[n]=Times[m].tshirt[n];	
	
	
	for( k= 0; k < MAX_TEAM;k++ )	
    	for (i = 0; i < MAX_PLAYERS; i++)
    	{
       		for (j = i; j < MAX_PLAYERS; j++)
        	{
            	if (Times[k].alfatshirt[i] > Times[k].alfatshirt[j])
            	{
            	    temp = Times[k].alfatshirt[i];
            	    Times[k].alfatshirt[i] = Times[k].alfatshirt[j];
            	    Times[k].alfatshirt[j] = temp;
            	}
        	}
    	}
    for( q = 0; q < MAX_TEAM;q++)       
		for ( o = 0; o < MAX_PLAYERS;o++)
			for( p =0; p < MAX_PLAYERS;p++ )
			
        		if ( Times[q].alfatshirt[o]-Times[q].tshirt[p]==0 ) 
				{
					strcpy (Times[q].alfaplayers[o],Times[q].players[p]);
				}
    
    
    
    for ( i = 0; i < MAX_TEAM;i++)
    {
	
				
					printf("----------------------------------------------------\n");		
					printf("---------------------%s-----------------------------\n",Times[i].teamName);
					printf("----------------------------------------------------\n");
						for ( j = 0; j < MAX_PLAYERS;j++)
						{
							printf("O nome do jogador é %s\n",Times[i].alfaplayers[j]);
							printf("O número da camisa do  jogador é %d\n",Times[i].alfatshirt[j]);
						}
								

	}
	printf("----------------------------------------------------\n");
}

void matchreport ( int second, int minute, int hour, int setattresul, char teampointer[20]) //Função de criação e adição de informação em arquivo.

{
	int i,j;
	i=0;
	j=0;

	
	FILE *PontArq;
	PontArq = fopen("matchreport.txt","a");	
	
if( c==0 )
	
	{
	
	fprintf(PontArq,"=======================================================================\n");
	fprintf(PontArq,"=====================//Voleyball Companion Guide//=====================\n");
	fprintf(PontArq,"=======================================================================\n");
	fprintf(PontArq,"................%s\t      X        \t%s...................\n",Times[0].teamName,Times[1].teamName);
	fprintf(PontArq,"-----------------------------------------------------------------------\n");
	
		for ( j = 0; j < MAX_PLAYERS;j++)
			{
				
	     		fprintf(PontArq,"..Jogador %s  \tCamisa \t %d...Jogador %s      \tCamisa \t %d ..\n\n",Times[0].players[j],Times[0].tshirt[j],Times[1].players[j],Times[1].tshirt[j]);
	     		
						
			}
		
	}
	
	
	fprintf(PontArq,"===========================//Match-Report//============================\n");
	fprintf(PontArq,"=======================================================================\n");
	fprintf(PontArq,"-----------------------------------------------------------------------\n");
	fprintf(PontArq," %d° SET                                                               \n",setattresul);
	fprintf(PontArq," %dh : %dmin : %dseg                                                   \n",hour, minute, second-1); 
	fprintf(PontArq,"-----------------------------------------------------------------------\n");
	fprintf(PontArq," PONTO EFETUADO!!!!                                                     \n");
	fprintf(PontArq,"    %s                                                                  \n",teampointer); 
	fprintf(PontArq,"=============================(Placar)==================================\n");
	fprintf(PontArq,"Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
	fprintf(PontArq,"SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
	fprintf(PontArq,"=======================================================================\n");
	fprintf(PontArq,"-----------------------------------------------------------------------\n");
	
	
	fclose (PontArq);

	
}

void MatchResults(char matchmarkedwinner[50]) //Função de adição ao arquivo informação de vitória.
{
	

	FILE *PontArq;
	PontArq = fopen("matchreport.txt","a");	
	
	{
		
		fprintf(PontArq,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		fprintf(PontArq,"%s  ganhou o set                                              \n",matchmarkedwinner); 
		fprintf(PontArq,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		fprintf(PontArq,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		fprintf(PontArq,"=============================(Placar)==================================\n");
		fprintf(PontArq,"Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
		fprintf(PontArq,"SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
		fprintf(PontArq,"=======================================================================\n");
		
	}	
		
	
	if ( Times[0].sets==3&&Times[1].sets != 3||Times[1].sets==3&&Times[0].sets!=3 )	
	{
		
		fprintf(PontArq,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		fprintf(PontArq,"%s  ganhou a partida!!!                                              \n",matchmarkedwinner); 
		fprintf(PontArq,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		fprintf(PontArq,"=============================(Placar)==================================\n");
		fprintf(PontArq,"Placar: %s  %d Ponto(s).........%s  %d Ponto(s)\n", Times[0].teamName,Times[0].score, Times[1].teamName,Times[1].score);
		fprintf(PontArq,"SETS:                    %d ...........  %d                 \n",Times[0].sets,Times[1].sets);
		fprintf(PontArq,"=======================================================================\n");
		
		
	}	
	
		
	fclose(PontArq);
}

 // Função campo de Volley
void VolleyCamp (){
     
      int i;
      
     
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls"); 
    // Definindo a cor verde para as bordas
    // Linha superior
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf("\r\r ");
    printf("\r                                   \r\n");
    printf("\r     -------------------------     \r\n");
   
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED);    
    printf("|");    
        printf("                         |");    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\t 24m de Altura.\n");
     for (i = 0; i < 6; i++){
      SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED);    
    printf("|");    

        printf("                         |");    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" \n");
}
   
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // Linha do meio
    {
      SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_BLUE);
    printf("   ---------------------------   ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    printf(" \n");}
     
      for (i = 0; i < 3; i++){
     
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");  
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED);    
    printf("|");    

        printf("                         |");    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf(" ");
    printf(" ");    
    printf(" ");  
      printf(" \n");
}
   
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    {
      SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_BLUE);
    printf(" --------------------------- ");
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    printf(" ");
    printf(" ");
    printf(" \n");}
    for (i = 0; i < 3; i++){
     
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED);    
    printf("|");    

        printf("                         |");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" \n");
}
   
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
   
    {
      SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_RED + BACKGROUND_BLUE);
    printf("   ---------------------------   ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    printf(" \n");}
     
      for (i = 0; i < 6; i++){
     
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN + BACKGROUND_RED);    
    printf("|");    

        printf("                         |");    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);    
    printf(" ");
    printf(" ");
    printf(" ");    
    printf(" \n");
}
     
    // Linha inferior
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    printf("\r     -------------------------     \r\n");
    printf("\r                                   \r\n");
   

    // Restaurando as cores padr o do console
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\t 16m de Largura.\n");
	system("pause");
	system("cls");
    
}

void reportmanegement(void) //Função para leitura do arquivo pelo terminal.
{
  FILE *PontArq;
  char texto_str[80];
  
	
  //Abrindo o matchreport em modo "leitura"
  PontArq = fopen("matchreport.txt","r");
  
  //enquanto não for fim de arquivo o looping será executado
    while(fgets(texto_str, 80, PontArq) != NULL)
  		printf("%s", texto_str);
  
  //fechando o arquivo
  fclose(PontArq);
  
  getch();
 
}

void reportclear (void) //Função de limpeza de arquivo.
{
	int descision;
	descision=0;

    printf("Deseja limpar o registro da partida?  (1) Sim, (2)Não.\n");
    scanf( "%d",&descision);
     
    if ( descision == 1)
    {
        FILE *PontArq;
    	PontArq = fopen("matchreport.txt","w");
    	fprintf(PontArq,"                                                                                    \n");
    	fclose(PontArq);
    }else
     	
     	system("pause"); 
       	system("cls");
		
}	 


 //Logotipo do programa.
void logo (void)
{
	printf(" _____     _ _         _____     _ _    _____                       _         \n");	
	printf("|  |  |___| | |___ _ _| __  |___| | |  |     |___ _____ ___ ___ ___|_|___ ___ \n");
	printf("|  |  | . | | | -_| | | __ -| .'| | |  |   --| . |     | . | .'|   | | . |   |\n");
	printf(" \\___/|___|_|_|___|_  |_____|__,|_|_|  |_____|___|_|_|_|  _|__,|_|_|_|___|_|_|\n");
	printf("                  |___|                                |_|                    \n");
	                     
	printf(" _____     _   _     \n");
	printf("|   __|_ _|_|_| |___ \n");
	printf("|  |  | | | | . | -_|\n");
	printf("|_____|___|_|___|___|\n\n\n");
	
	                                                                             
	printf("Projeto Integrador de Unidade Curricular ");

	getch();
	system("cls");

}











