#include "pico/stdlib.h"

// Pinos
#define led_pin_red 13

// Intervalos de tempo
#define TMP_PONTO 200
#define TMP_TRACO 800
#define TMP_LETRAS 250
#define INTERVALO 3000
#define GAP 125

// Mensagem em morse a ser emitida pelo led
char *mensagem = "... --- ...";

// Funções
void piscarLed(int led, int tempoLigado, int tempoDesligado);
int fimPalavra(char *str, int indice);

int main()
{   
    // Inicializar led
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);
    gpio_put(led_pin_red, false);
    
    char caractere;
    int fimSequencia;
    int intervaloTmp;
    while (true) {
        for (int i = 0; mensagem[i] != '\0'; i++) {

            // Identificar se restam ou não pontos e traços para formar uma letra
            fimSequencia = fimPalavra(mensagem, i);

            if (fimSequencia == 1) { // Se é o fim de uma sequência de morse, aplicar intervalo entre letras
                intervaloTmp = TMP_LETRAS;
            }
            else if (fimSequencia == 2) { // Se acabou a string, não aplicar intervalo
                intervaloTmp = 0;
            }
            else { // Se ainda restam caracteres da sequência de morse, aplicar intervalo de pontos e traços
                intervaloTmp = GAP;
            }

            // Obter caractere atual e piscar led de acordo com o caractere em morse
            caractere = mensagem[i];
            if (caractere == '.') {
                piscarLed(led_pin_red, TMP_PONTO, intervaloTmp);
            }
            else if (caractere == '-') {
                piscarLed(led_pin_red, TMP_TRACO, intervaloTmp);
            }
        }

        // Esperar um intervalo de tempo entre as repetições do SOS
        sleep_ms(INTERVALO);
    }
}

// Pisca um led em um dado pino
void piscarLed(int led, int tempoLigado, int tempoDesligado) {
    gpio_put(led, true);
    sleep_ms(tempoLigado);
    gpio_put(led, false);
    sleep_ms(tempoDesligado);
}

// Identifica se um determinado caractere é o último de uma palavra da string
int fimPalavra(char *str, int indice) {
    // Obter próximo caractere da string
    char prox = str[indice++];

    if (prox == ' ') {
        return 1; // Fim de uma palavra
    }
    else if (prox == '\0') {
        return 2; // Fim de uma palavra e da string
    }
    else {
        return 0; // Não é o fim de uma palavra
    }
}
