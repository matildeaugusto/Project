# Definindo o compilador
CC = gcc

# Definindo os flags do compilador
CFLAGS = -Wall -g

# Nome do executável
TARGET = navigate

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

# Regra para compilar o arquivo objeto
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Limpar arquivos gerados
clean:
	rm -f *.o $(TARGET)
