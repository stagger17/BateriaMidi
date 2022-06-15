#include <MIDI.h>

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();


/////////////// Definción de pines de I/O de Arduino ////////////////
#define PEDAL_B 9
#define REDO 10
#define HIHAT 11
#define TOM 12
#define LED_B 13
///////////////////////////////////////////////////////////////////////

///////////////// Declaración de constantes ////////////////////////////

#define C_PAD 5
#define T_SOUND 400

///////////////////////////////////////////////////////////////////////

///////////////// Declaración de variables globales ////////////////////////////

unsigned int pads[C_PAD] = {10,20,30,40,50};
unsigned int Note_pads[C_PAD];
boolean PAD_Activo[C_PAD] = {0,0,0,0,0};
unsigned long tiempo1[C_PAD];
unsigned long tiempo2[C_PAD];


unsigned int sensibilidad = 300;

///////////////// Declaración de funciones ////////////////////////////

void detectarGolpe();
void enviarNota(char mensaje, int nota, int velocidad);

///////////////////////////////////////////////////////////////////////////

void setup()
{
    
    MIDI.begin(MIDI_CHANNEL_OFF); // Seteamos el programa para que descarte todos los Mensajes entrantes.

    pinMode(LED_B, OUTPUT); // Pin digital 12 como SALIDA
    pinMode(REDO, INPUT); // Pin digital 10 como ENTRADA
    pinMode(PEDAL_B, INPUT); // Pin digital 9 como ENTRADA
    pinMode(HIHAT, INPUT); 
    pinMode(TOM, INPUT); 



}

void loop()
{
    // Send note 42 with velocity 127 on channel 1
    MIDI.sendNoteOn(42, 127, 1);

    // Read incoming messages
    //MIDI.read();


}

void detectarGolpe(){

    int velocidad;

    for(int i=0;i<C_PAD,i++){

        pads[i] = analogRead(i);

        if(pads[i]>sensibilidad){

            if(PAD_Activo[i] == false){

                velocidad = pads[i]/8 - 1;
                
                enviarNota("NotaON",Note_pads[i],velocidad);

                tiempo1[i] = millis();
            }

            else{

                tiempo2[i] = millis();

                if (((tiempo2[i])-tiempo1[i])> 500){

                    enviarNota("NotaOff",Note_pads[i],0);
                    PAD_Activo[i] = false;
                }

            }




        }





    }











}