#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct sDataNascimento{      // criação de uma estrutura para Data de Nascimento
	int dia, mes, ano;
}DataNasc;

typedef struct sPessoa{      // criação de uma estrutura para dados do(a) Paciente/Pessoa
	char nome[50], sexo, cpf[11], bairro[20];
	int idade;
	DataNasc dataNasc;
}Pessoa;

typedef struct sTeste{      // criação de uma estrutura para o Teste
	Pessoa pessoa;
	int numIdentificacaoTeste;
	char resultadoTeste;
	char valido[4];
}Teste;

int calcularIdade(int diaPessoa, int mesPessoa, int anoPessoa){
	
	int  diaAtual, mesAtual, anoAtual, diferenca, i;
	char dataAtual[8], *separarData;
	
	_strdate(dataAtual); // salvando a data atual do computador na variável
	separarData = strtok (dataAtual,"/"); // Separando a string de dataAtual através das barras
	
	/* 
		o for roda 3 vezes, a 1º vez, a variável separarData tem o valor do mes atual( data em Inglês, inverte dia e mes ), 
		na 2º a variável separarData tem o valor do dia atual, e por último, a variável separarData tem o valor do ano atual.
	*/
	for(i=1; separarData != NULL; i++){
		if(i == 1)
			mesAtual = atoi(separarData); // se o for tiver na 1º vez, pega o mesAtual
		else if(i == 2) // se o for tiver na 2º vez, pega o diaAtual
			diaAtual = atoi(separarData);
		else if(i == 3) // se o for tiver na 3º vez, pega o dia atual
			anoAtual = atoi(separarData)+2000;

		separarData = strtok (NULL, "/"); // apenas arrumando a variável separarData para o proximo valor ( dia, mes ou ano ).
	}

	diferenca = 365*anoAtual + 30*mesAtual + diaAtual - 365*anoPessoa - 30*mesPessoa - diaPessoa; // cálculo da diferença para pegar a idade.
	
	return diferenca/365; // retornando a idade do paciente.
}

/*
	função para preencher os cadastros, recebendo o ponteiro de testes, o indíce onde o i deve começar,
	já que outros testes podem ter sido cadastrados anteriormente, então os novos devem ficar do i para
	frente. Por último, a quantidade total de testes cadastrados.
*/
void preencherCadastro(Teste* testes, int i, int countTestes){   
	
	printf("\n-------------------- CADASTRO --------------------\n");
	for(i;i<countTestes;i++){
		printf("\nDados do paciente %d\n", i+1);
		printf("\nNome completo do paciente: ");
		fflush(stdin);
		gets(testes[i].pessoa.nome);
		printf("CPF do paciente: ");
		fflush(stdin);
		gets(testes[i].pessoa.cpf);
		printf("---- Data de nascimento ----\n");
		printf("Dia: ");
		scanf("%d",&testes[i].pessoa.dataNasc.dia);
		printf("Mes: ");
		scanf("%d",&testes[i].pessoa.dataNasc.mes);
		printf("Ano: ");
		scanf("%d",&testes[i].pessoa.dataNasc.ano);
		// salvando a idade do paciente na estrutura Teste.Pessoa atual do for ( através do retorno da função calcularIdade )
		testes[i].pessoa.idade = calcularIdade(testes[i].pessoa.dataNasc.dia, testes[i].pessoa.dataNasc.mes, testes[i].pessoa.dataNasc.ano);
		printf("Idade: %d\n", testes[i].pessoa.idade);
		printf("sexo do paciente ( M ou F ): ");
		fflush(stdin);
		scanf("%c",&testes[i].pessoa.sexo);
		printf("Digite o bairro do paciente: ");
		fflush(stdin);
		gets(testes[i].pessoa.bairro);
		printf("Resultado do Teste de Covid do paciente ( P ou N ): ");
		fflush(stdin);
		scanf("%c",&testes[i].resultadoTeste);
		// inserindo o numero de identificacao do teste automaticamente pelo valor do i.
		testes[i].numIdentificacaoTeste = i+1;
		// validando o teste inicialmente com sim.
		strcpy(testes[i].valido, "sim");
	}
	
	system("cls");
	printf("\n-------------------- CADASTRO --------------------\n");
	printf("\nPaciente(s) cadastrado(s) com sucesso !\n");
	printf("\n--------------------------------------------------\n");
}

void exibirTestePorNome(Teste* testes, char nomeComparacao[50], int countTestes){
	
	int i;
	system("cls");
	
	printf("\n-------------------- DADOS --------------------\n");

	// o for irá percorrer todos os testes.
	for(i=0;i<countTestes;i++){
		if(strcmp(testes[i].pessoa.nome, nomeComparacao) == 0 ){  // comparando nome por nome com o nomeComparacao do parametro.
			printf("\nNumero do teste: %d", testes[i].numIdentificacaoTeste);	
			printf("\nPaciente: %s", testes[i].pessoa.nome);
			printf("\nCPF: %s", testes[i].pessoa.cpf);
			printf("\nData de nascimento: %d / %d / %d", testes[i].pessoa.dataNasc.dia, testes[i].pessoa.dataNasc.mes, testes[i].pessoa.dataNasc.ano);
			printf("\nIdade: %d", testes[i].pessoa.idade);
			printf("\nSexo: %c", testes[i].pessoa.sexo);
			printf("\nBairro: %s", testes[i].pessoa.bairro);
			printf("\nResultado do teste: %c\n", testes[i].resultadoTeste);
			if(strcmp(testes[i].valido, "nao") == 0){
				printf("\nEste teste nao eh valido\n");
			}
	
			printf("\n-----------------------------------------------\n");
			return; // Caso encontre, a função retorna para a main.
		}
	}
		
	printf("\nNao existe teste cadastrado para essa pessoa\n");
	printf("\n-----------------------------------------------\n");
}

void cancelarTestePorNumCadastro(Teste* testes, int numTesteCancelar, int countTestes){
	
	int i;
	char confirmaCancelar;
	system("cls");
	
	printf("\n---------------- CANCELAR TESTE ----------------\n");
	for(i=0; i<countTestes; i++){	// percorrendo todos os testes já cadastrados.
		if( testes[i].numIdentificacaoTeste == numTesteCancelar ){	// se o número do teste atual é igual ao que o usuário deseja cancelar.					
			if(strcmp(testes[i].valido, "sim") == 0){ // verificando se este teste ainda nao foi cancelado.
				
				// chamando a função exibirTestePorNome apenas para mostrar ao usuário qual teste ela está tentando cancelar.
				exibirTestePorNome(testes, testes[i].pessoa.nome, countTestes);
				
				printf("\nDeseja realmente cancelar este teste ? s - n: ");
				fflush(stdin);
				scanf("%c", &confirmaCancelar);
				
				if(confirmaCancelar == 's'){
					strcpy(testes[i].valido, "nao"); // o campo valido do teste passa a ser 'nao', após o cancelamento.
					system("cls");	
					printf("\n---------------- CANCELAR TESTE ----------------\n");
					printf("\nTeste cancelado com sucesso !\n");
				}else{
					printf("\nTeste nao cancelado !\n");					
				}
			}else{
				printf("\nEste teste ja foi cancelado, tente outro !\n");
			}
			printf("\n------------------------------------------------\n");
			return;
		}
	}
		
	printf("\nNao existe teste cadastrado com este numero\n");
	printf("\n------------------------------------------------\n");
}

