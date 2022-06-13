module SADF where
import ForSyDe.Shallow

 -- Netlist
system (sin_a, sin_b, sin_c) = s_out where
    s_out = k_1 c_1 sin_a sin_b
    c_1 = d_1 sin_c

k_1 = kernel21SADF 

d_1 = detector11SADF consume_rate next_state select_scenario initial_state where
    consume_rate = 1
    next_state 0 [s_b]= if s_b==1 then 1 else 0
    next_state 1 [s_b]= if s_b==0 then 0 else 1

-- k_1_scenario_0 = ((1,0), 1, \([x],[x]) -> [x] --true
-- k_1_scenario_1 = ((0,1), 1, \([x],[x]) -> [x] --false

k_1_scenario_0 = ((1,0), 1, \[x] [] -> [x]) --true
k_1_scenario_1 = ((0,1), 1, \[] [x] -> [x])--false



select_scenario 0 = (1, [k_1_scenario_0])
select_scenario 1 = (1, [k_1_scenario_1])

initial_state = 0


s_test1 = signal [1..3]
s_test2 = signal [4..6]
s_test3 = signal [1]