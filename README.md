# raspberry-pi-ppm-rc-in
树莓派PPM解码用户空间驱动，直接读取PPM编码器输入，GPIO 方式读取，实时解码，并存入SHM中， key 2048。
PPPM decodeer for raspberry pi running in the user space.
Reading the ppm from gpio.7 decode it and save the pwm of each channel into SHM.

# 软件准备(install the ppmdecode)

$ sudo apt-get install pigpio

$ git clone https://github.com/crossa/raspberry-pi-ppm-rc-in

$ cd raspberry-pi-ppm-rc-in

$ ./configure && make && make install


# PPM解码器启动(startup the ppmdecode)
$ sudo nohup  ppmdecode L &

# PPM解码开机自启动(startup the ppmdecode with system)

$ sudo echo "nohup ppmdecode L &" >> /etc/rc.local

#使用systemd管理的系统，需启用rc.local,然后重新启动系统(For systemd managed system, rc.local service should be enabled.)
$sudo systemctl enabled rc.local
$sudo reboot


#硬件准备（plug the ppmencode）

首先确定ppmdecode正在运行。（Check the process and make sure that the ppmdecode is running）
$sudo ps aux | grep ppmdecode

1.将8通道接收机连接到PPM编码器 （Connect your 8 channel reciver to the ppmencode）
2.PPM编码器的GND 连接到  树莓派的GND ( Connect  the gnd of ppmencode to the  gnd of raspberry pi )
3.PPM编码器的SIGNAL／PWM 连接到  树莓派的GPIO.7( Connect  the pwm/singal pin of  ppmencode to the GPIO of raspberry pi )
3.PPM编码器的+ 连接到 正极（Connect  the  VCC pin of ppmencode to the VCC supplier）

#测试（Testing）

1.打开遥控器.（Power on your  transmitter）
2.运行ppmdecode输出程序（Running another instance of  ppmdecode to check it）

$sudo ppmdecode P

3.每个通道的数据会被打印在屏幕上（Pwm values of each channel will be print on the screen）





