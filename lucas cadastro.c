#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CPFB 11
#define MOV 20
#define qtdcliente 10



FILE *arquivob;

void abrirarquivowb() 
{
    arquivob = fopen ("Arquivo.txt","w+b");
}

void abrirarquivorb()
{
    arquivob = fopen ("Arquivo.txt","r+b");
}

void fechararquivo()
{
    fclose (arquivob);
}










//------------------------------------------------------ ESTRUTURAS--------------------------------------------------
typedef struct{

    char TIPO[25];
    float VALOR;
	int contValor,contTipo;
}transacoes;
//------------------------------------------------------ ESTRUTURAS-------------------------------------------------
typedef struct{

    char nconta[14];
    float SALDO;
    transacoes MOVIMENTACAO[MOV];

}conta;

//------------------------------------------------------ ESTRUTURAS----------------------------------------------------------
typedef struct{

    char CPF[CPFB];// usar para gerar conta
    int RG;
    char NC[30];    // usaar para gerar conta
    conta CONTACLIENTE;
}cadastro;

//------------------------------------------------------ ESTRUTURAS----------------------------------------------------------

//CAMPO DE DECLARACAO DE FUNCOES--------------------------------------------------------------------------------------------

void menu();
int cadastrarcliente();
void abrirconta();

cadastro cliente[qtdcliente];// quantidade de clientes
transacoes usuariobanco[qtdcliente];

float deposito();
float saquesemconta();
float transferenciabancaria();
float saldoBancario();
float extratob();
float pagarboleto();
float extratobancario();

//CAMPO DE DECLARACAO DE FUNCOES--------------------------------------------------------------------------------------------



int main(){//FUNCAO PRINCIPAL

    menu();
    return 0;

}

void menu(){

    int opc=1;

    while(opc!=0){
		printf("\n");
        printf("\n\t1-CADASTRAR CLIENTE\n");//ok
        printf("--------------------------------------\n");
        printf("\t2-DEPOSITO\n");//ok
        printf("--------------------------------------\n");
        printf("\t3-SAQUES\n");//ok
        printf("--------------------------------------\n");
        printf("\t4-TRANSFERENCIA\n");//ok
        printf("--------------------------------------\n");
        printf("\t5-SALDO\n");//ok
        printf("--------------------------------------\n");
        printf("\t6-ABRIR CONTA \n");
        printf("--------------------------------------\n");
        printf("\t7-PAGAR CONTAS\n");
        printf("--------------------------------------\n");
        printf("\t8-EXTRATO BANCARIO\n");
        printf("--------------------------------------\n");
        printf("\t0-SAIR\n");//ok
        printf("--------------------------------------\n");
        printf("\tOPCAO: ");
        scanf("%d",&opc);
   		printf("\n\n");
       

            switch(opc){

                case 1:
                    cadastrarcliente();
                break;

                case 2:
                    deposito();
                break;

                case 3:
                    saquesemconta();
                break;

                case 4:
                    transferenciabancaria();
                break;

                case 5:
                    saldoBancario();
                break;
                
                case 6:
                	abrirconta();
                break;
                
                case 7:
                	pagarboleto();
                break;
                
                case 8:
                	extratobancario();
				break;
				
                case 0:
                break;


            }

        }

}

int cadastrarcliente()
{

    char cf ='s',ds,nome[30];
    int novo=0,i;


    abrirarquivorb();
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
	novo++;

    }

    fechararquivo();
    
//-----------------------------------------
        printf("\nCadastrar cliente\n");
        printf("\n\n");
      
        while(cf!='n'){
		fflush(stdin);
		printf("-------------------------------------------\n");
        printf("Informe o nome completo: ");
        gets(cliente[novo].NC);
        printf("-------------------------------------------\n");
		printf("Informe o CPF: ");
        gets(cliente[novo].CPF);
        printf("-------------------------------------------\n");
		printf("Informe o RG:  ");
        scanf("%d",&cliente[novo].RG);
    	

        cf='n';
        
        }


    novo++;

//-----------------------------------SALVAR-----------------
    abrirarquivowb();

    fwrite(cliente,sizeof(cadastro),novo,arquivob);

    fechararquivo();

