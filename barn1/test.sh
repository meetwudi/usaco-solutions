PROGNAME="barn1"
for i in {1..2}
do
  cp "${PROGNAME}.in${i}" "${PROGNAME}.in"
  ./main
  diff "${PROGNAME}.out" "${PROGNAME}.out${i}"
  echo "Test $i OK"
done
