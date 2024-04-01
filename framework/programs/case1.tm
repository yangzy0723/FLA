#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15,q16,q17,q18,q19,end}
#S = {a,b}
#G = {a,b,c,_,I,l,e,g,a,n,p,u,t}
#q0 = q0
#B = _
#F = {end}
#N = 3
q0 a__ _c_ rr* q2
q0 b__ ___ r** q1
q0 ___ ___ *** q1
q2 a__ _c_ rr* q2
q2 ___ ___ *** q1
q2 b__ __b r*r q3
q3 b__ __b r*r q3
q3 a__ ___ r** q1
q3 ___ ___ *ll q17
q1 *__ ___ r** q1
q1 ___ I__ r** q4
q4 ___ l__ r** q5
q5 ___ l__ r** q6
q6 ___ e__ r** q7
q7 ___ g__ r** q8
q8 ___ a__ r** q9
q9 ___ l__ r** q10
q10 ___ ___ r** q11
q11 ___ I__ r** q12
q12 ___ n__ r** q13
q13 ___ p__ r** q14
q14 ___ u__ r** q15
q15 ___ t__ *** q16
q17 _cb ccb rl* q17
q17 __b ___ *rl q18
q18 _c_ _c_ l** end
q18 _cb _cb *r* q19
q19 _cb _cb *r* q19
q19 __b __b *l* q17