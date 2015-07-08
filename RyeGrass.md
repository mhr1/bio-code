# Introduction #




# Details #

rye\_blast.cpp is the main C++ code for picking RADs with q values > 0.5 and calling blast to find sequences matches on the rice genome. It then parses the blast file results and presents them in a more meaningful way.

rye\_job.cpp when compiled makes rye\_blast jobs for running on Beowulf. Without this the blast jobs would take approx 200 hours to run on a fast PC.

rgf.pl is a Perl script used to locate genomic regions in which the RAD markers have a match.

Results file Contains:
Rice Chromosome, Ryegrass Linkage grp, Locus, E, %Id, Length, Rad ID, Rice ORF ID, Decription of ORF

Used Perl script rgf.pl to locate genomic regions in which the RAD markers had a match