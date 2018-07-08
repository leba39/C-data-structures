#MAKEFILE
COMP = gcc
CFLAGS = -g
BINARIES = bbl ms_leba ms_morton

all: clean $(BINARIES)

#bubble sort
bbl: bbl_test.c
	$(COMP) $(CFLAGS) $< -o $@
ms_leba: ms_test_leba.c
	$(COMP) $(CFLAGS) $< -o $@
ms_morton: ms_test_morton.c
	$(COMP) $(CFLAGS) $< -o $@
cleantxt:
	rm -f *txt
clean:
	rm -f $(BINARIES)
.PHONY: all clean
