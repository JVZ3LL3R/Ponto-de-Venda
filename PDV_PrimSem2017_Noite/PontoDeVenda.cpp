// Programa de Ponto de Venda
// FATEC-MC - JCB - 10/05/2017 - Vers�o 0.0
#include "PontoDeVenda.h"
//
// entry point do programa
//
void main(void)
{
	int i;										// indexador e contador
	int nQtdeProduto;							// Recebe a quantidade de Produtos Vendidos
	char cWork[200],							// para o sprintf_s
		cOpcao;									// recebe a op��o do operador
	PRODUTO stProduto;							// struct para conter os dados de um produto
	FILE *fdProduto;							// file descriptor do arquivo de produtos
	SYSTEMTIME stTime;							// para receber data e hora do sistema

	PAIS_BRASIL;								// acentua��o brasileira
	// abrir o cadastro de produtos em modo r+b - precisa existir
	if(fopen_s(&fdProduto, CAMINHO_ARQUIVO, "r+b") != 0)	// erro de abertura?
	{	// n�o existe o arquivo porque � a primeira vez
		if(fopen_s(&fdProduto, CAMINHO_ARQUIVO, "w+b") != 0) // erro irrecuper�vel?
		{
			cout << "Erro de abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
			PAUSA;
			return;								// retorna ao S.O.
		}
		// arquivo aberto - vamos inicializ�-lo "formatar"
		for(i = 0; i < QTDE_PRODUTOS; i++)		// loop para gravar todos os produtos inativos
		{
			stProduto.cAtivo = INATIVO;			// produto inativo
			stProduto.nCodigo = i + 1;			// 1, 2, 3, ......QTDE_PRODUTOS
			if(fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0) // erro?
			{	// erro irrecuper�vel
				fclose(fdProduto);				// fecha o cadastro de produtos
				cout << "Erro de grava��o!" << endl;
				PAUSA;
				return;							// volta ao Sistema Operacional
			}
		} // for
	} // n�o existe

	// loop infinito do programa
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);					// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Sistema PDV - %02d/%02d/%04d %02d:%02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << cWork << endl;
		cout << CADASTRAR_NOVO_PRODUTO << " - Cadastrar novo produto" << endl;
		cout << EXCLUIR_PRODUTO << " - Excluir produto existente" << endl;
		cout << MOSTRAR_PRODUTO << " - Mostrar dados de um produto" << endl;
		cout << VENDER_PRODUTO << " - Vender um produto" << endl;
		cout << COMPRAR_PRODUTO << " - Comprar um produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						// op��o do operador
		cOpcao = toupper(cOpcao);			// converte para mai�scula
		switch(cOpcao)						// avaliar a op��o escolhida
		{
			case CADASTRAR_NOVO_PRODUTO:
				if(!PedeCodigoProduto(&stProduto.nCodigo, "Cadastrar Novo Produto")) // cancelou?
					break;					// volta ao menu
				if(!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de leitura!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				if(stProduto.cAtivo == ATIVO)	// produto j� cadastrado?
				{
					cout << "Produto" << "\tDescri��o" << "\t\t\t\t\tQtde. Estoq"
						<< "\tPre�o Unit." << "\tVlrTotal Est"
						<< "\tTotal Vend" << "\tTotal Comp\n";
					sprintf_s(cWork, sizeof(cWork),
						"%d \t%-40s \t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f",
						stProduto.nCodigo, stProduto.cDescricao, stProduto.dQtdeEstoque, stProduto.dPrecoUnit,
						stProduto.dVlrTotalEstoque, stProduto.dTotalVendido, stProduto.dTotalCompras);
					cout << cWork << endl;
					PAUSA;
					break;					// volta ao menu
				}
				// cadastrar o produto
				cin.ignore(1, EOF);			// ignorar a tecla Enter anterior
				cout << "Descri��o: ";
				cin.getline(stProduto.cDescricao, TAM_DESCRICAO, '\n');
				cout << "Pre�o Unit�rio: ";
				cin >> stProduto.dPrecoUnit;
				cout << "Quantidade em estoque: ";
				cin >> stProduto.dQtdeEstoque;
				stProduto.dVlrTotalEstoque = stProduto.dPrecoUnit * stProduto.dQtdeEstoque;
				stProduto.dTotalCompras =
					stProduto.dTotalVendido = 0.0;
				stProduto.cAtivo = ATIVO;	// produto ativo
				if(!GravarPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
				}
				break;						// volta ao menu
			case EXCLUIR_PRODUTO:
				if(!PedeCodigoProduto(&stProduto.nCodigo, "Exluir Produto")) // cancelou?
					break;					// volta ao menu
				if(!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de leitura!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				if(stProduto.cAtivo != ATIVO)
				{
					cout << "Nenhum Produto Cadastrado!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto" << "\tDescri��o" << "\t\t\t\t\tQtde. Estoq"
					<< "\tPre�o Unit." << "\tVlrTotal Est"
					<< "\tTotal Vend" << "\tTotal Comp\n";
				sprintf_s(cWork, sizeof(cWork), 
					"%d \t%-40s \t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dQtdeEstoque, stProduto.dPrecoUnit,
					stProduto.dVlrTotalEstoque, stProduto.dTotalVendido, stProduto.dTotalCompras);
				cout << cWork << endl;
				cout << "\nDeseja Excluir realmente? (S ou N): ";
				cin >> cOpcao;
				if (cOpcao == 's' || cOpcao == 'S')	// Exluir realmente?
					stProduto.cAtivo = INATIVO;		// Exclui cadastro do Produto
				else
					break;
				if(!GravarPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto Excluido com Sucesso!" << endl;
				PAUSA;
				break;						// volta ao menu
			case MOSTRAR_PRODUTO:
				if(!PedeCodigoProduto(&stProduto.nCodigo, "Mostrar Produto")) // cancelou?
					break;					// volta ao menu
				if(!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de leitura!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				if(stProduto.cAtivo == INATIVO)
				{
					cout << "Nenhum Produto Cadastrado!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto" << "\tDescri��o" << "\t\t\t\t\tQtde. Estoq"
					<< "\tPre�o Unit." << "\tVlrTotal Est"
					<< "\tTotal Vend" << "\tTotal Comp\n";
				sprintf_s(cWork, sizeof(cWork),
					"%d \t%-40s \t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dQtdeEstoque, stProduto.dPrecoUnit,
					stProduto.dVlrTotalEstoque, stProduto.dTotalVendido, stProduto.dTotalCompras);
				cout << cWork << endl;
				PAUSA;
				break;						// volta ao menu
			case VENDER_PRODUTO:
				if(!PedeCodigoProduto(&stProduto.nCodigo, "Vender Produto")) // cancelou?
					break;					// volta ao menu
				if(!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de leitura!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				if(stProduto.cAtivo == INATIVO)
				{
					cout << "Produto Inativo!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto" << "\tDescri��o" << "\t\t\t\t\tQtde. Estoq"
					<< "\tPre�o Unit." << "\tVlrTotal Est"
					<< "\tTotal Vend" << "\tTotal Comp\n";
				sprintf_s(cWork, sizeof(cWork),
					"%d \t%-40s \t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dQtdeEstoque, stProduto.dPrecoUnit,
					stProduto.dVlrTotalEstoque, stProduto.dTotalVendido, stProduto.dTotalCompras);
				cout << cWork << endl;
				cout << "\nDigite a Quantidade de Produtos Vendidos: ";
				cin >> nQtdeProduto;
				stProduto.dQtdeEstoque = stProduto.dQtdeEstoque - nQtdeProduto;		// Diminui quantidade do Produto do Estoque
				stProduto.dVlrTotalEstoque = stProduto.dVlrTotalEstoque - (stProduto.dPrecoUnit * nQtdeProduto);
				stProduto.dTotalVendido = stProduto.dTotalVendido + (stProduto.dPrecoUnit * nQtdeProduto);
				if(!GravarPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
					break;
				}
				cout << "Produtos Vendidos com Sucesso!" << endl;
				PAUSA;
				break;						// volta ao menu
			case COMPRAR_PRODUTO:
				if(!PedeCodigoProduto(&stProduto.nCodigo, "Comprar Produto")) // cancelou?
					break;					// volta ao menu
				if(!LerProdutoPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de leitura!" << endl;
					PAUSA;
					break;					// volta ao menu
				}
				if(stProduto.cAtivo == INATIVO)
				{
					cout << "Produto Inativo!" << endl;
					PAUSA;
					break;
				}
				cout << "Produto" << "\tDescri��o" << "\t\t\t\t\tQtde. Estoq"
					<< "\tPre�o Unit." << "\tVlrTotal Est"
					<< "\tTotal Vend" << "\tTotal Comp\n";
				sprintf_s(cWork, sizeof(cWork),
					"%d \t%-40s \t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f \t\t%0.2f",
					stProduto.nCodigo, stProduto.cDescricao, stProduto.dQtdeEstoque, stProduto.dPrecoUnit,
					stProduto.dVlrTotalEstoque, stProduto.dTotalVendido, stProduto.dTotalCompras);
				cout << cWork << endl;
				cout << "\nDigite a Quantidade de Produtos Comprados: ";
				cin >> nQtdeProduto;
				stProduto.dQtdeEstoque = stProduto.dQtdeEstoque + nQtdeProduto;		// Diminui quantidade do Produto do Estoque
				stProduto.dVlrTotalEstoque = stProduto.dVlrTotalEstoque + (stProduto.dPrecoUnit * nQtdeProduto);
				stProduto.dTotalCompras = stProduto.dTotalCompras + (stProduto.dPrecoUnit * nQtdeProduto);
				if(!GravarPosicional(stProduto.nCodigo, &stProduto, fdProduto)) // erro?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
					break;
				}
				cout << "Produtos Comprados com Sucesso!" << endl;
				PAUSA;
				break;						// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				{
					fclose(fdProduto);		// fechar o cadastro
					return;					// volta ao sistema operacional
				}
				break;						// volta ao menu
			default:
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main




