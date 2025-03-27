# Tarefa2---EmbarcaTech

# Projeto: Controle de LED com FreeRTOS no Raspberry Pi Pico

Este projeto demonstra a utilização do FreeRTOS para criar um sistema multitarefa que controla um LED baseado no estado de um botão, usando semáforos para sincronização entre tarefas.

## 📌 Visão Geral

### Hardware
- **Placa**: Raspberry Pi Pico (ou Bit Dog Lab)
- **LED**: Conectado ao GPIO12 (ou onboard no GPIO25)
- **Botão**: Conectado ao GPIO6 (com resistor pull-down)

### Software
- FreeRTOS para multitarefa
- Semáforos para sincronização
- Saída serial para debug (`printf` via USB)

## 🛠️ Funcionalidades

1. **Tarefa 1**: Leitura periódica (100ms) do botão (GPIO6)
2. **Tarefa 2**: Processa o estado do botão e aciona o LED via semáforo
3. **Tarefa 3**: Controla fisicamente o LED (GPIO12) quando acionada

## ⚙️ Configuração do Hardware

### Componentes Necessários
| Item              | Descrição                          |
|-------------------|------------------------------------|
| Raspberry Pi Pico | Placa principal                   |
| LED               | Conectado ao GPIO12 (com resistor) |
| Botão             | Conectado ao GPIO6 (pull-down)     |
| Cabo USB          | Para alimentação e comunicação     |


