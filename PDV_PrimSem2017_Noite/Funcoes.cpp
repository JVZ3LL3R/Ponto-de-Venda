// Arquivo com as funções do programa
#include "PontoDeVenda.h"

// Função que pede um código válido de produto ou
// zero para cancelar a transação ou ação que está sendo executada
//	Parâmetros:
//		Entrada: int *ptrCodigo - ponteiro de uma inteira que receberá o código
//				 char *ptrTransacao - ponteiro de um string que indica a
//										transação que está sendo executada
//		Retorno: bool true - tem um código de produto válido digitado
//					  false - o operador cancelou a transação
bool PedeCodigoProduto(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "Código do produto (1 a " << QTDE_PRODUTOS << ")" << endl
			<< "Ou zero para cancelar a transação: ";
		cin >> *ptrCodigo;					// recebe o código
		if(*ptrCodigo == 0)					// cancelou?
			return false;					// indica que cancelou
	} while(*ptrCodigo < 1 || *ptrCodigo > QTDE_PRODUTOS);
	return true;							// indica tudo OK
}
// Função que lê um produto com acesso direto (posicional)
//	Parâmetros:
//		Entrada: int nCodigo - código do produto a ser acessado
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
	// verificar se realmente é o mesmo código
	if(ptrStProduto->nCodigo != nCodigo)		// não é o mesmo produto?
		return false;
	return true;								// indica leitura OK
}
// Função que grava um produto com acesso direto (posicional)
//	Parâmetros:
//		Entrada: int nCodigo - código do produto a ser acessado
//				 PRODUTO *ptrStProduto - ponteiro do buffer de gravação
//				 FILE *fdProduto - file descriptor do arquivo de produtos
//		Retorno: bool - true - gravação foi realizada com sucesso
//						false - erro de fseek ou fwrite
bool GravarPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto)
{
	if(fseek(fdProduto, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0) // erro?
		return false;
	if(fwrite(ptrStProduto, sizeof(PRODUTO), 1, fdProduto) == 0) // erro?
		return false;
	return true;
}
