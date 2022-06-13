module SADF where
import ForSyDe.Shallow

 -- Netlist
system (s_a,s_b) = s_e where
    s_e = k_2 c_2 s_1 s_2 
    c_2 = d_2 s_b
    s_1 = c_act s_1_0
    s_2 = d_act s_2_0
    (s_1_0,s_2_0) = k_1 c_1 s_a
    c_1 = d_1 s_b




c_act = actor11SDF 1 1 f_1 where
    f_1 [x] = [x]

d_act = actor11SDF 1 1 f_2 where
    f_2 [x] = [-x]




k_1 = kernel12SADF 
k_2 = kernel21SADF

d_1 = detector11SADF consume_rate next_state_0 select_scenario_0 initial_state_0 where
    consume_rate = 1
    next_state_0 0 [s_b]= if s_b==1 then 1 else 0
    next_state_0 1 [s_b]= if s_b==0 then 0 else 1


d_2 = detector11SADF consume_rate next_state_1 select_scenario_1 initial_state_1 where
    consume_rate = 1
    next_state_1 0 [s_b]= if s_b==1 then 1 else 0
    next_state_1 1 [s_b]= if s_b==0 then 0 else 1


k_1_scenario_0 = (1, (1,0), \[x] -> ([x], [])) --true
k_1_scenario_1 = (1, (0,1), \[x] -> ([], [x])) --false

select_scenario_0 0 = (1, [k_1_scenario_0])
select_scenario_0 1 = (1, [k_1_scenario_1])


k_2_scenario_0 = ((1,0), 1, \[x] [] -> [x]) --true
k_2_scenario_1 = ((0,1), 1, \[] [x] -> [x])--false

select_scenario_1 0 = (1, [k_2_scenario_0])
select_scenario_1 1 = (1, [k_2_scenario_1])

initial_state_0 = 0
initial_state_1 = 0


s_test1 = signal [1..9]
s_test2 = signal [1,1,1,1,1,0,0,0,0]