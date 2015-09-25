/* Copyright 2015, Eduardo Filomena, Juan Manuel Reta
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "evaluacion.h"       /* <= own header */
#include "stdint.h"




/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */


///void ISR_interrumpe (void)
//{
	///Chip_RIT_ClearInt(LPC_RITIMER);
	///cambiar_estado(1);
///}

extern int bandera1;
int dato, dato_final;
float factor=1;
int salida_a_cero=0;
int retardo_n=1000000;
char cadena1[]="Aumenta Ganancia \n\r";
char cadena2[]="Disminuye Ganancia \n\r";
char cadena3[]="Mute \n\r";
char cadena4[]="Ganancia 1 \n\r";
int i;


int main(void)
{
   /* perform the needed initialization here */




	inicializar_ADC();
	inicializar_DAC();
	inicializar_timer(100);
	habilitar_interrupcion(11); ///habilito interrupcion del timer
	inicializacion_de_led();
	configurar_tecla();
	configurar_UART();


	while(1){


    	if(!(leer_tecla()&0b1000)) /// tecla 4 - vuelve el factor a 1
    	{
    			cambiar_estado(1);
    			factor=1;

    					for(i=0;i<=13;i++){
    						enviar_UART(cadena4[i]);
    						retardo(retardo_n);

    					}

    	}

    	if(!(leer_tecla()&0b0010))///tecla2
    	{
    		cambiar_estado(1);
    		factor=factor-0.5;

    		for(i=0;i<=21;i++){
    		    						enviar_UART(cadena2[i]);
    		    						retardo(retardo_n);

    		    					}


    		}


    	if(!(leer_tecla()&0b0001)) ///tecla1
    	{
    		cambiar_estado(1);
    		factor=factor+0.2;

    		for(i=0;i<=19;i++){
    		    						enviar_UART(cadena1[i]);
    		    						retardo(retardo_n);
    		    				    		    					}


    	}


		if (bandera1==1)
		{
			if(!(leer_tecla()&0b0100)) /// tecla 3 salida a cero
			{
				escribir_DAC(salida_a_cero);
				cambiar_estado(1);


				for(i=0;i<=7;i++){
				    		    						enviar_UART(cadena3[i]);
				    		    						retardo(retardo_n);

				    		    					}
			}else{
				dato=leer_ADC();
				dato_final=dato*factor;
				escribir_DAC(dato_final);

			}

		}
		bandera1=0;




	}
         return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

