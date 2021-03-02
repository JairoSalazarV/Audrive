chmod a+x getAudio.sh
mkdir 'FILES'
chmod a+x getAudio.sh

sudo apt-get update
sudo apt-get install alsa-base alsa-utils
sudo apt-get install libasound2-dev
sudo alsamixer
sudo alsactl store 1

