.PHONY: tool,0,1
tool:
	./other/hash.exe
1:
	g++ code/md5.cpp -o code/md5.exe
	./code/md5.exe
	rm code/md5.exe
0:
	rm code/*.exe
test:
	g++ code/md5_test.cpp -o code/md5_test.exe
	./code/md5_test.exe
	rm code/md5_test.exe