
#define camara1 1
#define camara2 2

#define sirena 13
#define boton 12
#define puerta1 11
#define puerta2 10
#define luzPuerta1 9
#define luzPuerta2 8

#define sensor1 A0
#define sensor2 A1

#define tempMax 10
#define tempMin -10

boolean estBoton = false;
boolean estSirena = false;

const unsigned long tiempoEspera = 300000;

int estSensor1 = 0;
int estSensor2 = 0;
int estPuerta1 = 0;
int estPuerta2 = 0;

int tiempoAbierto;

void setup(){
	Serial.begin(9600);
	pinMode(sirena, OUTPUT);
	pinMode(luzPuerta1, OUTPUT);
	pinMode(luzPuerta2, OUTPUT);

	pinMode(boton, INPUT);
	pinMode(puerta1, INPUT);
	pinMode(puerta2, INPUT);
}

void loop(){
	estSensor1 = map(analogRead(sensor1), 0, 1023, -20, 20);
	estSensor2 = map(analogRead(sensor2), 0, 1023, -20, 20);

	estPuerta1 = digitalRead(puerta1);
	estPuerta2 = digitalRead(puerta2);

	if(estPuerta1 == 1){
		digitalWrite(luzPuerta1, HIGH);	    
	}
	else
		digitalWrite(luzPuerta1, LOW);

	if(estPuerta2 == 1){
	    digitalWrite(luzPuerta2, HIGH);
	}
	else
		digitalWrite(luzPuerta2, LOW);

	
	if(estPuerta1 == 1 && estPuerta2 == 1){
		controlTemperatura(estSensor1, camara1);
		controlTemperatura(estSensor2, camara2);    
	}
	else{
		while(estPuerta1 == 0 || estPuerta2 == 0){
		    ;
		}
		Serial.println("Esperando a que se enfríen las cámaras.");
		delay(tiempoEspera);
	}

	delay(1000);
}

void controlTemperatura(int temp, int cam){
	if((temp > tempMax || temp < tempMin)){
		Serial.println("Alerta!!! temperatura de la camara "  + String(cam) + ": " + String(temp));
		digitalWrite(sirena, HIGH);
		estSirena = true;

		while(estSirena == true){
			estBoton = digitalRead(boton);

			if(estBoton == 0){
				digitalWrite(sirena, LOW);
				estSirena = false;
				Serial.println("Se presiono el boton de emergencia.");
				delay(10000);
			}
		}
	}
}