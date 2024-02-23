
使用systemd服务将程序注册到linux后台长期执行
创建BroadCast.service
```cfg
[Unit]
Description=BroadCast

[Service]
ExecStart=/path/to/your_program
Restart=always

[Install]
WantedBy=multi-user.target

```
将此文件保存到 /etc/systemd/system/ 目录下，并启用该服务：
```bash
sudo systemctl enable BroadCast.service
```
然后启动服务：
```bash
sudo systemctl start BroadCast.service
```

