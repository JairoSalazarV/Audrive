# Audrive
Grabar audio en intervalos temporizados


git clone --depth=1 https://github.com/JairoSalazarV/Audrive

cd /Audrive/

chmod a+x install.sh

./install.sh

crontab -e

//Add line

@reboot /home/pi/Audrive/getAudio.sh [audioDuration] [sleepTime]

//Reboot and check that AUDRIVE (locally) is working

//Once everythink is Ok, clear folders and FINISH, next reboot will start to updating
