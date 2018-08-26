# Mod Switchless MegaDrive 2 con _"hardware mínimo"_
Se trata de una versión más sencilla del mod para cambio de región de la Mega Drive 2 sin interruptores, utilizando el botón de RESET, con la menor cantidas de hardware.

Para reducir el uso de hardware se ha eliminado el zumbador, se ha sustituido el led RGB por un led RG y se utilizan las mismas salida para controlar el led RG y solamente se hacen cambios de región completos (excluyendo los cambios de frecuencia independientes)

## Funcionamiento
El pulsador de reset de la MegaDrive pasa a estar controlado  por el Attiny85, pasando a controlar el reseteo y el cambio de región, con las siguientes opciones:

  - **Pulsación de menos de un segundo:** Resetea la consola (se conserva la región)
  - **Pulsación de 1 segundo o más:** Se rota la región de la consola EUR->USA->JAP->EUR

## Indicador led

**TODO:** Pendiente de pruebas con LED RG y configuraciones, pero en principio serían:
  - **VERDE:** EUR
  - **ROJO:** JAPON
  - **NARANJA:** USA