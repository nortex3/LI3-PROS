#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers/CatalogoProdutos.h"
#include "headers/CatalogoClientes.h"
#include "headers/Faturacao.h"
#include "headers/GestaoFilial.h"
#include "headers/avlF.h"
#include "headers/avl.h"
#include "headers/avlFilial.h"
#include "headers/leitura.h"

extern Clientes cli;
extern Produtos pro;
extern FaturacaoGlobal fg;
extern GF gf;

void printQuerie2(ConjProds prods, int contador, int index);
void printQuerie4(ConjProdsF prods, int contador, int index);
void printQuerie7(ConjClisGF cligf, int contador, int index);
void printQuerie8(ConjClisGF cligf, int contador, int index);
void printQuerie9(ConjClisGF cligf, int contador, int index);
void printClientesAux(ConjClientes clientes, int contador, int index);


void querie1Clientes(){
	free(cli);
	free(gf);
	Leitura ler = inicializaLeitura();
	cli = InicializaClientes();
	gf = InicializaGestFil();
	ler = leituraCli(cli, gf, "Clientes.txt");
	printf("Nome do ficheiro: %s\n"
		   " Número de linhas lidas: %d\n"
		   " Número de linhas correctas: %d\n"
		   " Número de linhas erradas: %d\n",getNomeFile(ler), getLinhasLidas(ler), getLinhasBem(ler), getLinhasMal(ler));
	free(ler);
}

void querie1Produtos(){
	free(fg);
	free(pro);
	Leitura ler = inicializaLeitura();
	fg = InicializaTotalProdutos();
	pro = InicializaProdutos();
	ler = leituraPro(fg, pro, "Produtos.txt");
	printf("Nome do ficheiro: %s\n"
		   " Número de linhas lidas: %d\n"
		   " Número de linhas correctas: %d\n"
		   " Número de linhas erradas: %d\n",getNomeFile(ler), getLinhasLidas(ler), getLinhasBem(ler), getLinhasMal(ler));
	free(ler);
}

void querie1Vendas(){
	Leitura ler = inicializaLeitura();
	ler = leituraVendas(gf, fg, pro, cli, "Vendas_1M.txt");
	printf("Nome do ficheiro: %s\n"
		   " Número de linhas lidas: %d\n"
		   " Número de linhas correctas: %d\n"
		   " Número de linhas erradas: %d\n",getNomeFile(ler), getLinhasLidas(ler), getLinhasBem(ler), getLinhasMal(ler));
	free(ler);
}

void querie2(char c){
    int aux = 0;
    ConjProds prods = toArrayProdutos(pro, c);
	printf("\033c");
    printQuerie2(prods, aux, aux);
}


void querie3(int mes,char* codPro,int modo){

	double res[4];
	double resF[12];
	int r=0;
	if(modo==1){
		r=TotalVendasTotalFaturadoGlobal(fg,mes, codPro,res,modo);
		if(r==1) printf("Codigo Inexistente\n");
		else{
		printf("Total vendas em modo promoção: %d\n",(int)res[0] );
		printf("Total vendas em modo normal: %d\n",(int)res[1] );
		printf("Total faturado em modo promoção: %f\n",res[2] );
		printf("Total faturado em modo normal: %f\n",res[3] );
	}
	}else{

		r=TotalVendasTotalFaturadoGlobal(fg,mes, codPro,resF,modo);
		if(r==1) printf("Codigo Inexistente\n");
		else{
		printf("-----------------Filial 1------------------------\n");

		printf("Total vendas em modo promoção na filial1: %d\n",(int)resF[0] );
		printf("Total vendas em modo normal na filial1: %d\n",(int)resF[1] );
		printf("Total faturado em modo promoção na filial1: %f\n",resF[6] );
		printf("Total faturado em modo normal na filial1: %f\n\n",resF[7] );
		printf("-----------------Filial 2------------------------\n");
		printf("Total vendas em modo promoção na filial2: %d\n",(int)resF[2] );
		printf("Total vendas em modo normal na filial2: %d\n",(int)resF[3] );
		printf("Total faturado em modo promoção na filial2: %f\n",resF[8] );
		printf("Total faturado em modo normal na filial2: %f\n\n",resF[9] );

		printf("-----------------Filial 3------------------------\n");

		printf("Total vendas em modo promoção na filial3: %d\n",(int)resF[5] );
		printf("Total vendas em modo normal na filial3: %d\n",(int)resF[6] );
		printf("Total faturado em modo promoção na filial3: %f\n",resF[10] );
		printf("Total faturado em modo normal na filial3: %f\n",resF[11] );
	}
}


}
void querie4(char modo,char filial){
    int aux = 0;
    ConjProdsF prods;
    if (modo==1){
    prods = toArrayProdutosNaoVendidos(fg);
	printf("\033c");
    printQuerie4(prods, aux, aux);
    }
    else {
        switch(filial){
			case 1:
				prods = toArrayProdutosNaoVendidosF1(fg);
                printf("\033c");
                printQuerie4(prods, aux, aux);
				break;
			case 2:
                prods = toArrayProdutosNaoVendidosF2(fg);
                printf("\033c");
                printQuerie4(prods, aux, aux);
				break;
            case 3:
                prods = toArrayProdutosNaoVendidosF3(fg);
                printf("\033c");
                printQuerie4(prods, aux, aux);
				break;
            default:
				printf("\033c");
				printf("Opção inválida.\n");
		}
    }
}

