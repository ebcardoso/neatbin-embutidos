#include <EtherCard.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
float cmMsec;
long microsec;

//para conexao com a internet
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700];
static uint32_t timer;
char website[] = "192.168.0.116";
char sensor[150];

static void my_callback (byte status, word off, word len) {
   Ethernet::buffer[off+len] = 0;    //mensagem do retorno do servidor
   Serial.print((const char*) Ethernet::buffer + off);  //mostra todo o retorno
   Serial.print((const char*) Ethernet::buffer + off + 157); //mostra somente ok
}

void obterIP() {
   //Acessando o Shield Ethernet
  Serial.println("Obtendo IP:");
  if (ether.begin(sizeof Ethernet::buffer, mymac,10) == 0) {
    Serial.println( "Falha ao acessar o controlador Ethernet");
  }
  
  //pegando DHCP
  if (!ether.dhcpSetup()) {
    Serial.println( "Falha ao obter o IP");
  } 
}

void imprimirInfoNet() {
  ether.printIp("IP: ", ether.myip);
  ether.printIp("Mascara: ", ether.netmask);
  ether.printIp("Gatway: ", ether.gwip);
  ether.printIp("Sevidor DNS: ", ether.dnsip); 
  ether.parseIp(ether.hisip, website); //IP do servidor manual, pega da variavel website, definida mais acima
  ether.printIp("Servidor: ", ether.hisip);  
}

void setup () {
  delay(1000);
  Serial.begin(9600);
  
  obterIP();
  imprimirInfoNet();  

  Serial.println(" ");
}

void medicaoSensor() {
  microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
}

void enviarParaServidor() {    
  ether.persistTcpConnection(true);   
  sprintf(sensor, "?cod=1&med=%i", (int)cmMsec); //parametros da requisicao GET-HTTP
  ether.browseUrl(PSTR("http://192.168.0.116/neatbin/insert.php"), sensor, website, my_callback);
}

void loop () { 
  ether.packetLoop(ether.packetReceive());
  if (millis() > timer) {
    timer = millis() + 5000;
    
    medicaoSensor();
    enviarParaServidor();
  }
}
