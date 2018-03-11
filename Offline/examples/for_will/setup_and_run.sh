#/bin/sh

c++ example.cpp -o ex1.o
c++ example2.cpp -o ex2.o
c++ example3.cpp -o ex3.o

echo "-----------------------------------------------------------------------------------------------------"
echo "The First Run: "
echo "This example you don't have to delete the pointer for the array, is this because it is on the stack?"
echo "I'm confused about this because valgrind returns no errors."
./ex1.o
sleep .5
echo "-------------------------------------------------"
echo "The valgrind: "
valgrind --leak-check=yes ./ex1.o
echo "-----------------------------------------------------------------------------------------------------"
echo "The Second Run: "
echo "There is an issue with the second new operator in the loop. I believe this causes the second error"
echo "in valgrind."
./ex2.o
sleep .5
echo "-------------------------------------------------"  
echo "The valgrind: "
valgrind --leak-check=yes ./ex2.o
echo "-----------------------------------------------------------------------------------------------------"
echo "The Third Run: "
echo "There is an issue with the second new operator in the loop. I believe this causes the second error"
echo "in valgrind."
./ex3.o
sleep .5
echo "-------------------------------------------------"  
echo "The valgrind: "
valgrind --leak-check=yes ./ex3.o
echo "-----------------------------------------------------------------------------------------------------"
