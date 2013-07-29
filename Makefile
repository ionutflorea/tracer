KDIR=/lib/modules/$(shell uname -r)/build

kbuild:
	make -C $(KDIR) M=$(shell pwd)

clean:
	make -C $(KDIR) M=$(shell pwd) clean
	-rm -f *~
