
Broadcast with all local network  by asio

## how to build

```bash
mkdir build
cd build

cmake ../

make -j8

```
## make deb

```bash
cp cmake-build-debug/broadcast package/usr/local/bin/
sudo dpkg-deb --build broadcast.deb

```
## install
```bash
sudo dpkg -i broadcast.deb
```