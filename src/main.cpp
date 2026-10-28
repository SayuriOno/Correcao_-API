#include <Arduino.h>
#include <WiFi.h>
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

  pedirDadosPokemonAPIPorId(25);
}

// esp crash decoder eh uma extensao que decodifica o erro no esp. 


void loop() {
  
}


String pedirDadosPokemonAPIPorId (unsigned int idPokemon)
(
  String resposta = " ";


  enderecoAPI = enderecoAPI + idPokemon + "/";
  Serial.printf("endereco a ser pesquisado: %S", enderecoAPI.c_str());

  HTTPClient textoJsonHTTP;
  
  textoJsonHTTP.begin(enderecoAPI);

  int codigoHTTP = textoJsonHTTP.GET();

  resposta = textoJsonHTTP.getString();
  
  textoJsonHTTP.end();

  return resposta;

)