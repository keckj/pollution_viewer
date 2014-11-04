
"script pour rajouter un tiret avant le type de chaque station
for i in split(system("cat station_types | tr '\n' ' '"))
    echo "Substituing ".i."..."
    try
        execute '%s/'.i.'.*$/- '.i.'/g'
    endtry
endfor