void salvarArquivo(FILE* arquivo, Teste* testes, int countTestes){
		
	int i;
	int quantTestesValidos = 0;
	system("cls");
	
	// incrementando a variavel de quantTestesValidos para mostrar quantos são na primeira linha do arquivo posteriormente.
	for(i=0;i<countTestes;i++){
		if(strcmp(testes[i].valido, "sim") == 0){
			quantTestesValidos++;
		}
	}
	
	fprintf(arquivo, "%d\n",quantTestesValidos);
	
	// percorrendo todos os testes e imprimindo no arquivo aqueles que ainda são válidos, ou seja, possuem o campo valido como 'sim'
	for(i=0;i<countTestes;i++)
	{
		if(strcmp(testes[i].valido, "sim") == 0){
			fprintf(arquivo, "Nome: %s", testes[i].pessoa.nome);
			fprintf(arquivo, "\nCPF: %s", testes[i].pessoa.cpf);
			fprintf(arquivo, "\nData de nascimento: ");
			fprintf(arquivo, "\nDia: %d", testes[i].pessoa.dataNasc.dia);
			fprintf(arquivo, "\nMes: %d", testes[i].pessoa.dataNasc.mes);
			fprintf(arquivo, "\nAno: %d", testes[i].pessoa.dataNasc.ano);
			fprintf(arquivo, "\nSexo: %c", testes[i].pessoa.sexo);
			fprintf(arquivo, "\nBairro: %s", testes[i].pessoa.bairro);
			fprintf(arquivo, "\nCOVID-19: %c\n", testes[i].resultadoTeste);
		}	
	}	

	printf("\n--------------- SALVAR ARQUIVO ---------------\n");
	printf("\nArquivo salvo com sucesso\n");
	printf("\n----------------------------------------------\n");
}

void exibirTodosTestes(Teste* testes, int countTestes){
	
	int i;
	system("cls");
	
	printf("\n------------- TESTES CADASTRADOS -------------\n");
	if(countTestes != 0){		// se possuir pelo menos um teste cadastrado no programa.
		for(i=0; i<countTestes; i++){ // percorre todos os testes, imprimindo todos os dados de um por um.
			printf("\n----------------------------------------------\n");
			printf("\nTESTE %d\n", i+1);
			printf("\nNome: %s", testes[i].pessoa.nome);
			printf("\nCPF: %s", testes[i].pessoa.cpf);
			printf("\nData de nascimento: %d / %d / %d", testes[i].pessoa.dataNasc.dia, testes[i].pessoa.dataNasc.mes, testes[i].pessoa.dataNasc.ano);
			printf("\nIdade: %d", testes[i].pessoa.idade);
			printf("\nSexo: %c", testes[i].pessoa.sexo);
			printf("\nBairro: %s", testes[i].pessoa.bairro);
			printf("\nCOVID-19: %c", testes[i].resultadoTeste);
			printf("\nValido: %s\n", testes[i].valido);
		}
	}
	else
	{
		printf("\nNenhum teste foi cadastrado ainda\n");		
	}
	
	printf("\n----------------------------------------------\n");
}

// função para exibir todos os testes salvos, lendo os dados de um arquivo salvo préviamente.
void exibirTodosTestesArquivo(FILE* arquivo){
	
	char Linha[100];
  	char *result;
	int i = 1;
	
	printf("\n--------------- TESTES SALVOS ---------------\n\n");
	while (!feof(arquivo))
	{
		// Lê uma linha (inclusive com o '\n')
	  	result = fgets(Linha, 100, arquivo);  // o 'fgets' lê até 99 caracteres ou até o '\n'
	  	if (result)  // Se foi possível ler
	  		printf("%s",Linha);
	  		if(strcmp(Linha, "COVID-19: N") == 0 || strcmp(Linha, "COVID-19: P") == 0){
	  			printf("\n----------------------------------------------\n");
			}
	  	i++;
	}
	printf("\n----------------------------------------------\n");
}

