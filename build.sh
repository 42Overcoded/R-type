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
      "Usage: $0 [-p|--pack]"
      exit 84
      ;;
    --)
      shift;
      break
      ;;
    *)
      echo "Unexpected option: $1"
      ;;
  esac
done

mkdir build > /dev/null 2>&1
cd build > /dev/null 2>&1
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
if [ $PACK = True ]; then
    cpack -C CPackConfig.cmake
fi
cd - > /dev/null 2>&1
