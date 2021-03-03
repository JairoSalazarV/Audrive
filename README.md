# Audrive
Grabar audio en intervalos temporizados


git clone --depth=1 https://github.com/JairoSalazarV/Audrive

cd /Audrive/

chmod a+x install.sh

//Leer el siguiente link para configurar microfono
//https://www.internetdelascosas.cl/2014/09/01/grabando-e-interpretando-sonidos-con-la-raspberry-pi/

./install.sh

//Guardar cambios

sudo alsactl store 1

//[EJEMPLO] arecord -d 10 -f cd ~/Audrive/FILES/test.wav

crontab -e

//Add line

@reboot /home/pi/Audrive/getAudio.sh [audioDuration] [sleepTime]

//Reboot and check that AUDRIVE (locally) is working

//Once everythink is Ok, clear folders and FINISH, next reboot will start to updating
