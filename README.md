eemd-matlab
===========

EEMD family, Matlab version. PARFOR supported.

run `matlabpool open 8` to enable parallel computing.

# core functions

## emd.m

Empirical mode decomposition. No ensemble, no additional white noise.

```
c = emd(y, goal)
```

`y`: one-dimensional input data
`goal`: target mode numbers to decompose

## eemd.m

Ensemble empirical mode decomposition. 

```
modes = eemd(y, goal, ens, nos)
```

Please note if you are running with a 64-bit Windows PC, Matlab will automatically run with `eemd.mexw64` instead of this script.

## eemd2.m

```
modes = eemd2(img, goal, ens, nos_wn)
[modes, G, D] = eemd2(img, goal, ens, nos_wn)
```


## eemd3.m

```
modes = eemd3(img, goal, ens, nos_wn)
[modes, O, P, Q] = eemd3(img, goal, ens, nos_wn)
```



# Demo files

## eemd_2d_demo.m

Running this file will give you decomposed modes of a 64x64 Lena image. 


## eemd_3d_demo.m

Running this file will decompose a 54x54x54 volume of a Mimivirus.
Please be carful as running this demo will cost up to 20 GB memory.


# MEX compilaion

```
mex -IC:/path/to/boost_1_55_0 cpp/eemd.cpp
```

Replace `C:/path/to/boost_1_55_0` with path to Boost on your computer.

# Routine functions

## zerox.m

## find_extrema.m
