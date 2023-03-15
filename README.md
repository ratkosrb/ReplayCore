# ReplayCore
## Linux 
### Dependencies
- libssl
- mariadb
- libcrypto 
- zlib

libssl and libcrypto should come with openssl install. 
Mariadb can be changed to you mysql by modifying the make file to use `-lmysqlclientp` instead of `-lmariadb`.
`-pthread` might be needed in some cases too.
### compile
 Run make on ReplayCore folder.
 ### run
 ./replayCore
