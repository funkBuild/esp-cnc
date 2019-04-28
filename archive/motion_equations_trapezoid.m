pkg load symbolic;

syms a t_a v_e v_i v_m

t_a = (v_m - v_i)/a
t_b = (v_m - v_e) / a
d_a = (a*(t_a^2))/2 + v_i * t_a
d_b = v_m * t_b - (a*(t_b^2))/2

d = d_a + d_b

simp_expr = simplify(d)


