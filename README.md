# Equal-Cost Multi-Path (ECMP) Implementation in ns-3

As a part of the
[MMPTCP](https://ieeexplore.ieee.org/document/7524530) project, I have
implemented several ECMP modes in ns-3. These are random, per-flow
(hash-based) and round-robin modes.

To demonstrate these ECMP modes I have made a few videos, you can find
them as follows:

* TCP with round-robin ECMP ([YouTube](https://youtu.be/qTgAiNL0SO8))
* UDP with round-robin ECMP ([YouTube](https://youtu.be/7fx9cvg0egk))
* TCP with hash-based ECMP ([YouTube](https://youtu.be/6D_ip8H0LXU))
* TCP with random ECMP ([YouTube](https://youtu.be/z3yIgC32RdA))
* TCP with no ECMP ([YouTube](https://youtu.be/6oA1EopvU0o))

# Installations

1. Clone the ECMP's repository.

``` shell
git clone https://github.com/mkheirkhah/ecmp.git
```

2. Configure and build the ns-3 simulator

``` shell
CXXFLAGS="-Wall" ./waf configure build 
```

3. Run a simulation

``` shell
./waf --run "ecmp"
```

Note that we have written a simple simulation script to demonstrate
how to use the ECMP modes available in this repository. You can find
it in the [scratch](./scratch/) folder.

# Reference

If you use this code in part or entirely, please consider citing the
MMPTCP paper where this code was developed as part of it.

``` text
@inproceedings{kheirkhah2016mmptcp,
  title={{MMPTCP: A multipath transport protocol for data centers}},
  author={Kheirkhah, Morteza and Wakeman, Ian and Parisis, George},
  booktitle={IEEE INFOCOM 2016 - The 35th Annual IEEE International Conference on Computer Communications},
  pages={1-9},
  month={April},
  year={2016},
  doi={10.1109/INFOCOM.2016.7524530}
}
```

# Contact

``` shell
Morteza Kheirkhah, University College London (UCL), m.kheirkhah@ucl.ac.uk
```

