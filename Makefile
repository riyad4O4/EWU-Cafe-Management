SOURCES = Source_Codes/main.c \
          Source_Codes/Account.c \
          Source_Codes/admin_menu.c \
          Source_Codes/customer.c \
          Source_Codes/main_menu.c \
          Source_Codes/payment.c
make:
	gcc -IHeader_Files $(SOURCES) -o cafe_management
clean:
	rm -f $(TARGET)