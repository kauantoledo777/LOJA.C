CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
TARGET = loja

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe loja.txt loja.csv temp.txt
