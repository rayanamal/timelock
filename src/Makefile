# timelock - Time lock encryption tool
# See COPYING file for copyright and license details.

# timelock version
VERSION := 0.1

GMP := -lgmp
LIBS := $(GMP)

CFLAGS := -std=c17 -pedantic -Wall -Wno-unused-result
LDFLAGS := $(LIBS)

install: etlp dtlp
	mv etlp dtlp ../

# Show compile options set
options:
	echo timelock build options:
	echo "CFLAGS  = $(CFLAGS)"
	echo "LDFLAGS = $(LDFLAGS)"
	echo "CC      = $(CC)"

etlp dtlp: %: %.c
	cc $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f etlp dtlp

.PHONY: install options etlp dtlp clean

.SILENT:
