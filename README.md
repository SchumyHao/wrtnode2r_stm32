
## In the ununtu 14.04 x86\_64

There is an example in the linux.In the windows you can see the rt-thread's document.

### Install arm cross-compiler.

##### Install python and scons


	sudo apt-get install python scons


##### Install gcc-arm-none-eabi


	sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded

	sudo apt-get update

	sudo apt-get install gcc-arm-none-eabi


### Download the rt-thread and WRTnode-stm32 in the same directory

	git@github.com:RT-Thread/rt-thread.git

	git clone git@github.com:WRTnode/wrtnode2r_stm32.git\

### Configure the WRTnode-stm32

- Open the wrtnode2r\_stm32/rtconfig.py , change the \
	 '/Users/schumy/gcc-arm-none-eabi/bin' \ 
	as "/usr/bin" in the line 16.
- Open the wrtnode2r\_stm32/SConstruct , \
	change "/../rtt" as "/../rt-thread" in the line 8.
	
### Compile and Clean
##### complie

	scons -j 4

##### clean

	scons clean
