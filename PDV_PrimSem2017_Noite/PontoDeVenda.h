// Declara��es do programa
#include <iostream>
#include <Windows.h>
using namespace std;
// defini��es
#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define PAIS_BRASIL					setlocale(LC_ALL, "portuguese_brazil")
#define CAMINHO_ARQUIVO				"..\\Produtos.cad"
#define QTDE_PRODUTOS				2000
#define TAM_DESCRICAO				40
#define ATIVO						'A'
#define INATIVO						'I'

// defini��es do menu do operador
#define CADASTRAR_NOVO_PRODUTO		'C'
#define EXCLUIR_PRODUTO				'E'
#define MOSTRAR_PRODUTO				'M'
#define VENDER_PRODUTO				'V'
#define COMPRAR_PRODUTO				'P'
#define SAIR_DO_PROGRAMA			'S'

//
// struct do arquivo de produto
//
typedef struct tagPRODUTO
{
	int nCodigo;					// 1, 2, 3, .......QTDE_PRODUTOS
	char cAtivo,					// 'A' - ativo e 'I' - inativo
		cDescricao[TAM_DESCRICAO + 1]; // descri��o do produto
	double dQtdeEstoque,			// quantidade em estoque
		dPrecoUnit,					// pre�o unit�rio do produto
		dTotalVendido,				// valor total vendido
		dTotalCompras,				// valor total das compras
		dVlrTotalEstoque;			// valor total do estoque
} PRODUTO;							// struct de um produto
// prot�tipos das fun��es do programa
bool PedeCodigoProduto(int *ptrCodigo, char *ptrTransacao);
bool LerProdutoPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto);
bool GravarPosicional(int nCodigo, PRODUTO *ptrStProduto, FILE *fdProduto);




