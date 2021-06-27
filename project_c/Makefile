FLAGS = -w -Wextra -std=c99 -O2 -g -Wall -D_GNU_SOURCE
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER = gcc
INCLUDES = includes
SRC = src
OBJ = obj

program: 
	make stats
	make user
	make users
	make business
	make businesses
	make review
	make reviews
	make interface
	make view
	make sgr
	make controller
	make main
	make executable

stats: $(SRC)/stats.c $(INCLUDES)/stats.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/stats.o $(PKG) -c $(SRC)/stats.c

user: $(SRC)/user.c $(INCLUDES)/user.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/user.o $(PKG) -c $(SRC)/user.c 

users: $(SRC)/users.c $(INCLUDES)/users.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/users.o $(PKG) -c $(SRC)/users.c

business: $(SRC)/business.c $(INCLUDES)/business.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/business.o $(PKG) -c $(SRC)/business.c

businesses: $(SRC)/businesses.c $(INCLUDES)/businesses.h $(OBJ)/stats.o
	$(COMPILER) $(FLAGS) -o $(OBJ)/businesses.o $(PKG) -c $(SRC)/businesses.c

review: $(SRC)/review.c $(INCLUDES)/review.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/review.o $(PKG) -c $(SRC)/review.c 

reviews: $(SRC)/reviews.c $(INCLUDES)/reviews.h $(OBJ)/stats.o
	$(COMPILER) $(FLAGS) -o $(OBJ)/reviews.o $(PKG) -c $(SRC)/reviews.c

interface: $(SRC)/interface.c $(INCLUDES)/interface.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/interface.o $(PKG) -c $(SRC)/interface.c

view: $(SRC)/view.c $(INCLUDES)/view.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/view.o $(PKG) -c $(SRC)/view.c

sgr: $(SRC)/sgr.c $(OBJ)/users.o $(OBJ)/reviews.o $(OBJ)/businesses.o $(INCLUDES)/sgr.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/sgr.o $(PKG) -c $(SRC)/sgr.c

controller: $(SRC)/controller.c $(OBJ)/sgr.o $(INCLUDES)/controller.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/controller.o $(PKG) -c $(SRC)/controller.c

main: $(SRC)/main.c $(OBJ)/controller.o $(OBJ)/sgr.o
	$(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c

executable: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/user.o $(OBJ)/users.o $(OBJ)/business.o $(OBJ)/businesses.o $(OBJ)/review.o $(OBJ)/reviews.o $(OBJ)/view.o $(OBJ)/sgr.o $(OBJ)/controller.o $(OBJ)/stats.o
	$(COMPILER) $(FLAGS) $(OBJ)/stats.o $(OBJ)/user.o $(OBJ)/users.o $(OBJ)/business.o $(OBJ)/businesses.o $(OBJ)/review.o $(OBJ)/reviews.o $(OBJ)/interface.o $(OBJ)/view.o $(OBJ)/sgr.o $(OBJ)/controller.o $(OBJ)/main.o $(PKG) -o program

memcheck: 
	valgrind --leak-check=yes ./program

clean:
	rm -rf $(OBJ)/*.o program