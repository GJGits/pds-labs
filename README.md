# pds-labs

Repository contenente le soluzioni ai laboratori del cordo di Programmazione di Sistema del Politecnico di Torino (a.a. 2019/2020). Attualmente le soluzioni riguardano solamente le parti in C++ e presto verranno aggiunti tag per definire lo stato dei vari laboratori.

# Utilizzo con Docker

Per quanto riguarda la parte di C++ ho creato una semplice immagine docker basata su linux con all'interno tool per compilare e debuggare [gjcode-pds](https://hub.docker.com/repository/docker/gjcode/gjcode-pds). Nelle cartelle dei laboratori è già presente un apposito Dockerfile pronto per l'uso.

## Utilizzatori Linux e MacOS

Per provare il codice assicurarsi di avere installato [Docker](https://www.docker.com/), posizionarsi nella cartella di riferimento di uno dei labotari ed eseguire il comando  `./br`. Questo è il comando che effettua la build del container e ne lancia un'istanza. `Al primo lancio è fondamentale decommentare il comando che effettua la build dalla seconda in poi ricommentare il comando`. A questo punto ci si trova nel container e per eseguire il codice basta lanciare il comando `./run-lab <nome-cartella>`, questo creerà un eseguibile con il nome specificato ed eseguirà il programma.

## Utilizzatori Windows

Il procedimento è del tutto analogo a quello precedente, tuttavia non sarà possibile utilizzare direttamente il comando `./br` essendo questo uno script Linux. Aprire quindi il file `br` e lanciare da terminale i comandi scritti all'interno, il resto rimane invariato.