return 0;

    }


void abrirconta(){
	
		char nome[30],cpf[CPFB];
		int novo =0,i,cod=0,c,end;
	
		abrirarquivorb();
			
	   	while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
				novo++;
				 }

    	fechararquivo();
    	
    	/* TESTAR QUEM FOI CADASTRADO
    	for(i=0;i<novo;i++){
    		printf("-------------------------------------------\n");
    		printf("%s\n",cliente[i].NC);
    		printf("-------------------------------------------\n");
    		printf("%s\n",cliente[i].CPF);
		}
    	*/
		fflush(stdin);
		printf("\n-------------------------------------------\n");
		printf("Informar o CPF: ");
		gets(cpf);
		printf("\n-------------------------------------------\n");
		
	
		for(i=0;i<10;i++){
			
		if(	(strcmp(cpf,cliente[i].CPF))==0){
				cod+=1;// caso o cod seja igual a 2, significa que o CPF está duplicado
				end=i;
			}
			
		}
			
			if(cod==1){
			//--------------------------------------------------------------	
				strcpy(nome, cliente[end].NC);
		        nome[3]='\0';
		        strcat(nome,cliente[end].CPF);
		        strcpy(cliente[end].CONTACLIENTE.nconta,nome);
		        cliente[end].CONTACLIENTE.SALDO=0;
		        printf("Seu numero de conta: %s",cliente[end].CONTACLIENTE.nconta);	
				
			//--------------------------------------------------------------
			}
			else{
			
				printf("ERRO");
		
			}
   
  //---------------------------- GRAVAR AQUIVO-----------------------      
    abrirarquivowb();
	fwrite(cliente,sizeof(cadastro),novo,arquivob);
	fechararquivo();
	//---------------------------- GRAVAR AQUIVO-----------------------		
}

float deposito()
{
  
    int i,c,novo=0;
    char conta[15];
    float valor;
    
    
   //-------------------------CARREGAR ARQUIVO---------------------
    abrirarquivorb();
    
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
			novo++;
	}
	 
	fechararquivo();
	//----------------------CARREGAR ARQUIVO------------------------

	fflush(stdin);
	printf("-------------------------------------------\n");
    printf("A seguir informe o numero de sua conta: ");
    gets(conta);
   
    for(i=0;i<10;i++){

       		 c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

            if(c==0){
            
            
	            printf("%s\n",cliente[i].NC);
	            printf("%s\n",cliente[i].CPF);
	            printf("Seu saldo atual e: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
	            printf("\n\n");
	            printf("Insira o valor a ser depositado: ");
	            scanf("%f",&valor);
				cliente[i].CONTACLIENTE.SALDO  =  cliente[i].CONTACLIENTE.SALDO+valor;// ATUALIZAR SALDO--- modifiquei-- tirei o end e coloquei "i"
				
			//-------------------------------EXTRATO-----------------------------------------------------
				cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor].VALOR=valor;
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor++;
				strcpy(cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo].TIPO,"Deposito");
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo++;
			//-------------------------------EXTRATO-----------------------------------------------------	
			}
			
		}				

	//---------------------------- GRAVAR AQUIVO-----------------------
    abrirarquivowb();
	fwrite(cliente,sizeof(cadastro),novo,arquivob);
	fechararquivo();
	//---------------------------- GRAVAR AQUIVO-----------------------
}

