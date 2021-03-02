# Audrive
Grabar audio en intervalos temporizados

cd Documents

git clone --depth=1 https://github.com/JairoSalazarV/Audrive

cd /Audrive/

mkdir FILES

chmod a+x autorun.sh

g++ audrive.cpp -o audrive

//Once Rasprive is working, add a deamon

crontab -e

//Add line

@reboot /home/pi/Documents/Audrive/autorun.sh

//Reboot and check that AUDRIVE (locally) is working

//Once everythink is Ok, clear folders and FINISH, next reboot will start to updating
