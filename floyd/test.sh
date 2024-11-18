#!/bin/bash

floyd="./floyd"
out_file="/tmp/floyd-out"

for i in ./tests/input/*.txt; do
    file_name=$(basename "$i")
    $floyd -f "$i" >"$out_file"

    if diff -w "$out_file" "./tests/output/$file_name"; then
        echo "Teste $file_name: OK"
    else
        echo "Teste $file_name: ERRO"
    fi
done

rm "$out_file"
