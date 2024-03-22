# Projecte-Algoritmia

## Instruccions

Tots els programas poden ser compilats

## Algorisme de Lloyd i Algorisme de k-means++
La implementació de ambdós algorismes es gairebé la mateixa i s'utilitzen de la mateixa manera.

Cada algorisme necessita els següents paràmetres:
- *filename*: Arxiu que conté les dades a clusteritzar (Ex Dataset6).
- *iteracions*: Nombre máxim d'iteracions que l'algorisme en cuestió s'ha dexecutar.
- *dimensions*: Nombre de dimensions de les dades.
- *labelled*: Valor que indica si les dades venen etiquetades (1 = etiquetades, 0 = no etiquetades).
- *clústers*: Nombre de clústers que l'algorisme ha de generar.

> En cas de no coneixer el nombre de clústers caldria executar l' [[#Elbow Method]] del respectiu algorisme i dataset.

L'execució per terminal tindría un aspecte similar al següent:

- Algorisme de lloyd Ex: `./lloyd datasets/Dataset1.csv 100 16 0 7`
```
./lloyd datasets/Dataset1.csv 100 16 0 7`
Convergencia a la iteracio 8
finished computation at Fri Mar 20 22:14:42 2024
elapsed time: 0.425727s
```
- Algorisme  K-means++ Ex: `./kmeans++ datasets/Dataset1.csv 100 16 0 7`          
```
./kmeans++ datasets/Dataset1.csv 100 16 0 7         
Convergencia a la iteracio 6
finished computation at Fri Mar 20 22:14:55 2024
elapsed time: 0.476043s 
```

Posteriorment a l'execució dels algorismes es generará un arxiu *output_lloyd.csv* o *output_kmeans++.csv* que contendrá tots els punts dels dataset i a la última columna es mostrará a quin clúster a sigut assignad per l'algorimse.

Un cop generat els outputs dels algorismes es poden realizar les mesures de qualitat.

## Índex de Calinski-Harabasz
El programa que calcula l'índex de Calinski-Harabasz s'anomena CLIndex 

## Elbow Method