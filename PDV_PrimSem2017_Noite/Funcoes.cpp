// Arquivo com as fun��es do programa
#include "PontoDeVenda.h"

// Fun��o que pede um c�digo v�lido de produto ou
// zero para cancelar a transa��o ou a��o que est� sendo executada
//	Par�metros:
//		Entrada: int *ptrCodigo - ponteiro de uma inteira que receber� o c�digo
//				 char *ptrTransacao - ponteiro de um string que indica a
//										transa��o que est� sendo executada
//		Retorno: bool true - tem um c�digo de produto v�lido digitado
//					  false - o operador cancelou a transa��o
bool PedeCodigoProduto(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "C�digo do produto (1 a " << QTDE_PRODUTOS << ")" << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrCodigo;					// recebe o c�digo
		if(*ptrCodigo == 0)					// cancelou?
			return false;					// indica que cancelou
	} while(*ptrCodigo < 1 || *ptrCodigo > QTDE_PRODUTOS);
	return true;							// indica tudo OK
}
// Fun��o que l� um produto com acesso direto (posicional)
//	Par�metros:
//		Entrada: int nCodigo - c�digo do produto a ser acessado
//				 PRODUTO *ptrStProduto - ponteiro para o buffer de leitura
//				 FILE *fdProduto - file descriptor do arquivo de produtos
//		Retorno: bool - true - leitura foi realizada com sucesso
//						false - erro de fseek ou fread_s ou foi lido um produto errado
bool LerProdutoPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if(fseek(fdProduto, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0) // erro de seek?
		return false;							// avisa que houve erro
	if(fread_s(ptrStProduto, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdProduto) == 0) // erro?
		return false;							// avisa que houve erro
	// verificar se realmente � o mesmo c�digo
	if(ptrStProduto->nCodigo != nCodigo)		// n�o � o mesmo produto?
		return false;
	return true;								// indica leitura OK
}
// Fun��o que grava um produto com acesso direto (posicional)
//	Par�metros:
//		Entrada: int nCodigo - c�digo do produto a ser acessado
//				 PRODUTO *ptrStProduto - ponteiro do buffer de grava��o
//				 FILE *fdProduto - file descriptor do arquivo de produtos
//		Retorno: bool - true - grava��o foi realizada com sucesso
//						false - erro de fseek ou fwrite
bool GravarPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if(fseek(fdProduto, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0) // erro?
		return false;
	if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0) // erro?
		return false;
	return true;
}
