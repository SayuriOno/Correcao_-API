#include <Arduino.h>
#include <WiFi.h>
#include <arduinoJson.h>
#include <HTTPClient.h>

//============PROTOTIPOS DAS FUNCOES================
String pedirDadosPokemonAPIPorId (unsigned int idPokemon);


const char* nomeRedeWifi="SENAI EDUCACIONAL";
const char* senhaRedeWifi="info@134";
String enderecoAPI="https://pokeapi.co/api/v2/pokemon/" //adicionar o numero do pokemon a ser pesquisado 

void setup() {
  Serial.begin(115200);
  WiFi.begin(nomeRedeWifi, senhaRedeWifi);

  Serial.println();
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\n\rConectado\n\r");
  JsonDocument docPokemon;

  Serial.println(ESP.getFreeHeap());
  String JsonVindoDaApiPokemon = pedirDadosPokemonAPIPorId (25);
  Serial.println(ESP.getFreeHeap());
  DeserializationError codigoStatusJson = deserializeJson(docPokemon,JsonVindoDaApiPokemon);
  Serial.println(ESP.getFreeHeap());

  JsonVindoDaApiPokemon.end(); //desalocar memoria deste objeto pois eu nao vou usar mais.
  Serial.println(ESP.getFreeHeap());

  
  pedirDadosPokemonAPIPorId(25);
}

// esp crash decoder eh uma extensao que decodifica o erro no esp. 


void loop() {}


String pedirDadosPokemonAPIPorId (unsigned int idPokemon)
(
  String resposta = " ";

  enderecoAPI = enderecoAPI + idPokemon + "/";
  Serial.printf("endereco a ser pesquisado: %S", enderecoAPI.c_str());

  HTTPClient textoJsonHTTP;

  textoJsonHTTP.begin(enderecoAPI);//o begin inicia o objeto instanciado do tipo HTTP para pegar textos HTTP na internet.
  
  int codigoHTTP = textoJsonHTTP.GET();// o GET acessa o endereco passando no pegin e baixa as informacoes, e retorna o codgo HTTP 
  //de status como 200 para ok e 404 para pagina nao encontrada.
 
if(codigoHTTP != 200)//clausula de guarda, como se fosse algo que trava.
{
  resposta = " error ao acessar o endereco"+ codigoHTTP;
  return resposta;
}

  resposta = textoJsonHTTP.getString();

  textoJsonHTTP.end();
  return resposta;

)