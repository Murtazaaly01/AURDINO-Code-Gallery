//LED on digital pin 3 will exhibit a “breathing effect”

int d = 5;

void setup() {
    pinMode(3,OUTPUT);
}

void loop() {
    for( int a=0; a<256; a++)
    {
        analogWrite(3,a);
        delay(d);
    }
    for(int a=256; a>0; a--)
    {
        analgWrite(3,a);
        delay(d);
    }
    delay(200);
}