float saquesemconta()
{//COPIADO CONTEURO DA FUNCAO DEPOSITO e MODIFICADO

    int i,c, novo =0;
    char conta[15];
    float saque;
    //-----------------------------------------
    abrirarquivorb();
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
	novo++;
	 }
	fechararquivo();
	//-------------------------------------------
	fflush(stdin);
    printf("A seguir informe o numero de sua conta:");
    gets(conta);

    for(i=0;i<10;i++){

        c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

            if(c==0){
            printf("%s\n",cliente[i].NC);
            printf("%s\n",cliente[i].CPF);
            printf("Seu saldo atual e: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
            printf("\n\n");
            printf("Insira o valor a ser SACADO: ");
            scanf("%f",&saque);

                if((saque>cliente[i].CONTACLIENTE.SALDO)||(cliente[i].CONTACLIENTE.SALDO==0)){
                    printf("SALDO INSUFICIENTE");
                    break;
                }else if(saque<=cliente[i].CONTACLIENTE.SALDO){
                    cliente[i].CONTACLIENTE.SALDO=cliente[i].CONTACLIENTE.SALDO-saque;
                    printf("SEU SALDO E: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
                }
              //-------------------------------EXTRATO-----------------------------------------------------  
                cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor].VALOR=saque;
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor++;
				strcpy(cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo].TIPO,"Saque");
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo++;
              //-------------------------------EXTRATO-----------------------------------------------------  

        }

    }

//-----------------------------------------------
	abrirarquivowb();

    fwrite(cliente,sizeof(cadastro),novo,arquivob);

    fechararquivo();	
//----------------------------------------------



}

float transferenciabancaria()
{// COPIADO O CONTEUDO DA FUNCAO saquesemconta E MODIFICADO

    int i,c,c2,j, novo =0, end;
    char conta[15],contadestino[15];
    float transferencia;

//-----------------------------------------
    abrirarquivorb();
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
		novo++;
	 }
		fechararquivo();
//-------------------------------------------
	fflush(stdin);
    printf("A seguir informe o numero de sua conta:");
    gets(conta);

    for(i=0;i<10;i++){

        c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

            if(c==0){
            	end = i;
            printf("%s\n",cliente[i].NC);
            printf("%s\n",cliente[i].CPF);
            printf("Seu saldo atual e: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
            printf("\n\n");
            printf("Insira o valor a ser TRANSFERIDO: ");
            scanf("%f",&transferencia);
		
            //VERIFICAR SE E POSSIVEL REALIZAR A TRANSFERENCIA
                if((transferencia>cliente[i].CONTACLIENTE.SALDO)||(cliente[i].CONTACLIENTE.SALDO==0)){
                    printf("SALDO INSUFICIENTE");
                    break;
                }
				if(transferencia<=cliente[i].CONTACLIENTE.SALDO){
               			                       
                 //-------------------------------EXTRATO-----------------------------------------------------      
                cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor].VALOR=transferencia;
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor++;
				strcpy(cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo].TIPO,"Transferencia");
				cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo++;
                 //-------------------------------EXTRATO-----------------------------------------------------     
                    
                    
                }
            fflush(stdin);
            //------------------------------------------------------
            printf("Informe a conta destino: ");
            gets(contadestino);

                    for(j=0;j<10;j++){ // PROCURAR CONTA DESTINO
                        c2=strcmp(contadestino,cliente[j].CONTACLIENTE.nconta);

                        if(c2==0){

                            cliente[j].CONTACLIENTE.SALDO=cliente[j].CONTACLIENTE.SALDO+transferencia;
								cliente[end].CONTACLIENTE.SALDO=cliente[end].CONTACLIENTE.SALDO-transferencia;// movido
                    			printf("SEU SALDO E: %.2f\n",cliente[end].CONTACLIENTE.SALDO);//movido
						//-------------------------------EXTRATO----------------------------------------------------- 
						
						cliente[j].CONTACLIENTE.MOVIMENTACAO[cliente[j].CONTACLIENTE.MOVIMENTACAO[j].contValor].VALOR=transferencia;
						cliente[j].CONTACLIENTE.MOVIMENTACAO[j].contValor++;
						strcpy(cliente[j].CONTACLIENTE.MOVIMENTACAO[cliente[j].CONTACLIENTE.MOVIMENTACAO[j].contTipo].TIPO,"TransferenciaR");
						cliente[j].CONTACLIENTE.MOVIMENTACAO[j].contTipo++;
						
						
						

                        }

                    }//SEGUNDO LAÇO FOR



            }// CONDICIONAL

    } // PRIMEIRO LAÇO FOR
    
    
    
    //-----------------------------------------------
	abrirarquivowb();

    fwrite(cliente,sizeof(cadastro),novo,arquivob);

    fechararquivo();	
