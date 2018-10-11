#include <iostream>
#include <fstream>
#include <sstream>
#include "battleship.h"

int main(int argc, char **argv){
	int n_arq = 1, n_linha = 10, n_coluna = 10;

	if(argc == 1){
		std::cout << "\nVocê gerou " << n_arq << " arquivo(s) " << n_linha << " x " << n_coluna << ".\n";
	}

	if(argc == 2){									//Analisando validade das entradas.
		std::istringstream iss(argv[1]);
		iss >> n_arq;
		if(iss.fail() or !iss.eof() or n_arq > 100 or n_arq <= 0){
			std::cerr << "\nErro na escrita da quantidade de arquivos. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cerr << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}

		std::cout << "\nVocê gerou " << n_arq << " arquivo(s) " << n_linha << " x " << n_coluna << ".\n";

		iss.clear();
	}

	if(argc == 3){
		std::istringstream iss(argv[1]);       
		iss >> n_arq;
		if(iss.fail() or !iss.eof() or n_arq > 100 or n_arq <= 0){
			std::cerr << "\nErro na escrita da quantidade de arquivos. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cout << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}

		

		iss.clear();

		iss.str(argv[2]);       
		iss >> n_linha;
		if(iss.fail() or !iss.eof() or n_linha < 7 or n_linha > 15){
			std::cerr << "\nErro na escrita da quantidade de linhas. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cout << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}

		std::cout << "\nVocê gerou " << n_arq << " arquivo(s) " << n_linha << " x " << n_coluna << ".\n";

		iss.clear();
	}

	if(argc == 4){
		std::istringstream iss(argv[1]);       
		iss >> n_arq;
		if(iss.fail() or !iss.eof() or n_arq > 100 or n_arq <= 0){
			std::cerr << "\nErro na escrita da quantidade de arquivos. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cout << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}
		
		iss.clear();

		iss.str(argv[2]);       
		iss >> n_linha;
		if(iss.fail() or !iss.eof() or n_linha < 7 or n_linha > 15){
			std::cerr << "\nErro na escrita da quantidade de linhas. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cout << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}
		
		iss.clear();

		iss.str(argv[3]);       
		iss >> n_coluna;
		if(iss.fail() or !iss.eof() or n_coluna < 7 or n_coluna > 15){
			std::cerr << "\nErro na escrita da quantidade de colunas. Tente novamente.\n";
			std::cerr << "Lembre-se do formato básico: ./exe arq lin col\n";
			std::cerr << "arq: [1,100]\nlin: [7,15]\ncol: [7,15]\n";
			std::cout << "Se omitido o valor, o padrão é: arq = 1, lin = 10, col = 10.\n";
			iss.clear();
			return 0;
		}

		std::cout << "\nVocê gerou " << n_arq << " arquivo(s) " << n_linha << " x " << n_coluna << ".\n";

		iss.clear();
	}
	


	
	bt::navio battleship, cruiser, destroyer, submarine;   //Struct que organiza as caracteristicas dos navios.

	battleship.tamanho = 4;
	battleship.qtd = 1;
	battleship.formHoriz = "<++>";
	battleship.formVert = "^++v";

	cruiser.tamanho = 3;
	cruiser.qtd = 2;
	cruiser.formHoriz = "<+>";
	cruiser.formVert = "^+v";

	destroyer.tamanho = 2;
	destroyer.qtd = 3;
	destroyer.formHoriz = "<>";
	destroyer.formVert = "^v";

	submarine.tamanho = 1;
	submarine.qtd = 4;
	submarine.formHoriz = "o";

	


	std::ofstream out, out2;                   //Arquivos de saida com formatação e sem formatação.
	out.open("camposusuario.txt");
	out2.open("campo.txt");




	std::string ***vetMapas = new std::string **[n_arq];  //Criação de um vetor de matrizes.
	for(auto i = 0; i < n_arq; i++){
		vetMapas[i] = new std::string*[n_linha];
	}

	for(auto i = 0; i < n_arq; i++){
		for(auto j = 0; j < n_linha; j++){
			vetMapas[i][j] = new std::string[n_coluna];
		}
	}



	
	int k = 0;
	while(k < n_arq){
		battleship.qtd = 1;
		cruiser.qtd = 2;
		destroyer.qtd = 3;
		submarine.qtd = 4;


		std::string **mapa = new std::string *[n_linha];  	//Alocação dinâmica de uma matriz preenchida com a
	                                                  		//string '.'.
		for(auto i = 0; i < n_linha; i++){
			mapa[i] = new std::string [n_coluna];
		}

		for(auto i = 0; i < n_linha; i++){
			for(auto j = 0; j < n_coluna; j++){
				mapa[i][j] = "~";
			}
		}

		bt::insereNavios(mapa, n_linha, n_coluna, battleship);		//Inserção dos navios por tipo.
		bt::insereNavios(mapa, n_linha, n_coluna, cruiser);
		bt::insereNavios(mapa, n_linha, n_coluna, destroyer);
		bt::insereSubmarine(mapa, n_linha, n_coluna, submarine);	

		if(destroyer.qtd != 0 or submarine.qtd != 0){			//Ignora os mapas que não aceitam mais barcos.
			for(auto i = 0; i < n_linha; i++){					//e libera o espaço utilizado.		
				delete[] mapa[i];
			}

			delete[] mapa;
			
			continue;
		}
		
		
		bt::substituiDelimitador(mapa, n_linha, n_coluna);   		//Retira a 'máscara' dos barcos.

		if(bt::compararMapas(vetMapas, mapa, n_arq, n_linha, n_coluna) == false){  //Verifica se o mapa já existe.
			for(auto i = 0; i < n_linha; i++){
				for(auto j = 0; j < n_coluna; j++){
					vetMapas[k][i][j] = mapa[i][j];
				}
			}
		
		}else{

			for(auto i = 0; i < n_linha; i++){			
				delete[] mapa[i];
			}

			delete[] mapa;
			
			continue;
		}

		
		bt::mapaParaLeitura(mapa, n_linha, n_coluna, out2);			//Cria o mapa de caracteres.
		bt::mapaParaUsuario(mapa, n_linha, n_coluna, out);			//Cria o mapa formatado.

	

		for(auto i = 0; i < n_linha; i++){							//Libera o espaço do mapa não ignorado.
			delete[] mapa[i];
		}

		delete[] mapa;

		k++;
	}


	out.close();
	out2.close();

	return 0;
}