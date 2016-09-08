#define alarma 13
#define boton 12
#define puerta1 11
#define puerta2 10
#define sensor1 A0
#define sensor2 A1

int temMax = 10;
int tempMin = -10;

boolean estBoton = true;
boolean estAlarma = false;

int estSensor1 = 0;
int estSensor2 = 0;

void setup(){
	Serial.begin(9600);
	pinMode(alarma, OUTPUT);
	pinMode(boton, INPUT);
	pinMode(puerta1, INPUT);
	pinMode(puerta2, INPUT);
}

void loop(){
	estSensor1 = map(analogRead(sensor1), 0, 1023, -20, 20);
	estSensor2 = map(analogRead(sensor2), 0, 1023, -20, 20);

	controlTemperatura(estSensor1);
	//Serial.println(estSensor1);
	//delay(1000);
}

void controlTemperatura(int v){
	if((v > temMax || v < tempMin) && estAlarma == false){
		digitalWrite(alarma, HIGH);
		estAlarma = true;
		Serial.println("Alerta!!! temperatura de la camara 1: "  + String(v));
	}

	if(v <= temMax && v >= tempMin){	//Aca colocar la opcion de esperar 30 minutos.
		estAlarma = false;
	}

	estBoton = digitalRead(boton);
	if(estBoton == false){
		delay(150);
		digitalWrite(alarma, LOW);
		Serial.println("Alarma apagada...");
	}
}