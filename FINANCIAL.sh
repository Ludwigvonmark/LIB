 #!/bin/bash 
g++ LIBDBG.cpp -std=c++1z -O3 -lssl -lcrypto -lcurl -o LIBDBG -lstdc++fs && ./LIBDBG $@