void querie5(char *s){
	char aux;
	int mes[36];
	int i=0,j=0;
	int Nexiste=0;
	for(i=0;i<36;i++){
		mes[i]=0;
	}

	Nexiste=CalculaTotais(gf,s,mes);
	if(Nexiste==1) printf("Cliente Inexistente\n");
	else{
		printf("###########    Produtos comprados pelo cliente %s   ###########\n", s);
		printf("##################################################################\n");
		printf("##\tMês\t|    Filial 1   |   Filial 2    |   Filial 3    ##\n");
		printf("##################################################################\n");
		printf("##\t1\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[0],mes[1],mes[2]);
		printf("##\t2\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[3],mes[4],mes[5]);
		printf("##\t3\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[6],mes[7],mes[8]);
		printf("##\t4\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[9],mes[10],mes[11]);
		printf("##\t5\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[12],mes[13],mes[14]);
		printf("##\t6\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[15],mes[16],mes[17]);
		printf("##\t7\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[18],mes[19],mes[20]);
		printf("##\t8\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[21],mes[22],mes[23]);
		printf("##\t9\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[24],mes[25],mes[26]);
		printf("##\t10\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[27],mes[28],mes[29]);
		printf("##\t11\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[30],mes[31],mes[32]);
		printf("##\t12\t|\t%d\t|\t%d\t|\t%d\t##\n",mes[33],mes[34],mes[35]);
		printf("##################################################################\n");
		printf("Prima 'Enter' para sair.\n");
		getchar();
		j = scanf("%c",&aux);
		if(aux== '\n'){
			printf("\033c");
		}
		else{
			printf("\033c");
			querie5(s);
		}
	}
}

void querie6(int mesi,int mesf){
	double res[2];
	CalculaTotalVendasEFaturado(fg,mesi,mesf,res);
	printf("Total de vendas, entre mês %d e mês %d : %d\n",mesi, mesf,(int)res[0] );
	printf("Total faturado, entre mês %d e mês %d : %f\n",mesi, mesf,res[1] );


}

void querie7(){
	int aux = 0;
	printf("\033c");
	ConjClisGF tmp = percorreClientes(gf);
	printQuerie7(tmp, aux, aux);

}
void querie8(char* s,int filial,char tipo){
    int aux =0;
    printf("\033c");
    ConjClisGF tmp = percorreClientes8(gf,s,filial,tipo);
    if(tmp!=NULL){
		printQuerie8(tmp, aux, aux);}
	else{
	 printf("\033c");
	 printf("Produto Inexistente ou Nao vendido com os dados inseridos.\n");
	}

}
void querie9(char* s,int mes){

	int aux = 0;
	printf("\033c");
	ConjClisGF tmp = percorreClientes9(gf,mes,s);
	if(tmp!=NULL)
		printQuerie9(tmp, aux, aux);
	else{
	 printf("\033c");
	 printf("Cliente Inexistente.\n");
	}
}
void querie10(){}
void querie11(char *s){}
void querie12(){}


void printQuerie2(ConjProds prods, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################\n");
    for (i=0;i < 20 && index < retornaTamanhoPro(prods); i++){
			printf("# %s                                       #\n",retornaElementoPro(prods,index));
			contador++;
			index++;
	}
	printf("################################################\n");
	printf("# Número de linhas começadas por '%c': %d     #\n",retornaPrimeiraLetraPro(prods,0), retornaTamanhoPro(prods));
	printf("################################################\n");
	printf("# 1. Continuar.                                #\n");
	printf("# 2. Retroceder.                               #\n");
	printf("# 0. Sair.                                     #\n");
	printf("################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanhoPro(prods)){
			printf("\033c");
			printQuerie2(prods, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanhoPro(prods)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printQuerie2(prods, contador-20, index-20);
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printQuerie2(prods, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printQuerie2(prods, contador-20, index-20);
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printQuerie2(prods, contador-20, index-20);
		}
	}
}

void printQuerie4(ConjProdsF prods, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################\n");
    for (i=0;i < 20 && index < retornaTamanhoProF(prods); i++){
			printf("# %s                                       #\n",retornaElementoProF(prods,index));
			contador++;
			index++;
	}
	printf("################################################\n");
	printf("# Total de Produtos nao vendidos: %d          #\n", retornaTamanhoProF(prods));
	printf("################################################\n");
	printf("# 1. Continuar.                                #\n");
	printf("# 2. Retroceder.                               #\n");
	printf("# 0. Sair.                                     #\n");
	printf("################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanhoProF(prods)){
			printf("\033c");
			printQuerie4(prods, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanhoProF(prods)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printQuerie4(prods, contador-20, index-20);
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printQuerie4(prods, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printQuerie4(prods, contador-20, index-20);
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printQuerie4(prods, contador-20, index-20);
		}
	}
}

void printQuerie7(ConjClisGF cligf, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################################\n");
    for (i=0;i < 20 && index < retornaTamanhoConjClisGF(cligf); i++){
			printf("# %s                                                        #\n",retornaElementoConjClisGF(cligf,index));
			contador++;
			index++;
	}
	printf("################################################################\n");
	printf("# Número de clientes que compraram em todas as filiais: %d  #\n", retornaTamanhoConjClisGF(cligf));
	printf("################################################################\n");
	printf("# 1. Continuar.                                                #\n");
	printf("# 2. Retroceder.                                               #\n");
	printf("# 0. Sair.                                                     #\n");
	printf("################################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printQuerie7(cligf, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printQuerie7(cligf, contador-20, index-20);
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printQuerie7(cligf, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printQuerie7(cligf, contador-20, index-20);
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printQuerie7(cligf, contador-20, index-20);
		}
	}
}

void printQuerie9(ConjClisGF cligf, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################\n");
    for (i=0;i < 20 && index < retornaTamanhoConjClisGF(cligf); i++){
			printf("# %s                                       #\n",retornaElementoConjClisGF(cligf,index));
			contador++;
			index++;
	}
	printf("################################################################\n");
	printf("# Número de produtos comprados: %d                          #\n", retornaTamanhoConjClisGF(cligf));
	printf("################################################################\n");
	printf("# 1. Continuar.                                                #\n");
	printf("# 2. Retroceder.                                               #\n");
	printf("# 0. Sair.                                                     #\n");
	printf("################################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printQuerie9(cligf, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printQuerie9(cligf, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
	}
}

void printQuerie8(ConjClisGF cligf, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################\n");
    for (i=0;i < 20 && index < retornaTamanhoConjClisGF(cligf); i++){
			printf("# %s                                       #\n",retornaElementoConjClisGF(cligf,index));
			contador++;
			index++;
	}
	printf("################################################################\n");
	printf("# Número de clientes que compraram o produto: %d                          #\n", retornaTamanhoConjClisGF(cligf));
	printf("################################################################\n");
	printf("# 1. Continuar.                                                #\n");
	printf("# 2. Retroceder.                                               #\n");
	printf("# 0. Sair.                                                     #\n");
	printf("################################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printQuerie9(cligf, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanhoConjClisGF(cligf)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printQuerie9(cligf, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printQuerie9(cligf, contador-retornaTamanhoConjClisGF(cligf), index-retornaTamanhoConjClisGF(cligf));
		}
	}
}

void printClientes(char c){
    int aux = 0;
    ConjClientes clientes = toArrayClientes(cli, c);
	printf("\033c");
    printClientesAux(clientes, aux, aux);
}

void printClientesAux(ConjClientes clientes, int contador, int index){
	int n = 0, i,c = 0;

	printf("################## GEREVENDAS ##################\n");
    for (i=0;i < 20 && index < retornaTamanho(clientes); i++){
			printf("# %s                                        #\n",retornaElemento(clientes,index));
			contador++;
			index++;
	}
	printf("################################################\n");
	printf("# Número de linhas começadas por '%c': %d      #\n",retornaPrimeiraLetra(clientes,1), retornaTamanho(clientes));
	printf("################################################\n");
	printf("# 1. Continuar.                                #\n");
	printf("# 2. Retroceder.                               #\n");
	printf("# 0. Sair.                                     #\n");
	printf("################################################\n");
	printf(">");
	n = scanf("%d",&c);
	if(n > 0){
		if(c == 1 && contador != retornaTamanho(clientes)){
			printf("\033c");
			printClientesAux(clientes, contador, index++);
		}
		else if(c == 1 && contador == retornaTamanho(clientes)){
			printf("\033c");
			printf("Impossível continuar.\n");
			printClientesAux(clientes, contador-20, index-20);
		}
		else if(c == 2 && (contador-40) >= 0){
			printf("\033c");
			printClientesAux(clientes, contador-40, index-40);
		}
		else if(c == 2 && (contador-40) <= 0){
			printf("\033c");
			printf("Impossível retroceder.\n");
			printClientesAux(clientes, contador-20, index-20);
		}
		else if(c == 0){
			printf("\033c");
		}
		else{
			printf("\033c");
			printf("Comando inválido\n");
			printClientesAux(clientes, contador-20, index-20);
		}
	}
}

