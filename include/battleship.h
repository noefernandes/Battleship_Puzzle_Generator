/*! \file battleship.h
	\author Noé Fernandes
	\date September, 15th
*/

#ifndef BATTLESHIP_LIB_H
#define BATTLESHIP_LIB_H

/*! \namespace bt 
	\brief Namespace that organizes functions.
*/
namespace bt{

	/*! \brief Generates a random number between a given range (inclusive).
	*/
	int gerarAleatorio(int inicio /*!< Beginning of the range.*/, int fim /*!< End of the range.*/); 
	
	/*! \struct bt::navio
		\brief Structure that defines the type ship, with all its characteristics.
	*/  
	struct navio{
	int posicao					/*! It receives 0 for horizontal and 1 for vertical. */; 		
	int tamanho					/*! Size of the ship. */;
	int qtd						/*! Quantity of ships by type. */;
	int x						/*! Line where the considered ship is located. */;
	int y						/*! Column where the considered ship is located. */;
	std::string formHoriz		/*! String representation of ship horizontally. */; 
	std::string formVert		/*! String representation of the ship vertically. */;
	};

	/*! \enum bt::posicao 
		\brief Enumeration that represents the horizontal and vertical position.
	*/
	enum posicao{
		HORIZONTAL = 0,
		VERTICAL = 1
	};

	/*! \brief Alias for struct Navio.
	*/
	typedef struct navio navio;

	/*! \brief Replaces the '#' character with '.'.
	*/
	void substituiDelimitador(std::string **mapa 	/*!< Matrix of characters. */ , 
							  const int n_linha  	/*!< Number of rows in the matrix. */, 
							  const int n_coluna 	/*!< Number of columns in the matrix. */);

	/*! \brief Write to an output file the maps with only the characters that compose them.
	*/
	void mapaParaLeitura(std::string **mapa 	/*!< Matrix of characters. */ , 
						 const int n_linha 		/*!< Number of rows in the matrix. */, 
						 const int n_coluna		/*!< Number of columns in the matrix. */,
						 std::ofstream & out 	/*!< Output file. */);

	/*! \brief Writes to an output file the maps already formatted for user viewing.
	*/
	void mapaParaUsuario(std::string **mapa 	/*!< Matrix of characters. */, 
						 const int n_linha		/*!< Number of rows in the matrix. */, 
						 const int n_coluna		/*!< Number of columns in the matrix. */,
						 std::ofstream & out    /*!< Output file. */);

	/*! \brief Returns true if the map in question already exists and false if not.
	*/
	bool compararMapas(std::string ***vetMapas  /*!< Matrix vector. */, 
		 			   std::string **mapa 		/*!< Matrix of characters considered. */, 
		 			   const int n_arq			/*!< Number of matrix in matrix vector. */,	 
					   const int n_linha		/*!< Number of rows in the matrix considered. */, 
					   const int n_coluna       /*!< Number of columns in the matrix considered. */);


	/*! \brief Position the submarines on the map.
	*/
	void insereSubmarine(std::string **mapa 	/*! Matrix of Characters. */, 
						 const int n_linha		/*!< Number of rows in the matrix. */, 
						 const int n_coluna		/*!< Number of columns in the matrix considered. */, 
						 bt::navio & submarine 	/*!< navio type value. */);

	/*! \brief Position the other ships (not the submarine) on the map.
	*/
	void insereNavios(std::string **mapa 		/*!< Matrix of characters considered. */, 
					  const int n_linha 		/*!< Number of rows in the matrix. */, 
					  const int n_coluna 		/*!< Number of columns in the matrix considered. */,
					  bt::navio & barco 		/*!< navio type value. */);

}

#endif