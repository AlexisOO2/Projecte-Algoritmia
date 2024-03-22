# Projecte-Algoritmia

## Instruccions
**Algorisme de Lloyd i Algorisme de k-means++**:
La implementació de ambdós algorismes es gairebé la mateixa i s'utilitzen de la mateixa manera.

Cada algorisme necessita els següents paràmetres:
- *filename*: Arxiu que conté les dades a clusteritzar (Ex Dataset6).
- *iteracions*: Nombre máxim d'iteracions que l'algorisme en cuestió s'ha dexecutar.
- *dimensions*: Nombre de dimensions de les dades.
- *labelled*: Valor que indica si les dades venen etiquetades (1 = etiquetades, 0 = no etiquetades).
- *clústers*: Nombre de clústers que l'algorisme ha de generar.

L'execució per terminal tindría un aspecte similar al següent:

- Algorisme de lloyd Ex: `./lloyd datasets/Dataset1.csv 100 16 0 7`
```
./lloyd datasets/Dataset1.csv 100 16 0 7`
`Convergencia a la iteracio 8`
`finished computation at Fri Mar 20 22:14:42 2024`
`elapsed time: 0.425727s`
```
- Algorisme  K-means++ Ex: `./kmeans++ datasets/Dataset1.csv 100 16 0 7`          
```
./kmeans++ datasets/Dataset1.csv 100 16 0 7         
Convergencia a la iteracio 6
finished computation at Fri Mar 20 22:14:55 2024
elapsed time: 0.476043s 
```