
Broadcast with all local network  by asio

## how to build

```bash
mkdir build
cd build

cmake ../

make -j8

```
## make deb

then copy file to  ./package/usr/local/bin

```bash
cp 
sudo dpkg-deb --build broadcast.deb

```
## install
```bash
sudo dpkg -i broadcast.deb
```