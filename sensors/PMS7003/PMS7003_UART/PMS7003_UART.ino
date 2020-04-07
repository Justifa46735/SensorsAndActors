#include <SoftwareSerial.h>


SoftwareSerial mySerial(D2,D1); // TX, RX

void setup() {
// for debuging
Serial.begin(115200);

// Use software serial
mySerial.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:
static int CheckFirst=0;
static int pm_add[3][5]={0,};
static int pm_old[3]={0,};
int chksum=0,res=0;;
unsigned char pms[32]={0,};


if(mySerial.available()>=32)
{

for(int j=0; j<32 ; j++){
pms[j]=mySerial.read();
if(j<30)
chksum+=pms[j];
}

if(pms[30] != (unsigned char)(chksum>>8)
|| pms[31]!= (unsigned char)(chksum) ){


}
if(pms[0]!=0x42 || pms[1]!=0x4d )


Serial.println("PMS7003 read data: ");
Serial.print("PM1.0 ug/m3 Standard Particle: ");
Serial.print(pms[4]);
Serial.print(pms[5]);
Serial.println();
Serial.print("PM2.5 ug/m3 Standard Particle: ");
Serial.print(pms[6]);
Serial.print(pms[7]);
Serial.println();
Serial.print("PM10  ug/m3 Standard Particle: ");
Serial.print(pms[8]);
Serial.println(pms[9]);
Serial.println("Relevant data:");
Serial.print("PM1.0 ug/m3 Atmos. Environ: ");
Serial.print(pms[10]);
Serial.print(pms[11]);
Serial.println();
Serial.print("PM2.5 ug/m3 Atmos. Environ: ");
Serial.print(pms[12]);
Serial.print(pms[13]);
Serial.println();
Serial.print("PM10  ug/m3 Atmos. Environ: ");
Serial.print(pms[14]);
Serial.println(pms[15]);
Serial.print("Particle beyond 0.3 um in 0.1L air: ");
Serial.print(pms[16]);
Serial.println(pms[17]);
Serial.print("Particle beyond 0.5 um in 0.1L air: ");
Serial.print(pms[18]);
Serial.println(pms[19]);
Serial.print("Particle beyond 1.0 um in 0.1L air: ");
Serial.print(pms[20]);
Serial.println(pms[21]);
Serial.print("Particle beyond 2.5 um in 0.1L air: ");
Serial.print(pms[22]);
Serial.println(pms[23]);
Serial.print("Particle beyond 5.0 um in 0.1L air: ");
Serial.print(pms[24]);
Serial.println(pms[25]);
Serial.print("Particle beyond 10  um in 0.1L air: ");
Serial.print(pms[26]);
Serial.println(pms[27]);
Serial.println();

}


delay(2000);}
