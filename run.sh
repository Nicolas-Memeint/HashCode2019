#! /bin/sh

mkdir -p out

echo "--- run.sh ---"
for f in 'in'/*.txt; do
    echo $f: pending...
    out=${f#'in/'}
    ./main "$f" > "out/${out%.txt}.out"
done
echo "---  done  ---"
