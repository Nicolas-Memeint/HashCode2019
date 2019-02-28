#! /bin/sh

mkdir -p out

echo "--- run.sh ---"
for f in 'in'/*.in; do
    echo $f: pending...
    out=${f#'in/'}
    ./main "$f" > "out/${out%.in}.out"
done
echo "---  done  ---"
