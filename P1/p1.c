#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "sys/node-id.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PROCESS(timer_experiment_rpl, "RPL/Lite Timer Experiment");
AUTOSTART_PROCESSES(&timer_experiment_rpl);

PROCESS_THREAD(timer_experiment_rpl, ev, data)
{
  static struct etimer et;
  static int iteration_count = 0;

  PROCESS_BEGIN();
  NETSTACK_MAC.on();
  srand(time(NULL));

  while (iteration_count < 500) {
    
    // Caso 1: etimer con valor 10^-5 * CLOCK_SECOND
    etimer_set(&et, CLOCK_SECOND / 100000);
    printf("Nodo %u - Esperando Caso 1: 10^-5 segundos\n", node_id);
    PROCESS_WAIT_UNTIL(etimer_expired(&et));
    int sensor_value1 = rand() % 101;
    printf("Nodo %u - [Caso 1] Valor sensado: %d\n", node_id, sensor_value1);

    // Caso 2: etimer con valor 10^-10 * CLOCK_SECOND
    etimer_set(&et, CLOCK_SECOND / 100000000);
    printf("Nodo %u - Esperando Caso 2: 10^-10 segundos\n", node_id);
    PROCESS_WAIT_UNTIL(etimer_expired(&et));
    int sensor_value2 = rand() % 101;
    printf("Nodo %u - [Caso 2] Valor sensado: %d\n", node_id, sensor_value2);

    // Caso 3: etimer con valor 10^-20 * CLOCK_SECOND
    etimer_set(&et, CLOCK_SECOND / 100000000000000000);
    printf("Nodo %u - Esperando Caso 3: 10^-20 segundos\n", node_id);
    PROCESS_WAIT_UNTIL(etimer_expired(&et));
    int sensor_value3 = rand() % 101;
    printf("Nodo %u - [Caso 3] Valor sensado: %d\n", node_id, sensor_value3);

    iteration_count++;
  }

  printf("Nodo %u - Experimento finalizado después de 500 iteraciones.\n", node_id);

  PROCESS_END();
}

