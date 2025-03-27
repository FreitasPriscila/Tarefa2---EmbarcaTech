#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

#define LED_PIN 12
#define BOTAO_PIN 6


//variáveis globais
volatile bool botao_pressionado = false;  
volatile bool led_ligado = false;         

// Semáforos
SemaphoreHandle_t xSemaphoreBotao = NULL;  // nova leitura do botão
SemaphoreHandle_t xSemaphoreLED = NULL; 

// Protótipos das tarefas
void task_leitura_botao(void *pvParameters);
void task_processamento_botao(void *pvParameters);
void task_controle_led(void *pvParameters);



int main(){
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);  // LED como saída

    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);  // Botão como entrada
    gpio_pull_down(BOTAO_PIN);   
    
    // Cria os semáforos
    xSemaphoreBotao = xSemaphoreCreateBinary();  // Inicialmente bloqueado
    xSemaphoreLED = xSemaphoreCreateBinary(); 

      // Cria as tarefas
    xTaskCreate(task_leitura_botao, "Leitura Botao", 256, NULL, 1, NULL);
    xTaskCreate(task_processamento_botao, "Processa Botao", 256, NULL, 2, NULL);
    xTaskCreate(task_controle_led, "Controle LED", 256, NULL, 3, NULL);

    vTaskStartScheduler();  // Inicia o escalonador

    while (1)
    ;  // Fica preso aqui
    return 0;
}

// Tarefa 1: Leitura do botão (executa a cada 100ms)
void task_leitura_botao(void *pvParameters) {
    for (;;) {
        
        botao_pressionado = gpio_get(BOTAO_PIN);
        vTaskDelay(pdMS_TO_TICKS(50));  // Debounce

        // Envia sinal para a tarefa de processamento
        xSemaphoreGive(xSemaphoreBotao);

        vTaskDelay(pdMS_TO_TICKS(100));  // Executa a cada 100ms
    }
}

// Tarefa 2: Processamento do botão (aciona a tarefa do LED se necessário)
void task_processamento_botao(void *pvParameters) {
    for (;;) {
        // Aguarda nova leitura do botão
        if (xSemaphoreTake(xSemaphoreBotao, portMAX_DELAY) == pdTRUE) {
            if (botao_pressionado) {
                gpio_put(LED_PIN, led_ligado);  
                printf("Botao pressionado! Acionando LED...\n");
                xSemaphoreGive(xSemaphoreLED);  // Aciona a tarefa do LED
            }
        }
    }
}

// Tarefa 3: Controle do LED (executa apenas quando acionada)
void task_controle_led(void *pvParameters) {
    for (;;) {
        // Aguarda sinal para ligar/desligar o LED
        if (xSemaphoreTake(xSemaphoreLED, portMAX_DELAY) == pdTRUE) {
            led_ligado = botao_pressionado;  // LED reflete o estado do botão

            // Simula o controle do LED (substitua por GPIO real)
            printf("LED: %s\n", led_ligado ? "LIGADO" : "DESLIGADO");
        }
    }
}
