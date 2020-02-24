## To run:
### g++ main3C.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
### ./a.out 3B_input.pnm 3B_output.pnm


## To upload all directories from local computer to the ix-dev:
### scp -r /Users/mamtajakter/Documents/COURSES-UO-MS/CIS607/3C  makter2@ix-dev.cs.uoregon.edu:/home/users/makter2/cis330/3C


## To upload only one file from local computer to the ix-dev:
### scp /Users/mamtajakter/Documents/COURSES-UO-MS/CIS607/3C/readme.md  makter2@ix-dev.cs.uoregon.edu:/home/users/makter2/CIS607/3C/readme.md


## to tar the files:
### tar cvf proj3C.tar image.C sink.C source.C PNMreader.C PNMwriter.C filter.C image.h sink.h source.h PNMreader.h PNMwriter.h filter.h

## to give permission to grader.sh:
### chmod u+r+x grader.sh


## to run the grader.sh:
### ./grader.sh proj3C.tar