// imprimindo relatório de acordo com os testes, recebidos como parâmentro, juntamente com o countTestes = quantidade total de testes cadastrados.
void imprimirRelatorio(Teste* testes, int countTestes){
	
	int i;
	float quantTestesValidos = 0;
	
	float quantNaoInfectados = 0;
	float porcentNaoInfectados = 0;
	
	float quantInfectados = 0;
	float porcentInfectados = 0;
	
	float quantJovensInfectados = 0;
	float porcentJovensInfectados = 0;
	
	float quantAdultosInfectados = 0;
	float porcentAdultosInfectados = 0;
	
	float quantIdososInfectados = 0;
	float porcentIdososInfectados = 0;
	
	system("cls");
	printf("\n------------- RELATORIO COVID-19 -------------\n");
	
	// percorrendo todos os testes e incrementando a variável quantTestesValidos, caso o campo valido seja igual a 'sim'.
	for(i=0;i<countTestes;i++){
		if(strcmp(testes[i].valido, "sim") == 0){
			quantTestesValidos++;		
		}
	}
	
	// caso não exista nenhum teste com o campo valido = 'sim'
	if(quantTestesValidos == 0){		
		printf("\nNao possui testes validos para serem exibidos\n");
		printf("\n----------------------------------------------\n");
		return;
	}
	
	// incrementando as variáveis de quantidade para pessoas infectadas e não infectadas (total, jovens, adultos e idosos)
	for(i=0;i<countTestes;i++){ // percorrendo todos os testes.
		if(strcmp(testes[i].valido, "sim") == 0 && testes[i].resultadoTeste == 'N'){ // caso o teste sejá valido e resultado do teste para COVID negativo.
			quantNaoInfectados++;
		}else if(strcmp(testes[i].valido, "sim") == 0 && testes[i].resultadoTeste == 'P'){	// caso o teste sejá valido e resultado do teste para COVID positivo.
			quantInfectados++;
			if(testes[i].pessoa.idade < 20){ // caso a pessoa infectada seja adolescente.
				quantJovensInfectados++;
			}else if(testes[i].pessoa.idade > 19 && testes[i].pessoa.idade < 59){ // caso a pessoa infectada seja adulta.
				quantAdultosInfectados++;
			}else if(testes[i].pessoa.idade > 60){ // caso a pessoa infectada seja idosa.
				quantIdososInfectados++;
			}
		}
	}
	
	
	porcentNaoInfectados = (quantNaoInfectados/quantTestesValidos)*100; // calculando a porcentagem de pessoas não infectadas.
	porcentInfectados = (quantInfectados/quantTestesValidos)*100; // calculando a porcentagem de pessoas infectadas.
	
	if(quantInfectados != 0){
		porcentJovensInfectados = (quantJovensInfectados/quantInfectados)*100; // calculando a porcentagem de jovens infectados.
		porcentAdultosInfectados = (quantAdultosInfectados/quantInfectados)*100; // calculando a porcentagem de adultos infectados.
		porcentIdososInfectados = (quantIdososInfectados/quantInfectados)*100; // calculando a porcentagem de idosos infectados.
	}	
	
	// Imprimindo os dados calculados anteriormente.
	printf("\nTotal de pessoas cadastradas: %.0f", quantTestesValidos);
	printf("\nPessoas nao infectadas: %.0f (%.2f %%)", quantNaoInfectados, porcentNaoInfectados);
	printf("\nPessoas infectadas: %.0f (%.2f %%)", quantInfectados, porcentInfectados);	
	printf("\n\nJovens infectados: %.0f (%.2f %% dos infectados)", quantJovensInfectados, porcentJovensInfectados);
	printf("\nAdultos infectados: %.0f (%.2f %% dos infectados)", quantAdultosInfectados, porcentAdultosInfectados);
	printf("\nIdosos infectados: %.0f (%.2f %% dos infectados)", quantIdososInfectados, porcentIdososInfectados);
	printf("\n\n----------------------------------------------\n");

}

