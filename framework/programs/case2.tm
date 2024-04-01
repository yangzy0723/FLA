#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10}
#S = {a,b,c}
#G = {a,b,c,_,t,r,u,e,f,a,l,s}
#q0 = q0
#B = _
#F = {q10}
#N = 2
q0 a_ _a rr q0
q0 b_ _b rr q0
q0 c_ __ rl q1
q0 __ __ ** q3
q1 _a _a *l q1
q1 _b _b *l q1
q1 *a *a *l q1
q1 *b *b *l q1
q1 __ __ *r q2
q1 *_ *_ *r q2
q2 aa __ rr q2
q2 bb __ rr q2
q2 c* __ r* q3
q2 c_ __ r* q3
q2 ab __ r* q3
q2 ba __ r* q3
q2 _a __ r* q3
q2 _b __ r* q3
q2 a_ __ r* q3
q2 b_ __ r* q3
q3 a_ __ r* q3
q3 b_ __ r* q3
q3 c_ __ r* q3
q3 __ f_ r* q4
q4 __ a_ r* q5
q5 __ l_ r* q6
q6 __ s_ r* q7
q7 __ e_ ** q7
q2 __ t_ r* q8
q8 __ r_ r* q9
q9 __ u_ r* q10
q10 __ e_ ** q10