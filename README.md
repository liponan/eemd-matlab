# eemd-matlab
EEMD family, Matlab version. PARFOR supported. 

## Usage 

```
modes = emd(y, n_mode);
modes = eemd(y, n_mode, n_copies, amp_wn);
modes = eemd2(y, n_mode, n_copies, amp_wn);
modes = eemd3(y, n_mode, n_copies, amp_wn);
```


## MEX
`emd.cpp` is for mex compilation. You are definitly encouraged to complie your own MEX, but you need to have SNU Scientific Library (GSL) installed.
For mac user, you can use the command below, but remember to replace `/opt/local/include` with your own include path that contains `gsl/`.

```
mex -I/opt/local/include/ emd.cpp -lgsl -lgslcblas -lm
```

Or you can just use the precompiled `emd.mexmaci64`.
