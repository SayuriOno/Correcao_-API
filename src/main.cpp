#include <Arduino.h>
#include <WiFi.h>
#include <arduinoJson.h>
#include <HTTPClient.h>

//!============PROTOTIPOS DAS FUNCOES================
String pedirDadosPokemonAPIPorId (unsigned int idPokemon);
void printPokemon(unsigned int idPokemon);
const char* nomeRedeWifi="SENAI EDUCACIONAL";
const char* senhaRedeWifi="info@134";
String enderecoAPI="https://pokeapi.co/api/v2/pokemon/" //adicionar o numero do pokemon a ser pesquisado 



//!======================================================
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
  randomSeed(10);// nao existe numeros aleatorios na programacao, entao esse comando faz um calculo matematico em funcao do tempo
  // ele le o analogico de um pino qualquer e esse pino tem um ruido que eh aleatorio e ele esconde isso do pogramador

  //JsonVindoDaApiPokemon.end(); //desalocar memoria deste objeto pois eu nao vou usar mais.
  //Serial.println(ESP.getFreeHeap());
  //pedirDadosPokemonAPIPorId(25);
}

// esp crash decoder eh uma extensao que decodifica o erro no esp. 


//!======================================================
void loop() {
 unsigned int idPokemonAleatorio = random(1,1026);
 printPokemon(idPokemonAleatorio);
 delay(15000);
}


//!======================================================
 String pedirDadosPokemonAPIPorId (unsigned int idPokemon)
(
  String resposta = " ";
  String enderecoPesquisado = enderecoAPI + idPokemon + "/";
  Serial.printf("endereco a ser pesquisado: %S", enderecoPesquisado.c_str());

  HTTPClient textoJsonHTTP;

  textoJsonHTTP.begin(enderecoPesquisado);//o begin inicia o objeto instanciado do tipo HTTP para pegar textos HTTP na internet.
  
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


//!======================================================
void printPokemon(unsigned int idPokemon)
{

  JsonDocument docPokemon;
  JsonDocument docFiltro;
       docFiltro["name"] = true
       docFiltro["id "] = true
       docFiltro["abilities "] = true// se depois eu colocar [0] eu coloco so a primeira habilidade
        // se eu colocar um [0] e depois [ability] e depois [name], ele vem so os dados especificos, nao tudo
       docFiltro["forms"][0]["name"] = true
       docFiltro["types"][0]["types"]["name"] = true

  
  String JsonVindoDaApiPokemon = pedirDadosPokemonAPIPorId (25);
  
  DeserializationError codigoStatusJson = deserializeJson(docPokemon,JsonVindoDaApiPokemon,
  DeserializationOption :: Filter(docFiltro));
  String nomePokemon = docPokemon["name"];
  unsigned int idPokemonAPI = docPokemon["id"];

  JsonArrayConst habilidades = docPokemon["abilities"][0]["ability"]["name"];
  JsonArrayConst formasPossiveis = docPokemon ["forms"][0]["name"];
  JsonArrayConst tipoDoPokemon = docPokemon["types"][0]["types"]["name"];

  Serial.printf("nome do pokemon: %s \n\r", nomePokemon.c_str());
  Serial.printf( "id do pokemon: %03d \n\r",idPokemonAPI );



  Serial.print("habilidades:  ");
  For( int i = 0; i < habilidades.size(); i++)
  {
  Serial.print(habilidades[i]["ability"]["name"].as<const char*>());
  Serial.print(i == (habilidades.size() - 1)? ".":",");
  }



  Serial.print("Formas possiveis: ")
  For( int i = 0; i < formasPossiveis.size(); i++)
  {
  Serial.print(formasPossiveis[i]["ability"]["name"].as<const char*>());
  Serial.print(i == (formasPossiveis.size() - 1)? ".":",");
  }



   Serial.print("tipoDoPokemon: ")
  For( int i = 0; i < tipoDoPokemon.size(); i++)
  {
  Serial.print(tipoDoPokemon[i]["ability"]["name"].as<const char*>());
  Serial.print(i == (tipoDoPokemon.size() - 1)? ".":",");
  }

}