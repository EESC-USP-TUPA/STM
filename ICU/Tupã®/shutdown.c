#include <shutdown.h>

//Define as variáveis usadas...
uint8_t shutdown = 0;

uint8_t stateError = 0;




void verifica_erro(){
	shutdown = !HAL_GPIO_ReadPin(GPIOA, SHUTDOWN_MCU_Pin);

	//Caso haja erros, a variável torna-se verdadeira e partidaFlag, falsa.
	if (shutdown || canFlag0) {
		stateError = 1;
		partidaFlag = 0;
	}
	else if (erros){
		stateError = 1;
	}

	//Caso não tenha erros e o shutdown não esteja ativado, a variável é falsa.
	else {
		stateError = 0;
	}


}
