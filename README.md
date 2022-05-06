# APSP_algorithm

This is the implementation of algorithm developed by Loukides and Pissis to solve the all-pairs suffix/prefix (APSP) problem [[1]](https://doi.org/10.1016/j.ipl.2022.106275). 
This algorithm changes the APSP problem to *l*-APSP, where *l* defines the minimal overlap of the pairs. 

The current implementation does not provide the option to change *l*.

## Running the algorithm
To run the algorithm: `./bin/algorithm INPUT_FILE OUTPUT_FILE`

The `INPUT_FILE` should be a FASTA file and the `OUTPUT_FILE` will be a tab-delimited file.

### References
<a id="1">[1]</a> 
G. Loukides and S.P. Pissis (2022). 
All-pairs suffix/prefix in optimal time using Aho-Corasick space. 
Information Processing Letters, 106275, doi: https://doi.org/10.1016/j.ipl.2022.106275.
