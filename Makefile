grader: grader.c
	if [ ! -d "./bin" ]; then mkdir bin; fi
	gcc -o bin/grader grader.c -lpthread -std=c99
	cp ./grades.txt bin/grades.txt

clean:
	rm -rf bin/
