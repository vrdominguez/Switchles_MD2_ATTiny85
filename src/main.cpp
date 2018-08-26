#include <Arduino.h>
/**#include <avr/io.h>
 * #include <util/delay.h>
 * #include <avr/interrupt.h>
 */

// --- CONFIGURACION DE PINES CONECTADOS A LA CONSOLA -------------------------
int resetInput = 2; // Controla la interrupcion del boton reset
int pinJAP     = 3; // Controla el idioma de la consola
int pinNTSC    = 4; // Controla la frecuencia de refresco
int pinReset   = 5; // Controla el reseteo

// --- OTRAS VARIABLES --------------------------------------------------------
String region = "EUR"; // Guarda la region actual

// --- CAMBIOS DE REGION ------------------------------------------------------
/**
 * Establece la region como Europa (no japones, 50Hz) y pone el led en azul
 *
 * @param ---
 * @return void
 */
void setEUR() {
  digitalWrite(pinJAP, HIGH);
  digitalWrite(pinNTSC, LOW);
  region = "EUR";
}

/**
 * Establece la region como USA (no japones, 60Hz) y pone el led en verde
 *
 * @param ---
 * @return void
 */
void setUSA() {
  digitalWrite(pinJAP, HIGH);
  digitalWrite(pinNTSC, HIGH);
  region = "USA";
}

/**
 * Establece la region como Japon (japones, 60Hz) y pone el led en rojo
 *
 * @param ---
 * @return void
 */
void setJAP() {
  digitalWrite(pinJAP, LOW);
  digitalWrite(pinNTSC, HIGH);

  region = "JAP";
}

// --- CONTROL CONSOLA -----------------------------------------------
/**
 * Configura la region de la consola en una de las 3 existentes (Europera, USA
 * o Japon) de forma ciclica: EUR -> USA -> JAPON -> EUR
 *
 * @param ---
 * @return void
 */
void cambiarRegion() {
  if ( region.compareTo("EUR") == 0 ) {
    setUSA();
  }
  else if ( region.compareTo("USA") == 0 )
  {
    setJAP();
  }
  else {
    setEUR();
  }
}

/**
 * Ejecuta la accion de pulsar el reset en la Mega Drive II, poniendo durante
 * un corto espacio de tiempo la linea de reset a GND, para luego volver al 
 * estado de alta impedancia (entrada, con valor 1) 
 * 
 * @param ---
 * @return void
 */
void reinicarMD() {
  pinMode(pinReset, OUTPUT);
  digitalWrite(pinReset, LOW);
  delay(150);
  pinMode(pinReset, INPUT);
  digitalWrite(pinReset, HIGH);
}

// --- EJECUCION --------------------------------------------------------------
void setup() {
  pinMode(pinJAP, OUTPUT);
  pinMode(pinNTSC, OUTPUT);
  pinMode(resetInput, INPUT);
  
  // La salida de reset tiene que estar en HIGH_Z
  pinMode(pinReset, INPUT);
  digitalWrite(pinReset, HIGH);

  setEUR(); // Por defecto la region original al encender el PAL Europeo
}


void loop() {
    int contadorMilisegundos = 0;
    int estadoReset = digitalRead(resetInput);

    while( estadoReset == LOW ) {
        contadorMilisegundos++;
        delay(1);
        estadoReset = digitalRead(resetInput);
    }

    // Si el contador ha contado algo
    if( contadorMilisegundos > 0) {
        // Controlamos el tiempo
        if ( contadorMilisegundos < 1000 ) {
            reinicarMD();
        }
        else {
            cambiarRegion();
        }

        contadorMilisegundos = 0;
    }
}