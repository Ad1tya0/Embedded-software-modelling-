module SADF where
import ForSyDe.Shallow

 -- Netlist
system s_in = (s_out1, s_out2) where
    (s_out1, s_out2) = k_1 c_1 s_in
    c_1 = d_1 s_in

k_1 = kernel12SADF 

d_1 = detector11SADF consume_rate next_state select_scenario initial_state where
    consume_rate = 1
    next_state 0 _= 1
    next_state 1 _= 0

k_1_scenario_0 = (1, (1,0), \[x] -> ([x], []))
k_1_scenario_1 = (1, (0,1), \[x] -> ([], [-x]))

select_scenario 0 = (1, [k_1_scenario_0])
select_scenario 1 = (1, [k_1_scenario_1])

initial_state = 0


s_test = takeS 10 $ infiniteS (+1) 0