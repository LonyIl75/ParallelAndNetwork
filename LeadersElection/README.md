# PROJET PROGRAMMATION REPARTIE :

## Nécessaires :

	-	sudo apt-get install libgsl-dev

### Vocabulaire  :

- testServ : l'exécutable associe a leServeurTropPool3.c et 
- testClient : l'exécutable associé a testClient.c
- **CH** désigne *ClientHandler* 
- **NH** designe *NodeHandler*

## Compiler :

__Serveur__
	gcc -g -pthread leServeurTropPool3.c Links.c my-util.c my_poll.c my_sockaddr.c Cluster.c hashAddr.c tableau.c algebre.c Point.c eispack.c kmeans.c my_file.c helper_function.c MyNode.c ParserJ.c ColorParam.c message.c -lm  -lgslcblas  -lgsl  -o testServ

__Client__
		gcc -g -pthread testClient.c clientTropPool.c Links.c my-util.c my_poll.c my_sockaddr.c Cluster.c hashAddr.c tableau.c algebre.c Point.c eispack.c kmeans.c my_file.c message.c helper_function.c MyNode.c ParserJ.c colorParam.c -lm  -lgslcblas  -lgsl  -o testClient

## Lancement : 
__Les Serveurs__ ( clientHandler + nodeHandler ) :

		./testServ PORT_CH_IN PORT_CH_OUT PORT_CH_INOUT NH_IN NH_OUT STRICT_PATH FILENAME

__Noeuds-clients__ (NB_NODE)   :

		./testClient PORT_CH_IN IP_CH NB_NODE
 

## Exemple (avec makefile):

### Executer le makefile :
		make

### Lancer les serveurs ( clientHandler + nodeHandler ) :
		./bin/serveur 3490 3491 3492 3590 3591 . graph-test.txt  // si graph-test dans repertoire courant

### Lancer 10 noeuds-clients :
		./bin/client 3490 0.0.0.0 10



