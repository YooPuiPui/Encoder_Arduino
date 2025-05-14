# Encoder_Arduino

# 🧭 Medidor de distancia con Encoder - Arduino

Este proyecto implementa un sistema de medicion utilizando un **encoder** conectado a un **Arduino uno**. La distancia recorrida se calcula a partir del numeero de pulsos generados por el encoder mientras gira.

## 🎯 Objetivos del proyecto

> Medir la distancia total recorrida desde un punto inicial hasta que el encoder deje de emitir pulsos durante al menos 2 segundos.

## 🔌 Conexiones

| Encoder | Arduino |
|--------|---------|
| Señal A | D2      |
| Señal B | D3      |
| GND     | GND     |
| VCC     | 5V      |

> 📌 Asegúrate de usar `INPUT_PULLUP` para evitar lecturas erráticas.