//----------------------------------------------


}

float saldoBancario(){ //COPIADO O CODIGO DA FUNCAO DEPOSITO E MODIFICADO


    int i,c,novo =0;
    char conta[15];
//-----------------------------------------
    abrirarquivorb();
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
		novo++;
	 }
	fechararquivo();
//-------------------------------------------



	fflush(stdin);
    printf("A seguir informe o numero de sua conta:");
    gets(conta);
    for(i=0;i<10;i++){

        c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

            if(c==0){
            printf("%s\n",cliente[i].NC);
            printf("%s\n",cliente[i].CPF);
            printf("Seu saldo atual e: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
            printf("\n\n");


        }

    }
	
//---------------------------------------	
	abrirarquivowb();

    fwrite(cliente,sizeof(cadastro),novo,arquivob);

    fechararquivo();	
//--------------------------------------------
}

float pagarboleto(){
	
    int i,c,end,codbarras,novo=0;
    char conta[15];
    float valor;
   //----------------------------------------------
    abrirarquivorb();
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
	novo++;
	 }
	fechararquivo();
	//----------------------------------------------

	fflush(stdin);
    printf("A seguir informe o numero de sua conta:");
    gets(conta);
    
    for(i=0;i<10;i++){

       		 c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

            if(c==0){
		            printf("%s\n",cliente[i].NC);
		            printf("%s\n",cliente[i].CPF);
		            printf("Seu saldo atual e: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
		            printf("\n\n");
		            printf("Insira o codigo de barras: ");
		            scanf("%f",&codbarras);
		            printf("Informe o valor: ");
		            scanf("%f",&valor);
		            
		             if((valor>cliente[i].CONTACLIENTE.SALDO)||(cliente[i].CONTACLIENTE.SALDO==0)){
		              printf("SALDO INSUFICIENTE");
		              break;
		                    
			         }
			         
		 			if(valor<=cliente[i].CONTACLIENTE.SALDO){
                    cliente[i].CONTACLIENTE.SALDO=cliente[i].CONTACLIENTE.SALDO-valor;
                    printf("SEU SALDO E: %.2f\n",cliente[i].CONTACLIENTE.SALDO);
                    
			               //-------------------------------EXTRATO-----------------------------------------------------     
			                cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor].VALOR=valor;
							cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contValor++;
							strcpy(cliente[i].CONTACLIENTE.MOVIMENTACAO[cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo].TIPO,"Pagar Boletos");
							cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo++;
			               //-------------------------------EXTRATO-----------------------------------------------------     
			                    
			                    
			                	}
            
				}
				
				
    }

    


    abrirarquivowb();

    fwrite(cliente,sizeof(cadastro),novo,arquivob);

    fechararquivo();
	

}

float extratobancario(){
	
    int i,c,j,novo=0;
    char conta[15];
    float valor;

	
   //----------------------------------------------
   
    abrirarquivorb();
    
    while ((fread (&cliente[novo], sizeof (cadastro),1,arquivob) != NULL)){
    novo++;
	}
	 
	fechararquivo();
	//----------------------------------------------
	fflush(stdin);
    printf("A seguir informe o numero de sua conta:");
    gets(conta);
    
    for(i=0;i<10;i++){

    c=strcmp(conta,cliente[i].CONTACLIENTE.nconta);// STRCMP devolve numero inteiro

	            		if(c==0){
			            printf("%s\n",cliente[i].NC);
			            printf("%s\n",cliente[i].CPF);
			            
				        	for(j=0;j<cliente[i].CONTACLIENTE.MOVIMENTACAO[i].contTipo;j++){// modificado
					        printf("Operacao: %s / Valor: %.2f\n",cliente[i].CONTACLIENTE.MOVIMENTACAO[j].TIPO, cliente[i].CONTACLIENTE.MOVIMENTACAO[j].VALOR);	
				        				        		
							}
										 
					   	
					   }
		                   
	}
				
		
//-------------------------------------		
	abrirarquivowb();
	fwrite(cliente, sizeof(cadastro),novo,arquivob);
	fechararquivo();
		
//---------------------------------------		
		
		
}

