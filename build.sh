##
## EPITECH PROJECT, 2023
## R-type
## File description:
## build
##

PACK=False

SHORT=p,h
LONG=pack,help
OPTS=$(getopt -a -n build --options $SHORT --longoptions $LONG -- "$@")

eval set -- "$OPTS"

while :
do
  case "$1" in
    -p|--pack)
        PACK=True
        echo "Packaging enabled"
        shift
      ;;
    -h | --help)
      echo "Usage: $0 [-p|--pack]"
      exit 0
      ;;
    --)
      shift;
      break
      ;;
    *)
      echo "Unexpected option: $1"
      exit 84
      ;;
  esac
done

original_dir=${PWD}

mkdir build > /dev/null 2>&1
cd build > /dev/null 2>&1
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j 7
if [ $PACK = True ]; then
  cpack -C CPackConfig.cmake
fi
cd $original_dir > /dev/null 2>&1
