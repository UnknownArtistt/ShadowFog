[Leer esto en Español](./README.md)
# ShadowFog
ShadowFog is an anonymity tool developed in C++ that leverages Tor and Proxychains to facilitate secure and anonymous web browsing. This utility automates the entire process of installing, configuring, and executing Tor and Proxychains on your system. It allows users to run browsers and other applications through Tor and Proxychains seamlessly, ensuring your online activities remain private and protected.

## Context

In today's digital age, privacy and anonymity on the internet are more than just luxuries; they are essential rights that protect individual freedom. As our lives become increasingly intertwined with the internet, the ability to safeguard personal information from unauthorized access and surveillance has become crucial. Whether you're a journalist, a privacy advocate, or simply a cautious user, maintaining anonymity can shield you from targeted ads, prevent identity theft, and even protect your freedom of speech under oppressive regimes.

ShadowFog is designed to empower users by providing robust tools for anonymous web navigation. Leveraging the power of Tor and Proxychains, ShadowFog automates the complex processes of installation, configuration, and operation, making it easier than ever to browse the web securely and anonymously. This tool is not just about accessing the web; it's about reclaiming your right to privacy in an era where digital footprints are constantly monitored.

## Disclaimer

This software is provided "as is", without any kind of warranty, expressed or implied. In no event shall the author or contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.

The use of ShadowFog for activities that violate the law is strictly prohibited. The developer of ShadowFog does not endorse the illegal use of anonymity tools and is not responsible for any misuse of the software. The end user is solely responsible for ensuring that all their actions with ShadowFog comply with the applicable laws in their jurisdiction.

## Installation and Usage

**1. Clone the repository / Download source code**

First, you need to clone the ShadowFog repository to your local machine using GitHub or download the source code.
- git clone https://github.com/Julen-H/ShadowFog

**2. Run the installation script / Compile the program**

ShadowFog includes a bash script that prepares all necessary dependencies and compiles the program. Administrator permissions (sudo) are required to run this script. The script will install a C++ compiler and figlet. If you do not use the script, you can install the packages this way:
- sudo apt-get install g++ -y
- sudo apt-get install figlet -y

Once installed, run the script in administrator mode (sudo) or directly execute the script and it will automatically download and install. Furthermore, once the packages are installed, the script will compile and execute the program automatically.

**ATTENTION**
When the script compiles and runs the program, it will execute ShadowFog as administrator (sudo) as you will need to perform the initial Proxychains configuration. This configuration is done by editing parameters in the configuration file (the .conf file located at /etc/proxychains4.conf), for which you need administrator permissions. That is why it is executed as administrator (sudo). Once the configuration is done, close the program and run it with your normal user. Do the same when you want to use the program in your day-to-day.

Run the script in administrator mode (sudo)
- sudo ./shadowfog.sh

**3. Initial Configuration**

After the script has compiled and run the program and before you start browsing securely and anonymously, it is crucial to perform an initial configuration. This configuration includes the installation and setup of Tor and Proxychains, which is done through the -configure command within ShadowFog. Once Tor and Proxychains are installed, you need to configure Proxychains. For this, we can use the -set command and specify the chain mode.

To install Tor and Proxychains
- -configure

To configure Proxychains
|Mode|Command|
| -- | -- |
|Dynamic|-set dynamic|
|Random|-set random 3|
* The number after random is the chain length, in this case, Proxychains will bounce through 3 proxies. You can choose the length as you see fit, by default it is set to 2

**4. Start using ShadowFog**

Once you have completed the initial configuration, close the program using the -exit command and run it with your normal user (./ShadowFog). To start browsing anonymously, first, you need to change the Proxy settings of Mozilla Firefox. Open the browser and go to the **"Hamburger Menu"** (the icon with three horizontal lines). Access **"Settings"** and search for the word proxy. It will show a match, access the network settings and enter these values and check the box **"DNS proxy using SOCKS v5"** which is at the bottom.

This will be the configuration to ensure all your network traffic passes through Tor and Proxychains since browsers use webRTC which can lead to DNS leaks revealing your real IP. This configuration allows anonymous browsing. You will need to use this proxy setting in Mozilla Firefox to browse.

PHOTO OF FIREFOX CONFIGURATION

When you stop using ShadowFog and want to browse "normally" simply select the mode **"Use system proxy settings"** and uncheck the box **"DNS proxy using SOCKS v5"**. If you want to browse anonymously again, do the reverse operation, select the mode **"Manual proxy configuration"** and check the box **"DNS proxy using SOCKS v5"**.

PHOTO OF DEFAULT FIREFOX CONFIGURATION

Once you have configured Mozilla Firefox, enter these commands to start the service and begin browsing:

|Action|Command|
| -- | -- |
|-runsrv|Starts the Tor service|
|-status|Checks the status of the service to make sure it is active|
|-start firefox|Runs Firefox or the program you want to use to browse with Tor and Proxychains|
|-stopsrv|Stops the Tor service, run it after you finish browsing and after closing the browser. Finally, change the proxy configuration of Firefox|
* You can start the program you need by specifying it after -start (e.g., -start nmap -targetadress

## 5. Tips and Best Practices (Important)

ShadowFog allows creating a backup of the Proxychains configuration file. Before performing the initial Proxychains configuration, I encourage all users to make a backup to have a copy and be able to restore it in case of error or if you want to change the mode.

Run the **-cporiginalconf** command in the ShadowFog shell. It will ask you to insert the path where the configuration file backup will be made. You can leave it on the desktop or inside the ShadowFog directory (e.g., /home/myuser/Desktop/conforiginal.conf).

If you need to restore the initial configuration or wish to change the chain mode (from dynamic to random or vice versa), replace the original file with the backup file, or if you prefer and find it easier, copy all the content of the backup into the original configuration file.

Remember, if you want to change the chain mode, you must restore the initial configuration and then run the program as administrator (sudo). Then, perform the configuration again specifying the mode you want.

Remember, the configuration file is located in the etc directory (/etc/proxychains4.conf).

You can check if Tor and Proxychains are working correctly and hiding your real IP by making a curl request. To do this, install curl and run the following command in a new terminal:

- sudo apt install curl
- proxychains4 curl https://icanhazip.com

Check if the IP is different from yours, if it is, it means you have configured everything correctly and you are ready to browse.

## 6. Step-by-Step Summary Guide

|Steps|Command|
| -- | -- |
|Clone the repository|git clone https://github.com/Julen-H/ShadowFog|
|Run the script with sudo|sudo ./shadowfog.sh|
|Install Tor and Proxychains|-configure|
|Create a backup of the Proxychains configuration file|-cporiginalconf|
|Adjust the Proxychains mode|-set dynamic or -set random 2|
|Close the program|-exit|
|Run it with your normal user|./ShadowFog|
|Adjust the proxy settings in Mozilla Firefox|See point 4|
|Start the Tor service|-runsrv|
|Check that the Tor service is active|-status|
|Start a browser or program|-start firefox|
|Browse securely and anonymously and enjoy :)||
|Close the browser when you are done||
|Adjust the default settings in Firefox|See point 4|
|Stop the Tor service|-stopsrv|
|Close ShadowFog|-exit|
