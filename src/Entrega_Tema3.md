# Tema 3: practicas 1, 2, 3 y 4

## Practica3_1: primer programa multithreading

Cada constructor de `std::thread` lanza `greetings` con un identificador.
Los cuatro `join()` hacen que el hilo principal espere a todos los trabajadores.
El orden de los saludos puede variar y sus fragmentos pueden mezclarse en la
consola, porque los hilos escriben concurrentemente. El mensaje del hilo
principal aparece despues de que hayan terminado todos.

## Practica3_2: argumentos y factoriales

Se pasan 5, 6, 7 y 8 como argumentos a cuatro hilos. Los resultados son
120, 720, 5040 y 40320. Los mensajes pueden aparecer en cualquier orden o
mezclarse. El hilo principal espera a todos mediante `join()`.

Linea temporal esquematica (no representa duraciones medidas):

```text
tiempo       inicio --------------------------------------> fin
principal    lanzar t1,t2,t3,t4 | join t1,t2,t3,t4 | mensaje
t1                 factorial(5) --- fin
t2                    factorial(6) ---- fin
t3                       factorial(7) --- fin
t4                          factorial(8) ---- fin
```

## Practica3_3: suma paralela

El vector contiene 1.000.000 de enteros, del 1 al 1.000.000.
Cada hilo suma un tramo de 250.000 elementos y escribe solamente en su
propia casilla del vector `parciales`. Despues de los cuatro `join()`, el
hilo principal suma las casillas e imprime **500000500000**.

```text
tiempo       inicio --------------------------------------> fin
principal    preparar vector | lanzar hilos | join todos | sumar e imprimir
t1                               [0,250000) ------ fin
t2                               [250000,500000) ----- fin
t3                               [500000,750000) ---- fin
t4                               [750000,1000000) ------ fin
```

Los intervalos incluyen el inicio y excluyen el final. El orden y la
duracion de los hilos dependen del planificador.

## Practica3_4: entendiendo detach()

`detach()` separa el hilo trabajador de su objeto `std::thread`. El hilo
principal continua sin esperarlo y ya no puede llamar a `join()` sobre ese
objeto. El trabajador sigue perteneciendo al proceso.

Para repetir el experimento, cambiar `esperaPrincipalMs` de 500 a 3000 en
`Practica3_4/main.cpp`, recompilar y ejecutar.

### Caso 1: espera principal de 500 ms

```text
tiempo aproximado   0 ms              500 ms                 2000 ms
principal          lanzar + detach | esperar | fin del proceso
hilo de fondo      empezar tarea --- interrumpido al finalizar el proceso
```

El proceso termina antes de que transcurran los dos segundos de la tarea.
El hilo de fondo no llega a imprimir "tarea larga completada".

### Caso 2: espera principal de 3000 ms

```text
tiempo aproximado   0 ms                    2000 ms          3000 ms
principal          lanzar + detach | esperar ---------------- fin
hilo de fondo      empezar tarea ---------- completar y fin
```

La tarea termina aproximadamente a los dos segundos e imprime su mensaje
de finalizacion. El hilo principal termina aproximadamente al tercer segundo.
Esta espera permite observar la diferencia, pero `sleep_for()` no garantiza
la finalizacion del trabajador: el planificador puede retrasarlo. Para esperar
su finalizacion de forma garantizada se utilizaria `join()` en lugar de `detach()`.
Los tiempos y el orden de los primeros mensajes son aproximados.

## Prac_1M: ejercicio adicional

Este programa no corresponde a una practica del PowerPoint proporcionado.
Cuatro hilos incrementan un contador atomico un millon de veces cada uno.
El resultado esperado es 4000000. El contador atomico evita una carrera de
datos. Si el objetivo de otro enunciado fuera observar esa carrera, esta
version representa la solucion sincronizada.