int main(){
	
	char nomeComparacao[50]; // variável que recebe o nome do paciente que o usuário deseja consultar o teste.
	char nomeArquivo[20]; // variável para armazenar o nome do arquivo
	
	int opc; // variável para receber a opção do menu
	int numTestes = 0; // variável que armazena o numero de testes em cada vez que um cadastro vai ser realizado.
	int countTestes = 0; // variável que acumula a quantidade de testes que estão sendo cadastrados.
	int controleArquivo = 0; // variável que define se o usuário já criou um arquivo alguma vez ( para que não seja necessário pedir um novo nome para o arquivo ).
	int numTesteCancelar = 0; // variável que recebe o número do teste a ser cancelado.
	
	Teste *testes; // ponteiro para as estruturas de testes que serão cadastradas.
	testes = NULL;
	
	FILE* arquivo;
	
	while(1){ // não para de rodar, a não ser que a opcao 0 do menu seja digitada.
		printf(" \n **** TESTES COVID-19 ****\n");
		printf("\nMenu de opcoes:\n\n");
		printf("1 - Cadastrar novos testes\n");
		printf("2 - Consultar teste\n");
		printf("3 - Cancelar teste\n");
		printf("4 - Salvar informacoes em arquivo\n");
		printf("5 - Visualizar informacoes de testes realizados\n");
		printf("6 - Relatorio de testes realizados\n");
		printf("0 - Sair\n");

		printf("\nDigite uma opcao: ");
		scanf("%d",&opc);
		
		if(opc==1){	 // Cadastrar novos testes		
			
			printf("\nDigite quantos testes serao cadastrados: ");
			scanf("%d",&numTestes);
			countTestes = countTestes + numTestes; // acumulando a quantidade de testes.
				
			testes = (Teste*) realloc(testes, sizeof(Teste) * countTestes); // usando realloc tanto para alocar a primeira vez, quanto para realocar em casa de mais cadastros.
			if(!testes){
				printf("Erro ao Realocar");
				exit(1);
			}				
			
			preencherCadastro(testes, countTestes - numTestes, countTestes); // função para preencher cadastro.				
		}
		else if(opc==2){	// consultar teste
				
			printf("\nDigite o nome do paciente que deseja consultar:  ");
			fflush(stdin);
			gets(nomeComparacao);
		
			exibirTestePorNome(testes, nomeComparacao, countTestes); // função para exbir o teste completo a partir de um nome específico.
		}
		else if(opc==3){	// cancelar teste
			 
			printf("\nNumero do teste a ser cancelado: ");
			scanf("%d",&numTesteCancelar);
			
			cancelarTestePorNumCadastro(testes, numTesteCancelar, countTestes); // função para cancelar um teste com um número específico.
		}
		else if(opc==4){	// salvar informacoes em arquivo
					
			// verificando a variável controleArquivo para saber se algum arquivo já foi criado ou não durante a execução do programa.
			if(controleArquivo == 0){
				printf("\nNome do arquivo a ser criado: ");
				fflush(stdin);
				gets(nomeArquivo);
				strcat(nomeArquivo, ".txt"); // concatenando o nome do arquivo escolhido pelo usuário com '.txt', para que seja criado um arquivo do tipo texto.
				controleArquivo = 1; // setando a variável como 1 para que o usuário não precise digitar um novo arquivo da próxima vez, utilizará sempre o mesmo da primeira vez.
			}
			
			arquivo = fopen(nomeArquivo,"w"); // abrindo o arquivo em modo de escrita.

			if(arquivo == NULL){	// verificando se deu certo a abertura do arquivo.
				printf("n\Erro na abertura do arquivo\n");
				exit(1);
			}
			
			salvarArquivo(arquivo, testes, countTestes); // função para armazenar os testes no arquivo.
			fclose(arquivo); // fechando o arquivo
		}
		else if(opc==5){	// visualizar informacoes de testes realizados
			
			printf("\n	1 - Exibir testes salvos no arquivo");
			printf("\n	2 - Exibir todos os testes\n");
			printf("\n	Digite uma opcao: ");
			scanf("%d",&opc);
			
			if(opc==1){		// exibir testes salvos no arquivo, a partir do arquivo criado pelo usuário.
				arquivo = fopen(nomeArquivo, "r"); // abrindo o arquivo em modo de leitura.
				if(arquivo != NULL){
					exibirTodosTestesArquivo(arquivo);
				}else{		// exbir todos os testes cadastrados, independente do arquivo, apenas pelo ponteiro.
					system("cls");
					printf("\nProvavelmente voce ainda nao salvou um arquivo, use a opcao 4 do menu e depois tente novamente\n");
				}
				
				fclose(arquivo); // fechando o arquivo
			}else{
				exibirTodosTestes(testes, countTestes);
			}	
		}
		else if(opc==6){	// Relatorio de testes realizados	
		
			imprimirRelatorio(testes, countTestes);
		}
		else if(opc==0){	// finalizar o programa
			system("cls");
			printf("\nVoce finalizou o programa\n");
			return 0;
		}
	}

	free(testes); // desalocando os testes		
	return 0;
}
