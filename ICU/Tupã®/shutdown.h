//Define o header.
#ifndef shutdown_h
#define shutdown_h

//Importa as bibliotecas necessárias.
#include <stdint.h>


#include "cant.h"
#include "protocolopartida.h"

//Declara a variável que verifica erros e uma flag de partida.

extern uint8_t stateError;


//Define a função que verifica erros no BSE, CAN ou placa dos pedais.
void verifica_erro();


#endif
