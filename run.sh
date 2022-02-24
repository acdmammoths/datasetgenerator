#!/bin/sh

# a simple script to drive the generation of synthetic datasets


# Command Line Options:
#   -ntrans number_of_transactions_in_000s (default: 1000)
#   -tlen avg_items_per_transaction (default: 10)
#   -nitems number_of_different_items_in_000s) (default: 100)
# 
#   -npats number_of_patterns (default: 10000)
#   -patlen avg_length_of_maximal_pattern (default: 4)
#   -corr correlation_between_patterns (default: 0.25)
#   -conf avg_confidence_in_a_rule (default: 0.75)
# 
#   -fname <filename> (write to filename.data and filename.pat)
#   -ascii (default: False)
#   -randseed # (reset seed used generate to x-acts; must be negative)
#   -version (to print out version info)

L_TLEN="10"                    # T
L_NTRANS="20"               # D
L_NITEMS="1"                   # N

NPATS=2000                     # L 
PATLEN=8                      # I
CORR=0.25
CONF=0.75
ASCII="-ascii"
RANDSEED=
#RANDSEED=-123456789

OUTPATH="."
#--------------------------------------------------------------------

for NTRANS in ${L_NTRANS}; do 
  for TLEN in ${L_TLEN}; do
    for NITEMS in ${L_NITEMS}; do

      FNAME="$OUTPATH/data_${NTRANS}k_t${TLEN}_p${PATLEN}_l${NPATS}_n${NITEMS}k"
      OPT="-ntrans ${NTRANS} -tlen ${TLEN} -nitems ${NITEMS} -npats ${NPATS}"
      OPT="${OPT} -patlen ${PATLEN} -corr ${CORR} -conf ${CONF}"
      OPT="${OPT} -fname ${FNAME} ${ASCII}"

      comm="./gen lit $OPT"

      echo $comm
      $comm

    done
  done
done
