#!/bin/sh
for dir in `ls .`
 do
   if [ -d $dir ]
   then
     cd $dir
     for cdir in `ls .`
        do
            if [ -d $cdir ]
            then
                cd $cdir
                    test -e ./Makefile && make clean
                cd ..
            fi
        done
        test -e ./Makefile && make clean
     cd ..
   fi
done 
