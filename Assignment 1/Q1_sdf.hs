 module CSF_to_SDF where

import ForSyDe.Shallow

-- Netlist
system s_in = (s_out_1, s_out_2) where

    s_1_0 = selectS 0 2 s_in  --offset, stepsize, signal
    s_1_1 = selectS 1 2 s_in


    s_2 = a_1_0 s_1_0
    s_3 = a_1_1 s_1_1

    s_out_1 = a_2 s_2
    s_out_2 = a_3 s_3

-- Process specification
a_1_0 = actor11SDF 1 1 func1 where
    func1 [x] = [x]

a_1_1 = actor11SDF 1 1 func2 where
    func2 [x] = [x]


a_2 = actor11SDF 1 1 func3 where
    func3 [x] = [x]

a_3 = actor11SDF 1 1 func4 where
    func4 [x] = [-x]       

-- Test Signal
s_test = signal [0..9]


    
    
