module SADF where
import ForSyDe.Shallow

 -- Netlist
system s_in = s_out where
    s_out = k_1 c_1 s_in
    c_1 = d_1 s_outFeed
    s_outFeed = delaySY 0 s_out
  --  s_b = k_1 s_in c_1

k_1 = kernel11SADF 

d_1 = detector11SADF consume_rate next_state select_scenario initial_state where   
    consume_rate = 1
    next_state 0 [s_out]= if s_out>20 then 1 else 0
    next_state 1 [s_out]= if s_out<10 then 0 else 1

k_1_scenario_0 = (3, 1, \[x1,x2,x3] -> [x1 + x2 + x3]) --true
k_1_scenario_1 = (2, 1, \[x1,x2] -> [x1 + x2]) --false

select_scenario 0 = (1, [k_1_scenario_0])
select_scenario 1 = (1, [k_1_scenario_1])

initial_state = 0


s_test1 = signal [4,5,6,8,8,9,9,8,2,4,8,5,2]
