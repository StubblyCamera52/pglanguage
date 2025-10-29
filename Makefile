CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g

SRC = src
INC = src
BIN = bin

TARGET = $(BIN)/mylang

SRCS = $(wildcard $(SRC)/*.c)

OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $^

$(BIN)/%.o: $(SRC)/%.c
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(BIN)

run: all
	./$(TARGET) $(ARGS)
