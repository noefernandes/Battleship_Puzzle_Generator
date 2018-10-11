#include <chrono>
#include <random>
#include <sstream>
#include <fstream>

#include "../include/battleship.h"


namespace bt{
	//Gera um aleatório entre inicio e fim, inclusive.
	int gerarAleatorio(int inicio, int fim){
		unsigned seed = static_cast<int> (std::chrono::system_clock::now().time_since_epoch().count());
		std::mt19937 mt(seed);
		std::uniform_int_distribution<int> linear_i(inicio, fim);
		
		int value = linear_i(mt);
		return value;
	}

	
	//Substitui '#' por '.'.
	void substituiDelimitador(std::string **mapa, const int n_linha, const int n_coluna){
		for(auto i = 0; i < n_linha; i++){							
			for(auto j = 0; j < n_coluna; j++){
				if(mapa[i][j] == "#"){
					mapa[i][j] = "~";
				}
			}
		}
	}

	//Escreve o mapa de caracteres dos barcos em um arquivo de saída.
	void mapaParaLeitura(std::string **mapa, const int n_linha, const int n_coluna, std::ofstream & out){
		
		for(auto i = 0; i < n_linha; i++){										
			for(auto j = 0; j < n_coluna; j++){
				out << mapa[i][j];
			}

			out << "\n";
		}
	}

	//Escreve em o mapa formatado para visualização em um arquivo de saída.
	void mapaParaUsuario(std::string **mapa, const int n_linha, const int n_coluna, std::ofstream & out){

		out << "   ";											
		for(auto i = 0; i < n_coluna; i++){
			out << "  " << (char) (65 + i);
		}

		out << std::endl;
		
		for(auto i = 0; i < n_linha; i++){							
			if(i < 9){
				out << i+1 << "  [";
			}else{
				out << i+1 << " [";
			}

			for(auto j = 0; j < n_coluna; j++){
				out << " " << mapa[i][j] << " ";
			}

			out << "]\n\n";
		}

		out << "\n";
	}

	
	//Verifica se o mapa considerado já existe no vetor de mapas.
	bool compararMapas(std::string ***vetMapas, std::string **mapa, const int n_arq, 
						 const int n_linha, const int n_coluna){

		int cont = 0;
		bool existeIgual = false; 
		for(auto i = 0; i < n_arq; i++){
			cont = 0;
			for(auto j = 0; j < n_linha; j++){
				for(auto k = 0; k < n_coluna; k++){
					if(mapa[j][k] == vetMapas[i][j][k]){
						cont++;
					}

					if(cont == n_linha*n_coluna){
						existeIgual = true;
						break;
					}	
				}
			}
		}

		return existeIgual;
	}

	//Insere o submarino no mapa.
	void insereSubmarine(std::string **mapa, const int n_linha, const int n_coluna, bt::navio & submarine){
		int teste_maximo = 100;

		while(submarine.qtd > 0){
			submarine.x = gerarAleatorio(0, n_linha - 1);
			submarine.y = gerarAleatorio(0, n_coluna - 1);

			//Analisa se a posição é válida.
			if(mapa[submarine.x][submarine.y] != "#" and mapa[submarine.x][submarine.y] != submarine.formHoriz and
			mapa[submarine.x][submarine.y] != "+" and mapa[submarine.x][submarine.y] != "<" and 
			mapa[submarine.x][submarine.y] != ">" and mapa[submarine.x][submarine.y] != "^" and
			mapa[submarine.x][submarine.y] != "v"){
				mapa[submarine.x][submarine.y] = submarine.formHoriz;

				for(auto i = submarine.x - 1; i <= submarine.x + 1; i++){
					for(auto j = submarine.y - 1; j <= submarine.y + 1; j++){
						if(i >= 0 and i < n_linha and j >= 0 and j < n_coluna and mapa[i][j] != submarine.formHoriz){
							mapa[i][j] = "#";
						}
					}
				}
			
				submarine.qtd--;
			
			}

			if(teste_maximo == 0){					//Verifica se ainda cabem navios.
				break;
			}		

			
			teste_maximo--;	
		}


	}

	//Insere os outros tipos de navios no mapa.
	void insereNavios(std::string **mapa, const int n_linha, const int n_coluna, bt::navio & barco){
		int teste_maximo = 100;

		char ch;
		bool podeHorizontal;
		bool podeVertical;

		while(barco.qtd > 0){
			barco.x = gerarAleatorio(0, n_linha - 1);          
			barco.y = gerarAleatorio(0, n_coluna - 1);
			barco.posicao = gerarAleatorio(0, 1);            //0: Horizontal, 1: Vertical.

			podeHorizontal = true;
			podeVertical = true;

			
			//Verifica se a posição de origem é válida. 
			if(mapa[barco.x][barco.y] != "#" and mapa[barco.x][barco.y] != "o" and mapa[barco.x][barco.y] != "+" 
				and mapa[barco.x][barco.y] != "<" and mapa[barco.x][barco.y] != ">" and mapa[barco.x][barco.y] != "^"
				and mapa[barco.x][barco.y] != "v"){
				
				//Verificando se a posição horizontal é válida.
				for(auto i = barco.y; i < barco.y + barco.tamanho; i++){
					if(i > n_coluna - 1){
						podeHorizontal = false;
					}else if(mapa[barco.x][i] == "#"){
						podeHorizontal = false;
					}
				}
				
				//Verificando se a posição vertical é válida.
				for(auto i = barco.x; i < barco.x + barco.tamanho; i++){
					if(i > n_linha - 1){
						podeVertical = false;
					}else if(mapa[i][barco.y] == "#"){
						podeVertical = false;
					}
				}
				
				//Inserindo caracteres na horizontal se for possível e se a posição for horizontal. 
				if(podeHorizontal == true and barco.posicao == bt::HORIZONTAL){
					std::istringstream iss(barco.formHoriz);
					for(auto i = barco.y; i < barco.y + barco.tamanho; i++){
						iss >> ch;
						std::string str(1, ch);
						mapa[barco.x][i] = str;	
					}

					//Isolando o barco com o caractere '#'.
					for(auto i = barco.x - 1; i <= barco.x + 1; i++){
						for(auto j = barco.y - 1; j <= barco.y + barco.tamanho; j++){
							if(i >= 0 and i < n_linha and j >= 0 and j < n_coluna and mapa[i][j] != "+" and
							 mapa[i][j] != "<" and mapa[i][j] != ">" and mapa[i][j] != "^" and mapa[i][j] != "v"){
								mapa[i][j] = "#";
							}
						}
					}

					barco.qtd--;
				}

				//Inserindo caracteres na vertical se for possivel e se a posição for vertical.
				if(podeVertical == true and barco.posicao == bt::VERTICAL){
					std::istringstream iss(barco.formVert);
					for(auto i = barco.x; i < barco.x + barco.tamanho; i++){
						iss >> ch;
						std::string str(1, ch);
						mapa[i][barco.y] = str;
					}

					//Isolando o barco com o caractere '#'.
					for(auto i = barco.x - 1; i <= barco.x + barco.tamanho; i++){
						for(auto j = barco.y - 1; j <= barco.y + 1; j++){
							if(i >= 0 and i < n_linha and j >= 0 and j < n_coluna and mapa[i][j] != "+" and 
							mapa[i][j] != "<" and mapa[i][j] != ">" and mapa[i][j] != "^" and mapa[i][j] != "v"){
								mapa[i][j] = "#";
							}
						}
					}

					barco.qtd--;
				}

			}

			if(teste_maximo == 0){							//Verifica se ainda cabem navios.
				break;
			}

			teste_maximo--;
			
	
		}
	}
}
