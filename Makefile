SOURCES = Source_Codes/main.c \
          Source_Codes/Account.c \
          Source_Codes/admin_menu.c \
          Source_Codes/customer.c \
          Source_Codes/main_menu.c \
          Source_Codes/payment.c \
          Source_Codes/Sales.c

TARGET = cafe_management.exe

all:
	gcc -IHeader_Files $(SOURCES) -o $(TARGET)


clean:
	cmd /c del /F /Q cafe_management.exe