########################################
########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/client  bin/serveur

# liste des fichiers sources 
SRCS0=testClient.c
SRCS1=leServeurTropPool3.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/client: $(SRCS0:%.c=obj/%.o)
	gcc -g -pthread -o $@ $+

bin/serveur: $(SRCS1:%.c=obj/%.o)
	gcc -g -pthread -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~