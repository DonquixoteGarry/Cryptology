.PHONY: tool,0,1
tool:
	./other/RSATool.exe
1:
	g++ code/rsa.cpp -o code/rsa.exe
	./code/rsa.exe
	rm code/rsa.exe
0:
	rm code/*.exe
test:
	g++ code/rsa_test.cpp -o code/rsa_test.exe
	./code/rsa_test.exe
	rm code/rsa_test.exe