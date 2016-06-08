#include <EtherCard.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
float cmMsec;//inMsec;
long microsec;

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700];
static uint32_t timer;
char website[] = "192.168.0.116";
char temp_sensor[150];
//int an0 = A0;
//int sensor = 0;

#define pino_led 7


static void my_callback (byte status, word off, word len)
{
   Ethernet::buffer[off+len] = 0;    //mensagem do retorno do servidor
   //Serial.print((const char*) Ethernet::buffer + off);  //mostra todo o retorno
   Serial.print((const char*) Ethernet::buffer + off + 157); //mostra somente ok
}

void setup ()
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("Obtendo IP:");
  if (ether.begin(sizeof Ethernet::buffer, mymac,10) == 0)
    Serial.println( "Falha ao acessar o controlador Ethernet");
  if (!ether.dhcpSetup())
    Serial.println( "Falha ao obter o IP");
  ether.printIp("IP: ", ether.myip);
  ether.printIp("Mascara: ", ether.netmask);
  ether.printIp("Gatway: ", ether.gwip);
  ether.printIp("Sevidor DNS: ", ether.dnsip);
  //if (!ether.dnsLookup(website))     //IP do servidor por DNS
    //Serial.println("Falha no DNS");
  ether.parseIp(ether.hisip, "192.168.0.116"); //IP do servidor manual
  ether.printIp("Servidor: ", ether.hisip);
  Serial.println(" ");
}

void loop ()
{
  //inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  
  ether.packetLoop(ether.packetReceive());
  if (millis() > timer)
  {
    timer = millis() + 5000;
 
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    
    ether.persistTcpConnection(true);
    
    sprintf(temp_sensor, "?cod=1&med=%i", (int)cmMsec); 
    ether.browseUrl(PSTR("http://192.168.0.116/neatbin/insert.php?cod=1&med=50"), temp_sensor, website, my_callback);
  }
}
