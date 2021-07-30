# Proyecto de CPD (Travelling Salesman Problem)

## Integrantes

- Renato Bacigalupo
- Rodrigo Cespedes
- Benjamin Diaz

## Ejecución

Se necesita omp instalado.

- `make`
- `make run` (versión sin gasolina)
- `make runfuel` (versión con gasolina)
- `make clean` (limpiar todos los ejecutables)

## Ciudades

- 0 - Lima Centro
- 1 - Lince
- 2 - Miraflores
- 3 - Barranco
- 4 - Rimac
- 5 - Los Olivos
- 6 - La Molina
- 7 - La Victoria
- 8 - Magdalena del Mar
- 9 - San Borja

## Camino óptimo sin gasolina

Lima Centro -> Rimac -> Los Olivos -> Magdalena del Mar -> Lince -> Miraflores -> Barranco -> La Molina -> San Borja -> La Victoria -> Lima Centro

(0 -> 4 -> 5 -> 8 -> 1 -> 2 -> 3 -> 6 -> 9 -> 7 -> 0)

Distancia total: 74.3 km.

## Camino óptimo con gasolina

Empieza con 20 de gasolina, la gasolina de un camino es 1:1 con la distancia, para calcular el nuevo costo de un camino es lo siguiente:

- Si tengo gasolina, tomo el camino y le resto la gasolina.
- Si no me alcanza la gasolina, el costo seria el camino + (camino - gasolina_actual) \* 2.

Lima Centro -> Rimac -> Los Olivos -> Magdalena del Mar -> Miraflores -> Barranco -> San Borja -> La Molina -> La Victoria -> Lince -> Lima Centro

(0 -> 4 -> 5 -> 8 -> 2 -> 3 -> 9 -> 6 -> 7 -> 1 -> 0)

Costo: 84.4
