ifneq ($(shell command -v musl-clang 2>/dev/null),)
    CC = musl-clang
else
    CC = clang
endif

CFLAGS = -Wall -Wextra -O2
LDFLAGS = -static

TARGET = fronts
SRC = fronts.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
