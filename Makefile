all: aconfdump.c
	cc aconfdump.c -lasound -o aconfdump

clean:
	rm -f aconfdump
