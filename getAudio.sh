FECHA=`date +"%d_%m_%y_%H_%M_%S"`
FILEPATH="/home/pi/Audrive/FILES/${FECHA}.wav"
echo "Recording (${1} seconds) ${FILEPATH}"
XDG_RUNTIME_DIR=/run/user/1000 /usr/bin/arecord --duration=${1} "${FILEPATH}"
echo "Sleeping ${2} seconds"
sleep ${2}
/home/pi/Audrive/getAudio.sh $1 $2
