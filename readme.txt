HFKM Version 1.0 (September 2018)

A program to compute HFK^-(K) from grid diagrams.
Author: Daniel Rostovtsev

Table of contents:
    1. Install
    2. Command usage
    3. Example
    4. Uninstall
    5. Useful information

1. Install

2. Command usage:

    diff:   ./diff <dir> <a> <m>
            ./diff <dir> <i>

            Used to find the differential of a given chain group, or a grid 
            generator.

            - <dir>:    The directory in which the knot generators were saved.

            - <a>:      The Alexander grading.

            - <m>:      The Maslov grading.

            - <i>:      The factoradic index of a grid permutation.

            *NOTE:* the generators must already have been created by gen
            beforehand.

            Example: ./diff tr5x5 0

            Example: ./diff tr5x5 0 0

    gen:    ./gen <x_list> <o_list> <dir>

            Used to compute all the generators of a given knot, and save them 
            for later use.

            - <x_list>: The x permutations as a list of integers separated by 
                        commas with no spaces.

            - <o_list>: The o permutations as a list of integers separated by 
                        commas with no spaces.

            - <dir>:    The directory in which the generators will be saved. 
                        
            *NOTE:* The directory must be created manually before ./gen is 
            run.

            Example: ./gen 4,0,1,2,3 1,2,3,4,0 tr5x5 (for the trefoil)

    hfkm:   ./hfkm <dir> <a> <m>

            Used to compute HFK^-(K) once gen is run.

            - <dir>:    The directory in which the knot generators were saved.

            - <a>:      The Alexander grading of the homology to 
                        be computed.

            - <m>:      The Maslov grading of the homology to be 
                        computed.

            *NOTE:* the generators must already have been created by gen
            beforehand.

            Example: ./hfkm tr5x5 0 0

    itop:   ./itop <k>
            ./itop <k> <i>

            Used to find permutations of size k given factoradic indices. If 
            no index is specified, then all permutations of size k, and their
            indices, are listed.

            - <k>:      Permutation size, or equivalently, grid size.

            - <i>:      Factoradic index.

            Example: ./itop 3
            
            Example: ./itop 3 0

3. Example on *NIX systems:

    To find HFK^- of the right handed trefoil and (a,m) bigrading (0,0):

    [usr]@[hostname] [hfk_dir] $    mkdir tr5x5
    [usr]@[hostname] [hfk_dir] $    ./gen 4,0,1,2,3 1,2,3,4,0 tr5x5
    [usr]@[hostname] [hfk_dir] $    ./hfkm tr5x5 0 0

4. Uninstall:

5. Useful information:

    To see all the bigradings of generators on the grid diagram:

    [usr]@[hostname] [hfk_dir] $    ls <dir>

    This will list all files <a>_<m>.txt, corresponding to (a,m) bigradings 
    for which there is at least one generator on the grid diagram. The files
    jtp.txt and done.txt may be shown as well. jtp.txt is the save file for 
    the gen command, in case it has to clear memory between computations to 
    avoid crashes. done.txt is used to determine whether all the generators 
    have been found yet.

    dir/a_m.txt contains an integer on each line, corresponding to the 
    factoradic index of the grid generator on the diagram.

    *NOTE:* DO NOT delete or edit any files in <dir>, otherwise you may have 
    to run ./gen again.
