
ʹ��systemd���񽫳���ע�ᵽlinux��̨����ִ��
����BroadCast.service
```cfg
[Unit]
Description=BroadCast

[Service]
ExecStart=/path/to/your_program
Restart=always

[Install]
WantedBy=multi-user.target

```
�����ļ����浽 /etc/systemd/system/ Ŀ¼�£������ø÷���
```bash
sudo systemctl enable BroadCast.service
```
Ȼ����������
```bash
sudo systemctl start BroadCast.service
```

