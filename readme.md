
Send the IP addresses corresponding to all network cards on your machine through broadcast

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

~/Broadcast# dpkg-deb -b package/ BroadCast.deb
```
## install
```bash
sudo dpkg -i broadcast.deb
```