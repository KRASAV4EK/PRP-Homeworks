CFLAGS+=  -pedantic -Wall -Werror -std=c99 -O3 -g
HW=main
ZIP=zip

$(HW): grep.c 
	$(CC) $(CFLAGS) grep.c -o $(HW)

zip:
	$(ZIP) $(HW)-brute.zip grep.c

clean:
	$(RM) -f *.o
	$(RM) -f $(HW)
	$(RM) -f $(HW)-brute.zip

.PHONY: clean zip
