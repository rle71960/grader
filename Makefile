grader: grader.c
	mkdir bin
	gcc -o bin/grader grader.c -lpthread
	cp ./grades.txt bin/grades.txt

clean:
	rm -rf bin/
