CC = gcc
CFLAGS = -Wall -Wextra -I../Header_Files

TARGET = customer_test

SRC = customer.c customer_test.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)